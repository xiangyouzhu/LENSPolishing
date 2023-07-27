#ifndef READFILE_H
#define READFILE_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
//#include <QSerialPort>
//#include <QSerialPortInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTime>
#include <QTimer>
#include <QProcess>
#include <QDir>
/*********************************************************************
 * 函数功能：界面初始化
 * 参 数：  无
 * 返回值： 无
 * 备  注： 无
 *********************************************************************/
void fun_init(Ui::MainWindow *ui_ptr);//
void readSystemValue();
void Init_Timer();
void init_motion_control_gui();
bool checkOnly();//重复运行程序查询
#endif // READFILE_H


