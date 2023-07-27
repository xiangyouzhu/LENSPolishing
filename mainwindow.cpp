#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pcommserverlib.h"
#include "qt_windows.h"
#include "QMessageBox"
#include"QtDebug"
#include"QTextCodec"
#include "QCloseEvent"
#include "QDesktopServices"
#include"produce_gcode.h" 
#include"QVector2D"
#include <QDesktopWidget>
#include "QString"
#include"QFile"
#include <QFileDialog>
#include <QAxObject>
#include <QVariant>
#include <QList>
//#include "libxl.h"
//#include "QVariantListListModel.h"
#include "qvariantlistlistmodel.h"
#include <QElapsedTimer>
#include <exception>

#include"readwritefile.h"
#include "qcustomplot.h"
#include "init_fun.h"
#include <QThread>
#include"mythread.h"
#include "form.h"
#include "hzaxle.h"
#include "dialogserial.h"

//#pragma comment(lib, "libxl.lib")
using namespace PCOMMSERVERLib;//
using namespace ui;
extern void  readSystemValue();
extern void fun_init(Ui::MainWindow *ui_ptr);//外部初始化函数
extern void thread_init(Ui::MainWindow *ui_ptr);//外部初始化函数
void init_motion_control_gui();//外部初始化函数
bool checkOnly();//外部初始化函数，检查程序是否重复启动
//extern void
//using namespace libxl;
//using namespace Ui;
// static double first_position_feed;
// static double C_motor_scale_factor, C_motor_offset, Lworkpiece_h, other_h;
// static bool Vc_flag, F_flag;
 double MainWindow::A[20]={};//面型公式参数A
 double MainWindow::parameter_shape[10]={};//定义初始化
 double MainWindow::parameter_process[20]={};//加工参数定义
 bool MainWindow::selectPmacSuccess ;
 bool MainWindow::openPmacSuccess;
 int MainWindow::pmacNumber;
// double MainWindow::parameter_shape[10];
// double MainWindow::A[20];//非球面公式参数
//     double MainWindow:: parameter_process[20] ;
   QVector<double> MainWindow::x, MainWindow::zd;//面型补正数据
//       double  ** MainWindow::NC_Data;//生成代码数据
    QVector<double> MainWindow::F1;//补偿后的F
       double MainWindow:: x_devia_value, MainWindow:: b_devia_value,MainWindow:: z_devia_value,MainWindow:: y_devia_value;//定义轴的偏移量,单位脉冲
       double MainWindow:: x_devia_ADDvalue, MainWindow:: b_devia_ADDvalue, MainWindow:: z_devia_ADDvalue;//定义轴的偏移量改变值,单位脉冲
       bool MainWindow:: MainWindow:: draw_flag;//画过一次后标志
      bool MainWindow:: set_flag,MainWindow::set_proces_flag;//设置过一次参数后标志
      bool MainWindow:: own_code_flag, MainWindow::compensate_code_flag, MainWindow::other_code_flag;//判断下载了什么代码
       double MainWindow:: process_time;//加工时间
      bool MainWindow:: download_code_flag;//下载代码进控制器标志
    int MainWindow:: hour, MainWindow::min, MainWindow::Sec, MainWindow::h, MainWindow::m, MainWindow::s;
       double MainWindow:: compens_cycle_time;//补偿加工次数
      bool MainWindow:: process_fininsh_flag, MainWindow::process_begin_flag,MainWindow:: Z_motor_status,MainWindow:: C_motor_status, MainWindow::X_motor_status, MainWindow::B_motor_status;
       bool MainWindow:: Vc_flag,MainWindow::F_flag;//确定是否是恒转速和恒进给速度
      bool MainWindow:: connect_flag;//连接控制器标志
      bool MainWindow:: Pcode_return_flag;//进入生成代码界面标志
      bool MainWindow:: handle_model_flag   ;//进入手动界面标志
      bool MainWindow:: read_data_flag   ;//读取面型数据标志
      bool MainWindow:: compensate_flag     ;//进行面型补正后的
      bool MainWindow:: process_flag     ;//进入加工模式一次标志
      bool MainWindow:: multi_process_flag     ;//进入多段程序设定界面一次标志
      bool MainWindow:: multi_process_flag2     ;//从自己代码设定进入多段程序设定界面一次标志
      bool MainWindow:: X_ALARM_flag     ;//X轴警报标志
      bool MainWindow:: B_ALARM_flag     ;//B轴警报标志
      bool MainWindow:: Z_ALARM_flag     ;//Z轴警报标志
      bool MainWindow:: C_ALARM_flag     ;//C轴警报标志
      bool MainWindow:: Alarm_clear_flag     ;//异常清除按钮清除标志
//      Form1 frmForm1;
// private PmacApi Pmac = new PmacApi(pmacNumber);
// private   SerialPort comm = new SerialPort();//建立串口通讯，模拟量输出板控制抛光轴转动
      bool MainWindow:: buzzer_work;//蜂鸣器响
     int MainWindow:: buzzer_worktime;//蜂鸣器响的次数
      bool MainWindow:: resetC_work;//C轴清楚警报
     int MainWindow:: resetC_worktime;//发生警报清楚电平次数
    double MainWindow::Lworkpiece_h=0;//为L型件底面到中心孔高度
       double MainWindow:: other_h;//L型件底面到夹具底面高度
       double MainWindow:: C_motor_scale_factor;//C轴电压转速比例因子
       double MainWindow:: C_motor_offset;//C轴电压转速比例一次变换偏差
        double MainWindow:: U_motor_scale_factor;//抛光轴电压转速比例因子
       double MainWindow:: U_motor_offset;//抛光轴电压转速比例一次变换偏差
       double MainWindow:: zfeed;//多段抛光Z轴上升和下降速度
       double MainWindow:: xBfeed;//多段抛光XB轴速度
       double MainWindow:: xlimit_left;//X轴极限位置，左右对称
       double MainWindow:: xlimit_right;//X轴极限位置，左右对称
       double MainWindow:: ylimit_forward;//y轴极限位置，左右对称
       double MainWindow:: ylimit_bakcward;//y轴极限位置，左右对称
       double MainWindow:: blimit_left;//b轴极限位置，左右对称

       double MainWindow:: blimit_right;//b轴极限位置，左右对称
       double MainWindow:: zlimit_up;//Z轴上极限位置
       double MainWindow:: zlimit_down;//Z轴上极限位置
       double MainWindow:: min_z;//数控代码Z的最小值
       double MainWindow:: polish_axi_maxfeed;//抛光轴最大速度
       double MainWindow:: polish_axi_minfeed;//抛光轴最小速度
       double MainWindow:: x_axi_hand_maxfeed;//X轴手动最大速度
              double MainWindow:: y_axi_hand_maxfeed;//X轴手动最大速度
       double MainWindow:: b_axi_hand_maxfeed;//b轴手动最大速度
       double MainWindow:: z_axi_hand_maxfeed;//z轴手动最大速度
       double MainWindow:: C_axi_maxfeed;//C轴最大速度
       double MainWindow:: C_axi_minspeed;//C轴最小速度
       double MainWindow:: C_Button_speed;//C轴最小速度
       double MainWindow:: caculate_time_offset;//计算时间补正系数，单位/min
       double MainWindow:: first_position_feed;//单段抛X B 到初始位进给速度（mm/min）
       double MainWindow:: first_polish_zfeed;//抛光z到初始位速度
       double MainWindow:: x_software_limit_left;//x左软限位
       double MainWindow:: x_software_limit_right;//x右软限位
       double MainWindow:: b_software_limit_left;//b左软限位
       double MainWindow:: b_software_limit_right;//b右软限位
       double MainWindow:: z_software_limit_up;//z上软限位
       double MainWindow:: z_software_limit_down;//z下软限位
       double MainWindow:: z_axi_first_jogdownfeed;////抛光Z轴下降手动速度；
       double MainWindow:: B_axi_Center_Polish_head_distance;//在零位时，B轴回转中心到抛光头触碰到第二个限位的距离；
       bool MainWindow::interfere_flag;//干涉检查结果标志
       bool MainWindow::produce_ncCode_flag;//生成非补正代码标志
        bool MainWindow::produce_ncCode_flag2;//生成补正代码标志
        double MainWindow::Cloth_thickness;//抛光垫的厚度
        double MainWindow::Cloth_minthickness;
        int MainWindow::last_index;//工件坐标计数
        double MainWindow::max_x;//最大数控代码X坐标
        double MainWindow::max_b;//最大数控代码X坐标
        double MainWindow::max_z;//最大数控代码X坐标

        bool MainWindow::tip1;//安全提示标志
        bool MainWindow::tip2;
        bool MainWindow::tip3;
        bool MainWindow::tip4;
        bool MainWindow::tip5;
        bool MainWindow::tip6;
        bool MainWindow::tip7;
        bool MainWindow::tip8;
        bool MainWindow::tip9;
        bool MainWindow::tip10;
        bool MainWindow::tip11;
        bool MainWindow::tip12;

        bool MainWindow::door_open;


        QVector<QVector<double>> MainWindow::Nc_Data;//NC代码
        QVector<QVector<double>> MainWindow::Nc_Check;//NC代码检查代码
        QVector<double> MainWindow::external_rate;//外部倍率
        QVector<QString> MainWindow::Nc_x;//X位置代码
       PmacApi *MainWindow::PMAC;//
       QSerialPort *MainWindow::serial;
       //serialForm
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    if(!checkOnly())
    {
        QMessageBox::information(this,"提示！","程序已经启动运行");

        exit(0);

    }

   //  parameter_shape[]=0;
    //parameter_shape[0];
    ui->setupUi(this);
//设置中文字符

    ui_init(ui);//传递参数给readfile，实现界面操作
    fun_init(ui);
    thread_init(ui);
   //QTextCodec::setCodecForCStrings(QTextCodec::codeForName("GB2312"));
   // QTextCodec::setCodecForLocale(QTextCodec::codeForName("GB2312"));
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);

     connect_Pmac();//连接Pmac
/****//***********加载系统参数*****************************************/
     readSystemValue();//读系统参数
     Init_Pmac();//初始化pmac
     Init_hzaxi();//初始化昊志抛光轴

     if(int (PMAC->GetP(34))==0&&connect_flag==true)
     {
         QIcon icon= windowIcon();
         QMessageBox megBox;
         megBox.setIcon(QMessageBox::Question);
         megBox.setWindowIcon(icon);
         megBox.setWindowTitle("提示");
         megBox.addButton("是",QMessageBox::AcceptRole);
         megBox.addButton("否",QMessageBox::RejectRole);
         megBox.setText("是否进行复位？");
         int result= megBox.exec();
         if (result==QMessageBox::AcceptRole)
         {
             Axi_Home();//各个轴回零操作
         }

     }






  /************************************************************/


                  //  Init_shapeGUi();//形状参数界面初始化
                    readFileToshapeGUi();//形状参数界面初始化
                    readFileToprocessGUi();//加工参数界面初始化
                    init_motion_control_gui();//运动控制界面初速化
                     Init_customplot2(ui->customPlot_2);//画图控件初始化
                         Init_customplot1(ui->customPlot);//画图控件初始化
                        Init_Timer();//初始化读位置计时器



          //
                  //     monitroe_value = new MyThread(this); //定义线程
                    //   monitroe_value->start();

           // read_position=new QTimer(0);//定义计数器
          //  read_position->setInterval(100);//设定间隔
         //   read_position->moveToThread(monitroe_value);//分配到线程执行
          //  connect(read_position, SIGNAL(timeout()), this, SLOT(onTimeout()), Qt::DirectConnection);
         //   connect(monitroe_value, SIGNAL(started()), read_position,SLOT(start()));
//connect(ui->customPlot->yAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(setyAxisRange(QCPRange)));

//    ui->statusBar->setSizeGripEnabled(false);//去掉状态栏右下角的三角

//       ui->statusBar->showMessage(tr("临时信息!"),2000);//显示临时信息2000ms 前面的正常信息被覆盖 当去掉后一项时，会一直显示

//       QLabel *permanent=new QLabel(this);
//       permanent->setFrameStyle(QFrame::Box|QFrame::Sunken);
//     //  permanent->setText(tr("<a href=\"http://tengweitw.ueuo.com\">永久信息</a>"));
//       permanent->setText(tr("帮助按F1"));
//    //   permanent->setOpenExternalLinks(true);//设置能够打开网站连接
//       ui->statusBar->addPermanentWidget(permanent);//显示永久信息

                       // setPalette(QPalette(Qt::blue));//设置背景颜色
                         //   setAutoFillBackground(true);

   m_pDeskdop = QApplication::desktop();//设置启动程序居中
     move((m_pDeskdop->width() - this->width())/2, (m_pDeskdop->height() - this->height())/2);
ui->comboBox_8->setCurrentIndex(0);
if(ui->comboBox_8->currentIndex()==0)
    PMAC->SetP(4,1);
else
    PMAC->SetP(4,0);
//this->setWindowFlag(Qt::WindowMaximizeButtonHint,true);
  //   this->setWindowState(Qt::WindowMaximized);
//QAction *actionlianjie = new QAction(this);
// actionlianjie->setObjectName(QString::fromUtf8("actionlianji"));
// QIcon icon8;
// icon8.addFile(QString::fromUtf8(":/Image/port.jpeg"), QSize(), QIcon::Normal, QIcon::Off);
// actionlianjie->setIcon(icon8);
// ui->menu_H->addAction(actionlianjie);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Init_Timer()//初始化计时器函数,读位置
{
    //读位置计时器
       read_position=new QTimer(this);
       read_position->setInterval(100);
       connect(read_position, SIGNAL(timeout()), this, SLOT(read_pos()));
       read_position->start();
}
void MainWindow::connect_Pmac()//连接控制器,初始化参数
{
   // read_position->stop();
    bool pbsuccess=false;//连接pmac成功否
//= new PmacApi();
    PMAC=new PmacApi(0);
  //  PMAC->Open(0,pbsuccess);
//read
    Pmac=new PmacDevice();//实例化通信对象
   Pmac->Open(0,pbsuccess);//连接控制器0
    if(pbsuccess)
    {
        QMessageBox::information(this, "提示", "连接控制器成功！");
        PMAC->SendCommand("P33=1");//连接成功标志
        PMAC->SendCommand("ENABLE PLC1");
        //QMessageBox::information(this, "提示", "连接成功！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        connect_flag=true;

    }
    else
    {
       // QMessageBox::information(this, "提示", "连接失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
      QMessageBox::information(this, "提示", "连接控制器失败！");
       //  QMessageBox::information(this,"提示","连接失败！",QMessageBox::Ok,QMessageBox::Yes);

    }


}
void MainWindow::Init_Pmac()//初始化Pmac配置参数
{
    /*************设置回零偏置**************/
    QString str;//参数文件字符
    QString strPath=QCoreApplication::applicationDirPath();//获取程序当前路径
   // QDir dir(strPath);//实例化文件路径类
    QFile *file=new QFile();//实例化文件读取对象
    QStringList list;
    QDir dir(strPath);//创建路径类
    QString filepath=dir.path()+"\\home_value.txt";
    if(filepath.isEmpty())//取消读取
        return;
    file->setFileName(filepath);//目标文件
    if(filepath.isEmpty())//取消读取
        return;
    file->setFileName(filepath);//目标文件

    if(!file->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::information(NULL,"提示！","读取原点参数失败！");
      // QMessageBox()
        return;

    }

    while (!file->atEnd())
    {
        str=file->readLine();
        str=str.remove("\n");
        list.append(str);

    }
    file->close();
    double x=list.at(0).split(":").at(1).toDouble();
    double y=list.at(1).split(":").at(1).toDouble();
    double z=list.at(2).split(":").at(1).toDouble();
    double b=list.at(3).split(":").at(1).toDouble();
    file->close();
    MainWindow::PMAC->SetP(30,x);//X回零偏置
    MainWindow::PMAC->SetP(24,y);//y回零偏置
    MainWindow::PMAC->SetP(29,0);//z回零偏置设为零
    MainWindow::PMAC->SetP(31,b);//b回零偏置
    MainWindow::PMAC->SetP(28,C_Button_speed*0.6);//b回零偏置
/*********************软限位设置************************/
    MainWindow::PMAC->SetI(113,xlimit_left*10000);//X左限位
  //  qDebug()<<"Xlimit_left:"<<xlimit_left*10000<<"x/16:"<<x/16;
    MainWindow::PMAC->SetI(114,-xlimit_right*10000);//X右限位
    MainWindow::PMAC->SetI(213,blimit_left*10000);//B左限位
    MainWindow::PMAC->SetI(214,-blimit_right*10000);//B左限位
    MainWindow::PMAC->SetI(313,ylimit_bakcward*10000);//y后限位
    MainWindow::PMAC->SetI(314,-ylimit_forward*10000);//y前限位

//    MainWindow::PMAC->SetI(113,xlimit_left*10000+x/16);//X左限位
//    qDebug()<<"Xlimit_left:"<<xlimit_left*10000<<"x/16:"<<x/16;
//    MainWindow::PMAC->SetI(114,-xlimit_right*10000+x/16);//X右限位
//    MainWindow::PMAC->SetI(213,blimit_left*10000+b/16);//B左限位
//    MainWindow::PMAC->SetI(214,-blimit_right*10000+b/16);//B左限位
//    MainWindow::PMAC->SetI(513,ylimit_bakcward*10000+b/16);//y后限位
//    MainWindow::PMAC->SetI(514,-ylimit_forward*10000+b/16);//y前限位

}
void MainWindow::Init_hzaxi()//初始化昊志抛光轴
{
    /*************初始化串口**************/
    serial = new QSerialPort;
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setParity(QSerialPort::NoParity);
    serial->setDataBits(QSerialPort::Data8);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    QStringList portNameList;
   // ui->portbox->clear();                                        //关闭串口号
   // ui->portbox->addItem("刷新");                                //添加刷新
     portNameList.append("COM3");
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()) //添加新串口
    {
        portNameList.append(info.portName());
    }

  //  ui->portbox->addItems(portNameList);
    //ui->portbox->setCurrentIndex(9);                             // 当前串口号为COM1
    //serial->setPortName(ui->portbox->currentText());
if(portNameList.isEmpty())
{
    portNameList.append("COM3");
}
  serial->setPortName(portNameList.at(0));//设置串口号
  if(serial->isOpen())                                        // 如果串口打开了，先给他关闭
  {
      serial->clear();
      serial->close();
qDebug()<<"串口连接成功";
  }
  else                                                        // 如果串口关闭了，先给他打开
  {
      //当前选择的串口名字
     // serial->setPortName(ui->portbox->currentText());
      //用ReadWrite 的模式尝试打开串口，无法收发数据时，发出警告
      if(!serial->open(QIODevice::ReadWrite))
      {
          ui->statusBar->showMessage("抛光轴初始化打开失败",2000);
          return;
       }
      qDebug()<<"串口连接成功";
       qDebug()<<portNameList;
      // 打开状态，按钮显示“关闭串口”
    //  ui->openport->setText("关闭串口");
      // 打开状态，禁止用户操作
     // ui->portbox->setDisabled(1);
     // ui->startbutton->setDisabled(0);
     // ui->stopbutton->setDisabled(0);
     // ui->searcherr->setDisabled(0);
     // ui->openport->setStyleSheet("color: green;");
      // 打开，显示灯为绿色

  }
   //connect(serial,&QSerialPort::readyRead,this,&MainWindow::datareceived);


  //setCentralWidget(ui->txtEdit); //将txtEdit设置为中心组件，自动填充整个工作区



    hz =new hzaxle();





}
void MainWindow::Hz_start(int type,QString speed)//轴动作
{

    QStringList list;
    // list<<"正转运行:01 07 20 00 00 01";
      list<<"正转运行:01 07 20 00 00 01"<<"反转运行:01 07 20 00 00 02"<<"正转点动:01 07 20 00 00 03"<<"反转点动:01 07 20 00 00 04";

     //qDebug()<<list;
       QString oder;
        int c=type;
        switch (c)
        {
        case 0: oder= list.at(0).split(":").at(1) ;
            break;
        case 1: oder= list.at(1).split(":").at(1);
            break;
        case 2 : oder= list.at(2).split(":").at(1);
               break;
        case 3:  oder= list.at(3).split(":").at(1);
               break;
        }
        oder=oder.toLatin1();
        QByteArray senddata;
        hz->StringToHex(oder,senddata);
      //  qDebug()<<senddata;
       hz->AppendCRC16(senddata);
       QByteArray sendspeed;
     // QString speed = ui->speededit->text();
       hz->sendspeed(speed,sendspeed);
       qDebug()<<"速度";
       qDebug()<<sendspeed;

       serial->write(sendspeed);
       hz->Sleep(1000);
        serial->write(senddata);

}
void MainWindow::Hz_stop()//抛光轴停止
{
    //QStringList list;
    QString oder="01 07 20 00 00 05";
// list<<"自由停机:01 07 20 00 00 05"<<"减速停机:01 07 20 00 00 06";
//int c=ui->stopbox->currentIndex();
//      switch (c)
//      {
//      case 0: oder= list.at(0).split(":").at(1) ;
//          break;
//      case 1: oder= list.at(1).split(":").at(1);
//          break;
//      }
//       oder=oder.toLatin1();
       QByteArray senddata;
       hz->StringToHex(oder,senddata);
  //     qDebug()<<senddata;
      hz->AppendCRC16(senddata);
       serial->write(senddata);

PMAC->SetP(1,0);
}
void MainWindow::Axi_Home()//各个轴回零
{
    PMAC->SendCommand("ENABLE PLC5");
    PMAC->SetP(34, 1);//开机复位标志
}

 void MainWindow::read_pos()//读位置计时器的槽函数
{
    double x_pos,y_pos,z_pos,b_pos,c_pos,x_goal_pos;
    int c_po;
    int index_goal_pos;
 //   int last_index;
    PMAC->GetPositon(1,x_pos);
    PMAC->GetPositon(2,b_pos);
    PMAC->GetPositon(5,c_pos);
    PMAC->GetPositon(4,z_pos);
    PMAC->GetPositon(3,y_pos);
     x_goal_pos=PMAC->GetM(163)/32/96;
     c_po=c_pos;
    c_po=c_po%360;
    c_pos=c_po;
    ui->lineEdit_33->setText(QString::number(x_pos/10000, 'f', 4));
    ui->lineEdit_25->setText(QString::number(y_pos/10000, 'f', 4));
    ui->lineEdit_31->setText(QString::number(z_pos/10000, 'f', 4));
    ui->lineEdit_28->setText(QString::number(b_pos/10000, 'f', 4));
    ui->lineEdit_27->setText(QString::number(c_pos, 'f', 4));

    ui->lineEdit_34->setText(QString::number(x_pos/10000+x_devia_value, 'f', 4));
    ui->lineEdit_26->setText(QString::number(y_pos/10000+y_devia_value, 'f', 4));
    ui->lineEdit_32->setText(QString::number(z_pos/10000+z_devia_value, 'f', 4));
    ui->lineEdit_29->setText(QString::number(b_pos/10000+b_devia_value, 'f', 4));
    ui->lineEdit_30->setText(QString::number(c_pos, 'f', 4));


    ui->lineEdit_12->setText(QString::number(x_pos/10000, 'f', 4));
    ui->lineEdit_13->setText(QString::number(y_pos/10000, 'f', 4));
    ui->lineEdit_14->setText(QString::number(z_pos/10000, 'f', 4));
    ui->lineEdit_15->setText(QString::number(b_pos/10000, 'f', 4));
    ui->lineEdit_16->setText(QString::number(c_pos, 'f', 4));


    if(process_begin_flag==true)
    {
        //遍历
      //  for()
   //Nc_Data.indexOf()
        index_goal_pos=Nc_x.indexOf(QString::number(x_goal_pos/10000, 'f', 4));

        if(index_goal_pos!=-1)
        {
            last_index=index_goal_pos;
          //    qDebug()<<"last_index"<<last_index;
        }
        if(index_goal_pos==-1)
            index_goal_pos=last_index;

   //  ui->lineEdit_18->setText(QString::number(x_goal_pos/10000, 'f', 4));//工件坐标
         ui->lineEdit_18->setText(QString::number(Nc_Data.at(index_goal_pos).at(4), 'f', 4));//工件坐标
    ui->lineEdit_17->setText(QString::number(Nc_Data.at(index_goal_pos).at(7), 'f', 4));
    ui->lineEdit_20->setText(QString::number(Nc_Data.at(index_goal_pos).at(6), 'f', 4));
    ui->lineEdit_21->setText(QString::number(Nc_Data.at(index_goal_pos).at(1), 'f', 4));
    ui->lineEdit_19->setText(QString::number(c_pos, 'f', 4));
    }
    else
    {
        ui->lineEdit_18->setText("0.0000");//工件坐标
        ui->lineEdit_17->setText("0.0000");
        ui->lineEdit_20->setText("0.0000");
        ui->lineEdit_21->setText("0.0000");
        ui->lineEdit_19->setText("0.0000");

    }



    /*********************读机床位置状态**************************/


               int fluid_status, door_status,X_ALARM, B_ALARM, C_ALARM,Z_ALARM, X_P_LIMIT, B_P_LIMIT, X_N_LIMIT, B_N_LIMIT, Z_P_LIMIT, Z_N_LIMIT,LUN_ALARM,STOP_ALARM;
               double finish_flag,pmac_connect_status,polish_uplimit_contaceflag;
              // bool status;
                door_status=PMAC->GetM(15);//门按钮按下否
                fluid_status=PMAC->GetM(11);//开液按钮按下否
               X_ALARM=PMAC->GetM(123);//X轴警报
               B_ALARM=PMAC->GetM(223);//B轴警报
               C_ALARM = PMAC->GetM(343);//C轴警报
               LUN_ALARM = PMAC->GetM(50);//手轮急停警报
               STOP_ALARM = PMAC->GetM(9);//
               X_P_LIMIT=PMAC->GetM(121);//X正限位
               B_P_LIMIT=PMAC->GetM(221);//B正限位
               X_N_LIMIT=PMAC->GetM(122);//X负限位
               B_N_LIMIT=PMAC->GetM(222);//B负限位
               finish_flag = PMAC->GetP(32);//加工完成
               polish_uplimit_contaceflag = PMAC->GetP(48);//触碰抛光轴上限位
            //   PMAC_connect_status = PMAC->GetP(33);//询问是否连接上
              // MessageBox->Show(finish_flag->ToString());
               Z_P_LIMIT = PMAC->GetM(421);//Z上限位
               Z_N_LIMIT = PMAC->GetM(422);//Z下限位
               Z_ALARM = PMAC->GetM(423);//Z轴警报`
              // PAO_P_LIMIT = PMAC.GetM(321);//抛光轴上限位
             //  PMAC.GetResponseEx()

               int door_sta=ui->comboBox_7->currentIndex();
                int fluid_sta=ui->comboBox_8->currentIndex();
if(door_status == 1 && connect_flag==true&&door_sta==0)
{
    door_open=true;
    PMAC->SetM(4,1);//开门
    PMAC->SetM(2,0);//开门
}
if(door_status == 0 && connect_flag==true&&door_sta==0)
{
    door_open=false;
    PMAC->SetM(4,0);//关门
     PMAC->SetM(2,1);//关门
}

if(fluid_status == 1 && connect_flag==true&&fluid_sta==1)
{
   // door_open=true;
    PMAC->SetM(5,1);//开液
    //PMAC->SetM(2,0);//开门
}
if(fluid_status == 0 && connect_flag==true&&fluid_sta==1)
{
    //door_open=false;
    PMAC->SetM(5,0);//关液
    // PMAC->SetM(2,1);//关门
}



               if (X_ALARM == 1 && tip1 == false&&connect_flag==true)
               {
                   tip1 = true;
                   X_ALARM_flag = true;
                  // QMessageBox::information(this,"提示"，)
                   QMessageBox::information(this,"提示","X轴驱动器警报");

               }
               if (X_ALARM == 0 && tip1 == true)
               {
                   tip1 = false;
                   X_ALARM_flag = false;
               }



               if (X_P_LIMIT == 1 && tip3 == false)
               {
                   tip3 = true;
                   QMessageBox::information(this,"提示","X轴左限位触发,请手动回原点后复位！" );

               }
               if (X_P_LIMIT == 0 && tip3 == true && connect_flag == true)
               {
                   tip3 = false;
                   //QMessageBox::information(this,"提示","Z轴上限位触发");

               }


               if (B_ALARM == 1 && tip2 == false && connect_flag == true)
               {
                   tip2 = true;
                   B_ALARM_flag = true;
                   QMessageBox::information(this,"提示","B轴驱动器警报");

               }
               if (B_ALARM == 0 && tip2 == true)
               {
                   tip2 = false;
                   B_ALARM_flag = false;

               }

               if (B_P_LIMIT == 1 && tip4 == false)
               {
                   tip4 = true;
                 //  QMessageBox::information(this,"提示","B轴左限位触发,请手动回原点后复位！");

               }
               if (B_P_LIMIT == 0 && tip4 == true && connect_flag == true)
               {
                   tip4 = false;

               }

               if (X_N_LIMIT == 1 && tip5 == false)
               {
                   tip5 = true;
                   QMessageBox::information(this,"提示","X轴右限位触发,请手动回原点后复位！");

               }
               if (X_N_LIMIT == 0 && tip5 == true && connect_flag == true)
               {
                   tip5 = false;

               }


               if (B_N_LIMIT == 1&&tip6==false)
               {
                   tip6 = true;
                   QMessageBox::information(this,"提示","B轴右限位触发,请手动回原点后复位！");

               }
               if (B_N_LIMIT == 0 && tip6 == true && connect_flag == true)
               {
                   tip6 = false;

               }


               if (Z_N_LIMIT == 1 && tip7 == false&&connect_flag==true)
               {
                   tip7 = true;
                   QMessageBox::information(this,"提示","Z轴上限位触发,请手动回原点后复位！");

               }
               if (Z_N_LIMIT == 0 && tip7 == true && connect_flag == true)
               {
                   tip7 = false;

               }

               if (Z_P_LIMIT == 1 && tip8 == false && connect_flag == true)
               {
                   tip8 = true;
            //       QMessageBox::information(this,"提示","Z轴下限位触发,请手动回原点后复位！");

               }
               if (Z_P_LIMIT == 0 && tip8 == true && connect_flag == true)
               {
                   tip8 = false;

               }

               if (Z_ALARM == 1 && tip9 == false&&connect_flag==true)
               {
                   tip9 = true;
                   Z_ALARM_flag = true;
                   QMessageBox::information(this,"提示","Z轴驱动器警报");

               }
               if (Z_ALARM == 0 && tip9 == true)
               {
                   tip9 = false;
                   Z_ALARM_flag = false;

               }

               if (C_ALARM == 1 && tip10 == false && connect_flag == true)

               {
                   tip10 = true;
                   C_ALARM_flag = true;
                   QMessageBox::information(this,"提示","C轴警报");

               }

               if (C_ALARM == 0 && tip10 == true)
               {
                   tip10 = false;
                   C_ALARM_flag = false;

               }

//               if (LUN_ALARM == 0 && tip11 == false && connect_flag == true)
//               {
//                   tip11 = true;

//                   PMAC->SetM(47, 1);//亮红灯
//                   PMAC->SendCommand("&1A");
//                   PMAC->SendCommand("#1j/");
//                   PMAC->SendCommand("#2j/");
//                   PMAC->SendCommand("m502=0");
//                   PMAC->SendCommand("m302=0");
//                   PMAC->SendCommand("m6=0");
//                   PMAC->SendCommand("m7=0");
//                   PMAC->SendCommand("m0=1");
//                   QMessageBox::information(this,"提示","手轮急停警报");

//               }
//               if (LUN_ALARM == 1 && tip11 == true)
//               {
//                   tip11 = false;

//                   PMAC->SetM(47, 0);//灭红灯
//                   PMAC->SendCommand("m0=0");
//                  // QMessageBox::information(this,"提示","急停警报");

//               }

               if (STOP_ALARM == 1 && tip12 == false)
               {
                   tip12 = true;

                   PMAC->SetM(47, 1);//亮红灯
                   PMAC->SendCommand("&1A");
                   PMAC->SendCommand("#1j/");
                   PMAC->SendCommand("#2j/");
                   PMAC->SendCommand("m502=0");
                   PMAC->SendCommand("m302=0");
                   PMAC->SendCommand("m6=0");
                   PMAC->SendCommand("m7=0");
//                   PMAC->SendCommand("m0=1");
//                   PMAC->SendCommand("m3=0");
//                   PMAC->SendCommand("m4=0");
                   QMessageBox::information(this,"提示","急停警报");

               }
               if (STOP_ALARM == 0 && tip12 == true)
               {
                   tip12 = false;
               //    PMAC->SendCommand("m0=0");
                   PMAC->SetM(47, 0);//灭红灯
                 //  QMessageBox::information(this,"提示","急停警报");

               }


    //qDebug()<<"X:"<<x_pos;
}



