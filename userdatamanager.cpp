#include "userdatamanager.h"

User_Data::UserDataManager::UserDataManager()
{

}

void User_Data::UserDataManager::preloadUserData()
{

}

void User_Data::UserDataManager::saveFamiliarRadios()
{
    QString path = Paths::familiarRadiosPath();
    const QVector<Radio::RadioItem> familiar_radios_copy = this->familiar_radios_;

    auto future = QtConcurrent::run([this, path, familiar_radios_copy]() -> bool {
        return loader_.saveMusicItems(path, familiar_radios_copy);
    });

    auto* watcher = new QFutureWatcher<bool>(this);
    QObject::connect(watcher, &QFutureWatcherBase::finished, this, [this, watcher]() {
        watcher->deleteLater();
        bool result = watcher->result();

        if (result) {
            emit familiarRadiosSaved();
        } else {
            emit error("Error while saving familiarRadios");
        }
    });

    watcher->setFuture(future);
}

void User_Data::UserDataManager::saveLikedDownlaodedSongs()
{
    QString path = Paths::likedAndDownloadsSongsPath();

    const QVector<Song::SongItem> liked_copy = liked_tracklist_;
    const QVector<Song::SongItem> downloaded_copy = downloaded_tracklist_;

    auto future = QtConcurrent::run([this, path, liked_copy, downloaded_copy]() -> bool {
        QSet<QString> unique_songs_ids;
        QVector<Song::SongItem> merged;
        merged.reserve(liked_copy.size() + downloaded_copy.size());

        // add only unique songs

        for (const Song::SongItem& song : liked_copy) {
            if (not unique_songs_ids.contains(song.getId())) {
                unique_songs_ids.insert(song.getId());
                merged.append(song);
            }
        }

        for (const Song::SongItem& song : downloaded_copy) {
            if (not unique_songs_ids.contains(song.getId())) {
                unique_songs_ids.insert(song.getId());
                merged.append(song);
            }
        }

        return loader_.saveMusicItems(path, merged);
    });

    auto* watcher = new QFutureWatcher<bool>(this);
    QObject::connect(watcher, &QFutureWatcherBase::finished, this, [this, watcher]() {
        watcher->deleteLater();
        bool result = watcher->result();

        if (result) {
            emit likedDownloadedSongsSaved();
        } else {
            emit error("Error while saving likedDownloadedSongs");
        }
    });

    watcher->setFuture(future);
}

void User_Data::UserDataManager::saveFamiliarSongs()
{
    QString path = Paths::familiarSongsPath();
    const QVector<Song::SongItem> familiar_tracklist_copy = this->familiar_tracklist_;

    auto future = QtConcurrent::run([this, path, familiar_tracklist_copy]() -> bool {
        return loader_.saveMusicItems(path, familiar_tracklist_copy);
    });

    auto* watcher = new QFutureWatcher<bool>(this);
    QObject::connect(watcher, &QFutureWatcherBase::finished, this, [this, watcher]() {
        watcher->deleteLater();
        bool result = watcher->result();

        if (result) {
            emit familiarSongsSaved();
        } else {
            emit error("Error while saving familiarSongs");
        }
    });

    watcher->setFuture(future);
}

void User_Data::UserDataManager::saveFamiliarArtists()
{
    QString path = Paths::familiarArtistsPath();
    const QVector<Artists::ArtistItem> familiar_artists_copy = this->familiar_artists_;

    auto future = QtConcurrent::run([this, path, familiar_artists_copy]() -> bool {
        return loader_.saveMusicItems(path, familiar_artists_copy);
    });

    auto* watcher = new QFutureWatcher<bool>(this);
    QObject::connect(watcher, &QFutureWatcherBase::finished, this, [this, watcher]() {
        watcher->deleteLater();
        bool result = watcher->result();

        if (result) {
            emit familiarArtistsSaved();
        } else {
            emit error("Error while saving familiarArtists");
        }
    });

    watcher->setFuture(future);
}

