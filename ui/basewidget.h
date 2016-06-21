#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QSharedPointer>

class BaseWidget : public QWidget
{
    Q_OBJECT

private:
    typedef QSharedPointer<QGridLayout> QGridLayoutPtr;

public:
    BaseWidget(QWidget* parent = 0);
    virtual ~BaseWidget();

    void addWidgetToLayout(QWidget* wd, int row, int column, int rowSpawn, int colSpawn, Qt::Alignment aligment = 0);

protected:
    QGridLayoutPtr mWidgetLayout;
};

#endif // BASEWIDGET_H
