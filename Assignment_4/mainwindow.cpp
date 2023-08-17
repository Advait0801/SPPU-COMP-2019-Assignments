#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMouseEvent>
#include <iostream>
using namespace std;

QImage img(600,600,QImage::Format_RGBA8888);
float xvertices[20];
float yvertices[20];
float slopes[20];
int vertexindex = 0;
int numvertices = 0;

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
        img.setPixel(x,y,qRgb(r,g,b));
        x = x + xinc;
        y = y + yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int r = 0;
    int g = 255;
    int b= 0;

    int x = event -> pos().x();
    int y = event -> pos().y();

    if(x>600 || y>600){
        return;
    }

    if(event -> button() == Qt::RightButton){
        xvertices[vertexindex] = xvertices[0];
        yvertices[vertexindex] = yvertices[0];

        int x1 = xvertices[0];
        int y1 = yvertices[0];
        int x2 = xvertices[vertexindex-1];
        int y2 = yvertices[vertexindex-1];

        DDA(x1,y1,x2,y2,r,g,b);

        numvertices = vertexindex;
    }

    else{
        xvertices[vertexindex] = x;
        yvertices[vertexindex] = y;

        if(numvertices>0){
            int x1 = x;
            int y1 = y;
            int x2 = xvertices[vertexindex-1];
            int y2 = yvertices[vertexindex-1];

            DDA(x1,y1,x2,y2,r,g,b);
        }

        numvertices++;
        vertexindex++;
    }
}


void MainWindow::on_pushButton_clicked()
{
    float ymin = 1000.0f;
    for(float y:yvertices){
        if(y<ymin){
            ymin = y;
        }
    }

    float ymax = 0.0f;
    for(float y:yvertices){
        if(y>ymax){
            ymax = y;
        }
    }

    for(int i=0;i<numvertices;i++){
        float dx = xvertices[i+1] - xvertices[i];
        float dy = yvertices[i+1] - yvertices[i];

        if(dx==0.0f){
            slopes[i] = 1.0f;
        }
        else{
            slopes[i] = dy/dx;
        }
    }

    for(int y=ymin;y<ymax;y++){
        float xintersection[numvertices];
        int numactiveedges = 0;
        for(int i=0;i<numvertices;i++){
            float yminline = std::min(yvertices[i],yvertices[i+1]);
            float ymaxline = std::max(yvertices[i],yvertices[i+1]);

            if(y>yminline && y<=ymaxline){
                float x1 = xvertices[i];
                float m = slopes[i];
                float y1 = yvertices[i];

                xintersection[numactiveedges] = x1 + (y-y1)/m;
                numactiveedges++;
            }

        }

        for(int i=0;i<numactiveedges;i++){
            for(int j=0;j<numactiveedges - i -1;j++){
                if(xintersection[j] > xintersection[j+1]){
                    float temp = xintersection[j];
                    xintersection[j] = xintersection[j+1];
                    xintersection[j+1] = temp;
                }
            }
        }

        for(int i=0;i<numactiveedges;i += 2){
            int x1 = xintersection[i];
            int x2 = xintersection[i+1] + 1;

            DDA(x1,y,x2,y,0,0,255);
        }
    }


}

