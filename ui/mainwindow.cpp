#include "mainwindow.h"
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent)
    : BaseWidget(parent)
    , mURL(nullptr)
    , mFoundText(nullptr)
    , mMaxUrlNumber(nullptr)
    , mMaxThreadNumber(nullptr)
    , mURLStatusTable(nullptr)
    , mStartResumeButton(nullptr)
    , mStopButton(nullptr)
    , mProssesStarted(false)
    , mProssesPaused(true)
    , mProcData(ProcessData())
{
    initChildWidgets();
    addChildWidgets();
    updateWidget();

    connectSignalSlot();
}

MainWindow::~MainWindow()
{
}

void MainWindow::pressedStartResumeButton()
{
    if(!mProssesStarted && mProssesPaused)
    {
        mProcData.setURL(mURL->text());
        mProcData.setFindString(mFoundText->text());
        mProcData.setNumThread(mMaxThreadNumber->number());
        mProcData.setMaxNumURL(mMaxUrlNumber->number());

        mURL->setEnabled(false);
        mFoundText->setEnabled(false);
        mMaxThreadNumber->setEnabled(false);
        mMaxUrlNumber->setEnabled(false);

        mURLStatusTable->clear();
        emit processStarted(mProcData);
    }
    else
    {
        if(!mProssesPaused)
        {
            emit processPaused();
        }
        else
        {
            emit processResumed();
        }
    }

    mProssesStarted = true;
    mProssesPaused = !mProssesPaused;
    updateWidget();
}

void MainWindow::pressedStopButton()
{
    emit procesStoped();
    mProssesStarted = false;
    mProssesPaused = true;

    mStartResumeButton->setText("Start");

    mURL->setEnabled(true);
    mFoundText->setEnabled(true);
    mMaxThreadNumber->setEnabled(true);
    mMaxUrlNumber->setEnabled(true);

    updateWidget();
}

void MainWindow::updateWidget()
{
    if(mProssesStarted)
    {
        updateWidgetIfProccStarted();

    }
    else
    {
        updateWidgetIfProccNoStarted();
    }
}

void MainWindow::updateWidgetIfProccStarted()
{
    mStopButton->setHidden(false);
    if(mProssesPaused)
    {
        mStartResumeButton->setText("Resume");
    }
    else
    {
        mStartResumeButton->setText("Pause");
    }
}

void MainWindow::updateWidgetIfProccNoStarted()
{
    mStopButton->setHidden(true);
    mStartResumeButton->setText("Start");
}

void MainWindow::initChildWidgets()
{
    mURL = TextWidgetPtr(new TextWidget(this));
    mURL->setLabel("url");

    mFoundText = TextWidgetPtr(new TextWidget(this));
    mFoundText->setLabel("found text");

    mMaxUrlNumber = NumWidgetPtr(new NumWidget(this));
    mMaxUrlNumber->setLabel("max url number");
    mMaxUrlNumber->setNumber(30);

    mMaxThreadNumber = NumWidgetPtr(new NumWidget(this));
    mMaxThreadNumber->setLabel("max thread number");
    mMaxThreadNumber->setNumber(4);

    mURLStatusTable = URLTablePtr(new URLTable(this));
    mURLStatusTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mStartResumeButton = QPushButtonPtr(new QPushButton(this));
    mStopButton = QPushButtonPtr(new QPushButton(this));
    mStopButton->setText("Stop");
}

void MainWindow::addChildWidgets()
{
    mWidgetLayout->setColumnStretch(0, 1);
    mWidgetLayout->setColumnStretch(1, 4);

    mWidgetLayout->setRowStretch(0, 1);
    mWidgetLayout->setRowStretch(1, 1);
    mWidgetLayout->setRowStretch(2, 1);
    mWidgetLayout->setRowStretch(3, 1);
    mWidgetLayout->setRowStretch(4, 1);
    mWidgetLayout->setRowStretch(5, 95);

    addWidgetToLayout(mURL.data(), 0, 0, 1, 1);
    addWidgetToLayout(mFoundText.data(), 1, 0, 1, 1);
    addWidgetToLayout(mMaxUrlNumber.data(), 2, 0, 1, 1);
    addWidgetToLayout(mMaxThreadNumber.data(), 3, 0, 1, 1);
    addWidgetToLayout(mURLStatusTable.data(), 0, 1, 6, 1);
    addWidgetToLayout(mStartResumeButton.data(), 4, 0, 1, 1, Qt::AlignLeft);
    addWidgetToLayout(mStopButton.data(), 4, 0, 1, 1, Qt::AlignRight);
}

void MainWindow::connectSignalSlot()
{
    connect(mStartResumeButton.data(), SIGNAL (clicked()), this, SLOT (pressedStartResumeButton()));
    connect(mStopButton.data(), SIGNAL (clicked()), this, SLOT (pressedStopButton()));
    connect(&_core, SIGNAL (workFinished()), this, SLOT (pressedStopButton()));
    connect(this, SIGNAL(processStarted(const ProcessData&)), &_core, SLOT(init(const ProcessData&)));
    connect(this, SIGNAL(processPaused()), &_core, SLOT(pause()), Qt::ConnectionType::DirectConnection);
    connect(this, SIGNAL(processResumed()), &_core, SLOT(resume()), Qt::ConnectionType::DirectConnection);
    connect(this, SIGNAL(procesStoped()), &_core, SLOT(stop()), Qt::ConnectionType::DirectConnection);
    connect(&_core, SIGNAL(processing(UrlInfo*)), this, SLOT(processUrl(UrlInfo*)));
}

void MainWindow::processUrl(UrlInfo* info)
{
    mURLStatusTable->insertItem(info);
}
