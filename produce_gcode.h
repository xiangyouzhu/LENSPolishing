#ifndef PROCUDE_GCODE_H
#define PROCUDE_GCODE_H
namespace ui {

class Produce_Gcode
{

public:
   static int row;//行数
    static int colum;//列数
    double** aspheric(double curvature_compensate,double first_positon_feed,double D_workpiece, double Dp, double C_motor_scale_factor, double C_motor_offset, double Lworkpiece_h, double other_h, double SAG, double yuan_r, double ao_tu, double R_P_right, double tool_R, double constan_vc, double contan_F, bool vc_flag, bool F_flag, double dist, double symbol, double n, double vc, double H, double R_P_left, double R, double K, double A[]);
     double **Test2DArray(unsigned r, unsigned c);
     double** aspheric2(double press_distant,double Cloth_thickness,double curvature_compensate,double first_positon_feed,double D_workpiece, double Dp, double C_motor_scale_factor, double C_motor_offset, double Lworkpiece_h, double other_h, double SAG, double yuan_r, double ao_tu, double R_P_right, double tool_R, double constan_vc, double contan_F, bool vc_flag, bool F_flag, double dist, double symbol, double n, double vc, double H, double R_P_left, double R, double K, double A[]);
      bool interference_check();//干涉检查
    Produce_Gcode();


};



}


#endif // PROCUDE_GCODE_H




