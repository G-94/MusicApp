#include "artistitem.h"

Artists::ArtistItem::ArtistItem(QString name, QString id) :
    name_(std::move(name)), id_(std::move(id))
{}

QString Artists::ArtistItem::getName() const noexcept
{
    return name_;
}

QString Artists::ArtistItem::getId() const noexcept
{
    return id_;
}

QJsonObject Artists::ArtistItem::toJson() const
{
    QJsonObject obj;
    obj["name"] = name_;
    obj["id"] = id_;
    obj["playedCounter"] = getPlayedCounter();
    return obj;
}

Artists::ArtistItem Artists::ArtistItem::fromJson(const QJsonObject &obj)
{
    Artists::ArtistItem item {
        obj.value("title").toString(),
        obj.value("id").toString(),
    };

    item.setPlayedCounter(obj.value("playedCounter").toInt());

    return item;
}