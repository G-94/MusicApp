#include "musicapi.h"

Api::MusicApi::MusicApi(QObject *parent)
    : QObject{parent}, manager_{new QNetworkAccessManager(this)}
{}

// for QStringView Literals
// u"..."_sv
using namespace Qt::StringLiterals;

void Api::MusicApi::getSongsArtistsAlbumsByQuery(const QString &query, bool onlyOnePage)
{
    QUrl url(HTTP_Literals::QUERY_BASE + HTTP_Literals::PAGE_BASE + HTTP_Literals::EMPTY_PAGE_STR);
    url.setQuery(QUrlQuery{{"q", query}});

    if (not checkUrl(url)) {
        emit loadingArtistsFailed(Codes_Literals::INVALID_URL);
        return;
    }

    std::shared_ptr<QVector<Song::SongItem>> accumulator = std::make_shared<QVector<Song::SongItem>>();

    fetchPage(url, accumulator, 0, QUERY_SONGS_ARTISTS_ALBUMS, onlyOnePage);
}

void Api::MusicApi::getSongsByGenre(QString genre, bool onlyOnePage)
{
    QUrl url(HTTP_Literals::GENRE_BASE + genre + HTTP_Literals::PAGE_BASE + HTTP_Literals::EMPTY_PAGE_STR);
    if (not checkUrl(url)) return;

    std::shared_ptr<QVector<Song::SongItem>> accumulator = std::make_shared<QVector<Song::SongItem>>();

    fetchPage(url, accumulator, 0, GENRE, onlyOnePage);
}

