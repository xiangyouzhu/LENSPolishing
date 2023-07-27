#include "dialogserail.h"
#include "ui_dialogserail.h"
#include "mainwindow.h"
//QSerialPort *MainWindow::serial;
DialogSerail::DialogSerail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSerail)
{
    ui->setupUi(this);
    QStringList portNameList;
    ui->portbox->clear();                                        //关闭串口号
    ui->portbox->addItem("刷新");                                //添加刷新
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()) //添加新串口
    {
        portNameList.append(info.portName());
    }

    ui->portbox->addItems(portNameList);
    ui->portbox->setCurrentIndex(9);                             // 当前串口号为COM1
   MainWindow::serial->setPortName(ui->portbox->currentText());

}

DialogSerail::~DialogSerail()
{
    delete ui;
}

void DialogSerail::on_openport_clicked()
{


              //设置串口号
    if(MainWindow::serial->isOpen())                                        // 如果串口打开了，先给他关闭
    {
      //  MainWindow::serial->clear();
       // MainWindow::serial->close();
        ui->openport->setText("连接成功");
        ui->openport->setStyleSheet("color: green");
       // ui->portbox->setDisabled(0);

        ui->openport->setStyleSheet("color: green;");
    }
    else                                                        // 如果串口关闭了，先给他打开
    {
        //当前选择的串口名字
        MainWindow::serial->setPortName(ui->portbox->currentText());
        //用ReadWrite 的模式尝试打开串口，无法收发数据时，发出警告
        if(!MainWindow::serial->open(QIODevice::ReadWrite))
        {
           // ui->statusBar->showMessage("串口打开失败",2000);
            return;
         }
        // 打开状态，按钮显示“关闭串口”
        ui->openport->setText("连接成功");
        // 打开状态，禁止用户操作
       // ui->portbox->setDisabled(1);
        //ui->startbutton->setDisabled(0);
        //ui->stopbutton->setDisabled(0);
       // ui->searcherr->setDisabled(0);
        ui->openport->setStyleSheet("color: green;");
        // 打开，显示灯为绿色

    }

}

void DialogSerail::on_openport_2_clicked()
{
    this->close();
}
