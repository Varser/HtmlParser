#include "objectsthree.h"

#include <QThread>
#include <QSet>

ObjectsThree::ObjectsThree(QObject *parent)
    :
      QObject(parent),
      _paused(false),
      _stopped(false)
{

}

void ObjectsThree::init(const ProcessData &data)
{
    _url = data.getURL();
    _text = data.getFindString();
    start();
}

void ObjectsThree::doWork()
{
    process();
}

void ObjectsThree::process()
{
    QSet<HtmlParser*> parsers;
    parsers << new HtmlParser(_url, _text);
    QSet<HtmlParser *>::iterator iterator = parsers.begin();
    while(iterator != parsers.end() && ! _stopped)
    {
        while (_paused)
        {
            QThread::msleep(10);
        }
        HtmlParser* current_parser = *iterator;
        connect(current_parser, SIGNAL(processing(UrlInfo*)), this, SIGNAL(processing(UrlInfo*)));
        current_parser->parse();
        parsers.unite(current_parser->get_links());
        ++iterator;
    }
    emit workFinished();
}

void ObjectsThree::start()
{
    if (_url.isEmpty() || _text.isEmpty())
        return;
    QThread * thread = new QThread();
    this->moveToThread(thread);

    connect( thread, SIGNAL(started()), this, SLOT(doWork()));

    connect( this, SIGNAL(workFinished()), thread, SLOT(quit()));


    connect( thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();

}

void ObjectsThree::pause()
{
    _paused = true;
}

void ObjectsThree::resume()
{
    _paused = false;
}

void ObjectsThree::stop()
{
    _stopped = true;
}
