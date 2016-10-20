#include "imagelabel.h"

ImageLabel::ImageLabel(QWidget *parent) :
    QLabel(parent)
{
    setMouseTracking(true);
    pTemp = NULL;
    coorPoint.setX(0);
    coorPoint.setY(0);
}

ImageLabel::~ImageLabel()
{

}

void ImageLabel::reset()
{
    lines.clear();
    update();
}

void ImageLabel::back()
{
    if(lines.size()>0)
    {
        lines.pop_back();
        update();
    }
}

void ImageLabel::mouseMoveEvent(QMouseEvent *event)
{
    emit clicked(event->pos());
}

void ImageLabel::paintEvent(QPaintEvent *p)
{
    QLabel::paintEvent(p);

    QPainter painter1(this);
    QPen pen1;                                 //创建一个画笔
    pen1.setColor(Qt::black);
    pen1.setWidth(2);
    painter1.setPen(pen1);
    QPoint start,end;
    start.setX(0);
    start.setY(coorPoint.y());
    end.setX(this->size().width());
    end.setY(coorPoint.y());
    painter1.drawLine(start,end);
    start.setX(coorPoint.x());
    start.setY(0);
    end.setX(coorPoint.x());
    end.setY(this->size().height());
    painter1.drawLine(start,end);

    if(pTemp != NULL)
    {
        this->setPixmap(*pTemp);
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
}

void ImageLabel::mouseReleaseEvent(QMouseEvent *e)
{
    setCursor(Qt::ArrowCursor);
    this->lines.push_back(e->pos());
    pTemp = this->pixmap();
    if(pTemp != NULL)
    {
        update();
        emit release();
    }
}


void ImageLabel::setSaveImage(const QPixmap &value)
{
    saveImage = value;
}
vector<QPoint> ImageLabel::getLines() const
{
    return lines;
}
void ImageLabel::setCoorPoint(const QPoint &value)
{
     coorPoint = value;
     update();
}







