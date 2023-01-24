#ifndef DOWNLOAD_H
#define DOWNLOAD_H
#include <QWidget>
#include <QThread>
#include <QCoreApplication>
#include <QWidget>
#include <QVector>

class download : public QThread
{
    Q_OBJECT
public:
    download(){

    };
    void getfilename(QVector<QString> filename){
        filenames = filename;
    }
    QWidget* m_thread_creator;
    void download::run()
    {
        xiazai();
    }
signals:
    void updateProgress(double jindu);
private:
    void xiazai();
    void unzip(QString zippath,QString zipdir);

    QVector<QString> filenames;
};

#endif // DOWNLOAD_H
