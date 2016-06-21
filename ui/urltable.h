#ifndef URLTABLE_H
#define URLTABLE_H

#include <QTableWidget>

#include "basewidget.h"

struct UrlInfo;

class URLTable : public QTableWidget
{
    Q_OBJECT

public:
    URLTable(QWidget* parent = 0);

    virtual ~URLTable();
    void insertItem(UrlInfo*);
};

#endif // URLTABLE_H
