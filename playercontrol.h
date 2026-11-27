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
#include "userdatamanager.h"
#include "player.h"

class PlayerControl final : public QObject
{
    Q_OBJECT
public:
    PlayerControl(User_Data::UserDataManager* manager_, QObject* parent = nullptr);

private:

    MusicPlayer::Player* player_;
    User_Data::UserDataManager* manager_;

    std::shared_ptr<QVector<Song::SongItem>> current_tracklist_;
    int current_song_id_ = -1;

public:

    Song::SongItem getCurrentSong() const;

public:

    bool play();
    bool stop();
    bool pause();
    void setPosition(quint64 position);

    void nextSong();
    void previousSong();

    void likeSong();
    void downloadSong();

    void removeSongFromLiked();
    void removeSongFromDownloaded();

public:

    void setTracklist(std::shared_ptr<QVector<Song::SongItem>> tracklist);
    void setRadio(const Radio::RadioItem& radio);

signals:

    void trackChanged();
    void positionChanged(qint64 position);
    void stateChanged(bool playing);
    void trackFinished();
    void error(const QString& msg);

};

#endif // PLAYERCONTROL_H