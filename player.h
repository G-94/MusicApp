/*

-------------------------------------------------------------------------



-------------------------------------------------------------------------

*/

#ifndef PLAYER_H
#define PLAYER_H

#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QObject>
#include <QString>

#include "songitem.h"

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

private:

    QMediaPlayer* player_;
    QAudioOutput* output_;

signals:

    void error(QString message);
    void playbackStateChanged(QMediaPlayer::PlaybackState state);
    void positionChanged(unsigned int position);
    void durationChanged(unsigned int duration);

};

}

#endif // PLAYER_H