#include<PmacApi.h>
#include<pcommserverlib.h>
#include<QString>
#include<QMessageBox>
#include "mainwindow.h"
using namespace PCOMMSERVERLib;
using namespace Ui ;
static PCOMMSERVERLib::PmacDevice *Pmac;
//double  PmacApi::test=0;
//static int  m_nDevice;
//static bool m_bDeviceOpen;
 PmacApi::PmacApi(int M_NDEVICE)
{
   Pmac =new PmacDevice();
   m_nDevice=M_NDEVICE;//
   m_bDeviceOpen=false; 
}

bool PmacApi::Connect() //连接pmac
 {
     Pmac->Open(m_nDevice, m_bDeviceOpen);

     return m_bDeviceOpen;

 }
 ;
 bool PmacApi:: Close()//断开pmac
 {
     Pmac->Close(m_nDevice);
     return m_bDeviceOpen;

 };
 void  PmacApi:: RunProgram(int coordinatesystem,QString name)//执行n号程序
 {
     QString Command="&"+ QString::number(coordinatesystem)+ "B"+name+"R";
     QString response;
     int status;
     Pmac->GetResponseEx(m_nDevice,Command,false,response,status);

 };
 void  PmacApi:: StopProgram(QString name)//停止n号程序
 {
     QString Command= "B"+name+"A";
     QString response;
     int status;
     Pmac->GetResponseEx(m_nDevice,Command,false,response,status);

 };
 void  PmacApi:: StopAxi(int nAxi)//轴急停
 {
     QString Command= "#"+QString::number(nAxi)+"k";
     QString Command2= "#"+QString::number(nAxi)+"j/";
     QString response;
     int status;
   //  Pmac->GetResponseEx(m_nDevice,Command,false,response,status);
    Pmac->GetResponseEx(m_nDevice,Command2,false,response,status);

 };
 void  PmacApi:: AxiCloseLoop(int nAxi)//轴闭环停止
 {
     QString Command= "#"+QString::number(nAxi)+"j/";
     QString response;
     int status;
     Pmac->GetResponseEx(m_nDevice,Command,false,response,status);

 };
 int  PmacApi:: GetM(int id)//查询M值，返回整数
 {
     QString Command= "M"+QString::number(id);
     QString response;
     int status;
     Pmac->GetResponseEx(m_nDevice,Command,false,response,status);
    if(response!="")
    {
    response=response.trimmed();
    return QString(response).toInt();
    }
    else
    {
    return 0;
    }

 };
 int  PmacApi:: GetI(int id)//查询I值
 {
     QString Command= "I"+QString::number(id);
     QString response;
     int status;
     Pmac->GetResponseEx(m_nDevice,Command,false,response,status);
    if(response!="")
    {
    response=response.trimmed();
    return QString(response).toInt();
    }
    else
    {
    return 0;
    }


 };
 double  PmacApi:: GetP(int id)//查询P值
 {
     QString Command= "P"+QString::number(id);
     QString response;
     int status;
     Pmac->GetResponseEx(m_nDevice,Command,false,response,status);
    if(response!="")
    {
    response=response.trimmed();
    return QString(response).toDouble();
    }
    else
    {
    return 0;
    }



 };
 void  PmacApi:: SetM(int id,int value)//设置M值
 {
     QString Command= "M"+QString::number(id)+"="+QString::number(value);
     QString response;
     int status;
     Pmac->GetResponseEx(m_nDevice,Command,false,response,status);



 };
 void  PmacApi:: SetI(int id,double value)//设置MI值
 {
     QString Command= "I"+QString::number(id)+"="+QString::number(value,'f',1);
     QString response;
     int status;
     Pmac->GetResponseEx(m_nDevice,Command,false,response,status);

 };


// void SetI(int id,int value);//设置I值
 /*!
  * \internal
  *
  * \class PmacApi
  *
  * 设置P变量值.
  */
 void   PmacApi:: SetP(int id,double value)
 {
      QString Command="P"+QString::number(id)+"="+QString::number(value,'f',4);
      QString response;
      int status;
      Pmac->GetResponseEx(m_nDevice,Command,false,response,status);
      if(status==0)
      {
       //   QMessageBox::show(NULL,"tip","Set P value failed!");
         // QMessageBox::show();
      }

 };//设置P值