void User_Data::UserDataManager::saveFamiliarAlbums()
{
    QString path = Paths::familiarAlbumsPath();
    const QVector<Album::AlbumItem> familiar_albums_copy = this->familiar_albums_;

    auto future = QtConcurrent::run([this, path, familiar_albums_copy]() -> bool {
        return loader_.saveMusicItems(path, familiar_albums_copy);
    });

    auto* watcher = new QFutureWatcher<bool>(this);
    QObject::connect(watcher, &QFutureWatcherBase::finished, this, [this, watcher]() {
        watcher->deleteLater();
        bool result = watcher->result();

        if (result) {
            emit familiarAlbumsSaved();
        } else {
            emit error("Error while saving familiarAlbums");
        }
    });

    watcher->setFuture(future);
}

void User_Data::UserDataManager::saveFamiliarCollections()
{
    QString path = Paths::familiarCollectionsPath();
    const QVector<Collection::CollectionItem> familiar_collections_copy = this->familiar_collections_;

    auto future = QtConcurrent::run([this, path, familiar_collections_copy]() -> bool {
        return loader_.saveMusicItems(path, familiar_collections_copy);
    });

    auto* watcher = new QFutureWatcher<bool>(this);
    QObject::connect(watcher, &QFutureWatcherBase::finished, this, [this, watcher]() {
        watcher->deleteLater();
        bool result = watcher->result();

        if (result) {
            emit familiarCollectionsSaved();
        } else {
            emit error("Error while saving familiarCollections");
        }
    });

    watcher->setFuture(future);
}

void User_Data::UserDataManager::loadFamiliarRadios()
{
    QString path = Paths::familiarRadiosPath();
    auto future = QtConcurrent::run([this, path]() -> QVector<Radio::RadioItem> {
        return loader_.loadMusicItems<Radio::RadioItem>(path);
    });

    auto* watcher = new QFutureWatcher<QVector<Radio::RadioItem>>(this);
    QObject::connect(watcher, &QFutureWatcherBase::finished, this, [this, watcher]() {
        watcher->deleteLater();
        this->familiar_radios_ = watcher->result();

        emit familiarRadiosLoaded();
    });

    watcher->setFuture(future);
}

void User_Data::UserDataManager::loadLikedDownloadedSongs()
{
    QString path = Paths::likedAndDownloadsSongsPath();
    auto future = QtConcurrent::run([this, path]() -> QVector<Song::SongItem> {
        return loader_.loadMusicItems<Song::SongItem>(path);
    });

    auto* watcher = new QFutureWatcher<QVector<Song::SongItem>>(this);
    QObject::connect(watcher, &QFutureWatcherBase::finished, this, [this, watcher] () {
        watcher->deleteLater();
        QVector<Song::SongItem> data = watcher->result();

        // clear to add new data
        this->liked_tracklist_.clear();
        this->downloaded_tracklist_.clear();

        this->liked_tracklist_.reserve(data.size());
        this->downloaded_tracklist_.reserve(data.size());

        // check songs and adding them in tracklists
        for (Song::SongItem& song : data) {
            const bool liked = song.isLiked();
            const bool downloaded = song.isDownloaded();

            if (liked and downloaded) {
                this->liked_tracklist_.append(song);
                this->downloaded_tracklist_.append(std::move(song));
            } else if (liked) {
                this->liked_tracklist_.append(std::move(song));
            } else if (downloaded) {
                this->downloaded_tracklist_.append(std::move(song));
            }
        }

        emit likedDownloadedSongsLoaded();
    });

    watcher->setFuture(future);
}

void User_Data::UserDataManager::loadFamiliarSongs()
{
    QString path = Paths::familiarSongsPath();
    auto future = QtConcurrent::run([this, path]() -> QVector<Song::SongItem> {
        return loader_.loadMusicItems<Song::SongItem>(path);
    });

    auto* watcher = new QFutureWatcher<QVector<Song::SongItem>>(this);
    QObject::connect(watcher, &QFutureWatcherBase::finished, this, [this, watcher]() {
        watcher->deleteLater();
        this->familiar_tracklist_ = watcher->result();

        emit familiarSongsLoaded();
    });

    watcher->setFuture(future);
}

