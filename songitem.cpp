#include "songitem.h"

Song::SongItem::SongItem(
    QString author, QString title, QString source_url,
    QString img_url, QString id, QString duration) noexcept :
    author_(std::move(author)), title_(std::move(title)), source_url_(Helper::checkSourceUrl(source_url)),
    source_img_url_(std::move(img_url)), id_(QStringView(id).mid(id.lastIndexOf("-") + 1)),
    text_duration_(duration), duration_(Helper::castTextDurationToInt(duration))
{
    if (not isSuccess) {
        qDebug() << "Error while cast id to string";
        is_playable_ = false;
        return;
    }

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

unsigned short Song::SongItem::getDuration() const noexcept
{
    return duration_;
}

QString Song::SongItem::getId() const noexcept
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

bool Song::SongItem::isPlayable() const noexcept
{
    return is_playable_;
}

bool Song::SongItem::isLiked() const noexcept
{
    return is_liked_;
}

bool Song::SongItem::isDownloaded() const noexcept
{
    return is_downloaded_;
}

void Song::SongItem::setLikeStatus(bool state) noexcept
{
    is_liked_ = state;
}

void Song::SongItem::setDownloadStatus(bool state) noexcept
{
    is_downloaded_ = state;
}

QJsonObject Song::SongItem::toJson()
{
    QJsonObject obj;
    obj["title"] = title_;
    obj["author"] = author_;
    obj["url"] = source_url_;
    obj["imgUrl"] = source_img_url_;
    obj["duration"] = text_duration_;
    obj["id"] = id_;
    obj["playedCounter"] = getPlayedCounter();
    obj["isLiked"] = is_liked_;
    obj["isDownloaded"] = is_downloaded_;
    return obj;
}

