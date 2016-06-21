#include "processdata.h"

ProcessData::ProcessData()
    : mURL(QString())
    , mFindString(QString())
    , mNumThread(1)
    , mMaxNumURL(1)
{

}

ProcessData::~ProcessData()
{

}

void ProcessData::setURL(const QString& url)
{
    mURL = url;
}

void ProcessData::setFindString(const QString& string)
{
    mFindString = string;
}

void ProcessData::setNumThread(const int number)
{
    mNumThread = number;
}

void ProcessData::setMaxNumURL(const int number)
{
    mMaxNumURL = number;
}

const QString& ProcessData::getURL() const
{
    return mURL;
}

const QString& ProcessData::getFindString() const
{
    return mFindString;
}

int ProcessData::getNumThread() const
{
    return mNumThread;
}

int ProcessData::getMaxNumURL() const
{
    return mMaxNumURL;
}
