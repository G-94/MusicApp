#include "genreitem.h"

Genre::GenreItem::GenreItem(QString title, QString id) :
    title_(title), id_(id)
{}

QString Genre::GenreItem::getTitle() const noexcept
{
    return title_;
}

QString Genre::GenreItem::getId() const noexcept
{
    return id_;
}
QJsonObject Genre::GenreItem::toJson() const
{
    QJsonObject obj;
    obj["title"] = title_;
    obj["id"] = id_;
    obj["playedCounter"] = getPlayedCounter();
    return obj;
}

Genre::GenreItem Genre::GenreItem::fromJson(const QJsonObject &obj)
{
    Genre::GenreItem item {
        obj.value("title").toString(),
        obj.value("id").toString(),
    };

    item.setPlayedCounter(obj.value("playedCounter").toInt());

    return item;
}