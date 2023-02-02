#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsDropShadowEffect>
#include <cstring>
#include <QThread>
#include <QVector>

Widget *p =nullptr;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setProperty("canMove",true);
    this->initUi();
    this->initMember();
    //setWindowTitle("CSOL ADTeam服务器启动器");
    ui->update_progress->setValue(0);
    ui->update_progress->hide();
    gengxin = new QNetworkAccessManager();
    connect(gengxin,&QNetworkAccessManager::finished,this,&Widget::update_reply,Qt::DirectConnection);
    QNetworkAccessManager *gengxininfo = new QNetworkAccessManager();
    QUrl getVersionurl("http://api.adteam.asia/csol/update.php");
    gengxininfo->get(QNetworkRequest(getVersionurl));
    ui->label_4->hide();
    /*bool admin = QRunInfo::AdminAuthorization().hasAdminRights();
    if(admin == false){
        myMbox->setIcon("error");
        myMbox->setBodyText(u8"错误：请使用管理员权限启动本程序");
        myMbox->setButtonText(u8"确定");
        myMbox->exec();
        delete this;
    }*/

    connect(gengxininfo,&QNetworkAccessManager::finished,this,([=](QNetworkReply *reply){
        int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(); //获取网络状态码
        //如果reply有错误或者状态码不是200（http 200是正常的，这是硬性要求），输出服务器错误
        //否则用二进制值提取报文内容，送到parsejson，是json处理函数，并显示
        if(reply->error() != QNetworkReply::NoError || status_code != 200){
            myMbox->setIcon("error");
            myMbox->setBodyText(u8"错误：连接到更新服务器网络错误");
            myMbox->setButtonText(u8"确定");
            myMbox->exec();
        }else{
            QByteArray bytearray;
            bytearray = reply->readAll();
            QJsonParseError *error = new QJsonParseError;

            QByteArray fanhui = bytearray;
            QJsonDocument netversion = QJsonDocument::fromJson(fanhui, error);
            qDebug() << fanhui;
            QJsonObject netv = netversion.object();
            ui->updateinfo->setText(netv.value("description").toString());

        }
        reply->deleteLater();
    }));
    qDebug() << "ok";
}

Widget::~Widget()
{
    delete ui;
}

/**********************************************************初始化函数****************************************************************/

void Widget::initUi()
{
    //初始化窗口边框
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor("#444444"));
    shadow->setBlurRadius(16);
    ui->w_bg->setGraphicsEffect(shadow);
    ui->lay_bg->setMargin(12);

    //Logo
    QPixmap logo(":/icons/logo.png");
    ui->lab_logo->setPixmap(logo);

    //itemLogo
    QPixmap item1(":/icons/item_01.png");
    QPixmap item2(":/icons/item_02.png");
    ui->lab_item_01->setPixmap(item1);
    ui->lab_item_02->setPixmap(item2);
}

void Widget::initMember()
{
    this->myMbox = new MyMessageBox();
    connect(myMbox,SIGNAL(btnchicked(int)),this,SLOT(changeMboxReturn(int)));

    //最小化到托盘
    QIcon icon = QIcon(":/icons/logo.png");//设置最小图标
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("Peach"); //提示文字
    //添加托盘列表项(还原与退出)
    returnNormal = new QAction(" Show", this);
    returnNormal->setFont(QFont("Arial", 9));
    returnNormal->setObjectName("returnNormal");
    returnNormal->setIcon(QIcon(":/icons/show.png"));
    quitAction = new QAction(" Quit", this);
    quitAction->setFont(QFont("Arial", 9));
    quitAction->setObjectName("quitAction");
    quitAction->setIcon(QIcon(":/icons/out.png"));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));           //绑定槽函数退出
    connect(returnNormal, SIGNAL(triggered()), this, SLOT(showNormal()));   //绑定槽函数还原界面

    //创建托盘菜单(必须先创建动作，后添加菜单项，还可以加入菜单项图标美化)
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(returnNormal);
    trayIconMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayIconMenu);
}

/**********************************************************自定义函数****************************************************************/

void Widget::littleShow()
{
    this->hide();//隐藏主窗口
    trayIcon->show();//显示托盘

    //显示到系统提示框的信息
    QString title=u8"CSOL ADTeam启动器";
    QString text=u8"正在后台运行";
    trayIcon->showMessage(title,text,QSystemTrayIcon::Information,3000); //此参数为提示时长
}

/**********************************************************控件槽函数****************************************************************/

void Widget::closeEvent(QCloseEvent *event)
{
    myMbox->setIcon("question");
    myMbox->setBodyText(u8"是否退出?");
    myMbox->setButtonText(u8"后台挂起",u8"退出");
    myMbox->exec();
    if(mbox_return == 0) {
        event->ignore();
    }else if(mbox_return == 1){
        event->ignore();
        littleShow();
    }
}

