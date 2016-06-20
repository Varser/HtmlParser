#ifndef HTMLDOWNLOADER_H
#define HTMLDOWNLOADER_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QSharedPointer>
#include <QSemaphore>

class HtmlDownloader : public QObject
{
    Q_OBJECT
public:
    explicit HtmlDownloader(const QUrl& url,QObject *parent = 0);
    HtmlDownloader() = delete;
    QSharedPointer<QString> get_content() const;
private:
    QNetworkReply* _reply;
    QSharedPointer<QString> _content;
    QUrl _url;
    QNetworkAccessManager* _manager;
signals:
    //  Obtain download progress
    void downloadProgress(qint64,qint64);
    void finished(QSharedPointer<QString>);
public slots:
    void doWork();
    void download_finished();
private:
    static QSemaphore _num_threads;
};

#endif // HTMLDOWNLOADER_H
