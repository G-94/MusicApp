#include "userdatamanager.h"

User_Data::UserDataManager::UserDataManager(std::shared_ptr<Api::MusicApi> api)
{

}

void User_Data::UserDataManager::preloadUserData()
{

}

void User_Data::UserDataManager::saveTouchedSongs()
{

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