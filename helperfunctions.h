/*

-------------------------------------------------------------------------

    Helper Functions is
        used to solve some simple problems in different classes

-------------------------------------------------------------------------

*/

#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <QString>
#include <QList>
#include <QJsonObject>

#include "appexceptions.h"
#include "config.h"

namespace Helper {
quint32 castTextDurationToInt(const QString& duration) noexcept;

QString checkSourceUrl(QString url);

QString getOnlyNumericFromStr(const QString& str);

QJsonObject parseJsonStr(const QString& jsonText);

}

#endif // HELPERFUNCTIONS_H
