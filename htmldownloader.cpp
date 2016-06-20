#include "htmldownloader.h"
#include <cassert>

#include <QEventLoop>

/*static */QSemaphore HtmlDownloader::_num_threads(10);

HtmlDownloader::HtmlDownloader(const QUrl &url, QObject *parent)
    :
      QObject(parent),
      _reply(nullptr),
      _url(url),
      _manager(nullptr),
      _content(new QString, [](QString* p){ delete p; })
{
}

QSharedPointer<QString> HtmlDownloader::get_content() const
{
    return _content;
}

void HtmlDownloader::download_finished()
{
    _content->clear();
    if (_reply)
        _content->append(_reply->readAll());
    if (_manager)
    {
        delete _manager;
        _manager = nullptr;
    }
    _reply = nullptr;
    _num_threads.release();
    emit finished(_content);
}

void HtmlDownloader::doWork()
{
    _num_threads.acquire();
    if (_reply || _manager)
        return;
    //  Perform get request
    QNetworkAccessManager* _manager = new QNetworkAccessManager(this);
    _reply = _manager->get(QNetworkRequest(_url));
    if (!_reply)
    {
        if (_manager)
        {
            delete _manager;
            _manager = nullptr;
        }
        return;
    }

    //  connect finish signal
    connect(_reply, SIGNAL(finished()), this, SLOT(download_finished()), Qt::DirectConnection);

    //  connect progress signal
    connect(_reply, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(downloadProgress(qint64,qint64)), Qt::DirectConnection);
}
