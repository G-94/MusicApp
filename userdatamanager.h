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

/*
 *
 *
 *       TODO:
 *          ADD GENRES!!!!
 *
 *
 *
*/

class UserDataManager final : public QObject
{

    Q_OBJECT
public:
    UserDataManager();

    //async func that loads all user data
    void preloadUserData(std::shared_ptr<Api::MusicApi> music_api);

public:

    // savers async
    void saveFamiliarRadios();
    void saveLikedDownlaodedSongs();
    void saveFamiliarSongs();
    void saveFamiliarArtists();
    void saveFamiliarAlbums();
    void saveFamiliarCollections();

private:

    // loaders async
    void loadFamiliarRadios();
    void loadLikedDownloadedSongs();
    void loadFamiliarSongs();
    void loadFamiliarArtists();
    void loadFamiliarAlbums();
    void loadFamiliarCollections();

public:

    // async load radios
    void loadRadiosOnline(std::shared_ptr<Api::MusicApi> api);

private:

    //getters
    const QVector<Song::SongItem>& getFamiliarTracklist() const noexcept;
    const QVector<Song::SongItem>& getLikedTracklist() const noexcept;
    const QVector<Song::SongItem>& getDownloadedTracklist() const noexcept;

    const QVector<Artists::ArtistItem>& getFamiliarArtists() const noexcept;
    const QVector<Album::AlbumItem>& getFamiliarAlbums() const noexcept;
    const QVector<Collection::CollectionItem>& getFamiliarCollections() const noexcept;

    const QVector<Radio::RadioItem>& getFamiliarRadios() const noexcept;
    const QVector<Radio::RadioItem>& getRadioStationsList() const noexcept;

    const QVector<Song::SongItem>& getHistoryTracklist() const noexcept;

private:

    User_Data::UserDataLoader loader_;

    // player's states
    QVector<Song::SongItem> familiar_tracklist_;
    QVector<Song::SongItem> liked_tracklist_;
    QVector<Song::SongItem> downloaded_tracklist_;

    QVector<Artists::ArtistItem> familiar_artists_;
    QVector<Album::AlbumItem> familiar_albums_;
    QVector<Collection::CollectionItem> familiar_collections_;

    QVector<Radio::RadioItem> familiar_radios_;
    QVector<Radio::RadioItem> radio_stations_list_;

    QVector<Song::SongItem> history_tracklist_;

private:

    // TODO: make a cache rules for songs

public:

    // adders
    void addLikedSong(const Song::SongItem& song);
    void addDownloadedSong(const Song::SongItem& song);
    void addFamiliarSong(const Song::SongItem& song);
    void addFamiliarArtist(const Artists::ArtistItem& artist);
    void addFamiliarAlbum(const Album::AlbumItem& album);
    void addFamiliarCollection(const Collection::CollectionItem& collection);
    void addFamiliarRadio(const Radio::RadioItem& radio);
    void addSongToHistory(const Song::SongItem& song);

    // removers
    bool removeSongFromLiked(const Song::SongItem& song);
    bool removeSongFromDownloaded(const Song::SongItem& song);

signals:

    void familiarRadiosLoaded();
    void familiarRadiosSaved();

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

    void radiosOnlineLoaded();

    void error(QString msg);
};

}

#endif // USERDATAMANAGER_H