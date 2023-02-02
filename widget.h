#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//最小化相关
#include <QSystemTrayIcon>
#include <adminauthorization.h>
#include <QCloseEvent>
#include <QMenu>
#include <QAction>
#include <QVector>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
//自定义弹窗
#include "mymessagebox.h"
#include "download.h"
#include "n2n.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void closeEvent(QCloseEvent *event);

    void changeMboxReturn(int num);

    void on_btn_main_item_1_clicked();

    void on_btn_main_item_2_clicked();

    void on_btn_main_item_3_clicked();

    void on_btn_main_item_4_clicked();

    void on_btn_logout_clicked();

    void on_btn_littleshow_clicked();

    void on_startgame_clicked();

    void filenamelist(QVector<QString> filename,download *p){
        emit p->getfilename(filename);
    }


private:
    Ui::Widget *ui;

    MyMessageBox *myMbox;
    //自定义窗口通信参数
    int mbox_return;

    //最小化到托盘
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    //窗口管理动作
    QAction *returnNormal;
    QAction *quitAction;

    void initUi();          //Ui界面初始化函数
    void initMember();      //成员变量初始化函数
    void littleShow();      //最小化显示函数


    download my_thread;
    QNetworkAccessManager *gengxin;
    void update_reply(QNetworkReply *reply);
    void update(QByteArray &bytearray);
    QString local_version;

    void updateProgress(double jindu);

};

#endif // WIDGET_H