void Api::MusicApi::getSongsByArtist(QString artist_id, bool onlyOnePage)
{
    QUrl url(HTTP_Literals::ARTISTS_BASE + artist_id + HTTP_Literals::PAGE_BASE + HTTP_Literals::EMPTY_PAGE_STR);
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

void Api::MusicApi::getCollections(int pages)
{
    QUrl url(HTTP_Literals::COLLECTIONS_BASE + HTTP_Literals::PAGE_BASE + HTTP_Literals::EMPTY_PAGE_STR);
    if (not url.isValid()) {
        emit loadingCollectionsFailed(Codes_Literals::INVALID_URL);
        return;
    }

    std::shared_ptr<QVector<Collection::CollectionItem>> accumulator =
        std::make_shared<QVector<Collection::CollectionItem>>();

    fetchCollectionsPages(url, accumulator, 0, pages);
}

void Api::MusicApi::getRadios()
{
    QUrl url(HTTP_Literals::RADIO_BASE + HTTP_Literals::PAGE_BASE + HTTP_Literals::EMPTY_PAGE_STR);
    if (not url.isValid()) {
        emit loadingRadiosFailed(Codes_Literals::INVALID_URL);
        return;
    }

    std::shared_ptr<QVector<Radio::RadioItem>> accumulator = std::make_shared<QVector<Radio::RadioItem>>();

    fetchRadiosPages(url, accumulator, 0);
}

// parse page, finds albums; change result; used in fetchPage
void Api::MusicApi::parseAlbumsFromPage(const QStringView page, AlbumsVectorPtr result)
{
    qsizetype start_block_idx = page.indexOf(u"<h2 class=\"p-info-title\">Альбомы</h2>"_sv);

    if (start_block_idx == -1) {
        emit albumsListLoaded(result);
    }

    QStringView block_start_text = page.mid(start_block_idx +
        u"<h2 class=\"p-info-title\">Альбомы</h2>"_sv.length()
    );

    QList<QStringView> blocks = block_start_text.left(
        block_start_text.indexOf(u"</ul>"_sv)
    ).split(u"album-item"_sv).sliced(1);

    for (const QStringView& block : std::as_const(blocks)) {
        QStringView id_start_text = block.mid(
            block.indexOf(u"/album/"_sv) +
            qsizetype(u"/album/"_sv.length()
        ));

        QString id = QString(id_start_text.left(
            id_start_text.indexOf(u"\">"_sv)
        ));

        QStringView name_start_text = block.mid(
            block.indexOf(u"\"album-title\">"_sv) +
            qsizetype(u"\"album-title\">"_sv.length()
        ));

        // breckets using for parse date; format: (date)
        qsizetype breckets_open_pos = name_start_text.lastIndexOf(u"("_sv);

        if(breckets_open_pos == -1) {
            emit loadingAlbumsFailed(Codes_Literals::PARSE_ERROR);
            return;
        }

        // 4 - year string length
        QString year = QString(name_start_text.mid(breckets_open_pos + 1, 4));
        QString name = QString(name_start_text.left(breckets_open_pos).trimmed());

        result->append(Album::AlbumItem{
            name,
            year,
            id
        });
    }

    emit albumsListLoaded(result);
}

// parse page, finds radios; change result
void Api::MusicApi::parseRadiosFromPage(const QStringView page, RadiosVectorPtr accumulator)
{
    qsizetype start_bloc_idx = page.indexOf(u"album-list muslist"_sv);
    if (start_bloc_idx == -1) {
        emit loadingRadiosFailed(Codes_Literals::PARSE_ERROR);
        return;
    }

    QStringView start_block = page.mid(start_bloc_idx);
    QStringView radios_block = start_block.left(start_block.indexOf(u"</ul>"_sv));

    QList<QStringView> blocks = radios_block.split(u"album-item media-elem mustoggler"_sv).sliced(1);

    for (const QStringView& block : std::as_const(blocks)) {
        QStringView data_start = block.mid(block.indexOf(u"data-musmeta=\'"_sv)
            + qsizetype(u"data-musmeta=\'"_sv.length())
        );

        QStringView data_text = data_start.left(data_start.indexOf(u"\'>"_sv));

        QJsonObject obj;

        try {
            obj = Helper::parseJsonStr(QString(data_text));
        } catch (const QException& e) {
            e.raise();
            return;
        }

        // add radios to accumulator
        accumulator->append(Radio::RadioItem{
            obj.value("title").toString(),
            obj.value("id").toString(),
            obj.value("url").toString(),
            obj.value("img").toString()
        });
    }
}

// parse page, finds collections; change accumulator
void Api::MusicApi::parseCollectionsFromPage(const QStringView page, CollectionsVectorPtr accumulator)
{
    qsizetype block_start_idx = page.indexOf(u"<ul class=\"album-list\">"_sv);

    if (block_start_idx == -1) {
        emit collectionsListLoaded(accumulator);
        return;
    }

    QStringView block_start_text = page.mid(
        block_start_idx + qsizetype(u"<ul class=\"album-list\">"_sv.length())
    );

    QList<QStringView> blocks = block_start_text.left(
        block_start_text.indexOf(u"</ul>"_sv)).split(u"album-item"_sv).sliced(1);

    for (const QStringView& block : std::as_const(blocks)) {
        QStringView id_start_text = block.mid(block.indexOf(u"/collection/"_sv)
            + qsizetype(u"/collection/"_sv.length()));

        QString id = QString(id_start_text.left(
            id_start_text.indexOf(u"\""_sv))
        );

        QStringView title_start_text = block.mid(block.indexOf(u"\"album-title\">"_sv) +
            qsizetype(u"\"album-title\">"_sv.length())
        );

        QString title = QString(title_start_text.left(
            title_start_text.indexOf(u"</span>"_sv))
        );

        accumulator->append(Collection::CollectionItem{
            title,
            id
        });
    }
}

// get radios from pages/page
void Api::MusicApi::fetchRadiosPages(QUrl url, RadiosVectorPtr accumulator, int page, bool onlyOne)
{
    QNetworkRequest request(url);
    QNetworkReply* reply = manager_->get(request);

    QObject::connect(reply, &QNetworkReply::finished, [this, reply, url, accumulator, page, onlyOne]() mutable {
        reply->deleteLater();

        url = QUrl(url.toString().replace(HTTP_Literals::EMPTY_PAGE_STR, QString::number(page)));

        if(reply->error() != QNetworkReply::NoError) {
            emit loadingRadiosFailed(Codes_Literals::REPLY_ERROR);
            return;
        }

        QString page_text = reply->readAll();

        try {
            parseRadiosFromPage(page_text, accumulator);
        } catch (const QException& e) {
            emit loadingRadiosFailed(e.what());
        }

        if (onlyOne or page > 1000) {
            emit radiosListLoaded(accumulator);
            return;
        }

        QUrl next_url = replacePageToEmpty(url, page);

        fetchRadiosPages(next_url, accumulator, page + 48);
    });
}

void Api::MusicApi::fetchCollectionsPages(QUrl url, CollectionsVectorPtr accumulator, int page, int limit)
{
    QNetworkRequest request(url);
    QNetworkReply* reply = manager_->get(request);

    QObject::connect(reply, &QNetworkReply::finished, [this, reply, url, accumulator, page, limit]() mutable {
        reply->deleteLater();

        url = QUrl(url.toString().replace(HTTP_Literals::EMPTY_PAGE_STR, QString::number(page)));

        if(reply->error() != QNetworkReply::NoError) {
            emit loadingCollectionsFailed(Codes_Literals::REPLY_ERROR);
            return;
        }

        QString page_text = reply->readAll();

        try {
            parseCollectionsFromPage(page_text, accumulator);
        } catch (const QException& e) {
            emit loadingCollectionsFailed(e.what());
        }

        if ((limit != -1 and page >= (limit * 48)) or page >= 3000) {
            emit collectionsListLoaded(accumulator);
            return;
        }

        QUrl next_url = replacePageToEmpty(url, page);

        fetchCollectionsPages(next_url, accumulator, page + 48, limit);
    });
}

// parse page, finds artists; change result
void Api::MusicApi::parseArtistsFromPage(const QStringView page,
    std::shared_ptr<QVector<Artists::ArtistItem>> result)
{
    // find block start
    qsizetype block_start_idx = page.indexOf(u"<ul class=\"singers-list album-list\">"_sv);

    if (block_start_idx == -1) {
        emit artistsListLoaded(result);
    }

    QStringView block_start = page.mid(block_start_idx);

    // take block text
    QStringView artists_block_text = block_start.left(
        block_start.indexOf(u"</ul>"_sv)
    );

    QList<QStringView> artists_blocks = artists_block_text.split(u"album-item"_sv).sliced(1);

    for (const QStringView& block : std::as_const(artists_blocks)) {
        QStringView id_start_text = block.mid(
            block.indexOf(u"<a href=\"/artist/"_sv) +
            qsizetype(u"<a href=\"/artist/"_sv.length()
        ));

        QString id = QString(
            id_start_text.left(id_start_text.indexOf(u"\""_sv))
        );

        QStringView name_start_text = block.mid(
            block.indexOf(u"class=\"album-title\">"_sv) +
            qsizetype(u"class=\"album-title\">"_sv.length()
        ));

        QString name = QString(
            name_start_text.left(name_start_text.indexOf(u"</span>"_sv))
        );

        result->append(Artists::ArtistItem{
            name,
            id
        });
    }

    emit artistsListLoaded(result);
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

        QJsonObject data;

        try {
            data = Helper::parseJsonStr(QString(song_data_text));
        } catch (const QException& e) {
            continue;
        }

        // add song to accumulator
        accumulator->append(Song::SongItem{
            data.value("artist").toString(),
            data.value("title").toString(),
            data.value("url").toString(),
            data.value("img").toString(),
            data.value("id").toString(),
            song_duration
        });
    }
}

