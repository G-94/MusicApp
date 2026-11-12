#include "helperfunctions.h"

quint32 Helper::castTextDurationToInt(const QString &duration)
{
    QList<QStringView> parts = QStringView(duration).split(':');
    try {
        return parts.at(0).toInt() * 60 + parts.at(1).toInt();
    } catch (...) {
        return 0;
    }
}
