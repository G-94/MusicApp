/*

-------------------------------------------------------------------------



-------------------------------------------------------------------------

*/

#ifndef USERDATAMANAGER_H
#define USERDATAMANAGER_H

#include <QString>
#include <QVector>

#include "musicapi.h"
#include "songitem.h"
#include "radioitem.h"
#include "artistitem.h"
#include "collectionitem.h"
#include "albumitem.h"
#include "userdataloader.h"
#include "paths.h"

namespace User_Data {

class UserDataManager
{
public:
    UserDataManager(std::shared_ptr<Api::MusicApi> api);

    //async func that loads user data
    bool preloadUserData();

private:

    std::shared_ptr<Api::MusicApi> api_;
    User_Data::UserDataLoader loader_;

    QVector<Song::SongItem> familiar_tracklist_;
    QVector<Song::SongItem> liked_tracklist_;
    QVector<Song::SongItem> downloaded_tracklist_;

    QVector<Artists::ArtistItem> familiar_artists_;
    QVector<Album::AlbumItem> familiar_albums_;
    QVector<Collection::CollectionItem> familiar_collections_;

    QVector<Radio::RadioItem> radio_stations_list_;;

private:

    bool loadRadios();
    bool loadTouchedSongs();
    bool loadFamiliarSongs();
    bool loadFamiliarArtists();
    bool loadFamiliarAlbums();
    bool loadFamiliarCollections();

private:

    // TODO: make a cache rules for songs

signals:

};

}

#endif // USERDATAMANAGER_H