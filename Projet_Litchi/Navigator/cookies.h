#ifndef COOKIES_H
#define COOKIES_H

#include <QtGui>

#include <QtNetwork/QNetworkCookieJar>

class CookieJar : public QNetworkCookieJar
{
    public:
        CookieJar(QObject* parent);
        ~CookieJar();
        QList<QNetworkCookie> cookiesForUrl ( const QUrl & url ) const;
        bool setCookiesFromUrl ( const QList<QNetworkCookie> & cookieList, const QUrl & url );
};

#endif
