#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"pcommserverlib.h"
#include <QDesktopWidget>
#include <QScopedPointer>
#include <QList>
#include <QVariant>
#include "ExcelBase.h"
#include "qcustomplot.h"
#include"mythread.h"
#include"QTime"
#include"PmacAPI.h"
#include "form.h"
#include <QtSerialPort/QSerialPort>         // 提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>     // 提供系统中存在的串口信息
#include"hzaxle.h"
#include "dialogserail.h"
using namespace PCOMMSERVERLib;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    static bool selectPmacSuccess ;
    static bool openPmacSuccess;
    static int pmacNumber;
    static double parameter_shape[10];
    static double A[20];//非球面公式参数
    static double parameter_process[20] ;
    static QVector<double> x, zd;//面型补正数据
//    static double ** NC_Data;//生成代码数据
      static QVector<double>F1;//补偿后的F
      static double x_devia_value, b_devia_value,z_devia_value,y_devia_value;//定义轴的偏移量,单位脉冲
      static double x_devia_ADDvalue, b_devia_ADDvalue, z_devia_ADDvalue,y_devia_ADDvalue;//定义轴的偏移量改变值,单位脉冲
      static bool draw_flag;//画过一次后标志
      static bool set_flag,set_proces_flag;//设置过一次参数后标志
      static bool own_code_flag, compensate_code_flag, other_code_flag;//判断下载了什么代码
      static double process_time;//加工时间
      static bool download_code_flag;//下载代码进控制器标志
     static int hour, min, Sec, h, m, s;
      static double compens_cycle_time;//补偿加工次数
      static bool process_fininsh_flag, process_begin_flag, Z_motor_status, C_motor_status, X_motor_status, B_motor_status;
      static  bool Vc_flag,F_flag;//确定是否是恒转速和恒进给速度
      static bool connect_flag;//连接控制器标志
      static bool Pcode_return_flag;//进入生成代码界面标志
      static bool handle_model_flag   ;//进入手动界面标志
      static bool read_data_flag   ;//读取面型数据标志
      static bool compensate_flag     ;//进行面型补正后的
      static bool process_flag     ;//进入加工模式一次标志
      static bool multi_process_flag     ;//进入多段程序设定界面一次标志
      static bool multi_process_flag2     ;//从自己代码设定进入多段程序设定界面一次标志
      static bool X_ALARM_flag     ;//X轴警报标志
      static bool B_ALARM_flag     ;//B轴警报标志
      static bool Z_ALARM_flag     ;//Z轴警报标志
      static bool C_ALARM_flag     ;//C轴警报标志
      static bool Alarm_clear_flag     ;//异常清除按钮清除标志
  //  static   Form1 frmForm1;
   // private PmacApi Pmac = new PmacApi(pmacNumber);
   // private static SerialPort comm = new SerialPort();//建立串口通讯，模拟量输出板控制抛光轴转动
      static bool buzzer_work;//蜂鸣器响
      static int buzzer_worktime;//蜂鸣器响的次数
      static bool resetC_work;//C轴清楚警报
      static int resetC_worktime;//发生警报清楚电平次数
      static double Lworkpiece_h;//为L型件底面到中心孔高度
      static double other_h;//L型件底面到夹具底面高度
      static double C_motor_scale_factor;//C轴电压转速比例因子
      static double C_motor_offset;//C轴电压转速比例一次变换偏差
       static double U_motor_scale_factor;//抛光轴电压转速比例因子
      static double U_motor_offset;//抛光轴电压转速比例一次变换偏差
      static double zfeed;//多段抛光Z轴上升和下降速度
      static double xBfeed;//多段抛光XB轴速度
     // static double xlimit;//X轴极限位置，左右对称
       static double xlimit_left;//X轴左极限位置
       static double xlimit_right;//X轴左极限位置
       static double ylimit_bakcward;//X轴左极限位置
       static double ylimit_forward;//X轴左极限位置
      static double blimit_left;//B轴左极限位置
      static double blimit_right;//B轴右极限位置
      static double zlimit_up;//Z轴上极限位置
      static double zlimit_down;//Z轴上极限位置
      static double min_z;//数控代码Z的最小值
      static double polish_axi_maxfeed;//抛光轴最大速度
      static double polish_axi_minfeed;//抛光轴最小速度
      static double x_axi_hand_maxfeed;//X轴手动最大速度
      static double y_axi_hand_maxfeed;//y轴手动最大速度
      static double b_axi_hand_maxfeed;//b轴手动最大速度
      static double z_axi_hand_maxfeed;//z轴手动最大速度
      static double C_axi_maxfeed;//C轴最大速度
      static double C_axi_minspeed;//C轴最小速度
      static double C_Button_speed;//C轴最小速度
      static double caculate_time_offset;//计算时间补正系数，单位/min
      static double first_position_feed;//单段抛X B 到初始位进给速度（mm/min）
      static double first_polish_zfeed;//抛光z到初始位速度
      static double x_software_limit_left;//x左软限位
      static double x_software_limit_right;//x右软限位
      static double b_software_limit_left;//b左软限位
      static double b_software_limit_right;//b右软限位
      static double z_software_limit_up;//z上软限位
      static double z_software_limit_down;//z下软限位
      static double z_axi_first_jogdownfeed;//抛光Z轴下降手动速度；
      static double B_axi_Center_Polish_head_distance;//在零位时，B轴回转中心到抛光头触碰到第二个限位的距离；
      static QVector<QVector<double>> Nc_Data;
       static QVector<QVector<double>> Nc_Check;
       static QVector<QString> Nc_x;
        static bool interfere_flag;//干涉检查标志
        static bool produce_ncCode_flag;//生成非补正代码标志
        static bool produce_ncCode_flag2;//生成补正代码标志
        static double Cloth_thickness;//抛光垫的厚度
        static double Cloth_minthickness;//抛光垫压缩最小剩余厚度
        static int last_index;//工件坐标计数
        static double max_x;//数控代码最大X坐标
        static double max_b;//数控代码最大B坐标
        static double max_z;//数控代码最大Z坐标

        static bool tip1;//安全提示标志
        static bool tip2;
        static bool tip3;
        static bool tip4;
        static bool tip5;
        static bool tip6;
        static bool tip7;
        static bool tip8;
        static bool tip9;
        static bool tip10;
        static bool tip11;
        static bool tip12;

        static bool door_open;

      MyThread *Interfer_check;//声明线程指针，用指针时英文名线程时隐式的只能用指针访问
       QTimer *read_position;//声明读取位置计数
       QTimer *check_process_satus;//声明查询加工是否完成
       QTimer *buzzer_working;//蜂鸣响
       static QVector<double> external_rate;//外部倍率文件

      // Interfer_check_thread *Interfer_check;
