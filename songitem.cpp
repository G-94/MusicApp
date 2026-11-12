#include "songitem.h"

SongItem::SongItem(
    QString author, QString title, QString source_url,
    QString img_url, QString id, QString duration) noexcept :
    author_(std::move(author)), title_(std::move(title)), source_url_(std::move(source_url)),
    source_img_url_(std::move(img_url)), id_(QStringView(id).mid(id.lastIndexOf("-")).toInt(&isSuccess)),
    text_duration_(duration), duration_(Helper::castTextDurationToInt(duration))
{
    if (not isSuccess) { qDebug() << "Error while cast id to string"; return; }

    qDebug() << "Create song item with id: " << id_ << "\n";
}

QString& SongItem::getTitle() noexcept
{
    return title_;
}

QString &SongItem::getAuthor() noexcept
{
    return author_;
}

QString &SongItem::getTextDuration() noexcept
{
    return text_duration_;
}

quint16 SongItem::getDuration() const noexcept
{
    return duration_;
}

quint32 SongItem::getId() const noexcept
{
    return id_;
}

QString &SongItem::getSourceUrl() noexcept
{
    return source_url_;
}

QString &SongItem::getImgUrl() noexcept
{
    return source_img_url_;
}
