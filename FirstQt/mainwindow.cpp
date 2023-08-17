#include "mainwindow.h"
#include "./ui_mainwindow.h"

QImage img(500,500,QImage::Format_RGBA8888);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

    xinc = dx/step;
    yinc = dy/step;

    float x = x1;
    float y = y1;
    for(int i=0;i<int(step);i++){
        img.setPixel(x,y,qRgb(255,0,0));
        x = x + xinc;
        y = y + yinc;
    }
}


void MainWindow::on_pushButton_clicked()
{
    DDA(10,10,400,400);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