public:
   PmacDevice *Pmac;
   hzaxle *hz;
   static PmacApi *PMAC;//pmac的api函数
   static QSerialPort *serial;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
  void closeEvent(QCloseEvent *event);//关闭窗口事件，可以询问是否退出
  void Init();//初始化函数
void connect_Pmac();//连接Pmac
void Init_shapeGUi();//初始化形状参数界面
void Init_ProcessGUi();//初始化加工参数界面
void Init_Timer();//初始化计时器
void Init_Pmac();//初始化pamc参数
void Init_hzaxi();//初始化昊志抛光轴
void Hz_start(int type,QString speed);//轴动作
void Hz_stop();//轴停止
//void Produce_Nc(QWidget *parent);//生成代码
bool produce_NC();//生成非补正代码
bool produce_NC2();//生成全局补正代码
void interference_check();//干涉检查
 void produce_NC_interference_check();//生成全局检查干涉的代码
 void Axi_Home();//开软件回零操作
//signals:
 //void count_Signal(int);

private slots:
  void read_pos();//读取位置
  void checkMessage();//干涉检查
  void DisplayMsg(int num);//显示进度条进度和剩余加工时间
  void Check_iffinish();//查询是否加工完成或者终止加工
  void buzzer_sound();//蜂鸣器响函数
  void on_actionHelpFile_triggered();

  void on_actionconnect_triggered();

  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_4_clicked();

  void on_pushButton_6_clicked();

  void on_pushButton_5_clicked();

  void on_pushButton_3_clicked();

  void on_pushButton_8_clicked();

  void on_pushButton_9_clicked();

  void on_pushButton_7_clicked();

  //void on_spinBox_valueChanged(const QString &arg1);

  void on_pushButton_39_clicked();

  void on_pushButton_10_clicked();

  void on_pushButton_11_clicked();

  void on_pushButton_13_clicked();

  void on_pushButton_12_clicked();

  void on_pushButton_14_clicked();

  void on_pushButton_40_clicked();
  void setyAxisRange(QCPRange);

  void on_pushButton_15_clicked();

  //void on_pushButton_18_clicked();

 // void on_pushButton_20_released();

  void on_pushButton_18_released();

  void on_pushButton_18_pressed();

  void on_pushButton_41_clicked();

  void on_pushButton_42_clicked();

  void on_pushButton_43_clicked();

  void on_pushButton_19_pressed();

  void on_pushButton_19_released();

  void on_pushButton_23_pressed();

  void on_pushButton_23_released();

  void on_pushButton_21_clicked();

  void on_pushButton_22_pressed();

  void on_pushButton_22_released();

  void on_pushButton_26_pressed();

  void on_pushButton_26_released();

  void on_pushButton_24_clicked();

  void on_pushButton_25_pressed();

  void on_pushButton_25_released();

  void on_pushButton_29_pressed();

  void on_pushButton_29_released();

  void on_pushButton_27_clicked();

  void on_pushButton_28_pressed();

  void on_pushButton_28_released();

  void on_pushButton_32_pressed();

  void on_pushButton_32_released();

 // void on_pushButton_30_clicked(bool checked);

  void on_pushButton_31_pressed();

  void on_pushButton_31_released();

  void on_pushButton_30_clicked();

  void on_pushButton_20_clicked();

 // void on_pushButton_19_clicked();

  void on_pushButton_33_pressed();

  void on_pushButton_33_released();

  void on_pushButton_34_clicked();

  void on_pushButton_16_clicked();

  void on_pushButton_44_clicked();

  void on_pushButton_44_pressed();

  void on_pushButton_17_clicked();

  void on_pushButton_35_clicked();

  void on_pushButton_36_clicked();

  void on_Lens_tu_toggled(bool checked);

  void on_Lens_tu_clicked();

  void on_Lens_ao_clicked();

  //void on_Lens_plane_clicked();

  void on_pushButton_45_clicked();

  void on_pushButton_46_clicked();

  void on_pushButton_47_clicked();

  void on_pushButton_48_clicked();

  //void on_pushButton_50_clicked();

  void on_pushButton_49_clicked();

  void on_pushButton_37_clicked();

  void on_actiondisconnect_triggered();

  void on_pushButton_17_released();

  void on_pushButton_17_pressed();

  void on_actionversion_triggered();

  void on_actionsystem_valuesetting_triggered();

  void on_actionopen_triggered();

  void on_actionexit_triggered();

  void on_pushButton_38_clicked();

  void on_pushButton_54_clicked();

  void on_pushButton_53_clicked();

  void on_pushButton_52_clicked();

  void on_pushButton_51_clicked();

  void on_actionreset_system_value_triggered();

  void on_pushButton_31_clicked();

  void on_pushButton_18_clicked();

  void on_pushButton_33_clicked();

  void on_pushButton_23_clicked();

  void on_pushButton_30_pressed();

  //void on_action12_triggered();

// void on_comboBox_5_activated(const QString &arg1);

  //void on_pushButton_29_clicked();

  void on_comboBox_8_currentIndexChanged(int index);

  //void on_actionCOM3_triggered();

  void on_actionlianji_triggered();

  void on_actionversion_2_triggered();

  void on_actionreset_system_value_toggled(bool arg1);

private:
    Ui::MainWindow *ui;
    Ui::MainWindow *ui2;
     QDesktopWidget *m_pDeskdop;
     QScopedPointer<ExcelBase> m_xls;
       QList< QList<QVariant> > m_datas;
       Process_time_count *timecount;
       Form *myform;
     DialogSerail *serialForm;



       //QWidget *Form=new QWidget;
};

//MainWindow::parameter_shape[];


#endif // MAINWINDOW_H
