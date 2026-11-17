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

bool MusicItem::MusicItem::isLiked() const noexcept
{
    return is_liked_;
}

bool MusicItem::MusicItem::isDownloaded() const noexcept
{
    return is_downloaded_;
}

void MusicItem::MusicItem::setLikeStatus(bool state) noexcept
{
    is_liked_ = state;
}

void MusicItem::MusicItem::setDownloadStatus(bool state) noexcept
{
    is_downloaded_ = state;
}