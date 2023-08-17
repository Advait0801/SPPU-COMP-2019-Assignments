#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>
#include <cmath>
#include <iostream>
using namespace std;

QImage img(600,600,QImage::Format_RGBA8888);
float COS_60 = 0.5 ;
float SIN_60 = 0.866 ;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    img.fill(Qt::black);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DDA(int x1, int y1, int x2, int y2)
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
        img.setPixel(x,y,qRgb(0,255,0));
        x = x + xinc;
        y = y + yinc;
    }
}

void MainWindow::delay( int time ) {
    QTime dieTime = QTime::currentTime().addMSecs( time ) ;
    while( QTime::currentTime() < dieTime ) {
        QCoreApplication::processEvents( QEventLoop::AllEvents , 100 ) ;
    }
}

void MainWindow::Kochcurve( int x1 , int y1 , int x2 , int y2 , int iterations ) {
    // Use section formula to find the coordinates of the point that divides line in ratio 2 : 1
    int x3 = ( 0.67 * x1 + 0.33 * x2 ) ;
    int y3 = ( 0.67 * y1 + 0.33 * y2 ) ;

    // Use section formula to find the coordinates of the point that divides line in ratio 1 : 2
    int x4 = ( 0.33 * x1 + 0.67 * x2 ) ;
    int y4 = ( 0.33 * y1 + 0.67 * y2 ) ;

    // Rotate 60 degrees about point ( x3 , y3 )
    int x = x3 + (x4 - x3) * COS_60 - ( y4 - y3 ) * SIN_60;
    int y = y3 + (x4 - x3) * SIN_60 + ( y4 - y3 ) * COS_60;

    if( iterations > 1 ) {
        Kochcurve( x1 , y1 , x3 , y3 , iterations - 1 ) ;
        Kochcurve( x3 , y3 , x , y , iterations - 1 ) ;
        Kochcurve( x , y , x4 , y4 , iterations - 1 ) ;
        Kochcurve( x4 , y4 , x2 , y2 , iterations - 1 ) ;
    }
    else {
        DDA( x1 , y1 , x3 , y3  ) ;
        DDA( x3 , y3 , x , y ) ;
        DDA( x , y , x4 , y4 ) ;
        DDA( x4 , y4 , x2 , y2 ) ;
    }
    delay(10);
}




void MainWindow::on_pushButton_clicked()
{
    int iterations = ui->textEdit->toPlainText().toInt();
    Kochcurve(100,200,300,500,iterations);
    Kochcurve(300,500,500,200,iterations);
    Kochcurve(500,200,100,200,iterations);

    ui->label->setPixmap(QPixmap::fromImage(img));
}

