
#include <math.h>
#include <QtCore/qmath.h>
#include <QtMath>
#include "produce_gcode.h"
#include"QMessageBox"
#include"QDebug"
using namespace std;
using namespace ui;

int Produce_Gcode::row;
int Produce_Gcode::colum;
 Produce_Gcode::Produce_Gcode()
{

}

 //最初拷贝过来的代码
double** Produce_Gcode::aspheric(double curvature_compensate,double first_positon_feed,double D_workpiece, double Dp, double C_motor_scale_factor, double C_motor_offset, double Lworkpiece_h, double other_h, double SAG, double yuan_r, double ao_tu, double R_P_right, double tool_R, double constan_vc, double contan_F, bool vc_flag, bool F_flag, double dist, double symbol, double n, double vc, double H, double R_P_left, double R, double K, double A[20])
{
    vc_flag = true;//C轴恒速，变速功能不要
             double h =  - Lworkpiece_h + other_h;//B轴旋转中心到模具平面高度
             H = H + ao_tu * SAG;//求模仁底面到面型中心的距离
           //  double t = 0;
              dist = 0.1;//间隔为0.1
             double Vu = 19;//Vu=Wu.*Ru.*sin(U);抛光轴线速度 Vu大约等于20mm/s
             double C = 1 / R;
             double Vs = Vu + 5;//U轴和C轴的线速度模
             //加工口径左边缘的X坐标


             R_P_left = floor(R_P_left * 10) / 10;//取小数后一位
             Dp = floor(Dp * 10) / 10;
             D_workpiece = floor(D_workpiece * 10) / 10;

            // if (R_P_left * 10 % 2 == 1)
           //      R_P_left = R_P_left + 0.1;

             if (QString::number(Dp * 10).toInt() % 2 == 1)
                 Dp = Dp + 0.1;

             if (QString::number(D_workpiece * 10).toInt() % 2 == 1)
                 D_workpiece = D_workpiece - 0.1;
            double X_p = -Dp / 2;
             int c = QString::number((R_P_right-R_P_left) / dist).toInt();//输出代码行数-1
           // qDebug()<<"c"<<c;
           //  qDebug()<<(R_P_right-R_P_left) / dist;
            // qDebug()<<(int)122;
             int a = QString::number(D_workpiece / dist).toInt();//代码数组行数-1
             int d = QString::number((R_P_left / dist)).toInt();
             int e = QString::number((R_P_right / dist)).toInt();
             int f = QString::number(Dp / dist).toInt();
             bool normal_flag = true;
             double X[a+1];
              double Y[a+1];
             double Z[a + 1];  //原点变为转动点后的Z值
             double Z1[a + 1];//函数曲线Z值
             double Z2[a + 1];//曲线的一阶导数
             double ZZ[a + 1];//Z轴移动坐标
             double B[a + 1];//B转动角度
             double Vc[a + 1];//C线速度
             double Nc[a + 1];//C轴转速
             double F[a + 1]; //X轴进给速度
             double F1[a + 1]; //dist距离走一圈的进给速度
             double T[a + 1];  //两点间时间
             double X2[a + 1];//x移动坐标
             double r0[a + 1];//点到转动中心的夹角
             double flat_v_1p[] ={ 27.804, 24.2575, 16.5767, 11.2156, 9.2657, 8.3414, 7.4582,
                                   6.7514, 6.3777, 5.9989, 5.6724, 5.4287, 5.2395, 5.0569, 4.8999,
                                   4.7708, 4.6671, 4.5711, 4.482, 4.3991, 4.3219, 4.2464, 4.1822,
                                   4.1219, 4.0649, 4.011, 3.9599, 3.9113, 3.8651, 3.821, 3.7789, 3.7386,
                                   3.7, 3.6629, 3.6273, 3.5931, 3.5602, 3.5284, 3.4978, 3.4682, 3.4396,
                                   3.4119, 3.3852, 3.3592, 3.3341, 3.3096, 3.2859, 3.2629, 3.2405, 3.2188,
                                   3.1976, 3.1769, 3.1568, 3.1372, 3.1181, 3.0994, 3.0812, 3.0634, 3.0461,
                                   3.0291, 3.0125, 2.9963, 2.9804, 2.9648, 2.9496, 2.9347, 2.9201, 2.9057, 2.8917, 2.8779, 2.8644, 2.8512, 2.8381, 2.8254, 2.8128, 2.8005, 2.7884, 2.7765, 2.7648, 2.7533, 2.742, 2.7309, 2.72, 2.7092, 2.6986, 2.6882, 2.6779, 2.6678,
                                   2.6579, 2.6481, 2.6384, 2.6289, 2.6195, 2.6103, 2.6012, 2.5922, 2.5833,
                                   2.5746, 2.566, 2.5575, 2.5491, 2.5408, 2.5326, 2.5246, 2.5166, 2.5087,
                                   2.501, 2.4933, 2.4857, 2.4782, 2.4709, 2.4635, 2.4563, 2.4492, 2.4422,
                                   2.4352, 2.4283, 2.4215, 2.4148, 2.4081, 2.4015, 2.395, 2.3886, 2.3822,
                                   2.3759, 2.3697, 2.3635, 2.3574, 2.3514, 2.3454, 2.3395, 2.3336, 2.3278,
                                   2.3221, 2.3164, 2.3108, 2.3052, 2.2997, 2.2943, 2.2888, 2.2835, 2.2782, 2.2729, 2.2677, 2.2625, 2.2574, 2.2524, 2.2473, 2.2424, 2.2374, 2.2325, 2.2277, 2.2229, 2.2181, 2.2134, 2.2087, 2.2041, 2.1995, 2.1949, 2.1904, 2.1859, 2.1815, 2.1771, 2.1727, 2.1683, 2.164, 2.1598, 2.1555, 2.1513, 2.1472, 2.143, 2.1389, 2.1348, 2.1308, 2.1268, 2.1228, 2.1188, 2.1149, 2.111, 2.1072, 2.1033, 2.0995, 2.0957, 2.092, 2.0883, 2.0846, 2.0809, 2.0773, 2.0736, 2.07, 2.0665, 2.0629, 2.0594, 2.0559, 2.0524, 2.049, 2.0456, 2.0422, 2.0388, 2.0354, 2.0321, 2.0288, 2.0255, 2.0222, 2.019, 2.0158, 2.0126, 2.0094, 2.0062, 2.0031, 1.9999, 1.9968, 1.9937, 1.9907, 1.9876, 1.9846, 1.9816, 1.9786, 1.9756, 1.9727, 1.9697, 1.9668, 1.9639, 1.961, 1.9582, 1.9553, 1.9525, 1.9497, 1.9469, 1.9441, 1.9413, 1.9386, 1.9358, 1.9331, 1.9304, 1.9277, 1.925, 1.9224, 1.9197, 1.9171, 1.9145, 1.9119, 1.9093, 1.9067, 1.9042, 1.9016, 1.8991, 1.8966, 1.8941, 1.8916, 1.8891, 1.8866, 1.8842, 1.8817, 1.8793, 1.8769, 1.8745, 1.8721, 1.8697, 1.8674, 1.865, 1.8627, 1.8604, 1.858, 1.8557, 1.8534, 1.8512, 1.8489, 1.8466, 1.8444, 1.8422, 1.8399, 1.8377, 1.8355, 1.8333, 1.8311, 1.829, 1.8268, 1.8246, 1.8225, 1.8204, 1.8183, 1.8161, 1.814, 1.812, 1.8099, 1.8078, 1.8057, 1.8037, 1.8016, 1.7996, 1.7976, 1.7956, 1.7936, 1.7916, 1.7896, 1.7876, 1.7856, 1.7837, 1.7817, 1.7798, 1.7778, 1.7759, 1.774, 1.7721, 1.7702, 1.7683, 1.7664, 1.7645, 1.7626, 1.7608 };
             double flat_v_3p[] ={ 40.5259, 40.5141, 32.9916, 23.4416, 18.0608, 14.41, 12.4473, 11.0399, 9.7753, 8.9723, 8.2413, 7.68, 7.3041, 6.9754, 6.6848, 6.4257, 6.1929, 5.9818, 5.7891, 5.6112, 5.4335, 5.2944, 5.1922, 5.0945, 5.001, 4.9113, 4.8249, 4.7487, 4.6754, 4.6049, 4.5371, 4.4723, 4.4103, 4.3511, 4.2949, 4.2415, 4.1911, 4.1434, 4.0986, 4.0564, 4.0168, 3.9811, 3.9466, 3.9132, 3.8808, 3.8494, 3.8189, 3.7893, 3.7606, 3.7327, 3.7055, 3.6791, 3.6534, 3.6283, 3.6038, 3.58, 3.5568, 3.5341, 3.5119, 3.4903, 3.4692, 3.4485, 3.4283, 3.4085, 3.3892, 3.3702, 3.3517, 3.3335, 3.3157, 3.2982, 3.2811, 3.2644, 3.2479, 3.2317, 3.2159, 3.2003, 3.185, 3.17, 3.1553, 3.1408, 3.1265, 3.1125, 3.0987, 3.0852, 3.0718, 3.0587, 3.0458, 3.0331, 3.0206, 3.0083, 2.9962, 2.9842, 2.9725, 2.9609, 2.9494, 2.9382, 2.9271, 2.9161, 2.9053, 2.8947, 2.8842, 2.8739, 2.8636, 2.8536, 2.8436, 2.8338, 2.8241, 2.8145, 2.8051, 2.7957, 2.7865, 2.7774, 2.7684, 2.7596, 2.7508, 2.7421, 2.7335, 2.7251, 2.7167, 2.7084, 2.7002, 2.6922, 2.6842, 2.6762, 2.6684, 2.6607, 2.653, 2.6455, 2.638, 2.6306, 2.6232, 2.616, 2.6088, 2.6017, 2.5946, 2.5877, 2.5808, 2.574, 2.5672, 2.5605, 2.5539, 2.5473, 2.5408, 2.5344, 2.528, 2.5217, 2.5154, 2.5092, 2.5031, 2.497, 2.491, 2.485, 2.4791, 2.4732, 2.4674, 2.4616, 2.4559, 2.4502, 2.4446, 2.4391, 2.4335, 2.4281, 2.4226, 2.4172, 2.4119, 2.4066, 2.4014, 2.3962, 2.391, 2.3859, 2.3808, 2.3757, 2.3707, 2.3658, 2.3608, 2.356, 2.3511, 2.3463, 2.3415, 2.3368, 2.3321, 2.3274, 2.3228, 2.3182, 2.3136, 2.3091, 2.3046, 2.3001, 2.2957, 2.2913, 2.287, 2.2826, 2.2783, 2.274, 2.2698, 2.2656, 2.2614, 2.2572, 2.2531, 2.249, 2.2449, 2.2409, 2.2369, 2.2329, 2.2289, 2.225, 2.2211, 2.2172, 2.2133, 2.2095, 2.2057, 2.2019, 2.1981, 2.1944, 2.1907, 2.187, 2.1833, 2.1797, 2.1761, 2.1723, 2.168, 2.163, 2.1585, 2.155, 2.1515, 2.148, 2.1446, 2.1412, 2.1378, 2.1344, 2.131, 2.1277, 2.1244, 2.121, 2.1178, 2.1145, 2.1112, 2.108, 2.1048, 2.1016, 2.0984, 2.0953, 2.0921, 2.089, 2.0859, 2.0828, 2.0798, 2.0767, 2.0737, 2.0707, 2.0677, 2.0647, 2.0617, 2.0587, 2.0558, 2.0529, 2.05, 2.0471, 2.0442, 2.0414, 2.0385, 2.0357, 2.0329, 2.0301, 2.0273, 2.0245, 2.0217, 2.019, 2.0163, 2.0136, 2.0108, 2.0082, 2.0055, 2.0028, 2.0002, 1.9975, 1.9949, 1.9923, 1.9897, 1.9871, 1.9845, 1.982, 1.9794, 1.9769, 1.9744, 1.9719, 1.9694, 1.9669, 1.9644, 1.962, 1.9595, 1.9571, 1.9546, 1.9522, 1.9498, 1.9474, 1.945, 1.9427, 1.9403, 1.9379, 1.9356, 1.9333, 1.9309, 1.9286, 1.9263, 1.9241, 1.9218, 1.9195, 1.9172, 1.915, 1.9128 };
             double flat_v_5p[] ={ 45.201, 44.14, 39.91,31.5091, 25.0356, 20.3111, 16.5255, 14.4076, 12.827, 11.6089, 10.5568, 9.6852, 9.0155, 8.4652, 8.005, 7.6123, 7.2689, 6.9609, 6.678, 6.4284, 6.2069, 6.0652, 5.9219, 5.7785, 5.6365, 5.4985, 5.3666, 5.2474, 5.1562, 5.0698, 4.9876, 4.917, 4.8496, 4.7852, 4.7235, 4.6643, 4.6076, 4.553, 4.5005, 4.45, 4.4013, 4.3543, 4.3089, 4.2651, 4.2227, 4.1816, 4.1419, 4.1033, 4.0659, 4.0297, 3.9944, 3.9602, 3.9269, 3.8945, 3.863, 3.8323, 3.8024, 3.7733, 3.7448, 3.7171, 3.6901, 3.6636, 3.6378, 3.6126, 3.588, 3.5639, 3.5403, 3.5172, 3.4947, 3.4726, 3.4509, 3.4297, 3.4089, 3.3885, 3.3685, 3.3489, 3.3297, 3.3108, 3.2923, 3.2741, 3.2563, 3.2388, 3.2215, 3.2046, 3.188, 3.1716, 3.1555, 3.1397, 3.1241, 3.1088, 3.0938, 3.0789, 3.0643, 3.05, 3.0358, 3.0219, 3.0082, 2.9947, 2.9813, 2.9682, 2.9553, 2.9425, 2.9299, 2.9175, 2.9053, 2.8932, 2.8813, 2.8696, 2.858, 2.8466, 2.8353, 2.8242, 2.8132, 2.8024, 2.7916, 2.7811, 2.7706, 2.7603, 2.7501, 2.74, 2.7301, 2.7203, 2.7105, 2.7009, 2.6914, 2.6821, 2.6728, 2.6636, 2.6546, 2.6456, 2.6367, 2.628, 2.6193, 2.6107, 2.6022, 2.5938, 2.5855, 2.5773, 2.5692, 2.5611, 2.5531, 2.5453, 2.5374, 2.5297, 2.5221, 2.5145, 2.507, 2.4996, 2.4922, 2.4849, 2.4777, 2.4706, 2.4635, 2.4565, 2.4495, 2.4426, 2.4358, 2.4291, 2.4224, 2.4157, 2.4092, 2.4026, 2.3962, 2.3898, 2.3834, 2.3771, 2.3709, 2.3647, 2.3586, 2.3525, 2.3465, 2.3405, 2.3346, 2.3287, 2.3229, 2.3171, 2.3114, 2.3057, 2.3001, 2.2945, 2.2889, 2.2834, 2.2779, 2.2725, 2.2671, 2.2618, 2.2565, 2.2513, 2.2461, 2.2409, 2.2357, 2.2306, 2.2256, 2.2206, 2.2156, 2.2106, 2.2057, 2.2009, 2.196, 2.1912, 2.1864, 2.1817, 2.177, 2.1723, 2.1677, 2.1631, 2.1585, 2.154, 2.1495, 2.145, 2.1406, 2.1361, 2.1318, 2.1274, 2.1231, 2.1188, 2.1145, 2.1103, 2.1061, 2.1019, 2.0977, 2.0925, 2.0875, 2.0834, 2.0794, 2.0753, 2.0713, 2.0674, 2.0634, 2.0595, 2.0556, 2.0517, 2.0479, 2.044, 2.0402, 2.0365, 2.0327, 2.029, 2.0252, 2.0216, 2.0179, 2.0142, 2.0106, 2.007, 2.0034, 1.9999, 1.9963, 1.9928, 1.9893, 1.9858, 1.9824, 1.9789, 1.9755, 1.9721, 1.9687, 1.9654, 1.962, 1.9587, 1.9554, 1.9521, 1.9488, 1.9456, 1.9423, 1.9391, 1.9359, 1.9328, 1.9296, 1.9264, 1.9233, 1.9202, 1.9171, 1.914, 1.911, 1.9079, 1.9049, 1.9019, 1.8989, 1.8959, 1.8929, 1.89, 1.887, 1.8841, 1.8812, 1.8783, 1.8754, 1.8725, 1.8697, 1.8669, 1.864, 1.8612, 1.8584, 1.8556, 1.8529, 1.8501, 1.8474, 1.8447, 1.8419, 1.8392, 1.8366, 1.8339, 1.8312, 1.8286, 1.8259, 1.8233, 1.8207, 1.8181, 1.8155, 1.8129, 1.8104, 1.8078, 1.8053 };
             double flat_v_vertical[] ={ 29.474, 28.685, 27.348, 25.973, 17.534, 12.548, 11.556, 10.321, 8.903, 8.097, 7.608, 6.85, 6.639, 6.087, 5.697, 5.493, 5.426, 5.249, 5.031, 4.889, 4.774, 4.742, 4.563, 4.622, 4.32, 4.326, 4.269, 4.196, 4.27, 4.117, 4.073, 4.027, 3.912, 3.875, 3.945, 3.868, 3.828, 3.721, 3.806, 3.77, 3.741, 3.621, 3.754, 3.592, 3.563, 3.629, 3.495, 3.533, 3.535, 3.557, 3.358, 3.403, 3.375, 3.466, 3.357, 3.388, 3.319, 3.256, 3.277, 3.136, 3.174, 3.136, 3.151, 3.13, 3.103, 3.096, 3.116, 3.031, 3.022, 2.958, 3.014, 3.017, 3.066, 3.076, 3.067, 3.057, 3.047, 3.037, 3.027, 3.017, 3.007, 2.997, 2.987, 2.977, 2.967, 2.957, 2.947, 2.937, 2.927, 2.917, 2.907, 2.897, 2.887, 2.877, 2.867, 2.857, 2.847, 2.837, 2.827, 2.817, 2.807, 2.797, 2.787, 2.777, 2.767, 2.757, 2.747, 2.737, 2.727, 2.717, 2.707, 2.697, 2.687, 2.677, 2.667, 2.657, 2.647, 2.637, 2.627, 2.617, 2.607, 2.597, 2.587, 2.577, 2.567, 2.557, 2.5453, 2.5374, 2.5297, 2.5221, 2.5145, 2.507, 2.4996, 2.4922, 2.4849, 2.4777, 2.4706, 2.4635, 2.4565, 2.4495, 2.4426, 2.4358, 2.4291, 2.4224, 2.4157, 2.4092, 2.4026, 2.3962, 2.3898, 2.3834, 2.3771, 2.3709, 2.3647, 2.3586, 2.3525, 2.3465, 2.3405, 2.3346, 2.3287, 2.3229, 2.3171, 2.3114, 2.3057, 2.3001, 2.2945, 2.2889, 2.2834, 2.2779, 2.2725, 2.2671, 2.2618, 2.2565, 2.2513, 2.2461, 2.2409, 2.2357, 2.2306, 2.2256, 2.2206, 2.2156, 2.2106, 2.2057, 2.2009, 2.196, 2.1912, 2.1864, 2.1817, 2.177, 2.1723, 2.1677, 2.1631, 2.1585, 2.154, 2.1495, 2.145, 2.1406, 2.1361, 2.1318, 2.1274, 2.1231, 2.1188, 2.1145, 2.1103, 2.1061, 2.1019, 2.0977, 2.0925, 2.0875, 2.0834, 2.0794, 2.0753, 2.0713, 2.0674, 2.0634, 2.0595, 2.0556, 2.0517, 2.0479, 2.044, 2.0402, 2.0365, 2.0327, 2.029, 2.0252, 2.0216, 2.0179, 2.0142, 2.0106, 2.007, 2.0034, 1.9999, 1.9963, 1.9928, 1.9893, 1.9858, 1.9824, 1.9789, 1.9755, 1.9721, 1.9687, 1.9654, 1.962, 1.9587, 1.9554, 1.9521, 1.9488, 1.9456, 1.9423, 1.9391, 1.9359, 1.9328, 1.9296, 1.9264, 1.9233, 1.9202, 1.9171, 1.914, 1.911, 1.9079, 1.9049, 1.9019, 1.8989, 1.8959, 1.8929, 1.89, 1.887, 1.8841, 1.8812, 1.8783, 1.8754, 1.8725, 1.8697, 1.8669, 1.864, 1.8612, 1.8584, 1.8556, 1.8529, 1.8501, 1.8474, 1.8447, 1.8419, 1.8392, 1.8366, 1.8339, 1.8312, 1.8286, 1.8259, 1.8233, 1.8207, 1.8181, 1.8155, 1.8129, 1.8104, 1.8078, 1.8053, 1.8027, 1.8002, 1.7976, 1.7951, 1.7925, 1.79, 1.7874, 1.7849, 1.7823, 1.7798, 1.7772, 1.7747, 1.7721, 1.7696, 1.767 };
             double Z11 = symbol * (qPow(X[f / 2 + a / 2], 2) * C / (1 + qSqrt(1 - (K + 1) * qPow(X[f / 2 + a / 2], 2) * qPow(C, 2))) + A[0] * qAbs(X[f / 2 + a / 2]) + A[1] * qPow((X[f / 2 + a / 2]), 2) + A[2] * qPow(qAbs(X[f / 2 + a / 2]), 3) + A[3] * qPow((X[f / 2 + a / 2]), 4) + A[4] * qPow(qAbs(X[f / 2 + a / 2]), 5) + A[5] * qPow((X[f / 2 + a / 2]), 6) + A[6] * qPow(qAbs(X[f / 2 + a / 2]), 7) + A[7] * qPow((X[f / 2 + a / 2]), 8) + A[8] * qPow(qAbs(X[f / 2 + a / 2]), 9) + A[9] * qPow((X[f / 2 + a / 2]), 10) + A[10] * qPow(qAbs(X[f / 2 + a / 2]), 11) + A[11] * qPow((X[f / 2 + a / 2]), 12) + A[12] * qPow(qAbs(X[f / 2 + a / 2]), 13) + A[13] * qPow((X[f / 2 + a / 2]), 14) + A[14] * qPow(qAbs(X[f / 2 + a / 2]), 15) + A[15] * qPow((X[f / 2 + a / 2]), 16) + A[16] * qPow(qAbs(X[f / 2 + a / 2]), 17) + A[17] * qPow((X[f / 2 + a / 2]), 18) + A[18] * qPow(qAbs(X[f / 2 + a / 2]), 19) + A[19] * qPow((X[f / 2 + a / 2]), 20));


             Produce_Gcode::row=c+1;//行数
              Produce_Gcode::colum=8;//列数=c+1;//行数
              //Produce_Gcode::colum=7;//列数
//QDebug<<Qstring(Produce_Gcode::row);
             for (int i = 0; i < a + 1; i++)//x坐标
                       {
                          // ArrayList_X.Add(-D/2+i*0.001);
                           X[i] = -D_workpiece / 2 + i * dist;
                           Y[i]=0;
                       }

             if (Z11 > 0&&ao_tu>0)
                  {
                      H = H -2*ao_tu * SAG;
                  }
                  if (Z11 < 0 && ao_tu < 0)
                  {
                      H = H - 2 * ao_tu * SAG;
                  }

                  //加工口径左边缘B角度
                        double tan_B_p;
                         if(X_p>=0)
                         tan_B_p = symbol * ((2 * C * X_p * (1 + qSqrt(1 - (K + 1) * qPow(X_p, 2) * qPow(C, 2))) + qPow(X_p, 3) / qSqrt(1 - (K + 1) * qPow(X_p, 2) * qPow(C, 2)) * (K + 1) * qPow(C, 3)) / qPow((1 + qSqrt(1 - (K + 1) * qPow(X_p, 2) * qPow(C, 2))), 2) + A[0] + A[1] * 2 * X_p + A[2] * 3 * qPow(X_p, 2) + A[3] * 4 * qPow(X_p, 3) + A[4] * 5 * qPow(X_p, 4) + A[5] * 6 * qPow(X_p, 5) + A[6] * 7 * qPow(X_p, 6) + A[7] * 8 * qPow(X_p, 7) + A[8] * 9 * qPow(X_p, 8) + A[9] * 10 * qPow(X_p, 9) + A[10] * 11 * qPow(X_p, 10) + A[11] * 12 * qPow(X_p, 11) + A[12] * 13 * qPow(X_p, 12) + A[13] * 14 * qPow(X_p, 13) + A[14] * 15 * qPow(X_p, 14) + A[15] * 16 * qPow(X_p, 15) + A[16] * 17 * qPow(X_p, 16) + A[17] * 18 * qPow(X_p, 17) + A[18] * 19 * qPow(X_p, 18) + A[19] * 20 * qPow(X_p, 19));//正切值
                         else
                             tan_B_p = symbol * ((2 * C * X_p * (1 + qSqrt(1 - (K + 1) * qPow(X_p, 2) * qPow(C, 2))) + qPow(X_p, 3) / qSqrt(1 - (K + 1) * qPow(X_p, 2) * qPow(C, 2)) * (K + 1) * qPow(C, 3)) / qPow((1 + qSqrt(1 - (K + 1) * qPow(X_p, 2) * qPow(C, 2))), 2) - A[0] + A[1] * 2 * X_p - A[2] * 3 * qPow(X_p, 2) + A[3] * 4 * qPow(X_p, 3) - A[4] * 5 * qPow(X_p, 4) + A[5] * 6 * qPow(X_p, 5) - A[6] * 7 * qPow(X_p, 6) + A[7] * 8 * qPow(X_p, 7) - A[8] * 9 * qPow(X_p, 8) + A[9] * 10 * qPow(X_p, 9) - A[10] * 11 * qPow(X_p, 10) + A[11] * 12 * qPow(X_p, 11) - A[12] * 13 * qPow(X_p, 12) + A[13] * 14 * qPow(X_p, 13) - A[14] * 15 * qPow(X_p, 14) + A[15] * 16 * qPow(X_p, 15) - A[16] * 17 * qPow(X_p, 16) + A[17] * 18 * qPow(X_p, 17) - A[18] * 19 * qPow(X_p, 18) + A[19] * 20 * qPow(X_p, 19));//正切值


                         double B_p = qAtan(tan_B_p) * 180 / M_PI;  //B角度

                        //加工口径左边缘Z坐标
                        double Z_p = symbol * (qPow(X_p, 2) * C / (1 + qSqrt(1 - (K + 1) * qPow(X_p, 2) * qPow(C, 2))) + A[0] * qAbs(X_p) + A[1] * qPow((X_p), 2) + A[2] * qPow(qAbs(X_p), 3) + A[3] * qPow((X_p), 4) + A[4] * qPow(qAbs(X_p), 5) + A[5] * qPow((X_p), 6) + A[6] * qPow(qAbs(X_p), 7) + A[7] * qPow((X_p), 8) + A[8] * qPow(qAbs(X_p), 9) + A[9] * qPow((X_p), 10) + A[10] * qPow(qAbs(X_p), 11) + A[11] * qPow((X_p), 12) + A[12] * qPow(qAbs(X_p), 13) + A[13] * qPow((X_p), 14) + A[14] * qPow(qAbs(X_p), 15) + A[15] * qPow((X_p), 16) + A[16] * qPow(qAbs(X_p), 17) + A[17] * qPow((X_p), 18) + A[18] * qPow(qAbs(X_p), 19) + A[19] * qPow((X_p), 20));


                        //左圆角圆心X坐标
                        double X_circleCenter = -qAbs(yuan_r * qSin(B_p/180*M_PI)) + X_p;
                       // double tempP = qAsin((X_p - X_circleCenter) / yuan_r) * 180 / M_PI;


                         //左圆角圆心Z坐标
                        double Z_circleCenter = B_p/qAbs(B_p)*yuan_r * qCos(B_p) + Z_p;

                       //左圆角圆心左边取一位小数位


                        double R_circleCenter=floor((qAbs(X_circleCenter)*10))/10;


                        for (int i = 0; i < a + 1; i++)//B角度，
                                 {


                                      //ArrayList_X.Add(-D / 2 + i * 0.001);
                                      //double[] values = ArrayList_X.Cast<double>().ToArray();
                                      //double[] d = Convert.ToDouble(X[i]);

                                      if (i < (D_workpiece / 2 - R_circleCenter)/dist-1)//平面左边部分
                                      {
                                          Z1[i] = -B_p / qAbs(B_p) * (yuan_r - yuan_r * qCos(B_p / 180 * M_PI)) + Z_p;
                                          B[i] = 0;
                                          Z[i] = H + Z1[i] + h;//原点变为转动点后的Z值
                                      }
                                      if (i >= ((D_workpiece / 2 - R_circleCenter) / dist)-1 && i < (D_workpiece / 2 - Dp/2) / dist)//左边圆角部分
                                      {
                                         // Z1[i] = Z[0] + B_p / qAbs(B_p) * (yuan_r - qSqrt(qPow(yuan_r, 2) - qPow(qAbs(X_circleCenter) - (a / 2 - i) * dist, 2)));
                                          Z1[i] = -B_p / qAbs(B_p) * (yuan_r - yuan_r * qCos(B_p / 180 * M_PI)) + Z_p + B_p / qAbs(B_p) * (yuan_r - qSqrt(qPow(yuan_r, 2) - qPow(qAbs(X_circleCenter) - (a / 2 - i) * dist, 2)));
                                          B[i] = B_p / qAbs(B_p) * qAsin((qAbs(X_circleCenter) - (a / 2 - i) * dist) / yuan_r) * 180 / M_PI;
                                          if (B[i] * B_p < 0)
                                              B[i] = 0;
                                          Z[i] = H + Z1[i] + h;//原点变为转动点后的Z值
                                      }
                                      if (i >=QString::number((D_workpiece / 2 - Dp / 2) / dist).toInt() && i<= QString::number((D_workpiece / 2 + Dp / 2)/dist).toInt())
                                     {

                                         Z1[i] = symbol * (qPow(X[i], 2) * C / (1 + qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2))) + A[0] * qAbs(X[i]) + A[1] * qPow((X[i]), 2) + A[2] * qPow(qAbs(X[i]), 3) + A[3] * qPow((X[i]), 4) + A[4] * qPow(qAbs(X[i]), 5) + A[5] * qPow((X[i]), 6) + A[6] * qPow(qAbs(X[i]), 7) + A[7] * qPow((X[i]), 8) + A[8] * qPow(qAbs(X[i]), 9) + A[9] * qPow((X[i]), 10) + A[10] * qPow(qAbs(X[i]), 11) + A[11] * qPow((X[i]), 12) + A[12] * qPow(qAbs(X[i]), 13) + A[13] * qPow((X[i]), 14) + A[14] * qPow(qAbs(X[i]), 15) + A[15] * qPow((X[i]), 16) + A[16] * qPow(qAbs(X[i]), 17) + A[17] * qPow((X[i]), 18) + A[18] * qPow(qAbs(X[i]), 19) + A[19] * qPow((X[i]), 20));
                                       //  Z1[i] = symbol * (qPow(X[i], 2) * C / (1 + qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2))) - A[0] * qAbs(X[i]) + A[1] * qPow((X[i]), 2) - A[2] * qPow(qAbs(X[i]), 3) + A[3] * qPow((X[i]), 4) - A[4] * qPow(qAbs(X[i]), 5) + A[5] * qPow((X[i]), 6) - A[6] * qPow(qAbs(X[i]), 7) + A[7] * qPow((X[i]), 8) - A[8] * qPow(qAbs(X[i]), 9) + A[9] * qPow((X[i]), 10) + A[10] * qPow(qAbs(X[i]), 11) + A[11] * qPow((X[i]), 12) + A[12] * qPow(qAbs(X[i]), 13) + A[13] * qPow((X[i]), 14) + A[14] * qPow(qAbs(X[i]), 15) + A[15] * qPow((X[i]), 16) + A[16] * qPow(qAbs(X[i]), 17) + A[17] * qPow((X[i]), 18) + A[18] * qPow(qAbs(X[i]), 19) + A[19] * qPow((X[i]), 20));

                                         if (isnan(Z1[i]))
                                         {
                                             Z1[i] = Z1[i - 2];
                                             //if()
                                       //      MessageBox.Show("异常Z1N");
                                             normal_flag = false;
                                         }

                                         if (isinf(Z1[i]))
                                         {
                                             Z1[i] = Z1[i - 1] + Z1[i - 1] - Z1[i - 2];
                                             //if()
                                          //   MessageBox.Show("异常Z1I");
                                             normal_flag = false;
                                         }

                                         Z[i] = H + Z1[i] + h;// -Z1[a - 1];

                                      //   Z2[i] = symbol * ((2 * C * X[i] * (1 + qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2))) + qPow(X[i], 3) / qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2)) * (K + 1) * qPow(C, 3)) / qPow((1 + qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2))), 2) + A[0] + A[1] * 2 * X[i] + A[2] * 3 * qPow(X[i], 2) + A[3] * 4 * qPow(X[i], 3) + A[4] * 5 * qPow(X[i], 4) + A[5] * 6 * qPow(X[i], 5) + A[6] * 7 * qPow(X[i], 6) + A[7] * 8 * qPow(X[i], 7) + A[8] * 9 * qPow(X[i], 8) + A[9] * 10 * qPow(X[i], 9) + A[10] * 11 * qPow(X[i], 10) + A[11] * 12 * qPow(X[i], 11) + A[12] * 13 * qPow(X[i], 12) + A[13] * 14 * qPow(X[i], 13) + A[14] * 15 * qPow(X[i], 14) + A[15] * 16 * qPow(X[i], 15) + A[16] * 17 * qPow(X[i], 16) + A[17] * 18 * qPow(X[i], 17) + A[18] * 19 * qPow(X[i], 18) + A[19] * 20 * qPow(X[i], 19));
                                        if(X[i]<=0)
                                         Z2[i] = symbol * ((2 * C * X[i] * (1 + qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2))) + qPow(X[i], 3) / qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2)) * (K + 1) * qPow(C, 3)) / qPow((1 + qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2))), 2) - A[0] + A[1] * 2 * X[i] - A[2] * 3 * qPow(X[i], 2) + A[3] * 4 * qPow(X[i], 3) - A[4] * 5 * qPow(X[i], 4) + A[5] * 6 * qPow(X[i], 5) - A[6] * 7 * qPow(X[i], 6) + A[7] * 8 * qPow(X[i], 7) - A[8] * 9 * qPow(X[i], 8) + A[9] * 10 * qPow(X[i], 9) - A[10] * 11 * qPow(X[i], 10) + A[11] * 12 * qPow(X[i], 11) - A[12] * 13 * qPow(X[i], 12) + A[13] * 14 * qPow(X[i], 13) - A[14] * 15 * qPow(X[i], 14) + A[15] * 16 * qPow(X[i], 15) - A[16] * 17 * qPow(X[i], 16) + A[17] * 18 * qPow(X[i], 17) - A[18] * 19 * qPow(X[i], 18) + A[19] * 20 * qPow(X[i], 19));
                                        else
                                           Z2[i] = symbol * ((2 * C * X[i] * (1 + qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2))) + qPow(X[i], 3) / qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2)) * (K + 1) * qPow(C, 3)) / qPow((1 + qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2))), 2) + A[0] + A[1] * 2 * X[i] + A[2] * 3 * qPow(X[i], 2) + A[3] * 4 * qPow(X[i], 3) + A[4] * 5 * qPow(X[i], 4) + A[5] * 6 * qPow(X[i], 5) + A[6] * 7 * qPow(X[i], 6) + A[7] * 8 * qPow(X[i], 7) + A[8] * 9 * qPow(X[i], 8) + A[9] * 10 * qPow(X[i], 9) + A[10] * 11 * qPow(X[i], 10) + A[11] * 12 * qPow(X[i], 11) + A[12] * 13 * qPow(X[i], 12) + A[13] * 14 * qPow(X[i], 13) + A[14] * 15 * qPow(X[i], 14) + A[15] * 16 * qPow(X[i], 15) + A[16] * 17 * qPow(X[i], 16) + A[17] * 18 * qPow(X[i], 17) + A[18] * 19 * qPow(X[i], 18) + A[19] * 20 * qPow(X[i], 19));

                                          //  Z2[i] = symbol * ((2 * X[i] * (qPow(R, 2) + qSqrt(qPow(R, 2) - (K + 1) * qPow(X[i], 2))) + qPow(X[i], 3) * (K + 1) * C / qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2))) / qPow(1 + qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2)), 2) * qPow(C, 2)*(K+1) - A[0] + A[1] * 2 * X[i] - A[2] * 3 * qPow(X[i], 2) + A[3] * 4 * qPow(X[i], 3) - A[4] * 5 * qPow(X[i], 4) + A[5] * 6 * qPow(X[i], 5) - A[6] * 7 * qPow(X[i], 6) + A[7] * 8 * qPow(X[i], 7) - A[8] * 9 * qPow(X[i], 8) + A[9] * 10 * qPow(X[i], 9) - A[10] * 11 * qPow(X[i], 10) + A[11] * 12 * qPow(X[i], 11) - A[12] * 13 * qPow(X[i], 12) + A[13] * 14 * qPow(X[i], 13) - A[14] * 15 * qPow(X[i], 14) + A[15] * 16 * qPow(X[i], 15) - A[16] * 17 * qPow(X[i], 16) + A[17] * 18 * qPow(X[i], 17) - A[18] * 19 * qPow(X[i], 18) + A[19] * 20 * qPow(X[i], 19));

                                         B[i] = qAtan(Z2[i]) * 180 / M_PI;

                                         if (i == a / 2)
                                         {
                                             //MessageBox.Show("异常B");
                                             Z2[i] = 0;
                                             B[i] = 0;
                                         }


                                     }


                                      if (i > (D_workpiece / 2 + Dp / 2) / dist && i <= (D_workpiece / 2+R_circleCenter )/dist+1)//右边圆角部分
                                      {


                                        //  Z1[i] = Z[0] + B_p / qAbs(B_p) * (yuan_r - qSqrt(qPow(yuan_r, 2) - qPow(qAbs(X_circleCenter) - (i - a / 2) * dist, 2)));
                                          Z1[i] = -B_p / qAbs(B_p) * (yuan_r - yuan_r * qCos(B_p / 180 * M_PI)) + Z_p + B_p / qAbs(B_p) * (yuan_r - qSqrt(qPow(yuan_r, 2) - qPow(qAbs(X_circleCenter) - (i - a / 2) * dist, 2)));
                                          B[i] = -B_p / qAbs(B_p) * qAsin((qAbs(X_circleCenter) - (i - a / 2) * dist) / yuan_r) * 180 / M_PI;
                                          if (B[i] * B_p > 0)
                                              B[i] = 0;
                                          Z[i] = H + Z1[i] + h;//原点变为转动点后的Z值

                                      }

                                      if (i >(D_workpiece / 2 + R_circleCenter) / dist+1)//右边平面部分
                                      {
                                          Z1[i] = -B_p / qAbs(B_p) * (yuan_r - yuan_r * qCos(B_p / 180 * M_PI)) + Z_p;
                                          B[i] = 0;
                                          Z[i] = H + Z1[i] + h;//原点变为转动点后的Z值
                                      }



                                  }

                        double r0max = 0, r0min = 100, tempz = 0;
                             for (int i = 0; i < a + 1; i++)//x移动
                               {
                                   // ArrayList_X.Add(-D/2+i*0.001);
                                   // X[i] = -D / 2 + i * 0.001;

                                   r0[i] = qSqrt(qPow(X[i], 2) + qPow(Z[i], 2));//转动中心半径

                                   //ZZ[i] = r0[i] * qAbs(qCos(qAbs(B[i]) * M_PI / 180 + qAbs(qAsin(X[i] / r0[i]))));//Z轴转动中心
                                   //MessageBox.Show(X[i].ToString());
                                   tempz = r0[i] * qAbs(qSin(B[i] * M_PI / 180));
                                   if (tempz > r0max)
                                      r0max = tempz;
                                   if (tempz < r0min)
                                       r0min = tempz;


                                   //X2[i]=r0[i]*qCos(qAcos(X[i]/r0[i])-qAtan(Z2[i]));//x移动坐标
                                   //X2[i] = -r0[i] * qCos(M_PI / 2 + qAsin(X[i] / r0[i]) + qAtan(Z2[i]));//x移动坐标
                                   X2[i] = r0[i] * qCos(qAcos(X[i] / r0[i]) - B[i] * M_PI / 180);//x移动坐标

                                   if (isnan(X2[i]))
                                   {
                                       X2[i] = X2[i - 1];
                                       //if()
                                       //MessageBox.Show("异常X2N");
                                       normal_flag = false;
                                   }
                                   if (isinf(X2[i]))
                                   {
                                       X2[i] = X2[i - 1];
                                       //if()
                                      // MessageBox.Show("异常X2I");
                                       normal_flag = false;
                                   }

                                   //dangle=(beta1-alfa1); //切线与转动中心连线的夹角
                                   // dX=(r0*cos(dangle));

                                   ZZ[i] = qSqrt(qPow(r0[i], 2) - qPow(X2[i], 2));
                               }

                             for (int i = 0; i < a + 1; i++)//C转速
                                      {
                                          // ArrayList_X.Add(-D/2+i*0.001);
                                          //X[i] = -D / 2 + i * 0.001;
                                          //Vc[i] = -Vu * Math.Cos(Z2[i]) + Math.Sqrt(Math.Abs(Math.Pow(Vu, 2) * Math.Cos(Z2[i]) - Math.Pow(Vu, 2) + Math.Pow(Vs, 2)));
                                          Vc[i] = qSqrt(qAbs(-qPow(Vu, 2) + qPow(Vs, 2)));
                                          Nc[i] = qAbs(18 / X[i]) * 30 / M_PI * C_motor_scale_factor + C_motor_offset;

                                          if (vc_flag == true)
                                              Nc[i] = constan_vc * C_motor_scale_factor + C_motor_offset;
                                      }

                             /**************根据面型来做曲率补正系数****************/

                              /************************读取TXT里面的F************/
                              double F_store[a / 2 + 1];
                              double curvature_coefficient;


                              for (int i = 0; i <a / 2 + 1; i++)
                              {
                                   double temp = 0, temp2 = 0;
                                  // for (int j = 0; j < 100; j++)
                                  // {
                                  //if(j<10)
                                  int j = 10;
                                  temp2 = (qPow(i * 0.1 + j * 0.001, 2)*C / (1 + qSqrt(1 - (K + 1) * qPow(i * 0.1 + j * 0.001, 2)*qPow(C, 2))) + A[0] * qAbs(i * 0.1 + j * 0.001) + A[1] * qPow((i * 0.1 + j * 0.001), 2) + A[2] * qPow(qAbs(i * 0.1 + j * 0.001), 3) + A[3] * qPow((i * 0.1 + j * 0.001), 4) + A[4] * qPow(qAbs(i * 0.1 + j * 0.001), 5) + A[5] * qPow((i * 0.1 + j * 0.001), 6) + A[6] * qPow(qAbs(i * 0.1 + j * 0.001), 7) + A[7] * qPow((i * 0.1 + j * 0.001), 8) + A[8] * qPow(qAbs(i * 0.1 + j * 0.001), 9) + A[9] * qPow((i * 0.1 + j * 0.001), 10) + A[10] * qPow(qAbs(i * 0.1 + j * 0.001), 11) + A[11] * qPow((i * 0.1 + j * 0.001), 12) + A[12] * qPow(qAbs(i * 0.1 + j * 0.001), 13) + A[13] * qPow((i * 0.1 + j * 0.001), 14) + A[14] * qPow(qAbs(i * 0.1 + j * 0.001), 15) + A[15] * qPow((i * 0.1 + j * 0.001), 16) + A[16] * qPow(qAbs(i * 0.1 + j * 0.001), 17) + A[17] * qPow((i * 0.1 + j * 0.001), 18) + A[18] * qPow(qAbs(i * 0.1 + j * 0.001), 19) + A[19] * qPow((i * 0.1 + j * 0.001), 20));
                                  j = 0;
                                  temp = (qPow(i * 0.1 + j * 0.001, 2)*C / (1 + qSqrt(1 - (K + 1) * qPow(i * 0.1 + j * 0.001, 2)*qPow(C, 2))) + A[0] * qAbs(i * 0.1 + j * 0.001) + A[1] * qPow((i * 0.1 + j * 0.001), 2) + A[2] * qPow(qAbs(i * 0.1 + j * 0.001), 3) + A[3] * qPow((i * 0.1 + j * 0.001), 4) + A[4] * qPow(qAbs(i * 0.1 + j * 0.001), 5) + A[5] * qPow((i * 0.1 + j * 0.001), 6) + A[6] * qPow(qAbs(i * 0.1 + j * 0.001), 7) + A[7] * qPow((i * 0.1 + j * 0.001), 8) + A[8] * qPow(qAbs(i * 0.1 + j * 0.001), 9) + A[9] * qPow((i * 0.1 + j * 0.001), 10) + A[10] * qPow(qAbs(i * 0.1 + j * 0.001), 11) + A[11] * qPow((i * 0.1 + j * 0.001), 12) + A[12] * qPow(qAbs(i * 0.1 + j * 0.001), 13) + A[13] * qPow((i * 0.1 + j * 0.001), 14) + A[14] * qPow(qAbs(i * 0.1 + j * 0.001), 15) + A[15] * qPow((i * 0.1 + j * 0.001), 16) + A[16] * qPow(qAbs(i * 0.1 + j * 0.001), 17) + A[17] * qPow((i * 0.1 + j * 0.001), 18) + A[18] * qPow(qAbs(i * 0.1 + j * 0.001), 19) + A[19] * qPow((i * 0.1 + j * 0.001), 20));
                                  temp = qAbs(temp - temp2);
                                  temp = qSqrt(qPow(temp, 2) + qPow(0.01, 2));
                                  curvature_coefficient = temp / 0.01;
                                  if (isinf(curvature_coefficient))
                                      curvature_coefficient = 1;
                                  if(isnan(curvature_coefficient))
                                      curvature_coefficient = 1;

                                  if (curvature_compensate == 1)
                                      curvature_coefficient = 1;
                                  else if (curvature_compensate == 2)
                                      curvature_coefficient = 1 / curvature_coefficient;
                                  else
                                  { }

                                  if (i > (Dp / 2) / dist)
                                  curvature_coefficient = 1;
                                  if (tool_R == 1)
                                      F_store[i] = flat_v_1p[i] * curvature_coefficient;
                                  else if (tool_R == 5)

                                      F_store[i] = flat_v_5p[i] * curvature_coefficient;
                                   else if(tool_R==7)//垂直抛
                                      F_store[i] = flat_v_vertical[i] * curvature_coefficient;

                                  else
                                      F_store[i] = flat_v_3p[i] * curvature_coefficient;

                              }

                              for (int i = 0; i < a; i++)//F进给速度
                                        {

                                            if (i < a / 2)
                                            {
                                                F[i + 1] = F_store[a / 2 - i - 1];
                                                F[i + 1] = F[i + 1] * qAbs(X2[i + 1] - X2[i]) / (qSqrt(qPow(0.1, 2) + qPow(Z1[i + 1] - Z1[i], 2)));
                                               // if (i == 32)
                                               //     MessageBox.Show("");
                                            }
                                            else
                                            {
                                                F[i + 1] = F_store[i - a / 2];

                                                F[i + 1] = F[i + 1] * qAbs(X2[i + 1] - X2[i]) / (qSqrt(qPow(0.1, 2) + qPow(Z1[i + 1] - Z1[i], 2)));
                                            }

                                                //qAbs((X2[i + 1] - X2[i]) / T[i] * 60);
                                            if (F_flag == true)
                                                F[i + 1] = qAbs(X2[i + 1] - X2[i])/(dist / contan_F);


                                        }


                              //申请空间

