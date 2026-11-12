#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <QString>
#include <QList>
#include <QJsonObject>

namespace Helper {
quint32 castTextDurationToInt(const QString& duration) noexcept;

QJsonObject parseJsonStr(const QString& jsonText);
}

#endif // HELPERFUNCTIONS_H
