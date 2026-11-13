#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

namespace HTTP_Literals {

const QString SOURCE_URL_ADDITIONAL = "https://ru.hitmox.net";

const QString QUERY_BASE = "https://ru.hitmox.net/search";
const QString GENRE_BASE = "https://ru.hitmox.net/genre/";
const QString COLLECTION_BASE = "https://ru.hitmox.net/collection/";
const QString ALBUM_BASE = "https://ru.hitmox.net/album/";
const QString ARTISTS_BASE = "https://ru.hitmox.net/artist/";

const QString PAGE_BASE = "/start/";
const int PAGE_STEP = 48;

}

#endif // CONFIG_H
