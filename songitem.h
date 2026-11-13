/*

-------------------------------------------------------------------------

    SongItem class store songs main data:

    author_, title_, text_duration_ is used like meta-data
    source_url_ provides access to download and play songs
    id_ is used to find track
    duration_ what integer type used for play tracks
    source_img_ is unused but maybe will be need in future

-------------------------------------------------------------------------

*/

#ifndef SONGITEM_H
#define SONGITEM_H

#include <QObject>
#include <QString>
#include <QDebug>

#include "helperfunctions.h"

namespace Song {

class SongItem
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
    quint16 getDuration() const noexcept;
    quint32 getId() const noexcept;
    QString& getSourceUrl() noexcept;
    QString& getImgUrl() noexcept;

private:

// song meta data
    QString title_;
    QString author_;

    quint16 duration_;
    QString text_duration_;

    quint32 id_;

// song source data
    QString source_img_url_;
    QString source_url_;

//init success flag
    bool isSuccess;

signals:
};

}

#endif // SONGITEM_H
