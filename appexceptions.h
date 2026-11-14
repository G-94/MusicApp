/*

-------------------------------------------------------------------------

    Classes of exceptions what used in other classes
    QException is base class for all self-made exceptions

-------------------------------------------------------------------------

*/

#ifndef APPEXCEPTIONS_H
#define APPEXCEPTIONS_H

#include <QString>
#include <QException>

namespace AppExceptions {

class ConnectionApiException : public QException {
public:
    explicit ConnectionApiException(QString url);
    const char* what() const noexcept override;

    void raise() const override;
    ConnectionApiException *clone() const override;

private:

    QString source_url_;
    std::string message_;
};

class InvalidUrlException : public QException {
public:
    explicit InvalidUrlException(QString url);
    const char* what() const noexcept override;

    void raise() const override;
    InvalidUrlException *clone() const override;

private:

    QString source_url_;
    std::string message_;
};

class ParseDataException : public QException {
public:
    explicit ParseDataException(QString msg);
    const char* what() const noexcept override;

    void raise() const override;
    ParseDataException *clone() const override;

private:

    std::string message_;
};

}

#endif // APPEXCEPTIONS_H