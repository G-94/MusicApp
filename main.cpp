#include <QApplication>

#include "musicapi.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Api::MusicApi m;
    // m.getSongsByQuery("jazz", true);

    // QObject::connect(&m, &Api::MusicApi::songsByQueryLoaded, [] (std::shared_ptr<QVector<Song::SongItem>> res) {
    //     for (auto el : *res) {
    //         qDebug() << el.getAuthor() << el.getTitle() << el.getDuration() << el.getId() << el.getSourceUrl() << "\n";
    //     }
    // });

    // m.getSongsByGenre("51");

    // QObject::connect(&m, &Api::MusicApi::songsByGenreLoaded, [] (std::shared_ptr<QVector<Song::SongItem>> res) {
    //     for (auto el : *res) {
    //         qDebug() << el.getAuthor() << el.getTitle() << el.getDuration() << el.getId() << el.getSourceUrl() << "\n";
    //     }
    // });

    // m.getSongsCollection("10181");

    // QObject::connect(&m, &Api::MusicApi::songsCollectionLoaded, [] (std::shared_ptr<QVector<Song::SongItem>> res) {
    //     for (auto el : *res) {
    //         qDebug() << el.getAuthor() << el.getTitle() << el.getDuration() << el.getId() << el.getSourceUrl() << "\n";
    //     }
    // });

    // m.getSongsAlbum("488389");

    // QObject::connect(&m, &Api::MusicApi::songsAlbumLoaded, [] (std::shared_ptr<QVector<Song::SongItem>> res) {
    //     for (auto el : *res) {
    //         qDebug() << el.getAuthor() << el.getTitle() << el.getDuration() << el.getId() << el.getSourceUrl() << "\n";
    //     }
    // });

    m.getSongsByArtist("584601");

    QObject::connect(&m, &Api::MusicApi::songsByArtistLoaded, [] (std::shared_ptr<QVector<Song::SongItem>> res) {
        for (auto el : *res) {
            qDebug() << el.getAuthor() << el.getTitle() << el.getDuration() << el.getId() << el.getSourceUrl() << "\n";
        }
    });

    return QApplication::exec();
}
