#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
class MyThread : public QThread
{
public:
    MyThread(QWidget* creator, QObject* parent) : QThread(parent){
        m_thread_creator = creator;
    };
    void MyThread::startWork(double now,double total)
    {
        emit progress(now/total);
    }
    void MyThread::run(double now,double total)
    {
        startWork(now,total);
    }
signals:
    void progress(double jindu);
private:
    QWidget* m_thread_creator;
};

#endif // MYTHREAD_H
