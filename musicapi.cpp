#include "musicapi.h"

Api::MusicApi::MusicApi(QObject *parent)
    : QObject{parent}, manager{new QNetworkAccessManager(this)}
{}

// for QStringView Literals
// u"..."_sv
using namespace Qt::StringLiterals;

void Api::MusicApi::getSongsByQuery(const QString &query)
{
    QUrl url(QUERY_BASE);
    url.setQuery(QUrlQuery{{"q", query}});

    if (not url.isValid())
        throw AppExceptions::InvalidUrlException(url.toString());

    QNetworkRequest request(url);
    QNetworkReply* reply = manager->get(request);

    QObject::connect(reply, &QNetworkReply::finished, [reply, url]() {

        reply->deleteLater();

        // if (reply->error() != QNetworkReply::NoError)
            // throw AppExceptions::ConnectionApiException(url.toString());

        // TODO normal throw with slot and emit

        //live to emit
        QVector<Song::SongItem> result;

        QString page_text = reply->readAll();
        QList<QStringView> songs_blocks = QStringView(page_text).split(u"tracks__item"_sv).sliced(1);

        // parse blocks of song data html
        for (const auto& block : songs_blocks) {
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

            // add song to result
            result.append(Song::SongItem(
                data.value("artist").toString(),
                data.value("title").toString(),
                data.value("url").toString(),
                data.value("img").toString(),
                data.value("id").toString(),
                song_duration
            ));

            qDebug() << data.value("artist").toString() <<
                data.value("title").toString() <<
                data.value("url").toString() <<
                data.value("img").toString() <<
                data.value("id").toString() <<
                song_duration;
        }

    });

    //TODO emit signal songs loaded
}
