#ifndef OBJECTSTHREE_H
#define OBJECTSTHREE_H

#include <QObject>

#include <htmlparser.h>

class ObjectsThree : public QObject
{
    Q_OBJECT
public:
    explicit ObjectsThree(const QUrl& url, const QString& text, QObject *parent = 0);

    void process();
    void start();

private:
    QUrl _url;
    QString _text;
signals:
    void workFinished();
public slots:
    void doWork();
};

#endif // OBJECTSTHREE_H
