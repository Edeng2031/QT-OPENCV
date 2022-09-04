#include "QtWidgetsApplication1.h"
#include <qmessagebox.h>
#include <opencv2\opencv.hpp>
#include <random>
#include <QFileDialog>
//随机数生成器
std::default_random_engine generator;
std::uniform_int_distribution<int>
blur_num(3, 30);//随即模糊的随机数
std::uniform_int_distribution<int>
flip_num(-1, 1);//随机翻转的随机数
using namespace cv;
using namespace std;
//Mat类型图片QImage类型图片转换函数
QImage Mat2QImage(cv::Mat& image);

QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //连接信号和按钮
    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(on_button()));
    connect(ui.blur_button, SIGNAL(clicked()), this, SLOT(on_blur()));
    connect(ui.flip_button, SIGNAL(clicked()), this, SLOT(on_flip()));
    connect(ui.sharpen_button, SIGNAL(clicked()), this, SLOT(on_sharpen()));
    connect(ui.hsv_button, SIGNAL(clicked()), this, SLOT(on_hsv()));
    
}

QtWidgetsApplication1::~QtWidgetsApplication1()
{}
//打开图片函数
void QtWidgetsApplication1::on_button() {
    //得到文件名,打开目录，可以打开图片的格式
    QString file_name = QFileDialog::getOpenFileName(this, tr("open image"), "C:\\Users\\25248\\Desktop\\images", tr("images(*.png *.jpg)"));
     
    //判断打开的图片是否为空
    if (file_name.isEmpty())
    {
        return;
    }
    ui.line->setText(file_name);
    //toLatinl().data()将getFileNmae得到的Qstring类型转换为imread能读取的类型(char*)
     img = imread(file_name.toLatin1().data());
     Mat src = img.clone();//定义副本，对副本进行转换
    //匹配图片与label的大小
    QSize label_size = ui.label->size();
    int row = label_size.height();
    int col = label_size.width();
    cv::resize(src, src, Size(col, row), 0, 0);
    
    QImage dst = Mat2QImage(src);//对副本转换后src会变成RGB类型  
    ui.label->setPixmap(QPixmap::fromImage(dst));

   
}
//随机模糊函数
void QtWidgetsApplication1::on_blur() {
    ui.label_2->clear();
    
    Mat blur_src = img;
    Mat blur_dst;
    
  
    int r = blur_num(generator);
    r = 2 * r + 1;
    GaussianBlur(blur_src, blur_dst, Size(r, r), 0, 0);
    QSize label_2_size = ui.label_2->size();
    int row = label_2_size.height();
    int col = label_2_size.width();
    cv::resize(blur_dst, blur_dst, Size(col, row), 0, 0);
    QImage Qblur = Mat2QImage(blur_dst);
    ui.label_2->setPixmap(QPixmap::fromImage(Qblur));   
}
void QtWidgetsApplication1::on_flip() {
    ui.label_2->clear();
    Mat flip_src = img;
    Mat flip_dst;
    int k = flip_num(generator);
    flip(flip_src, flip_dst, k);
  
    QSize label_2_size = ui.label_2->size();
    int r = label_2_size.height();
    int c = label_2_size.width();
    cv::resize(flip_dst, flip_dst, Size(c, r), 0, 0);
    
    QImage Qflip = Mat2QImage(flip_dst);
   
    ui.label_2->setPixmap(QPixmap::fromImage(Qflip));
}

void QtWidgetsApplication1::on_sharpen() {
    ui.label_2->clear();
    Mat sharpen_src = img;
    Mat sharpen_dst;
    Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    filter2D(sharpen_src, sharpen_dst, -1, kernel, Point(-1, -1));
   
   
    //使图片大小与label_2大小匹配
    QSize label_2_size = ui.label_2->size();
    int row = label_2_size.height();
    int col = label_2_size.width();
    cv::resize(sharpen_dst, sharpen_dst,Size(col,row), 0, 0);
   
    QImage Qsharpen = Mat2QImage(sharpen_dst);
    //将图片放入label_2
   ui.label_2->setPixmap(QPixmap::fromImage(Qsharpen));
   
}
//转换为HSV
void QtWidgetsApplication1::on_hsv() {
    Mat hsv_src = img;
    Mat hsv_dst;
    cvtColor(hsv_src, hsv_dst, COLOR_BGR2HSV);
    QImage Qhsv = Mat2QImage(hsv_dst);
   
  //  ui.label_2->setPixmap(QPixmap::fromImage(Qhsv.scaled(ui.label_2->size(), Qt::KeepAspectRatio)));
    ui.label_2->setPixmap(QPixmap::fromImage(Qhsv.scaled(ui.label_2->size())));
}

static QImage Mat2QImage(cv::Mat& image)
{
  QImage Qimg;

    if (image.channels() == 3) {
        cvtColor(image, image, COLOR_BGR2RGB);
        Qimg = QImage((const unsigned char*)(image.data), image.cols, image.rows,
            image.cols * image.channels(), QImage::Format_RGB888);
    }
    else if (image.channels() == 1) {
        Qimg = QImage((const unsigned char*)(image.data), image.cols, image.rows,
            image.cols * image.channels(), QImage::Format_ARGB32);
    }
    else {
        Qimg = QImage((const unsigned char*)(image.data), image.cols, image.rows,
            image.cols * image.channels(), QImage::Format_RGB888);
    }

    return Qimg;
   
}


