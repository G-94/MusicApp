#include <QApplication>

#include "musicapi.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Api::MusicApi m;
    m.getSongsByQuery("скучаю");

    return QApplication::exec();
}
