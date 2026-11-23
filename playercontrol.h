/*

-------------------------------------------------------------------------



-------------------------------------------------------------------------

*/


#ifndef PLAYERCONTROL_H
#define PLAYERCONTROL_H

#include <QObject>
#include <QString>
#include <QVector>

#include "songitem.h"
#include "radioitem.h"
#include "player.h"

class PlayerControl : public QObject
{
    Q_OBJECT
public:
    PlayerControl(QObject* parent = nullptr);

private:

    MusicPlayer::Player* player_;

    std::shared_ptr<QVector<Song::SongItem>> current_tracklist_;
    // Song::SongItem current_song_;

signals:

};

#endif // PLAYERCONTROL_H