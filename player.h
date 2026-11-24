/*

-------------------------------------------------------------------------

    Player class is used to play songs, stream songs, stream radio;
        inside uses bypass to pass through some defensers

-------------------------------------------------------------------------

*/

#ifndef PLAYER_H
#define PLAYER_H

#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QObject>
#include <QString>

// side lib to connect radios url
#include "bass.h"

#include "songitem.h"
#include "radioitem.h"
#include "networkbypass.h"

namespace MusicPlayer {

enum STREAM_TYPE {
    SONG,
    RADIO
};

class Player final : public QObject
{
    Q_OBJECT

public:

    explicit Player();
    ~Player() override;

    Player(const MusicPlayer::Player&) = delete;
    Player& operator = (const MusicPlayer::Player&) = delete;

    Player(MusicPlayer::Player&&) = delete;
    Player& operator = (MusicPlayer::Player&&) = delete;

    bool setSong(const Song::SongItem& song);
    bool setRadioStream(const Radio::RadioItem& radio);

    bool play();
    bool stop();
    bool pause();

    void setPosition(quint64 position);
    QMediaPlayer::PlaybackState state() const;

private:

    QMediaPlayer* player_;
    QAudioOutput* output_;
    Api::NetworkBypass* bypass_;

    STREAM_TYPE stream_type_ = SONG;

    // side bass.dll lib
    HSTREAM radio_stream_ = 0;
    bool bass_initialized_ = false;

private:

    bool bassInit();

signals:

    void error(QString message);
    void playbackStateChanged(QMediaPlayer::PlaybackState state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void songFinished();
    void songLoaded();
};

}

#endif // PLAYER_H