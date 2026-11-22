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

#include "songitem.h"
#include "networkbypass.h"

namespace MusicPlayer {

class Player : public QObject
{
    Q_OBJECT

public:

    explicit Player();

    bool setSong(const Song::SongItem& song);
    bool play();
    bool stop();
    bool pause();

    void setPosition(quint64 position);
    QMediaPlayer::PlaybackState state() const;

private:

    QMediaPlayer* player_;
    QAudioOutput* output_;
    Api::NetworkBypass* bypass_;

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