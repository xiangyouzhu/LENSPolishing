#include "init_fun.h"
#include"mainwindow.h"
//#include"ui_mainwindow.h"




//#include <ui_mainwindow.h>



//using namespace  ui;
 static Ui::MainWindow *uii = nullptr;

void fun_init(Ui::MainWindow *ui_ptr)
{
uii = ui_ptr;
}

void readSystemValue()
{
   // QFileDialog* fd = new QFileDialog();//创建打开文件对话框
    QString path=QCoreApplication::applicationDirPath();
    QDir dir(path);//创建路径类

    QString fileName = dir.path()+"\\system_value.csv";
            if(fileName == "")
          return;
  //  QDir dir = QDir::current();
    QFile file(dir.filePath(fileName));

    if(!file.open(QIODevice::ReadOnly))
         qDebug()<<"OPEN FILE FAILED";
    QTextStream * out = new QTextStream(&file);//文本流
    QStringList m_datas = out->readAll().split("\n");//每行以\n区分

   file.close();//关闭文件


 MainWindow::Lworkpiece_h = QString(m_datas.at(1).split(",").at(1)).toDouble(); //为L型件底面到中心孔高度，单位mm/
                 //   qDebug()<<MainWindow::Lworkpiece_h;
    MainWindow::other_h =QString(m_datas.at(2).split(",").at(1)).toDouble();//L型件底面到夹具底面高度，单位mm/
    MainWindow::U_motor_scale_factor = QString(m_datas.at(3).split(",").at(1)).toDouble();//C轴电压转速比例因子
    MainWindow::U_motor_offset = QString(m_datas.at(4).split(",").at(1)).toDouble();//C轴电压转速比例一次变换偏差
   MainWindow::xlimit_left =QString(m_datas.at(5).split(",").at(1)).toDouble();;//抛光轴电压转速比例因子
   MainWindow::xlimit_right = QString(m_datas.at(6).split(",").at(1)).toDouble();//抛光轴电压转速比例一次变换偏差
   MainWindow::ylimit_bakcward = QString(m_datas.at(7).split(",").at(1)).toDouble();//多段抛光Z轴上升和下降速度，单位mm/分钟
   MainWindow::ylimit_forward =QString(m_datas.at(8).split(",").at(1)).toDouble();//多段抛光XB轴到初始位速度，单位mm/分钟

   MainWindow::zlimit_up = QString(m_datas.at(9).split(",").at(1)).toDouble();//Z轴上极限位置，单位mm/
   MainWindow::zlimit_down =QString(m_datas.at(10).split(",").at(1)).toDouble();//Z轴下极限位置，单位mm/

   MainWindow::blimit_left =QString(m_datas.at(11).split(",").at(1)).toDouble();//X轴极限位置，左右对称，单位mm
   MainWindow::blimit_right =QString(m_datas.at(12).split(",").at(1)).toDouble();;//B轴极限位置，左右对称，单位度
   MainWindow::C_axi_maxfeed = QString(m_datas.at(13).split(",").at(1)).toDouble();//C轴最大速度,r/min

   MainWindow::C_axi_minspeed = QString(m_datas.at(14).split(",").at(1)).toDouble();//C轴最小速度,r/min
   MainWindow::C_Button_speed = QString(m_datas.at(15).split(",").at(1)).toDouble();//C轴按钮速度,r/min

  // MainWindow::min_z =QString(m_datas.at(13).split(",").at(1)).toDouble();//数控代码Z的最小值，单位mm/
   MainWindow::polish_axi_maxfeed =QString(m_datas.at(16).split(",").at(1)).toDouble();//抛光轴最大速度,r/min
  MainWindow::polish_axi_minfeed = QString(m_datas.at(17).split(",").at(1)).toDouble();//抛光轴最小速度,r/min

   MainWindow::x_axi_hand_maxfeed = QString(m_datas.at(18).split(",").at(1)).toDouble();//X轴手动最大速度，单位mm/分钟
   MainWindow::y_axi_hand_maxfeed = QString(m_datas.at(19).split(",").at(1)).toDouble();//X轴手动最大速度，单位mm/分钟
    MainWindow::z_axi_hand_maxfeed = QString(m_datas.at(20).split(",").at(1)).toDouble();//z轴手动最大速度，单位mm/分钟
   MainWindow::b_axi_hand_maxfeed = QString(m_datas.at(21).split(",").at(1)).toDouble();//b轴手动最大速度，单位mm/分钟



 //  MainWindow::caculate_time_offset = QString(m_datas.at(22).split(",").at(1)).toDouble();//时间计算补正系数，单位分钟
   MainWindow::first_position_feed=QString(m_datas.at(22).split(",").at(1)).toDouble();//X_b_Z初始位速度，单位mm/分钟

   MainWindow::x_devia_value = QString(m_datas.at(23).split(",").at(1)).toDouble();//X轴回零偏移量，mm
    MainWindow::y_devia_value = QString(m_datas.at(24).split(",").at(1)).toDouble();//y轴回零偏移量，mm
    MainWindow::z_devia_value =QString(m_datas.at(25).split(",").at(1)).toDouble();//Z轴回零偏移量，mm

   MainWindow::b_devia_value = QString(m_datas.at(26).split(",").at(1)).toDouble();//B轴回零偏移量,度

   MainWindow::z_axi_first_jogdownfeed = QString(m_datas.at(27).split(",").at(1)).toDouble();//抛光Z轴下降手动速度；
  MainWindow::Cloth_minthickness = QString(m_datas.at(28).split(",").at(1)).toDouble();//抛光Z轴下降手动速度；

  //  MainWindow::B_axi_Center_Polish_head_distance = QString(m_datas.at(29).split(",").at(1)).toDouble();//在零位时，B轴回转中心到抛光头触碰到第二个限位的距离；

   //qDebug()<<MainWindow::B_axi_Center_Polish_head_distance;

   for (int i=0;i<800;i++)//初始化外部倍率
   {
       MainWindow::external_rate.push_back(1);
   }



   QString str;//参数文件字符
   QString strPath=QCoreApplication::applicationDirPath();//获取程序当前路径
  // QDir dir(strPath);//实例化文件路径类
   QFile *file2=new QFile();//实例化文件读取对象
   QStringList list;
   QString filepath=dir.path()+"\\home_value.txt";
   if(filepath.isEmpty())//取消读取
       return;
   file2->setFileName(filepath);//目标文件
   if(filepath.isEmpty())//取消读取
       return;
   file2->setFileName(filepath);//目标文件

   if(!file2->open(QIODevice::ReadOnly|QIODevice::Text))
   {
       QMessageBox::information(NULL,"提示！","读取原点参数失败！");
     // QMessageBox()
       return;

   }

   while (!file2->atEnd())
   {

       str=file2->readLine();
       str=str.remove("\n");
       list.append(str);

   }
file2->close();
   double x_pos=list.at(0).split(":").at(1).toDouble();
   double y_pos=list.at(1).split(":").at(1).toDouble();
   double z_pos=list.at(2).split(":").at(1).toDouble();
   double b_pos=list.at(3).split(":").at(1).toDouble();

  MainWindow::PMAC->SetP(30,x_pos);//X回零偏置
  MainWindow::PMAC->SetP(24,y_pos);//y回零偏置
  MainWindow::PMAC->SetP(29,z_pos);//z回零偏置
  MainWindow::PMAC->SetP(31,b_pos);//b回零偏置

}

