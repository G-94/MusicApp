#include "albumitem.h"

Album::AlbumItem::AlbumItem(QString name, QString year, QString id) :
    name_(std::move(name)), year_(std::move(year)), id_(std::move(id))
{}

QString Album::AlbumItem::getName() const noexcept
{
    return name_;
}

QString Album::AlbumItem::getYear() const noexcept
{
    return year_;
}

QString Album::AlbumItem::getId() const noexcept
{
    return id_;
}