#ifndef OBJECTSTHREE_H
#define OBJECTSTHREE_H

#include <QObject>

#include <core/htmlparser.h>
#include <ui/processdata.h>

class ObjectsThree : public QObject
{
    Q_OBJECT
public:
    explicit ObjectsThree(QObject *parent = 0);

    void process();
    void start();

private:
    QUrl _url;
    QString _text;
    volatile bool _paused, _stopped;
signals:
    void workFinished();
    void processing(UrlInfo*);
public slots:
    void doWork();
    void init(const ProcessData& data);
    void pause();
    void resume();
    void stop();
};

#endif // OBJECTSTHREE_H
