#ifndef N2N_H
#define N2N_H

#include <QThread>
#include <adminauthorization.h>

class n2n : public QThread
{
    Q_OBJECT
public:
    n2n();
    void n2n::run(){
        QRunInfo::AdminAuthorization().execute(nullptr,lujing,canshu);
    }
private:
    QString lujing;
    QStringList canshu;
};

#endif // N2N_H
