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
    QString get_content() const;
private:
    QNetworkReply* _reply;
    QString _content;
    QUrl _url;
    QNetworkAccessManager* _manager;
signals:
    //  Obtain download progress
    void downloadProgress(qint64,qint64);
    void finished(QString);
public slots:
    void doWork();
    void download_finished();
public:
    static void initialize_threads_count(int count);
private:
    static QSharedPointer<QSemaphore> _num_threads;
};

#endif // HTMLDOWNLOADER_H
