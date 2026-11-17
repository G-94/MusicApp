/*

-------------------------------------------------------------------------

    SongItem class store songs main data:

    author_, title_, text_duration_ is used like meta-data
    source_url_ provides access to download and play songs
    id_ is used to find track
    duration_ what integer type used for play tracks
    source_img_ is unused but maybe will be need in future
    is_playable_ is variable what show state of song

-------------------------------------------------------------------------

*/

#ifndef SONGITEM_H
#define SONGITEM_H

#include <QJsonObject>
#include <QString>
#include <QDebug>

#include "helperfunctions.h"
#include "musicitem.h"

namespace Song {

class SongItem : MusicItem::MusicItem
{
public:
    explicit SongItem(
        QString author,
        QString title,
        QString source_url,
        QString img_url,
        QString id,
        QString duration
    ) noexcept;

    QString& getTitle() noexcept;
    QString& getAuthor() noexcept;
    QString& getTextDuration() noexcept;
    unsigned short getDuration() const noexcept;
    QString getId() const noexcept;
    QString& getSourceUrl() noexcept;
    QString& getImgUrl() noexcept;
    bool isPlayable() const noexcept;

    bool isLiked() const noexcept;
    bool isDownloaded() const noexcept;

    void setLikeStatus(bool state) noexcept;
    void setDownloadStatus(bool state) noexcept;

    QJsonObject toJson() const override;
    static SongItem fromJson(const QJsonObject& obj);

private:

// song meta data
    QString title_;
    QString author_;

    unsigned short duration_;
    QString text_duration_;

    QString id_;

// song source data
    QString source_img_url_;
    QString source_url_;

// state of song
    bool is_playable_ = true;

    bool is_liked_ = false;
    bool is_downloaded_ = false;

//init success flag
    bool isSuccess;

signals:
};

}

#endif // SONGITEM_H