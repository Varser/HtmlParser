#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include "htmldownloader.h"

#include <QObject>


class HtmlParser : public QObject
{
    Q_OBJECT
public:
    explicit HtmlParser(const QUrl &url, const QString &text, QObject *parent = 0);
    bool operator==(const HtmlParser& other);
    bool operator==(const QUrl& another);
    QSet<HtmlParser *> get_links() const;
    void parse();
private:
    QString _content;
    const QUrl _url;
    const QString _text;
    bool _found;
    QSet<HtmlParser*> _links;
    HtmlDownloader* _downloader;
    std::atomic<bool> _downloaded;
signals:

public slots:
    void downloaded(QSharedPointer<QString>);
};

#endif // HTMLPARSER_H
