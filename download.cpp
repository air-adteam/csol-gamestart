#include "download.h"
#include <cstring>
#include <alibabacloud/oss/OssClient.h>
#include <QDebug>
#include <QString>
#include <QtGui/private/qzipreader_p.h>
#include <QDir>
#include "JlCompress.h"
using namespace AlibabaCloud::OSS;

download *p = nullptr;

void ProgressCallback(size_t increment, int64_t transfered, int64_t total, void* userData)
{
    std::cout<<(double)transfered/(double)total<<std::endl;
    emit p->updateProgress((double)transfered/(double)total * 100.00); //发送该地址信号
}


void download::xiazai(){
    //阿里云OSS配置
    std::string AccessKeyId = "";
    std::string AccessKeySecret = "";
    std::string Endpoint = "http://oss-cn-beijing.aliyuncs.com";
    std::string BucketName = "csol-adteam";
    std::string ObjectName = "update.zip";
    QString lujing = QCoreApplication::applicationDirPath();
    lujing.replace("/","\\");
    std::string DownloadFilePath = lujing.toStdString() + "\\update.zip";
    std::string CheckpointFilePath = lujing.toStdString() + "\\update.zip.dcp";
    std::cout << CheckpointFilePath << std::endl;
    //初始化网络
    InitializeSdk();
    ClientConfiguration conf;
    OssClient client(Endpoint, AccessKeyId, AccessKeySecret, conf);

    //断点续传下载 + 下载进度获取
    DownloadObjectRequest request(BucketName,  ObjectName, DownloadFilePath);
    TransferProgress progressCallback = { ProgressCallback , nullptr };
    request.setTransferProgress(progressCallback);

    p = this;

    auto outcome = client.ResumableDownloadObject(request);

    if (!outcome.isSuccess()) {
            /*异常处理。*/
            std::cout << "ResumableDownloadObject fail" <<
            ",code:" << outcome.error().Code() <<
            ",message:" << outcome.error().Message() <<
            ",requestId:" << outcome.error().RequestId() << std::endl;
            ShutdownSdk();
     }else{
        qDebug() <<"ok";
        unzip("update.zip",lujing);
    }
}

void download::unzip(QString zippath,QString zipdir){
    for(auto i = filenames.begin();i != filenames.end();i++){
        QFile filedelete(zipdir +"\\"+ i);
        filedelete.remove();
        filedelete.close();
    }//事先删除更新前的文件
    QFile filedelete(zipdir +"\\version.json");
    filedelete.remove();//删除版本文件
    filedelete.close();
    QDir tempdir;
    if(!tempdir.exists(zipdir)){
        tempdir.mkpath(zipdir);
    }
    JlCompress::extractDir(zipdir + "\\" +zippath,zipdir);//解压更新包
    QFile zipdelete(zipdir +"\\"+ zippath);
    zipdelete.remove();
    QString command = "cd " + QCoreApplication::applicationDirPath() + "/Bin && start CSOLauncher_Exe.exe --ip 10.200.173.1";
    QByteArray kaishi = command.toLatin1();
    qDebug() << kaishi.data();
    system(kaishi.data());
}
