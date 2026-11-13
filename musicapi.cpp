#include "musicapi.h"

Api::MusicApi::MusicApi(QObject *parent)
    : QObject{parent}, manager{new QNetworkAccessManager(this)}
{}

// for QStringView Literals
// u"..."_sv
using namespace Qt::StringLiterals;

void Api::MusicApi::getSongsByQuery(const QString &query)
{
    QUrl url(HTTP_Literals::QUERY_BASE + HTTP_Literals::PAGE_BASE + "---");
    url.setQuery(QUrlQuery{{"q", query}});

    if (not url.isValid()) {
        emit errorLoadedSongsByQueryFailed("InvalidUrl");
        return;
    }

    std::shared_ptr<QVector<Song::SongItem>> accumulator = std::make_shared<QVector<Song::SongItem>>();

    fetchPage(url, accumulator, 0);
}

// get songs from pages
void Api::MusicApi::fetchPage(QUrl url, std::shared_ptr<QVector<Song::SongItem>> accumulator, int page)
{
    url = QUrl(url.toString().replace("---", QString::number(page)));

    QNetworkRequest request(url);
    QNetworkReply* reply = manager->get(request);

    QObject::connect(reply, &QNetworkReply::finished, [this, reply, url, accumulator, page]() {
        reply->deleteLater();

        if (reply->error() != QNetworkReply::NoError) {
            emit errorLoadedSongsByQueryFailed("ReplyError");
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

        // parse blocks of song data html
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

        if (page + HTTP_Literals::PAGE_STEP > 480) {
            emit songsByQueryLoaded(accumulator);
            return;
        }

        QString temp_url = url.toString();

        // replace page counter to ---
        QUrl next_url = QUrl(temp_url.replace(
            temp_url.indexOf(HTTP_Literals::PAGE_BASE) +
            qsizetype(HTTP_Literals::PAGE_BASE.length()),
            QString::number(page).length(), "---")
        );

        fetchPage(next_url, accumulator, page + HTTP_Literals::PAGE_STEP);
    });
}