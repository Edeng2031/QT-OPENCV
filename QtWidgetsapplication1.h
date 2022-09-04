#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include<opencv2/opencv.hpp>
using namespace cv;//添加后才可以在private中添加Mat
class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = nullptr);
    ~QtWidgetsApplication1();
private slots:
    
   void on_button();
   void on_blur();
   void on_flip();
   void on_sharpen();
   void on_hsv();
private:
    Ui::QtWidgetsApplication1Class ui;
    Mat img;
   
};