// get songs from pages
void Api::MusicApi::fetchPage(QUrl url, std::shared_ptr<QVector<Song::SongItem>> accumulator,
    int page, EMIT_TYPE type, bool onlyOne)
{
    // change empty part of string to insert page counter
    if (type != COLLECTION and type != ALBUM) {
        url = QUrl(url.toString().replace(HTTP_Literals::EMPTY_PAGE_STR, QString::number(page)));
    }

    QNetworkRequest request(url);
    QNetworkReply* reply = manager_->get(request);

    QObject::connect(reply, &QNetworkReply::finished, [this, reply, url,
            accumulator, page, onlyOne, type]() mutable {
        reply->deleteLater();

        if (reply->error() != QNetworkReply::NoError) {
            emit loadingSongsFailed(Codes_Literals::REPLY_ERROR);
            emit loadingArtistsFailed(Codes_Literals::REPLY_ERROR);
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

        // create artists list,
        //      create albums list,
        // parse page and set type to QUERY
        if (type == QUERY_SONGS_ARTISTS_ALBUMS) {

            std::shared_ptr<QVector<Artists::ArtistItem>> artists =
                std::make_shared<QVector<Artists::ArtistItem>>();
            parseArtistsFromPage(QStringView(page_text), artists);

            std::shared_ptr<QVector<Album::AlbumItem>> albums =
                std::make_shared<QVector<Album::AlbumItem>>();
            parseAlbumsFromPage(QStringView(page_text), albums);

            type = QUERY;
        }

        // parse blocks of song data html, change accumulator
        try {
            parseSongsFromPage(songs_blocks, accumulator);
        } catch (const QException& e) {
            emit loadingSongsFailed(e.what());
            return;
        }

        if (onlyOne or page + HTTP_Literals::PAGE_STEP > 480) {
            chooseSignalSongList(type, accumulator);
            return;
        }

        QUrl next_url = replacePageToEmpty(url, page);

        fetchPage(next_url, accumulator, page + HTTP_Literals::PAGE_STEP, type);
    });
}

//choose signal for songs query
void Api::MusicApi::chooseSignalSongList(EMIT_TYPE type, std::shared_ptr<QVector<Song::SongItem>> arg)
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
        emit loadingSongsFailed(Codes_Literals::EMIT_ERROR);
        break;
    }
}

bool Api::MusicApi::checkUrl(const QUrl &url)
{
    if (not url.isValid()) {
        emit loadingSongsFailed(Codes_Literals::INVALID_URL);
        return false;
    }
    return true;
}

// replace page counter to ---
QUrl Api::MusicApi::replacePageToEmpty(QUrl url, int page)
{
    QString temp_url = url.toString();

    QUrl next_url = QUrl(temp_url.replace(
        temp_url.indexOf(HTTP_Literals::PAGE_BASE) +
            qsizetype(HTTP_Literals::PAGE_BASE.length()),
        QString::number(page).length(), HTTP_Literals::EMPTY_PAGE_STR)
    );

    return next_url;
}