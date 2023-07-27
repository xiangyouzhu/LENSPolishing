#-------------------------------------------------
#
# Project created by QtCreator 2021-03-27T22:28:19
#
#-------------------------------------------------

QT       += core gui
RC_ICONS += logo1.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = APEC-100
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

CONFIG += c++11

CONFIG += exceptions#开启异常

#INCLUDEPATH = ../LensPolishing/include_cpp
#LIBS += ../LensPolishing/libxl.lib

SOURCES += \
        PmacApi.cpp \
        dialogserail.cpp \
        form.cpp \
        hzaxle.cpp \
        init_fun.cpp \
        main.cpp \
        mainwindow.cpp \
        mythread.cpp \
        pcommserverlib.cpp \
        produce_gcode.cpp \
        qcustomplot.cpp \
        readwritefile.cpp

HEADERS += \
        PmacAPI.h \
        dialogserail.h \
        form.h \
        hzaxle.h \
        init_fun.h \
        mainwindow.h \
        mythread.h \
        pcommserverlib.h \
        produce_gcode.h \
        qcustomplot.h \
        readwritefile.h

FORMS += \
        dialogserail.ui \
        form.ui \
        mainwindow.ui

#引用Pmac通讯库
#CONFIG +=qaxcontainer
CONFIG +=axcontainer
#QT +=qaxcontainer
QT +=axcontainer

QT += widgets printsupport #打印相关
QT       += serialport
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    Image/Question.jpg \
    Image/Question.png \
    Image/concave.jpg \
    Image/document.jpeg \
    Image/qusetion.png \
    Image/raised.jpg \
    Image/warning.png \
    Image/wenhao.png


