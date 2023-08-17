#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtMath>
#include <cmath>
#include <iostream>
using namespace std;

QImage img(600,600,QImage::Format_RGBA8888);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    img.fill(Qt::black);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DDA(int x1,int y1,int x2,int y2)
{
    float dx,dy,step,xinc,yinc;
    dx = x2 - x1;
    dy = y2 - y1;
    if(abs(dy)>abs(dx)){
        step = abs(dy);
    }
    else{
        step = abs(dx);
    }

    float x =x1;
    float y = y1;

    xinc = dx/step;
    yinc = dy/step;

    for(int i=0;i<step;i++){
        img.setPixel(x,y,qRgb(255,0,0));
        x = x + xinc;
        y = y + yinc;
    }
}

void MainWindow::Rectangle(int x1,int y1,int l,int w)
{
    int x2,y2,x3,y3,x4,y4;
    x2 = x1 + l;
    y2 = y1;
    x3 = x2;
    y3 = y2 + w;
    x4 = x1;
    y4 = y3;

    DDA(x1,y1,x2,y2);
    DDA(x2,y2,x3,y3);
    DDA(x3,y3,x4,y4);
    DDA(x1,y1,x4,y4);
}

void MainWindow::InnerQuad(int x1,int y1,int l,int w)
{
    int m1,m1_,m2,m2_,m3,m3_,m4,m4_;
    m1 = x1 + l/2;
    m1_ = y1;
    m2 = x1 + l;
    m2_ = y1 + w/2;
    m3 = m1;
    m3_ = y1 + w;
    m4 = x1;
    m4_ = m2_;

    DDA(m1,m1_,m2,m2_);
    DDA(m2,m2_,m3,m3_);
    DDA(m3,m3_,m4,m4_);
    DDA(m1,m1_,m4,m4_);
}

void MainWindow::Bresenham(float h,float k,float r)
{
    float x,y,d;
    x = 0;
    y = r;
    d = 3 - 2*r;
    while(x<=y){
        img.setPixel(x+h,y+k,qRgb(255,0,0));
        img.setPixel(-x+h,y+k,qRgb(255,0,0));
        img.setPixel(x+h,-y+k,qRgb(255,0,0));
        img.setPixel(-x+h,-y+k,qRgb(255,0,0));
        img.setPixel(y+h,x+k,qRgb(255,0,0));
        img.setPixel(-y+h,x+k,qRgb(255,0,0));
        img.setPixel(-y+h,-x+k,qRgb(255,0,0));
        img.setPixel(y+h,-x+k,qRgb(255,0,0));

        if(d<0.0f){
            d = d + 4*x + 6;
        }
        else{
            d = d + 4*(x-y) + 10;
            y--;
        }
        x++;
    }
}

void MainWindow::Triangle(int h,int k,int r)
{
    double angle = 30*3.141/180;

    int x1 = h - r*cos(angle);
    int y1 = k + r*sin(angle);
    int x2 = h + r*cos(angle);
    int y2 = y1;
    int x3 = h;
    int y3 = k - r;

    DDA(x1,y1,x2,y2);
    DDA(x2,y2,x3,y3);
    DDA(x1,y1,x3,y3);
}


void MainWindow::on_pushButton_clicked()
{
    int x1,y1,length,width;
    x1 = ui->textEdit->toPlainText().toInt();
    y1 = ui->textEdit_2->toPlainText().toInt();
    length = ui->textEdit_3->toPlainText().toInt();
    width = ui->textEdit_4->toPlainText().toInt();

    float l = length/2;
    float w = width/2;

    float h = x1 + l;
    float k = y1 + w;
    float radius = (l*w)/sqrt(l*l + w*w);

    Rectangle(x1,y1,length,width);
    InnerQuad(x1,y1,length,width);
    Bresenham(h,k,radius);

    ui->label->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::on_pushButton_2_clicked()
{
    int h = ui->textEdit_5->toPlainText().toInt();
    int k = ui->textEdit_6->toPlainText().toInt();
    int outer_radius = ui->textEdit_7->toPlainText().toInt();

    int inner_radius = outer_radius/2;

    Triangle(h,k,outer_radius);
    Bresenham(h,k,outer_radius);
    Bresenham(h,k,inner_radius);

    ui->label->setPixmap(QPixmap::fromImage(img));
}

