#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "basewidget.h"
#include "textwidget.h"
#include "numwidget.h"
#include "urltable.h"

#include <QPushButton>
#include <QSharedPointer>

#include "processdata.h"
#include "core/objectsthree.h"

#include <core/htmlparser.h>

class MainWindow : public BaseWidget
{
    Q_OBJECT

private:
    typedef QSharedPointer<TextWidget> TextWidgetPtr;
    typedef QSharedPointer<NumWidget> NumWidgetPtr;
    typedef QSharedPointer<URLTable> URLTablePtr;
    typedef QSharedPointer<QPushButton> QPushButtonPtr;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void pressedStartResumeButton();
    void pressedStopButton();

public slots:
    void processUrl(UrlInfo*);

private:
    void updateWidget();

    void updateWidgetIfProccStarted();
    void updateWidgetIfProccNoStarted();

    void initChildWidgets();
    void addChildWidgets();

    void connectSignalSlot();

signals:
    void processStarted(const ProcessData& data);
    void processPaused();
    void processResumed();
    void procesStoped();

private:
    TextWidgetPtr mURL;
    TextWidgetPtr mFoundText;

    NumWidgetPtr mMaxUrlNumber;
    NumWidgetPtr mMaxThreadNumber;

    URLTablePtr mURLStatusTable;

    QPushButtonPtr mStartResumeButton;
    QPushButtonPtr mStopButton;

    bool mProssesStarted;
    bool mProssesPaused;

    ProcessData mProcData;

    ObjectsThree _core;
};

#endif // MAINWINDOW_H
