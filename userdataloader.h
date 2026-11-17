/*

-------------------------------------------------------------------------



-------------------------------------------------------------------------

*/

#ifndef USERDATALOADER_H
#define USERDATALOADER_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QSaveFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>

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

private:

    QJsonObject load(const QString& path);
    bool save(const QString& path, const QJsonObject& data);

};

}

#endif // USERDATALOADER_H
