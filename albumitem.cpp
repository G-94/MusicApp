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

int Album::AlbumItem::getPlayedCounter() const noexcept
{
    return played_counter_;
}

void Album::AlbumItem::setPlayedCounter(int new_val) noexcept
{
    played_counter_ = new_val;
}

void Album::AlbumItem::incrPlayedCounter() noexcept
{
    ++played_counter_;
}