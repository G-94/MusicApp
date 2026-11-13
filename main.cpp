#include <QApplication>

#include "musicapi.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Api::MusicApi m;
    m.getSongsByQuery("Kanye West", true);

    QObject::connect(&m, &Api::MusicApi::songsByQueryLoaded, [] (std::shared_ptr<QVector<Song::SongItem>> res) {
        for (auto el : *res) {
            qDebug() << el.getAuthor() << el.getTitle() << el.getDuration() << el.getId() << el.getSourceUrl() << "\n";
        }
    });

    return QApplication::exec();
}
