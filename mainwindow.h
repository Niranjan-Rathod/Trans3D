#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <threed_point.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    void Draw_Axes();
    void Draw_Cube();
    void Draw_car();
    void Draw_sin();
    void Draw_cos();
    void Draw_tan();
    void Draw_Hyperboloid();
    void Draw_Cone();
    void Draw_Sphere();
    void Draw_polygon(ThreeD_point,ThreeD_point,ThreeD_point,ThreeD_point,QPainter *);
    void Draw_3d_line(float, float, float, float, float, float, QPainter *);
    void paintEvent(QPaintEvent *);
    void wheelEvent(QWheelEvent *);
    void mousePressEvent(QMouseEvent *);
    //void mouseDoubleClickEvent(QMouseEvent *);

    ~MainWindow();

private slots:


    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_3_valueChanged(int value);

    void on_draw_clicked();

    void on_animate_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
