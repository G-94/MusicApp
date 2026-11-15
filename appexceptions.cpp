#include "appexceptions.h"

//ConnectionApiException methods

AppExceptions::ConnectionApiException::ConnectionApiException(QString url):
    source_url_(std::move(url)), message_("Failed to connect to resource: " + source_url_.toStdString())
{}

const char *AppExceptions::ConnectionApiException::what() const noexcept
{
    return message_.c_str();
}

void AppExceptions::ConnectionApiException::raise() const
{
    throw *this;
}

AppExceptions::ConnectionApiException *AppExceptions::ConnectionApiException::clone() const
{
    return new ConnectionApiException(*this);
}

//InvalidUrlExcpetion methods

AppExceptions::InvalidUrlException::InvalidUrlException(QString url):
    source_url_(std::move(url)), message_("Invalid url: " + source_url_.toStdString())
{}

const char *AppExceptions::InvalidUrlException::what() const noexcept
{
    return message_.c_str();
}

void AppExceptions::InvalidUrlException::raise() const
{
    throw *this;
}

AppExceptions::InvalidUrlException *AppExceptions::InvalidUrlException::clone() const
{
    return new InvalidUrlException(*this);
}

//ParseDataException

AppExceptions::ParseDataException::ParseDataException(QString msg) : message_(std::move(msg.toStdString()))
{}

const char *AppExceptions::ParseDataException::what() const noexcept
{
    return message_.c_str();
}

void AppExceptions::ParseDataException::raise() const
{
    throw *this;
}

AppExceptions::ParseDataException *AppExceptions::ParseDataException::clone() const
{
    return new ParseDataException(*this);
}