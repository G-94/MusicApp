#ifndef MUSICAPI_H
#define MUSICAPI_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QString>
#include <QVector>
#include <QUrlQuery>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QLatin1String>

#include "config.h"
#include "songitem.h"
#include "appexceptions.h"

namespace Api {

class MusicApi : public QObject
{
    Q_OBJECT
public:
    explicit MusicApi(QObject *parent = nullptr);

    void getSongsByQuery(const QString& query);

private:

    QNetworkAccessManager* manager;

signals:
};

}

#endif // MUSICAPI_H
