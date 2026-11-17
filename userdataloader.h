/*

-------------------------------------------------------------------------



-------------------------------------------------------------------------

*/

#ifndef USERDATALOADER_H
#define USERDATALOADER_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QSaveFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <type_traits>

#include "musicitem.h"
#include "songitem.h"
#include "radioitem.h"
#include "albumitem.h"
#include "artistitem.h"
#include "collectionitem.h"

namespace User_Data {

class UserDataLoader
{
public:
    UserDataLoader();

private:

    QJsonObject load(const QString& path);
    bool save(const QString& path, const QJsonObject& data);

public:

    template <typename Item>
    bool LoadMusicItem(const QString& path, QVector<MusicItem::MusicItem> data) {
        static_assert(std::is_base_of<MusicItem::MusicItem, Item>::value,
                      "only MusicItems sub-classes are allowed");

    }

    template <typename Item>
    bool SaveMusicItem(const QString& path, QVector<MusicItem::MusicItem> data) {
        static_assert(std::is_base_of<MusicItem::MusicItem, Item>::value,
                      "only MusicItems sub-classes are allowed");
    }

};

}

#endif // USERDATALOADER_H