//                              static double **b=new double* [c+1];

//                              for(int i=0;i<c+1;++i){
//                                  b[i]=new double[7];
//                              }

//                              double **b_null=new double* [c+1];

//                              for(int i=0;i<c+1;++i){
//                                  b_null[i]=new double[7];
//                              }

                              double ** b=0;
                              b=new double*[c+1];
                              for (int i = 0; i < c+1; i++)
                              {
                                  b[i] = new double[8];
                                  for (int j = 0; j < 7; j++)
                                  {
                                      b[i][j] =0;

                                  }
                              }

                              double ** b_null=0;
                             b_null=new double*[c+1];
                              for (int i = 0; i < c+1; i++)
                              {
                                  b_null[i] = new double[7];
                                  for (int j = 0; j < 7; j++)
                                  {
                                      b_null[i][j] =0;

                                  }
                              }



                              for (int i = 0; i < c + 1; i++)
                              {


                                  b[i][0] = X2[i+d+a/2];//x移动坐标
                                  b[i][1] = B[i + d + a / 2];//B轴角度

                                  b[i][2] = F[i + d + a / 2];//进给速度
                                  b[i][3] = Nc[i + d + a / 2];//C轴转速

                                  b[i][4] = X[i + d + a / 2];//X工件坐标
                                  b[i][5] = ZZ[i + d + a / 2];//Z轴移动坐标
                                  b[i][6] = Z1[i + d + a / 2];//函数曲线Z值

                                  b[i][7] = Y[i + d + a / 2];//Y值

                              }
                              b[0][2] = first_positon_feed;

                              if (normal_flag == false)
                              {
                           //   QMessageBox::information(, "提示", "连接失败！");     // QMessageBox.Show("输入参数有误，数据异常，生成代码失败！");
                             //     return b_null;
                              }


                              return b;
}


