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
      _info(new UrlInfo, [](UrlInfo* p){delete p;}),
      _downloaded(false),
      _text(text),
      _downloader(nullptr)
{
    _info->_url = url.toString();
    _info->_found = false;
    _info->_status = UrlInfo::DOWNLOADING;
    _info->_percentage = 0;
    emit processing(_info.data());
    QThread * thread = new QThread();
    _downloader = new HtmlDownloader(url);
    _downloader->moveToThread(thread);

    connect( thread, SIGNAL(started()), _downloader, SLOT(doWork()));

    connect( _downloader, SIGNAL(finished(QString)), thread, SLOT(quit()));
    connect( _downloader, SIGNAL(finished(QString)), this, SLOT(downloaded(QString)), Qt::ConnectionType::DirectConnection);
    connect(_downloader, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));

    connect( thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}

void HtmlParser::downloadProgress(qint64 current,qint64 total)
{
    _info->_percentage = current/((float)total);
    emit processing(_info.data());
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
    _info->_status = UrlInfo::PARSING;
    emit processing(_info.data());
    _info->_found = _content.contains(_text, Qt::CaseInsensitive);


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
    _info->_status = UrlInfo::FINISHED;
    emit processing(_info.data());
}

void HtmlParser::downloaded(QString content)
{
    _content = content;
    _downloaded = true;
}
