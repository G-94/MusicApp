/*

-------------------------------------------------------------------------

    NetworkBypass class is used to pass through
        403 error on songs links (urls)

    getMirrorUrl method is used to get mirror workable link
        that can be used to connect resourece to stream

-------------------------------------------------------------------------

*/

#ifndef NETWORKBYPASS_H
#define NETWORKBYPASS_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QObject>
#include <QString>

#include "config.h"

namespace Api {

class NetworkBypass final : public QObject
{
    Q_OBJECT
public:
    NetworkBypass(QObject *parent = nullptr);

    void getMirrorUrl(const QUrl& url);

private:

    QNetworkAccessManager* manager_;

signals:

    void error(QString msg);
    void mirrorFind(QUrl result);

};

}

#endif // NETWORKBYPASS_H