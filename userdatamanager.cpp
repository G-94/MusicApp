#include "userdatamanager.h"

User_Data::UserDataManager::UserDataManager()
{

}

void User_Data::UserDataManager::preloadUserData()
{

}

void User_Data::UserDataManager::saveTouchedSongs()
{
    QString path = Paths::LikedAndDownloadsSongsPath();

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

        return loader_.SaveMusicItems(path, merged);
    });

    auto* watcher = new QFutureWatcher<bool>(this);
    QObject::connect(watcher, &QFutureWatcherBase::finished, this, [this, watcher]() {
        watcher->deleteLater();
        bool result = watcher->result();

        if (result) {
            emit touchedSongsSaved();
        } else {
            emit error("Error while saving touchedSongs");
        }
    });

    watcher->setFuture(future);
}

void User_Data::UserDataManager::addLikedSong(const Song::SongItem &song)
{
    this->liked_tracklist_.append(song);
}

void User_Data::UserDataManager::addDownloadedSong(const Song::SongItem &song)
{
    this->downloaded_tracklist_.append(song);
}

void User_Data::UserDataManager::loadTouchedSongs()
{
    QString path = Paths::LikedAndDownloadsSongsPath();
    auto future = QtConcurrent::run([this, path]() -> QVector<Song::SongItem> {
        return loader_.LoadMusicItems<Song::SongItem>(path);
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

        emit touchedSongsLoaded();
    });

    watcher->setFuture(future);
}