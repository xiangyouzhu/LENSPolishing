#ifndef MYTHREAD_H
#define MYTHREAD_H
#include<QThread>
//#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QThread"
#include"PmacAPI.h"
#include"produce_gcode.h"

class MyThread : public QThread
{
    Q_OBJECT//信号与曹要用的宏定义
public:
         MyThread(QObject * parent);
    void thread_init(Ui::MainWindow *ui_ptr);

    QObject *timerReceiver;
    PmacApi *myPmac;
    bool pbsuccess;
protected:

    void run();//线程函数
private slots:
    void onTimeout();

};


class Interfer_check_thread:public QThread
{
    Q_OBJECT//信号与曹要用的宏定义
public:
    Interfer_check_thread(QObject * parent);
protected:
    void run();//线程函数


};

class Process_time_count:public QThread
{
    Q_OBJECT//信号与曹要用的宏定义
public:
    Process_time_count(QObject * parent,double Processtime);
protected:
    void run();//线程函数
signals:
        void count_Signal(int);
private:
        int count;
        int ProcessTime;

};

#endif // MYTHREAD_H
