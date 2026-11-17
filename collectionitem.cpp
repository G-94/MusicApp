#include "collectionitem.h"

Collection::CollectionItem::CollectionItem(QString title, QString id) :
    title_(std::move(title)), id_(std::move(id))
{}

QString Collection::CollectionItem::getTitle() const noexcept
{
    return title_;
}

QString Collection::CollectionItem::getId() const noexcept
{
    return id_;
}

QJsonObject Collection::CollectionItem::toJson()
{
    QJsonObject obj;
    obj["title"] = title_;
    obj["id"] = id_;
    obj["playedCounter"] = getPlayedCounter();
    return obj;
}