#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QPen>
#include <QPainter>
#include <QPoint>
#include <vector>

using namespace std;

class ImageLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ImageLabel(QWidget *parent = 0);
    ~ImageLabel();
    void reset();
    void back();

    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent* p);
    virtual void mouseReleaseEvent(QMouseEvent *e);



    void setSaveImage(const QPixmap &value);
    vector<QPoint> getLines() const;
    void setCoorPoint(const QPoint &value);

signals:
    void clicked(QPoint pos);
    void release();

protected:
    vector<QPoint> lines;
    const QPixmap *pTemp;
    QPixmap saveImage;
    QPoint coorPoint;

public slots:


};

#endif // IMAGELABEL_H
