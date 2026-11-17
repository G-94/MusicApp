#ifndef PATHS_H
#define PATHS_H

#include <QString>
#include <QStandardPaths>
#include <QDir>

namespace Paths {

inline QString familiarSongsPath()
{
    const QString dir = QStandardPaths::writableLocation(
        QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    return dir + QStringLiteral("/familiar_songs.json");
}

inline QString LikedAndDownloadsSongsPath()
{
    const QString dir = QStandardPaths::writableLocation(
        QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    return dir + QStringLiteral("/liked_downloaded_songs.json");
}

inline QString familiarArtistsPath()
{
    const QString dir = QStandardPaths::writableLocation(
        QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    return dir + QStringLiteral("/familiar_artists.json");
}

inline QString familiarAlbumsPath()
{
    const QString dir = QStandardPaths::writableLocation(
        QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    return dir + QStringLiteral("/familiar_albums.json");
}

inline QString familiarCollectionsPath()
{
    const QString dir = QStandardPaths::writableLocation(
        QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    return dir + QStringLiteral("/familiar_collections.json");
}

inline QString familiarRadiosPath()
{
    const QString dir = QStandardPaths::writableLocation(
        QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    return dir + QStringLiteral("/familiar_radios.json");
}

}

#endif // PATHS_H
