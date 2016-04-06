#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<computation.h>
#include<QLabel>
#include<math.h>
#include<QPainterPath>
//#include<unistd.h>
#include<QThread>
#include<QWheelEvent>
#include<QRectF>
#include<QBrush>
#include<point3d.h>

int flagx=0;
int flagy=0;
int flagz=0;

int sphere_drawn=0;
int Hyperboloid_drawn=0;
int Cone_drawn=0;
int spoint_count=0;
int hpoint_count=0;
int cpoint_count=0;
float compare=10000,compare_1=10000,compare_2=10000,smallest=10001,smaller=10002,small=10003;
float equation_buffer[1000][6];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this); 
    update();
    ui->animate->hide();
    ui->textBrowser->setText("If you can't see axes plotted on left side .Try running program again. It Sometimes take 3 or 4 times to run the program  Rebuild and run it.");
    ui->TF->setText("1");
    connect(ui->draw,SIGNAL(clicked()),this,SLOT(on_draw_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::wheelEvent(QWheelEvent *event)
{   Computation obj;

    int scale=scale+(event->delta()/120);
     obj.get_scaling_factor(scale);
      event->accept();
      update();
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x=event->x();
    int y=event->y();

    int sf=0.5;
    if(ui->TF->text().isEmpty())
    {
        sf=0.5;
    }
    else
    {
        sf=ui->TF->text().toInt();
    }
    Computation obj;
    if(x<267&&y<267)
    {
    obj.get_tx(-sf);
    obj.get_tz(-sf);
    }
    else if((267<x&&x<533)&&y<267)
    {
    obj.get_ty(sf);
    }
    else if((x>533&&x<780)&&y<267)
    {
    obj.get_tx(sf);
    obj.get_tz(-sf);
    }
    else if(x<267&&(267<y&&y<533))
    {
    obj.get_tx(-sf);
    }
    else if((267<x&&x<533)&&(267<y&&y<533))
    {

    }
    else if((x>533&&x<780)&&(267<y&&y<533))
    {
    obj.get_tx(sf);
    }
    else if(y>533&&x<267)
    {
    obj.get_tx(sf);
    obj.get_tz(sf);
    }
    else if(y>533&&(267<x&&x<533))
    {
    obj.get_ty(-sf);
    }
    else if(y>533&&x>533&&x<780)
    {
        obj.get_tx(sf);
        obj.get_tz(sf);
    }
    update();

}

void MainWindow::paintEvent(QPaintEvent *)
{
    Computation axes;
    axes.are_they_axes(1);
        Draw_Axes();
    axes.are_they_axes(0);
    QString shape=ui->comboBox->currentText();
    QString cube="Cube";
    QString Car="car";
    QString sin="Sine Curve";
    QString cos="Cos Curve";
    QString tan="Tan Curve";
    QString Hyperboloid="Z^2=X^2+Y^2";
    QString Cone="Z^2=X^2-Y^2";
    QString Sphere="Sphere Equation";

    if(shape==cube)
    {
       Draw_Cube();
    }
    else if(shape==Car)
    {
        Draw_car();
    }
    else if(shape==sin)
    {
        Draw_sin();
    }
    else if(shape==cos)
    {
        Draw_cos();
    }
    else if(shape==tan)
    {
        Draw_tan();
    }
    else if (shape==Hyperboloid)
    {
        Draw_Hyperboloid();
    }
    else if (shape==Cone)
    {
        Draw_Cone();
    }
    else if (shape==Sphere)
    {
        Draw_Sphere();
    }
}



void MainWindow::Draw_Sphere()
{
    QPainter sphere(this);
           QPen pen(Qt::red, 1, Qt::SolidLine);
           sphere.setBrush(Qt::red);
           sphere.setPen(pen);
            float x=0;
              float y=0;


             if(sphere_drawn==0)
             {
               for( x=-8;x<8;x=x+0.8)
               {
               for(y=-8;y<8;y=y+0.8)
               {
                   float equ=sqrt(5*5-x*x-y*y);

                   if(equ>=0)
                   {

                   float z=equ;

               equation_buffer[spoint_count][0]=x;
               equation_buffer[spoint_count][1]=y;
               equation_buffer[spoint_count][2]=z;
               spoint_count++;
               equation_buffer[spoint_count][0]=x;
               equation_buffer[spoint_count][1]=y;
               equation_buffer[spoint_count][2]=-z;
               spoint_count++;
                   }
               }

               }






               int p,q;
               float distance;
               for(p=0;p<=spoint_count;p++)
               {
                   for(q=0;q<=spoint_count;q++)
                   {   if(p!=q)
                       {   ui->length->setText(QString::number(equation_buffer[q][0]));
                           ui->bredth->setText(QString::number(equation_buffer[q][1]));

                    distance=(((equation_buffer[p][0]-equation_buffer[q][0])*(equation_buffer[p][0]-equation_buffer[q][0]))
                            +((equation_buffer[p][1]-equation_buffer[q][1])*(equation_buffer[p][1]-equation_buffer[q][1]))
                            +((equation_buffer[p][2]-equation_buffer[q][2])*(equation_buffer[p][2]-equation_buffer[q][2])));
                    float dis=sqrt(distance);

                    ui->hight->setText(QString::number(compare));
                    if(dis<=compare)
                    {

                    small=smaller;
                    smaller=smallest;
                    smallest=q;
                    compare=dis;
                    }
                    else if(dis<=compare_1)
                    {   small=smaller;
                        smaller=q;
                        compare_1=dis;
                    }
                    else if(dis<=compare_2)
                    {
                        small=q;
                        compare_2=dis;
                    }

                   }

                   else
                   {
                       continue;
                   }
                   }
                   equation_buffer[p][3]=smallest;
                   equation_buffer[p][4]=smaller;
                   equation_buffer[p][5]=small;
                   ui->length->setText(QString::number(smallest));
                   ui->bredth->setText(QString::number(smaller));
                   ui->hight->setText(QString::number(small));
                   smallest=1000,compare=compare_1=compare_2=smaller=small=1000;
               }

             sphere_drawn=1;
             }



               int z=0;
               for(z=0;z<=spoint_count;z++)
               {

              Computation ob;
               Computation point=ob.threeD_to_2d(equation_buffer[z][0],equation_buffer[z][1],equation_buffer[z][2]);
               int index1=equation_buffer[z][3];
               int index2=equation_buffer[z][4];
               int index3=equation_buffer[z][5];
               ui->length->setText(QString::number(index1));
               ui->bredth->setText(QString::number(index2));
               ui->hight->setText(QString::number(index3));
              Computation point1=ob.threeD_to_2d(equation_buffer[index1][0],equation_buffer[index1][1],equation_buffer[index1][2]);

               Computation point2=ob.threeD_to_2d(equation_buffer[index2][0],equation_buffer[index2][1],equation_buffer[index2][2]);
               Computation point3=ob.threeD_to_2d(equation_buffer[index3][0],equation_buffer[index3][1],equation_buffer[index3][2]);

               const QPointF points[4] = {
                QPointF(400+point.real_x,400-point.real_y),
                QPointF(400+point1.real_x,400-point1.real_y),
                QPointF(400+point2.real_x,400-point2.real_y),
                QPointF(400+point3.real_x,400-point3.real_y)
                           };
               sphere.setOpacity(0.5);
               sphere.drawPolygon(points, 4,Qt::OddEvenFill);



             }
               update();

}

void MainWindow::Draw_Cone()
{
    QPainter sphere(this);
           QPen pen(Qt::red, 1, Qt::SolidLine);
           sphere.setBrush(Qt::red);
           sphere.setPen(pen);
            float x=0;
              float y=0;


             if(Cone_drawn==0)
             {
               for( x=-8;x<8;x=x+0.8)
               {
               for(y=-8;y<8;y=y+0.8)
               {

                   float equ=sqrt((x*x)-(y*y));
                   if(equ>=0)
                   {

                   float z=equ;

               equation_buffer[cpoint_count][0]=x;
               equation_buffer[cpoint_count][1]=y;
               equation_buffer[cpoint_count][2]=z;
               cpoint_count++;
               equation_buffer[cpoint_count][0]=x;
               equation_buffer[cpoint_count][1]=y;
               equation_buffer[cpoint_count][2]=-z;
               cpoint_count++;
                   }
               }

               }






               int p,q;
               float distance;
               for(p=0;p<=cpoint_count;p++)
               {
                   for(q=0;q<=cpoint_count;q++)
                   {   if(p!=q)
                       {   ui->length->setText(QString::number(equation_buffer[q][0]));
                           ui->bredth->setText(QString::number(equation_buffer[q][1]));

                    distance=(((equation_buffer[p][0]-equation_buffer[q][0])*(equation_buffer[p][0]-equation_buffer[q][0]))
                            +((equation_buffer[p][1]-equation_buffer[q][1])*(equation_buffer[p][1]-equation_buffer[q][1]))
                            +((equation_buffer[p][2]-equation_buffer[q][2])*(equation_buffer[p][2]-equation_buffer[q][2])));
                    float dis=sqrt(distance);

                    ui->hight->setText(QString::number(compare));
                    if(dis<=compare)
                    {

                    small=smaller;
                    smaller=smallest;
                    smallest=q;
                    compare=dis;
                    }
                    else if(dis<=compare_1)
                    {   small=smaller;
                        smaller=q;
                        compare_1=dis;
                    }
                    else if(dis<=compare_2)
                    {
                        small=q;
                        compare_2=dis;
                    }

                   }

                   else
                   {
                       continue;
                   }
                   }
                   equation_buffer[p][3]=smallest;
                   equation_buffer[p][4]=smaller;
                   equation_buffer[p][5]=small;
                   ui->length->setText(QString::number(smallest));
                   ui->bredth->setText(QString::number(smaller));
                   ui->hight->setText(QString::number(small));
                   smallest=1000,compare=compare_1=compare_2=smaller=small=1000;
               }

             Cone_drawn=1;
             }



               int z=0;
               for(z=0;z<=cpoint_count;z++)
               {

              Computation ob;
               Computation point=ob.threeD_to_2d(equation_buffer[z][0],equation_buffer[z][1],equation_buffer[z][2]);
               int index1=equation_buffer[z][3];
               int index2=equation_buffer[z][4];
               int index3=equation_buffer[z][5];
               ui->length->setText(QString::number(index1));
               ui->bredth->setText(QString::number(index2));
               ui->hight->setText(QString::number(index3));
              Computation point1=ob.threeD_to_2d(equation_buffer[index1][0],equation_buffer[index1][1],equation_buffer[index1][2]);

               Computation point2=ob.threeD_to_2d(equation_buffer[index2][0],equation_buffer[index2][1],equation_buffer[index2][2]);
               Computation point3=ob.threeD_to_2d(equation_buffer[index3][0],equation_buffer[index3][1],equation_buffer[index3][2]);

               const QPointF points[4] = {
                QPointF(400+point.real_x,400-point.real_y),
                QPointF(400+point1.real_x,400-point1.real_y),
                QPointF(400+point2.real_x,400-point2.real_y),
                QPointF(400+point3.real_x,400-point3.real_y)
                           };
               sphere.setOpacity(0.5);
               sphere.drawPolygon(points, 4,Qt::OddEvenFill);



             }
               update();

}

void MainWindow::Draw_Hyperboloid()
{
    QPainter sphere(this);
           QPen pen(Qt::red, 1, Qt::SolidLine);
           sphere.setBrush(Qt::red);
           sphere.setPen(pen);
            float x=0;
              float y=0;


             if(Hyperboloid_drawn==0)
             {
               for( x=-8;x<8;x=x+1)
               {
               for(y=-8;y<8;y=y+1)
               {
                   //float equ=sqrt(5*5-x*x-y*y);
                   float equ=sqrt((x*x)+(y*y));
                   if(equ>=0)
                   {

                   float z=equ;

               equation_buffer[hpoint_count][0]=x;
               equation_buffer[hpoint_count][1]=y;
               equation_buffer[hpoint_count][2]=z;
               hpoint_count++;
               equation_buffer[hpoint_count][0]=x;
               equation_buffer[hpoint_count][1]=y;
               equation_buffer[hpoint_count][2]=-z;
               hpoint_count++;
                   }
               }

               }






               int p,q;
               float distance;
               for(p=0;p<=hpoint_count;p++)
               {
                   for(q=0;q<=hpoint_count;q++)
                   {   if(p!=q)
                       {   ui->length->setText(QString::number(equation_buffer[q][0]));
                           ui->bredth->setText(QString::number(equation_buffer[q][1]));

                    distance=(((equation_buffer[p][0]-equation_buffer[q][0])*(equation_buffer[p][0]-equation_buffer[q][0]))
                            +((equation_buffer[p][1]-equation_buffer[q][1])*(equation_buffer[p][1]-equation_buffer[q][1]))
                            +((equation_buffer[p][2]-equation_buffer[q][2])*(equation_buffer[p][2]-equation_buffer[q][2])));
                    float dis=sqrt(distance);

                    ui->hight->setText(QString::number(compare));
                    if(dis<=compare)
                    {

                    small=smaller;
                    smaller=smallest;
                    smallest=q;
                    compare=dis;
                    }
                    else if(dis<=compare_1)
                    {   small=smaller;
                        smaller=q;
                        compare_1=dis;
                    }
                    else if(dis<=compare_2)
                    {
                        small=q;
                        compare_2=dis;
                    }

                   }

                   else
                   {
                       continue;
                   }
                   }
                   equation_buffer[p][3]=smallest;
                   equation_buffer[p][4]=smaller;
                   equation_buffer[p][5]=small;
                   ui->length->setText(QString::number(smallest));
                   ui->bredth->setText(QString::number(smaller));
                   ui->hight->setText(QString::number(small));
                   smallest=1000,compare=compare_1=compare_2=smaller=small=1000;
               }

             Hyperboloid_drawn=1;
             }



               int z=0;
               for(z=0;z<=hpoint_count;z++)
               {

              Computation ob;
               Computation point=ob.threeD_to_2d(equation_buffer[z][0],equation_buffer[z][1],equation_buffer[z][2]);
               int index1=equation_buffer[z][3];
               int index2=equation_buffer[z][4];
               int index3=equation_buffer[z][5];
               ui->length->setText(QString::number(index1));
               ui->bredth->setText(QString::number(index2));
               ui->hight->setText(QString::number(index3));
              Computation point1=ob.threeD_to_2d(equation_buffer[index1][0],equation_buffer[index1][1],equation_buffer[index1][2]);

               Computation point2=ob.threeD_to_2d(equation_buffer[index2][0],equation_buffer[index2][1],equation_buffer[index2][2]);
               Computation point3=ob.threeD_to_2d(equation_buffer[index3][0],equation_buffer[index3][1],equation_buffer[index3][2]);

               const QPointF points[4] = {
                QPointF(400+point.real_x,400-point.real_y),
                QPointF(400+point1.real_x,400-point1.real_y),
                QPointF(400+point2.real_x,400-point2.real_y),
                QPointF(400+point3.real_x,400-point3.real_y)
                           };
               sphere.setOpacity(0.5);
               sphere.drawPolygon(points, 4,Qt::OddEvenFill);



             }
               update();


}


















void MainWindow::Draw_sin()

{
    QPainter sine(this);
            QPen pen(Qt::red, 2, Qt::SolidLine);
            sine.setPen(pen);
                int x=0;
                 float y=0;
                for( x=-360;x<=360;x=x+8)
                {    float angle=(x*3.14)/180;
                     y= sin(angle);
                     Computation ob;
                     Computation point=ob.threeD_to_2d(angle,y,0);

                     sine.drawPoint(400+point.real_x,400-point.real_y);
                }
update();


}
void MainWindow::Draw_cos()
{
    QPainter sine(this);
            QPen pen(Qt::red, 2, Qt::SolidLine);
            sine.setPen(pen);
                int x=0;
                 float y=0;
                for( x=-360;x<=360;x=x+8)
                {    float angle=(x*3.14)/180;
                     y= cos(angle);
                     Computation ob;
                     Computation point=ob.threeD_to_2d(angle,y,0);

                     sine.drawPoint(400+point.real_x,400-point.real_y);
                }
              update();


}
void MainWindow::Draw_tan()
{
    QPainter sine(this);
            QPen pen(Qt::red, 2, Qt::SolidLine);
            sine.setPen(pen);
                int x=0;
                 float y=0;
                for( x=-360;x<=360;x=x+4)
                {    float angle=(x*3.14)/180;
                     y= tan(angle);
                     Computation ob;
                     Computation point=ob.threeD_to_2d(angle,y,0);

                     sine.drawPoint(400+point.real_x,400-point.real_y);
                }

            update();


}



void MainWindow::Draw_car()
{   ui->animate->setVisible(true);
    QPainter car(this);
    QPen pen(Qt::red, 2, Qt::SolidLine);
    car.setPen(pen);
    car.setBrush(QBrush(Qt::red));
    ThreeD_point p1(5,5,10),p2(5,5,-10),p3(-5,5,-10),
            p4(-5,5,10),p5(-6,0,11),p6(6,0,11),p7(-6,-0.5,16),
            p8(6,-0.5,16),p9(6,-2.5,16),p10(-6,-2.5,16),
            p11(-6,0,-11),p12(6,0,-11),p13(6,-0.5,-16),
            p14(-6,-0.5,-16),p15(6,-2.5,-16),p16(-6,-2.5,-16),
            p17(6,-2.5,11),p18(6,-2.5,-11),p19(-6,-2.5,11),p20(-6,-2.5,-11);
    car.setOpacity(1);
    car.setBrush(QBrush(Qt::red));
    car.setOpacity(0.7);
    car.setOpacity(0.5);
    car.setBrush(QBrush(Qt::black));
    Draw_polygon(p15,p16,p10,p9,&car);
    car.setOpacity(0.5);
    car.setBrush(QBrush(Qt::black));
    Draw_polygon(p15,p16,p14,p13,&car);
    car.setBrush(QBrush(Qt::red));
    car.setOpacity(0.7);
    car.setBrush(QBrush(Qt::red));
    Draw_polygon(p17,p9,p8,p6,&car);
    Draw_polygon(p17,p6,p12,p18,&car);
    Draw_polygon(p11,p20,p19,p5,&car);
    Draw_polygon(p19,p5,p7,p10,&car);
    Draw_polygon(p20,p16,p14,p11,&car);
    Draw_polygon(p15,p18,p12,p13,&car);
    car.setBrush(QBrush(Qt::gray));
    car.setOpacity(0.5);
    Draw_polygon(p4,p5,p6,p1,&car);
    car.setOpacity(1);
    car.setBrush(QBrush(Qt::red));
    car.setBrush(QBrush(Qt::blue));
    car.setOpacity(1);
    Draw_polygon(p6,p8,p7,p5,&car);//no
    car.setOpacity(1);
    car.setBrush(QBrush(Qt::red));
    car.setOpacity(0.5);
    car.setBrush(QBrush(Qt::black));
    Draw_polygon(p7,p10,p9,p8,&car);    //no
    car.setOpacity(1);
    car.setBrush(QBrush(Qt::red));
    car.setBrush(QBrush(Qt::gray));
    car.setOpacity(0.5);
    Draw_polygon(p12,p11,p3,p2,&car);
    Draw_polygon(p2,p12,p6,p1,&car);
    Draw_polygon(p3,p11,p5,p4,&car);
    car.setOpacity(1);
    car.setBrush(QBrush(Qt::red));
    car.setOpacity(1);
    car.setBrush(QBrush(Qt::blue));
    Draw_polygon(p11,p14,p13,p12,&car);
    car.setOpacity(1);
    car.setBrush(QBrush(Qt::red));
    car.setOpacity(0.5);
    car.setBrush(QBrush(Qt::gray));
    Draw_polygon(p4,p5,p11,p3,&car);
    Draw_polygon(p6,p12,p2,p1,&car);
    car.setBrush(QBrush(Qt::green));
    car.setOpacity(1);
    Draw_polygon(p1,p2,p3,p4,&car);
    update();


}

void MainWindow::Draw_Axes()
{   QPainter axes(this);
    QPen pen(Qt::red, 2, Qt::SolidLine);

    axes.setPen(pen);
    flagz=1;
    Draw_3d_line(0,0,-30,0,0,30,&axes);
    flagz=0;
    flagy=1;
    pen.setColor(Qt::green);
    axes.setPen(pen);
    Draw_3d_line(0,30,0,0,-30,0,&axes);
    flagy=0;
    flagx=1;
    pen.setColor(Qt::blue);
    axes.setPen(pen);
    Draw_3d_line(30,0,0,-30,0,0,&axes);
    flagx=0;

}

void MainWindow::Draw_polygon(ThreeD_point point1, ThreeD_point point2 , ThreeD_point point3, ThreeD_point point4, QPainter *painter)
{   Computation obj;
    Computation point11=obj.threeD_to_2d(point1.x,point1.y,point1.z);
    Computation point21=obj.threeD_to_2d(point2.x,point2.y,point2.z);
    Computation point31=obj.threeD_to_2d(point3.x,point3.y,point3.z);
    Computation point41=obj.threeD_to_2d(point4.x,point4.y,point4.z);
    int point1_x=point11.real_x;
    int point1_y=point11.real_y;
    int point2_x=point21.real_x;
    int point2_y=point21.real_y;
    int point3_x=point31.real_x;
    int point3_y=point31.real_y;
    int point4_x=point41.real_x;
    int point4_y=point41.real_y;
    const QPointF points[4] = {
        QPointF(400+point1_x,400-point1_y),
        QPointF(400+point2_x,400-point2_y),
        QPointF(400+point3_x,400-point3_y),
        QPointF(400+point4_x,400-point4_y)
    };


    painter->drawPolygon(points, 4,Qt::OddEvenFill);
   }


void MainWindow::Draw_Cube()
{
    QPainter cube(this);
    QPen pen(Qt::red, 2, Qt::SolidLine);
    cube.setOpacity(0.5);
    cube.setBrush(QBrush(Qt::red));
float length=ui->length->text().toFloat();
float bredth=ui->bredth->text().toFloat();
float hight=ui->hight->text().toFloat();
ThreeD_point p1(0,0,0),p2(length,0,0),p3(length,hight,0),p4(0,hight,0),p5(0,hight,bredth),p6(length,hight,bredth),p7(length,0,bredth),p8(0,0,bredth);
Draw_polygon(p1,p2,p3,p4,&cube);
Draw_polygon(p3,p4,p5,p6,&cube);
Draw_polygon(p2,p3,p6,p7,&cube);
Draw_polygon(p5,p6,p7,p8,&cube);
Draw_polygon(p1,p4,p5,p8,&cube);
Draw_polygon(p1,p2,p7,p8,&cube);



}


void MainWindow::Draw_3d_line(float x11, float y11 , float z11, float x22, float y22 , float z22, QPainter *painter)
{        int hight=800,width=800;
         int origin_x=hight/2;
         int origin_y=width/2;
        Computation obj;
        Computation point1=obj.threeD_to_2d(x11,y11,z11);
        Computation point2=obj.threeD_to_2d(x22,y22,z22);
                int x1=origin_x+point1.real_x;
                int y1=origin_y-point1.real_y;
                int x2=origin_x+point2.real_x;
                int y2=origin_y-point2.real_y;
                     if(flagx==1)
                     {
                     painter->setFont(QFont("Arial", 20));
                        painter->drawText(x2,y2,"x");
                     }
                     else if(flagy==1)
                     {
                         painter->setFont(QFont("Arial", 20));
                            painter->drawText(x2,y2,"y");
                     }
                     else if(flagz==1)
                     {
                         painter->setFont(QFont("Arial", 20));
                            painter->drawText(x2,y2,"z");
                     }

        painter->drawLine(x1,y1,x2,y2);


}




void MainWindow::on_horizontalSlider_valueChanged(int value)
{   int newvalue=value*8-360;
    Computation o;
    o.get_z_angle(newvalue);

    update();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    int newvalue=value*8-360;
    Computation b;
    b.get_x_angle(newvalue);

    update();

}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    int newvalue=value*8-360;
    Computation j;
    j.get_y_angle(newvalue);

    update();
}





void MainWindow::on_draw_clicked()
{   ui->textBrowser->setText("Double click in blank Space to translate object in various directions.");
    Draw_Cube();
      ui->Displayy->clear();
       update();

       return;
}

void MainWindow::on_animate_clicked()
{   Computation obj;
    Draw_car();
    update();
    for(int i=0;i<90;i=i+4)
    {
       obj.get_y_angle(i);
       repaint();
}

    for(int j=0;j<8;j++)
    {
       obj.get_tx(-2);
       repaint();

    }
    for(int j=0;j<8;j++)
    {
       obj.get_tx(2);
       repaint();

    }


}
