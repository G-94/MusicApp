/*

-------------------------------------------------------------------------

    AlbumItem store albums main data

    name_ - name of album
    year_ - store year of album
    id_ - used to find albums songs, get album page

-------------------------------------------------------------------------

*/

#ifndef ALBUMITEM_H
#define ALBUMITEM_H

#include <QString>

namespace Album {

class AlbumItem
{
public:
    explicit AlbumItem(QString name, QString year, QString id);

    QString getName() const noexcept;
    QString getYear() const noexcept;
    QString getId() const noexcept;

private:

    QString name_;
    QString year_;
    QString id_;

};

}

#endif // ALBUMITEM_H