#include "numwidget.h"
#include <limits>

NumWidget::NumWidget(QWidget* parent)
    : EntitledWidget<QSpinBox>(parent)
{
    mSecondWidget->setMaximum(std::numeric_limits<int>::max());
}

NumWidget::~NumWidget()
{

}

void NumWidget::setNumber(const int number)
{
    mSecondWidget->setValue(number);
}

int NumWidget::number() const
{
    return mSecondWidget->value();
}
