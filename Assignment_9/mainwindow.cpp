#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QtMath>
using namespace std;

QImage img(600,600,QImage::Format_RGBA8888);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    img.fill(Qt::black);
    Axis(0,300,600,300);
    Axis(300,0,300,600);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Axis(int x1, int y1, int x2, int y2)
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

    xinc = dx/step;
    yinc = dy/step;

    float x = x1;
    float y = y1;

    for(int i=0;i<step;i++){
        img.setPixel(x,y,qRgb(255,255,255));
        x = x + xinc;
        y = y + yinc;
    }
}

void MainWindow::DDA(int x1, int y1, int x2, int y2,int r,int g,int b)
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

    xinc = dx/step;
    yinc = dy/step;

    float x = x1;
    float y = y1;

    for(int i=0;i<step;i++){
        img.setPixel(x+300,-y+300,qRgb(r,g,b));
        x = x + xinc;
        y = y + yinc;
    }
}

void MainWindow::on_pushButton_clicked()
{
    int x1,y1,length,width;
    x1 = ui->textEdit->toPlainText().toInt();
    y1 = ui->textEdit_2->toPlainText().toInt();
    length = ui->textEdit_3->toPlainText().toInt();
    width = ui->textEdit_4->toPlainText().toInt();

    int x2,y2,x3,y3,x4,y4;
    x2 = x1 + length;
    y2 = y1;
    x3 = x2;
    y3 = y1 + width;
    x4 = x1;
    y4 = y3;

    vertices[0] = x1;
    vertices[1] = y1;
    vertices[2] = x2;
    vertices[3] = y2;
    vertices[4] = x3;
    vertices[5] = y3;
    vertices[6] = x4;
    vertices[7] = y4;

    DDA(x1,y1,x2,y2,255,255,255);
    DDA(x2,y2,x3,y3,255,255,255);
    DDA(x3,y3,x4,y4,255,255,255);
    DDA(x1,y1,x4,y4,255,255,255);

    ui->label->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::on_pushButton_2_clicked()
{
    int tx = ui->textEdit_5->toPlainText().toInt();
    int ty = ui->textEdit_6->toPlainText().toInt();

    int x1 = vertices[0] + tx;
    int y1 = vertices[1] + ty;

    int x2 = vertices[2] + tx;
    int y2 = vertices[3] + ty;

    int x3 = vertices[4] + tx;
    int y3 = vertices[5] + ty;

    int x4 = vertices[6] + tx;
    int y4 = vertices[7] + ty;

    DDA(x1,y1,x2,y2,255,0,0);
    DDA(x2,y2,x3,y3,255,0,0);
    DDA(x3,y3,x4,y4,255,0,0);
    DDA(x1,y1,x4,y4,255,0,0);

    ui->label->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::on_pushButton_3_clicked()
{
    int x1 = vertices[0];
    int y1 = vertices[1];

    int x2 = vertices[2];
    int y2 = vertices[3];

    int x3 = vertices[4];
    int y3 = vertices[5];

    int x4 = vertices[6];
    int y4 = vertices[7];

    double angle_in_degrees = ui->textEdit_7->toPlainText().toDouble();
    double angle_in_radians = qDegreesToRadians(angle_in_degrees);

    int x1_ = x1*qCos(angle_in_radians) - y1*qSin(angle_in_radians);
    int y1_= x1*qSin(angle_in_radians) + y1*qCos(angle_in_radians);
    int x2_ = x2*qCos(angle_in_radians) - y2*qSin(angle_in_radians);
    int y2_= x2*qSin(angle_in_radians) + y2*qCos(angle_in_radians);
    int x3_ = x3*qCos(angle_in_radians) - y3*qSin(angle_in_radians);
    int y3_= x3*qSin(angle_in_radians) + y3*qCos(angle_in_radians);
    int x4_ = x4*qCos(angle_in_radians) - y4*qSin(angle_in_radians);
    int y4_= x4*qSin(angle_in_radians) + y4*qCos(angle_in_radians);

    DDA(x1_,y1_,x2_,y2_,0,255,0);
    DDA(x2_,y2_,x3_,y3_,0,255,0);
    DDA(x3_,y3_,x4_,y4_,0,255,0);
    DDA(x1_,y1_,x4_,y4_,0,255,0);

    ui->label->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::on_pushButton_4_clicked()
{
    float sx = ui->textEdit_8->toPlainText().toFloat();
    float sy = ui->textEdit_9->toPlainText().toFloat();

    int x1 = vertices[0] * sx;
    int y1 = vertices[1] * sy;

    int x2 = vertices[2] * sx;
    int y2 = vertices[3] * sy;

    int x3 = vertices[4] * sx;
    int y3 = vertices[5] * sy;

    int x4 = vertices[6] * sx;
    int y4 = vertices[7] * sy;

    DDA(x1,y1,x2,y2,0,0,255);
    DDA(x2,y2,x3,y3,0,0,255);
    DDA(x3,y3,x4,y4,0,0,255);
    DDA(x1,y1,x4,y4,0,0,255);

    ui->label->setPixmap(QPixmap::fromImage(img));
}

