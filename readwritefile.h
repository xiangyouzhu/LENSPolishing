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
#include "excelbase.h"
/*********************************************************************
 * 函数功能：界面初始化
 * 参 数：  无
 * 返回值： 无
 * 备  注： 无
 *********************************************************************/
void ui_init(Ui::MainWindow *ui_ptr);
void readHomeValue();
void readFileToshapeGUi();
void readFileToprocessGUi();
void system_value();
void Init_customplot1(QCustomPlot *w);
void Init_customplot2(QCustomPlot *w);
void Init_UiCustomPlot();
void drawPlot(double A[]);//画图
void drawPlot_errdata(QVector<double>X,QVector<double>Y);//画面型误差数据图
static QScopedPointer<ExcelBase> m_xls;
 static QList< QList<QVariant> > m_datas;
#endif // READFILE_H
