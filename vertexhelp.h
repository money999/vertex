#ifndef VERTEXHELP_H
#define VERTEXHELP_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPoint>
#include <QString>
#include <QWidget>
#include <QScrollArea>
#include <QUrl>
#include <QList>
#include <QMimeData>
#include <QStackedLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QTextEdit>
#include <QLineEdit>
#include <vector>

using namespace std;

#include "imagelabel.h"
#include "mypainterwidget.h"


class Explain : public QDialog
{
    Q_OBJECT

public:
    Explain(QWidget *parent = 0);
    ~Explain();

private:
    QLabel *lbImage, *lbCopyRight, *lbcontext;

};




class VertexHelp : public QDialog
{
    Q_OBJECT

public:
    VertexHelp(QWidget *parent = 0);
    ~VertexHelp();

    virtual bool eventFilter(QObject *, QEvent *);

private:
    QPushButton *pbClear, *pbSure, *pbImageClear, *pbImageBack, *pbRevise, *pbCopyRight;
    QLabel *lbText, *lbDlam;
    QRadioButton *rb1, *rb2;
    QGroupBox *gbRadio, *gbCoordinate, *gbSpriteName;
    QButtonGroup *bgRadio;
    ImageLabel *lbImage;
    QScrollArea *saImage;
    QTextEdit *teShow;
    QLineEdit *coorX, *coorY, *spriteName;
    QWidget *wdDlam;

    QPoint coorPoint;

    Explain *setExplain;
private slots:
    void showPoint(QPoint p);
    void radioChange();
    void showResult();
    void resetImage();
    void backImage();
    void resultRelease();
    void showClear();
    void reviseCoor();
    void copyright();
};

#endif // VERTEXHELP_H
