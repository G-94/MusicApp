#include "artistitem.h"


ArtistItem::ArtistItem(QString name, QString id) :
    name_(std::move(name)), id_(std::move(id))
{}

QString ArtistItem::getName() const noexcept
{
    return name_;
}

QString ArtistItem::getId() const noexcept
{
    return id_;
}
