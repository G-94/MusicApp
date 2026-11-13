#include "musicapi.h"

Api::MusicApi::MusicApi(QObject *parent)
    : QObject{parent}, manager_{new QNetworkAccessManager(this)}
{}

// for QStringView Literals
// u"..."_sv
using namespace Qt::StringLiterals;

void Api::MusicApi::getSongsByQuery(const QString &query, bool onlyOnePage)
{
    QUrl url(HTTP_Literals::QUERY_BASE + HTTP_Literals::PAGE_BASE + "---");
    url.setQuery(QUrlQuery{{"q", query}});

    if (not checkUrl(url)) return;

    std::shared_ptr<QVector<Song::SongItem>> accumulator = std::make_shared<QVector<Song::SongItem>>();

    fetchPage(url, accumulator, 0, QUERY, onlyOnePage);
}

void Api::MusicApi::getSongsByGenre(QString genre, bool onlyOnePage)
{
    QUrl url(HTTP_Literals::GENRE_BASE + genre + HTTP_Literals::PAGE_BASE + "---");
    if (not checkUrl(url)) return;

    std::shared_ptr<QVector<Song::SongItem>> accumulator = std::make_shared<QVector<Song::SongItem>>();

    fetchPage(url, accumulator, 0, GENRE, onlyOnePage);
}

void Api::MusicApi::getSongsByArtist(QString artist_id, bool onlyOnePage)
{
    QUrl url(HTTP_Literals::ARTISTS_BASE + artist_id + HTTP_Literals::PAGE_BASE + "---");
    if (not checkUrl(url)) return;

    std::shared_ptr<QVector<Song::SongItem>> accumulator = std::make_shared<QVector<Song::SongItem>>();

    fetchPage(url, accumulator, 0, ARTIST, onlyOnePage);
}

void Api::MusicApi::getSongsCollection(QString collection_id)
{
    QUrl url(HTTP_Literals::COLLECTION_BASE + collection_id);
    if (not checkUrl(url)) return;

    std::shared_ptr<QVector<Song::SongItem>> accumulator = std::make_shared<QVector<Song::SongItem>>();

    fetchPage(url, accumulator, 0, COLLECTION, true);
}

void Api::MusicApi::getSongsAlbum(QString album_id)
{
    QUrl url(HTTP_Literals::ALBUM_BASE + album_id);
    if (not checkUrl(url)) return;

    std::shared_ptr<QVector<Song::SongItem>> accumulator = std::make_shared<QVector<Song::SongItem>>();

    fetchPage(url, accumulator, 0, ALBUM, true);
}

// parse blocks of song data html, change accumulator
void Api::MusicApi::parseSongsFromPage(const QList<QStringView> &songs_blocks,
        std::shared_ptr<QVector<Song::SongItem>> accumulator)
{
    for (const auto& block : std::as_const(songs_blocks)) {
        // get song duration
        QStringView dur_start = block.mid(
            block.indexOf(u"\"track__fulltime\">"_sv) +
            qsizetype(qstrlen("\"track__fulltime\">")));

        QString song_duration = dur_start.left(
            dur_start.indexOf(u"</div>"_sv)
        ).toString();

        //get song data text
        QStringView song_data_start = block.mid(
            block.indexOf(u"data-musmeta=\'"_sv) +
            qsizetype(qstrlen("data-musmeta='"))
        );

        QStringView song_data_text = song_data_start.left(
            song_data_start.indexOf(u"\'>"_sv)
        );

        QJsonObject data = Helper::parseJsonStr(QString(song_data_text));

        // add song to accumulator
        accumulator->append(Song::SongItem(
            data.value("artist").toString(),
            data.value("title").toString(),
            data.value("url").toString(),
            data.value("img").toString(),
            data.value("id").toString(),
            song_duration
        ));
    }
}

// get songs from pages
void Api::MusicApi::fetchPage(QUrl url, std::shared_ptr<QVector<Song::SongItem>> accumulator,
    int page, EMIT_SONGS_TYPE type, bool onlyOne)
{
    // change empty part of string to insert page counter
    if (type != COLLECTION and type != ALBUM) {
        url = QUrl(url.toString().replace("---", QString::number(page)));
    }

    QNetworkRequest request(url);
    QNetworkReply* reply = manager_->get(request);

    QObject::connect(reply, &QNetworkReply::finished, [this, reply, url,
            accumulator, page, onlyOne, type]() {
        reply->deleteLater();

        if (reply->error() != QNetworkReply::NoError) {
            emit loadingSongsFailed("ReplyError");
            return;
        }

        QString page_text = reply->readAll();

        //split html page by songs to blocks
        QList<QStringView> songs_blocks = QStringView(page_text).split
            (u"tracks__item"_sv).sliced(1);

        // if page doesnt have songs
        if (songs_blocks.isEmpty()) {
            emit songsByQueryLoaded(accumulator);
            return;
        }

        // parse blocks of song data html, change accumulator
        parseSongsFromPage(songs_blocks, accumulator);

        if (onlyOne or page + HTTP_Literals::PAGE_STEP > 480) {
            chooseSignalSongList(type, accumulator);
            return;
        }

        QString temp_url = url.toString();

        // replace page counter to ---
        QUrl next_url = QUrl(temp_url.replace(
            temp_url.indexOf(HTTP_Literals::PAGE_BASE) +
            qsizetype(HTTP_Literals::PAGE_BASE.length()),
            QString::number(page).length(), "---")
        );

        fetchPage(next_url, accumulator, page + HTTP_Literals::PAGE_STEP, type);
    });
}

//choose signal for songs query
void Api::MusicApi::chooseSignalSongList(EMIT_SONGS_TYPE type, std::shared_ptr<QVector<Song::SongItem>> arg)
{
    switch (type) {
    case QUERY:
        emit songsByQueryLoaded(arg);
        break;
    case GENRE:
        emit songsByGenreLoaded(arg);
        break;
    case ARTIST:
        emit songsByArtistLoaded(arg);
        break;
    case COLLECTION:
        emit songsCollectionLoaded(arg);
        break;
    case ALBUM:
        emit songsAlbumLoaded(arg);
        break;
    default:
        emit loadingSongsFailed("EmitError");
        break;
    }
}

bool Api::MusicApi::checkUrl(const QUrl &url)
{
    if (not url.isValid()) {
        emit loadingSongsFailed("InvalidUrl");
        return false;
    }
    return true;
}