//生成抛镜片代码
double** Produce_Gcode::aspheric2(double press_distant,double Cloth_thickness,double curvature_compensate,double first_positon_feed,double D_workpiece, double Dp, double C_motor_scale_factor, double C_motor_offset, double Lworkpiece_h, double other_h, double SAG, double yuan_r, double ao_tu, double R_P_right, double tool_R, double constan_vc, double contan_F, bool vc_flag, bool F_flag, double dist, double symbol, double n, double vc, double H, double R_P_left, double R, double K, double A[20])
{
           vc_flag = true;//C轴恒速，变速功能不要
             double h =  - Lworkpiece_h + other_h;//B轴旋转中心到模具平面高度
              double L=Lworkpiece_h+Cloth_thickness-press_distant;//B轴回旋半径
              double LZ=other_h;//B轴回转中心到塑料治具底面距离
              double Lz2=H+ao_tu * SAG;//塑料治具底面到工件坐标原点（非球中心的距离）
             H = H + ao_tu * SAG;//求塑料治具底面到面型中心的距离
           //  double t = 0;
              dist = 0.1;//间隔为0.1
             double Vu = 19;//Vu=Wu.*Ru.*sin(U);抛光轴线速度 Vu大约等于20mm/s
             double C = 1 / R;
             double Vs = Vu + 5;//U轴和C轴的线速度模
             //加工口径左边缘的X坐标
             qDebug()<<"b_D_workpiece"<<D_workpiece ;
             qDebug()<<R_P_left ;

           //  R_P_left = floor(R_P_left * 10) / 10;//取小数后一位
             R_P_left=floor(R_P_left * 10.f + 0.5) / 10.f;

           //  Dp = floor(Dp * 10) / 10;
           //  D_workpiece = floor(D_workpiece * 10) / 10;

             Dp=floor(Dp * 10.f + 0.5) / 10.f;
            D_workpiece=floor(D_workpiece * 10.f + 0.5) / 10.f;
             qDebug()<<"a_D_workpiece"<<D_workpiece ;
             qDebug()<<R_P_left ;

            // if (R_P_left * 10 % 2 == 1)
           //      R_P_left = R_P_left + 0.1;

             if (QString::number(Dp * 10).toInt() % 2 == 1)
                 Dp = Dp + 0.1;

             if (QString::number(D_workpiece * 10).toInt() % 2 == 1)
                 D_workpiece = D_workpiece - 0.1;
            double X_p = -Dp / 2;
             int c = QString::number((R_P_right-R_P_left) / dist).toInt();//输出代码行数-1
           // qDebug()<<"c"<<c;
           //  qDebug()<<(R_P_right-R_P_left) / dist;
            // qDebug()<<(int)122;
             int a = QString::number(qRound(D_workpiece / dist)).toInt();//代码数组行数-1
             int d = QString::number(qRound((R_P_left / dist))).toInt();

             int e = QString::number((R_P_right / dist)).toInt();
             int f = QString::number(Dp / dist).toInt();
             bool normal_flag = true;
             double X[a+1];
              double Y[a+1];
             double Z[a + 1];  //原点变为转动点后的Z值
             double Z1[a + 1];//函数曲线Z值
             double Z2[a + 1];//曲线的一阶导数
             double ZZ[a + 1];//Z轴移动坐标
             double B[a + 1];//B转动角度
             double Vc[a + 1];//C线速度
             double Nc[a + 1];//C轴转速
             double F[a + 1]; //X轴进给速度
             double F1[a + 1]; //dist距离走一圈的进给速度
             double T[a + 1];  //两点间时间
             double X2[a + 1];//x移动坐标
             double r0[a + 1];//点到转动中心的夹角
             double flat_v_1p[] ={ 27.804, 24.2575, 16.5767, 11.2156, 9.2657, 8.3414, 7.4582,
                                   6.7514, 6.3777, 5.9989, 5.6724, 5.4287, 5.2395, 5.0569, 4.8999,
                                   4.7708, 4.6671, 4.5711, 4.482, 4.3991, 4.3219, 4.2464, 4.1822,
                                   4.1219, 4.0649, 4.011, 3.9599, 3.9113, 3.8651, 3.821, 3.7789, 3.7386,
                                   3.7, 3.6629, 3.6273, 3.5931, 3.5602, 3.5284, 3.4978, 3.4682, 3.4396,
                                   3.4119, 3.3852, 3.3592, 3.3341, 3.3096, 3.2859, 3.2629, 3.2405, 3.2188,
                                   3.1976, 3.1769, 3.1568, 3.1372, 3.1181, 3.0994, 3.0812, 3.0634, 3.0461,
                                   3.0291, 3.0125, 2.9963, 2.9804, 2.9648, 2.9496, 2.9347, 2.9201, 2.9057, 2.8917, 2.8779, 2.8644, 2.8512, 2.8381, 2.8254, 2.8128, 2.8005, 2.7884, 2.7765, 2.7648, 2.7533, 2.742, 2.7309, 2.72, 2.7092, 2.6986, 2.6882, 2.6779, 2.6678,
                                   2.6579, 2.6481, 2.6384, 2.6289, 2.6195, 2.6103, 2.6012, 2.5922, 2.5833,
                                   2.5746, 2.566, 2.5575, 2.5491, 2.5408, 2.5326, 2.5246, 2.5166, 2.5087,
                                   2.501, 2.4933, 2.4857, 2.4782, 2.4709, 2.4635, 2.4563, 2.4492, 2.4422,
                                   2.4352, 2.4283, 2.4215, 2.4148, 2.4081, 2.4015, 2.395, 2.3886, 2.3822,
                                   2.3759, 2.3697, 2.3635, 2.3574, 2.3514, 2.3454, 2.3395, 2.3336, 2.3278,
                                   2.3221, 2.3164, 2.3108, 2.3052, 2.2997, 2.2943, 2.2888, 2.2835, 2.2782, 2.2729, 2.2677, 2.2625, 2.2574, 2.2524, 2.2473, 2.2424, 2.2374, 2.2325, 2.2277, 2.2229, 2.2181, 2.2134, 2.2087, 2.2041, 2.1995, 2.1949, 2.1904, 2.1859, 2.1815, 2.1771, 2.1727, 2.1683, 2.164, 2.1598, 2.1555, 2.1513, 2.1472, 2.143, 2.1389, 2.1348, 2.1308, 2.1268, 2.1228, 2.1188, 2.1149, 2.111, 2.1072, 2.1033, 2.0995, 2.0957, 2.092, 2.0883, 2.0846, 2.0809, 2.0773, 2.0736, 2.07, 2.0665, 2.0629, 2.0594, 2.0559, 2.0524, 2.049, 2.0456, 2.0422, 2.0388, 2.0354, 2.0321, 2.0288, 2.0255, 2.0222, 2.019, 2.0158, 2.0126, 2.0094, 2.0062, 2.0031, 1.9999, 1.9968, 1.9937, 1.9907, 1.9876, 1.9846, 1.9816, 1.9786, 1.9756, 1.9727, 1.9697, 1.9668, 1.9639, 1.961, 1.9582, 1.9553, 1.9525, 1.9497, 1.9469, 1.9441, 1.9413, 1.9386, 1.9358, 1.9331, 1.9304, 1.9277, 1.925, 1.9224, 1.9197, 1.9171, 1.9145, 1.9119, 1.9093, 1.9067, 1.9042, 1.9016, 1.8991, 1.8966, 1.8941, 1.8916, 1.8891, 1.8866, 1.8842, 1.8817, 1.8793, 1.8769, 1.8745, 1.8721, 1.8697, 1.8674, 1.865, 1.8627, 1.8604, 1.858, 1.8557, 1.8534, 1.8512, 1.8489, 1.8466, 1.8444, 1.8422, 1.8399, 1.8377, 1.8355, 1.8333, 1.8311, 1.829, 1.8268, 1.8246, 1.8225, 1.8204, 1.8183, 1.8161, 1.814, 1.812, 1.8099, 1.8078, 1.8057, 1.8037, 1.8016, 1.7996, 1.7976, 1.7956, 1.7936, 1.7916, 1.7896, 1.7876, 1.7856, 1.7837, 1.7817, 1.7798, 1.7778, 1.7759, 1.774, 1.7721, 1.7702, 1.7683, 1.7664, 1.7645, 1.7626, 1.7608 };
             double flat_v_3p[] ={ 40.5259, 40.5141, 32.9916, 23.4416, 18.0608, 14.41, 12.4473, 11.0399, 9.7753, 8.9723, 8.2413, 7.68, 7.3041, 6.9754, 6.6848, 6.4257, 6.1929, 5.9818, 5.7891, 5.6112, 5.4335, 5.2944, 5.1922, 5.0945, 5.001, 4.9113, 4.8249, 4.7487, 4.6754, 4.6049, 4.5371, 4.4723, 4.4103, 4.3511, 4.2949, 4.2415, 4.1911, 4.1434, 4.0986, 4.0564, 4.0168, 3.9811, 3.9466, 3.9132, 3.8808, 3.8494, 3.8189, 3.7893, 3.7606, 3.7327, 3.7055, 3.6791, 3.6534, 3.6283, 3.6038, 3.58, 3.5568, 3.5341, 3.5119, 3.4903, 3.4692, 3.4485, 3.4283, 3.4085, 3.3892, 3.3702, 3.3517, 3.3335, 3.3157, 3.2982, 3.2811, 3.2644, 3.2479, 3.2317, 3.2159, 3.2003, 3.185, 3.17, 3.1553, 3.1408, 3.1265, 3.1125, 3.0987, 3.0852, 3.0718, 3.0587, 3.0458, 3.0331, 3.0206, 3.0083, 2.9962, 2.9842, 2.9725, 2.9609, 2.9494, 2.9382, 2.9271, 2.9161, 2.9053, 2.8947, 2.8842, 2.8739, 2.8636, 2.8536, 2.8436, 2.8338, 2.8241, 2.8145, 2.8051, 2.7957, 2.7865, 2.7774, 2.7684, 2.7596, 2.7508, 2.7421, 2.7335, 2.7251, 2.7167, 2.7084, 2.7002, 2.6922, 2.6842, 2.6762, 2.6684, 2.6607, 2.653, 2.6455, 2.638, 2.6306, 2.6232, 2.616, 2.6088, 2.6017, 2.5946, 2.5877, 2.5808, 2.574, 2.5672, 2.5605, 2.5539, 2.5473, 2.5408, 2.5344, 2.528, 2.5217, 2.5154, 2.5092, 2.5031, 2.497, 2.491, 2.485, 2.4791, 2.4732, 2.4674, 2.4616, 2.4559, 2.4502, 2.4446, 2.4391, 2.4335, 2.4281, 2.4226, 2.4172, 2.4119, 2.4066, 2.4014, 2.3962, 2.391, 2.3859, 2.3808, 2.3757, 2.3707, 2.3658, 2.3608, 2.356, 2.3511, 2.3463, 2.3415, 2.3368, 2.3321, 2.3274, 2.3228, 2.3182, 2.3136, 2.3091, 2.3046, 2.3001, 2.2957, 2.2913, 2.287, 2.2826, 2.2783, 2.274, 2.2698, 2.2656, 2.2614, 2.2572, 2.2531, 2.249, 2.2449, 2.2409, 2.2369, 2.2329, 2.2289, 2.225, 2.2211, 2.2172, 2.2133, 2.2095, 2.2057, 2.2019, 2.1981, 2.1944, 2.1907, 2.187, 2.1833, 2.1797, 2.1761, 2.1723, 2.168, 2.163, 2.1585, 2.155, 2.1515, 2.148, 2.1446, 2.1412, 2.1378, 2.1344, 2.131, 2.1277, 2.1244, 2.121, 2.1178, 2.1145, 2.1112, 2.108, 2.1048, 2.1016, 2.0984, 2.0953, 2.0921, 2.089, 2.0859, 2.0828, 2.0798, 2.0767, 2.0737, 2.0707, 2.0677, 2.0647, 2.0617, 2.0587, 2.0558, 2.0529, 2.05, 2.0471, 2.0442, 2.0414, 2.0385, 2.0357, 2.0329, 2.0301, 2.0273, 2.0245, 2.0217, 2.019, 2.0163, 2.0136, 2.0108, 2.0082, 2.0055, 2.0028, 2.0002, 1.9975, 1.9949, 1.9923, 1.9897, 1.9871, 1.9845, 1.982, 1.9794, 1.9769, 1.9744, 1.9719, 1.9694, 1.9669, 1.9644, 1.962, 1.9595, 1.9571, 1.9546, 1.9522, 1.9498, 1.9474, 1.945, 1.9427, 1.9403, 1.9379, 1.9356, 1.9333, 1.9309, 1.9286, 1.9263, 1.9241, 1.9218, 1.9195, 1.9172, 1.915, 1.9128 };
             double flat_v_5p[] ={ 45.201, 44.14, 39.91,31.5091, 25.0356, 20.3111, 16.5255, 14.4076, 12.827, 11.6089, 10.5568, 9.6852, 9.0155, 8.4652, 8.005, 7.6123, 7.2689, 6.9609, 6.678, 6.4284, 6.2069, 6.0652, 5.9219, 5.7785, 5.6365, 5.4985, 5.3666, 5.2474, 5.1562, 5.0698, 4.9876, 4.917, 4.8496, 4.7852, 4.7235, 4.6643, 4.6076, 4.553, 4.5005, 4.45, 4.4013, 4.3543, 4.3089, 4.2651, 4.2227, 4.1816, 4.1419, 4.1033, 4.0659, 4.0297, 3.9944, 3.9602, 3.9269, 3.8945, 3.863, 3.8323, 3.8024, 3.7733, 3.7448, 3.7171, 3.6901, 3.6636, 3.6378, 3.6126, 3.588, 3.5639, 3.5403, 3.5172, 3.4947, 3.4726, 3.4509, 3.4297, 3.4089, 3.3885, 3.3685, 3.3489, 3.3297, 3.3108, 3.2923, 3.2741, 3.2563, 3.2388, 3.2215, 3.2046, 3.188, 3.1716, 3.1555, 3.1397, 3.1241, 3.1088, 3.0938, 3.0789, 3.0643, 3.05, 3.0358, 3.0219, 3.0082, 2.9947, 2.9813, 2.9682, 2.9553, 2.9425, 2.9299, 2.9175, 2.9053, 2.8932, 2.8813, 2.8696, 2.858, 2.8466, 2.8353, 2.8242, 2.8132, 2.8024, 2.7916, 2.7811, 2.7706, 2.7603, 2.7501, 2.74, 2.7301, 2.7203, 2.7105, 2.7009, 2.6914, 2.6821, 2.6728, 2.6636, 2.6546, 2.6456, 2.6367, 2.628, 2.6193, 2.6107, 2.6022, 2.5938, 2.5855, 2.5773, 2.5692, 2.5611, 2.5531, 2.5453, 2.5374, 2.5297, 2.5221, 2.5145, 2.507, 2.4996, 2.4922, 2.4849, 2.4777, 2.4706, 2.4635, 2.4565, 2.4495, 2.4426, 2.4358, 2.4291, 2.4224, 2.4157, 2.4092, 2.4026, 2.3962, 2.3898, 2.3834, 2.3771, 2.3709, 2.3647, 2.3586, 2.3525, 2.3465, 2.3405, 2.3346, 2.3287, 2.3229, 2.3171, 2.3114, 2.3057, 2.3001, 2.2945, 2.2889, 2.2834, 2.2779, 2.2725, 2.2671, 2.2618, 2.2565, 2.2513, 2.2461, 2.2409, 2.2357, 2.2306, 2.2256, 2.2206, 2.2156, 2.2106, 2.2057, 2.2009, 2.196, 2.1912, 2.1864, 2.1817, 2.177, 2.1723, 2.1677, 2.1631, 2.1585, 2.154, 2.1495, 2.145, 2.1406, 2.1361, 2.1318, 2.1274, 2.1231, 2.1188, 2.1145, 2.1103, 2.1061, 2.1019, 2.0977, 2.0925, 2.0875, 2.0834, 2.0794, 2.0753, 2.0713, 2.0674, 2.0634, 2.0595, 2.0556, 2.0517, 2.0479, 2.044, 2.0402, 2.0365, 2.0327, 2.029, 2.0252, 2.0216, 2.0179, 2.0142, 2.0106, 2.007, 2.0034, 1.9999, 1.9963, 1.9928, 1.9893, 1.9858, 1.9824, 1.9789, 1.9755, 1.9721, 1.9687, 1.9654, 1.962, 1.9587, 1.9554, 1.9521, 1.9488, 1.9456, 1.9423, 1.9391, 1.9359, 1.9328, 1.9296, 1.9264, 1.9233, 1.9202, 1.9171, 1.914, 1.911, 1.9079, 1.9049, 1.9019, 1.8989, 1.8959, 1.8929, 1.89, 1.887, 1.8841, 1.8812, 1.8783, 1.8754, 1.8725, 1.8697, 1.8669, 1.864, 1.8612, 1.8584, 1.8556, 1.8529, 1.8501, 1.8474, 1.8447, 1.8419, 1.8392, 1.8366, 1.8339, 1.8312, 1.8286, 1.8259, 1.8233, 1.8207, 1.8181, 1.8155, 1.8129, 1.8104, 1.8078, 1.8053 };
             double flat_v_vertical[] ={ 29.474, 28.685, 27.348, 25.973, 17.534, 12.548, 11.556, 10.321, 8.903, 8.097, 7.608, 6.85, 6.639, 6.087, 5.697, 5.493, 5.426, 5.249, 5.031, 4.889, 4.774, 4.742, 4.563, 4.622, 4.32, 4.326, 4.269, 4.196, 4.27, 4.117, 4.073, 4.027, 3.912, 3.875, 3.945, 3.868, 3.828, 3.721, 3.806, 3.77, 3.741, 3.621, 3.754, 3.592, 3.563, 3.629, 3.495, 3.533, 3.535, 3.557, 3.358, 3.403, 3.375, 3.466, 3.357, 3.388, 3.319, 3.256, 3.277, 3.136, 3.174, 3.136, 3.151, 3.13, 3.103, 3.096, 3.116, 3.031, 3.022, 2.958, 3.014, 3.017, 3.066, 3.076, 3.067, 3.057, 3.047, 3.037, 3.027, 3.017, 3.007, 2.997, 2.987, 2.977, 2.967, 2.957, 2.947, 2.937, 2.927, 2.917, 2.907, 2.897, 2.887, 2.877, 2.867, 2.857, 2.847, 2.837, 2.827, 2.817, 2.807, 2.797, 2.787, 2.777, 2.767, 2.757, 2.747, 2.737, 2.727, 2.717, 2.707, 2.697, 2.687, 2.677, 2.667, 2.657, 2.647, 2.637, 2.627, 2.617, 2.607, 2.597, 2.587, 2.577, 2.567, 2.557, 2.5453, 2.5374, 2.5297, 2.5221, 2.5145, 2.507, 2.4996, 2.4922, 2.4849, 2.4777, 2.4706, 2.4635, 2.4565, 2.4495, 2.4426, 2.4358, 2.4291, 2.4224, 2.4157, 2.4092, 2.4026, 2.3962, 2.3898, 2.3834, 2.3771, 2.3709, 2.3647, 2.3586, 2.3525, 2.3465, 2.3405, 2.3346, 2.3287, 2.3229, 2.3171, 2.3114, 2.3057, 2.3001, 2.2945, 2.2889, 2.2834, 2.2779, 2.2725, 2.2671, 2.2618, 2.2565, 2.2513, 2.2461, 2.2409, 2.2357, 2.2306, 2.2256, 2.2206, 2.2156, 2.2106, 2.2057, 2.2009, 2.196, 2.1912, 2.1864, 2.1817, 2.177, 2.1723, 2.1677, 2.1631, 2.1585, 2.154, 2.1495, 2.145, 2.1406, 2.1361, 2.1318, 2.1274, 2.1231, 2.1188, 2.1145, 2.1103, 2.1061, 2.1019, 2.0977, 2.0925, 2.0875, 2.0834, 2.0794, 2.0753, 2.0713, 2.0674, 2.0634, 2.0595, 2.0556, 2.0517, 2.0479, 2.044, 2.0402, 2.0365, 2.0327, 2.029, 2.0252, 2.0216, 2.0179, 2.0142, 2.0106, 2.007, 2.0034, 1.9999, 1.9963, 1.9928, 1.9893, 1.9858, 1.9824, 1.9789, 1.9755, 1.9721, 1.9687, 1.9654, 1.962, 1.9587, 1.9554, 1.9521, 1.9488, 1.9456, 1.9423, 1.9391, 1.9359, 1.9328, 1.9296, 1.9264, 1.9233, 1.9202, 1.9171, 1.914, 1.911, 1.9079, 1.9049, 1.9019, 1.8989, 1.8959, 1.8929, 1.89, 1.887, 1.8841, 1.8812, 1.8783, 1.8754, 1.8725, 1.8697, 1.8669, 1.864, 1.8612, 1.8584, 1.8556, 1.8529, 1.8501, 1.8474, 1.8447, 1.8419, 1.8392, 1.8366, 1.8339, 1.8312, 1.8286, 1.8259, 1.8233, 1.8207, 1.8181, 1.8155, 1.8129, 1.8104, 1.8078, 1.8053, 1.8027, 1.8002, 1.7976, 1.7951, 1.7925, 1.79, 1.7874, 1.7849, 1.7823, 1.7798, 1.7772, 1.7747, 1.7721, 1.7696, 1.767 };
             double Z11 = symbol * (qPow(X[f / 2 + a / 2], 2) * C / (1 + qSqrt(1 - (K + 1) * qPow(X[f / 2 + a / 2], 2) * qPow(C, 2))) + A[0] * qAbs(X[f / 2 + a / 2]) + A[1] * qPow((X[f / 2 + a / 2]), 2) + A[2] * qPow(qAbs(X[f / 2 + a / 2]), 3) + A[3] * qPow((X[f / 2 + a / 2]), 4) + A[4] * qPow(qAbs(X[f / 2 + a / 2]), 5) + A[5] * qPow((X[f / 2 + a / 2]), 6) + A[6] * qPow(qAbs(X[f / 2 + a / 2]), 7) + A[7] * qPow((X[f / 2 + a / 2]), 8) + A[8] * qPow(qAbs(X[f / 2 + a / 2]), 9) + A[9] * qPow((X[f / 2 + a / 2]), 10) + A[10] * qPow(qAbs(X[f / 2 + a / 2]), 11) + A[11] * qPow((X[f / 2 + a / 2]), 12) + A[12] * qPow(qAbs(X[f / 2 + a / 2]), 13) + A[13] * qPow((X[f / 2 + a / 2]), 14) + A[14] * qPow(qAbs(X[f / 2 + a / 2]), 15) + A[15] * qPow((X[f / 2 + a / 2]), 16) + A[16] * qPow(qAbs(X[f / 2 + a / 2]), 17) + A[17] * qPow((X[f / 2 + a / 2]), 18) + A[18] * qPow(qAbs(X[f / 2 + a / 2]), 19) + A[19] * qPow((X[f / 2 + a / 2]), 20));


             Produce_Gcode::row=c+1;//行数
              Produce_Gcode::colum=8;//列数=c+1;//行数
              //Produce_Gcode::colum=7;//列数
//QDebug<<Qstring(Produce_Gcode::row);
             for (int i = 0; i < a + 1; i++)//x坐标
                       {
                          // ArrayList_X.Add(-D/2+i*0.001);
                           X[i] = -D_workpiece / 2 + i * dist;
                           Y[i]=0;
                       }

             if (Z11 > 0&&ao_tu>0)
                  {
                      H = H -2*ao_tu * SAG;
                  }
                  if (Z11 < 0 && ao_tu < 0)
                  {
                      H = H - 2 * ao_tu * SAG;
                  }

                  //加工口径左边缘B角度
                        double tan_B_p;
                         if(X_p>=0)
                         tan_B_p = symbol * ((2 * C * X_p * (1 + qSqrt(1 - (K + 1) * qPow(X_p, 2) * qPow(C, 2))) + qPow(X_p, 3) / qSqrt(1 - (K + 1) * qPow(X_p, 2) * qPow(C, 2)) * (K + 1) * qPow(C, 3)) / qPow((1 + qSqrt(1 - (K + 1) * qPow(X_p, 2) * qPow(C, 2))), 2) + A[0] + A[1] * 2 * X_p + A[2] * 3 * qPow(X_p, 2) + A[3] * 4 * qPow(X_p, 3) + A[4] * 5 * qPow(X_p, 4) + A[5] * 6 * qPow(X_p, 5) + A[6] * 7 * qPow(X_p, 6) + A[7] * 8 * qPow(X_p, 7) + A[8] * 9 * qPow(X_p, 8) + A[9] * 10 * qPow(X_p, 9) + A[10] * 11 * qPow(X_p, 10) + A[11] * 12 * qPow(X_p, 11) + A[12] * 13 * qPow(X_p, 12) + A[13] * 14 * qPow(X_p, 13) + A[14] * 15 * qPow(X_p, 14) + A[15] * 16 * qPow(X_p, 15) + A[16] * 17 * qPow(X_p, 16) + A[17] * 18 * qPow(X_p, 17) + A[18] * 19 * qPow(X_p, 18) + A[19] * 20 * qPow(X_p, 19));//正切值
                         else
                             tan_B_p = symbol * ((2 * C * X_p * (1 + qSqrt(1 - (K + 1) * qPow(X_p, 2) * qPow(C, 2))) + qPow(X_p, 3) / qSqrt(1 - (K + 1) * qPow(X_p, 2) * qPow(C, 2)) * (K + 1) * qPow(C, 3)) / qPow((1 + qSqrt(1 - (K + 1) * qPow(X_p, 2) * qPow(C, 2))), 2) - A[0] + A[1] * 2 * X_p - A[2] * 3 * qPow(X_p, 2) + A[3] * 4 * qPow(X_p, 3) - A[4] * 5 * qPow(X_p, 4) + A[5] * 6 * qPow(X_p, 5) - A[6] * 7 * qPow(X_p, 6) + A[7] * 8 * qPow(X_p, 7) - A[8] * 9 * qPow(X_p, 8) + A[9] * 10 * qPow(X_p, 9) - A[10] * 11 * qPow(X_p, 10) + A[11] * 12 * qPow(X_p, 11) - A[12] * 13 * qPow(X_p, 12) + A[13] * 14 * qPow(X_p, 13) - A[14] * 15 * qPow(X_p, 14) + A[15] * 16 * qPow(X_p, 15) - A[16] * 17 * qPow(X_p, 16) + A[17] * 18 * qPow(X_p, 17) - A[18] * 19 * qPow(X_p, 18) + A[19] * 20 * qPow(X_p, 19));//正切值


                         double B_p = qAtan(tan_B_p) * 180 / M_PI;  //B角度

                        //加工口径左边缘Z坐标
                        double Z_p = symbol * (qPow(X_p, 2) * C / (1 + qSqrt(1 - (K + 1) * qPow(X_p, 2) * qPow(C, 2))) + A[0] * qAbs(X_p) + A[1] * qPow((X_p), 2) + A[2] * qPow(qAbs(X_p), 3) + A[3] * qPow((X_p), 4) + A[4] * qPow(qAbs(X_p), 5) + A[5] * qPow((X_p), 6) + A[6] * qPow(qAbs(X_p), 7) + A[7] * qPow((X_p), 8) + A[8] * qPow(qAbs(X_p), 9) + A[9] * qPow((X_p), 10) + A[10] * qPow(qAbs(X_p), 11) + A[11] * qPow((X_p), 12) + A[12] * qPow(qAbs(X_p), 13) + A[13] * qPow((X_p), 14) + A[14] * qPow(qAbs(X_p), 15) + A[15] * qPow((X_p), 16) + A[16] * qPow(qAbs(X_p), 17) + A[17] * qPow((X_p), 18) + A[18] * qPow(qAbs(X_p), 19) + A[19] * qPow((X_p), 20));


                        //左圆角圆心X坐标
                        double X_circleCenter = -qAbs(yuan_r * qSin(B_p/180*M_PI)) + X_p;
                       // double tempP = qAsin((X_p - X_circleCenter) / yuan_r) * 180 / M_PI;


                         //左圆角圆心Z坐标
                        double Z_circleCenter = B_p/qAbs(B_p)*yuan_r * qCos(B_p) + Z_p;

                       //左圆角圆心左边取一位小数位


                        double R_circleCenter=floor((qAbs(X_circleCenter)*10))/10;


                        for (int i = 0; i < a + 1; i++)//B角度，
                                 {


                                      //ArrayList_X.Add(-D / 2 + i * 0.001);
                                      //double[] values = ArrayList_X.Cast<double>().ToArray();
                                      //double[] d = Convert.ToDouble(X[i]);

                                      if (i < (D_workpiece / 2 - R_circleCenter)/dist-1)//平面左边部分
                                      {
                                          Z1[i] = -B_p / qAbs(B_p) * (yuan_r - yuan_r * qCos(B_p / 180 * M_PI)) + Z_p;
                                          B[i] = 0;
                                          Z[i] = H + Z1[i] + h;//原点变为转动点后的Z值
                                      }
                                      if (i >= ((D_workpiece / 2 - R_circleCenter) / dist)-1 && i < (D_workpiece / 2 - Dp/2) / dist)//左边圆角部分
                                      {
                                         // Z1[i] = Z[0] + B_p / qAbs(B_p) * (yuan_r - qSqrt(qPow(yuan_r, 2) - qPow(qAbs(X_circleCenter) - (a / 2 - i) * dist, 2)));
                                          Z1[i] = -B_p / qAbs(B_p) * (yuan_r - yuan_r * qCos(B_p / 180 * M_PI)) + Z_p + B_p / qAbs(B_p) * (yuan_r - qSqrt(qPow(yuan_r, 2) - qPow(qAbs(X_circleCenter) - (a / 2 - i) * dist, 2)));
                                          B[i] = -B_p / qAbs(B_p) * qAsin((qAbs(X_circleCenter) - (a / 2 - i) * dist) / yuan_r) * 180 / M_PI;
                                          if (B[i] * (-B_p) < 0)
                                              B[i] = 0;
                                          Z[i] = H + Z1[i] + h;//原点变为转动点后的Z值
                                      }
                                      if (i >=QString::number((D_workpiece / 2 - Dp / 2) / dist).toInt() && i<= QString::number((D_workpiece / 2 + Dp / 2)/dist).toInt())
                                     {

                                         Z1[i] = symbol * (qPow(X[i], 2) * C / (1 + qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2))) + A[0] * qAbs(X[i]) + A[1] * qPow((X[i]), 2) + A[2] * qPow(qAbs(X[i]), 3) + A[3] * qPow((X[i]), 4) + A[4] * qPow(qAbs(X[i]), 5) + A[5] * qPow((X[i]), 6) + A[6] * qPow(qAbs(X[i]), 7) + A[7] * qPow((X[i]), 8) + A[8] * qPow(qAbs(X[i]), 9) + A[9] * qPow((X[i]), 10) + A[10] * qPow(qAbs(X[i]), 11) + A[11] * qPow((X[i]), 12) + A[12] * qPow(qAbs(X[i]), 13) + A[13] * qPow((X[i]), 14) + A[14] * qPow(qAbs(X[i]), 15) + A[15] * qPow((X[i]), 16) + A[16] * qPow(qAbs(X[i]), 17) + A[17] * qPow((X[i]), 18) + A[18] * qPow(qAbs(X[i]), 19) + A[19] * qPow((X[i]), 20));
                                       //  Z1[i] = symbol * (qPow(X[i], 2) * C / (1 + qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2))) - A[0] * qAbs(X[i]) + A[1] * qPow((X[i]), 2) - A[2] * qPow(qAbs(X[i]), 3) + A[3] * qPow((X[i]), 4) - A[4] * qPow(qAbs(X[i]), 5) + A[5] * qPow((X[i]), 6) - A[6] * qPow(qAbs(X[i]), 7) + A[7] * qPow((X[i]), 8) - A[8] * qPow(qAbs(X[i]), 9) + A[9] * qPow((X[i]), 10) + A[10] * qPow(qAbs(X[i]), 11) + A[11] * qPow((X[i]), 12) + A[12] * qPow(qAbs(X[i]), 13) + A[13] * qPow((X[i]), 14) + A[14] * qPow(qAbs(X[i]), 15) + A[15] * qPow((X[i]), 16) + A[16] * qPow(qAbs(X[i]), 17) + A[17] * qPow((X[i]), 18) + A[18] * qPow(qAbs(X[i]), 19) + A[19] * qPow((X[i]), 20));

                                         if (isnan(Z1[i]))
                                         {
                                             Z1[i] = Z1[i - 2];
                                             //if()
                                       //      MessageBox.Show("异常Z1N");
                                             normal_flag = false;
                                         }

                                         if (isinf(Z1[i]))
                                         {
                                             Z1[i] = Z1[i - 1] + Z1[i - 1] - Z1[i - 2];
                                             //if()
                                          //   MessageBox.Show("异常Z1I");
                                             normal_flag = false;
                                         }

                                         Z[i] = H + Z1[i] + h;// -Z1[a - 1];

                                      //   Z2[i] = symbol * ((2 * C * X[i] * (1 + qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2))) + qPow(X[i], 3) / qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2)) * (K + 1) * qPow(C, 3)) / qPow((1 + qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2))), 2) + A[0] + A[1] * 2 * X[i] + A[2] * 3 * qPow(X[i], 2) + A[3] * 4 * qPow(X[i], 3) + A[4] * 5 * qPow(X[i], 4) + A[5] * 6 * qPow(X[i], 5) + A[6] * 7 * qPow(X[i], 6) + A[7] * 8 * qPow(X[i], 7) + A[8] * 9 * qPow(X[i], 8) + A[9] * 10 * qPow(X[i], 9) + A[10] * 11 * qPow(X[i], 10) + A[11] * 12 * qPow(X[i], 11) + A[12] * 13 * qPow(X[i], 12) + A[13] * 14 * qPow(X[i], 13) + A[14] * 15 * qPow(X[i], 14) + A[15] * 16 * qPow(X[i], 15) + A[16] * 17 * qPow(X[i], 16) + A[17] * 18 * qPow(X[i], 17) + A[18] * 19 * qPow(X[i], 18) + A[19] * 20 * qPow(X[i], 19));
                                        if(X[i]<=0)
                                         Z2[i] = symbol * ((2 * C * X[i] * (1 + qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2))) + qPow(X[i], 3) / qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2)) * (K + 1) * qPow(C, 3)) / qPow((1 + qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2))), 2) - A[0] + A[1] * 2 * X[i] - A[2] * 3 * qPow(X[i], 2) + A[3] * 4 * qPow(X[i], 3) - A[4] * 5 * qPow(X[i], 4) + A[5] * 6 * qPow(X[i], 5) - A[6] * 7 * qPow(X[i], 6) + A[7] * 8 * qPow(X[i], 7) - A[8] * 9 * qPow(X[i], 8) + A[9] * 10 * qPow(X[i], 9) - A[10] * 11 * qPow(X[i], 10) + A[11] * 12 * qPow(X[i], 11) - A[12] * 13 * qPow(X[i], 12) + A[13] * 14 * qPow(X[i], 13) - A[14] * 15 * qPow(X[i], 14) + A[15] * 16 * qPow(X[i], 15) - A[16] * 17 * qPow(X[i], 16) + A[17] * 18 * qPow(X[i], 17) - A[18] * 19 * qPow(X[i], 18) + A[19] * 20 * qPow(X[i], 19));
                                        else
                                           Z2[i] = symbol * ((2 * C * X[i] * (1 + qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2))) + qPow(X[i], 3) / qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2)) * (K + 1) * qPow(C, 3)) / qPow((1 + qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2))), 2) + A[0] + A[1] * 2 * X[i] + A[2] * 3 * qPow(X[i], 2) + A[3] * 4 * qPow(X[i], 3) + A[4] * 5 * qPow(X[i], 4) + A[5] * 6 * qPow(X[i], 5) + A[6] * 7 * qPow(X[i], 6) + A[7] * 8 * qPow(X[i], 7) + A[8] * 9 * qPow(X[i], 8) + A[9] * 10 * qPow(X[i], 9) + A[10] * 11 * qPow(X[i], 10) + A[11] * 12 * qPow(X[i], 11) + A[12] * 13 * qPow(X[i], 12) + A[13] * 14 * qPow(X[i], 13) + A[14] * 15 * qPow(X[i], 14) + A[15] * 16 * qPow(X[i], 15) + A[16] * 17 * qPow(X[i], 16) + A[17] * 18 * qPow(X[i], 17) + A[18] * 19 * qPow(X[i], 18) + A[19] * 20 * qPow(X[i], 19));

                                          //  Z2[i] = symbol * ((2 * X[i] * (qPow(R, 2) + qSqrt(qPow(R, 2) - (K + 1) * qPow(X[i], 2))) + qPow(X[i], 3) * (K + 1) * C / qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2))) / qPow(1 + qSqrt(1 - (K + 1) * qPow(X[i], 2) * qPow(C, 2)), 2) * qPow(C, 2)*(K+1) - A[0] + A[1] * 2 * X[i] - A[2] * 3 * qPow(X[i], 2) + A[3] * 4 * qPow(X[i], 3) - A[4] * 5 * qPow(X[i], 4) + A[5] * 6 * qPow(X[i], 5) - A[6] * 7 * qPow(X[i], 6) + A[7] * 8 * qPow(X[i], 7) - A[8] * 9 * qPow(X[i], 8) + A[9] * 10 * qPow(X[i], 9) - A[10] * 11 * qPow(X[i], 10) + A[11] * 12 * qPow(X[i], 11) - A[12] * 13 * qPow(X[i], 12) + A[13] * 14 * qPow(X[i], 13) - A[14] * 15 * qPow(X[i], 14) + A[15] * 16 * qPow(X[i], 15) - A[16] * 17 * qPow(X[i], 16) + A[17] * 18 * qPow(X[i], 17) - A[18] * 19 * qPow(X[i], 18) + A[19] * 20 * qPow(X[i], 19));

                                         B[i] = -qAtan(Z2[i]) * 180 / M_PI;

                                         if (i == a / 2)
                                         {
                                             //MessageBox.Show("异常B");
                                             Z2[i] = 0;
                                             B[i] = 0;
                                         }


                                     }


                                      if (i > (D_workpiece / 2 + Dp / 2) / dist && i <= (D_workpiece / 2+R_circleCenter )/dist+1)//右边圆角部分
                                      {


                                        //  Z1[i] = Z[0] + B_p / qAbs(B_p) * (yuan_r - qSqrt(qPow(yuan_r, 2) - qPow(qAbs(X_circleCenter) - (i - a / 2) * dist, 2)));
                                          Z1[i] = -B_p / qAbs(B_p) * (yuan_r - yuan_r * qCos(B_p / 180 * M_PI)) + Z_p + B_p / qAbs(B_p) * (yuan_r - qSqrt(qPow(yuan_r, 2) - qPow(qAbs(X_circleCenter) - (i - a / 2) * dist, 2)));
                                          B[i] = B_p / qAbs(B_p) * qAsin((qAbs(X_circleCenter) - (i - a / 2) * dist) / yuan_r) * 180 / M_PI;
                                          if (B[i] * B_p < 0)
                                              B[i] = 0;
                                          Z[i] = H + Z1[i] + h;//原点变为转动点后的Z值

                                      }

                                      if (i >(D_workpiece / 2 + R_circleCenter) / dist+1)//右边平面部分
                                      {
                                          Z1[i] = -B_p / qAbs(B_p) * (yuan_r - yuan_r * qCos(B_p / 180 * M_PI)) + Z_p;
                                          B[i] = 0;
                                          Z[i] = H + Z1[i] + h;//原点变为转动点后的Z值
                                      }



                                  }

                        double r0max = 0, r0min = 100, tempz = 0;
                             for (int i = 0; i < a + 1; i++)//x移动
                               {
                                   // ArrayList_X.Add(-D/2+i*0.001);
                                   // X[i] = -D / 2 + i * 0.001;

                                   r0[i] = qSqrt(qPow(X[i], 2) + qPow(Z[i], 2));//转动中心半径

                                   //ZZ[i] = r0[i] * qAbs(qCos(qAbs(B[i]) * M_PI / 180 + qAbs(qAsin(X[i] / r0[i]))));//Z轴转动中心
                                   //MessageBox.Show(X[i].ToString());
                                   tempz = r0[i] * qAbs(qSin(B[i] * M_PI / 180));
                                   if (tempz > r0max)
                                      r0max = tempz;
                                   if (tempz < r0min)
                                       r0min = tempz;


                                   //X2[i]=r0[i]*qCos(qAcos(X[i]/r0[i])-qAtan(Z2[i]));//x移动坐标
                                   //X2[i] = -r0[i] * qCos(M_PI / 2 + qAsin(X[i] / r0[i]) + qAtan(Z2[i]));//x移动坐标
                               //    X2[i] = r0[i] * qCos(qAcos(X[i] / r0[i]) - B[i] * M_PI / 180);//x移动坐标
                                  //  X2[i] = L * qCos(B[i] * M_PI / 180)+X[i];//x移动坐标
                                   X2[i] = -(L * qSin(B[i] * M_PI / 180)+X[i]);
                                   if (isnan(X2[i]))
                                   {
                                       X2[i] = X2[i - 1];
                                       //if()
                                       //MessageBox.Show("异常X2N");
                                       normal_flag = false;
                                   }
                                   if (isinf(X2[i]))
                                   {
                                       X2[i] = X2[i - 1];
                                       //if()
                                      // MessageBox.Show("异常X2I");
                                       normal_flag = false;
                                   }

                                   //dangle=(beta1-alfa1); //切线与转动中心连线的夹角
                                   // dX=(r0*cos(dangle));

                                  // ZZ[i] = qSqrt(qPow(r0[i], 2) - qPow(X2[i], 2));
                                   ZZ[i] = L * qCos(B[i] * M_PI / 180)+Z1[i]+Lz2-LZ;//Z轴移动坐标
                               }

                             for (int i = 0; i < a + 1; i++)//C转速
                                      {
                                          // ArrayList_X.Add(-D/2+i*0.001);
                                          //X[i] = -D / 2 + i * 0.001;
                                          //Vc[i] = -Vu * Math.Cos(Z2[i]) + Math.Sqrt(Math.Abs(Math.Pow(Vu, 2) * Math.Cos(Z2[i]) - Math.Pow(Vu, 2) + Math.Pow(Vs, 2)));
                                          Vc[i] = qSqrt(qAbs(-qPow(Vu, 2) + qPow(Vs, 2)));
                                          Nc[i] = qAbs(18 / X[i]) * 30 / M_PI * C_motor_scale_factor + C_motor_offset;

                                          if (vc_flag == true)
                                              Nc[i] = constan_vc * C_motor_scale_factor + C_motor_offset;
                                      }

                             /**************根据面型来做曲率补正系数****************/

                              /************************读取TXT里面的F************/
                              double F_store[a / 2 + 1];
                              double curvature_coefficient;


                              for (int i = 0; i <a / 2 + 1; i++)
                              {
                                   double temp = 0, temp2 = 0;
                                  // for (int j = 0; j < 100; j++)
                                  // {
                                  //if(j<10)
                                  int j = 10;
                                  temp2 = (qPow(i * 0.1 + j * 0.001, 2)*C / (1 + qSqrt(1 - (K + 1) * qPow(i * 0.1 + j * 0.001, 2)*qPow(C, 2))) + A[0] * qAbs(i * 0.1 + j * 0.001) + A[1] * qPow((i * 0.1 + j * 0.001), 2) + A[2] * qPow(qAbs(i * 0.1 + j * 0.001), 3) + A[3] * qPow((i * 0.1 + j * 0.001), 4) + A[4] * qPow(qAbs(i * 0.1 + j * 0.001), 5) + A[5] * qPow((i * 0.1 + j * 0.001), 6) + A[6] * qPow(qAbs(i * 0.1 + j * 0.001), 7) + A[7] * qPow((i * 0.1 + j * 0.001), 8) + A[8] * qPow(qAbs(i * 0.1 + j * 0.001), 9) + A[9] * qPow((i * 0.1 + j * 0.001), 10) + A[10] * qPow(qAbs(i * 0.1 + j * 0.001), 11) + A[11] * qPow((i * 0.1 + j * 0.001), 12) + A[12] * qPow(qAbs(i * 0.1 + j * 0.001), 13) + A[13] * qPow((i * 0.1 + j * 0.001), 14) + A[14] * qPow(qAbs(i * 0.1 + j * 0.001), 15) + A[15] * qPow((i * 0.1 + j * 0.001), 16) + A[16] * qPow(qAbs(i * 0.1 + j * 0.001), 17) + A[17] * qPow((i * 0.1 + j * 0.001), 18) + A[18] * qPow(qAbs(i * 0.1 + j * 0.001), 19) + A[19] * qPow((i * 0.1 + j * 0.001), 20));
                                  j = 0;
                                  temp = (qPow(i * 0.1 + j * 0.001, 2)*C / (1 + qSqrt(1 - (K + 1) * qPow(i * 0.1 + j * 0.001, 2)*qPow(C, 2))) + A[0] * qAbs(i * 0.1 + j * 0.001) + A[1] * qPow((i * 0.1 + j * 0.001), 2) + A[2] * qPow(qAbs(i * 0.1 + j * 0.001), 3) + A[3] * qPow((i * 0.1 + j * 0.001), 4) + A[4] * qPow(qAbs(i * 0.1 + j * 0.001), 5) + A[5] * qPow((i * 0.1 + j * 0.001), 6) + A[6] * qPow(qAbs(i * 0.1 + j * 0.001), 7) + A[7] * qPow((i * 0.1 + j * 0.001), 8) + A[8] * qPow(qAbs(i * 0.1 + j * 0.001), 9) + A[9] * qPow((i * 0.1 + j * 0.001), 10) + A[10] * qPow(qAbs(i * 0.1 + j * 0.001), 11) + A[11] * qPow((i * 0.1 + j * 0.001), 12) + A[12] * qPow(qAbs(i * 0.1 + j * 0.001), 13) + A[13] * qPow((i * 0.1 + j * 0.001), 14) + A[14] * qPow(qAbs(i * 0.1 + j * 0.001), 15) + A[15] * qPow((i * 0.1 + j * 0.001), 16) + A[16] * qPow(qAbs(i * 0.1 + j * 0.001), 17) + A[17] * qPow((i * 0.1 + j * 0.001), 18) + A[18] * qPow(qAbs(i * 0.1 + j * 0.001), 19) + A[19] * qPow((i * 0.1 + j * 0.001), 20));
                                  temp = qAbs(temp - temp2);
                                  temp = qSqrt(qPow(temp, 2) + qPow(0.01, 2));
                                  curvature_coefficient = temp / 0.01;
                                  if (isinf(curvature_coefficient))
                                      curvature_coefficient = 1;
                                  if(isnan(curvature_coefficient))
                                      curvature_coefficient = 1;

                                  if (curvature_compensate == 1)
                                      curvature_coefficient = 1;
                                  else if (curvature_compensate == 2)
                                      curvature_coefficient = 1 / curvature_coefficient;
                                  else
                                  { }

                                  if (i > (Dp / 2) / dist)
                                  curvature_coefficient = 1;
                                  if (tool_R == 1)
                                      F_store[i] = flat_v_1p[i] * curvature_coefficient;
                                  else if (tool_R == 5)

                                      F_store[i] = flat_v_5p[i] * curvature_coefficient;
                                   else if(tool_R==7)//垂直抛
                                      F_store[i] = flat_v_vertical[i] * curvature_coefficient;

                                  else
                                      F_store[i] = flat_v_3p[i] * curvature_coefficient;

                              }

                              for (int i = 0; i < a; i++)//F进给速度
                                        {

                                            if (i < a / 2)
                                            {
                                                F[i + 1] = F_store[a / 2 - i - 1];
                                                F[i + 1] = F[i + 1] * qAbs(X2[i + 1] - X2[i]) / (qSqrt(qPow(0.1, 2) + qPow(Z1[i + 1] - Z1[i], 2)));
                                               // if (i == 32)
                                               //     MessageBox.Show("");
                                            }
                                            else
                                            {
                                                F[i + 1] = F_store[i - a / 2];

                                                F[i + 1] = F[i + 1] * qAbs(X2[i + 1] - X2[i]) / (qSqrt(qPow(0.1, 2) + qPow(Z1[i + 1] - Z1[i], 2)));
                                            }

                                                //qAbs((X2[i + 1] - X2[i]) / T[i] * 60);
                                            if (F_flag == true)
                                                F[i + 1] = qAbs(X2[i + 1] - X2[i])/(dist / contan_F);


                                        }


                              //申请空间

