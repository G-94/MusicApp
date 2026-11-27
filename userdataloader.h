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
#include <QJsonArray>
#include <type_traits>

#include "musicitem.h"

namespace User_Data {

class UserDataLoader final
{
private:

    QJsonObject load(const QString& path);
    bool save(const QString& path, const QJsonObject& data);

public:

    template <typename Item>
    QVector<Item> loadMusicItems(const QString& path) {
        static_assert(std::is_base_of<MusicItem::MusicItem, Item>::value,
                      "only MusicItems sub-classes are allowed");

        const QJsonObject obj = load(path);
        const QJsonArray items_array = obj.value("items").toArray();

        QVector<Item> data;
        data.reserve(items_array.size());

        for (const auto& item : items_array) {
            if(item.isObject())
                data.append(Item::fromJson(item.toObject()));
        }

        return data;
    }

    template <typename Item>
    bool saveMusicItems(const QString& path, const QVector<Item>& data) {
        static_assert(std::is_base_of<MusicItem::MusicItem, Item>::value,
                      "only MusicItems sub-classes are allowed");

        QJsonArray arr;
        for (const Item& item : data) {
            arr.append(item.toJson());
        }

        QJsonObject obj;
        obj["items"] = arr;

        return save(path, obj);
    }

};

}

#endif // USERDATALOADER_H