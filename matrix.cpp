#include "matrix.h"
#define PI 3.14159265
#include<math.h>

Matrix::Matrix()
{
}

Matrix Matrix::rotation_matrix(float x, float y, float z, int Theta_degree, int x_angle, int y_angle, float scaling_Factor, float Tx, float Ty, float Tz)
{
    int i,j,k;
double thetaz=(Theta_degree*PI/180);
double thetax=(x_angle*PI/180);
double thetay=(y_angle*PI/180);
float a[3][3];
float b[3][1];
float c[3][1];

/*a[0][0]=cos(thetaz); a[0][1]=-sin(thetaz);    a[0][2]=0;
a[1][0]=sin(thetaz); a[1][1]=cos(thetaz);     a[1][2]=0;
a[2][0]=0;          a[2][1]=0;                a[2][2]=1;*/


a[0][0]=cos(thetaz)*cos(thetay); a[0][1]=(cos(thetax)*sin(thetaz))+(sin(thetax)*sin(thetay)*cos(thetaz));    a[0][2]=(sin(thetax)*sin(thetaz))-(cos(thetax)*sin(thetay)*cos(thetaz));
a[1][0]=-cos(thetay)*sin(thetaz); a[1][1]=(cos(thetax)*cos(thetaz))-(sin(thetax)*sin(thetay)*sin(thetaz));     a[1][2]=(sin(thetax)*cos(thetaz)+(cos(thetax)*sin(thetay)*sin(thetaz)));
a[2][0]=sin(thetay);          a[2][1]=-sin(thetax)*cos(thetay);                a[2][2]=cos(thetax)*cos(thetay);


b[0][0]=x;
b[1][0]=y;
b[2][0]=z;

for(i=0;i<3;i++)
{
    for(j=0;j<1;j++)
    {
        for(k=0;k<3;k++)
        {
            c[i][j]=c[i][j]+(a[i][k]*b[k][j]);
        }
    }
}


  float d[3][3];                        //Scaling Matrix
  float e[3][1];
  d[0][0]=scaling_Factor;               d[0][1]=0;                  d[0][2]=0;
  d[1][0]=0;                            d[1][1]=scaling_Factor;     d[1][2]=0;
  d[2][0]=0;                            d[2][1]=0;                  d[2][2]=scaling_Factor;

  for(i=0;i<3;i++)
  {
      for(j=0;j<1;j++)
      {
          for(k=0;k<3;k++)
          {
              e[i][j]=e[i][j]+(d[i][k]*c[k][j]);
          }
      }
  }
  /*float f[4][4];
  float g[3][1];

  f[0][0]=1;                          f[0][1]=0;              f[0][2]=0;         f[0][3]=0;
  f[1][0]=0;                          f[1][1]=1;              f[1][2]=0;         f[1][3]=0;
  f[2][0]=0;                          f[2][1]=0;              f[2][2]=1;         f[2][3]=0;
  f[3][0]= Tx;                        f[3][1]=Ty;             f[3][2]=Tz;        f[3][3]=1;


  for(i=0;i<4;i++)
  {
      for(j=0;j<1;j++)
      {
          for(k=0;k<4;k++)
          {
              g[i][j]=g[i][j]+(f[i][k]*e[k][j]);
          }
      }
  }*/

  Matrix point;
  point.x=e[0][0]+Tx;
  point.y=e[1][0]+Ty;
  point.z=e[2][0]+Tz;


  return point;




}
