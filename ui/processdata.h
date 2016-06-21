#ifndef PROCCESSDATA_H
#define PROCCESSDATA_H

#include <QString>

class ProcessData
{
public:
    ProcessData();

    virtual ~ProcessData();

    void setURL(const QString& url);
    void setFindString(const QString& string);
    void setNumThread(const int number);
    void setMaxNumURL(const int number);

    const QString& getURL() const;
    const QString& getFindString() const;
    int getNumThread() const;
    int getMaxNumURL() const;

private:
    QString mURL;
    QString mFindString;
    int mNumThread;
    int mMaxNumURL;
};

#endif // PROCCESSDATA_H
