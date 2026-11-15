#include "collectionitem.h"

Collection::CollectionItem::CollectionItem(QString name, QString id) :
    name_(std::move(name)), id_(std::move(id))
{}

QString Collection::CollectionItem::getName() const noexcept
{
    return name_;
}

QString Collection::CollectionItem::getId() const noexcept
{
    return id_;
}

int Collection::CollectionItem::getPlayedCounter() const noexcept
{
    return played_counter_;
}

void Collection::CollectionItem::setPlayedCounter(int new_val) noexcept
{
    played_counter_ = new_val;
}

void Collection::CollectionItem::incrPlayedCounter() noexcept
{
    ++played_counter_;
}
