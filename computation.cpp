#include "computation.h"
#include<math.h>
#include<mainwindow.h>
#include<matrix.h>

#define sqrt2 1.414213562
int anglex=0;
int angley=0;
int anglez=0;
float Tx,Ty,Tz;
float scaling_factor=1;
int axes_flag=0;

Computation::Computation()
{
}

void Computation::are_they_axes(int flag)
{
    axes_flag=flag;
}

void Computation::get_z_angle(int angle_from_ui)
{
anglez=angle_from_ui;
}
void Computation::get_x_angle(int angle_from_ui)
{
anglex=angle_from_ui;
}
void Computation::get_y_angle(int angle_from_ui)
{
angley=angle_from_ui;
}
void Computation::get_scaling_factor(float scale)
{
    scaling_factor=scaling_factor+scale;
}
void Computation::get_tx(float tx)
{
    Tx=Tx+tx;
}
void Computation::get_ty(float ty)
{
    Ty=Ty+ty;
}
void Computation::get_tz(float tz)
{
    Tz=Tz+tz;
}

Computation Computation::threeD_to_2d(float x1, float y1, float z1)
{   Matrix o;
    MainWindow ob;
    if(axes_flag==1)
    {
    Matrix roteted=o.rotation_matrix(x1,y1,z1,0,0,0,scaling_factor,0,0,0);
    Computation result;
    /*int x=roteted.x;
    int y=roteted.y;
    int z=roteted.z;*/
    //result.real_x=x-z/sqrt(2);
    //result.real_y=y-x/2-z/sqrt(2);
   result.real_x=(roteted.x-roteted.z/sqrt2)*10;
   result.real_y=(roteted.y-roteted.x/2-roteted.z/sqrt2)*10;
   /*result.real_x=roteted.x-roteted.z/sqrt2;
   result.real_y=roteted.y-roteted.z/sqrt2;*/
    return result;
    }
    else if(axes_flag==0)
    {
    Matrix roteted=o.rotation_matrix(x1,y1,z1,anglez,anglex,angley,scaling_factor,Tx,Ty,Tz);
    Computation result;
    /*int x=roteted.x;
    int y=roteted.y;
    int z=roteted.z;*/
    //result.real_x=x-z/sqrt(2);
    //result.real_y=y-x/2-z/sqrt(2);
   result.real_x=(roteted.x-roteted.z/sqrt2)*10;
   result.real_y=(roteted.y-roteted.x/2-roteted.z/sqrt2)*10;
   /*result.real_x=roteted.x-roteted.z/sqrt2;
   result.real_y=roteted.y-roteted.z/sqrt2;*/
    return result;
    }

}





