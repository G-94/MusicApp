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
#include "appexceptions.h"

namespace Api {

using SongsVectorPtr = std::shared_ptr<QVector<Song::SongItem>>;

enum EMIT_TYPE {
    QUERY,
    GENRE
};

class MusicApi : public QObject
{
    Q_OBJECT
public:
    explicit MusicApi(QObject *parent = nullptr);

    void getSongsByQuery(const QString& query, bool onlyOnePage = false);
    void getSongsByGenre(int genre, bool onlyOnePage = false);

private:

    QNetworkAccessManager* manager;

signals:

    void songsByQueryLoaded(std::shared_ptr<QVector<Song::SongItem>> result);
    void songsByGenreLoaded(std::shared_ptr<QVector<Song::SongItem>> result);

    void loadingSongsFailed(QString msg);

private:

    // parse blocks of song data html, change accumulator
    void parseSongsFromPage(const QList<QStringView>& songs_blocks, SongsVectorPtr accumulator);

    // get songs from pages/page
    void fetchPage(QUrl url, SongsVectorPtr accumulator,
        int page, EMIT_TYPE type, bool onlyOne = false);

    //choose signal for songs query
    void chooseSignalSongList(EMIT_TYPE type, SongsVectorPtr arg);

};

}

#endif // MUSICAPI_H
