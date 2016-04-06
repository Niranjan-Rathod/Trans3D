#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
    Matrix();
    float x,y,z;
    Matrix rotation_matrix(float,float, float,int,int,int,float,float,float,float);

};

#endif // MATRIX_H