void MainWindow::closeEvent(QCloseEvent *event)
{ //窗口关闭时询问是否退出
//   QMessageBox::StandardButton result=QMessageBox::question(this, "确认", "确定要退出本系统吗？",
//                      QMessageBox::Yes|QMessageBox::No,
//                      QMessageBox::No);

    QIcon icon= windowIcon();


   QMessageBox megBox;
   megBox.setIcon(QMessageBox::Question);
   megBox.setWindowIcon(icon);
   megBox.setWindowTitle("提示");
   megBox.addButton("是",QMessageBox::AcceptRole);
   megBox.addButton("否",QMessageBox::RejectRole);
   megBox.setText("确定要退出本系统吗？");
   int result= megBox.exec();
//   switch(result){
//   case QMessageBox::AcceptRole:
//   this->close();
//   break;
//   default:
//   break;
//   }

   if (result==QMessageBox::AcceptRole)
        event->accept();
    else
        event->ignore();
}

void MainWindow::Init()//初始化函数
{
        /*初始化buttongroup*/
    //ui->buttongroup


}
void MainWindow::Init_shapeGUi()//初始化函数
{


}

void MainWindow::Init_ProcessGUi()//初始化函数
{

}
void MainWindow::on_actionHelpFile_triggered()//帮助文档
{

    bool bRet = QDesktopServices::openUrl(QUrl::fromLocalFile("非球面镜片抛光机床操作手册.pdf"));
    if (!bRet)
    {
        QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("系统未安装PDF阅读软件，请安装\n一款后再执行此操作!"));
    }

}