void User_Data::UserDataManager::loadFamiliarArtists()
{
    QString path = Paths::familiarArtistsPath();
    auto future = QtConcurrent::run([this, path]() -> QVector<Artists::ArtistItem> {
        return loader_.loadMusicItems<Artists::ArtistItem>(path);
    });

    auto* watcher = new QFutureWatcher<QVector<Artists::ArtistItem>>(this);
    QObject::connect(watcher, &QFutureWatcherBase::finished, this, [this, watcher]() {
        watcher->deleteLater();
        this->familiar_artists_ = watcher->result();

        emit familiarArtistsLoaded();
    });

    watcher->setFuture(future);
}

void User_Data::UserDataManager::loadFamiliarAlbums()
{
    QString path = Paths::familiarAlbumsPath();
    auto future = QtConcurrent::run([this, path]() -> QVector<Album::AlbumItem> {
        return loader_.loadMusicItems<Album::AlbumItem>(path);
    });

    auto* watcher = new QFutureWatcher<QVector<Album::AlbumItem>>(this);
    QObject::connect(watcher, &QFutureWatcherBase::finished, this, [this, watcher]() {
        watcher->deleteLater();
        this->familiar_albums_ = watcher->result();

        emit familiarAlbumsLoaded();
    });

    watcher->setFuture(future);
}

void User_Data::UserDataManager::loadFamiliarCollections()
{
    QString path = Paths::familiarCollectionsPath();
    auto future = QtConcurrent::run([this, path]() -> QVector<Collection::CollectionItem> {
        return loader_.loadMusicItems<Collection::CollectionItem>(path);
    });

    auto* watcher = new QFutureWatcher<QVector<Collection::CollectionItem>>(this);
    QObject::connect(watcher, &QFutureWatcherBase::finished, this, [this, watcher]() {
        watcher->deleteLater();
        this->familiar_collections_ = watcher->result();

        emit familiarCollectionsLoaded();
    });

    watcher->setFuture(future);
}

void User_Data::UserDataManager::loadRadiosOnline(std::shared_ptr<Api::MusicApi> api)
{
    QObject::connect(api.get(), &Api::MusicApi::radiosListLoaded,
        [this](std::shared_ptr<QVector<Radio::RadioItem>> result) {
            if (result)
                this->radio_stations_list_ = std::move(*result);
            emit radiosOnlineLoaded();
    });

    api->getRadios();
}

void User_Data::UserDataManager::addLikedSong(const Song::SongItem &song)
{
    this->liked_tracklist_.append(song);
}

void User_Data::UserDataManager::addDownloadedSong(const Song::SongItem &song)
{
    this->downloaded_tracklist_.append(song);
}

void User_Data::UserDataManager::addFamiliarSong(const Song::SongItem &song)
{
    this->familiar_tracklist_.append(song);
}

void User_Data::UserDataManager::addFamiliarArtist(const Artists::ArtistItem &artist)
{
    this->familiar_artists_.append(artist);
}

void User_Data::UserDataManager::addFamiliarAlbum(const Album::AlbumItem &album)
{
    this->familiar_albums_.append(album);
}

void User_Data::UserDataManager::addFamiliarCollection(const Collection::CollectionItem &collection)
{
    this->familiar_collections_.append(collection);
}

void User_Data::UserDataManager::addFamiliarRadio(const Radio::RadioItem &radio)
{
    this->familiar_radios_.append(radio);
}

bool User_Data::UserDataManager::removeSongFromLiked(const Song::SongItem &song)
{
    auto it = std::find_if(this->liked_tracklist_.begin(), this->liked_tracklist_.end(),
            [&song] (const Song::SongItem& s) {
                return s.getId() == song.getId();
            });

    if (it == this->liked_tracklist_.end()) {
        return false;
    }

    std::swap(*it, this->liked_tracklist_.back());
    this->liked_tracklist_.pop_back();
    return true;
}

bool User_Data::UserDataManager::removeSongFromDownloaded(const Song::SongItem &song)
{
    auto it = std::find_if(this->downloaded_tracklist_.begin(), this->downloaded_tracklist_.end(),
            [&song] (const Song::SongItem& s) {
                return s.getId() == song.getId();
            });

    if (it == this->downloaded_tracklist_.end()) {
        return false;
    }

    std::swap(*it, this->downloaded_tracklist_.back());
    this->downloaded_tracklist_.pop_back();
    return true;
}