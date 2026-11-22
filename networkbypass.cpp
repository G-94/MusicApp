#include "networkbypass.h"

Api::NetworkBypass::NetworkBypass(QObject *parent) : QObject(parent), manager_(nullptr)
{
    manager_ = new QNetworkAccessManager(this);
}

void Api::NetworkBypass::getMirrorUrl(const QUrl &url)
{
    if (url.isEmpty()) {
        emit error(Codes_Literals::INVALID_URL);
        return;
    }

    QNetworkRequest request(url);
    QNetworkReply* reply = manager_->get(request);

    QObject::connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() != QNetworkReply::NoError) {
            emit error(Codes_Literals::REPLY_ERROR);
        }

        const QUrl mirror_url = reply->url();
        if (not mirror_url.isEmpty()) {
            emit mirrorFind(mirror_url);
        } else {
            emit error(Codes_Literals::INVALID_URL);
        }

        reply->deleteLater();
    });
}