void MainWindow::on_actionconnect_triggered()//连接控制器
{
    bool pbsuccess;//连接pmac成功否

    Pmac->Open(0,pbsuccess);//连接控制器0
    if(pbsuccess)
    {
       // QMessageBox::information(this, "提示", "连接失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        QMessageBox::information(this, "提示", "连接控制器成功！");
   }
    else
    {
      QMessageBox::information(this, "提示", "连接控制器失败！");
        //  QMessageBox::information(this, "提示", "连接失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}

void MainWindow::on_pushButton_clicked()//进入界面
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_2_clicked()//退出
{
    this->close();
}

void MainWindow::on_pushButton_4_clicked()//返回主界面
{
   this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_6_clicked()//形状参数设定界面
{
   ui->stackedWidget_2->setCurrentIndex(0);
   read_position->stop();
}

void MainWindow::on_pushButton_5_clicked()//加工参数设定界面
{
    ui->stackedWidget_2->setCurrentIndex(1);
    read_position->stop();
}
void MainWindow::on_pushButton_39_clicked()//面型误差补正界面
{
  ui->stackedWidget_2->setCurrentIndex(2);
  read_position->stop();
}
void MainWindow::on_pushButton_3_clicked()//生成代码界面
{
    ui->stackedWidget_2->setCurrentIndex(3);
    read_position->stop();
}

void MainWindow::on_pushButton_8_clicked()//加工界面
{
    ui->stackedWidget_2->setCurrentIndex(4);
    ui->lineEdit_11->setText(ui->lineEdit_Lensname->text());
    read_position->start();
}

void MainWindow::on_pushButton_9_clicked()//运动控制界面
{
    ui->stackedWidget_2->setCurrentIndex(5);
    read_position->start();
//   QAction *actionlianjie = new QAction(this);
//    actionlianjie->setObjectName(QString::fromUtf8("actionlianji"));
//    QIcon icon8;
//    icon8.addFile(QString::fromUtf8(":/Image/port.jpeg"), QSize(), QIcon::Normal, QIcon::Off);
//    actionlianjie->setIcon(icon8);
//    ui->menu->addAction(actionlianjie);
//
}




void MainWindow::on_pushButton_7_clicked()//读取形状参数界面参数
{


    QString str;//参数文件字符
    QString strPath=QCoreApplication::applicationDirPath();//获取程序当前路径
    QDir dir(strPath);//实例化文件路径类
    QFile *file=new QFile(this);//实例化文件读取对象
   QStringList list;
    if(dir.exists("形状参数"))//判断文件夹是否存在
    {
        dir.mkdir("形状参数");

    }
    dir.setPath(dir.path()+"/形状参数");//设置文件路径
    QString filepath=QFileDialog::getOpenFileName(this,"读取参数文件",dir.path(),"txt(*.txt1)");
    if(filepath.isEmpty())//取消读取
        return;
    file->setFileName(filepath);//目标文件

    if(!file->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::information(this,"提示！","读取失败！");
       return;

    }

    while (!file->atEnd())
    {

        str=file->readLine();
        str=str.remove("\n");
        list.append(str);

    }
ui->lineEdit_11->setText(list.at(0).split(":").at(1));//镜片名称
ui->lineEdit_Lensname->setText(list.at(0).split(":").at(1));//镜片名称
ui->lineEdit_HC->setText(list.at(2).split(":").at(1));
ui->lineEdit_HE->setText(list.at(3).split(":").at(1));
//ui->lineEdit_H->setText(list.at(4).split(":").at(1));
ui->lineEdit_DP->setText(list.at(5).split(":").at(1));
ui->lineEdit_D->setText(list.at(6).split(":").at(1));
ui->lineEdit_R->setText(list.at(7).split(":").at(1));
ui->lineEdit_K->setText(list.at(8).split(":").at(1));
ui->lineEdit_A1->setText(list.at(9).split(":").at(1));
ui->lineEdit_A2->setText(list.at(10).split(":").at(1));
ui->lineEdit_A3->setText(list.at(11).split(":").at(1));
ui->lineEdit_A4->setText(list.at(12).split(":").at(1));
ui->lineEdit_A5->setText(list.at(13).split(":").at(1));
ui->lineEdit_A6->setText(list.at(14).split(":").at(1));
ui->lineEdit_A7->setText(list.at(15).split(":").at(1));
ui->lineEdit_A8->setText(list.at(16).split(":").at(1));
ui->lineEdit_A9->setText(list.at(17).split(":").at(1));
ui->lineEdit_A10->setText(list.at(18).split(":").at(1));
ui->lineEdit_A11->setText(list.at(19).split(":").at(1));
ui->lineEdit_A12->setText(list.at(20).split(":").at(1));
ui->lineEdit_A13->setText(list.at(21).split(":").at(1));
ui->lineEdit_A14->setText(list.at(22).split(":").at(1));
ui->lineEdit_A15->setText(list.at(23).split(":").at(1));
ui->lineEdit_A16->setText(list.at(24).split(":").at(1));
ui->lineEdit_A17->setText(list.at(25).split(":").at(1));
ui->lineEdit_A18->setText(list.at(26).split(":").at(1));
ui->lineEdit_A19->setText(list.at(27).split(":").at(1));
ui->lineEdit_A20->setText(list.at(28).split(":").at(1));
ui->lineEdit_yuan_r->setText(list.at(29).split(":").at(1));

QString shape_type=list.at(1).split(":").at(1);
int shape_id=shape_type.toInt();
switch (shape_id)
{
case 1:
    ui->Lens_ao->setChecked(true);
    break;
case 2:
    ui->Lens_tu->setChecked(true);
    break;
//case 3:
//    ui->Lens_plane->setChecked(true);
//    break;
}
file->close();
delete file;

A[0]=ui->lineEdit_A1->  text().toDouble();
A[1]=ui->lineEdit_A2->  text().toDouble();
A[2]=ui->lineEdit_A3->  text().toDouble();
A[3]=ui->lineEdit_A4->  text().toDouble();
A[4]=ui->lineEdit_A5->  text().toDouble();
A[5]=ui->lineEdit_A6->  text().toDouble();
A[6]=ui->lineEdit_A7->  text().toDouble();
A[7]=ui->lineEdit_A8->  text().toDouble();
A[8]=ui->lineEdit_A9->  text().toDouble();
A[9]=ui->lineEdit_A10->  text().toDouble();
A[10]=ui->lineEdit_A11->  text().toDouble();
A[11]=ui->lineEdit_A12->  text().toDouble();
A[12]=ui->lineEdit_A13->  text().toDouble();
A[13]=ui->lineEdit_A14->  text().toDouble();
A[14]=ui->lineEdit_A15->  text().toDouble();
A[15]=ui->lineEdit_A16->  text().toDouble();
A[16]=ui->lineEdit_A17->  text().toDouble();
A[17]=ui->lineEdit_A18->  text().toDouble();
A[18]=ui->lineEdit_A19->  text().toDouble();
A[19]=ui->lineEdit_A20->  text().toDouble();
drawPlot(A);


}




void MainWindow::on_pushButton_10_clicked()//保存面型参数设定
{
    QFile *file=new QFile(this);
   QString Lens_name,shape_type,Hc,He,h,Dp,D,R,K,A1,A2,A3,A4,A5,A6,A7,A8,A9
           ,A10,A11,A12,A13,A14,A15,A16,A17,A18,A19,A20,yuan_r;
    //界面参数，shape_type曲面类型，非球面矢高Hc,工件高度He，夹具高度h
   //加工口径Dp,镜片直径D，非球面公式系数R,K,A1~A20
    //读取

   try
   {
       //shape_trpe=ui->line
    Lens_name=ui->lineEdit_Lensname->text();//镜片名称

    if(ui->Lens_ao->isChecked())
    {
        shape_type="1";

    }
    else if(ui->Lens_tu->isChecked())
    {
        shape_type="2";
    }
//    else if(ui->Lens_plane->isChecked())
//    {
//        shape_type="3";
//    }
    else
    {
         shape_type="1";
    }

      Hc=ui->lineEdit_HC->text();
      He=ui->lineEdit_HE->text();
      //h=ui->lineEdit_H->text();
    Dp=ui->lineEdit_DP->text();
    D=ui->lineEdit_D->text();
    R=ui->lineEdit_R->text();
    K=ui->lineEdit_K->text();
    A1=ui->lineEdit_A1->text();
    A2=ui->lineEdit_A2->text();
    A3=ui->lineEdit_A3->text();
    A4=ui->lineEdit_A4->text();
    A5=ui->lineEdit_A5->text();
    A6=ui->lineEdit_A6->text();
    A7=ui->lineEdit_A7->text();
    A8=ui->lineEdit_A8->text();
    A9=ui->lineEdit_A9->text();
    A10=ui->lineEdit_A10->text();
    A11=ui->lineEdit_A11->text();
    A12=ui->lineEdit_A12->text();
    A13=ui->lineEdit_A13->text();
    A14=ui->lineEdit_A14->text();
    A15=ui->lineEdit_A15->text();
    A16=ui->lineEdit_A16->text();
    A17=ui->lineEdit_A17->text();
    A18=ui->lineEdit_A18->text();
    A19=ui->lineEdit_A19->text();
    A20=ui->lineEdit_A20->text();
   yuan_r=ui->lineEdit_yuan_r->text();

   }
   catch(EXCEPINFO err)
   {
   // QMessageBox(err.tagEXCEPINFO)
     //  QMessageBox::information(this,"tip",err);
       throw err;
      // return;
   }
 QString path=QCoreApplication::applicationDirPath();//获取程序路径
 QDir dir(path);//创建文件路径对象

 if(dir.exists("形状参数"))
 {
     dir.mkdir("形状参数");
 }
 dir.setPath(dir.path()+"/形状参数");
// if(!dir.exists(ui->lineEdit_Lensname->text())){
//     dir.mkdir(ui->lineEdit_Lensname->text());
// }
 //dir.setCurrent(dir.path()+"/"+ui->lineEdit_Lensname->text());
 QString savefile=QFileDialog::getSaveFileName(this,"保存参数",dir.path(),"txt(*.txt1)");
 //if()
 if(savefile.isEmpty())
 {
     return;

 }
 file->setFileName(savefile);

 if(!file->open(QIODevice::WriteOnly|QIODevice::Text))
    {
     QMessageBox::information(this,"提示！","文件保存失败！");
     return;
    }
 QTextStream filestream(file);
 filestream<<"lens_name:"+Lens_name<<"\n"<<"shape_type:"+shape_type<<"\n"<<"Hc:"+Hc<<"\n"
          <<"He:"+He<<"\n"<<"h:"+h<<"\n"<<
         "DP:"+Dp<<"\n"<<"D:"+D<<"\n"<<"R:"+R<<"\n"<<"K:"+K<<"\n"<<
            "A1:"+A1<<"\n"<<"A2:"+A2<<"\n"<<"A3:"+A3<<"\n"<<"A4:"+A4<<"\n"<<
         "A5:"+A5<<"\n"<<"A6:"+A6<<"\n"<<"A7:"+A7<<"\n"<<"A8:"+A8<<"\n"<<"A9:"+A9
         <<"\n"<<"A10:"+A10<<"\n"<<"A11:"+A11<<"\n"<<"A12:"+A12<<"\n"<<"A13:"+A13<<"\n"<<
           "A14:"+A14<<"\n"<<"A15:"+A15<<"\n"<<"A16:"+A16<<"\n"<<"A17:"+A17<<"\n"<<"A18:"+A18<<"\n"<<
           "A19:"+A19<<"\n"<<"A20:"+A20<<"\n"<<"r:"+yuan_r;
 file->close();

 A[0]=ui->lineEdit_A1->  text().toDouble();
 A[1]=ui->lineEdit_A2->  text().toDouble();
 A[2]=ui->lineEdit_A3->  text().toDouble();
 A[3]=ui->lineEdit_A4->  text().toDouble();
 A[4]=ui->lineEdit_A5->  text().toDouble();
 A[5]=ui->lineEdit_A6->  text().toDouble();
 A[6]=ui->lineEdit_A7->  text().toDouble();
 A[7]=ui->lineEdit_A8->  text().toDouble();
 A[8]=ui->lineEdit_A9->  text().toDouble();
 A[9]=ui->lineEdit_A10->  text().toDouble();
 A[10]=ui->lineEdit_A11->  text().toDouble();
 A[11]=ui->lineEdit_A12->  text().toDouble();
 A[12]=ui->lineEdit_A13->  text().toDouble();
 A[13]=ui->lineEdit_A14->  text().toDouble();
 A[14]=ui->lineEdit_A15->  text().toDouble();
 A[15]=ui->lineEdit_A16->  text().toDouble();
 A[16]=ui->lineEdit_A17->  text().toDouble();
 A[17]=ui->lineEdit_A18->  text().toDouble();
 A[18]=ui->lineEdit_A19->  text().toDouble();
 A[19]=ui->lineEdit_A20->  text().toDouble();
 drawPlot(A);


}

void MainWindow::on_pushButton_11_clicked()//形状参数设定界面应用按钮
{


    try
    {


     if(ui->Lens_ao->isChecked())
     {
         MainWindow::parameter_shape[0]=1;

     }
     else if(ui->Lens_tu->isChecked())
     {
         MainWindow::parameter_shape[0]=2;

     }
//     else if(ui->Lens_plane->isChecked())
//     {
//         MainWindow::parameter_shape[0]=3;

//     }
     else
     {
             MainWindow::parameter_shape[0]=1;;
     }

        MainWindow::parameter_shape[1]=ui->lineEdit_HC->text().toDouble();
       MainWindow::parameter_shape[2]=ui->lineEdit_HE->text().toDouble();
   //   MainWindow::parameter_shape[3]=ui->lineEdit_H->text().toDouble();
     MainWindow::parameter_shape[4]=ui->lineEdit_DP->  text().toDouble();
     MainWindow::parameter_shape[5]=ui->lineEdit_D->  text().toDouble();
    MainWindow::parameter_shape[6]=ui->lineEdit_R->  text().toDouble();
    MainWindow::parameter_shape[7]=ui->lineEdit_K->  text().toDouble();
    MainWindow::parameter_shape[8]=ui->lineEdit_yuan_r->  text().toDouble();
     A[0]=ui->lineEdit_A1->  text().toDouble();
     A[1]=ui->lineEdit_A2->  text().toDouble();
     A[2]=ui->lineEdit_A3->  text().toDouble();
     A[3]=ui->lineEdit_A4->  text().toDouble();
     A[4]=ui->lineEdit_A5->  text().toDouble();
     A[5]=ui->lineEdit_A6->  text().toDouble();
     A[6]=ui->lineEdit_A7->  text().toDouble();
     A[7]=ui->lineEdit_A8->  text().toDouble();
     A[8]=ui->lineEdit_A9->  text().toDouble();
     A[9]=ui->lineEdit_A10->  text().toDouble();
     A[10]=ui->lineEdit_A11->  text().toDouble();
     A[11]=ui->lineEdit_A12->  text().toDouble();
     A[12]=ui->lineEdit_A13->  text().toDouble();
     A[13]=ui->lineEdit_A14->  text().toDouble();
     A[14]=ui->lineEdit_A15->  text().toDouble();
     A[15]=ui->lineEdit_A16->  text().toDouble();
     A[16]=ui->lineEdit_A17->  text().toDouble();
     A[17]=ui->lineEdit_A18->  text().toDouble();
     A[18]=ui->lineEdit_A19->  text().toDouble();
     A[19]=ui->lineEdit_A20->  text().toDouble();

     ui->lineEdit_11->setText(ui->lineEdit_Lensname->text());
     QString path=QCoreApplication::applicationDirPath();//获取程序路径
     QDir dir(path);//创建文件路径对象

    // dir.setPath(dir.path()+"/形状参数");
    // if(!dir.exists(ui->lineEdit_Lensname->text())){
    //     dir.mkdir(ui->lineEdit_Lensname->text());
    // }
     //dir.setCurrent(dir.path()+"/"+ui->lineEdit_Lensname->text());
     QString savefile=dir.path()+"\\paramenter_shape.txt";
     QFile *file=new QFile(this);

    file->setFileName(savefile);

     if(!file->open(QIODevice::WriteOnly|QIODevice::Text))
        {
         QMessageBox::information(this,"提示！","系统参数文件缺失！");
         return;
        }
     QTextStream filestream(file);
     filestream<<"lens_name:"+ui->lineEdit_Lensname->text()<<"\n"<<"shape_type:"+QString::number(parameter_shape[0])
             <<"\n"<<"Hc:"+QString::number(parameter_shape[1])<<"\n"
 <<"He:"+QString::number(parameter_shape[2])<<"\n"<<"h:"+QString::number(parameter_shape[3])<<"\n"<<
             "DP:"+QString::number(parameter_shape[4])<<"\n"<<"D:"+QString::number(parameter_shape[5])<<
 "\n"<<"R:"+QString::number(parameter_shape[6])<<"\n"<<"K:"+QString::number(parameter_shape[7])<<"\n"<<
                "A1:"+QString::number(A[0])<<"\n"<<"A2:"+QString::number(A[1])<<"\n"<<"A3:"+QString::number(A[2])
             <<"\n"<<"A4:"+QString::number(A[3])<<"\n"<<
             "A5:"+QString::number(A[4])<<"\n"<<"A6:"+QString::number(A[5])<<"\n"<<"A7:"+QString::number(A[6])
             <<"\n"<<"A8:"+QString::number(A[7])<<"\n"<<"A9:"+QString::number(A[8])
             <<"\n"<<"A10:"+QString::number(A[9])<<"\n"<<"A11:"+QString::number(A[10])<<"\n"<<
          "A12:"+QString::number(A[11])<<"\n"<<"A13:"+QString::number(A[12])<<"\n"<<
               "A14:"+QString::number(A[13])<<"\n"<<"A15:"+QString::number(A[14])<<"\n"<<
"A16:"+QString::number(A[15])<<"\n"<<"A17:"+QString::number(A[16])<<"\n"<<"A18:"+QString::number(A[17])<<"\n"<<
               "A19:"+QString::number(A[18])<<"\n"<<"A20:"+QString::number(A[19])<<"\n"<<"r:"+QString::number(parameter_shape[8]);
     file->close();
     delete  file;

    }
    catch(EXCEPINFO err)
    {
    // QMessageBox(err.tagEXCEPINFO)
        throw err;
       // return;
    }



   drawPlot(A);



}

void MainWindow::on_pushButton_13_clicked()//加工参数保存
{
    QFile *file =new QFile(this);
    QString constc_radiobutton,//恒转速
            constCspeed,//C轴速度
            changeC_radiobutton,//变转速
            max_cspeed,//最大C轴速度
            combox_datadistance,//数据间隔
            combox_toolradius//磨头直径
            ,combox_Cdirect,//工件转动方向
            combox_Tooldirect,//抛光头方向
          //  radiobutton_0degree,//0度
         //   radiobutton_45degree,//45度
            radiobutton_constfeed,//恒进给
            feed,//恒进给速度
            radiobutton_changefeed,//变进给

            feerate,//进给倍率
            process_left,//加工范围左
            process_right,//加工范围右
            pressure,//抛光压力
            toolspeed,//抛光头速度
            process_cycle,//加工次数
            tool_diameter,//抛光头直径
            cloth_thick,//抛光垫厚
            Tool_high;//工具头高度



    try
    {
//       if(ui->radioButton_constC->isChecked())//恒转速
//           constc_radiobutton="1";
//       else constc_radiobutton="0";


//       if(ui->radioButton_changedC->isChecked())//变转速
//            changeC_radiobutton="1";
//           else
//          changeC_radiobutton="0";

       constCspeed=ui->lineEdit_constCSpeed->text();//C轴速度
     // max_cspeed=ui->lineEdit_maxCspeed->text();//最大C轴速度
//      combox_datadistance=QString::asprintf("%.0f",static_cast<double>(ui->comboBox_dataDistance->currentIndex()));//数据间隔
//       combox_toolradius=QString::asprintf("%.0f",static_cast<double>(ui->comboBox_toolRaidus->currentIndex()));      //磨头直径
//        combox_Cdirect=QString::asprintf("%.0f",static_cast<double>(ui->comboBox_Cdirect->currentIndex())); //工件转动方向
//        combox_Tooldirect=QString::asprintf(static_cast<int>(ui->comboBox_ToolDirect->currentIndex()));   //抛光头方向
      combox_datadistance=QString::number(ui->comboBox_dataDistance->currentIndex(),16);//数据间隔
       combox_toolradius=QString::number(ui->comboBox_toolRaidus->currentIndex(),16);      //磨头直径
        combox_Cdirect=QString::number(ui->comboBox_Cdirect->currentIndex(),16); //工件转动方向
        combox_Tooldirect=QString::number(ui->comboBox_ToolDirect->currentIndex(),16);   //抛光头方向

    //    if(ui->radioButton_0degree->isChecked())//0度
       //  radiobutton_0degree="1";
      //  else radiobutton_0degree="0";

      // if (ui->radioButton_45degree->isChecked()) //45度
     //    radiobutton_45degree="1";
      //  else radiobutton_45degree="0";

        if(ui->radioButton_constantFeed->isChecked())//恒进给
         radiobutton_constfeed="1";
        else radiobutton_constfeed="0";

        if (ui->radioButton_ChangedFeed->isChecked()) //变进给
         radiobutton_changefeed="1";
        else radiobutton_changefeed="0";

        feed=ui->lineEdit_constfeed->text();//恒进给速度
        feerate=ui->lineEdit_feedrate->text();//进给倍率
        process_left=ui->lineEdit_ProdessLeft->text();
        process_right=ui->lineEdit_ProcessRight->text();//加工范围右
        pressure=ui->lineEdit_Pressure->text();//抛光压力
        toolspeed=ui->lineEdit_Toolspeed->text();//抛光头速度
        process_cycle=ui->lineEdit_ProcessCycle->text();//加工次数
        tool_diameter=ui->lineEdit_ToolD->text();//抛光头直径
        cloth_thick=ui->lineEdit_ClothThick->text();//抛光垫厚度
        Tool_high=ui->lineEdit_Toolhigh->text();//工具头高度
}

    catch(EXCEPINFO err)
    {
      throw err;
    }

 QString path=QCoreApplication::applicationDirPath();//获取程序路径
 QDir dir(path);

 if(!dir.exists("加工参数"))//创建路径
     dir.mkdir("加工参数");
    dir.setPath(dir.path()+"/加工参数");//设置路径
     QString savefilename=QFileDialog::getSaveFileName(this,"保存加工参数",dir.path());//打开对话框获取文件名
     file->setFileName(savefilename);//设置文件名

     if(!file->open(QIODevice::WriteOnly|QIODevice::Text))//打开文件
        {
         QMessageBox::information(this,"提示！","文件保存失败！");
         return;
        }

    QTextStream filestream(file);//借助QTextstream输出文本流

    filestream<<constc_radiobutton<<"\n"<<//恒转速
            constCspeed<<"\n"<<//C轴速度
            changeC_radiobutton<<"\n"<<//变转速
            max_cspeed<<"\n"<<//最大C轴速度
            combox_datadistance<<"\n"<<//数据间隔
            combox_toolradius<<"\n"<<//磨头直径
            combox_Cdirect<<"\n"<<//工件转动方向
            combox_Tooldirect<<"\n"<<//抛光头方向
           // radiobutton_0degree<<"\n"<<//0度
           // radiobutton_45degree<<"\n"<<//45度
            radiobutton_constfeed<<"\n"<<//恒进给
            feed<<"\n"<<//恒进给速度
            radiobutton_changefeed<<"\n"<<//变进给
            feerate<<"\n"<<//进给倍率
            process_left<<"\n"<<//加工范围左
            process_right<<"\n"<<//加工范围右
            pressure<<"\n"<<//抛光压力
            toolspeed<<"\n"<<//抛光头速度
            process_cycle<<"\n"<<//加工次数
            tool_diameter<<"\n"<<//抛光头直径
             cloth_thick<<"\n"<<//抛光垫厚
                Tool_high;//工具头高度

    file->close();//关闭文件
    delete  file;
}

void MainWindow::on_pushButton_12_clicked()//读取加工参数文件
{
    QString str;//存放读取的文件
    QFile *file =new QFile(this);//实例化文件读取类
    QString filepath=QCoreApplication::applicationDirPath();//获取程序路径
    QDir dir(filepath);//创建路径类
    QStringList list;
    if(!dir.exists("加工参数"))//创建路径
        dir.mkdir("加工参数");
       dir.setPath(dir.path()+"/加工参数");//设置路径

       QString filename=QFileDialog::getOpenFileName(this,"加工参数文件",dir.path());

       if(filename.isEmpty())//取消读取
           return;
       file->setFileName(filename);//目标文件

       if(!file->open(QIODevice::ReadOnly|QIODevice::Text))
       {
           QMessageBox::information(this,"提示！","读取失败！");
          return;

       }


       while(!file->atEnd())
       {
           str=file->readLine();
           str.remove("\n");
           list.append(str);
       }

      //  if(list.at(0)=="1")//恒转速
      // ui->radioButton_constC->setChecked(true);

       ui->lineEdit_constCSpeed->setText(list.at(1));//C转速

      //  if(list.at(2)=="1")
      // ui->radioButton_changedC->setChecked(true);//变转速

      // ui->lineEdit_maxCspeed->setText(list.at(3));//最大C速度

       ui->comboBox_dataDistance->setCurrentIndex(list.at(4).toInt());//数据间隔
       ui->comboBox_toolRaidus->setCurrentIndex(list.at(5).toInt());//磨头直径
       ui->comboBox_Cdirect->setCurrentIndex(list.at(6).toInt());//C轴方向
       ui->comboBox_ToolDirect->setCurrentIndex(list.at(7).toInt());//抛光头方向

//       if(list.at(8)=="1")//
//      ui-> radioButton_0degree->setChecked(true);//0度

//       if(list.at(9)=="1")
//      ui->radioButton_45degree->setChecked(true);//45度


       if(list.at(8)=="1")
      ui-> radioButton_constantFeed->setChecked(true);//恒进给

      ui-> lineEdit_constfeed->setText(list.at(9));//恒进给速度

       if(list.at(10)=="1")
      ui-> radioButton_ChangedFeed->setChecked(true);//变进给

       ui->lineEdit_feedrate->setText(list.at(11));//进给倍率
       ui->lineEdit_ProdessLeft->setText(list.at(12));//加工点左
      ui-> lineEdit_ProcessRight->setText(list.at(13));//加工点右
      ui-> lineEdit_Pressure->setText(list.at(14));//压力
       ui->lineEdit_Toolspeed->setText(list.at(15));//抛头转速
       ui->lineEdit_ProcessCycle->setText(list.at(16));//加工次数
       ui->lineEdit_ToolD->setText(list.at(17));//抛光头直径
       ui->lineEdit_ClothThick->setText(list.at(18));//抛光垫厚度
       ui->lineEdit_Toolhigh->setText(list.at(19));//工具头高度
     file->close();
   delete file;

}

void MainWindow::on_pushButton_14_clicked()//加工参数应用按钮
{

    try{
//    if(ui->radioButton_constC->isChecked())//恒转速
     //   parameter_process[0]=1;
 //   else {
  //       parameter_process[0]=0;

 //   }

   parameter_process[2]= ui->lineEdit_constCSpeed->text().toDouble();//C转速

  //   if(ui->radioButton_changedC->isChecked())//变转速
   //      parameter_process[2]=1;
  //   else {
  //        parameter_process[2]=0;

  //   }

   //  parameter_process[3]=ui->lineEdit_maxCspeed->text().toDouble();//最大C速度

    parameter_process[4]=QString::number(ui->comboBox_dataDistance->currentIndex(),16).toDouble();//数据间隔
    parameter_process[5]=QString::number(ui->comboBox_toolRaidus->currentIndex(),16).toDouble();//磨头直径
    parameter_process[6]=QString::number(ui->comboBox_Cdirect->currentIndex(),16).toDouble();//C轴方向
    parameter_process[7]=QString::number(ui->comboBox_ToolDirect->currentIndex(),16).toDouble();//抛光头方向

   // if(ui-> radioButton_0degree->isChecked())//0度
   //     parameter_process[8]=1;
  //  else {
  //       parameter_process[8]=0;

//    }

//    if(ui-> radioButton_45degree->isChecked())//45度
//        parameter_process[9]=1;
//    else {
//         parameter_process[9]=0;

//    }

    if(ui-> radioButton_constantFeed->isChecked())//恒进给
        parameter_process[10]=1;
    else {
         parameter_process[10]=0;

    }

   parameter_process[11]=ui-> lineEdit_constfeed->text().toDouble();//恒进给速度

   if(ui-> radioButton_ChangedFeed->isChecked())//变进给
       parameter_process[12]=1;
   else {
        parameter_process[12]=0;

   }

    parameter_process[13]=ui->lineEdit_feedrate->text().toDouble();//进给倍率
    parameter_process[14]=ui->lineEdit_ProdessLeft->text().toDouble();//加工点左
   parameter_process[15]=ui-> lineEdit_ProcessRight->text().toDouble();//加工点右
   parameter_process[16]=ui-> lineEdit_Pressure->text().toDouble();//压力
    parameter_process[17]=ui->lineEdit_Toolspeed->text().toDouble();//抛头转速
    parameter_process[18]=ui->lineEdit_ProcessCycle->text().toDouble();//加工次数
    }
    catch(EXCEPINFO err)
    {
        throw err;
    }

    QFile *file =new QFile(this);
    QString constc_radiobutton,//恒转速
            constCspeed,//C轴速度
            changeC_radiobutton,//变转速
            max_cspeed,//最大C轴速度
            combox_datadistance,//数据间隔
            combox_toolradius//磨头直径
            ,combox_Cdirect,//工件转动方向
            combox_Tooldirect,//抛光头方向
          //  radiobutton_0degree,//0度
           // radiobutton_45degree,//45度
            radiobutton_constfeed,//恒进给
            feed,//恒进给速度
            radiobutton_changefeed,//变进给

            feerate,//进给倍率
            process_left,//加工范围左
            process_right,//加工范围右
            pressure,//抛光压力
            toolspeed,//抛光头速度
            process_cycle,//加工次数
            tool_diameter,//抛光头直径
            cloth_thick,//抛光垫厚度
            Tool_high;//工具头高度

    try
    {
   //    if(ui->radioButton_constC->isChecked())//恒转速
   //        constc_radiobutton="1";
    //   else constc_radiobutton="0";


   //    if(ui->radioButton_changedC->isChecked())//变转速
    //        changeC_radiobutton="1";
     //      else
     //     changeC_radiobutton="0";

       constCspeed=ui->lineEdit_constCSpeed->text();//C轴速度
    //  max_cspeed=ui->lineEdit_maxCspeed->text();//最大C轴速度
//      combox_datadistance=QString::asprintf("%.0f",static_cast<double>(ui->comboBox_dataDistance->currentIndex()));//数据间隔
//       combox_toolradius=QString::asprintf("%.0f",static_cast<double>(ui->comboBox_toolRaidus->currentIndex()));      //磨头直径
//        combox_Cdirect=QString::asprintf("%.0f",static_cast<double>(ui->comboBox_Cdirect->currentIndex())); //工件转动方向
//        combox_Tooldirect=QString::asprintf(static_cast<int>(ui->comboBox_ToolDirect->currentIndex()));   //抛光头方向
      combox_datadistance=QString::number(ui->comboBox_dataDistance->currentIndex(),16);//数据间隔
       combox_toolradius=QString::number(ui->comboBox_toolRaidus->currentIndex(),16);      //磨头直径
        combox_Cdirect=QString::number(ui->comboBox_Cdirect->currentIndex(),16); //工件转动方向
        combox_Tooldirect=QString::number(ui->comboBox_ToolDirect->currentIndex(),16);   //抛光头方向

      //  if(ui->radioButton_0degree->isChecked())//0度
       //  radiobutton_0degree="1";
      //  else radiobutton_0degree="0";

       //if (ui->radioButton_45degree->isChecked()) //45度
       //  radiobutton_45degree="1";
      //  else radiobutton_45degree="0";

        if(ui->radioButton_constantFeed->isChecked())//恒进给
         radiobutton_constfeed="1";
        else radiobutton_constfeed="0";

        if (ui->radioButton_ChangedFeed->isChecked()) //变进给
         radiobutton_changefeed="1";
        else radiobutton_changefeed="0";

        feed=ui->lineEdit_constfeed->text();//恒进给速度
        feerate=ui->lineEdit_feedrate->text();//进给倍率
        process_left=ui->lineEdit_ProdessLeft->text();
        process_right=ui->lineEdit_ProcessRight->text();//加工范围右
        pressure=ui->lineEdit_Pressure->text();//抛光压力
        toolspeed=ui->lineEdit_Toolspeed->text();//抛光头速度
        process_cycle=ui->lineEdit_ProcessCycle->text();//加工次数
       tool_diameter=ui->lineEdit_ToolD->text();//抛光头直径
       cloth_thick=ui->lineEdit_ClothThick->text();//抛光垫厚度
       Tool_high=ui->lineEdit_Toolhigh->text();//工具头高度

}

    catch(EXCEPINFO err)
    {
      throw err;
    }



 QString path=QCoreApplication::applicationDirPath();//获取程序路径
 QDir dir(path);


//   dir.setPath(dir.path()+"/加工参数");//设置路径
     QString savefilename=dir.path()+"\\paramenter_process.txt";
     file->setFileName(savefilename);//设置文件名

     if(!file->open(QIODevice::WriteOnly|QIODevice::Text))//打开文件
        {
         QMessageBox::information(this,"提示！","系统参数文件缺失！");
         return;
        }

    QTextStream filestream(file);//借助QTextstream输出文本流

    filestream<<constc_radiobutton<<"\n"<<//恒转速
            constCspeed<<"\n"<<//C轴速度
            changeC_radiobutton<<"\n"<<//变转速
            max_cspeed<<"\n"<<//最大C轴速度
            combox_datadistance<<"\n"<<//数据间隔
            combox_toolradius<<"\n"<<//磨头直径
            combox_Cdirect<<"\n"<<//工件转动方向
            combox_Tooldirect<<"\n"<<//抛光头方向
//            radiobutton_0degree<<"\n"<<//0度
//            radiobutton_45degree<<"\n"<<//45度
            radiobutton_constfeed<<"\n"<<//恒进给
            feed<<"\n"<<//恒进给速度
            radiobutton_changefeed<<"\n"<<//变进给
            feerate<<"\n"<<//进给倍率
            process_left<<"\n"<<//加工范围左
            process_right<<"\n"<<//加工范围右
            pressure<<"\n"<<//抛光压力
            toolspeed<<"\n"<<//抛光头速度
            process_cycle<<"\n"<<//;//加工次数
           tool_diameter<<"\n"<<//抛光头直径
            cloth_thick<<"\n"<<//抛光垫厚度
                Tool_high;//工具头高度
    file->close();//关闭文件
    delete  file;


}

bool MainWindow::produce_NC2()//生成补正代码
{
    //以下注释试试生成NC代码的
    Produce_Gcode *Nc_data= new Produce_Gcode;

//    double curvature_compensate=1, n=1, R=100, K=0, dist=0.1, t = 0, vc=100, H=10, R_left=-5, SAG=1, yuan_r=1, ao_tu=1, R_right=5, constan_vc=100, constan_F=100, symbol = 1, tool_r=3, Dp=20, D_workpiece=30;
    double B_turnR,curvature_compensate,n, R, K,dist, t = 0, vc, H, R_left,SAG,yuan_r,ao_tu,R_right,constan_vc,constan_F, symbol = 1,tool_r,Dp,D_workpiece;
    double press_distant;//压缩量
    try {

        A[0]=ui->lineEdit_A1->  text().toDouble();
        A[1]=ui->lineEdit_A2->  text().toDouble();
        A[2]=ui->lineEdit_A3->  text().toDouble();
        A[3]=ui->lineEdit_A4->  text().toDouble();
        A[4]=ui->lineEdit_A5->  text().toDouble();
        A[5]=ui->lineEdit_A6->  text().toDouble();
        A[6]=ui->lineEdit_A7->  text().toDouble();
        A[7]=ui->lineEdit_A8->  text().toDouble();
        A[8]=ui->lineEdit_A9->  text().toDouble();
        A[9]=ui->lineEdit_A10->  text().toDouble();
        A[10]=ui->lineEdit_A11->  text().toDouble();
        A[11]=ui->lineEdit_A12->  text().toDouble();
        A[12]=ui->lineEdit_A13->  text().toDouble();
        A[13]=ui->lineEdit_A14->  text().toDouble();
        A[14]=ui->lineEdit_A15->  text().toDouble();
        A[15]=ui->lineEdit_A16->  text().toDouble();
        A[16]=ui->lineEdit_A17->  text().toDouble();
        A[17]=ui->lineEdit_A18->  text().toDouble();
        A[18]=ui->lineEdit_A19->  text().toDouble();
        A[19]=ui->lineEdit_A20->  text().toDouble();

                  n = ui->lineEdit_ProcessCycle->text().toDouble();//加工次数
                   R = ui->lineEdit_R->text().toDouble();  //面型参数R
                   K = ui->lineEdit_K->text().toDouble();//面型参数K
                   vc = ui->lineEdit_constfeed->text().toDouble();//C轴最大转速
                 //  H = ui->lineEdit_HC->text().toDouble()+ui->lineEdit_H->text().toDouble();//镜片高度+夹具高度
               //  H = ui->lineEdit_HC->text().toDouble();
//                   SAG = ui->lineEdit_HE->text().toDouble();//非球面中心到平面距离
                   H = ui->lineEdit_HE->text().toDouble();
                     SAG = ui->lineEdit_HC->text().toDouble();//非球面中心到边缘垂直距离

                 //  fixture_h = Convert.ToDouble(yuanr_text.Text.Trim());//夹具高度，从移动调心夹具底面到模仁底面距离
                   yuan_r = ui->lineEdit_yuan_r->text().toDouble();//圆角半径
                   if(yuan_r<0.2)//圆角最小为0.2
                       yuan_r=0.2;
                    constan_vc = ui->lineEdit_constfeed->text().toDouble();//恒定C转速
                   constan_F = ui->lineEdit_constfeed->text().toDouble();//恒定进给

                   Dp = ui->lineEdit_DP->text().toDouble();//工件加工口径
                   D_workpiece = ui->lineEdit_D->text().toDouble();
                   press_distant=ui->lineEdit_Pressure->text().toDouble();//压缩量
                   Cloth_thickness=qAbs(ui->lineEdit_ClothThick->text().toDouble());//抛光垫厚度
                   B_turnR=Lworkpiece_h+qAbs(ui->lineEdit_Toolhigh->text().toDouble());//B轴回转径

                //    Dp = D_workpiece;
                       if (ui->lineEdit_ProdessLeft->text()=="")
                           R_left = 0;
                       else
                           R_left = ui->lineEdit_ProdessLeft->text().toDouble();//加工范围半径

                       if (ui->lineEdit_ProcessRight->text()=="")
                           R_right = 0;
                       else
                           R_right = ui->lineEdit_ProcessRight->text().toDouble();//加工口径另一值
                       // textBox18.text
                       if (R_left >= R_right)
                       { QMessageBox::information(this,"提示！","加工范围设定有误，左边框值不可大于右边框值，请重新设定加工范围！"); return false; }
                       if (qAbs(R_left) >qAbs(D_workpiece/2))
                       {
                           QMessageBox::information(this,"提示！","加工范围设定有误，左边框值超出工件直径范围，请重新设定加工范围！");
                           return false;
                       }
                       else if (qAbs(R_right) > qAbs(D_workpiece/2))
                       {
                           QMessageBox::information(this,"提示！","加工范围设定有误，右边框值超出工件直径范围，请重新设定加工范围！");
                           return false;
                       }
                       R_left=-D_workpiece/2;
                       R_right=D_workpiece/2;
                       if (ui->Lens_ao->isChecked())//凹凸判断
                           ao_tu = -1;
                       else
                           ao_tu = 1;

                       if (ui->comboBox_dataDistance->currentIndex()==0)

                           dist = 0.1;
                       else if(ui->comboBox_dataDistance->currentIndex()==1)
                           dist = 0.05;
                       else
                           dist=0.01;

                       if (ui->comboBox_toolRaidus->currentIndex()==0)
                           tool_r = 1;
                       else if (ui->comboBox_toolRaidus->currentIndex()==1)
                           tool_r = 3;
                       else
                           tool_r = 5;

//                       if (ui->radioButton_0degree->isChecked())//垂直抛
//                       {
//                           tool_r = 7;
//                       }


                       if (ui->Lens_ao->isChecked() || ui->Lens_tu->isChecked())
                       {
                           if (ui->Lens_ao->isChecked())
                           {
                               if (R > 1e-7)
                                   symbol = 1;
                               else
                                   symbol = -1;

                           }
                           if (ui->Lens_tu->isChecked())
                           {
                               if (R > 1e-7)
                                   symbol = -1;
                               else
                                   symbol = 1;
                           }
                           if(ui->radioButton_constantFeed->isChecked())//判断恒进给
                           {
                               F_flag=true;
                           }
                           else {
                               F_flag=false;
                           }

                         //  if (comboBox13.SelectedIndex == 1)
                               curvature_compensate = 1;
                         //  else if (comboBox13.SelectedIndex == 2)
                           //    curvature_compensate = 2;
                        //   else
                  }         //    curvature_compensate = 0;


    } catch (QString exception) {
        //QMessageBox::information(this,tr("提示！"),tr(err.1))
       QMessageBox::about(this,"Error",exception);
    }

    if(Dp>D_workpiece)
      {
        QMessageBox::information(this,tr("提示！"),tr("参数设定有误，加工口径大于工件口径！"));
        return false;
    }
    if(press_distant>Cloth_thickness-Cloth_minthickness)
    {
        QMessageBox::information(this,tr("提示！"),tr("抛光垫压缩量过大！"));
        return false;
    }

 //   double A[20];
    double **data=Nc_data->aspheric2(press_distant,Cloth_thickness,curvature_compensate, first_position_feed, D_workpiece, Dp, C_motor_scale_factor, C_motor_offset, B_turnR, other_h, SAG, yuan_r, ao_tu, R_right, tool_r, constan_vc, constan_F, Vc_flag, F_flag, dist, symbol, n, vc, H, R_left, R, K, A);//生成代码
//double a=;


//double ** data2=Nc_data->Test2DArray(2,3);
//for(int i=0;i<2;i++)
//{
//    for(int j=0;j<3;j++)
//    {
//         qDebug()<<data[i][j];
//    }

//}


QVector<double>v;//

int r=Nc_data->row;
int c= Nc_data->colum;
Nc_Data.clear();
Nc_x.clear();
for (int i = 0; i < r; i++)//输入r*c的二维数组
    {
        v.clear();//子数组返回时要清除
        for (int j = 0; j <c; j++)
        {
            //cin >> temp;
            v.push_back(data[i][j]);
        }
        Nc_Data.push_back(v);
        Nc_x.push_back(QString::number(v.at(0),'f',4));
    }


// 释放内存
// for (int i = 0; i < 3; i++)
// {
//     delete[] data[i];
// }
 v.clear();
 delete[] data;
// delete Nc_data;



}
bool MainWindow::produce_NC()//生成非补正代码
{
    //以下注释试试生成NC代码的
    Produce_Gcode *Nc_data= new Produce_Gcode;

//    double curvature_compensate=1, n=1, R=100, K=0, dist=0.1, t = 0, vc=100, H=10, R_left=-5, SAG=1, yuan_r=1, ao_tu=1, R_right=5, constan_vc=100, constan_F=100, symbol = 1, tool_r=3, Dp=20, D_workpiece=30;
    double B_turnR,curvature_compensate,n, R, K,dist, t = 0, vc, H, R_left,SAG,yuan_r,ao_tu,R_right,constan_vc,constan_F, symbol = 1,tool_r,Dp,D_workpiece;
    double press_distant;//布压缩量
    try {

        A[0]=ui->lineEdit_A1->  text().toDouble();
        A[1]=ui->lineEdit_A2->  text().toDouble();
        A[2]=ui->lineEdit_A3->  text().toDouble();
        A[3]=ui->lineEdit_A4->  text().toDouble();
        A[4]=ui->lineEdit_A5->  text().toDouble();
        A[5]=ui->lineEdit_A6->  text().toDouble();
        A[6]=ui->lineEdit_A7->  text().toDouble();
        A[7]=ui->lineEdit_A8->  text().toDouble();
        A[8]=ui->lineEdit_A9->  text().toDouble();
        A[9]=ui->lineEdit_A10->  text().toDouble();
        A[10]=ui->lineEdit_A11->  text().toDouble();
        A[11]=ui->lineEdit_A12->  text().toDouble();
        A[12]=ui->lineEdit_A13->  text().toDouble();
        A[13]=ui->lineEdit_A14->  text().toDouble();
        A[14]=ui->lineEdit_A15->  text().toDouble();
        A[15]=ui->lineEdit_A16->  text().toDouble();
        A[16]=ui->lineEdit_A17->  text().toDouble();
        A[17]=ui->lineEdit_A18->  text().toDouble();
        A[18]=ui->lineEdit_A19->  text().toDouble();
        A[19]=ui->lineEdit_A20->  text().toDouble();

                  n = ui->lineEdit_ProcessCycle->text().toDouble();//加工次数
                   R = ui->lineEdit_R->text().toDouble();  //面型参数R
                   K = ui->lineEdit_K->text().toDouble();//面型参数K
                   vc = ui->lineEdit_constfeed->text().toDouble();//C轴最大转速
              //     H = ui->lineEdit_HE->text().toDouble()+ui->lineEdit_H->text().toDouble();//镜片高度+夹具高度
                 H = ui->lineEdit_HE->text().toDouble();
                   SAG = ui->lineEdit_HC->text().toDouble();//非球面中心到边缘垂直距离
                 //  fixture_h = Convert.ToDouble(yuanr_text.Text.Trim());//夹具高度，从移动调心夹具底面到模仁底面距离
                   yuan_r = ui->lineEdit_yuan_r->text().toDouble();//圆角半径
                    constan_vc = ui->lineEdit_constfeed->text().toDouble();//恒定C转速
                   constan_F = ui->lineEdit_constfeed->text().toDouble();//恒定进给
                   if(yuan_r<0.2)//圆角最小为0.2
                       yuan_r=0.2;
                   Dp = ui->lineEdit_DP->text().toDouble();//工件加工口径
                   D_workpiece = ui->lineEdit_D->text().toDouble();



                   press_distant=ui->lineEdit_Pressure->text().toDouble();//压缩量
                   Cloth_thickness=qAbs(ui->lineEdit_ClothThick->text().toDouble());//布的厚度
                   B_turnR=Lworkpiece_h+qAbs(ui->lineEdit_Toolhigh->text().toDouble());//B轴回转径
                       if (ui->lineEdit_ProdessLeft->text()=="")
                           R_left = 0;
                       else
                           R_left = ui->lineEdit_ProdessLeft->text().toDouble();//加工范围半径

                       if (ui->lineEdit_ProcessRight->text()=="")
                           R_right = 0;
                       else
                           R_right = ui->lineEdit_ProcessRight->text().toDouble();//加工口径另一值
                       // textBox18.text
                       if (R_left >= R_right)
                       { QMessageBox::information(this,"提示！","加工范围设定有误，左边框值不可大于右边框值，请重新设定加工范围！"); return false; }

                       if (qAbs(R_left) >qAbs(D_workpiece/2))
                       {
                           QMessageBox::information(this,"提示！","加工范围设定有误，左边框值超出工件直径范围，请重新设定加工范围！");
                           return false;
                       }
                       else if (qAbs(R_right) > qAbs(D_workpiece/2))
                       {
                           QMessageBox::information(this,"提示！","加工范围设定有误，右边框值超出工件直径范围，请重新设定加工范围！");
                           return false;
                       }


                       if (ui->Lens_ao->isChecked())//凹凸判断
                           ao_tu = -1;
                       else
                           ao_tu = 1;

                       if (ui->comboBox_dataDistance->currentIndex()==0)

                           dist = 0.1;
                       else if(ui->comboBox_dataDistance->currentIndex()==1)
                           dist = 0.05;
                       else
                           dist=0.01;

                       if (ui->comboBox_toolRaidus->currentIndex()==0)
                           tool_r = 1;
                       else if (ui->comboBox_toolRaidus->currentIndex()==1)
                           tool_r = 3;
                       else
                           tool_r = 5;

                       //if (ui->radioButton_0degree->isChecked())//垂直抛
                     //  {
                     //      tool_r = 7;
                     //  }


                       if (ui->Lens_ao->isChecked() || ui->Lens_tu->isChecked())
                       {
                           if (ui->Lens_ao->isChecked())
                           {
                               if (R > 1e-7)
                                   symbol = 1;
                               else
                                   symbol = -1;

                           }
                           if (ui->Lens_tu->isChecked())
                           {
                               if (R >1e-7)
                                   symbol = -1;
                               else
                                   symbol = 1;
                           }

                           if(ui->radioButton_constantFeed->isChecked())//判断恒进给
                           {
                               F_flag=true;
                           }
                           else {
                               F_flag=false;
                           }
                         //  if (comboBox13.SelectedIndex == 1)
                               curvature_compensate = 1;
                         //  else if (comboBox13.SelectedIndex == 2)
                           //    curvature_compensate = 2;
                        //   else
                  }         //    curvature_compensate = 0;


    } catch (QString exception) {
        //QMessageBox::information(this,tr("提示！"),tr(err.1))
       QMessageBox::about(this,"Error",exception);
    }


  /**************参数判断**************/

    if(Dp>D_workpiece)
      {QMessageBox::information(this,tr("提示！"),tr("参数设定有误，加工口径大于工件口径！"));
      return false;}
    if(press_distant>Cloth_thickness-Cloth_minthickness)
       {
        QMessageBox::information(this,tr("提示！"),tr("抛光垫压缩量过大！"));
        return false;
    }
     /****************************/

 //   double A[20];
    double **data=Nc_data->aspheric2(press_distant,Cloth_thickness,curvature_compensate, first_position_feed, D_workpiece, Dp, C_motor_scale_factor, C_motor_offset,  B_turnR, other_h, SAG, yuan_r, ao_tu, R_right, tool_r, constan_vc, constan_F, Vc_flag, F_flag, dist, symbol, n, vc, H, R_left, R, K, A);//生成代码
//double a=;


//double ** data2=Nc_data->Test2DArray(2,3);
//for(int i=0;i<2;i++)
//{
//    for(int j=0;j<3;j++)
//    {
//         qDebug()<<data[i][j];
//    }

//}


QVector<double>v;//

int r=Nc_data->row;
int c= Nc_data->colum;
double speedrate=1;
double temp;
int index_feed;//位置索引
Nc_Data.clear();
Nc_x.clear();

for (int i = 0; i < r; i++)//输入r*c的二维数组
    {
        v.clear();//子数组返回时要清除
        temp=10*data[i][4];

        index_feed=qRound(temp);//取整

        if(index_feed<0)//判断位置
          index_feed=-index_feed;
        else if(index_feed>0)
            index_feed=index_feed-1;
        //qDebug()<<"index"<<10*data[i][4];
      //  qDebug()<<"index2"<< index_feed;
      //  qDebug()<<"index3"<< temp;
        speedrate=external_rate[index_feed];

   //    speedrate=external_rate[i-(r-1)/2];

        for (int j = 0; j <c; j++)
        {
            //cin >> temp;
           if(j==2)
            v.push_back(data[i][j]*speedrate);
           else {
               v.push_back(data[i][j]);

                }

        }
     //   qDebug()<<"data[i]"<<data[i][0];
        Nc_Data.push_back(v);
        Nc_x.push_back(QString::number(v.at(0),'f',4));
    }


// 释放内存
// for (int i = 0; i < 3; i++)
// {
//     delete[] data[i];
// }
 v.clear();
 delete[] data;
// delete Nc_data;




}

void MainWindow::produce_NC_interference_check()
{
    //以下注释试试生成NC代码的
    Produce_Gcode *Nc_data= new Produce_Gcode;

//    double curvature_compensate=1, n=1, R=100, K=0, dist=0.1, t = 0, vc=100, H=10, R_left=-5, SAG=1, yuan_r=1, ao_tu=1, R_right=5, constan_vc=100, constan_F=100, symbol = 1, tool_r=3, Dp=20, D_workpiece=30;
    double curvature_compensate,n, R, K,dist, t = 0, vc, H, R_left,SAG,yuan_r,ao_tu,R_right,constan_vc,constan_F, symbol = 1,tool_r,Dp,D_workpiece;
double press_distant;
    try {

        A[0]=ui->lineEdit_A1->  text().toDouble();
        A[1]=ui->lineEdit_A2->  text().toDouble();
        A[2]=ui->lineEdit_A3->  text().toDouble();
        A[3]=ui->lineEdit_A4->  text().toDouble();
        A[4]=ui->lineEdit_A5->  text().toDouble();
        A[5]=ui->lineEdit_A6->  text().toDouble();
        A[6]=ui->lineEdit_A7->  text().toDouble();
        A[7]=ui->lineEdit_A8->  text().toDouble();
        A[8]=ui->lineEdit_A9->  text().toDouble();
        A[9]=ui->lineEdit_A10->  text().toDouble();
        A[10]=ui->lineEdit_A11->  text().toDouble();
        A[11]=ui->lineEdit_A12->  text().toDouble();
        A[12]=ui->lineEdit_A13->  text().toDouble();
        A[13]=ui->lineEdit_A14->  text().toDouble();
        A[14]=ui->lineEdit_A15->  text().toDouble();
        A[15]=ui->lineEdit_A16->  text().toDouble();
        A[16]=ui->lineEdit_A17->  text().toDouble();
        A[17]=ui->lineEdit_A18->  text().toDouble();
        A[18]=ui->lineEdit_A19->  text().toDouble();
        A[19]=ui->lineEdit_A20->  text().toDouble();

                  n = ui->lineEdit_ProcessCycle->text().toDouble();//加工次数
                   R = ui->lineEdit_R->text().toDouble();  //面型参数R
                   K = ui->lineEdit_K->text().toDouble();//面型参数K
                   vc = ui->lineEdit_constfeed->text().toDouble();//C轴最大转速
//                   H = ui->lineEdit_HC->text().toDouble();//模仁高度

//                   SAG = ui->lineEdit_HE->text().toDouble();//非球面中心到平面距离
                   H = ui->lineEdit_HE->text().toDouble();
                     SAG = ui->lineEdit_HC->text().toDouble();//非球面中心到边缘垂直距离

                 //  fixture_h = Convert.ToDouble(yuanr_text.Text.Trim());//夹具高度，从移动调心夹具底面到模仁底面距离
                   yuan_r = ui->lineEdit_yuan_r->text().toDouble();//圆角半径
                    constan_vc = ui->lineEdit_constfeed->text().toDouble();//恒定C转速
                   constan_F = ui->lineEdit_constfeed->text().toDouble();//恒定进给

                   Dp = ui->lineEdit_DP->text().toDouble();//工件加工口径
                   D_workpiece = ui->lineEdit_D->text().toDouble();
                   press_distant=ui->lineEdit_Pressure->text().toDouble();
                //    Dp = D_workpiece;
                       if (ui->lineEdit_ProdessLeft->text()=="")
                           R_left = 0;
                       else
                           R_left = ui->lineEdit_ProdessLeft->text().toDouble();//加工范围半径

                       if (ui->lineEdit_ProcessRight->text()=="")
                           R_right = 0;
                       else
                           R_right = ui->lineEdit_ProcessRight->text().toDouble();//加工口径另一值
                       // textBox18.text
                       if (R_left >= R_right)
                       { QMessageBox::information(this,"提示！","加工范围设定有误，左边框值不可大于右边框值，请重新设定加工范围！"); return; }

                       R_left=-D_workpiece/2;
                       R_right=D_workpiece/2;
                       if (ui->Lens_ao->isChecked())//凹凸判断
                           ao_tu = -1;
                       else
                           ao_tu = 1;

                       if (ui->comboBox_dataDistance->currentIndex()==0)

                           dist = 0.1;
                       else if(ui->comboBox_dataDistance->currentIndex()==1)
                           dist = 0.05;
                       else
                           dist=0.01;

                       if (ui->comboBox_toolRaidus->currentIndex()==0)
                           tool_r = 1;
                       else if (ui->comboBox_toolRaidus->currentIndex()==1)
                           tool_r = 3;
                       else
                           tool_r = 5;

//                       if (ui->radioButton_0degree->isChecked())//垂直抛
//                       {
//                           tool_r = 7;
//                       }


                       if (ui->Lens_ao->isChecked() || ui->Lens_tu->isChecked())
                       {
                           if (ui->Lens_ao->isChecked())
                           {
                               if (R > 1e-7)
                                   symbol = 1;
                               else
                                   symbol = -1;

                           }
                           if (ui->Lens_tu->isChecked())
                           {
                               if (R > 1e-7)
                                   symbol = -1;
                               else
                                   symbol = 1;
                           }

                         //  if (comboBox13.SelectedIndex == 1)
                               curvature_compensate = 1;
                         //  else if (comboBox13.SelectedIndex == 2)
                           //    curvature_compensate = 2;
                        //   else
                  }         //    curvature_compensate = 0;


    } catch (QString exception) {
        //QMessageBox::information(this,tr("提示！"),tr(err.1))
       QMessageBox::about(this,"Error",exception);
    }


 //   double A[20];
    double **data=Nc_data->aspheric2(press_distant,Cloth_thickness,curvature_compensate, first_position_feed, D_workpiece, Dp, C_motor_scale_factor, C_motor_offset, Lworkpiece_h, other_h, SAG, yuan_r, ao_tu, R_right, tool_r, constan_vc, constan_F, Vc_flag, F_flag, dist, symbol, n, vc, H, R_left, R, K, A);//生成代码
//double a=;


//double ** data2=Nc_data->Test2DArray(2,3);
//for(int i=0;i<2;i++)
//{
//    for(int j=0;j<3;j++)
//    {
//         qDebug()<<data[i][j];
//    }

//}


QVector<double>v;//

int r=Nc_data->row;
int c= Nc_data->colum;
Nc_Check.clear();
for (int i = 0; i < r; i++)//输入r*c的二维数组
    {
        v.clear();//子数组返回时要清除
        for (int j = 0; j <c; j++)
        {
            //cin >> temp;
            v.push_back(data[i][j]);

        }
        Nc_Check.push_back(v);
    }


// 释放内存
// for (int i = 0; i < 3; i++)
// {
//     delete[] data[i];
// }
 v.clear();
 delete[] data;
 delete Nc_data;

interference_check();//干涉检查


}
void MainWindow::interference_check()//干涉检查
{
    QVector <QVector<double>> RHO;//半径
    QVector <QVector<double>> THETA;//角度
    QVector <QVector<double>> Z;//刀具Z值
    QVector <QVector<double>> workpiece;//工件X,B,Zd值
     QVector <QVector<double>> X_ROT;//转动后X值
       QVector <QVector<double>> Y_ROT;//转动后Y值
         QVector <QVector<double>> Z_ROT;//转动后Z值
         QVector<int> X_D;
    QVector <double> temp;//
    bool interfere_flag=false;//干涉标志
    int interfer_number=0;

    double R=ui->lineEdit_ToolD->text().toDouble()/2/0.01;//抛光头半径分组
    double radius=ui->lineEdit_ToolD->text().toDouble()/2;//抛光头半径
    double offset=ui->lineEdit_Pressure->text().toDouble();//压缩量
    int COUNT=R;
    int toolLength=50;//5mm长的杆
    temp.clear();

    for(int j=(Nc_Check.size()-1)/2;j<Nc_Check.size();j++)
    {
        temp.clear();

            temp.push_back(QString::number(Nc_Check.at(j).at(4)*10,'f',1).toDouble());//X
            temp.push_back(Nc_Check.at(j).at(6));//ZD
            temp.push_back(Nc_Check.at(j).at(1));//B
            X_D.push_back(QString::number(Nc_Check.at(j).at(4)*10).toInt());

             workpiece.push_back(temp);

    }

    for(int j=0;j<=COUNT;j++)//RHO矩阵
    {
         temp.clear();
        for(int i=0;i<=COUNT;i++)
        {

            temp.push_back(i*0.01);
        }
        RHO.push_back(temp);

    }

    for(int j=0;j<RHO.size();j++)//THETA矩阵
    {
         temp.clear();
        for(int i=0;i<RHO.at(1).size();i++)
        {

            temp.push_back(0+2*(M_PI)/(RHO.size()-1)*j);
        }
        THETA.push_back(temp);

    }

    for(int j=0;j<RHO.size();j++)//Z矩阵
    {
         temp.clear();
        for(int i=0;i<RHO.at(1).size();i++)
        {
            //radius-qSqrt(

            temp.push_back(radius-qSqrt(qAbs(qPow(radius,2)-qPow(RHO.at(j).at(i)*qCos(THETA.at(j).at(i)),2)-qPow(RHO.at(j).at(i)*qSin(THETA.at(j).at(i)),2))));
        }
        Z.push_back(temp);

    }



    for(int j=0;j<toolLength;j++)//RHO矩阵增加圆柱杆部分
    {
         temp.clear();
        for(int i=0;i<RHO.at(1).size();i++)
        {

            temp.push_back(RHO.at(0).at(COUNT));
        }
        RHO.push_back(temp);

    }

    for(int j=0;j<toolLength;j++)//THETA矩阵增加圆柱杆部分
    {
         temp.clear();
        for(int i=0;i<RHO.at(1).size();i++)
        {

            temp.push_back(0+2*(M_PI)/(RHO.at(1).size()-1)*i);
        }
        THETA.push_back(temp);

    }

    for(int j=0;j<toolLength;j++)//Z矩阵增加圆柱杆部分
    {
         temp.clear();
        for(int i=0;i<RHO.at(1).size();i++)
        {
            //radius-qSqrt(

            temp.push_back(radius+(j+1)*0.1);
        }
        Z.push_back(temp);

    }


//矩阵旋转平移

   for (int k=0;k<workpiece.size();k++)
{
    for(int j=0;j<RHO.size();j++)//旋转后XYZ值
    {
         temp.clear();
        for(int i=0;i<RHO.at(1).size();i++)
        {

            temp.push_back(RHO.at(j).at(i)*qCos(THETA.at(j).at(i))*qCos(workpiece.at(k).at(2))+Z.at(j).at(i)*qSin(workpiece.at(k).at(2))+workpiece.at(k).at(0));
        }
        X_ROT.push_back(temp);

        temp.clear();
       for(int i=0;i<RHO.at(1).size();i++)
       {

           temp.push_back(RHO.at(j).at(i)*qCos(THETA.at(j).at(i))*qSin(workpiece.at(k).at(2))+Z.at(j).at(i)*qCos(workpiece.at(k).at(2))+workpiece.at(k).at(1));
       }
       Z_ROT.push_back(temp);

       temp.clear();
      for(int i=0;i<RHO.at(1).size();i++)
      {

          temp.push_back(RHO.at(j).at(i)*qSin(THETA.at(j).at(i)));
      }
      Y_ROT.push_back(temp);


    }

   int rho,index;
    for(int j=0;j<RHO.size();j++)//旋转后XYZ值
    {
        for(int i=0;i<RHO.at(1).size();i++)
        {
            rho=QString::number(sqrt(qPow(X_ROT.at(j).at(i),2)+qPow(Y_ROT.at(j).at(i),2))*10).toInt();
            index=X_D.indexOf(rho);
            if(Z_ROT.at(j).at(i)-(workpiece.at(index).at(1)-offset)<0.01)
            {
                interfere_flag=true;
                interfer_number++;
            }

        }

    }
 }

    //干涉校验



  if(interfere_flag==true)
   QMessageBox::information(this, "提示！", "加工参数干涉，请减小压缩量！");
  else
       QMessageBox::information(this, "提示！", "检查完成，无加工干涉！");



}



void MainWindow::on_pushButton_40_clicked()//生成非补正代码
{

bool produce_successflag;
    produce_successflag=produce_NC();//生成非补正NC代码
    if(produce_successflag==false)
       {
        QMessageBox::information(this,"提示","生成代码失败");
        return;
       }
   // produce_NC_interference_check();
    compensate_flag=false;
    produce_ncCode_flag2=false;
bool x_limit_flag;
ui->textEdit->clear();
max_x=qAbs(Nc_Data.at(0).at(0));
max_b=qAbs(Nc_Data.at(0).at(1));
max_z=qAbs(Nc_Data.at(0).at(5));

try {
    for (int i = 0; i <Nc_Data.size(); i++)
    {
        if (i == 0)
          {
            ui->textEdit->append("X" + QString::number(Nc_Data.at(i).at(4),'f',4) + " " + "Y" + QString::number(Nc_Data.at(i).at(7),'f',4) + " " + "Z" + QString::number(Nc_Data.at(i).at(5),'f',4) + " " + "B" + QString::number(Nc_Data.at(i).at(1),'f',4) + "  "  );// + "  " + "F" + (Convert.ToDouble(textBox4.Text) * 0.01 * NC_Data[i, 2]).ToString("f4") + "  " + "\n"));
         //  qDebug()<<i<<"X" + QString::number(Nc_Data.at(i).at(4),'f',4) + " " + "Y" + QString::number(Nc_Data.at(i).at(7),'f',4) + " " + "Z" + QString::number(Nc_Data.at(i).at(5),'f',4) + " " + "B" + QString::number(Nc_Data.at(i).at(1),'f',4) + "  " ;
        }
            else
           {
            ui->textEdit->append("X" + QString::number(Nc_Data.at(i).at(4),'f',4) + " " + "Y" + QString::number(Nc_Data.at(i).at(7),'f',4) + " " + "Z" + QString::number(Nc_Data.at(i).at(5),'f',4) + " " + "B" + QString::number(Nc_Data.at(i).at(1),'f',4) + "  " );// + "  " + "F" + (Convert.ToDouble(textBox4.Text) * 0.01 * NC_Data[i, 2] * 0.1 / Math.Abs(NC_Data[i, 0] - NC_Data[i - 1, 0])).ToString("f4") + "  " + "\n"));
       //     qDebug()<<i<<"X" + QString::number(Nc_Data.at(i).at(4),'f',4) + " " + "Y" + QString::number(Nc_Data.at(i).at(7),'f',4) + " " + "Z" + QString::number(Nc_Data.at(i).at(5),'f',4) + " " + "B" + QString::number(Nc_Data.at(i).at(1),'f',4) + "  " ;

        }
        if(max_x<=qAbs(Nc_Data.at(i).at(0)))
            max_x=qAbs(Nc_Data.at(i).at(0));
        if(max_b<=qAbs(Nc_Data.at(i).at(1)))
            max_b=qAbs(Nc_Data.at(i).at(1));
        if(max_z<=qAbs(Nc_Data.at(i).at(5)))
            max_z=qAbs(Nc_Data.at(i).at(5));

        //Nc_Data.at(i).at(4)=1;
        //               if (Nc_Data.at(i).at(0) > xlimit)
//                   x_limit_flag = true;
//               // wr.WriteLine(Convert.ToString("X" + NC_Data[i, 0].ToString("f4") + "  " + "B" + NC_Data[i, 1].ToString("f4") + "  " + "Z" + NC_Data[i, 5].ToString("f4") + "  " + "F" + (Convert.ToDouble(textBox4.Text) * 0.01 * NC_Data[i, 2]).ToString("f4") + "  " + "M302==" + NC_Data[i, 3].ToString("f4") + "  " + "\n"));
//               if (i == 0)
//                   Nc_Data[i][2] = Nc_Data.at(i).at(2);
//               else
//                   // NC_Data[j, 2] = Math.Sqrt(Math.Pow((NC_Data[j, 0] - NC_Data[j - 1, 0]), 2) + Math.Pow((NC_Data[j, 5] - NC_Data[j - 1, 5]), 2)) * Convert.ToDouble(str4.Trim()) * 10;//进给速度X Z联动

//                   Nc_Data[i][2] = qSqrt(qPow((NC_Data[i][0] - NC_Data[i - 1][ 0]), 2) + qPow((NC_Data[i][ 5] - NC_Data[i - 1][ 5]), 2)) * NC_Data[i][ 2] / qAbs(NC_Data[i][0] - NC_Data[i - 1][ 0]) * (ui->lineEdit_feedrate->text().toDouble()) * 0.01;//进给速度X Z联动

       // if(ui->radioButton_ChangedFeed->isChecked())
         //   Nc_Data.at(i).at(1)=Nc_Data.at(i).at(1)*0.01*(ui->lineEdit_feedrate->text().toDouble());
    }


} catch (EXCEPINFO err) {
    throw  err;

}

produce_ncCode_flag=true;//生成代码标志




}

void MainWindow::setyAxisRange(QCPRange)//设置画图范围
{
    this->ui->customPlot->yAxis->setRangeLower(-10);
    this->ui->customPlot->xAxis->setRangeLower(-10);

}

void MainWindow::on_pushButton_15_clicked()//读取面型误差数据
{


read_position->stop();
    ui->pushButton_15->setText("补正运算中...");
    QFileDialog* fd = new QFileDialog(this);//创建打开文件对话框
    QString path=QCoreApplication::applicationDirPath();
    QDir dir(path);//创建路径类
    if(!dir.exists("面型误差数据"))//创建路径
        dir.mkdir("面型误差数据");
  //     dir.setPath(dir.path()+"/加工参数");//设置路径
    QString fileName = fd->getOpenFileName(this,tr("打开文件"),path+"\\面型误差数据",tr("数据文件(*.csv;*.mod;*.MOD)"));
    if(fileName == "")
          {
        ui->pushButton_15->setText("导入");
        read_position->start();
            return;

         }
    QString name=fileName;
    ui->lineEdit_dataname->setText(name.remove(path+"/面型误差数据/").split(".").at(0));

  //  QDir dir = QDir::current();
    QFile file(dir.filePath(fileName));

    if(!file.open(QIODevice::ReadOnly))
         qDebug()<<"OPEN FILE FAILED";
    QTextStream * out = new QTextStream(&file);//文本流
    QStringList tempOption = out->readAll().split("\n");//每行以\n区分
    //QStringList tempba;
   // QVector<double> X,Y;
   qDebug()<< tempOption.count();
   QString filetype=name.split(".").at(1);//获取文件名后缀
   x.clear();
   zd.clear();
   if(filetype=="csv"||filetype=="CSV")//读取CSV文件
   {
    for(int i = 2 ; i < tempOption.count() ; i++)
    {
        if(tempOption.at(i)=="")
          break;
          x.push_back(QString(tempOption.at(i).split(",").at(0)).toDouble());//一行中的单元格以，区分
          zd.push_back(QString(tempOption.at(i).split(",").at(3)).toDouble());//一行中的单元格以，区分
    }
   }
   if(filetype=="mod"||filetype=="MOD")//读取MOD文件
   {
       for(int i = 34 ; i < tempOption.count()-3 ; i++)
       {
       if(tempOption.at(i)=="")
         break;
       if(i<(tempOption.count()-37)/2+34)
         x.push_back(QString(tempOption.at(i)).toDouble());//一行中的单元格以，区分
       else
         zd.push_back(QString(tempOption.at(i)).toDouble());//一行中的单元格以，区分
         //zd.push_back(QString(tempOption.at(i))).toDouble()*1000);//一行中的单元格以，区分
       }

   }
   // ui->customPlot_2->graph(0)->setData(x,zd);//填充画图数据
   // ui->customPlot_2->replot();//更新画图区域
   file.close();//操作完成后记得关闭文件// drawPlot_errdata(X,Y);

  int count=x.size();//面型数据X的行数
  int m_b = 0, m_yu = count - m_b, m_ave_zd;//x面型补正数据的x,

                QVector<double> zd_b, zd_yu, ave_zd, ave_zd1, x1, ave_zd2, ave_zd3, zd_d, x_d, zd_d2;//zd_b开始的一段面型误差值，zd_yu余下的一段面型误差值，zd_d取0.0105为间隔的面型误差值（存储加工范围），zd_d2取滤波后0.0105为间隔的面型误差值（存储加工范围），x_d0.0105间隔横坐标，ave_zd面型误差左右对称平均值，x1横坐标，ave_zd1滤波后的平均误差
                double max_ave_zd1 = 0, min_ave_zd1 = 0, PV, PV_rate = 0.3, std_revel,removal;// removal 为
                double curvature_compensate,n, R, K, dist, t = 0, vc, H, R_left, SAG, yuan_r, ao_tu, R_right, constan_vc, constan_F, symbol = 1, tool_r, D_workpiece, Dp;

                D_workpiece = ui->lineEdit_D->text().toDouble();//模仁柱面直径
               // QString A=QString::number(D_workpiece * 10 % 2);
                 if (QString::number(D_workpiece * 10 ).toInt()% 2==1)
                    {
                     D_workpiece = D_workpiece +0.1;
                     ui->lineEdit_D->setText(QString::number(D_workpiece));
                 }
 /****************************数据对此做均值********************************************************************/
                 for (int i = 0; i < count; i++)//找出X正值所在位置
                  {
                    if (x[i] > 0)
                    m_b = m_b + 1;//m_b是靠近零第一个X正值所在位置
                  }
             m_yu = count - m_b;
      if (m_b <= m_yu)//前半部分做均值
             {

                                    //zd_b = double[m_b];
                                    // zd_yu = new double[m_b];
                                   //  ave_zd = new double[m_b];
                                  //   x1 = new double[m_b];

                                     for (int i = 0; i < m_b; i++)//提取正并倒转
                                     {
                                         zd_b.push_back(zd[m_b - i - 1]);//
                                     }
                                     for (int i = 0; i < m_b; i++)//提取余下的
                                     {
                                         zd_yu.push_back(zd[m_b + i - 1]);//
                                     }
                                     for (int i = 0; i < m_b; i++)//求zd的均值
                                     {

                                         ave_zd.push_back((zd_b[i] + zd_yu[i]) / 2);
                                         x1.push_back(x[m_b - i - 1]);


                                     }



    }
      else//后半部分做均值
    {
                                   //  zd_b = new double[m_yu];
                                   //  zd_yu = new double[m_yu];
                                   //  ave_zd = new double[m_yu];
                                   //  x1 = new double[m_yu];

                                     for (int i = 0; i < m_yu; i++)//提取正并倒转
                                     {
                                         zd_b.push_back(zd[m_b - i - 1]);
                                     }
                                     for (int i = 0; i < m_yu; i++)//提取余下的
                                     {
                                         zd_yu.push_back(zd[m_b + i - 1]);
                                     }
                                     for (int i = 0; i < m_yu; i++)//求zd的均值
                                     {

                                         ave_zd.push_back((zd_b[i] + zd_yu[i]) / 2);
                                         x1.push_back(-x[m_b + i]);

                                     }

                                 }

 /************************************************************************************************/
 /******************************提取0.0105为间隔的X与zd*********************************************/

      int count_num = 0;//0.015的个数



   double process_radius=D_workpiece/2;  //加工半径

int data_size=(int)(D_workpiece/ 2 * 10000 / 105)+1;
   if (qAbs(x1[x1.size()-1]) > process_radius)//判断数据范围与补偿范围
                       {
                           for (int i = 0; i < ave_zd.size(); i++)
                           {
                               if (qAbs(x1[i]) >= count_num * 0.0105&&count_num<data_size)
                               {
                                   x_d.push_back(count_num * 0.0105);
                                   zd_d.push_back( ave_zd.at(i));
                                   zd_d2.push_back(ave_zd.at(i));
                                   count_num++;
                               }

                           }

                       }
                       else //数据范围小于补偿加工范围
                       {
                           for (int i = 0; i < ave_zd.size()-1; i++)
                           {
                               if( qAbs(x1[i]) >= count_num * 0.0105)
                               {
                                   x_d.push_back(count_num * 0.0105);
                                   zd_d.push_back( ave_zd.at(i));
                                   zd_d2.push_back(ave_zd.at(i));
                                   count_num++;
                               }

                           }
                           for (int i = count_num; i < data_size; i++)
                           {
                               x_d.push_back(count_num * 0.0105);
                               zd_d.push_back( ave_zd[ave_zd.size()-2]);
                               zd_d2.push_back(ave_zd[ave_zd.size()-2]);
                               count_num++;
                           }

                       }


   for (int i = 0; i < 10; i++)//滤波
           {
               zd_d.replace(i,(zd_d2[i] + zd_d2[i + 1] + zd_d2[i + 2] + zd_d2[i + 2]) / 4);
           }
           for (int i = 10; i < 50; i++)//滤波
           {
               zd_d.replace(i,(zd_d2[i - 1] + zd_d2[i - 2] + zd_d2[i - 3] + zd_d2[i] + zd_d2[i + 1] + zd_d2[i + 2] + zd_d2[i + 3]) / 7);

           }
          for (int i = 50; i < zd_d.size()-5; i++)//滤波
           {
               zd_d.replace(i,(zd_d2[i - 1] + zd_d2[i - 2] + zd_d2[i - 3] + zd_d2[i - 4] + zd_d2[i - 5] +zd_d2[i] + zd_d2[i + 1] + zd_d2[i + 2] + zd_d2[i + 3] + zd_d2[i +4] + zd_d2[i + 5]) / 11);
              // zd_d[i]= (zd_d2[i]+zd_d2[i+1])/2;
           }


  m_ave_zd = zd_d.size();
  for (int i = 0; i < m_ave_zd ; i++)//滤波
  {
    ave_zd1.push_back(zd_d[i]);
  }

//double *max_temp=std::max_element(std::begin(ave_zd1), std::end(ave_zd1));
//double *min_temp=std::min_element(std::begin(ave_zd1), std::end(ave_zd1));
// max_ave_zd1=*max_temp;  //ave_zd1中最大值
// min_ave_zd1=*min_temp;//ave_zd1中最小值
// PV = max_ave_zd1 - min_ave_zd1;

  double temp1 = ave_zd1[0], temp2 = ave_zd1[0];
//qDebug()<<ui->lineEdit_ProdessLeft->text().toDouble() * 10000 / 105;
//qDebug()<<ui->lineEdit_ProdessLeft->text().toDouble() * 10000 / 105;
  int c = (int)qAbs(ui->lineEdit_ProdessLeft->text().toDouble() * 10000 / 105) + 1;
                    int d =  (int)qAbs(ui->lineEdit_ProcessRight->text().toDouble() * 10000 / 105) + 1;
                    int compare_range = c;
                    if (c > d)
                    {
                        compare_range = c;

                    }
                    else
                    {
                        compare_range = d;
                    }


                    for (int i = 0; i < compare_range + 1 - 6; i++)//取zd1中最大最小值
                    {

                        // temp1 = ave_zd1[0];
                        //temp2 = ave_zd1[0];
                        if (temp1 < ave_zd1[i])
                        {
                            temp1 = ave_zd1[i];
                            // max_index = i;
                        //    c = i;
                        }

                        if (temp2 > ave_zd1[i])
                        {
                            temp2 = ave_zd1[i];
                            //  min_index = i;
                        }

                    }

                    for (int i = compare_range + 1 - 6; i < compare_range ; i++)//取zd1中最大最小值
                    {

                        // temp1 = ave_zd1[0];
                        //temp2 = ave_zd1[0];
                        if (temp1 < zd_d2[i])
                        {
                            temp1 = zd_d2[i];
                            // max_index = i;
                          //  c = i;
                        }

                        if (temp2 > zd_d2[i])
                        {
                            temp2 = zd_d2[i];
                            //  min_index = i;
                        }

                    }
                    max_ave_zd1 = temp1;
                    min_ave_zd1 = temp2;
                  //  max_ave_zd1 = -0.0000107559;
                    PV = max_ave_zd1 - min_ave_zd1;
                    std_revel = min_ave_zd1 - (PV * PV_rate);
                    for (int i = 0; i < m_ave_zd; i++)
             {
                 ave_zd2.push_back(std_revel - ave_zd1[i]);
             }

  /************************************************************************************************/

/**********************************************计算标准NC代码**************************************************/
                    bool produce_successflag;
                        produce_successflag=produce_NC2();//生成非补正NC代码
                        if(produce_successflag==false)
                           {
                            QMessageBox::information(this,"提示","生成代码失败");
                             ui->pushButton_15->setText("导入");

                            return;
                           }


/************************************************************************************************/

/******************************************************迭代补偿*****************************************/
if (ui->comboBox_toolRaidus->currentIndex()==0)
    removal = 0.006667;
else if (ui->comboBox_toolRaidus->currentIndex()==1)
    removal = 0.0125;
else
    removal = 0.0185;

std_revel = std_revel * 1000;
                  int num_cycle, num_cycle1;//初次抛光次数
                  double first_num;
                  double P_or_N = 1;//x2与x1正负要相同；
                  QVector<double> sim ;//= new double[NC_Data.Length / 14];
                  QVector<double> x2 ;//= new double[NC_Data.Length / 14];
                  QVector<double> y2;// = new double[NC_Data.Length / 14];
                  QVector<int> y2_temp;// = new int[NC_Data.Length / 14];
                  QVector<double>rate ;//= new double[NC_Data.Length / 14];
                  QVector<double>rate1;// = new double[NC_Data.Length / 7];
                  double SIM = 1, zd_temp_x_1 = 1;
                  double pressure_cycle_effect = 1, C_speed_cycle_effect = 1, P_speed_cycle_effect = 1,Cloth_diaman_effect=1;//压力，抛光轴速度和C轴速度,黄布与颗粒对抛光次数影响。
                  double multiple_rate = 1;//速度倍率
                  // num_cycle = Convert.ToInt16(-min_ave_zd1 / 0.0125);
                  if (ui->lineEdit_feedrate->text() != "")
                      multiple_rate = ui->lineEdit_feedrate->text().toDouble()*0.01;
                  if (ui->lineEdit_feedrate->text()!= "")//抛压力影响抛光次数
                      pressure_cycle_effect = qPow(qAbs(15/ui->lineEdit_feedrate->text().toDouble()), 0.65);
                  if (ui->lineEdit_constfeed->text()!= "")//C轴转速影响抛光次数
                      C_speed_cycle_effect = qPow(qAbs(150 / ui->lineEdit_constfeed->text().toDouble()), 0.5);
                  if (ui->lineEdit_Toolspeed->text()!= "")//抛光轴转速影响抛光次数
                      P_speed_cycle_effect = qPow(qAbs(180 / ui->lineEdit_Toolspeed->text().toDouble()), 0.5);
                 // if (this.comboBox12.SelectedIndex == 1)//黄布的规格选择
                  //    Cloth_diaman_effect = 0.555;

                  if (x1[2] * Nc_Data.at(2).at(4) > 0)
                                         P_or_N = 1;
                                     else
                                         P_or_N = -1;
                                   //  num_cycle = QString::number(zd_temp_x_1 / removal).toInt();
                                     // this.textBox17.Text = P_or_N.ToString();
                                     for (int i = 0; i < Nc_Data.size()/2 ; i++)//计算倍率
                                     {
                                         //x2[i] = P_or_N*NC_Data[NC_Data.Length / 10 + i, 4];
                                         x2.push_back(Nc_Data.at(Nc_Data.size()/2 + i).at(4));
                                         // x2[i] = 0.1 * i;
                                         //    y2[i] = a[0] + a[1] * x2[i] + a[2] * Math.Pow(x2[i], 2) + a[3] * Math.Pow(x2[i], 3) + a[4] * Math.Pow(x2[i], 4) + a[5] * Math.Pow(x2[i], 5) + a[6] * Math.Pow(x2[i], 6) + a[7] * Math.Pow(x2[i], 7) + a[8] * Math.Pow(x2[i], 8) + a[9] * Math.Pow(x2[i], 9) + a[10] * Math.Pow(x2[i], 10) + a[11] * Math.Pow(x2[i], 11) + a[12] * Math.Pow(x2[i], 7) + a[12] * Math.Pow(x2[i], 7) + a[13] * Math.Pow(x2[i], 13) + a[14] * Math.Pow(x2[i], 14) + a[15] * Math.Pow(x2[i], 15) + a[16] * Math.Pow(x2[i], 16) + a[17] * Math.Pow(x2[i], 17) + a[18] * Math.Pow(x2[i], 18) + a[19] * Math.Pow(x2[i], 19) + a[20] * Math.Pow(x2[i], 20);
                                         int index = 0;//s
                                         double temp = qAbs(x2[i] + P_or_N * x_d[0]);
                                         //listBox1.Items.Add("y"+i.ToString());
                                         for (int ii = 0; ii < x_d.size(); ii++)
                                         {
                                             double tep = qAbs(x2[i] + P_or_N * x_d[ii]);
                                             //  listBox1.Items.Add(tep.ToString());

                                             if (temp > tep)
                                             {
                                                 index = ii;
                                                 temp = tep;
                                                 // MessageBox.Show("1");
                                             }
                                            // if (Math.Abs(1 + x_d[ii]) < 0.1)//1附件的点为补偿基准点
                                             ///{
                                            //     zd_temp_x_1 = Math.Abs(ave_zd2[ii] * 1000);
                                             //}
                                             if(ave_zd1.size()<97)
                                                 zd_temp_x_1 = qAbs(ave_zd2[ave_zd1.size()-1]);
                                             else
                                                 zd_temp_x_1 = qAbs(ave_zd2[96]*1000);//1附件的点为补偿基准点

                                         }
                                         //if (radioButton26.Checked == true)//补正模式2选中
                                         //    zd_temp_x_1 = Math.Abs(PV / 2) * 1000;

                                         index = i * 10*100/105;
                                         // SIM = zd_temp_x_1 / 0.05;
                                         num_cycle = (int)(zd_temp_x_1 / removal);//抛光次数
                                         if( num_cycle<1)
                                              num_cycle=1;
                                         num_cycle1 = num_cycle;
                                         compens_cycle_time = QString::number(num_cycle).toDouble();

                                          first_num = QString::number(num_cycle1).toDouble() * removal;
                                         SIM = -num_cycle * removal;
                                        // SIM = 0.1;
                                                 y2.push_back(ave_zd2[index]);
                                             y2_temp.push_back(index);

                                                    rate.push_back(y2[i]/ SIM*1000);
                                                   //  qDebug()<<"rate"<<i <<":"<<y2[i]/ SIM*1000;


                                     }

                                     if (compens_cycle_time * pressure_cycle_effect * P_speed_cycle_effect * C_speed_cycle_effect * Cloth_diaman_effect * multiple_rate > 1)
                                                             {
                                            ui->lineEdit_ProcessCycle->setText(QString::number((int)(compens_cycle_time * pressure_cycle_effect * P_speed_cycle_effect * C_speed_cycle_effect * Cloth_diaman_effect * multiple_rate)));
                                                    ui->lineEdit_ProcessCycle_3->setText(QString::number((int)(compens_cycle_time * pressure_cycle_effect * P_speed_cycle_effect * C_speed_cycle_effect * Cloth_diaman_effect * multiple_rate)));

                          }
                            else
                              {

                                 ui->lineEdit_ProcessCycle->setText("1");
                                 ui->lineEdit_ProcessCycle_2->setText("1");


                               }

                                     // QFileDialog* fd = new QFileDialog();//创建打开文件对话框
                                      QString DATApath=QCoreApplication::applicationDirPath();
                                      QDir DATAdir(DATApath);//创建路径类

                                      QString DATAfileName = DATAdir.path()+"\\data1.csv";
                                              if(DATAfileName == "")
                                            return;
                                    //  QDir dir = QDir::current();
                                      QFile DATAfile(DATAdir.filePath(DATAfileName));

                                      if(!DATAfile.open(QIODevice::ReadOnly))
                                           qDebug()<<"OPEN FILE FAILED";
                                      QTextStream * DATAout = new QTextStream(&DATAfile);//文本流
                                      QStringList DATAm_datas= DATAout->readAll().split("\n");//每行以\n区分
//while(!DATAout->atEnd())
//{
//    DATAm_datas.push_back(DATAout->readLine());
//}
                                     DATAfile.close();//关闭文件
   QVector <QVector<double>> data;   //存放原始表格数据
   QVector <QVector<double>> data2;//存放迭代数据
   QVector<double> data3;//存放理论去除量
   QVector<double> temp;//存放原始表格一行
  QStringList list;//存放原始表格一行
  double data3addtemp;//data3
   for(int i=0;i<DATAm_datas.size();i++)
   {
       temp.clear();
        list=DATAm_datas.at(i).split(",");
        for(int k=0;k<list.size();k++)
        {
            temp.push_back(list.at(k).toDouble());//一行
        }
        data.push_back(temp);//一行放进去
   }

   for (int i = 0; i < x_d.size(); i++)//乘上倍率
   {

    if (i < 2098)
     {
        temp.clear();
        data3addtemp=0;
      for (int j = 0; j < rate.size(); j++)
       {
        temp.push_back(data.at(i).at(j) * rate[j]);//一行乘以倍率
         data3addtemp = data.at(i).at(j) * rate[j]+data3addtemp;//一行相加
         }
                data2.push_back(temp);
        data3.push_back(data3addtemp/ -0.37315 * SIM);
         }
        else
       {
         data3.push_back(data3addtemp);

        }

 }
  //*************************收敛运算*********************  //
                        double er1 = 0.03;
                      double er2 = 0.02;
                      double er3 = 0.01;
                      double sc1 = 0.05;
                      double sc2 = 0.03;
                      double sc3 = 0.01;
                      double sc4 = 0;
                      double sc = 0;
                      double max_er =  er3*1.1;
                      int k = 0;
                      int offset = 0;
                      while (max_er > er3 && k < 20)
                      {


                          max_er = er3 * 1.1;//最大误差赋初始值
                          for (int j = 0; j < (int)(x_d[x_d.size() - 1] * 10); j++)//倍率
                          {
                              //if (j <= 8)
                              //    offset = 0;
                              //else
                              //    offset = -8;
                              if (j < 220)
                              {

                                  if (qAbs(data3[j * 10 * 100 / 105 + offset] - ave_zd2[j * 10 * 100 / 105 + offset] * 1000) >= er1)//根据补正误差判断增减倍率量
                                      sc = sc1;
                                  else if (qAbs(data3[j * 10 * 100 / 105 + offset] - ave_zd2[j * 10 * 100 / 105 + offset] * 1000) >= er2 && qAbs(data3[j * 10 * 100 / 105 + offset] - ave_zd2[j * 10 * 100 / 105 + offset] * 1000) < er1)

                                      sc = sc2;
                                  else if (qAbs(data3[j * 10 * 100 / 105 + offset] - ave_zd2[j * 10 * 100 / 105 + offset] * 1000) >= er3 && qAbs(data3[j * 10 * 100 / 105 + offset] - ave_zd2[j * 10 * 100 / 105 + offset] * 1000) < er2)
                                      sc = sc3;
                                  else if (qAbs(data3[j * 10 * 100 / 105 + offset] - ave_zd2[j * 10 * 100 / 105 + offset] * 1000) <= er3)
                                      sc = sc4;
                                  if (qAbs(data3[j * 10 * 100 / 105 + offset] - ave_zd2[j * 10 * 100 / 105 + offset] * 1000) >= max_er)
                                      max_er = qAbs(data3[j * 10 * 100 / 105 + offset] - ave_zd2[j * 10 * 100 / 105 + offset] * 1000);

                                  if (data3[j * 10 * 100 / 105 + offset] <= ave_zd2[j * 10 * 100 / 105 + offset] * 1000)//补正误差为正时
                                  {
                                      if (rate[j] > 0.3)
                                      {
                                          if (j == 0 || j == 1)
                                              rate.replace(j,rate[j] - sc);
                                          else if (j == 2)
                                          {
                                              rate.replace(j,rate[j] - sc / 2);
                                              rate.replace(j-1,rate[j - 1] - sc / 2);
                                          }
                                          else
                                              rate.replace(j-1,rate[j - 1] - sc);
                                      }

                                  }
                                  else if (data3[j * 10 * 100 / 105 + offset] > ave_zd2[j * 10 * 100 / 105 + offset] * 1000)   //补正误差为负时
                                  {
                                      if (rate[j] < 5)
                                      {
                                          if (j == 0 || j == 1)
                                              rate.replace(j,rate[j] + sc);
                                          else if (j == 2)
                                          {
                                              rate.replace(j,rate[j] + sc / 2);
                                              rate.replace(j-1,rate[j - 1] + sc / 2);
                                          }
                                          else
                                              rate.replace(j-1,rate[j - 1] + sc);
                                      }
                                  }
                                }

                              }
                           data3.clear();//清除内容
                          for (int i = 0; i < x_d.size(); i++)//乘上倍率
                          {

                           if (i < 2098)
                            {
                               temp.clear();
                               data3addtemp=0;
                             for (int j = 0; j < rate.size(); j++)
                              {
                               temp.push_back(data.at(i).at(j) * rate[j]);//一行乘以倍率
                                data3addtemp = data.at(i).at(j) * rate[j]+data3addtemp;//一行相加
                                }
                                       data2.push_back(temp);
                               data3.push_back(data3addtemp/ -0.37315 * SIM);
                                }
                               else
                              {
                                data3.push_back(data3addtemp);

                               }

                        }

                              k++;


                      }

                     rate1.clear();//

                      rate1.push_back(1);
                                        for (int i = 0; i < Nc_Data.size()/2; i++)//乘上了外部倍率
                                        {
                                            rate1.push_back(rate[Nc_Data.size()/2 -1 - i]*external_rate[Nc_Data.size()/2 -1 - i]);

                                        }
                                        for (int i = Nc_Data.size()/2; i < Nc_Data.size() - 1; i++)
                                        {
                                            rate1.push_back(rate[i - Nc_Data.size()/2]*external_rate[i - Nc_Data.size()/2]);
                                           // qDebug()<<"rate"<<i - Nc_Data.size()/2<<":"<<rate[i - Nc_Data.size()/2];
                                        }
                                        //  rate1[NC_Data.Length / 5 - 1] = rate[ NC_Data.Length / 10-1];
                                       // QVector<double> F1;// = new double[NC_Data.Length];
                                       // rate_dist = new double[NC_Data.Length];
                                        F1.clear();
                                        for (int i = 0; i < Nc_Data.size(); i++)
                                        {
                                            F1.push_back( Nc_Data.at(i).at(2)/ (rate1[i]));
                                              //qDebug()<<"rate1"<<i<<":"<<rate1[i];
                                            //  qDebug()<<"F1"<<i<<":"<<F1[i];
                                            //rate_dist.pushback(rate1[i]);//
                                        }


 /**********************************************绘图*****************************************************/
QVector<double> X_plot;
QVector<double> avezd2_plot;
QVector<double> data3_plot;
QVector<double> err;
//QVector<double> err2;
for(int i=x_d.size()-10;i>0;i--)
{
    X_plot.push_back(-x_d.at(i));
    data3_plot.push_back(data3.at(i));
    avezd2_plot.push_back(ave_zd2.at(i)*1000);
    err.push_back(data3.at(i)-ave_zd2.at(i)*1000);
}
for(int i=0;i<x_d.size()-10;i++)
{
    X_plot.push_back(x_d.at(i));
    data3_plot.push_back(data3.at(i));
    avezd2_plot.push_back(ave_zd2.at(i)*1000);
    err.push_back(data3.at(i)-ave_zd2.at(i)*1000);
}

//ui->customPlot_2->addGraph();
auto maxX=std::max_element(std::begin(X_plot), std::end(X_plot));
auto minY=std::min_element(std::begin(data3_plot), std::end(data3_plot));
double max_x=*maxX;
double max_y=*minY;
//QList <QCPAxis*> axes;
//axes<<ui->customPlot_2->yAxis<<ui->customPlot_2->yAxis2;
//ui->customPlot_2->xAxis->setVisible(true);
//ui->customPlot_2->yAxis->setVisible(true);
//qDebug()<<min;
//qDebug()<<max;
ui->customPlot_2->xAxis->setRange(-qAbs(max_x)*1.5,qAbs(max_x)*1.5);
ui->customPlot_2->yAxis->setRange(-qAbs(max_y)*1.5,qAbs(max_y)*1.5);
//ui->customPlot_2

 //ui->customPlot_2 ->graph(0)->rescaleValueAxis(true);
//ui->customPlot_2->axisRect()->setRangeZoomAxes(axes);
//ui->customPlot_2->axisRect()->setRangeDragAxes(axes);
//ui->customPlot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

ui->customPlot_2->clearGraphs();

ui->customPlot_2->addGraph();
ui->customPlot_2->graph(0)->setPen(QPen(Qt::red)); // 曲线的颜色
ui->customPlot_2->graph(0)->data().clear();
 ui->customPlot_2->graph(0)->setData( X_plot,avezd2_plot);//填充画图数据

 ui->customPlot_2->addGraph();
  ui->customPlot_2->graph(1)->setPen(QPen(Qt::black)); // 曲线的颜色
  ui->customPlot_2->graph(1)->data().clear();
 ui->customPlot_2->graph(1)->setData( X_plot,data3_plot);//填充画图数据

 ui->customPlot_2->addGraph();
 ui->customPlot_2->graph(2)->setPen(QPen(Qt::blue)); // 曲线的颜色
 ui->customPlot_2->graph(2)->data().clear();
 ui->customPlot_2->graph(2)->setData( X_plot,err);//填充画图数据

 ui->customPlot_2->legend->setVisible(true);//设置图例可用

 ui->customPlot_2->graph(0)->setName("实际应去除量");
 ui->customPlot_2->graph(1)->setName("理论去除量");
 ui->customPlot_2->graph(2)->setName("补正误差");
 ui->customPlot_2->replot();//更新画图区域

compensate_flag=true;
 ui->pushButton_15->setText("导入");
 read_position->start();
 QMessageBox::information(this,"提示","补正运算完成！");
//
}


















void MainWindow::on_pushButton_41_clicked()//导入非补正代码
{

    if(produce_ncCode_flag==false)//判断是否先生成数控代码
    {
        QMessageBox::information(this,"提示！","请先生成非补正代码！");
                return;
    }

    if(max_x>qAbs(xlimit_left))
    {
        QMessageBox::information(this,"提示！","X轴行程不足！");
                return;
    }
    if(max_b>qAbs(blimit_left))
    {
        QMessageBox::information(this,"提示！","Z轴行程不足！");
                return;
    }
    if(max_z>qAbs(zlimit_up))
    {
        QMessageBox::information(this,"提示！","Z轴行程不足！");
                return;
    }

    ui->pushButton_41->setText("导入中...");
    double t=0;//加工时间
    double t_feed=0;//进刀和退刀时间和
    double feedrate=ui->lineEdit_feedrate->text().trimmed().toDouble()*0.01;//进给倍率
    int n=ui->lineEdit_ProcessCycle_2->text().toInt();//标准加工次数
    QString text_data=ui->textEdit->toPlainText();
   QStringList data_list=text_data.split("\n");
   QVector<double> temp;
 //  QString toolspeed=ui->lineEdit_Toolspeed->text().trimmed();
   // Hz_start(1,toolspeed);
 //  qDebug()<<"Nc:"<<Nc_Data.at(1).at(4);
   if(ui->radioButton_ChangedFeed->isChecked())
       feedrate=ui->lineEdit_feedrate->text().trimmed().toDouble()*0.01;//进给倍率
   else {
       feedrate=1;//进给倍率
        }
   for(int i=0;i<data_list.size();i++)//替换数控代码容器里的数据
   {
       temp=Nc_Data.at(i);
        temp.replace(4,data_list.at(i).mid(data_list.at(i).indexOf("X")+1,data_list.at(i).indexOf("Y")-data_list.at(i).indexOf("X")-1).toDouble());
         temp.replace(7,data_list.at(i).mid(data_list.at(i).indexOf("Y")+1,data_list.at(i).indexOf("Z")-data_list.at(i).indexOf("Y")-1).toDouble());
         temp.replace(5,data_list.at(i).mid(data_list.at(i).indexOf("Z")+1,data_list.at(i).indexOf("B")-data_list.at(i).indexOf("Z")-1).toDouble());
         temp.replace(1,data_list.at(i).split("B").at(1).toDouble());
   //  qDebug()<<"Nc:"<<data_list.at(i);
   //   qDebug()<<"B:"<<data_list.at(i).mid(data_list.at(i).indexOf("B")+1,data_list.at(i).indexOf("Z")-data_list.at(i).indexOf("B")-1);
     //  qDebug()<<"B-Z:"<<data_list.at(i).indexOf("Z")-data_list.at(i).indexOf("B");
     // temp.replace(5,data_list.at(i).split("Z").at(1).toDouble());
    //  qDebug()<<"BINDEX:"<<data_list.at(i).indexOf("B");
  //    qDebug()<<"Z:"<<data_list.at(i).split("Z").at(1).toDouble();

//        if(i>0)//进给速度乘倍率
//        {
//            if(ui->radioButton_ChangedFeed->isChecked())
//            temp.replace(2,temp.at(2)*feedrate);
//        }

        Nc_Data.replace(i,temp);
    //    qDebug()<<"Nc2:"<<Nc_Data.at(i);
   }
 //  read_position->blockSignals(true);
//if(read_position->isActive())
//read_position->stop();//停止读位置
//tim
//read_position->setInterval(0);
//                           PMAC->SendCommand("OPEN PROG 1");
//                           PMAC->SendCommand("CLEAR");
//                           // wr->WriteLine("S150");
//                           PMAC->SendCommand("DISABLE PLC6");
//                           PMAC->SendCommand("FRAX(X,Z)");
//                           PMAC->SendCommand("G90 G01");
//                           PMAC->SendCommand("P26=1");
//                           PMAC->SendCommand("P27=1");
//                           // wr->WriteLine("WHILE(P25<" + QString::number(n) + ")");
//                           //PMAC->SendCommand("P50=" + QString::number(NC_Data[0, 5]));
//                           PMAC->SendCommand("P50=" + QString::number(Nc_Data.at(0).at(5)));
//                           PMAC->SendCommand("X" + QString::number(Nc_Data.at(0).at(0)) + "  " + "B" + QString::number(Nc_Data.at(0).at(1)) + "  " + "F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");

//                          // PMAC->SendCommand(QString::number("X" + NC_Data[0, 0] + "  " + "B" + NC_Data[0, 1] + "  " + "F" + NC_Data[0, 2]->ToString()->Trim() + "  " + "M113==" + (NC_Data[0, 4] * 1/dist)->ToString("f4") + "  " + "M213==" + (NC_Data[0, 6] * 1000)->ToString("f4") + "  " + "\n"));
//                           //t = t ;+ Math->Abs(NC_Data[0, 0]) / 100
//                           if (Nc_Data.at(0).at(0) > 0)
//                               PMAC->SendCommand("WHILE((" + QString::number(Nc_Data.at(0).at(0)*10000,'f',4) + "-M162/32/96)>100" + ")");
//                           else
//                               PMAC->SendCommand("WHILE((" + QString::number(Nc_Data.at(0).at(0)*10000,'f',4) + "-M162/32/96)<-100" + ")");
//                           PMAC->SendCommand("P10=0");
//                           PMAC->SendCommand("DWELL 10");
//                           PMAC->SendCommand("ENDWHILE");
//                           PMAC->SendCommand("P10=1");
//                           PMAC->SendCommand("CLOSE");

                           //运动到初始加工位置
                           PMAC->SendCommand("OPEN PROG 7");
                           PMAC->SendCommand("CLEAR");
                           PMAC->SendCommand("FRAX(X,Z)");
                           PMAC->SendCommand("G90 G01");

                           PMAC->SendCommand("X" + QString::number(Nc_Data.at(0).at(0)) + "  "+"Y" + QString::number(Nc_Data.at(0).at(7)) + "  " + "B" + QString::number(Nc_Data.at(0).at(1)) + "  " + "F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");

                           PMAC->SendCommand("CLOSE");

                           PMAC->SendCommand("OPEN PROG 8");
                           PMAC->SendCommand("CLEAR");
                           PMAC->SendCommand("FRAX(X,Z)");
                           PMAC->SendCommand("G90 G01");

                           PMAC->SendCommand("X" + QString::number(-Nc_Data.at(0).at(0)) + "  " + "Y" + QString::number(Nc_Data.at(0).at(7)) + "  " +"B" + QString::number(-Nc_Data.at(0).at(1)) + "  " + "F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");
                            PMAC->SendCommand("CLOSE");

           if (n == 1)
                          {

                           PMAC->SendCommand("OPEN PROG 2");
                            PMAC->SendCommand("CLEAR");
                            PMAC->SendCommand("FRAX(X,Z)");
                            PMAC->SendCommand("M46=1");//绿灯亮
                            PMAC->SendCommand("M2=1");//抛光轴转
                        //    PMAC->SendCommand("PSET Z(P50)");//加工程序
                         PMAC->SendCommand("G90 G01 P25=0 P32=0 M502==" + QString::number((ui->lineEdit_Toolspeed->text().toDouble()) * U_motor_scale_factor + U_motor_offset));

                                                      //wr.WriteLine("P25=0");
                          if (ui->comboBox_ToolDirect->currentIndex()==0)//抛光轴转动方向
                            {
                               PMAC->SendCommand("M44==0");

                            }
                           else
                          {
                             PMAC->SendCommand("M44==1");
                            }

                       PMAC->SendCommand("M5=1");//开抛光液
                            PMAC->SendCommand("X" + QString::number(Nc_Data.at(0).at(0)) + "  " + "B" + QString::number(Nc_Data.at(0).at(1)) + "  " + "F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");
                       qDebug()<<("X" + QString::number(Nc_Data.at(0).at(0)) + "  " + "B" + QString::number(Nc_Data.at(0).at(1)) + "  " + "F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");

                            //  t_feed=qSqrt(qPow((Nc_Data.at(0).at(0)), 2) + qPow((Nc_Data.at(0).at(5)), 2)) / Nc_Data.at(0).at(2);//(Math.Abs(Nc_Data[i, 0] - Nc_Data[i - 1, 0])) / Nc_Data[i, 2];
                             t_feed=t_feed+qAbs(Nc_Data.at(0).at(0)) / Nc_Data.at(0).at(2);
                            PMAC->SendCommand("Z" + QString::number(Nc_Data.at(0).at(5)+5) + "  " + "F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");
                            qDebug()<<("Z" + QString::number(Nc_Data.at(0).at(5)+5) + "  " + "F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");

                             PMAC->SendCommand("DWELL 0");
                          PMAC->SendCommand("G97 S" +ui->lineEdit_constCSpeed->text());
                          //  PMAC->SendCommand("G97");
                            PMAC->SendCommand("DWELL0");
                            if (ui->comboBox_Cdirect->currentIndex()==0)//工件转动方向
                             {
                             PMAC->SendCommand("M03");
                            // PMAC->SendCommand("M4=0");
                             }
                            else
                              {
                               // PMAC->SendCommand("M3=0");
                                PMAC->SendCommand("M04");
                               }
                                     PMAC->SendCommand("P26=1");
                                PMAC->SendCommand("P27=0");
                         //      PMAC->SendCommand("M302==" +QString::number(Nc_Data.at(1).at(3),'f',4));
                                PMAC->SendCommand("M45=1");//抛光轴转

                                PMAC->SendCommand("Z" + QString::number(Nc_Data.at(0).at(5)) + "  " + "F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");
                                qDebug()<<("Z" + QString::number(Nc_Data.at(0).at(5)) + "  " + "F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");

                                t_feed=t_feed+qAbs(Nc_Data.at(0).at(5)) / Nc_Data.at(0).at(2);//(Math.Abs(Nc_Data[i, 0] - Nc_Data[i - 1, 0])) / Nc_Data[i, 2];

                              PMAC->SendCommand("WHILE(P25<" +QString::number(n) + ")");
                               qDebug()<<("WHILE(P25<" +QString::number(n) + ")");
                            PMAC->SendCommand("P27=P27+1");
                              for (int i = 0; i < Nc_Data.size(); i++)
                             {
                                  if(i==0)
                                 {
                                 PMAC->SendCommand("X" + QString::number(Nc_Data.at(i).at(0),'f',4) + "  "+"Y" + QString::number(Nc_Data.at(i).at(7),'f',4) + "  " + "B" +QString::number(Nc_Data.at(i).at(1),'f',4) + "  " + "Z" + QString::number(Nc_Data.at(i).at(5),'f',4) + "  " + "F" + QString::number(Nc_Data.at(i).at(2),'f',4) + "  " + "\n");// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 1 / dist).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));
                                 qDebug()<<("X" + QString::number(Nc_Data.at(i).at(0),'f',4) + "  "+"Y" + QString::number(Nc_Data.at(i).at(7),'f',4) + "  " + "B" +QString::number(Nc_Data.at(i).at(1),'f',4) + "  " + "Z" + QString::number(Nc_Data.at(i).at(5),'f',4) + "  " + "F" + QString::number(Nc_Data.at(i).at(2),'f',4) + "  " + "\n");// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 1 / dist).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));

                                  }
                                      else
                                  {
                             PMAC->SendCommand("X" + QString::number(Nc_Data.at(i).at(0),'f',4) + "  "+"Y" + QString::number(Nc_Data.at(i).at(7),'f',4) + "  " + "B" +QString::number(Nc_Data.at(i).at(1),'f',4) + "  " + "Z" + QString::number(Nc_Data.at(i).at(5),'f',4) + "  " + "F" + QString::number(Nc_Data.at(i).at(2)*feedrate,'f',4) + "  " + "\n");// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 1 / dist).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));
                            qDebug()<<("X" + QString::number(Nc_Data.at(i).at(0),'f',4) + "  "+"Y" + QString::number(Nc_Data.at(i).at(7),'f',4) + "  " + "B" +QString::number(Nc_Data.at(i).at(1),'f',4) + "  " + "Z" + QString::number(Nc_Data.at(i).at(5),'f',4) + "  " + "F" + QString::number(Nc_Data.at(i).at(2)*feedrate,'f',4) + "  " + "\n");// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 1 / dist).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));
                                }
                            if (i > 0)
                              t = t + qAbs(qSqrt(qPow((Nc_Data.at(i).at(0) - Nc_Data.at(i-1).at(0)), 2) + qPow((Nc_Data.at(i).at(5) - Nc_Data.at(i-1).at(5)), 2)) / (Nc_Data.at(i).at(2)*feedrate));//(Math.Abs(Nc_Data[i, 0] - Nc_Data[i - 1, 0])) / Nc_Data[i, 2];
                            }
                            PMAC->SendCommand("P25=P25+1");
                            PMAC->SendCommand("ENDWHILE");
                            qDebug()<<("ENDWHILE");

                            PMAC->SendCommand("Z" + QString::number(Nc_Data.at(Nc_Data.size()-1).at(5)+5,'f',4)+"F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");
                            PMAC->SendCommand("DWELL 0");
                            t_feed=t_feed+qAbs(Nc_Data.at(Nc_Data.size()-1).at(5)) / Nc_Data.at(0).at(2);
                            PMAC->SendCommand("M45=0");//抛光轴停
                              PMAC->SendCommand("M05");//C轴停
                               PMAC->SendCommand("M5=0");//抛光液停
                            PMAC->SendCommand("Z0 F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");

                            PMAC->SendCommand("X0B0F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");
                           t_feed=t_feed+qAbs(Nc_Data.at(Nc_Data.size()-1).at(0)) / Nc_Data.at(0).at(2);
                          PMAC->SendCommand("DWELL 0");
                          PMAC->SendCommand("P14=1");
                          PMAC->SendCommand("P32=1");
                        //     PMAC->SendCommand("M45=0");
                           PMAC->SendCommand("M7=1");//灯亮
                           PMAC->SendCommand("M113=0 M213=0");
                           PMAC->SendCommand("M163=0 ");
                            PMAC->SendCommand("M46=0 ");//绿灯灭
                            PMAC->SendCommand("M2=0");//抛光轴停
                         PMAC->SendCommand("ENABLE PLC6");
                         PMAC->SendCommand("CLOSE");






                  }
           else
                  {
                   PMAC->SendCommand("OPEN PROG 2");
                   PMAC->SendCommand("CLEAR");
                   PMAC->SendCommand("FRAX(X,Z)");
                    PMAC->SendCommand("M46=1");//绿灯亮
                    PMAC->SendCommand("M2=1");//抛光轴转
                 //  PMAC->SendCommand("PSET Z(P50)");//加工程序
                   PMAC->SendCommand("G90 G01 P25=0 P32=0 M502==" + QString::number((ui->lineEdit_Toolspeed->text().toDouble()) * U_motor_scale_factor + U_motor_offset));
                                                      //wr.WriteLine("P25=0");

                   if (ui->comboBox_ToolDirect->currentIndex()==0)//抛光轴转动方向
                     {
                        PMAC->SendCommand("M44==0");

                     }
                    else
                   {
                      PMAC->SendCommand("M44==1");
                   }

                    PMAC->SendCommand("M5=1");//开抛光液
                     PMAC->SendCommand("X" + QString::number(Nc_Data.at(0).at(0)) + "  " + "B" + QString::number(Nc_Data.at(0).at(1)) + "  " + "F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");
qDebug()<<("X" + QString::number(Nc_Data.at(0).at(0)) + "  " + "B" + QString::number(Nc_Data.at(0).at(1)) + "  " + "F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");

                     t_feed=qSqrt(qPow((Nc_Data.at(0).at(0)), 2)) / Nc_Data.at(0).at(2);//(Math.Abs(Nc_Data[i, 0] - Nc_Data[i - 1, 0])) / Nc_Data[i, 2];

                     PMAC->SendCommand("Z" + QString::number(Nc_Data.at(0).at(5)+5) + "  " + "F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");
                 qDebug()<<("Z" + QString::number(Nc_Data.at(0).at(5)+5) + "  " + "F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");

                     //  t_feed=t_feed+qSqrt(qPow((Nc_Data.at(0).at(5)), 2)) / Nc_Data.at(0).at(2);
                      PMAC->SendCommand("DWELL 0");
                     PMAC->SendCommand("G97 S" +ui->lineEdit_constCSpeed->text());

                     //PMAC->SendCommand("G97");
                     PMAC->SendCommand("DWELL0");
                     if (ui->comboBox_Cdirect->currentIndex()==0)//工件转动方向
                      {
                      PMAC->SendCommand("M03");
                     // PMAC->SendCommand("M4=0");
                      }
                     else
                       {
                        // PMAC->SendCommand("M3=0");
                         PMAC->SendCommand("M04");
                        }
                       PMAC->SendCommand("P26=1");
                       PMAC->SendCommand("P27=0");
                  //      PMAC->SendCommand("M302==" +QString::number(Nc_Data.at(1).at(3),'f',4));
                         PMAC->SendCommand("M45=1");
                         PMAC->SendCommand("Z" + QString::number(Nc_Data.at(0).at(5)) + "  " + "F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");
                        qDebug()<<("Z" + QString::number(Nc_Data.at(0).at(5)) + "  " + "F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");

                         t_feed=t_feed+qAbs(Nc_Data.at(0).at(5)) / Nc_Data.at(0).at(2);//(Math.Abs(Nc_Data[i, 0] - Nc_Data[i - 1, 0])) / Nc_Data[i, 2];

                if (n % 2 == 1)
               PMAC->SendCommand("WHILE(P25<" + QString::number((n - 1) / 2) + ")");
                 else
             PMAC->SendCommand("WHILE(P25<" + QString::number(n / 2) + ")");
                qDebug()<<("WHILE(P25<" + QString::number((n - 1) / 2) + ")");
           PMAC->SendCommand("P27=P27+1");
        for (int i = 0; i < Nc_Data.size(); i++)
          {
            if(i==0)
           {
                PMAC->SendCommand("X" + QString::number(Nc_Data.at(i).at(0),'f',4) + "  " + "B" +QString::number(Nc_Data.at(i).at(1),'f',4) + "  " + "Z" + QString::number(Nc_Data.at(i).at(5),'f',4) + "  " + "F" + QString::number(Nc_Data.at(i).at(2),'f',4) + "  " + "\n");// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 1 / dist).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));
                qDebug()<<("X" + QString::number(Nc_Data.at(i).at(0),'f',4) + "  " + "B" +QString::number(Nc_Data.at(i).at(1),'f',4) + "  " + "Z" + QString::number(Nc_Data.at(i).at(5),'f',4) + "  " + "F" + QString::number(Nc_Data.at(i).at(2),'f',4) + "  " + "\n");// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 1 / dist).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));

            }
                else
          {
                PMAC->SendCommand("X" + QString::number(Nc_Data.at(i).at(0),'f',4) + "  " + "B" +QString::number(Nc_Data.at(i).at(1),'f',4) + "  " + "Z" + QString::number(Nc_Data.at(i).at(5),'f',4) + "  " + "F" + QString::number(Nc_Data.at(i).at(2)*feedrate,'f',4) + "  " + "\n");// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 1 / dist).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));
                qDebug()<<("X" + QString::number(Nc_Data.at(i).at(0),'f',4) + "  " + "B" +QString::number(Nc_Data.at(i).at(1),'f',4) + "  " + "Z" + QString::number(Nc_Data.at(i).at(5),'f',4) + "  " + "F" + QString::number(Nc_Data.at(i).at(2)*feedrate,'f',4) + "  " + "\n");// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 1 / dist).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));

            }

           if (i > 0)
             t = t + qSqrt(qPow((Nc_Data.at(i).at(0) - Nc_Data.at(i-1).at(0)), 2) + qPow((Nc_Data.at(i).at(5) - Nc_Data.at(i-1).at(5)), 2)) / (Nc_Data.at(i).at(2)*feedrate);//(Math.Abs(Nc_Data[i, 0] - Nc_Data[i - 1, 0])) / Nc_Data[i, 2];
            }
           PMAC->SendCommand("P27=P27+1");
          for (int i =  Nc_Data.size() - 2; i >= 0; i--)//代码倒转
     {
          PMAC->SendCommand("X" + QString::number(Nc_Data.at(i).at(0),'f',4) + "  " + "B" +QString::number(Nc_Data.at(i).at(1),'f',4) + "  " + "Z" + QString::number(Nc_Data.at(i).at(5),'f',4) + "  " + "F" + QString::number(Nc_Data.at(i+1).at(2)*feedrate,'f',4) + "  " + "\n");// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 1 / dist).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));
      qDebug()<<("X" + QString::number(Nc_Data.at(i).at(0),'f',4) + "  " + "B" +QString::number(Nc_Data.at(i).at(1),'f',4) + "  " + "Z" + QString::number(Nc_Data.at(i).at(5),'f',4) + "  " + "F" + QString::number(Nc_Data.at(i+1).at(2)*feedrate,'f',4) + "  " + "\n");// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 1 / dist).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));

       // PMAC->SendCommand(Convert.ToString("X" + Nc_Data[i, 0].ToString("f4") + "  " + "B" + Nc_Data[i, 1].ToString("f4") + "  " + "Z" + Nc_Data[i, 5].ToString("f4") + "  " + "F" + Nc_Data[i + 1, 2].ToString("f4") + "  " + "\n"));// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 10).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));
     }
           PMAC->SendCommand("P25=P25+1");
     PMAC->SendCommand("ENDWHILE");
 qDebug()<<("ENDWHILE");
        if (n % 2 == 1)
        {
                                                          //    PMAC->SendCommand("COMMAND\"&1B9R\"");
                                                          //    PMAC->SendCommand("CLOSE");
                                                          //    PMAC->SendCommand("OPEN PROG 9 CLEAR");

        PMAC->SendCommand("P27=P27+1");
        for (int i = 0; i < Nc_Data.size(); i++)
         {
         PMAC->SendCommand("X" + QString::number(Nc_Data.at(i).at(0),'f',4) + "  " + "B" +QString::number(Nc_Data.at(i).at(1),'f',4) + "  " + "Z" + QString::number(Nc_Data.at(i).at(5),'f',4) + "  " + "F" + QString::number(Nc_Data.at(i).at(2)*feedrate,'f',4) + "  " + "\n");// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 1 / dist).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));                                                              // if (i > 0)                                                              //   t = t + qSqrt(qPow((Nc_Data.at(i).at(0) - Nc_Data.at(i-1).at(0)), 2) + qPow((Nc_Data.at(i).at(5) - Nc_Data.at(i-1).at(5)), 2)) / Nc_Data.at(i).at(2);//(Math.Abs(Nc_Data[i, 0] - Nc_Data[i - 1, 0])) / Nc_Data[i, 2];
qDebug()<<("X" + QString::number(Nc_Data.at(i).at(0),'f',4) + "  " + "B" +QString::number(Nc_Data.at(i).at(1),'f',4) + "  " + "Z" + QString::number(Nc_Data.at(i).at(5),'f',4) + "  " + "F" + QString::number(Nc_Data.at(i).at(2)*feedrate,'f',4) + "  " + "\n");// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 1 / dist).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));                                                              // if (i > 0)                                                              //   t = t + qSqrt(qPow((Nc_Data.at(i).at(0) - Nc_Data.at(i-1).at(0)), 2) + qPow((Nc_Data.at(i).at(5) - Nc_Data.at(i-1).at(5)), 2)) / Nc_Data.at(i).at(2);//(Math.Abs(Nc_Data[i, 0] - Nc_Data[i - 1, 0])) / Nc_Data[i, 2];

        }

        PMAC->SendCommand("Z" + QString::number(Nc_Data.at(Nc_Data.size()-1).at(5)+5,'f',4)+"F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");
        PMAC->SendCommand("DWELL 0");

        t_feed=t_feed+qAbs(Nc_Data.at(Nc_Data.size()-1).at(5))/Nc_Data.at(0).at(2);//Z进给时间
        t_feed=t_feed+qAbs(Nc_Data.at(Nc_Data.size()-1).at(0))/Nc_Data.at(0).at(2);//X进给时间
        }
        else
        {
            PMAC->SendCommand("Z" + QString::number(Nc_Data.at(0).at(5)+5,'f',4)+"F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");
            PMAC->SendCommand("DWELL 0");

            t_feed=t_feed+qAbs(Nc_Data.at(0).at(5))/Nc_Data.at(0).at(2);//Z进给时间
            t_feed=t_feed+qAbs(Nc_Data.at(Nc_Data.size()-1).at(0))/Nc_Data.at(0).at(2);//X进给时间
        }



         PMAC->SendCommand("M45=0");
         PMAC->SendCommand("M05");
          PMAC->SendCommand("M5=0");//停抛光液
         PMAC->SendCommand("Z0 F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");

         PMAC->SendCommand("X0B0F" +QString::number(Nc_Data.at(0).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0).at(6)*1000) + "  " + "\n");

    PMAC->SendCommand("DWELL 0");
    PMAC->SendCommand("P14=1");
    PMAC->SendCommand("P32=1");

    PMAC->SendCommand("M7=1");
    PMAC->SendCommand("M113=0 M213=0");
   PMAC->SendCommand("M163=0 ");
   PMAC->SendCommand("ENABLE PLC6");
    PMAC->SendCommand("M46=0 ");//绿灯灭
    PMAC->SendCommand("M2=0");//抛光轴停
  PMAC->SendCommand("CLOSE");
 }
//read_position->start();//开始读位置
      //     read_position->setInterval(200);
           process_time=t*n+t_feed;
           QMessageBox::information(this, "提示！", "加工时间："+QString::number(process_time,'f',2)+"分钟");

ui->pushButton_41->setText("导入非补正代码");
download_code_flag=true;//导入代码标志


}



void MainWindow::on_pushButton_42_clicked()//生成补正代码
{

    if(compensate_flag==false)
    {
       QMessageBox::information(this, "提示", "请先导入面型误差数据！");
       return ;
    }

    bool x_limit_flag;
    ui->textEdit_2->clear();
    double D_workpiece=0;
    double R_left=0;
    double R_right = 0;
    double dist=0.1;
    D_workpiece = ui->lineEdit_D->text().toDouble();
   if (ui->lineEdit_ProdessLeft->text()=="")
                              R_left = 0;
                          else
                              R_left = ui->lineEdit_ProdessLeft->text().toDouble();//加工范围半径

                          if (ui->lineEdit_ProcessRight->text()=="")
                              R_right = 0;
                          else
                              R_right = ui->lineEdit_ProcessRight->text().toDouble();//加工口径另一值
     if (ui->comboBox_dataDistance->currentIndex()==0)

                              dist = 0.1;
                          else if(ui->comboBox_dataDistance->currentIndex()==1)
                              dist = 0.05;
                          else
                              dist=0.01;

               int c = (int)(qRound((R_right - R_left) / dist));//输出代码行数-1
               int a = (int)(qRound(D_workpiece / dist));//代码数组行数-1
               int d = (int)(qRound(R_left / dist));

               max_x=qAbs(Nc_Data.at(d + a / 2).at(0));
               max_b=qAbs(Nc_Data.at(d + a / 2).at(1));
               max_z=qAbs(Nc_Data.at(d + a / 2).at(5));
    try {
        for (int i = 0; i <c+1; i++)
        {
            if (i == 0)
               ui->textEdit_2->append("X" + QString::number(Nc_Data.at(i + d + a / 2).at(4),'f',4) + " " + "Y" + QString::number(Nc_Data.at(i + d + a / 2).at(7),'f',4) + " " + "Z" + QString::number(Nc_Data.at(i + d + a / 2).at(5),'f',4)  + " "+ "B" + QString::number(Nc_Data.at(i + d + a / 2).at(1),'f',4)  + " " + "F" + QString::number(F1.at(i),'f',4));
            else
                ui->textEdit_2->append("X" + QString::number(Nc_Data.at(i + d + a / 2).at(4),'f',4) + " " + "Y" + QString::number(Nc_Data.at(i + d + a / 2).at(7),'f',4) + " " + "Z" + QString::number(Nc_Data.at(i + d + a / 2).at(5),'f',4) + " "+ "B" + QString::number(Nc_Data.at(i + d + a / 2).at(1),'f',4)  + " " + "F" + QString::number(ui->lineEdit_feedrate->text().toDouble() * 0.01 * F1.at(i+d+a/2) * dist / qAbs(Nc_Data.at(i+d+a/2).at(0) - Nc_Data.at(i+d+a/2-1).at(0)),'f',4));
    //Nc_Data.at(i).at(4)=1;
            //               if (Nc_Data.at(i).at(0) > xlimit)
    //                   x_limit_flag = true;
    //               // wr.WriteLine(Convert.ToString("X" + NC_Data[i, 0].ToString("f4") + "  " + "B" + NC_Data[i, 1].ToString("f4") + "  " + "Z" + NC_Data[i, 5].ToString("f4") + "  " + "F" + (Convert.ToDouble(textBox4.Text) * 0.01 * NC_Data[i, 2]).ToString("f4") + "  " + "M302==" + NC_Data[i, 3].ToString("f4") + "  " + "\n"));
    //               if (i == 0)
    //                   Nc_Data[i][2] = Nc_Data.at(i).at(2);
    //               else
    //                   // NC_Data[j, 2] = Math.Sqrt(Math.Pow((NC_Data[j, 0] - NC_Data[j - 1, 0]), 2) + Math.Pow((NC_Data[j, 5] - NC_Data[j - 1, 5]), 2)) * Convert.ToDouble(str4.Trim()) * 10;//进给速度X Z联动

    //                   Nc_Data[i][2] = qSqrt(qPow((NC_Data[i][0] - NC_Data[i - 1][ 0]), 2) + qPow((NC_Data[i][ 5] - NC_Data[i - 1][ 5]), 2)) * NC_Data[i][ 2] / qAbs(NC_Data[i][0] - NC_Data[i - 1][ 0]) * (ui->lineEdit_feedrate->text().toDouble()) * 0.01;//进给速度X Z联动

            if(max_x<=qAbs(Nc_Data.at(i + d + a / 2).at(0)))
                max_x=qAbs(Nc_Data.at(i + d + a / 2).at(0));
            if(max_b<=qAbs(Nc_Data.at(i + d + a / 2).at(1)))
                max_b=qAbs(Nc_Data.at(i + d + a / 2).at(1));
            if(max_z<=qAbs(Nc_Data.at(i + d + a / 2).at(5)))
                max_z=qAbs(Nc_Data.at(i + d + a / 2).at(5));
        }


    } catch (EXCEPINFO err) {
        throw  err;

}
               produce_ncCode_flag2=true;
               produce_ncCode_flag=false;
}

void MainWindow::on_pushButton_43_clicked()//导入补正代码
{
    if(produce_ncCode_flag2==false)//判断是否先生成数控代码
    {
        QMessageBox::information(this,"提示！","请先生成补正代码！");
                return;
    }
    if(max_x>qAbs(xlimit_left))
    {
        QMessageBox::information(this,"提示！","X轴行程不足！");
                return;
    }
    if(max_b>qAbs(blimit_left))
    {
        QMessageBox::information(this,"提示！","Z轴行程不足！");
                return;
    }
    if(max_z>qAbs(zlimit_up))
    {
        QMessageBox::information(this,"提示！","Z轴行程不足！");
                return;
    }
    ui->pushButton_43->setText("导入中...");
    double D_workpiece=0;
    double R_left=0;
    double R_right = 0;
    double dist=0.1;
    D_workpiece = ui->lineEdit_D->text().toDouble();
   if (ui->lineEdit_ProdessLeft->text()=="")
                              R_left = 0;
                          else
                              R_left = ui->lineEdit_ProdessLeft->text().toDouble();//加工范围半径

                          if (ui->lineEdit_ProcessRight->text()=="")
                              R_right = 0;
                          else
                              R_right = ui->lineEdit_ProcessRight->text().toDouble();//加工口径另一值
     if (ui->comboBox_dataDistance->currentIndex()==0)

                              dist = 0.1;
                          else if(ui->comboBox_dataDistance->currentIndex()==1)
                              dist = 0.05;
                          else
                              dist=0.01;

               int c = (int)(qRound((R_right - R_left) / dist));//输出代码行数-1
               int a = (int)(qRound(D_workpiece / dist));//代码数组行数-1
               int d = (int)(qRound(R_left / dist));
    double t=0;//加工时间
    double t_feed=0;//进刀和退刀时间
    int n=ui->lineEdit_ProcessCycle_3->text().toInt();//标准加工次数
    QString text_data=ui->textEdit_2->toPlainText();
   QStringList data_list=text_data.split("\n");
   QVector<double> temp;
 //  qDebug()<<"Nc:"<<Nc_Data.at(1).at(4);
   for(int i=0;i<data_list.size();i++)
   {
       temp=Nc_Data.at(i +d + a / 2);
     //   qDebug()<<"Nc1:"<<Nc_Data.at(i +d + a / 2);
//        temp.replace(4,data_list.at(i).mid(data_list.at(i).indexOf("X")+1,data_list.at(i).indexOf("B")-data_list.at(i).indexOf("X")).toDouble());
//         temp.replace(1,data_list.at(i).mid(data_list.at(i).indexOf("B")+1,data_list.at(i).indexOf("Z")-data_list.at(i).indexOf("B")-1).toDouble());
//         temp.replace(5,data_list.at(i).mid(data_list.at(i).indexOf("Z")+1,data_list.at(i).indexOf("F")-data_list.at(i).indexOf("Z")-1).toDouble());

       temp.replace(4,data_list.at(i).mid(data_list.at(i).indexOf("X")+1,data_list.at(i).indexOf("Y")-data_list.at(i).indexOf("X")-1).toDouble());
     //  qDebug()<<"X"<<data_list.at(i).mid(data_list.at(i).indexOf("X")+1,data_list.at(i).indexOf("Y")-data_list.at(i).indexOf("X")-1);
        temp.replace(7,data_list.at(i).mid(data_list.at(i).indexOf("Y")+1,data_list.at(i).indexOf("Z")-data_list.at(i).indexOf("Y")-1).toDouble());
        temp.replace(5,data_list.at(i).mid(data_list.at(i).indexOf("Z")+1,data_list.at(i).indexOf("B")-data_list.at(i).indexOf("Z")-1).toDouble());
        temp.replace(1,data_list.at(i).mid(data_list.at(i).indexOf("B")+1,data_list.at(i).indexOf("F")-data_list.at(i).indexOf("B")-1).toDouble());

        if(i==0)
             {
            temp.replace(2,data_list.at(i).split("F").at(1).toDouble());//F速度
          //  qDebug()<<"Z0"<<data_list.at(i).split("Z").at(1);
            }
           else
        // temp.replace(2,data_list.at(i).split("Z").at(1).toDouble());//F速度
         temp.replace(2,qSqrt(qPow((Nc_Data.at(i+ d + a / 2).at(0) - Nc_Data.at(i+ d + a / 2-1).at(0)), 2) + qPow(Nc_Data.at(i+ d + a / 2).at(5) - Nc_Data.at(i+ d + a / 2-1).at(5), 2)) * data_list.at(i).split("F").at(1).toDouble() / dist);//进给速度X Z联动

   //  qDebug()<<"Nc:"<<data_list.at(i);
   //   qDebug()<<"B:"<<data_list.at(i).mid(data_list.at(i).indexOf("B")+1,data_list.at(i).indexOf("Z")-data_list.at(i).indexOf("B")-1);
     //  qDebug()<<"B-Z:"<<data_list.at(i).indexOf("Z")-data_list.at(i).indexOf("B");
     // temp.replace(5,data_list.at(i).split("Z").at(1).toDouble());
    //  qDebug()<<"BINDEX:"<<data_list.at(i).indexOf("B");
  //    qDebug()<<"Z:"<<data_list.at(i).split("Z").at(1).toDouble();

        Nc_Data.replace(i +d + a / 2,temp);
     //  qDebug()<<"Nc2:"<<Nc_Data.at(i);
   }


//                           PMAC->SendCommand("OPEN PROG 1");
//                           PMAC->SendCommand("CLEAR");
//                           // wr->WriteLine("S150");
//                           PMAC->SendCommand("DISABLE PLC6");
//                           PMAC->SendCommand("FRAX(X,Z)");
//                           PMAC->SendCommand("G90 G01");
//                           PMAC->SendCommand("P26=1");
//                           PMAC->SendCommand("P27=1");
//                           // wr->WriteLine("WHILE(P25<" + QString::number(n) + ")");
//                           //PMAC->SendCommand("P50=" + QString::number(NC_Data[0, 5]));
//                           PMAC->SendCommand("P50=" + QString::number(Nc_Data.at(0+d + a / 2).at(5)));
//                           PMAC->SendCommand("X" + QString::number(Nc_Data.at(0+d + a / 2).at(0)) + "  " + "B" + QString::number(Nc_Data.at(0+d + a / 2).at(1)) + "  " + "F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");

//                          // PMAC->SendCommand(QString::number("X" + NC_Data[0, 0] + " " + "B" + NC_Data[0, 1] + "  " + "F" + NC_Data[0, 2]->ToString()->Trim() + "  " + "M113==" + (NC_Data[0, 4] * 1/dist)->ToString("f4") + "  " + "M213==" + (NC_Data[0, 6] * 1000)->ToString("f4") + "  " + "\n"));
//                           //t = t ;+ Math->Abs(NC_Data[0, 0]) / 100
//                           if (Nc_Data.at(0).at(0) > 0)
//                               PMAC->SendCommand("WHILE((" + QString::number(Nc_Data.at(0+d + a / 2).at(0)*10000,'f',4) + "-M162/32/96)>100" + ")");
//                           else
//                               PMAC->SendCommand("WHILE((" + QString::number(Nc_Data.at(0+d + a / 2).at(0)*10000,'f',4) + "-M162/32/96)<-100" + ")");
//                           PMAC->SendCommand("P10=0");
//                           PMAC->SendCommand("DWELL 10");
//                           PMAC->SendCommand("ENDWHILE");
//                           PMAC->SendCommand("P10=1");
//                           PMAC->SendCommand("CLOSE");

  // read_position->stop();//停止读位置
                           //运动到初始加工位置
                           PMAC->SendCommand("OPEN PROG 7");
                           PMAC->SendCommand("CLEAR");
                           PMAC->SendCommand("FRAX(X,Z)");
                           PMAC->SendCommand("G90 G01");

                           PMAC->SendCommand("X" + QString::number(Nc_Data.at(0+d + a / 2).at(0)) + "  " + "B" + QString::number(Nc_Data.at(0+d + a / 2).at(1)) + "  " + "F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");
                           PMAC->SendCommand("CLOSE");

                           PMAC->SendCommand("OPEN PROG 8");
                           PMAC->SendCommand("CLEAR");
                           PMAC->SendCommand("FRAX(X,Z)");
                           PMAC->SendCommand("G90 G01");

                           PMAC->SendCommand("X" + QString::number(-Nc_Data.at(0+d + a / 2).at(0)) + "  " + "B" + QString::number(-Nc_Data.at(0+d + a / 2).at(1)) + "  " + "F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");
                            PMAC->SendCommand("CLOSE");

           if (n == 1)
                          {
                           PMAC->SendCommand("OPEN PROG 2");

                            PMAC->SendCommand("CLEAR");
                             PMAC->SendCommand("M46=1");//绿灯亮
                            PMAC->SendCommand("FRAX(x,z)");
                        //    PMAC->SendCommand("PSET Z(P50)");//加工程序
                         PMAC->SendCommand("G90 G01 P25=0 P32=0 M502==" + QString::number((ui->lineEdit_Toolspeed->text().toDouble()) * U_motor_scale_factor + U_motor_offset));
                                                      //wr.WriteLine("P25=0");
                         if (ui->comboBox_ToolDirect->currentIndex()==0)//抛光轴转动方向
                           {
                              PMAC->SendCommand("M44==0");

                           }
                          else
                         {
                            PMAC->SendCommand("M44==1");
                           }

                         PMAC->SendCommand("M5=1");//开抛光液
                          PMAC->SendCommand("X" + QString::number(Nc_Data.at(0+d + a / 2).at(0)) + "  " + "B" + QString::number(Nc_Data.at(0+d + a / 2).at(1)) + "  " + "F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");
                          qDebug()<<("X" + QString::number(Nc_Data.at(0+d + a / 2).at(0)) + "  " + "B" + QString::number(Nc_Data.at(0+d + a / 2).at(1)) + "  " + "F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");

                          t_feed=qAbs(Nc_Data.at(0+d + a / 2).at(0)/Nc_Data.at(0+d + a / 2).at(2));
                          PMAC->SendCommand("Z" + QString::number(Nc_Data.at(0+d + a / 2).at(5)+5) + "  "  + "F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");
                         qDebug()<<("Z" + QString::number(Nc_Data.at(0+d + a / 2).at(5)+5) + "  "  + "F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");

                          t_feed=t_feed+qAbs(Nc_Data.at(0+d + a / 2).at(5)/Nc_Data.at(0+d + a / 2).at(2));
                          PMAC->SendCommand("DWELL0");

                          PMAC->SendCommand("G97 S" +ui->lineEdit_constCSpeed->text());//主轴转速
                            //PMAC->SendCommand("G97");
                            PMAC->SendCommand("DWELL0");
                           if (ui->comboBox_Cdirect->currentIndex()==0)//工件转动方向
                            {
                            PMAC->SendCommand("M03");
                           // PMAC->SendCommand("M4=0");
                            }
                           else
                             {
                              // PMAC->SendCommand("M3=0");
                               PMAC->SendCommand("M04");
                              }
                                    PMAC->SendCommand("P26=1");
                               PMAC->SendCommand("P27=0");
                             //  PMAC->SendCommand("M302==" +QString::number(Nc_Data.at(1).at(3),'f',4));
                                PMAC->SendCommand("M45=1");
                                PMAC->SendCommand("Z" + QString::number(Nc_Data.at(0+d + a / 2).at(5)) + "  "  + "F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");
                               qDebug()<<("Z" + QString::number(Nc_Data.at(0+d + a / 2).at(5)) + "  "  + "F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");

                                PMAC->SendCommand("DWELL0");

                              PMAC->SendCommand("WHILE(P25<" +QString::number(n) + ")");
                              qDebug()<<("WHILE(P25<" +QString::number(n) + ")");

                               PMAC->SendCommand("P27=P27+1");
                            for (int i = 0; i < c+1; i++)
                             {
                            PMAC->SendCommand("X" + QString::number(Nc_Data.at(i+d + a / 2).at(0),'f',4) + "  "+"Y" + QString::number(Nc_Data.at(i+d + a / 2).at(7),'f',4) + "  " + "B" +QString::number(Nc_Data.at(i+d + a / 2).at(1),'f',4) + "  " + "Z" + QString::number(Nc_Data.at(i+d + a / 2).at(5),'f',4) + "  " + "F" + QString::number(Nc_Data.at(i+d + a / 2).at(2),'f',4) + "  " + "\n");// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 1 / dist).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));
                            qDebug()<<("X" + QString::number(Nc_Data.at(i+d + a / 2).at(0),'f',4) + "  "+"Y" + QString::number(Nc_Data.at(i+d + a / 2).at(7),'f',4) + "  " + "B" +QString::number(Nc_Data.at(i+d + a / 2).at(1),'f',4) + "  " + "Z" + QString::number(Nc_Data.at(i+d + a / 2).at(5),'f',4) + "  " + "F" + QString::number(Nc_Data.at(i+d + a / 2).at(2),'f',4) + "  " + "\n");// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 1 / dist).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));

                            if (i > 0)
                              t = t + qSqrt(qPow((Nc_Data.at(i+d + a / 2).at(0) - Nc_Data.at(i-1+d + a / 2).at(0)), 2) + qPow((Nc_Data.at(i+d + a / 2).at(5) - Nc_Data.at(i-1+d + a / 2).at(5)), 2)) / Nc_Data.at(i+d + a / 2).at(2);//(Math.Abs(Nc_Data[i, 0] - Nc_Data[i - 1, 0])) / Nc_Data[i, 2];
                            }
                            PMAC->SendCommand("P25=P25+1");
                            PMAC->SendCommand("ENDWHILE");
                            qDebug()<<("ENDWHILE");
                            PMAC->SendCommand( "Z"+QString::number(Nc_Data.at(c+d + a / 2).at(5)+5,'f',4)+"F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");
                            PMAC->SendCommand("DWELL 0");
                            t_feed=t_feed+qAbs(Nc_Data.at(c+d + a / 2).at(5)/Nc_Data.at(0+d + a / 2).at(2));
                            PMAC->SendCommand("M05");
                             PMAC->SendCommand("M45=0");
                              PMAC->SendCommand("M5=0");//关抛光液
                            PMAC->SendCommand( "Z0F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");
                            PMAC->SendCommand("X0B0F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");
                              t_feed=t_feed+qAbs(Nc_Data.at(c+d + a / 2).at(0)/Nc_Data.at(0+d + a / 2).at(2));
                          PMAC->SendCommand("DWELL 0");
                          PMAC->SendCommand("P14=1");
                          PMAC->SendCommand("P32=1");

                           PMAC->SendCommand("M7=1");
                           PMAC->SendCommand("M113=0 M213=0");
                           PMAC->SendCommand("M163=0 ");
                           PMAC->SendCommand("M46=0 ");//绿灯灭
                         PMAC->SendCommand("ENABLE PLC6");
                         PMAC->SendCommand("CLOSE");






                  }
           else
                  {
                   PMAC->SendCommand("OPEN PROG 2");
                   PMAC->SendCommand("CLEAR");
                    PMAC->SendCommand("FRAX(x,z)");
                     PMAC->SendCommand("M46=1");//绿灯亮
                 //  PMAC->SendCommand("PSET Z(P50)");//加工程序
                   PMAC->SendCommand("G90 G01 P25=0 P32=0 M502==" + QString::number((ui->lineEdit_Toolspeed->text().toDouble()) * U_motor_scale_factor + U_motor_offset));
                                                      //wr.WriteLine("P25=0");
                   if (ui->comboBox_ToolDirect->currentIndex()==0)//抛光轴转动方向
                     {
                        PMAC->SendCommand("M44==0");

                     }
                    else
                   {
                      PMAC->SendCommand("M44==1");
                     }

                    PMAC->SendCommand("M5=1");//开抛光液
                    PMAC->SendCommand("X" + QString::number(Nc_Data.at(0+d + a / 2).at(0)) + "  " + "B" + QString::number(Nc_Data.at(0+d + a / 2).at(1)) + "  " + "F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");
                   qDebug()<<("X" + QString::number(Nc_Data.at(0+d + a / 2).at(0)) + "  " + "B" + QString::number(Nc_Data.at(0+d + a / 2).at(1)) + "  " + "F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");

                    t_feed=qAbs(Nc_Data.at(0+d + a / 2).at(0)/Nc_Data.at(0+d + a / 2).at(2));

                    PMAC->SendCommand("Z" + QString::number(Nc_Data.at(0+d + a / 2).at(5)+5) + "  "  + "F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4)+5,'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");
                    qDebug()<<("Z" + QString::number(Nc_Data.at(0+d + a / 2).at(5)+5) + "  "  + "F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4)+5,'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");

                    PMAC->SendCommand("DWELL0");
                    t_feed=t_feed+qAbs(Nc_Data.at(0+d + a / 2).at(5)/Nc_Data.at(0+d + a / 2).at(2));

                     PMAC->SendCommand("G97 S" +ui->lineEdit_constCSpeed->text());//主轴转速
                    //  PMAC->SendCommand("G97");
                      PMAC->SendCommand("DWELL0");

                     if (ui->comboBox_Cdirect->currentIndex()==0)//工件转动方向
                      {
                      PMAC->SendCommand("M03");
                     // PMAC->SendCommand("M4=0");
                      }
                     else
                       {
                        // PMAC->SendCommand("M3=0");
                         PMAC->SendCommand("M04");
                        }
                              PMAC->SendCommand("P26=1");
                         PMAC->SendCommand("P27=0");
                       //  PMAC->SendCommand("M302==" +QString::number(Nc_Data.at(1).at(3),'f',4));
                          PMAC->SendCommand("M45=1");

                          PMAC->SendCommand("Z" + QString::number(Nc_Data.at(0+d + a / 2).at(5)) + "  "  + "F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");
                         qDebug()<<("Z" + QString::number(Nc_Data.at(0+d + a / 2).at(5)) + "  "  + "F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");

                          PMAC->SendCommand("DWELL0");


                if (n % 2 == 1)
               PMAC->SendCommand("WHILE(P25<" + QString::number((n - 1) / 2) + ")");
                 else
             PMAC->SendCommand("WHILE(P25<" + QString::number(n / 2) + ")");
                 qDebug()<<("WHILE(P25<" + QString::number(n / 2) + ")");("WHILE(P25<" + QString::number(n / 2) + ")");
           PMAC->SendCommand("P27=P27+1");
        for (int i = 0; i < c+1; i++)
          {
            PMAC->SendCommand("X" + QString::number(Nc_Data.at(i+d + a / 2).at(0),'f',4) + "  " + "B" +QString::number(Nc_Data.at(i+d + a / 2).at(1),'f',4) + "  " + "Z" + QString::number(Nc_Data.at(i+d + a / 2).at(5),'f',4) + "  " + "F" + QString::number(Nc_Data.at(i+d + a / 2).at(2),'f',4) + "  " + "\n");// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 1 / dist).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));
             qDebug()<<("X" + QString::number(Nc_Data.at(i+d + a / 2).at(0),'f',4) + "  " + "B" +QString::number(Nc_Data.at(i+d + a / 2).at(1),'f',4) + "  " + "Z" + QString::number(Nc_Data.at(i+d + a / 2).at(5),'f',4) + "  " + "F" + QString::number(Nc_Data.at(i+d + a / 2).at(2),'f',4) + "  " + "\n");// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 1 / dist).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));

            if (i > 0)
                  t = t + qSqrt(qPow((Nc_Data.at(i+d + a / 2).at(0) - Nc_Data.at(i-1+d + a / 2).at(0)), 2) + qPow((Nc_Data.at(i+d + a / 2).at(5) - Nc_Data.at(i-1+d + a / 2).at(5)), 2)) / Nc_Data.at(i+d + a / 2).at(2);//(Math.Abs(Nc_Data[i, 0] - Nc_Data[i - 1, 0])) / Nc_Data[i, 2];
            }
           PMAC->SendCommand("P27=P27+1");
          for (int i = c+2 - 2; i >= 0; i--)//代码倒转
     {
              PMAC->SendCommand("X" + QString::number(Nc_Data.at(i+d + a / 2).at(0),'f',4) + "  " + "B" +QString::number(Nc_Data.at(i+d + a / 2).at(1),'f',4) + "  " + "Z" + QString::number(Nc_Data.at(i+d + a / 2).at(5),'f',4) + "  " + "F" + QString::number(Nc_Data.at(i+d + a / 2+1).at(2),'f',4) + "  " + "\n");// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 1 / dist).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));
            qDebug()<<("X" + QString::number(Nc_Data.at(i+d + a / 2).at(0),'f',4) + "  " + "B" +QString::number(Nc_Data.at(i+d + a / 2).at(1),'f',4) + "  " + "Z" + QString::number(Nc_Data.at(i+d + a / 2).at(5),'f',4) + "  " + "F" + QString::number(Nc_Data.at(i+d + a / 2+1).at(2),'f',4) + "  " + "\n");// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 1 / dist).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));

       // PMAC->SendCommand(Convert.ToString("X" + Nc_Data[i, 0].ToString("f4") + "  " + "B" + Nc_Data[i, 1].ToString("f4") + "  " + "Z" + Nc_Data[i, 5].ToString("f4") + "  " + "F" + Nc_Data[i + 1, 2].ToString("f4") + "  " + "\n"));// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 10).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));
     }
           PMAC->SendCommand("P25=P25+1");
     PMAC->SendCommand("ENDWHILE");
qDebug()<<("ENDWHILE");


       if (n % 2 == 1)
           {
                                                          //    PMAC->SendCommand("COMMAND\"&1B9R\"");
                                                          //    PMAC->SendCommand("CLOSE");
                                                          //    PMAC->SendCommand("OPEN PROG 9 CLEAR");

        PMAC->SendCommand("P27=P27+1");
        for (int i = 0; i < c+1; i++)
         {
            PMAC->SendCommand("X" + QString::number(Nc_Data.at(i+d + a / 2).at(0),'f',4) + "  " + "B" +QString::number(Nc_Data.at(i+d + a / 2).at(1),'f',4) + "  " + "Z" + QString::number(Nc_Data.at(i+d + a / 2).at(5),'f',4) + "  " + "F" + QString::number(Nc_Data.at(i+d + a / 2).at(2),'f',4) + "  " + "\n");// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 1 / dist).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));
           qDebug()<<("X" + QString::number(Nc_Data.at(i+d + a / 2).at(0),'f',4) + "  " + "B" +QString::number(Nc_Data.at(i+d + a / 2).at(1),'f',4) + "  " + "Z" + QString::number(Nc_Data.at(i+d + a / 2).at(5),'f',4) + "  " + "F" + QString::number(Nc_Data.at(i+d + a / 2).at(2),'f',4) + "  " + "\n");// + "M302==" + Nc_Data[i, 3].ToString("f4") + "  " + "M113==" + (Nc_Data[i, 4] * 1 / dist).ToString("f4") + "  " + "M213==" + (Nc_Data[i, 6] * 1000).ToString("f4") + "  " + "\n"));
                                                   // if (i > 0)
                                                                //   t = t + qSqrt(qPow((Nc_Data.at(i).at(0) - Nc_Data.at(i-1).at(0)), 2) + qPow((Nc_Data.at(i).at(5) - Nc_Data.at(i-1).at(5)), 2)) / Nc_Data.at(i).at(2);//(Math.Abs(Nc_Data[i, 0] - Nc_Data[i - 1, 0])) / Nc_Data[i, 2];
        }

        PMAC->SendCommand( "Z"+QString::number(Nc_Data.at(c+d + a / 2).at(5)+5,'f',4)+"F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");
        PMAC->SendCommand("DWELL 0");
        t_feed=t_feed+qAbs(Nc_Data.at(c+d + a / 2).at(5)/Nc_Data.at(0+d + a / 2).at(2));
        t_feed=t_feed+qAbs(Nc_Data.at(c+d + a / 2).at(0)/Nc_Data.at(0+d + a / 2).at(2));


        }
       else
       {
           PMAC->SendCommand( "Z"+QString::number(Nc_Data.at(0+d + a / 2).at(5)+5,'f',4)+"F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");
           PMAC->SendCommand("DWELL 0");
           t_feed=t_feed+qAbs(Nc_Data.at(0+d + a / 2).at(5)/Nc_Data.at(0+d + a / 2).at(2));
            t_feed=t_feed+qAbs(Nc_Data.at(0+d + a / 2).at(0)/Nc_Data.at(0+d + a / 2).at(2));

       }

       PMAC->SendCommand("M05");
        PMAC->SendCommand("M45=0");
         PMAC->SendCommand("M5=0");//关抛光液
       PMAC->SendCommand( "Z0F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");
       PMAC->SendCommand("X0B0F" +QString::number(Nc_Data.at(0+d + a / 2).at(2))+ "  " + "M113==" + QString::number(Nc_Data.at(0+d + a / 2).at(4),'f',4) + "  " + "M213==" + QString::number(Nc_Data.at(0+d + a / 2).at(6)*1000) + "  " + "\n");

    PMAC->SendCommand("DWELL 0");
  PMAC->SendCommand("P14=1");
 PMAC->SendCommand("P32=1");
 PMAC->SendCommand("M7=1");
   PMAC->SendCommand("M113=0 M213=0");
 PMAC->SendCommand("M163=0 ");
  PMAC->SendCommand("M46=0 ");//绿灯灭
 PMAC->SendCommand("ENABLE PLC6");
PMAC->SendCommand("CLOSE");
 }
      //    startTimer(1);//开始读位置
            process_time=t*n+t_feed;//加工时间
  QMessageBox::information(this, "提示！", "加工时间："+QString::number(process_time,'f',2)+"分钟");

  download_code_flag=true;

           ui->pushButton_43->setText("导入补正代码");
        //    read_position->start();


}



void MainWindow::on_pushButton_18_released()//X左
{
    if(ui->comboBox_6->currentIndex()==1)
    PMAC->StopAxi(1);

}

void MainWindow::on_pushButton_18_pressed()//X左
{
    double pos=ui->lineEdit_35->text().toDouble();
    double velocity=ui->lineEdit_47->text().toDouble();
    if(pos>xlimit_left)
    {
        QMessageBox::information(this, "提示", "X轴目标位置超出行程！");
        return;
    }
    if(velocity>x_axi_hand_maxfeed/60)
    {
        QMessageBox::information(this, "提示", "X轴运动速度过大！");
        return;
    }
        PMAC->SetVelocity(1,velocity*10);//设置速度
    if(ui->comboBox_6->currentIndex()==1)//点动
       // PMAC->JogForward(1);
         PMAC->JogBackward(1);
    else {
        PMAC->JogBackwardP(1,pos*10000);//点位
         }
}

void MainWindow::on_pushButton_20_clicked()
{
     PMAC->StopAxi(1);
}
void MainWindow::on_pushButton_19_pressed()//X右
{
   // QString status;
    double pos=ui->lineEdit_35->text().toDouble();
    double velocity=ui->lineEdit_47->text().toDouble();
    if(pos>xlimit_right)
    {
        QMessageBox::information(this, "提示", "X轴目标位置超出行程！");
        return;
    }
    if(velocity>x_axi_hand_maxfeed/60)
    {
        QMessageBox::information(this, "提示", "X轴运动速度过大！");
        return;
    }
        PMAC->SetVelocity(1,velocity*10);//设置速度
    if(ui->comboBox_6->currentIndex()==1)//点动
        PMAC->JogForward(1);
    else {
        PMAC->JogForwardP(1,pos*10000);//点位
         }
}

void MainWindow::on_pushButton_19_released()//X右停
{
   // QString status;
    if(ui->comboBox_6->currentIndex()==1)
    PMAC->StopAxi(1);

}

void MainWindow::on_pushButton_23_pressed()//Y前
{
    double pos=ui->lineEdit_36->text().toDouble();
    double velocity=ui->lineEdit_49->text().toDouble();
    if(pos>ylimit_forward)
    {
        QMessageBox::information(this, "提示", "Y轴目标位置超出行程！");
        return;
    }
    if(velocity>y_axi_hand_maxfeed/60)
    {
        QMessageBox::information(this, "提示", "Y轴运动速度过大！");
        return;
    }
        PMAC->SetVelocity(3,velocity*10);//设置速度
    if(ui->comboBox_6->currentIndex()==1)//点动
        PMAC->JogForward(3);
    else {
        PMAC->JogForwardP(3,pos*10000);//点位
         }
}

void MainWindow::on_pushButton_23_released()//Y前
{
    if(ui->comboBox_6->currentIndex()==1)
    PMAC->StopAxi(3);
}

void MainWindow::on_pushButton_21_clicked()//Y停
{
PMAC->StopAxi(3);
}

void MainWindow::on_pushButton_22_pressed()//Y后
{

    double pos=ui->lineEdit_36->text().toDouble();
    double velocity=ui->lineEdit_49->text().toDouble();
    if(pos>ylimit_bakcward)
    {
        QMessageBox::information(this, "提示", "Y轴目标位置超出行程！");
        return;
    }
    if(velocity>y_axi_hand_maxfeed/60)
    {
        QMessageBox::information(this, "提示", "Y轴运动速度过大！");
        return;
    }
        PMAC->SetVelocity(3,velocity*10);//设置速度
    if(ui->comboBox_6->currentIndex()==1)//点动
        PMAC->JogBackward(3);
    else {
        PMAC->JogBackwardP(3,pos*10000);//点位
         }
}

void MainWindow::on_pushButton_22_released()//Y后
{
    if(ui->comboBox_6->currentIndex()==1)
    PMAC->StopAxi(3);

}

void MainWindow::on_pushButton_26_pressed()//Z上
{
    double pos=ui->lineEdit_37->text().toDouble();
    double velocity=ui->lineEdit_48->text().toDouble();
    if(pos>zlimit_up)
    {
        QMessageBox::information(this, "提示", "Z轴目标位置超出行程！");
        return;
    }
    if(velocity>z_axi_hand_maxfeed/60)
    {
        QMessageBox::information(this, "提示", "Z轴运动速度过大！");
        return;
    }
        PMAC->SetVelocity(4,velocity*10);//设置速度
    if(ui->comboBox_6->currentIndex()==1)//点动
        PMAC->JogBackward(4);
    else {
        PMAC->JogBackwardP(4,pos*10000);//点位
         }


}

void MainWindow::on_pushButton_26_released()//Z上
{
    if(ui->comboBox_6->currentIndex()==1)
    PMAC->StopAxi(4);

}

void MainWindow::on_pushButton_24_clicked()//Z停
{
    PMAC->StopAxi(4);

}

void MainWindow::on_pushButton_25_pressed()//Z下
{
    double pos=ui->lineEdit_37->text().toDouble();
    double velocity=ui->lineEdit_48->text().toDouble();
    if(pos>zlimit_down)
    {
        QMessageBox::information(this, "提示", "Z轴目标位置超出行程！");
        return;
    }
    if(velocity>z_axi_hand_maxfeed/60)
    {
        QMessageBox::information(this, "提示", "Z轴运动速度过大！");
        return;
    }
        PMAC->SetVelocity(4,velocity*10);//设置速度
    if(ui->comboBox_6->currentIndex()==1)//点动
        PMAC->JogForward(4);
    else {
        PMAC->JogForwardP(4,pos*10000);//点位
         }


}

void MainWindow::on_pushButton_25_released()//Z下
{
    if(ui->comboBox_6->currentIndex()==1)
    PMAC->StopAxi(4);
}

void MainWindow::on_pushButton_29_pressed()//B顺
{
    double pos=ui->lineEdit_38->text().toDouble();
    double velocity=ui->lineEdit_51->text().toDouble();
    if(pos>blimit_left)
    {
        QMessageBox::information(this, "提示", "B轴目标位置超出行程！");
        return;
    }
    if(velocity>b_axi_hand_maxfeed)
    {
        QMessageBox::information(this, "提示", "B轴运动速度过大！");
        return;
    }
        PMAC->SetVelocity(2,velocity*10);//设置速度
    if(ui->comboBox_6->currentIndex()==1)//点动
        PMAC->JogBackward(2);
    else {
        PMAC->JogBackwardP(2,pos*10000);//点位
         }

}

void MainWindow::on_pushButton_29_released()//B顺
{
    if(ui->comboBox_6->currentIndex()==1)
    PMAC->StopAxi(2);
}

void MainWindow::on_pushButton_27_clicked()//B停
{
    PMAC->StopAxi(2);

}

void MainWindow::on_pushButton_28_pressed()//B逆
{
    double pos=ui->lineEdit_38->text().toDouble();
    double velocity=ui->lineEdit_51->text().toDouble();
    if(pos>blimit_right)
    {
        QMessageBox::information(this, "提示", "B轴目标位置超出行程！");
        return;
    }
    if(velocity>b_axi_hand_maxfeed)
    {
        QMessageBox::information(this, "提示", "B轴运动速度过大！");
        return;
    }
        PMAC->SetVelocity(2,velocity*10);//设置速度
    if(ui->comboBox_6->currentIndex()==1)//点动
        PMAC->JogForward(2);
    else {
        PMAC->JogForwardP(2,pos*10000);//点位
         }

}

void MainWindow::on_pushButton_28_released()//B逆
{
    if(ui->comboBox_6->currentIndex()==1)
    PMAC->StopAxi(2);

}

void MainWindow::on_pushButton_32_pressed()//C顺
{
    double pos=ui->lineEdit_39->text().toDouble();
    double velocity=ui->lineEdit_46->text().toDouble();
    if(velocity>C_axi_maxfeed)
    {
        QMessageBox::information(this, "提示", "B轴运动速度过大！");
        return;
    }
        PMAC->SetVelocity(5,velocity/10);//设置速度
    if(ui->comboBox_6->currentIndex()==1)//点动
        PMAC->JogBackward(5);
    else {
        PMAC->JogBackwardP(5,pos*100);//点位
         }

}

void MainWindow::on_pushButton_32_released()//C顺
{
    if(ui->comboBox_6->currentIndex()==1)
    PMAC->StopAxi(3);

}


void MainWindow::on_pushButton_30_clicked()//C停
{
    PMAC->StopAxi(5);

}
void MainWindow::on_pushButton_31_pressed()//C逆
{
    double pos=ui->lineEdit_39->text().toDouble();
    double velocity=ui->lineEdit_46->text().toDouble();
        PMAC->SetVelocity(5,velocity/10);//设置速度
    if(ui->comboBox_6->currentIndex()==1)//点动
        PMAC->JogForward(5);
    else {
        PMAC->JogForwardP(5,pos*100);//点位
         }

}

void MainWindow::on_pushButton_31_released()//C逆
{
    if(ui->comboBox_6->currentIndex()==1)
    PMAC->StopAxi(3);


}






void MainWindow::on_pushButton_33_pressed()//抛光轴
{
//    double velocity=ui->lineEdit_45->text().toDouble();
//    QString speed=QString::number(velocity,'f',2);
//    int M_Velocity;
//    int DIR;

//    if(ui->comboBox_5->currentIndex()==1)//转动方向
//        Hz_start(0,speed);
//    else {
//       // DIR=0;
//        Hz_start(1,speed);
//    }

//    if(velocity>19500)//速度限定
//       {
//        QMessageBox::information(this,"提示","抛光轴速度设定过大！");
//                return;
//        }

      //  PMAC->SetVelocity(2,velocity/10);//设置速度
     //  M_Velocity=velocity*921.6/50000*15.39;
     //  PMAC->SetM(44,DIR);
       // PMAC->SetM(502,M_Velocity);
       // PMAC->SetM(45,1);


}

void MainWindow::on_pushButton_33_released()//抛光轴
{
   // double pos=ui->lineEdit_39->text().toDouble();
 if(ui->comboBox_6->currentIndex()==1)
    {
     //PMAC->SetM(502,0);
    // PMAC->SetM(45,0);
    // Hz_stop();
    }

}

void MainWindow::on_pushButton_34_clicked()//抛光轴停
{
   // PMAC->SetM(502,0);
        // PMAC->SetM(45,0);
    Hz_stop();


}

void MainWindow::on_pushButton_16_clicked()//执行加工
{
    QIcon icon= windowIcon();//
   QMessageBox megBox;
   megBox.setIcon(QMessageBox::Question);
   megBox.setWindowIcon(icon);
   megBox.setWindowTitle("提示");
   megBox.addButton("是",QMessageBox::AcceptRole);
   megBox.addButton("否",QMessageBox::RejectRole);
   megBox.setText("是否开始加工？");
   int result= megBox.exec();
  int door_stat=PMAC->GetM(14);
  int door_control=ui->comboBox_7->currentIndex();
  if(door_stat==1&&door_control==1)
      door_open=true;
  else {
      door_open=false;

       }
   if (result==QMessageBox::AcceptRole)
   {
       if(door_open==true)
       {
           QMessageBox::information(this, "提示！", "现由软件控制门开关，请先关门！");
           return;
       }

       if(download_code_flag==true)
      {
           QString toolspeed=ui->lineEdit_Toolspeed->text().trimmed();
            if(ui->comboBox_ToolDirect->currentIndex()==0)

           Hz_start(1,toolspeed);
            else
                Hz_start(0,toolspeed);


             PMAC->SetP(1,1);         ui->pushButton_16->setDisabled(true);
        PMAC->SendCommand("&1B2R");//执行加工程序
        process_begin_flag = true;//设置加工开始
        int count_time=process_time*60;//加工时间秒
        ui->progressBar->setRange(0,count_time);//设置加工进度条范围
        timecount=new Process_time_count(this, process_time);//建立线程
       connect(timecount,SIGNAL(count_Signal(int)),this,SLOT(DisplayMsg(int)));
       timecount->start();
        check_process_satus= new QTimer(this);
        connect(check_process_satus,SIGNAL(timeout()),this,SLOT(Check_iffinish()));
         check_process_satus->setInterval(100);
        check_process_satus->start();
               qDebug()<<count_time;
      }
       else
       {
           QMessageBox::information(this, "提示！", "请先设定好参数！");
       }

   }
    else
        return;


}

void MainWindow::Check_iffinish()//查询是否加工完成或者终止加工
{
    int Finish_Pflag=PMAC->GetP(14);
    int process_circle=PMAC->GetP(27);//加工次数
    ui->lineEdit_23->setText(QString::number(process_circle));//显示加工次数
    int em_STOP_lun=PMAC->GetM(50);//手轮急停信号
    if(process_begin_flag==false&&em_STOP_lun==0)//没开始执行时
        {

        QMessageBox::information(this,"提示","请先松开手轮急停按钮！");
        process_begin_flag=false;//重置标志
        ui->lineEdit_22->setText("0时0分0秒");//设置加工时间为零
        ui->progressBar->setValue(0);//设置加工进度条为零
        ui->pushButton_16->setDisabled(false);
        check_process_satus->stop();//结束计时

        }

    if(process_begin_flag==true&&em_STOP_lun==0)//开始执行时
        {

        ui->pushButton_16->setDisabled(false);
        PMAC->SendCommand("&1A");//停止加工程序
        Sleep(100);
       PMAC->SendCommand("#5j/");//C轴停
       Sleep(100);
       PMAC->SendCommand("M45=0");//抛光轴停
        PMAC->SendCommand("M5=0");//关抛光液
        //QString toolspeed=ui->lineEdit_Toolspeed->text().trimmed();
           Hz_stop();
         timecount->terminate();
        ui->lineEdit_22->setText("0时0分0秒");//设置加工时间为零
        ui->progressBar->setValue(0);//设置加工进度条为零
        ui->pushButton_16->setDisabled(false);
        QMessageBox::information(this,"提示","手轮急停按钮按下，停止加工！");
         process_begin_flag=false;//重置标志
        check_process_satus->stop();//结束计时

        }

    if(process_begin_flag==true&&Finish_Pflag==1)
    {

        buzzer_working= new QTimer(this);//实例化timer
        buzzer_working->setInterval(3000);//设置响的间隔
        connect(buzzer_working,SIGNAL(timeout()),this,SLOT(buzzer_sound()));//连接信号与槽
        buzzer_working->start();//蜂鸣器响
       Hz_stop();
        QMessageBox::information(this,"提示","加工完成！");
        PMAC->SetM(7,0);//关黄灯
        PMAC->SetP(14,0);//重置标志加工标志变量
        process_begin_flag=false;//重置标志


        ui->lineEdit_22->setText("0时0分0秒");//设置加工时间为零
        ui->progressBar->setValue(0);//设置加工进度条为零
        ui->pushButton_16->setDisabled(false);
        check_process_satus->stop();//结束计时

        qDebug()<<"finish";
    }

    //if()
qDebug()<<Finish_Pflag;

}

void MainWindow::buzzer_sound()
{
    int buzzer_M=PMAC->GetM(6);
    PMAC->SetM(6,1);

    if(buzzer_M==1)
    {
        PMAC->SetM(6,0);
        buzzer_working->stop();
    }
}

void MainWindow::DisplayMsg(int num)
{

    int hour,min,second,time,remain_time;
    time=process_time*60;//时间/S
    remain_time=time-num;
    hour=(remain_time-remain_time%3600)/3600;
    min= (remain_time%3600-remain_time%3600%60)/60;
    second=remain_time%60;
    ui->lineEdit_22->setText(QString::number(hour)+"时"+QString::number(min)+"分"+QString::number(second)+"秒");
    ui->progressBar->setValue(num);

   // qDebug()<<num;
}

void MainWindow::on_pushButton_44_clicked()//干涉检查
{

    // produce_NC_interference_check();

     //ui->pushButton_44->setText("干涉检查");
     Interfer_check = new MyThread(this); //定义线程
     Interfer_check->start();
   //  QEventLoop eventLoop;
     connect(Interfer_check,SIGNAL(finished ()),this,SLOT(checkMessage()));

     // Interfer_check->wait(1);
     // eventLoop.exec();
}

void MainWindow::checkMessage()//干涉检查信息
{
    if(interfere_flag==true)
     QMessageBox::information(this, "提示！", "加工参数干涉，请减小压缩量！");
    else
         QMessageBox::information(this, "提示！", "检查完成，无加工干涉！");

     ui->pushButton_44->setText("干涉检查");
}

void MainWindow::on_pushButton_44_pressed()//干涉检查
{
    ui->pushButton_44->setText("检查中...");
}

void MainWindow::on_pushButton_17_clicked()//终止加工
{
    process_begin_flag=false;
    ui->pushButton_16->setDisabled(false);
    timecount->terminate();
    PMAC->SendCommand("&1A");//停止加工程序
    Sleep(500);//延时1000毫秒
    PMAC->SendCommand("&1B1R");//执行回零位程序
     check_process_satus->stop();
    Hz_stop();
    Sleep(1000);//延时400毫秒
    ui->lineEdit_22->setText("0时0分0秒");
    ui->progressBar->setValue(0);
    PMAC->SendCommand("M7=0");//关黄灯

}

void MainWindow::on_pushButton_35_clicked()//初始加工点左
{
    QIcon icon= windowIcon();
    QMessageBox megBox;
    megBox.setIcon(QMessageBox::Question);
    megBox.setWindowIcon(icon);
    megBox.setWindowTitle("提示");
    megBox.addButton("是",QMessageBox::AcceptRole);
    megBox.addButton("否",QMessageBox::RejectRole);
    megBox.setText("是否运动到加工点左？");
    int result= megBox.exec();
    if (result==QMessageBox::AcceptRole)
    {
         PMAC->SendCommand("&1B7R");//
    }
     else
         return;

}

void MainWindow::on_pushButton_36_clicked()//初始加工点右
{
    QIcon icon= windowIcon();
    QMessageBox megBox;
    megBox.setIcon(QMessageBox::Question);
    megBox.setWindowIcon(icon);
    megBox.setWindowTitle("提示");
    megBox.addButton("是",QMessageBox::AcceptRole);
    megBox.addButton("否",QMessageBox::RejectRole);
    megBox.setText("是否运动到加工点右？");
    int result= megBox.exec();
    if (result==QMessageBox::AcceptRole)
    {
         PMAC->SendCommand("&1B8R");//
    }
     else
         return;

}

void MainWindow::on_Lens_tu_toggled(bool checked)//凸曲面
{


}

void MainWindow::on_Lens_tu_clicked()
{
    QImage *img=new QImage;//新建图像对象
     QString filepath=QCoreApplication::applicationDirPath()+"\\Image\\picture_tu.PNG";
    img->load(filepath);
    ui->label_16->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
}

void MainWindow::on_Lens_ao_clicked()
{
    QImage *img=new QImage;//新建图像对象
     QString filepath=QCoreApplication::applicationDirPath()+"\\Image\\picture_ao.PNG";
    img->load(filepath);
    ui->label_16->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
}

//void MainWindow::on_Lens_plane_clicked()
//{

//    QImage *img=new QImage;//新建图像对象
//     QString filepath=QCoreApplication::applicationDirPath()+"\\Image\\picture_plane.PNG";
//    img->load(filepath);
//    ui->label_16->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img

//}

void MainWindow::on_pushButton_45_clicked()//开门
{
    int door_sta=ui->comboBox_7->currentIndex();
    if(door_sta==0)
    {
        QMessageBox::information(this,"提示","门由面板按钮控制，请选择由软件控制");
        return;
    }
    PMAC->SendCommand("M2=0");
    PMAC->SendCommand("M4=1");
   // PMAC->SendCommand("M2=0");


}

void MainWindow::on_pushButton_46_clicked()//关门
{
    int door_sta=ui->comboBox_7->currentIndex();
    if(door_sta==0)
    {
        QMessageBox::information(this,"提示","门由面板按钮控制，请选择由软件控制");
        return;
    }
      PMAC->SendCommand("M4=0");
    PMAC->SendCommand("M2=1");
   // PMAC->SendCommand("M4=0");

}

void MainWindow::on_pushButton_47_clicked()//开液
{
    int fluid_sta=ui->comboBox_8->currentIndex();
    if(fluid_sta==1)
    {
        QMessageBox::information(this,"提示","抛光液由面板按钮控制，请选择由软件控制");
        return;
    }

    PMAC->SendCommand("M5=1");
}

void MainWindow::on_pushButton_48_clicked()//关液
{
    int fluid_sta=ui->comboBox_8->currentIndex();
    if(fluid_sta==1)
    {
        QMessageBox::information(this,"提示","抛光液由面板按钮控制，请选择由软件控制");
        return;
    }
     PMAC->SendCommand("M5=0");
}

//void MainWindow::on_pushButton_50_clicked()//夹紧
//{
//     PMAC->SendCommand("ENABLE PLC1");
//}

void MainWindow::on_pushButton_49_clicked()//松开
{
   // PMAC->SendCommand("M3=0");
    PMAC->SendCommand("ENABLE PLC1");

}


void MainWindow::on_pushButton_37_clicked()//原点复位
{
    QIcon icon= windowIcon();
    QMessageBox megBox;
    megBox.setIcon(QMessageBox::Question);
    megBox.setWindowIcon(icon);
    megBox.setWindowTitle("提示");
    megBox.addButton("是",QMessageBox::AcceptRole);
    megBox.addButton("否",QMessageBox::RejectRole);
    megBox.setText("是否进行原点复位？");
    int result= megBox.exec();
    if (result==QMessageBox::AcceptRole)
    {
         PMAC->SendCommand("ENABLE PLC5");//
    }
     else
         return;

}

void MainWindow::on_actiondisconnect_triggered()//断开
{
    bool pbsuccess;//连接pmac成功否

  //  Pmac->Close(0,pbsuccess);//连接控制器0
    Pmac->Close(0);



}

void MainWindow::on_pushButton_17_released()//终止加工
{
    PMAC->SendCommand("&1B1R");//执行回零位程序

}

void MainWindow::on_pushButton_17_pressed()//终止加工
{
    PMAC->SendCommand("&1A");//停止加工程序

}

void MainWindow::on_actionversion_triggered()//版本信息
{
//    QIcon icon= windowIcon();


//   QMessageBox megBox;
//   megBox.setIcon(QMessageBox::Information);
//   megBox.setWindowIcon(icon);
//   megBox.setWindowTitle("版本信息");
//   megBox.addButton("确定",QMessageBox::AcceptRole);
   QMessageBox::information(this,"版本信息","Version 1.0\n Copyright(c) BEIJING HECHUANGZHIDA \n All rights reserved!");
  // megBox.addButton("否",QMessageBox::RejectRole);
  // megBox.setText("Version 1.0/n Copyright(c) GUANGZHOU JINDDIAN /n All rights reserved!");
}

void MainWindow::on_actionsystem_valuesetting_triggered()//系统参数设定
{
   // this->hide();
   myform=new Form;//参数设定对话框

    myform->show();

    //a.exec();

}

void MainWindow::on_actionopen_triggered()//导入外部倍率
{
    read_position->stop();
    QFileDialog* fd = new QFileDialog(this);//创建打开文件对话框
    QString path=QCoreApplication::applicationDirPath();
    QDir dir(path);//创建路径类
    if(!dir.exists("速度倍率"))//创建路径
        dir.mkdir("面型误差数据");
  //     dir.setPath(dir.path()+"/加工参数");//设置路径
    QString fileName = fd->getOpenFileName(this,tr("打开文件"),path+"\\速度倍率",tr("数据文件(*.csv)"));
    if(fileName == "")
         {
        read_position->stop();
        return;

    }

 //   QString name=fileName;
   // ui->lineEdit_dataname->setText(name.remove(path+"/面型误差数据/").split(".").at(0));
  //  QDir dir = QDir::current();
    QFile file(dir.filePath(fileName));

    if(!file.open(QIODevice::ReadOnly))
         qDebug()<<"OPEN FILE FAILED";
    QTextStream * out = new QTextStream(&file);//文本流
    QStringList tempOption = out->readAll().split("\n");//每行以\n区分
file.close();
qDebug()<<"tempOption.size"<<tempOption.size()-1;
    for(int i=0;i<tempOption.size()-2;i++)
    {
        external_rate.replace(i,tempOption.at(i+1).split(",").at(1).toDouble());
    }
   read_position->start();
}

void MainWindow::on_actionexit_triggered()//退出
{
    this->close();
}

void MainWindow::on_pushButton_38_clicked()//再原点
{
    QIcon icon= windowIcon();
    QMessageBox megBox;
    megBox.setIcon(QMessageBox::Question);
    megBox.setWindowIcon(icon);
    megBox.setWindowTitle("提示");
    megBox.addButton("是",QMessageBox::AcceptRole);
    megBox.addButton("否",QMessageBox::RejectRole);
    megBox.setText("是否设定当前位置为原点？");
    int result= megBox.exec();
    double x_pos,b_pos,z_pos,y_pos;
    PMAC->GetPositon(1,x_pos);
    PMAC->GetPositon(3,y_pos);
    PMAC->GetPositon(4,z_pos);
    PMAC->GetPositon(2,b_pos);
    if (result==QMessageBox::AcceptRole)
    {
         //PMAC->SendCommand("ENABLE PLC5");//

        QString str;//参数文件字符
        QString strPath=QCoreApplication::applicationDirPath();//获取程序当前路径
       // QDir dir(strPath);//实例化文件路径类
        QFile *file=new QFile();//实例化文件读取对象
        QStringList list;
        QDir dir(strPath);//创建路径类
        QString filepath=dir.path()+"\\home_value.txt";
        if(filepath.isEmpty())//取消读取
            return;
        file->setFileName(filepath);//目标文件
//        if(filepath.isEmpty())//取消读取
//            return;
//        file->setFileName(filepath);//目标文件

        if(!file->open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QMessageBox::information(NULL,"提示！","读取原点参数失败！");
          // QMessageBox()
            return;

        }

        while (!file->atEnd())
        {

            str=file->readLine();
            str=str.remove("\n");
            list.append(str);

        }
     file->close();
        double x=list.at(0).split(":").at(1).toDouble();
        double y=list.at(1).split(":").at(1).toDouble();
        double z=list.at(2).split(":").at(1).toDouble();
        double b=list.at(3).split(":").at(1).toDouble();
        file->close();

        if(!file->open(QIODevice::WriteOnly|QIODevice::Text))
           {
            QMessageBox::information(this,"提示！","文件保存失败！");
            return;
           }
        QTextStream filestream(file);

        filestream<<"x_pos:"+QString::number(x_pos*16+x)<<"\n"
                 <<"y_pos:"+QString::number(y_pos*16+y)<<"\n"
                 <<"z_pos:"+QString::number(z_pos*16+z)<<"\n"
                 <<"b_pos:"+QString::number(b_pos*16+b)<<"\n";

        file->close();


        MainWindow::PMAC->SetP(30,x_pos*16+x);//X回零偏置
        MainWindow::PMAC->SetP(24,y_pos*16+y);//y回零偏置
        MainWindow::PMAC->SetP(29,0);//z回零偏置
        MainWindow::PMAC->SetP(31,b_pos*16+b);//b回零偏置
        PMAC->SendCommand("#1hmz");
         PMAC->SendCommand("#2hmz");
          PMAC->SendCommand("#3hmz");
           PMAC->SendCommand("#5hmz");
        QMessageBox::information(this,"提示","原点设定成功！");
    }
     else
         return;

}

void MainWindow::on_pushButton_54_clicked()//X回零
{
    PMAC->SendCommand("ENABLE PLC11");
}

void MainWindow::on_pushButton_53_clicked()//Y回零
{
    PMAC->SendCommand("ENABLE PLC14");
}

void MainWindow::on_pushButton_52_clicked()//Z回零
{
    PMAC->SendCommand("ENABLE PLC13");
}


void MainWindow::on_pushButton_51_clicked()//B回零
{
     PMAC->SendCommand("ENABLE PLC12");

}

void MainWindow::on_actionreset_system_value_triggered()
{

}

void MainWindow::on_pushButton_31_clicked()
{

}

void MainWindow::on_pushButton_18_clicked()
{

}

void MainWindow::on_pushButton_33_clicked()//抛光轴转动
{
    double velocity=ui->lineEdit_45->text().toDouble();
    QString speed=ui->lineEdit_45->text().trimmed();
    int M_Velocity;
    int DIR;

    if(ui->comboBox_5->currentIndex()==1)//转动方向
     {  Hz_start(0,speed);
    PMAC->SetP(1,1);}
    else {
       // DIR=0;
        Hz_start(1,speed);
        PMAC->SetP(1,1);
    }
qDebug()<<speed;
    if(velocity>19500)//速度限定
       {
        QMessageBox::information(this,"提示","抛光轴速度设定过大！");
                return;
        }

}

void MainWindow::on_pushButton_23_clicked()
{


}

void MainWindow::on_pushButton_30_pressed()
{

}

//void MainWindow::on_action12_triggered()//连接抛光轴
//{


//}

void MainWindow::on_comboBox_8_currentIndexChanged(int index)
{
    if (index==0)
        PMAC->SetP(4,1);
    else {
        PMAC->SetP(4,0);
    }


}


void MainWindow::on_actionlianji_triggered()
{

   serialForm=new DialogSerail;//参数设定对话框
   serialForm->show();


}

void MainWindow::on_actionversion_2_triggered()
{
    QMessageBox::information(this,"版本信息","Version 1.0\n Copyright(c) BEIJING HECHUANGZHIDA \n All rights reserved!");

}

void MainWindow::on_actionreset_system_value_toggled(bool arg1)
{

}
