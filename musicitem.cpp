#include "musicitem.h"

int MusicItem::MusicItem::getPlayedCounter() const noexcept
{
    return played_counter_;
}

void MusicItem::MusicItem::setPlayedCounter(int new_val) noexcept
{
    played_counter_ = new_val;
}

void MusicItem::MusicItem::incrPlayedCounter() noexcept
{
    ++played_counter_;
}