#ifndef PROGRESS_H
#define PROGRESS_H
#include <QThread>
#include <QDebug>


class progress : public QThread
{
Q_OBJECT
public:
    explicit progress(QObject *parent = 0): QThread(parent)
    {

        qDebug() << "Worker Thread : " << QThread::currentThreadId();
    }

protected:
    virtual void run() Q_DECL_OVERRIDE
    {

        qDebug() << "Worker Run Thread : " << QThread::currentThreadId();

        int nValue = 0;

        while (nValue < 100)

        {

            // 休眠50毫秒

            msleep(50);

            ++nValue;


            // 准备更新

            emit resultReady(nValue);

        }

    }

signals:

    void resultReady(int value);
};

#endif // PROGRESS_H
