#include "htmlparser.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QRegularExpressionMatch>
#include <QRegularExpression>

#include <QThread>

#include <cassert>


HtmlParser::HtmlParser(const QUrl &url, const QString &text, QObject *parent)
    :
      QObject(parent),
      _url(url),
      _found(false),
      _downloaded(false),
      _text(text),
      _downloader(nullptr)
{
    QThread * thread = new QThread();
    _downloader = new HtmlDownloader(url);
    _downloader->moveToThread(thread);

    connect( thread, SIGNAL(started()), _downloader, SLOT(doWork()));

    connect( _downloader, SIGNAL(finished(QSharedPointer<QString>)), thread, SLOT(quit()));
    connect( _downloader, SIGNAL(finished(QSharedPointer<QString>)), this, SLOT(downloaded(QSharedPointer<QString>)), Qt::ConnectionType::DirectConnection);


    connect( thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
//    connect( thread, SIGNAL(finished()), _downloader, SLOT(deleteLater()));

    thread->start();
}

bool HtmlParser::operator==(const HtmlParser& other)
{
    return _url == other._url;
}

bool HtmlParser::operator==(const QUrl& another)
{
    return _url == another;
}


QSet<HtmlParser *> HtmlParser::get_links() const
{
    return _links;
}

void HtmlParser::parse()
{
    while(!_downloaded)
    {
        QThread::msleep(10);
    }
    _found = _content.contains(_text, Qt::CaseInsensitive);


    int start_offset = -1;
    QRegularExpression regExp("(?:https?|ftp)://(((((((((\\w|\\d)|\\055)|\\056)|\\046)|\\077)|\\043)|\\045)|\\057)|\\075)+");

    while (true)
    {
        QRegularExpressionMatch match = regExp.match(_content, ++start_offset);
        if (!match.hasMatch())
            break;
        start_offset = match.capturedStart();
        int end_offset = match.capturedEnd();
        _links << new HtmlParser(_content.mid(start_offset, end_offset), _text);
    }
    _content.clear();
    if (_downloader)
        delete _downloader;
    _downloader = nullptr;
}

void HtmlParser::downloaded(QSharedPointer<QString> content)
{
    _content = *content.data();
    _downloaded = true;
}
