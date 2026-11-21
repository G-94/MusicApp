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

};

}

#endif // PLAYER_H