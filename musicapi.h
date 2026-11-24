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
#include "radioitem.h"
#include "albumitem.h"
#include "collectionitem.h"
#include "appexceptions.h"

namespace Api {

using SongsVectorPtr = std::shared_ptr<QVector<Song::SongItem>>;
using ArtistsVectorPtr = std::shared_ptr<QVector<Artists::ArtistItem>>;
using RadiosVectorPtr = std::shared_ptr<QVector<Radio::RadioItem>>;
using AlbumsVectorPtr = std::shared_ptr<QVector<Album::AlbumItem>>;
using CollectionsVectorPtr = std::shared_ptr<QVector<Collection::CollectionItem>>;

enum EMIT_TYPE {
    QUERY_SONGS_ARTISTS_ALBUMS,
    QUERY,
    GENRE,
    ARTIST,
    ALBUM,
    COLLECTION
};

class MusicApi final : public QObject
{
    Q_OBJECT
public:
    explicit MusicApi(QObject *parent = nullptr);

    void getSongsArtistsAlbumsByQuery(const QString& query, bool onlyOnePage = false);
    void getSongsByGenre(QString genre, bool onlyOnePage = false);
    void getSongsByArtist(QString artist_id, bool onlyOnePage = false);
    void getSongsCollection(QString collection_id);
    void getSongsAlbum(QString album_id);

    void getCollections(int pages = -1);
    void getRadios();

private:

    QNetworkAccessManager* manager_;

signals:

    void songsByQueryLoaded(std::shared_ptr<QVector<Song::SongItem>> result);
    void songsByGenreLoaded(std::shared_ptr<QVector<Song::SongItem>> result);
    void songsByArtistLoaded(std::shared_ptr<QVector<Song::SongItem>> result);
    void songsCollectionLoaded(std::shared_ptr<QVector<Song::SongItem>> result);
    void songsAlbumLoaded(std::shared_ptr<QVector<Song::SongItem>> result);

    void artistsListLoaded(std::shared_ptr<QVector<Artists::ArtistItem>> result);
    void albumsListLoaded(std::shared_ptr<QVector<Album::AlbumItem>> result);
    void radiosListLoaded(std::shared_ptr<QVector<Radio::RadioItem>> result);
    void collectionsListLoaded(std::shared_ptr<QVector<Collection::CollectionItem>>);

    void loadingSongsFailed(QString msg);
    void loadingArtistsFailed(QString msg);
    void loadingAlbumsFailed(QString msg);
    void loadingRadiosFailed(QString msg);
    void loadingCollectionsFailed(QString msg);

private:

    // parse blocks of song data html; change accumulator
    void parseSongsFromPage(const QList<QStringView>& songs_blocks, SongsVectorPtr accumulator);

    // parse page, finds artists; change result; used in fetchPage
    void parseArtistsFromPage(const QStringView page, ArtistsVectorPtr result);

    // parse page, finds albums; change result; used in fetchPage
    void parseAlbumsFromPage(const QStringView page, AlbumsVectorPtr result);

    // parse page, finds radios; change result
    void parseRadiosFromPage(const QStringView page, RadiosVectorPtr accumulator);

    // parse page, finds collections; change accumulator
    void parseCollectionsFromPage(const QStringView page, CollectionsVectorPtr accumulator);

    // get songs from pages/page
    void fetchPage(QUrl url, SongsVectorPtr accumulator,
        int page, EMIT_TYPE type, bool onlyOne = false);

    // get radios from pages/page
    void fetchRadiosPages(QUrl url, RadiosVectorPtr accumulator,
        int page, bool onlyOne = false);

    // get collections from page/pages
    void fetchCollectionsPages(QUrl url, CollectionsVectorPtr accumulator,
        int page, int limit = -1);

    //choose signal for songs query
    void chooseSignalSongList(EMIT_TYPE type, SongsVectorPtr arg);

private:

    bool checkUrl(const QUrl& url);

    // replace page counter to ---
    QUrl replacePageToEmpty(QUrl url, int page);

};

}

#endif // MUSICAPI_H