#include "readwritefile.h"
#include"mainwindow.h"
#include <ui_mainwindow.h>
#include "qvariantlistlistmodel.h"
#include<PmacApi.h>


using namespace  Ui;
static Ui::MainWindow *uii = nullptr;

void ui_init(Ui::MainWindow *ui_ptr)
{
    uii = ui_ptr;
}
void readHomeValue()
{


}
void readFileToshapeGUi()
{
    QString str;//参数文件字符
    QString strPath=QCoreApplication::applicationDirPath();//获取程序当前路径
    QDir dir(strPath);//实例化文件路径类
    QFile *file=new QFile();//实例化文件读取对象
    QStringList list;
    QString filepath=dir.path()+"\\paramenter_shape.txt";
    if(filepath.isEmpty())//取消读取
        return;
    file->setFileName(filepath);//目标文件

    if(!file->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::information(NULL,"提示！","读取形状参数失败！");
      // QMessageBox()
        return;

    }

    while (!file->atEnd())
    {

        str=file->readLine();
        str=str.remove("\n");
        list.append(str);

    }
uii->lineEdit_11->setText(list.at(0).split(":").at(1));//镜片名称,加工界面
uii->lineEdit_Lensname->setText(list.at(0).split(":").at(1));//镜片名称
uii->lineEdit_HC->setText(list.at(2).split(":").at(1));
uii->lineEdit_HE->setText(list.at(3).split(":").at(1));
//uii->lineEdit_H->setText(list.at(4).split(":").at(1));
uii->lineEdit_DP->setText(list.at(5).split(":").at(1));
uii->lineEdit_D->setText(list.at(6).split(":").at(1));
uii->lineEdit_R->setText(list.at(7).split(":").at(1));
uii->lineEdit_K->setText(list.at(8).split(":").at(1));
uii->lineEdit_A1->setText(list.at(9).split(":").at(1));
uii->lineEdit_A2->setText(list.at(10).split(":").at(1));
uii->lineEdit_A3->setText(list.at(11).split(":").at(1));
uii->lineEdit_A4->setText(list.at(12).split(":").at(1));
uii->lineEdit_A5->setText(list.at(13).split(":").at(1));
uii->lineEdit_A6->setText(list.at(14).split(":").at(1));
uii->lineEdit_A7->setText(list.at(15).split(":").at(1));
uii->lineEdit_A8->setText(list.at(16).split(":").at(1));
uii->lineEdit_A9->setText(list.at(17).split(":").at(1));
uii->lineEdit_A10->setText(list.at(18).split(":").at(1));
uii->lineEdit_A11->setText(list.at(19).split(":").at(1));
uii->lineEdit_A12->setText(list.at(20).split(":").at(1));
uii->lineEdit_A13->setText(list.at(21).split(":").at(1));
uii->lineEdit_A14->setText(list.at(22).split(":").at(1));
uii->lineEdit_A15->setText(list.at(23).split(":").at(1));
uii->lineEdit_A16->setText(list.at(24).split(":").at(1));
uii->lineEdit_A17->setText(list.at(25).split(":").at(1));
uii->lineEdit_A18->setText(list.at(26).split(":").at(1));
uii->lineEdit_A19->setText(list.at(27).split(":").at(1));
uii->lineEdit_A20->setText(list.at(28).split(":").at(1));
uii->lineEdit_yuan_r->setText(list.at(29).split(":").at(1));

QString shape_type=list.at(1).split(":").at(1);
int shape_id=shape_type.toInt();
QImage *img=new QImage;//新建图像对象
 QString file_tu=QCoreApplication::applicationDirPath()+"\\Image\\picture_tu.PNG";
 QString file_ao=QCoreApplication::applicationDirPath()+"\\Image\\picture_ao.PNG";

switch (shape_id)
{
case 1:
{
    uii->Lens_ao->setChecked(true);
    img->load(file_ao);
    uii->label_16->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img

     break;
}

case 2:
   {
    uii->Lens_tu->setChecked(true);
    img->load(file_tu);
    uii->label_16->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img

    break;
   }

//case 3:
//    uii->Lens_plane->setChecked(true);
//    break;
}
file->close();
delete file;
double A[20];
A[0]=uii->lineEdit_A1->  text().toDouble();
A[1]=uii->lineEdit_A2->  text().toDouble();
A[2]=uii->lineEdit_A3->  text().toDouble();
A[3]=uii->lineEdit_A4->  text().toDouble();
A[4]=uii->lineEdit_A5->  text().toDouble();
A[5]=uii->lineEdit_A6->  text().toDouble();
A[6]=uii->lineEdit_A7->  text().toDouble();
A[7]=uii->lineEdit_A8->  text().toDouble();
A[8]=uii->lineEdit_A9->  text().toDouble();
A[9]=uii->lineEdit_A10->  text().toDouble();
A[10]=uii->lineEdit_A11->  text().toDouble();
A[11]=uii->lineEdit_A12->  text().toDouble();
A[12]=uii->lineEdit_A13->  text().toDouble();
A[13]=uii->lineEdit_A14->  text().toDouble();
A[14]=uii->lineEdit_A15->  text().toDouble();
A[15]=uii->lineEdit_A16->  text().toDouble();
A[16]=uii->lineEdit_A17->  text().toDouble();
A[17]=uii->lineEdit_A18->  text().toDouble();
A[18]=uii->lineEdit_A19->  text().toDouble();
A[19]=uii->lineEdit_A20->  text().toDouble();
drawPlot(A);

}

