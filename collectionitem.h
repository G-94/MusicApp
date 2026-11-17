/*

-------------------------------------------------------------------------

    CollectionItem store collection main data
        Collection like album but songs chosen by resource
    title_ - name of collection
    id_ - used to find collections songs, get collection page

-------------------------------------------------------------------------

*/

#ifndef COLLECTIONITEM_H
#define COLLECTIONITEM_H

#include <QString>

#include "musicitem.h"

namespace Collection {

class CollectionItem : MusicItem::MusicItem
{
public:
    explicit CollectionItem(QString title, QString id);

    QString getTitle() const noexcept;
    QString getId() const noexcept;

private:

    QString title_;
    QString id_;

};

}

#endif // COLLECTIONITEM_H