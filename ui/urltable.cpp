#include "urltable.h"
#include <QHeaderView>
#include <QSizePolicy>

#include <core/htmlparser.h>


URLTable::URLTable(QWidget* parent)
    : QTableWidget(parent)
{
    setColumnCount(2);

    setHorizontalHeaderLabels(QStringList() << "url" << "status");

    horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}

URLTable::~URLTable()
{

}

void URLTable::insertItem(UrlInfo* info)
{
    auto result = this->findItems(info->_url, Qt::MatchExactly);
    if (result.empty())
    {
        int row_count = this->rowCount();
        this->insertRow(row_count);
        this->setItem(row_count, 0, new QTableWidgetItem(info->_url));
        QTableWidgetItem* status = new QTableWidgetItem;
        switch (info->_status)
        {
        case UrlInfo::DOWNLOADING:
            status->setText("Downloading...");
        case UrlInfo::PARSING:
            status->setText("Parsing...");
        case UrlInfo::FINISHED:
            status->setText("Ready...");
        }

        this->setItem(row_count, 1, status);
    }
    else
    {
        int row = result.at(0)->row();
        QTableWidgetItem* status = new QTableWidgetItem;
        switch (info->_status)
        {
        case UrlInfo::DOWNLOADING:
            status->setText("Downloading...");
        case UrlInfo::PARSING:
            status->setText("Parsing...");
        case UrlInfo::FINISHED:
            status->setText("Ready...");
        }

        this->setItem(row, 1, status);
    }
}
