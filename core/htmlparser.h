#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include "htmldownloader.h"

#include <QObject>

struct UrlInfo
{
    enum Status
    {
        DOWNLOADING,
        PARSING,
        FINISHED
    };


    QString _url;
    Status _status;
    bool _found;
    float _percentage;
};


class HtmlParser : public QObject
{
    Q_OBJECT
public:
    explicit HtmlParser(const QUrl &url, const QString &text, QObject *parent = 0);
    QSet<HtmlParser *> get_links() const;
    void parse();
private:
    QSharedPointer<UrlInfo> _info;
    QString _content;
    const QString _text;
    QSet<HtmlParser*> _links;
    HtmlDownloader* _downloader;
    std::atomic<bool> _downloaded;
signals:
    void parsing();
    void processing(UrlInfo*);
public slots:
    void downloaded(QString);
    void downloadProgress(qint64,qint64);
};

#endif // HTMLPARSER_H
