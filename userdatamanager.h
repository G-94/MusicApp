/*

-------------------------------------------------------------------------



-------------------------------------------------------------------------

*/

#ifndef USERDATAMANAGER_H
#define USERDATAMANAGER_H

#include <QString>
#include <QObject>
#include <QVector>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrentRun>

#include "musicapi.h"
#include "songitem.h"
#include "radioitem.h"
#include "artistitem.h"
#include "collectionitem.h"
#include "albumitem.h"
#include "userdataloader.h"
#include "paths.h"

namespace User_Data {

class UserDataManager : public QObject
{

    Q_OBJECT
public:
    UserDataManager();
    // UserDataManager(std::shared_ptr<Api::MusicApi> api);

    //async func that loads user data
    void preloadUserData();

    void saveLikedDownlaodedSongs();

    void addLikedSong(const Song::SongItem& song);
    void addDownloadedSong(const Song::SongItem& song);

private:

    std::shared_ptr<Api::MusicApi> api_;
    User_Data::UserDataLoader loader_;

    QVector<Song::SongItem> familiar_tracklist_;
    QVector<Song::SongItem> liked_tracklist_;
    QVector<Song::SongItem> downloaded_tracklist_;

    QVector<Artists::ArtistItem> familiar_artists_;
    QVector<Album::AlbumItem> familiar_albums_;
    QVector<Collection::CollectionItem> familiar_collections_;

    QVector<Radio::RadioItem> radio_stations_list_;

private:

    // void loadRadios();
    void loadLikedDownloadedSongs();
    void loadFamiliarSongs();
    void loadFamiliarArtists();
    void loadFamiliarAlbums();
    void loadFamiliarCollections();

private:

    // TODO: make a cache rules for songs

signals:

    // void radiosLoaded();
    // void radiosSaved();

    void likedDownloadedSongsLoaded();
    void likedDownloadedSongsSaved();

    void familiarSongsLoaded();
    void familiarSongsSaved();

    void familiarArtistsLoaded();
    void familiarArtistsSaved();

    void familiarAlbumsLoaded();
    void familiarAlbumsSaved();

    void familiarCollectionsLoaded();
    void familiarCollectionsSaved();

    void error(QString msg);
};

}

#endif // USERDATAMANAGER_H