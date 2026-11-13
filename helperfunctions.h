#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <QString>
#include <QList>
#include <QJsonObject>

#include "config.h"

namespace Helper {
quint32 castTextDurationToInt(const QString& duration) noexcept;

QString checkSourceUrl(QString url);

QJsonObject parseJsonStr(const QString& jsonText);
}

#endif // HELPERFUNCTIONS_H
