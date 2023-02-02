#-------------------------------------------------
#
# Project created by QtCreator 2020-09-02T22:09:28
#
#-------------------------------------------------

QT       += core gui network gui-private

INCLUDEPATH += D:/QT/aliyun-oss-cpp-sdk-master/sdk/include \
               D:/QT/aliyun-oss-cpp-sdk-master/sdk/src \
               D:/QT/aliyun-oss-cpp-sdk-master/third_party/include

LIBS += -LD:/QT/aliyun-oss-cpp-sdk-master/third_party/lib/x64/ -llibcurl
LIBS += -LD:/QT/aliyun-oss-cpp-sdk-master/third_party/lib/x64/ -llibeay32
LIBS += -LD:/QT/aliyun-oss-cpp-sdk-master/third_party/lib/x64/ -lssleay32
LIBS += -LD:/QT/aliyun-oss-cpp-sdk-master/build/lib/Release -lalibabacloud-oss-cpp-sdk

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_ICONS = logo.ico

TARGET = PeachDemo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    download.cpp \
        main.cpp \
    n2n.cpp \
        widget.cpp \
    appinit.cpp \
    mymessagebox.cpp

HEADERS += \
    appinit.h \
    download.h \
    mymessagebox.h \
    n2n.h \
    widget.h

FORMS += \
        widget.ui \
    mymessagebox.ui

RESOURCES += \
    qss.qrc

win32:CONFIG(release, debug|release): LIBS += -LC:/Qt/quazip/lib/ -lquazip
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/Qt/quazip/lib/ -lquazipd
else:unix: LIBS += -LC:/Qt/quazip/lib/ -lquazip

INCLUDEPATH += C:/Qt/quazip/include
DEPENDPATH += C:/Qt/quazip/include

win32:CONFIG(release, debug|release): LIBS += -LC:/Qt/qruninfo/lib/ -lQRunInfo
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/Qt/qruninfo/lib/ -lQRunInfod
else:unix: LIBS += -LC:/Qt/qruninfo/lib/ -lQRunInfo

INCLUDEPATH += C:/Qt/qruninfo/include
DEPENDPATH += C:/Qt/qruninfo/include