// QString Command="P"+QString::number(id)+"="QString::number(id);
// QString response;
// int status;
// Pmac->GetResponseEx(m_nDevice,Command,false,response,status);




 void  PmacApi:: JogForward(int nAxi)//轴正点动
 {
     QString Command="#"+QString::number(nAxi)+"j+";
     QString response;
     int status;
     Pmac->GetResponseEx(m_nDevice,Command,false,response,status);
     if(status==0)
     {
      //   QMessageBox::show(NULL,"tip","Set P value failed!");
        // QMessageBox::show();
     }

 };
 void  PmacApi:: JogBackward(int nAxi)//轴负点动
 {
     QString Command="#"+QString::number(nAxi)+"j-";
     QString response;
     int status;
     Pmac->GetResponseEx(m_nDevice,Command,false,response,status);
     if(status==0)
     {
      //   QMessageBox::show(NULL,"tip","Set P value failed!");
        // QMessageBox::show();
     }

 };
 void  PmacApi:: JogForwardP(int nAxi,double position_value)//轴正点位
 {
     QString Command="#"+QString::number(nAxi)+"j="+QString::number(qAbs(position_value));
     QString response;
     int status;
     Pmac->GetResponseEx(m_nDevice,Command,false,response,status);
     if(status==0)
     {
      //   QMessageBox::show(NULL,"tip","Set P value failed!");
        // QMessageBox::show();
     }

 };
  void  PmacApi:: JogBackwardP(int nAxi,double position_value)//轴负点位
  {
      QString Command="#"+QString::number(nAxi)+"j=-"+QString::number(qAbs(position_value));
      QString response;
      int status;
      Pmac->GetResponseEx(m_nDevice,Command,false,response,status);
      if(status==0)
      {
       //   QMessageBox::show(NULL,"tip","Set P value failed!");
         // QMessageBox::show();
      }

  };
 void  PmacApi:: SetVelocity(int nAxi,double velocity)//设置轴运动速度
 {
     QString Command="I"+QString::number(nAxi)+"22="+QString::number(qAbs(velocity));
     QString response;
     int status;
     Pmac->GetResponseEx(m_nDevice,Command,false,response,status);
     if(status==0)
     {
      //   QMessageBox::show(NULL,"tip","Set P value failed!");
        // QMessageBox::show();
     }

 };
 bool  PmacApi:: GetPositon(int nAxi,double &position)//查询轴位置
 {
     QString Command1="M"+QString::number(nAxi)+"62";
     QString Command2="M"+QString::number(nAxi)+"69";

     QString response1;
     QString response2;
     int status;
     Pmac->GetResponseEx(m_nDevice,Command1,false,response1,status);
     Pmac->GetResponseEx(m_nDevice,Command2,false,response2,status);

     if(response1!="")
     {
      //   QMessageBox::show(NULL,"tip","Set P value failed!");
        // QMessageBox::show();
         position=response1.trimmed().toDouble()/96/32+response2.trimmed().toDouble()/96/32;
         return  true;
     }
     else {
         position=0;
         return false;
     }

 };
 void  PmacApi:: ResetPmac()//pmac复位
 {
     QString Command="$$$";
     QString response;
     int status;
     Pmac->GetResponseEx(m_nDevice,Command,false,response,status);
     if(status==0)
     {
      //   QMessageBox::show(NULL,"tip","Set P value failed!");
        // QMessageBox::show();
     }

 };
 void PmacApi::SendCommand(QString command)//发送在线指令
 {
    // QString Command="$$$";
     QString response;
     int status;
     Pmac->GetResponseEx(m_nDevice,command,false,response,status);
     if(status==0)
     {
      //   QMessageBox::show(NULL,"tip","Set P value failed!");
        // QMessageBox::show();
     }

 }




