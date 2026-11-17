#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QStringLiteral>

namespace HTTP_Literals {

inline const QString SOURCE_URL_ADDITIONAL = QStringLiteral("https://ru.hitmox.net");

inline const QString QUERY_BASE = QStringLiteral("https://ru.hitmox.net/search");
inline const QString GENRE_BASE = QStringLiteral("https://ru.hitmox.net/genre/");
inline const QString COLLECTION_BASE = QStringLiteral("https://ru.hitmox.net/collection/");
inline const QString ALBUM_BASE = QStringLiteral("https://ru.hitmox.net/album/");
inline const QString ARTISTS_BASE = QStringLiteral("https://ru.hitmox.net/artist/");
inline const QString COLLECTIONS_BASE = QStringLiteral("https://ru.hitmox.net/collections");

inline const QString PAGE_BASE = QStringLiteral("/start/");
inline const int PAGE_STEP = 48;

inline const QString RADIO_BASE = QStringLiteral("https://ru.hitmox.net/radio");

inline const QString EMPTY_PAGE_STR = QStringLiteral("---");

}

namespace Codes_Literals {

inline const QString INVALID_URL = QStringLiteral("InvalidUrl");
inline const QString EMIT_ERROR = QStringLiteral("EmitError");
inline const QString REPLY_ERROR = QStringLiteral("ReplyError");
inline const QString PARSE_ERROR = QStringLiteral("ParseError");

}

#endif // CONFIG_H
