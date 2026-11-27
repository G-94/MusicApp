#include "player.h"

MusicPlayer::Player::Player(QObject* parent) :
    QObject(parent), player_(nullptr), output_(nullptr), bypass_(nullptr)
{
    player_ = new QMediaPlayer(this);
    output_ = new QAudioOutput(this);
    bypass_ = new Api::NetworkBypass(this);

    player_->setAudioOutput(output_);
    output_->setVolume(1.0);

    QObject::connect(player_, &QMediaPlayer::playbackStateChanged, this, &Player::playbackStateChanged);
    QObject::connect(player_, &QMediaPlayer::positionChanged, this, &Player::positionChanged);
    QObject::connect(player_, &QMediaPlayer::durationChanged, this, &Player::durationChanged);

    QObject::connect(player_, &QMediaPlayer::errorOccurred, this,
                     [this](QMediaPlayer::Error, const QString &msg) {
        emit error(msg);
    });

    QObject::connect(player_, &QMediaPlayer::mediaStatusChanged, this, [this] (auto status) {
        if (status == QMediaPlayer::EndOfMedia)
            emit songFinished();
    });

    QObject::connect(bypass_, &Api::NetworkBypass::mirrorFind, [this](QUrl result) {
        player_->stop();
        player_->setSource(result);
        emit songLoaded();
    });

    QObject::connect(bypass_, &Api::NetworkBypass::error, [this](QString msg) {
        qDebug() << msg;
    });
}

MusicPlayer::Player::~Player()
{
    if (radio_stream_ != 0) {
        BASS_ChannelStop(radio_stream_);
        BASS_StreamFree(radio_stream_);
        radio_stream_ = 0;
    }

    if (bass_initialized_) {
        BASS_Free();
        bass_initialized_ = false;
    }
}

bool MusicPlayer::Player::setSong(const Song::SongItem &song)
{
    if (not song.isPlayable()) return false;

    QUrl url;

    if (song.isDownloaded()) {
        if (song.getLocalPath().isEmpty())
            return false;
        url = QUrl::fromLocalFile(song.getLocalPath());
    } else {
        url = QUrl(song.getSourceUrl());
    }

    if (not url.isValid() or url.isEmpty()) {
        return false;
    }

    stream_type_ = SONG;
    bypass_->getMirrorUrl(url);

    return true;
}

bool MusicPlayer::Player::setRadioStream(const Radio::RadioItem &radio)
{
    QUrl stream_url = radio.getSourceUrl();
    qDebug() << stream_url;

    if (not stream_url.isValid() or stream_url.isEmpty()) return false;

    if (not bassInit()) {
        emit error("Bass lib init error");
        return false;
    }

    this->stop();

    const QByteArray url_bytes = stream_url.toString().toUtf8();
    radio_stream_ = BASS_StreamCreateURL(
        url_bytes.constData(),
        0,
        0,
        nullptr,
        nullptr
    );

    if (radio_stream_ == 0) {
        emit error("Radio stream failed");
        return false;
    }

    stream_type_ = RADIO;

    return true;
}

bool MusicPlayer::Player::play()
{
    if (stream_type_ == RADIO) {
        if (!BASS_ChannelPlay(radio_stream_, FALSE)) {
            BASS_StreamFree(radio_stream_);
            radio_stream_ = 0;
            return false;
        }
    } else {
        player_->play();
    }

    return true;
}

bool MusicPlayer::Player::stop()
{
    if (stream_type_ == RADIO) {
        BASS_ChannelStop(radio_stream_);
        BASS_StreamFree(radio_stream_);
        radio_stream_ = 0;
    } else {
        player_->stop();
    }
    return true;
}

bool MusicPlayer::Player::pause()
{
    if (stream_type_ == RADIO) return false;
    player_->pause();
    return true;
}

void MusicPlayer::Player::setPosition(quint64 position)
{
    player_->setPosition(position);
}

bool MusicPlayer::Player::bassInit()
{
    if (!bass_initialized_) {
        if (!BASS_Init(-1, 44100, 0, nullptr, nullptr)) {
            emit error("BASS init failed");
            return false;
        }
        BASS_PluginLoad("bass_aac.dll", 0);
        bass_initialized_ = true;
    }
    return true;
}