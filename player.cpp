#include "player.h"

MusicPlayer::Player::Player() : player_(nullptr), output_(nullptr), bypass_(nullptr)
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

    bypass_->getMirrorUrl(url);

    return true;
}

bool MusicPlayer::Player::play()
{
    player_->play();
    return true;
}

bool MusicPlayer::Player::stop()
{
    player_->stop();
    return true;
}

bool MusicPlayer::Player::pause()
{
    player_->pause();
    return true;
}

void MusicPlayer::Player::setPosition(quint64 position)
{
    player_->setPosition(position);
}