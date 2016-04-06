#ifndef POINT3D_H
#define POINT3D_H

class point3d
{


public:
    float x,y,z;
    point3d();
    bool operator<(const point3d &second)
    const {
            return ( x<=second.x );
        }
};

#endif // POINT3D_H
