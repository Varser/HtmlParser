#ifndef URLWIDGET_H
#define URLWIDGET_H

#include <QLineEdit>

#include "entitledwidget.h"

class TextWidget : public EntitledWidget<QLineEdit>
{
    Q_OBJECT

public:
    TextWidget(QWidget *parent = 0);
    ~TextWidget();


    void setText(const QString& text);

    QString text() const;
};

#endif // URLWIDGET_H