void readFileToprocessGUi()
{

    QString str;//存放读取的文件
    QFile *file =new QFile();//实例化文件读取类
    QString filepath=QCoreApplication::applicationDirPath();//获取程序路径
    QDir dir(filepath);//创建路径类
    QStringList list;


       QString filename=dir.path()+"\\paramenter_process.txt";

       if(filename.isEmpty())//取消读取
           return;
       file->setFileName(filename);//目标文件

       if(!file->open(QIODevice::ReadOnly|QIODevice::Text))
       {
           QMessageBox::information(NULL,"提示！","读取失败！");
          return;

       }


       while(!file->atEnd())
       {
           str=file->readLine();
           str.remove("\n");
           list.append(str);
       }

   //     if(list.at(0)=="1")//恒转速
     //  uii->radioButton_constC->setChecked(true);

       uii->lineEdit_constCSpeed->setText(list.at(1));//C转速

  //      if(list.at(2)=="1")
   //    uii->radioButton_changedC->setChecked(true);//变转速

    //   uii->lineEdit_maxCspeed->setText(list.at(3));//最大C速度

       uii->comboBox_dataDistance->setCurrentIndex(list.at(4).toInt());//数据间隔
       uii->comboBox_toolRaidus->setCurrentIndex(list.at(5).toInt());//磨头直径
       uii->comboBox_Cdirect->setCurrentIndex(list.at(6).toInt());//C轴方向
       uii->comboBox_ToolDirect->setCurrentIndex(list.at(7).toInt());//抛光头方向

    //   if(list.at(8)=="1")//
     // ui-> radioButton_0degree->setChecked(true);//0度

     //  if(list.at(9)=="1")
    //  ui->radioButton_45degree->setChecked(true);//45度


       if(list.at(8)=="1")
      uii-> radioButton_constantFeed->setChecked(true);//恒进给

      uii-> lineEdit_constfeed->setText(list.at(9));//恒进给速度

       if(list.at(10)=="1")
      uii-> radioButton_ChangedFeed->setChecked(true);//变进给

       uii->lineEdit_feedrate->setText(list.at(11));//进给倍率
       uii->lineEdit_ProdessLeft->setText(list.at(12));//加工点左
      uii-> lineEdit_ProcessRight->setText(list.at(13));//加工点右
      uii-> lineEdit_Pressure->setText(list.at(14));//压力
       uii->lineEdit_Toolspeed->setText(list.at(15));//抛头转速
       uii->lineEdit_ProcessCycle->setText(list.at(16));//加工次数
       uii->lineEdit_ToolD->setText(list.at(17));//抛光头直径
       uii->lineEdit_ClothThick->setText(list.at(18));//抛光垫厚度
       uii->lineEdit_Toolhigh->setText(list.at(19));//工具头高度
     file->close();
   delete file;
}
void system_value()
{

}
void Init_customplot1(QCustomPlot *w)//面型图
{
    QList <QCPAxis*> axes;
    axes<<w->yAxis<<w->xAxis;
    w->addGraph();
    w->graph(0)->data().clear();
    w->xAxis->setVisible(true);
    w->yAxis->setVisible(true);
    w->xAxis->setRange(-10,10);
    w->yAxis->setRange(-10,10);
    w->graph(0)->rescaleValueAxis(true);
    w->axisRect()->setRangeZoomAxes(axes);
    w->axisRect()->setRangeDragAxes(axes);
    w->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void Init_customplot2(QCustomPlot *w)//面型误差数据图
{
    QList <QCPAxis*> axes;
    axes<<w->yAxis<<w->xAxis;
    w->addGraph();
    w->graph(0)->data().clear();
    w->xAxis->setVisible(true);
    w->yAxis->setVisible(true);
    w->xAxis->setRange(-20,20);
    w->yAxis->setRange(-1,1);
    w->graph(0)->rescaleValueAxis(true);
    w->axisRect()->setRangeZoomAxes(axes);
    w->axisRect()->setRangeDragAxes(axes);
    w->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    w->xAxis->setLabel("范围/mm");
    w->yAxis->setLabel("面型误差/um");
   // w->legend->setVisible(true);//设置图例可用

}
void Init_UiCustomPlot()
{

}
void drawPlot(double A[])//非球面面型图
{
 QVector <double> X, Y;
// double[] A = new double[20] { Convert.ToDouble(A1.Text), Convert.ToDouble(A2.Text), Convert.ToDouble(A3.Text), Convert.ToDouble(A4.Text), Convert.ToDouble(A5.Text), Convert.ToDouble(A6.Text), Convert.ToDouble(A7.Text), Convert.ToDouble(A8.Text), Convert.ToDouble(A9.Text), Convert.ToDouble(A10.Text), Convert.ToDouble(A11.Text), Convert.ToDouble(A12.Text), Convert.ToDouble(A13.Text), Convert.ToDouble(A14.Text), Convert.ToDouble(A15.Text), Convert.ToDouble(A16.Text), Convert.ToDouble(A17.Text), Convert.ToDouble(A18.Text), Convert.ToDouble(A19.Text), Convert.ToDouble(A20.Text) };
                     double R = uii->lineEdit_R->text().toDouble();  //面型参数R
                     double K = uii->lineEdit_K->text().toDouble();//面型参数K
                     double symbol=1;
                     double C = 1 / R;
                     double D = uii->lineEdit_DP->text().toDouble();//加工口径

                                 // if (tu_sphere.Checked == true || ao_sphere.Checked == true)
                                 // {
                                      if (D > 2 * qAbs(uii->lineEdit_R->text().toDouble()))
                                          D = 2 * qAbs(uii->lineEdit_R->text().toDouble());
                                 // }

                                  int a = (D / 0.01);
                     if (uii->Lens_ao->isChecked())
                     {
                         if (R > 0)
                             symbol = 1;
                         else
                             symbol = -1;

                     }
                     if (uii->Lens_tu->isChecked())
                     {
                         if (R > 0)
                             symbol = -1;
                         else
                             symbol = 1;

                     }


                     for (int i = 0; i < a + 1; i++)//x坐标
                     {
                        X.push_back( -D / 2 + i * 0.01);
                     }
//                      qDebug()<<A[1];
//                      qDebug()<<A[2];
//                      qDebug()<<A[3];
//                      qDebug()<<A[4];
//                      qDebug()<<A[5];
//                      qDebug()<<A[6];
//                      qDebug()<<A[7];
//                      qDebug()<<A[8];
                     for (int i = 0; i < a + 1; i++)//Y坐标，
                     {
//                         qDebug()<<"X[I]"<<X[i];
//                         qDebug()<<"X.at(i)"<<X.at(i);
//                         qDebug()<<A[1];
//                         double b=qPow(X.at(i), 2) * C / (1 + qSqrt(1 - (K + 1) * qPow(X.at(i), 2) * qPow(C, 2)));// + A[0] * qAbs(X.at(i)) + A[1] * qPow((X.at(i)), 2) + A[2] * qPow(qAbs(X.at(i)), 3) + A[3] * qPow((X.at(i)), 4) + A[4] * qPow(qAbs(X.at(i)), 5) + A[5] * qPow((X.at(i)), 6) + A[6] * qPow(qAbs(X.at(i)), 7) + A[7] * qPow((X.at(i)), 8) + A[8] * qPow(qAbs(X.at(i)), 9) + A[9] * qPow((X.at(i)), 10) + A[10] * qPow(qAbs(X.at(i)), 11) + A[11] * qPow((X.at(i)), 12) + A[12] * qPow(qAbs(X.at(i)), 13) + A[13] * qPow((X.at(i)), 14) + A[14] * qPow(qAbs(X.at(i)), 15) + A[15] * qPow((X.at(i)), 16) + A[16] * qPow(qAbs(X.at(i)), 17) + A[17] * qPow((X.at(i)), 18) + A[18] * qPow(qAbs(X.at(i)), 19) + A[19] * qPow((X.at(i)), 20);
//                         double a=A[0] * qAbs(X.at(i)) + A[1] * qPow((X.at(i)), 2)+ A[2] * qPow(qAbs(X.at(i)), 3) + A[3] * qPow((X.at(i)), 4) + A[4] * qPow(qAbs(X.at(i)), 5) + A[5] * qPow((X.at(i)), 6) + A[6] * qPow(qAbs(X.at(i)), 7) + A[7] * qPow((X.at(i)), 8) + A[8] * qPow(qAbs(X.at(i)), 9) + A[9] * qPow((X.at(i)), 10) + A[10] * qPow(qAbs(X.at(i)), 11) + A[11] * qPow((X.at(i)), 12) + A[12] * qPow(qAbs(X.at(i)), 13) + A[13] * qPow((X.at(i)), 14) + A[14] * qPow(qAbs(X.at(i)), 15) + A[15] * qPow((X.at(i)), 16) + A[16] * qPow(qAbs(X.at(i)), 17) + A[17] * qPow((X.at(i)), 18) + A[18] * qPow(qAbs(X.at(i)), 19);// + A[19] * qPow((X.at(i)), 20);
//                         double c=A[16] * qPow(qAbs(X.at(i)), 17) + A[17] * qPow((X.at(i)), 18) + A[18] * qPow(qAbs(X.at(i)), 19);// + A[19] * qPow((X.at(i)), 20);
//                        double d=A[19] * qPow((X.at(i)), 20);
//                         qDebug()<<a;
//                         qDebug()<<b;
//                         qDebug()<<c;
//                         qDebug()<<"A19"<<A[19];
                         Y.push_back(symbol * (qPow(X.at(i), 2) * C / (1 + qSqrt(1 - (K + 1) * qPow(X.at(i), 2) * qPow(C, 2))) + A[0] * qAbs(X.at(i)) + A[1] * qPow((X.at(i)), 2) + A[2] * qPow(qAbs(X.at(i)), 3) + A[3] * qPow((X.at(i)), 4) + A[4] * qPow(qAbs(X.at(i)), 5) + A[5] * qPow((X.at(i)), 6) + A[6] * qPow(qAbs(X.at(i)), 7) + A[7] * qPow((X.at(i)), 8) + A[8] * qPow(qAbs(X.at(i)), 9) + A[9] * qPow((X.at(i)), 10) + A[10] * qPow(qAbs(X.at(i)), 11) + A[11] * qPow((X.at(i)), 12) + A[12] * qPow(qAbs(X.at(i)), 13) + A[13] * qPow((X.at(i)), 14) + A[14] * qPow(qAbs(X.at(i)), 15) + A[15] * qPow((X.at(i)), 16) + A[16] * qPow(qAbs(X.at(i)), 17) + A[17] * qPow((X.at(i)), 18) + A[18] * qPow(qAbs(X.at(i)), 19) + A[19] * qPow((X.at(i)), 20)));

                     }

                     auto maxX=std::max_element(std::begin(X), std::end(X));
                     auto minY=std::min_element(std::begin(Y), std::end(Y));
                     auto max_yy=std::max_element(std::begin(Y), std::end(Y));
                     double max_x=*maxX;
                     double max_y=*minY;
                     double max_YY=*max_yy;
                     if(qAbs(max_y)<qAbs(max_YY))
                         max_y=max_YY;

                     //QList <QCPAxis*> axes;
                     //axes<<ui->customPlot_2->yAxis<<ui->customPlot_2->yAxis2;
                     //ui->customPlot_2->xAxis->setVisible(true);
                     //ui->customPlot_2->yAxis->setVisible(true);
                    // qDebug()<<max_x;
                    // qDebug()<<max_y;
                     uii->customPlot->xAxis->setRange(-qAbs(max_x)*1.5,qAbs(max_x)*1.5);
                     uii->customPlot->yAxis->setRange(-qAbs(max_y*0.5),qAbs(max_y*0.5));
                     uii->customPlot->clearGraphs();

                     uii->customPlot->addGraph();
    uii->customPlot->graph(0)->setData(X,Y);
    uii->customPlot->replot();

}
void drawPlot_errdata(QVector <double>X,QVector <double>Y)
{
    uii->customPlot_2->graph(0)->setData(X,Y);
    uii->customPlot_2->replot();
}
QVector<double> readFeedVelocityFile(QString fileName)
{

    QString str;//参数文件字符
    QString strPath=QCoreApplication::applicationDirPath();//获取程序当前路径
    QDir dir(strPath);//实例化文件路径类
    QFile *file=new QFile();//实例化文件读取对象
   // QStringList list;
    QVector<double> Feedspeed;

    QString filepath=dir.path()+"\\"+fileName;
    if(filepath.isEmpty())//取消读取
        return Feedspeed;
    file->setFileName(filepath);//目标文件

    if(!file->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::information(NULL,"提示！","读取进给速度文件失败！");
      // QMessageBox()
        return Feedspeed;

    }

    while (!file->atEnd())
    {

        str=file->readLine();
        str=str.remove("\n");
        //list.append(str);

     Feedspeed.push_back(str.trimmed().toDouble());
    }

    return  Feedspeed;

}
