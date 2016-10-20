#include "mypainterwidget.h"

#include <QString>
#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>


MyPainterWidget::MyPainterWidget(QWidget* parent)
     :QWidget(parent){
    setMinimumSize(240,120);
    setMaximumSize(480,240);
    this->setMouseTracking(true);
    this->isPressed = false;
}

MyPainterWidget::~MyPainterWidget(){

}

void MyPainterWidget::paintEvent(QPaintEvent*p){
    QPainter painter(this);
    QPen pen;                                 //创建一个画笔
    pen.setColor(Qt::darkCyan);
    pen.setWidth(5);
    painter.setPen(pen);

    for(int i = 0;i<lines.size();i++){
        //painter.drawPoint(lines[i]);
        if(i == 0)
            painter.drawPoint(lines[i]);
        else
            painter.drawLine(lines[i-1],lines[i]);
    }
}

void MyPainterWidget::mouseReleaseEvent(QMouseEvent *e){
    setCursor(Qt::ArrowCursor);
    this->lines.push_back(e->pos());
    update();
    this->isPressed = false;
}

//void MyPainterWidget::mousePressEvent(QMouseEvent *e){
//    setCursor(Qt::PointingHandCursor);
//    startPnt = e->pos();
//    endPnt = e->pos();
//    this->isPressed = true;
//}

//void MyPainterWidget::mouseMoveEvent(QMouseEvent *e){
//    if(this->isPressed){
//        endPnt = e->pos();

//        myLine* line = new myLine;  //put the new line into vector
//        line->startPnt = startPnt;
//        line->endPnt = endPnt;
//        this->lines.push_back(line);

//        update();                                    //repainter，call paintEvent
//        startPnt = endPnt;
//    }
//}


