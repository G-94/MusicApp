#include <QApplication>

#include "musicapi.h"
#include "paths.h"
#include "userdataloader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Api::MusicApi m;
    // m.getSongsArtistsAlbumsByQuery("Flash");

    // QObject::connect(&m, &Api::MusicApi::songsByQueryLoaded, [] (std::shared_ptr<QVector<Song::SongItem>> res) {
    //     for (auto& el : *res) {
    //         qDebug() << el.getAuthor() << el.getTitle() << el.getDuration() << el.getId() << el.getSourceUrl() << "\n";
    //     }
    // });

    // QObject::connect(&m, &Api::MusicApi::artistsListLoaded, [] (std::shared_ptr<QVector<Artists::ArtistItem>> res) {
    //     for (auto& el : *res) {
    //         qDebug() << el.getName() << el.getId() << "\n";
    //     }
    // });

    // QObject::connect(&m, &Api::MusicApi::albumsListLoaded, [] (std::shared_ptr<QVector<Album::AlbumItem>> res) {
    //     for (auto& el : *res) {
    //         qDebug() << el.getTitle() << el.getYear() << el.getId() << "\n";
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

    // m.getSongsByArtist("584601");

    // QObject::connect(&m, &Api::MusicApi::songsByArtistLoaded, [] (std::shared_ptr<QVector<Song::SongItem>> res) {
    //     for (auto el : *res) {
    //         qDebug() << el.getAuthor() << el.getTitle() << el.getDuration() << el.getId() << el.getSourceUrl() << "\n";
    //     }
    // });

    // m.getRadios();

    // QObject::connect(&m, &Api::MusicApi::radiosListLoaded, [] (std::shared_ptr<QVector<Radio::RadioItem>> res) {
    //     for (auto& el : *res) {
    //         qDebug() << el.getName() << el.getId() << el.getSourceImgUrl() << el.getSourceUrl() << "\n";
    //     }
    // });

    m.getCollections(2);

    QObject::connect(&m, &Api::MusicApi::collectionsListLoaded, [] (std::shared_ptr<QVector<Collection::CollectionItem>> res) {
        User_Data::UserDataLoader ld;
        ld.SaveMusicItems(Paths::familiarCollectionsPath(), *res);
        for (auto& el : *res) {
            qDebug() << el.getTitle()<< el.getId() << "\n";
        }

        qDebug("fdskfdsfdlsfjdskfn\n\\n\n\n\n\n\\n\n\n\n\n\n");
        QVector<Collection::CollectionItem> te;
        ld.LoadMusicItems(Paths::familiarCollectionsPath(), te);

        for (auto& el : te) {
            qDebug() << el.getTitle()<< el.getId() << "\n";
        }
    });

    return QApplication::exec();
}
