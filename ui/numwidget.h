#ifndef NUMWIDGET_H
#define NUMWIDGET_H

#include <QSpinBox>

#include "entitledwidget.h"

class NumWidget : public EntitledWidget<QSpinBox>
{
    Q_OBJECT

public:
    NumWidget(QWidget* parent = 0);
    ~NumWidget();

    void setNumber(const int number);

    int number() const;
};

#endif // NUMWIDGET_H
