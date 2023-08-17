#include "mainwindow.h"
#include "./ui_mainwindow.h"

QImage img(600,600,QImage::Format_RGBA8888);
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

void MainWindow::BresenhamsLine(int x1, int y1, int x2, int y2)
{
    int dx,dy,p;
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    p = 2*dy - dx;

    int x = x1;
    int y = y1;
    img.setPixel(x,y,qRgb(255,0,0));

    for(int i=0;i<dx;i++){
        if(p>=0){
            x++;
            y++;
            img.setPixel(x,y,qRgb(255,0,0));
            p = p + 2*(dy-dx);
        }
        else{
            x++;
            img.setPixel(x,y,qRgb(255,0,0));
            p = p + 2*dy;
        }
    }
}

void MainWindow::MidpointCircle(float h, float k, float r)
{
    float x,y,d;
    x = 0;
    y = r;
    d = 1 - r;

    while(x<=y){
        img.setPixel(x+h,y+k,qRgb(255,0,0));
        img.setPixel(-x+h,y+k,qRgb(255,0,0));
        img.setPixel(-x+h,-y+k,qRgb(255,0,0));
        img.setPixel(x+h,-y+k,qRgb(255,0,0));
        img.setPixel(y+h,x+k,qRgb(255,0,0));
        img.setPixel(y+h,-x+k,qRgb(255,0,0));
        img.setPixel(-y+h,-x+k,qRgb(255,0,0));
        img.setPixel(-y+h,x+k,qRgb(255,0,0));

        if(d<0.0f){
            d = d + 2*x + 3;
        }
        else{
            d = d + 2*(x-y) + 5;
            y--;
        }

        x++;
    }
}


void MainWindow::on_pushButton_clicked()
{
    BresenhamsLine(100,100,500,600);
    MidpointCircle(300,300,150);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