//                              static double **b=new double* [c+1];

//                              for(int i=0;i<c+1;++i){
//                                  b[i]=new double[7];
//                              }

//                              double **b_null=new double* [c+1];

//                              for(int i=0;i<c+1;++i){
//                                  b_null[i]=new double[7];
//                              }

                              double ** b=0;
                              b=new double*[c+1];
                              for (int i = 0; i < c+1; i++)
                              {
                                  b[i] = new double[8];
                                  for (int j = 0; j < 7; j++)
                                  {
                                      b[i][j] =0;

                                  }
                              }

                              double ** b_null=0;
                             b_null=new double*[c+1];
                              for (int i = 0; i < c+1; i++)
                              {
                                  b_null[i] = new double[7];
                                  for (int j = 0; j < 7; j++)
                                  {
                                      b_null[i][j] =0;

                                  }
                              }



                              for (int i = 0; i < c + 1; i++)
                              {


                                  b[i][0] = -X2[i+d+a/2];//x移动坐标
                                  b[i][1] = -B[i + d + a / 2];//B轴角度

                                  b[i][2] = F[i + d + a / 2];//进给速度
                                  b[i][3] = Nc[i + d + a / 2];//C轴转速

                                  b[i][4] = X[i + d + a / 2];//X工件坐标
                                  b[i][5] = ZZ[i + d + a / 2];//Z轴移动坐标
                                  b[i][6] = Z1[i + d + a / 2];//函数曲线Z值

                                  b[i][7] = Y[i + d + a / 2];//Y值

                                //  qDebug()<<i<<"b[0]"<<b[i][0]<<"a"<<a;
                              //    qDebug()<<"b[4]"<<b[i][4]<<"d"<<d;
                              }
                              b[0][2] = first_positon_feed;

                              if (normal_flag == false)
                              {
                           //   QMessageBox::information(, "提示", "连接失败！");     // QMessageBox.Show("输入参数有误，数据异常，生成代码失败！");
                             //     return b_null;
                              }


                              return b;
}

bool interference_check()//干涉检查
{


}

double ** Produce_Gcode::Test2DArray(unsigned r, unsigned c){
    double ** arr2d;
    arr2d = new double*[r];
    for (int i = 0; i < r; i++)
    {
        arr2d[i] = new double[c];
        for (int j = 0; j < c; j++)
        {
            arr2d[i][j] = j + c*i;

        }
    }

    return arr2d;
}


