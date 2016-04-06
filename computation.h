#ifndef COMPUTATION_H
#define COMPUTATION_H

class Computation
{

public:
    float real_x;
    float real_y;
    //int threed_x;
  //  int threed_y;
    //int threed_z;
    //QRgb intensity;
    Computation();
    void get_z_angle(int);
    void get_x_angle(int);
    void get_y_angle(int);
    void get_scaling_factor(float scale);
    void get_tx(float);
    void get_ty(float);
    void get_tz(float);
    void are_they_axes(int flag);
    Computation threeD_to_2d(float,float,float);
   // Computation get_3d_Coordinate(int, int, QImage &);
};



#endif // COMPUTATION_H
