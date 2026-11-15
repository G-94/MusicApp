/*

-------------------------------------------------------------------------

    AlbumItem store albums main data

    name_ - name of album
    year_ - store year of album
    id_ - used to find albums songs, get album page

-------------------------------------------------------------------------

*/

#ifndef COLLECTIONITEM_H
#define COLLECTIONITEM_H

#include <QString>

namespace Collection {

class CollectionItem
{
public:
    explicit CollectionItem(QString name, QString id);

    QString getName() const noexcept;
    QString getId() const noexcept;

    int getPlayedCounter() const noexcept;
    void setPlayedCounter(int new_val) noexcept;
    void incrPlayedCounter() noexcept;

private:

    QString name_;
    QString id_;

    // played counter
    int played_counter_ = 0;
};

}

#endif // COLLECTIONITEM_H
