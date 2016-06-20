#include "objectsthree.h"

#include <QThread>
#include <QSet>

ObjectsThree::ObjectsThree(const QUrl &url, const QString &text, QObject *parent)
    :
      QObject(parent),
      _url(url),
      _text(text)
{

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
    while(iterator != parsers.end())
    {
        HtmlParser* current_parser = *iterator;
        current_parser->parse();
        parsers.unite(current_parser->get_links());
        ++iterator;
    }
    emit workFinished();
}

void ObjectsThree::start()
{
    QThread * thread = new QThread();
    this->moveToThread(thread);

    connect( thread, SIGNAL(started()), this, SLOT(doWork()));

    connect( this, SIGNAL(workFinished()), thread, SLOT(quit()));


    connect( thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();

}
