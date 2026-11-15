/*

-------------------------------------------------------------------------

    AlbumItem store albums main data

    title_ - name of album
    year_ - store year of album
    id_ - used to find albums songs, get album page

-------------------------------------------------------------------------

*/

#ifndef ALBUMITEM_H
#define ALBUMITEM_H

#include <QString>

#include "musicitem.h"

namespace Album {

class AlbumItem : MusicItem::MusicItem
{
public:
    explicit AlbumItem(QString title, QString year, QString id);

    QString getTitle() const noexcept;
    QString getYear() const noexcept;
    QString getId() const noexcept;

private:

    QString title_;
    QString year_;
    QString id_;

};

}

#endif // ALBUMITEM_H