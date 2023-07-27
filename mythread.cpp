#include "mythread.h"
//#include"ui_mainwindow.h"
#include"mainwindow.h"
#include"QDebug"
#include"PmacAPI.h"
#include"produce_gcode.h"
#include"QMessageBox"
/*********************************************************************
 * 函数功能：干涉检查线程
 * 参 数：  无
 * 返回值： 无
 * 备  注： 无
 *********************************************************************/
static Ui::MainWindow *uii = nullptr;
//static MainWindow *mainw;
using namespace ui;
void thread_init(Ui::MainWindow *ui_ptr)
{
uii = ui_ptr;


}

MyThread::MyThread(QObject *parent)
   :QThread() {

    //thread_init(parent);
    timerReceiver = parent;

    myPmac=new PmacApi(0);
    myPmac->Open(0,pbsuccess);
    qDebug()<<"pbsuccess"<<pbsuccess;
double a=myPmac->GetP(10);
qDebug()<<"p10"<<a;
double x_pos;
myPmac->GetPositon(1,x_pos);
qDebug()<<"x:"<<x_pos;
//Produce_Gcode


}

void MyThread::run()//重写线程函数（虚函数run）
{
    //执行操作
//    Q_OBJECT
//    QTimer *timer = new QTimer();
//       timer->setInterval(3000);
//       connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()), Qt::DirectConnection);

//       timer->start();

//       exec();
//       return;

//    double x_pos;
//    while(1)
//    {
//        qDebug()<<"当前线程ID:"<<QThread::currentThreadId();
//     //MainWindow::Pmac->GetPosition(1,double x_pos);
//     MainWindow::PMAC->GetPositon(1,x_pos);
//     myPmac->GetPositon(1,x_pos);
//     qDebug()<<"x:"<<x_pos;
//     sleep(1);


//    }
  //  static MainWindow *mainw;
    // mainw->produce_NC_interference_check();
    // ui->

    //以下注释试试生成NC代码的

     Produce_Gcode *Nc_data= new Produce_Gcode;
QVector<QVector<double>> Nc_Check;//NC代码检查代码
//    double curvature_compensate=1, n=1, R=100, K=0, dist=0.1, t = 0, vc=100, H=10, R_left=-5, SAG=1, yuan_r=1, ao_tu=1, R_right=5, constan_vc=100, constan_F=100, symbol = 1, tool_r=3, Dp=20, D_workpiece=30;
    double limit_right,limit_left,curvature_compensate,n, R, K,dist, t = 0, vc, H, R_left,SAG,yuan_r,ao_tu,R_right,constan_vc,constan_F, symbol = 1,tool_r,Dp,D_workpiece;
    double press_distant;
    double A[20];
    int compare_index;//数控代码校验行
    try {

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

                  n = uii->lineEdit_ProcessCycle->text().toDouble();//加工次数
                   R = uii->lineEdit_R->text().toDouble();  //面型参数R
                   K = uii->lineEdit_K->text().toDouble();//面型参数K
                   vc = uii->lineEdit_constfeed->text().toDouble();//C轴最大转速
                   H = uii->lineEdit_HE->text().toDouble();//模仁高度

                   SAG = uii->lineEdit_HC->text().toDouble();//非球面中心到平面距离
                 //  fixture_h = Convert.ToDouble(yuanr_text.Text.Trim());//夹具高度，从移动调心夹具底面到模仁底面距离
                   yuan_r = uii->lineEdit_yuan_r->text().toDouble();//圆角半径
                    constan_vc = uii->lineEdit_constfeed->text().toDouble();//恒定C转速
                   constan_F = uii->lineEdit_constfeed->text().toDouble();//恒定进给

                   Dp = uii->lineEdit_DP->text().toDouble();//工件加工口径
                   D_workpiece = uii->lineEdit_D->text().toDouble();
                   press_distant=uii->lineEdit_Pressure->text().toDouble();
                //    Dp = D_workpiece;
                       if (uii->lineEdit_ProdessLeft->text()=="")
                           R_left = 0;
                       else
                           R_left = uii->lineEdit_ProdessLeft->text().toDouble();//加工范围半径

                       if (uii->lineEdit_ProcessRight->text()=="")
                           R_right = 0;
                       else
                           R_right = uii->lineEdit_ProcessRight->text().toDouble();//加工口径另一值
                       // textBox18.text
                       //if (R_left >= R_right)
                    //   {
                    //       QMessageBox::information(this,"提示！","加工范围设定有误，左边框值不可大于右边框值，请重新设定加工范围！");

                      //     return;
                    //   }

                       R_left=-D_workpiece/2;
                       R_right=D_workpiece/2;
                    limit_left=qAbs(uii->lineEdit_ProdessLeft->text().toDouble()*10);
                    limit_right=qAbs(uii->lineEdit_ProcessRight->text().toDouble()*10);
                    if(limit_left>limit_right)
                        compare_index=qRound(limit_left);
                    else {
                        compare_index=qRound(limit_right);

                          }
                       if (uii->Lens_ao->isChecked())//凹凸判断
                           ao_tu = -1;
                       else
                           ao_tu = 1;

                       if (uii->comboBox_dataDistance->currentIndex()==0)

                           dist = 0.1;
                       else if(uii->comboBox_dataDistance->currentIndex()==1)
                           dist = 0.05;
                       else
                           dist=0.01;

                       if (uii->comboBox_toolRaidus->currentIndex()==0)
                           tool_r = 1;
                       else if (uii->comboBox_toolRaidus->currentIndex()==1)
                           tool_r = 3;
                       else
                           tool_r = 5;

//                       if (ui->radioButton_0degree->isChecked())//垂直抛
//                       {
//                           tool_r = 7;
//                       }

curvature_compensate = 1;

                       if (uii->Lens_ao->isChecked() || uii->Lens_tu->isChecked())
                       {
                           if (uii->Lens_ao->isChecked())
                           {
                               if (R > 1e-7)
                                   symbol = 1;
                               else
                                   symbol = -1;

                           }
                           if (uii->Lens_tu->isChecked())
                           {
                               if (R > 1e-7)
                                   symbol = -1;
                               else
                                   symbol = 1;
                           }

                         //  if (comboBox13.SelectedIndex == 1)

                         //  else if (comboBox13.SelectedIndex == 2)
                           //    curvature_compensate = 2;
                        //   else
                  }         //    curvature_compensate = 0;


    } catch (QString exception) {
        //QMessageBox::information(this,tr("提示！"),tr(err.1))
     //  QMessageBox::about(this,"Error",exception);
    }

double first_position_feed=MainWindow::first_position_feed;
double C_motor_offset=MainWindow::C_motor_offset;
double C_motor_scale_factor=MainWindow::C_motor_scale_factor;
double Lworkpiece_h=MainWindow::Lworkpiece_h+uii->lineEdit_Toolhigh->text().toDouble();
double other_h=MainWindow::other_h;
bool Vc_flag=MainWindow::Vc_flag;
bool F_flag=MainWindow::F_flag;
double Cloth_thickness=uii->lineEdit_ClothThick->text().toDouble();
int tool_type=uii->comboBox_toolRaidus->currentIndex();
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

//interference_check();//干涉检查
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

  R=uii->lineEdit_ToolD->text().toDouble()/2/0.01;//抛光头半径分组
 double radius=uii->lineEdit_ToolD->text().toDouble()/2;//抛光头半径
 double offset=Cloth_thickness-uii->lineEdit_Pressure->text().toDouble();//泡棉厚度减去压缩量
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

 for(int j=0;j<=COUNT;j++)//RHO矩阵,抛光工具坐标
 {
      temp.clear();
     for(int i=0;i<=COUNT;i++)
     {

         temp.push_back(i*0.01);
     }
     RHO.push_back(temp);

 }

 for(int j=0;j<RHO.size();j++)//THETA矩阵，抛光工具坐标
 {
      temp.clear();
     for(int i=0;i<RHO.at(1).size();i++)
     {

         temp.push_back(0+2*(M_PI)/(RHO.size()-1)*j);
     }
     THETA.push_back(temp);

 }

 for(int j=0;j<RHO.size();j++)//Z矩阵，抛光工具坐标
 {
      temp.clear();
     for(int i=0;i<RHO.at(1).size();i++)
     {
         //radius-qSqrt(
if(tool_type==0)//球头
         temp.push_back(offset+radius-qSqrt(qAbs(qPow(radius,2)-qPow(RHO.at(j).at(i)*qCos(THETA.at(j).at(i)),2)-qPow(RHO.at(j).at(i)*qSin(THETA.at(j).at(i)),2))));
else {
    //平头
    temp.push_back(0+offset);

}
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
     if(tool_type==0)//球头
         temp.push_back(offset+radius+(j+1)*0.1);
     else {
         //平头
         temp.push_back(offset+(j+1)*0.1);

          }
     }
     Z.push_back(temp);

 }





//矩阵旋转平移

for (int k=0;k<workpiece.size();k++)
{
   // X_ROT.clear();
   // Y_ROT.clear();
  //  Z_ROT.clear();
 for(int j=0;j<RHO.size();j++)//旋转后XYZ值
 {
      temp.clear();
     for(int i=0;i<RHO.at(1).size();i++)//旋转后X值
     {

        // temp.push_back(RHO.at(j).at(i)*qCos(THETA.at(j).at(i))*qCos(workpiece.at(k).at(2))+Z.at(j).at(i)*qSin(workpiece.at(k).at(2))+workpiece.at(k).at(0));
         temp.push_back(RHO.at(j).at(i)*qCos(THETA.at(j).at(i))*qCos(workpiece.at(k).at(2)/180*M_PI)+Z.at(j).at(i)*qSin(workpiece.at(k).at(2)/180*M_PI)+workpiece.at(k).at(0)/10);

     }
     X_ROT.push_back(temp);

     temp.clear();
    for(int i=0;i<RHO.at(1).size();i++)//旋转后Z值
    {

        temp.push_back(-RHO.at(j).at(i)*qCos(THETA.at(j).at(i))*qSin(workpiece.at(k).at(2)/180*M_PI)+Z.at(j).at(i)*qCos(workpiece.at(k).at(2)/180*M_PI)+workpiece.at(k).at(1));
    }
    Z_ROT.push_back(temp);

    temp.clear();
   for(int i=0;i<RHO.at(1).size();i++)//旋转后Y值
   {

       temp.push_back(RHO.at(j).at(i)*qSin(THETA.at(j).at(i)));
   }
   Y_ROT.push_back(temp);


 }

int rho,index;
//double test_x,text_y;
//if(k>15)
 //   rho=150;
 for(int j=0;j<RHO.size();j++)//旋转后XYZ值
 {
     for(int i=0;i<RHO.at(1).size();i++)
     {
         rho=QString::number(qRound(sqrt(qPow(X_ROT.at(j).at(i),2)+qPow(Y_ROT.at(j).at(i),2))*10)).toInt();
     //    test_x=X_ROT.at(j).at(i);
      //           text_y=Y_ROT.at(j).at(i);
        // qDebug()<<"rho:"<<qPow(X_ROT.at(j).at(i),2)+qPow(Y_ROT.at(j).at(i),2);

         index=X_D.indexOf(rho);
//if(k==15)
//    k=15;
//         if(index>100)
//             index=100;
//      if(j>201)
//          j=200;

//      if(i>151)
//          i=150;
//text_y=Z_ROT.at(j).at(i);

      if(index==-1)
      {
//          qDebug()<<"index"<<index;
//          qDebug()<<"rho"<<rho;
//          qDebug()<<"rho2"<<sqrt(qPow(X_ROT.at(j).at(i),2)+qPow(Y_ROT.at(j).at(i),2));
//           qDebug()<<"x"<<X_ROT.at(j).at(i);
//           qDebug()<<"y"<<Y_ROT.at(j).at(i);
           index=workpiece.size()-1;
      }
     // qDebug()<<"size"<<workpiece.size();
//text_y=workpiece.at(index).at(1);
         if(Z_ROT.at(j).at(i)-(workpiece.at(index).at(1))<0.01)
         {
             if(index!=workpiece.size()-1)
             {
//                 qDebug()<<"index"<<index;
//                 qDebug()<<"rho"<<rho;
//                 qDebug()<<"rho2"<<sqrt(qPow(X_ROT.at(j).at(i),2)+qPow(Y_ROT.at(j).at(i),2));
//                    qDebug()<<"x"<<X_ROT.at(j).at(i);
//                   qDebug()<<"y"<<Y_ROT.at(j).at(i);
//                 qDebug()<<"Z_ROT"<<Z_ROT.at(j).at(i);
//                 qDebug()<<"workpiece"<<workpiece.at(index).at(1);

                 interfere_flag=true;
                 interfer_number++;

             }
         }

     }

 }

  X_ROT.clear();
 Y_ROT.clear();
  Z_ROT.clear();


}

 //干涉校验



//if(interfere_flag==true)
//QMessageBox::information(this, "提示！", "加工参数干涉，请减小压缩量！");
//else
//    QMessageBox::information(this, "提示！", "检查完成，无加工干涉！");
qDebug()<<"interfere_flag:"<<interfere_flag;
MainWindow::interfere_flag=interfere_flag;//

//quit();


}
void MyThread::onTimeout()
{
double x_pos;
 //  qDebug()<<"当前线程ID:"<<QThread::currentThreadId();
//MainWindow::Pmac->GetPosition(1,double x_pos);
//MainWindow::PMAC->GetPositon(1,x_pos);
//myPmac->GetPositon(1,x_pos);
//qDebug()<<"x:"<<x_pos;
//ui->lineEdit_33->setText(QString::number(x_pos, 'f', 4));
//MainWindow::read_pos();
}


void Interfer_check_thread::run()
{


}

Process_time_count::Process_time_count(QObject * parent,double Processtime):QThread(parent)
{
   ProcessTime=Processtime*60;

}

void Process_time_count::run()
{
    for(count=0;count<=ProcessTime;count++)
    {
        emit count_Signal(count);//触发信号
     //    qDebug()<<count;
       sleep(1);
    }

}