void init_motion_control_gui()
{
    uii->lineEdit_35->setText("0");//X
    uii->lineEdit_36->setText("0");//Y
    uii->lineEdit_37->setText("0");//Z
    uii->lineEdit_38->setText("0");//B
    uii->lineEdit_39->setText("0");//C
      uii->lineEdit_45->setText("50");//U

      uii->lineEdit_47->setText("5");//X
      uii->lineEdit_49->setText("5");//Y
      uii->lineEdit_48->setText("5");//Z
       uii->lineEdit_51->setText("10");//B
        uii->lineEdit_46->setText("10");//C
        uii->comboBox_5->setCurrentIndex(0);//点位
          uii->comboBox_5->setCurrentIndex(0);//U方向
          uii->comboBox_7->setCurrentIndex(1);//门开关由软件控制
uii->lineEdit_ProcessCycle_2->setText("1");//标准加工次数
uii->lineEdit_ProcessCycle_3->setText("1");//补正加工次数
//ui->groupBox_2->setStyleSheet(QObject::tr("border: 3px solid;"));

}

void Init_Timer()
{

}


bool checkOnly()
{
    //  创建互斥量
    HANDLE m_hMutex  =  CreateMutex(NULL, FALSE,  L"fortest_abc123" );
    //  检查错误代码
    if  (GetLastError()  ==  ERROR_ALREADY_EXISTS)  {
      //  如果已有互斥量存在则释放句柄并复位互斥量
     CloseHandle(m_hMutex);
     m_hMutex  =  NULL;
      //  程序退出
      return  false;
    }
    else
        return true;

}
