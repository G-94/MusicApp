#include "songitem.h"

Song::SongItem::SongItem(
    QString author, QString title, QString source_url,
    QString img_url, QString id, QString duration) noexcept :
    author_(std::move(author)), title_(std::move(title)), source_url_(Helper::checkSourceUrl(source_url)),
    source_img_url_(std::move(img_url)), id_(QStringView(id).mid(id.lastIndexOf("-") + 1).toInt(&isSuccess)),
    text_duration_(duration), duration_(Helper::castTextDurationToInt(duration))
{
    if (not isSuccess) { qDebug() << "Error while cast id to string"; return; }
    qDebug() << "Create song item with id: " << id_ << "\n";
}

QString& Song::SongItem::getTitle() noexcept
{
    return title_;
}

QString &Song::SongItem::getAuthor() noexcept
{
    return author_;
}

QString &Song::SongItem::getTextDuration() noexcept
{
    return text_duration_;
}

quint16 Song::SongItem::getDuration() const noexcept
{
    return duration_;
}

quint32 Song::SongItem::getId() const noexcept
{
    return id_;
}

QString &Song::SongItem::getSourceUrl() noexcept
{
    return source_url_;
}

QString &Song::SongItem::getImgUrl() noexcept
{
    return source_img_url_;
}
