/*

-------------------------------------------------------------------------

    Classes of exceptions what used in other classes
    QException is base class for all self-made exceptions

-------------------------------------------------------------------------

*/

#ifndef USERDATALOADER_H
#define USERDATALOADER_H

#include <QString>
#include <QVector>
#include <QJsonObject>
#include <QJsonDocument>

#include "songitem.h"
#include "radioitem.h"
#include "albumitem.h"
#include "artistitem.h"
#include "collectionitem.h"

namespace User_Data {

class UserDataLoader
{
public:
    UserDataLoader();
};

}

#endif // USERDATALOADER_H
