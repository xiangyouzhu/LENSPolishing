#ifndef PMACAPI_H
#define PMACAPI_H
//#include"PmacAPI.h"
#include <pcommserverlib.h>
#include<QString>

class PmacApi: public PCOMMSERVERLib::PmacDevice
{

  //  static praivte:

public:
     int m_nDevice;
     PmacApi(int M_NDEVICE);
     bool Connect();//连接pmac
     bool Close();//断开pmac
     void RunProgram(int coordinatesystem,QString name);//执行n号程序
     void StopProgram(QString name);//停止n号程序
     void StopAxi(int nAxi);//轴急停
     void AxiCloseLoop(int nAxi);//轴闭环停止
      int GetM(int id);//查询M值，返回整数
      int GetI(int id);//查询I值
     double GetP(int id);//查询P值
     void SetM(int id,int value);//设置M值
     void SetI(int id,double value);//设置I值
     void  SetP(int id,double value);//设置P值

     void JogForward(int nAxi);//轴正点动
     void JogBackward(int nAxi);//轴负点动
     void JogForwardP(int nAXI,double position_value);//轴正点位
      void JogBackwardP(int nAXI,double position_value);//轴负点位
     void SetVelocity(int nAxi,double velocity);//设置轴运动速度
     bool GetPositon(int nAxi,double &position);//查询轴位置
     void ResetPmac();//pmac复位
     void SendCommand(QString command);//发送指令
//static double test;
private:
     bool  m_bDeviceOpen;




signals:



};






#endif // PMACAPI_H