void Widget::changeMboxReturn(int num)
{
    this->mbox_return = num;
}

void Widget::on_btn_main_item_1_clicked()
{
    ui->sw_main->setCurrentIndex(0);
}

void Widget::on_btn_main_item_2_clicked()
{
    ui->sw_main->setCurrentIndex(1);
}

void Widget::on_btn_main_item_3_clicked()
{
    ui->sw_main->setCurrentIndex(2);
}

void Widget::on_btn_main_item_4_clicked()
{
    ui->sw_main->setCurrentIndex(3);
}

void Widget::on_btn_logout_clicked()
{
    close();
}

void Widget::on_btn_littleshow_clicked()
{
    showMinimized();
}

void Widget::update_reply(QNetworkReply *reply){
    int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(); //获取网络状态码
    //如果reply有错误或者状态码不是200（http 200是正常的，这是硬性要求），输出服务器错误
    //否则用二进制值提取报文内容，送到parsejson，是json处理函数，并显示
    if(reply->error() != QNetworkReply::NoError || status_code != 200){
        myMbox->setIcon("error");
        myMbox->setBodyText(u8"错误：连接到更新服务器网络错误");
        myMbox->setButtonText(u8"确定");
        myMbox->exec();
    }else{
        QByteArray bytearray;
        bytearray = reply->readAll();
        update(bytearray);//传入报文内容处理
        //qDebug() << bytearray;
    }
    reply->deleteLater();
}

void Widget::updateProgress(double jindu)
{
    ui->update_progress->setValue(jindu);
    if(jindu == 100){
        ui->label_4->setText(u8"下载完成，正在安装，将在安装完成后自动启动游戏。");
    }
}//更新进度条更新

void Widget::update(QByteArray &bytearray){
    QJsonParseError *error = new QJsonParseError;
    QByteArray fanhui = bytearray;
    QJsonDocument netversion = QJsonDocument::fromJson(fanhui, error);
    qDebug() << fanhui;
    if(error->error != QJsonParseError::NoError){
        myMbox->setIcon("error");
        myMbox->setBodyText(u8"错误：服务器版本号无法读取，请联系air");
        myMbox->setButtonText(u8"确定");
        myMbox->exec();
        return;
    }
    QJsonObject netv = netversion.object();
    qDebug() << netv;
    if(netv.value("update").toString() == "true"){
        myMbox->setIcon("error");
        myMbox->setBodyText(u8"错误：服务器正在更新中，请在更新完成后再进入游戏");
        myMbox->setButtonText(u8"确定");
        myMbox->exec();
        return;
    }
    if(netv.value("version").toString() != local_version){//如果版本不一致
        QJsonArray filenames = netv.value("filelist").toArray();
        QVector<QString> filename;
        for(auto i = filenames.begin() ; i !=filenames.end() ;i++){
            filename.append(i->toString());
        }
        ui->label_4->show();
        ui->update_progress->show();//展示进度条
        //下载与解压缩子线程
        connect(&my_thread, &download::updateProgress, this, &Widget::updateProgress);
        connect(this, &Widget::filenamelist, &my_thread, &download::getfilename);
        filenamelist(filename, &my_thread);
        my_thread.start();
    }else{
        myMbox->setIcon("warn");
        myMbox->setBodyText(u8"游戏正在启动中，如果出现权限窗口请点击确定");
        myMbox->setButtonText(u8"我知道了");
        myMbox->exec();
        n2n p;
        p.run();
        QString command = "cd " + QCoreApplication::applicationDirPath() + "/Bin && start CSOLauncher_Exe.exe --ip 10.200.173.1";
        QByteArray kaishi = command.toLatin1();
        qDebug() << kaishi.data();
        system(kaishi.data());
    }
}

void Widget::on_startgame_clicked()
{
    qDebug() << "ok";
    QFile versionFile(QApplication::applicationDirPath()+"/version.json");
    if(!versionFile.open(QIODevice::ReadOnly)){
        myMbox->setIcon("error");
        myMbox->setBodyText(u8"错误：版本号文件不存在，请联系air");
        myMbox->setButtonText(u8"确定");
        myMbox->exec();
        return;
    }
    QJsonParseError *error = new QJsonParseError;
    QJsonDocument jdc = QJsonDocument::fromJson(versionFile.readAll(),error);
    versionFile.close();
    if(error->error != QJsonParseError::NoError){
        myMbox->setIcon("error");
        myMbox->setBodyText(u8"错误：目前版本号无法读取，请联系air");
        myMbox->setButtonText(u8"确定");
        myMbox->exec();
        return;
    }

    QJsonObject obj = jdc.object();
    local_version = obj.value("version").toString();
    qDebug() << local_version;

    QUrl getVersionurl("http://api.adteam.asia/csol/update.php");
    gengxin->get(QNetworkRequest(getVersionurl));
}
