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