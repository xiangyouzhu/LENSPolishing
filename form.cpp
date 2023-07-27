#include "form.h"
#include "ui_form.h"
#include "QDir"
#include"QDebug"
#include"mainwindow.h"
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

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
ui->tableWidget->setItem(0,0,new QTableWidgetItem(m_datas.at(1).split(",").at(1)));
ui->tableWidget->setItem(1,0,new QTableWidgetItem(m_datas.at(2).split(",").at(1)));
ui->tableWidget->setItem(2,0,new QTableWidgetItem(m_datas.at(3).split(",").at(1)));
ui->tableWidget->setItem(3,0,new QTableWidgetItem(m_datas.at(4).split(",").at(1)));
ui->tableWidget->setItem(4,0,new QTableWidgetItem(m_datas.at(5).split(",").at(1)));
ui->tableWidget->setItem(5,0,new QTableWidgetItem(m_datas.at(6).split(",").at(1)));
ui->tableWidget->setItem(6,0,new QTableWidgetItem(m_datas.at(7).split(",").at(1)));
ui->tableWidget->setItem(7,0,new QTableWidgetItem(m_datas.at(8).split(",").at(1)));
ui->tableWidget->setItem(8,0,new QTableWidgetItem(m_datas.at(9).split(",").at(1)));
ui->tableWidget->setItem(9,0,new QTableWidgetItem(m_datas.at(10).split(",").at(1)));
ui->tableWidget->setItem(10,0,new QTableWidgetItem(m_datas.at(11).split(",").at(1)));
ui->tableWidget->setItem(11,0,new QTableWidgetItem(m_datas.at(12).split(",").at(1)));
ui->tableWidget->setItem(12,0,new QTableWidgetItem(m_datas.at(13).split(",").at(1)));
ui->tableWidget->setItem(13,0,new QTableWidgetItem(m_datas.at(14).split(",").at(1)));
ui->tableWidget->setItem(14,0,new QTableWidgetItem(m_datas.at(15).split(",").at(1)));
ui->tableWidget->setItem(15,0,new QTableWidgetItem(m_datas.at(16).split(",").at(1)));
ui->tableWidget->setItem(16,0,new QTableWidgetItem(m_datas.at(17).split(",").at(1)));
ui->tableWidget->setItem(17,0,new QTableWidgetItem(m_datas.at(18).split(",").at(1)));
ui->tableWidget->setItem(18,0,new QTableWidgetItem(m_datas.at(19).split(",").at(1)));
ui->tableWidget->setItem(19,0,new QTableWidgetItem(m_datas.at(20).split(",").at(1)));
ui->tableWidget->setItem(20,0,new QTableWidgetItem(m_datas.at(21).split(",").at(1)));
ui->tableWidget->setItem(21,0,new QTableWidgetItem(m_datas.at(22).split(",").at(1)));
ui->tableWidget->setItem(22,0,new QTableWidgetItem(m_datas.at(23).split(",").at(1)));
ui->tableWidget->setItem(23,0,new QTableWidgetItem(m_datas.at(24).split(",").at(1)));
ui->tableWidget->setItem(24,0,new QTableWidgetItem(m_datas.at(25).split(",").at(1)));
ui->tableWidget->setItem(25,0,new QTableWidgetItem(m_datas.at(26).split(",").at(1)));
ui->tableWidget->setItem(26,0,new QTableWidgetItem(m_datas.at(27).split(",").at(1)));
ui->tableWidget->setItem(27,0,new QTableWidgetItem(m_datas.at(28).split(",").at(1)));


}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()//应用
{

    QString path=QCoreApplication::applicationDirPath();
    QDir dir(path);//创建路径类

    QString fileName = dir.path()+"\\system_value.csv";
            if(fileName == "")
          return;
  //  QDir dir = QDir::current();
//    QFile file(dir.filePath(fileName));

//    if(!file.open(QIODevice::ReadOnly))
//         qDebug()<<"OPEN FILE FAILED";
//    QTextStream * out = new QTextStream(&file);//文本流
//    QStringList m_datas = out->readAll().split("\n");//每行以\n区分

//   file.close();//关闭文件

   fileName = dir.path()+"\\system_value.csv";
   QFile file2(dir.filePath(fileName));
   QString line_0="B rotation radius,"+ui->tableWidget->item(0,0)->text()+"\n";
   QString line_1="B rotation to plane,"+ui->tableWidget->item(1,0)->text()+"\n";
   QString line_2="U_motor_scale_factor,"+ui->tableWidget->item(2,0)->text()+"\n";
   QString line_3="U_motor_offset,"+ui->tableWidget->item(3,0)->text()+"\n";
   QString line_4="xlimit_left,"+ui->tableWidget->item(4,0)->text()+"\n";
   QString line_5="xlimit_right,"+ui->tableWidget->item(5,0)->text()+"\n";
   QString line_6="ylimit_bakcward,"+ui->tableWidget->item(6,0)->text()+"\n";
   QString line_7="ylimit_forward,"+ui->tableWidget->item(7,0)->text()+"\n";
   QString line_8="zlimit_up,"+ui->tableWidget->item(8,0)->text()+"\n";
   QString line_9="zlimit_down,"+ui->tableWidget->item(9,0)->text()+"\n";
   QString line_10="blimit_left,"+ui->tableWidget->item(10,0)->text()+"\n";
   QString line_11="blimit_right,"+ui->tableWidget->item(11,0)->text()+"\n";
   QString line_12="C_axi_maxfeed,"+ui->tableWidget->item(12,0)->text()+"\n";
   QString line_13="C_axi_minspeed,"+ui->tableWidget->item(13,0)->text()+"\n";
   QString line_14="C_Button_speed,"+ui->tableWidget->item(14,0)->text()+"\n";
   QString line_15="polish_axi_maxfeed,"+ui->tableWidget->item(15,0)->text()+"\n";
   QString line_16="polish_axi_minfeed,"+ui->tableWidget->item(16,0)->text()+"\n";
   QString line_17="x_axi_hand_maxfeed,"+ui->tableWidget->item(17,0)->text()+"\n";
   QString line_18="y_axi_hand_maxfeed ,"+ui->tableWidget->item(18,0)->text()+"\n";
   QString line_19="z_axi_hand_maxfeed,"+ui->tableWidget->item(19,0)->text()+"\n";
   QString line_20="b_axi_hand_maxfeed,"+ui->tableWidget->item(20,0)->text()+"\n";
   QString line_21="first_position_feed,"+ui->tableWidget->item(21,0)->text()+"\n";
   QString line_22="x_devia_value,"+ui->tableWidget->item(22,0)->text()+"\n";
   QString line_23="y_devia_value,"+ui->tableWidget->item(23,0)->text()+"\n";
   QString line_24="z_devia_value,"+ui->tableWidget->item(24,0)->text()+"\n";
   QString line_25="b_devia_value,"+ui->tableWidget->item(25,0)->text()+"\n";
   QString line_26="z_axi_first_jogdownfeed,"+ui->tableWidget->item(26,0)->text()+"\n";
   QString line_27="cloth_thickness,"+ui->tableWidget->item(27,0)->text()+"\n";





   if(file2.open(QIODevice::ReadWrite))
   {
      // file.write(m_datas.at(1).split(",").at(0).toStdU16String());
      // toLocal8Bit()
   //    data="B_L，"+ui->tableWidget->item(0,1)->text();
       file2.write("parameters,vlaue\n");
      file2.write(line_0.toUtf8());
      file2.write(line_1.toUtf8());
       file2.write(line_2.toUtf8());
       file2.write(line_3.toUtf8());
        file2.write(line_4.toUtf8());
        file2.write(line_5.toUtf8());
         file2.write(line_6.toUtf8());
         file2.write(line_7.toUtf8());
          file2.write(line_8.toUtf8());
          file2.write(line_9.toUtf8());
           file2.write(line_10.toUtf8());
           file2.write(line_11.toUtf8());
            file2.write(line_12.toUtf8());
            file2.write(line_13.toUtf8());
             file2.write(line_14.toUtf8());
             file2.write(line_15.toUtf8());
              file2.write(line_16.toUtf8());
              file2.write(line_17.toUtf8());
               file2.write(line_18.toUtf8());
               file2.write(line_19.toUtf8());
                file2.write(line_20.toUtf8());
                file2.write(line_21.toUtf8());
                 file2.write(line_22.toUtf8());
                 file2.write(line_23.toUtf8());
                  file2.write(line_24.toUtf8());
                  file2.write(line_25.toUtf8());
                   file2.write(line_26.toUtf8());
                   file2.write(line_27.toUtf8());

   }
file2.close();


MainWindow::Lworkpiece_h = QString(ui->tableWidget->item(0,0)->text().trimmed()).toDouble(); //为L型件底面到中心孔高度，单位mm/
                //   qDebug()<<MainWindow::Lworkpiece_h;
   MainWindow::other_h =QString(ui->tableWidget->item(1,0)->text().trimmed()).toDouble();//L型件底面到夹具底面高度，单位mm/
   MainWindow::U_motor_scale_factor = QString(ui->tableWidget->item(2,0)->text().trimmed()).toDouble();//C轴电压转速比例因子
   MainWindow::U_motor_offset = QString(ui->tableWidget->item(3,0)->text().trimmed()).toDouble();//C轴电压转速比例一次变换偏差
  MainWindow::xlimit_left =QString(ui->tableWidget->item(4,0)->text().trimmed()).toDouble();;//抛光轴电压转速比例因子
  MainWindow::xlimit_right = QString(ui->tableWidget->item(5,0)->text().trimmed()).toDouble();//抛光轴电压转速比例一次变换偏差
  MainWindow::ylimit_bakcward = QString(ui->tableWidget->item(6,0)->text().trimmed()).toDouble();//多段抛光Z轴上升和下降速度，单位mm/分钟
  MainWindow::ylimit_forward =QString(ui->tableWidget->item(7,0)->text().trimmed()).toDouble();//多段抛光XB轴到初始位速度，单位mm/分钟

  MainWindow::zlimit_up = QString(ui->tableWidget->item(8,0)->text().trimmed()).toDouble();//Z轴上极限位置，单位mm/
  MainWindow::zlimit_down =QString(ui->tableWidget->item(9,0)->text().trimmed()).toDouble();//Z轴下极限位置，单位mm/

  MainWindow::blimit_left =QString(ui->tableWidget->item(10,0)->text().trimmed()).toDouble();//X轴极限位置，左右对称，单位mm
  MainWindow::blimit_right =QString(ui->tableWidget->item(11,0)->text().trimmed()).toDouble();;//B轴极限位置，左右对称，单位度
  MainWindow::C_axi_maxfeed = QString(ui->tableWidget->item(12,0)->text().trimmed()).toDouble();//C轴最大速度,r/min

  MainWindow::C_axi_minspeed = QString(ui->tableWidget->item(13,0)->text().trimmed()).toDouble();//C轴最小速度,r/min
  MainWindow::C_Button_speed = QString(ui->tableWidget->item(14,0)->text().trimmed()).toDouble();//C轴按钮速度,r/min

 // MainWindow::min_z =QString(m_datas.at(13).split(",").at(1)).toDouble();//数控代码Z的最小值，单位mm/
  MainWindow::polish_axi_maxfeed =QString(ui->tableWidget->item(15,0)->text().trimmed()).toDouble();//抛光轴最大速度,r/min
 MainWindow::polish_axi_minfeed = QString(ui->tableWidget->item(16,0)->text().trimmed()).toDouble();//抛光轴最小速度,r/min

  MainWindow::x_axi_hand_maxfeed = QString(ui->tableWidget->item(17,0)->text().trimmed()).toDouble();//X轴手动最大速度，单位mm/分钟
  MainWindow::y_axi_hand_maxfeed = QString(ui->tableWidget->item(18,0)->text().trimmed()).toDouble();//y轴手动最大速度，单位mm/分钟
   MainWindow::z_axi_hand_maxfeed = QString(ui->tableWidget->item(19,0)->text().trimmed()).toDouble();//z轴手动最大速度，单位mm/分钟
  MainWindow::b_axi_hand_maxfeed = QString(ui->tableWidget->item(20,0)->text().trimmed()).toDouble();//b轴手动最大速度，单位mm/分钟



//  MainWindow::caculate_time_offset = QString(m_datas.at(22).split(",").at(1)).toDouble();//时间计算补正系数，单位分钟
  MainWindow::first_position_feed=QString(ui->tableWidget->item(21,0)->text().trimmed()).toDouble();//X_b_Z初始位速度，单位mm/分钟

  MainWindow::x_devia_value = QString(ui->tableWidget->item(22,0)->text().trimmed()).toDouble();//X轴回零偏移量，mm
   MainWindow::y_devia_value = QString(ui->tableWidget->item(23,0)->text().trimmed()).toDouble();//X轴回零偏移量，mm
   MainWindow::z_devia_value =QString(ui->tableWidget->item(24,0)->text().trimmed()).toDouble();//Z轴回零偏移量，mm

  MainWindow::b_devia_value = QString(ui->tableWidget->item(25,0)->text().trimmed()).toDouble();//B轴回零偏移量,度

  MainWindow::z_axi_first_jogdownfeed = QString(ui->tableWidget->item(26,0)->text().trimmed()).toDouble();//抛光Z轴下降手动速度；
   MainWindow::Cloth_thickness = QString(ui->tableWidget->item(27,0)->text().trimmed()).toDouble();//抛光垫的厚度；

}

void Form::on_pushButton_2_clicked()//返回
{

    this->close();

}
