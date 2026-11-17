#include "albumitem.h"

Album::AlbumItem::AlbumItem(QString title, QString year, QString id) :
    title_(std::move(title)), year_(std::move(year)), id_(std::move(id))
{}

QString Album::AlbumItem::getTitle() const noexcept
{
    return title_;
}

QString Album::AlbumItem::getYear() const noexcept
{
    return year_;
}

QString Album::AlbumItem::getId() const noexcept
{
    return id_;
}

QJsonObject Album::AlbumItem::toJson() const
{
    QJsonObject obj;
    obj["title"] = title_;
    obj["id"] = id_;
    obj["year"] = year_;
    obj["playedCounter"] = getPlayedCounter();
    return obj;
}

Album::AlbumItem Album::AlbumItem::fromJson(const QJsonObject &obj)
{
    Album::AlbumItem item {
        obj.value("title").toString(),
        obj.value("year").toString(),
        obj.value("id").toString()
    };

    item.setPlayedCounter(obj.value("playedCounter").toInt());

    return item;
}