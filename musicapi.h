/*

-------------------------------------------------------------------------

    MusicApi to connect resource with songs,
    Parse html pages,
    Use songs from the resource

-------------------------------------------------------------------------

*/

#ifndef MUSICAPI_H
#define MUSICAPI_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QString>
#include <QVector>
#include <QUrlQuery>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QLatin1String>

#include "config.h"
#include "songitem.h"
#include "artistitem.h"
#include "appexceptions.h"

namespace Api {

using SongsVectorPtr = std::shared_ptr<QVector<Song::SongItem>>;
using ArtistsVectorPtr = std::shared_ptr<QVector<Artists::ArtistItem>>;

enum EMIT_TYPE {
    QUERY_AND_ARTISTS,
    QUERY,
    GENRE,
    ARTIST,
    ALBUM,
    COLLECTION
};

class MusicApi : public QObject
{
    Q_OBJECT
public:
    explicit MusicApi(QObject *parent = nullptr);

    void getSongsAndArtistsByQuery(const QString& query, bool onlyOnePage = false);
    void getSongsByGenre(QString genre, bool onlyOnePage = false);
    void getSongsByArtist(QString artist_id, bool onlyOnePage = false);
    void getSongsCollection(QString collection_id);
    void getSongsAlbum(QString album_id);

private:

    QNetworkAccessManager* manager_;

signals:

    void songsByQueryLoaded(std::shared_ptr<QVector<Song::SongItem>> result);
    void songsByGenreLoaded(std::shared_ptr<QVector<Song::SongItem>> result);
    void songsByArtistLoaded(std::shared_ptr<QVector<Song::SongItem>> result);
    void songsCollectionLoaded(std::shared_ptr<QVector<Song::SongItem>> result);
    void songsAlbumLoaded(std::shared_ptr<QVector<Song::SongItem>> result);

    void artistsListLoaded(std::shared_ptr<QVector<Artists::ArtistItem>> result);

    void loadingSongsFailed(QString msg);
    void loadingArtistsFailed(QString msg);

private:

    // parse blocks of song data html; change accumulator
    void parseSongsFromPage(const QList<QStringView>& songs_blocks, SongsVectorPtr accumulator);

    //parse page, finds artists; change result
    void parseArtistsFromPage(const QStringView page, ArtistsVectorPtr result);

    // get songs from pages/page
    void fetchPage(QUrl url, SongsVectorPtr accumulator,
        int page, EMIT_TYPE type, bool onlyOne = false);

    //choose signal for songs query
    void chooseSignalSongList(EMIT_TYPE type, SongsVectorPtr arg);

private:

    bool checkUrl(const QUrl& url);

};

}

#endif // MUSICAPI_H
