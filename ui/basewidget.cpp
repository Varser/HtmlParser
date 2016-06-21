#include <cassert>
#include "basewidget.h"

BaseWidget::BaseWidget(QWidget* parent)
    : QWidget(parent)
    , mWidgetLayout(nullptr)
{
    mWidgetLayout = QGridLayoutPtr(new QGridLayout());
    setLayout(mWidgetLayout.data());
}

BaseWidget::~BaseWidget()
{
}

void BaseWidget::addWidgetToLayout(QWidget* wd, int row, int column, int rowSpawn, int colSpawn, Qt::Alignment aligment)
{
    assert(mWidgetLayout != nullptr);
    mWidgetLayout->addWidget(wd, row, column, rowSpawn, colSpawn, aligment);
}
