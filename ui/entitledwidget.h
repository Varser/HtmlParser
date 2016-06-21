#ifndef ENTITLEDWIDGET_H
#define ENTITLEDWIDGET_H

#include <QLabel>
#include <QSharedPointer>

#include "basewidget.h"

template<typename SecondWidgetType>
class EntitledWidget : public BaseWidget
{
private:
    typedef QSharedPointer<QLabel> QLabelPtr;
    typedef QSharedPointer<SecondWidgetType> SecondWidgetTypePtr;

public:
    EntitledWidget(QWidget* parent = 0)
        : BaseWidget(parent)
        , mWidgetLabel(nullptr)
        , mSecondWidget(nullptr)
    {
        mWidgetLabel = QLabelPtr(new QLabel(this));
        mSecondWidget = SecondWidgetTypePtr(new SecondWidgetType(this));

        addWidgetToLayout(mWidgetLabel.data(), 0, 0, 1, 1);
        addWidgetToLayout(mSecondWidget.data(), 0, 1, 1, 1);
    }

    virtual ~EntitledWidget()
    {

    }

    void setLabel(const QString& label)
    {
        mWidgetLabel->setText(label);
    }

    QString label() const
    {
        return mWidgetLabel->text();
    }

    void setActive(bool active)
    {
        mSecondWidget->setEnabled(active);
    }

protected:
    QLabelPtr mWidgetLabel;
    SecondWidgetTypePtr mSecondWidget;
};

#endif // ENTITLEDWIDGET_H
