#include "textwidget.h"

TextWidget::TextWidget(QWidget *parent)
    : EntitledWidget<QLineEdit>(parent)
{

}

TextWidget::~TextWidget()
{

}

void TextWidget::setText(const QString& text)
{
    mSecondWidget->setText(text);
}

QString TextWidget::text() const
{
    return mSecondWidget->text();
}
