#include "vertexhelp.h"

VertexHelp::VertexHelp(QWidget *parent)
    : QDialog(parent)
{

    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowCloseButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags);

    setWindowTitle(tr("Vertex by fzj v1.0"));
    setWindowIcon(QIcon(":/image/lyd.png"));

    coorPoint.setX(0);
    coorPoint.setY(0);

    lbText = new QLabel();
    lbText->setText(tr("将图片拖入上方框中，此处将显示坐标"));

    lbImage = new ImageLabel();
    saImage = new QScrollArea();
    saImage->installEventFilter(this);
    saImage->setAcceptDrops(true);
    pbImageClear = new QPushButton(tr("重置"));
    pbImageBack = new QPushButton(tr("后退"));
    QHBoxLayout *imCoor = new QHBoxLayout;
    imCoor->addWidget(pbImageClear);
    imCoor->addWidget(pbImageBack);


    rb1 = new QRadioButton();
    rb1->setText(tr("box2D"));
    rb1->setChecked(true);
    rb2 = new QRadioButton();
    rb2->setText(tr("android"));
    rb2->setEnabled(false);//////////////////暂时先不用
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(rb1);
    vbox->addWidget(rb2);
    gbRadio = new QGroupBox(tr("选择坐标系"));
    gbRadio->setLayout(vbox);
    bgRadio = new QButtonGroup();
    bgRadio->addButton(rb1);
    bgRadio->addButton(rb2);
    bgRadio->setId(rb1,1);
    bgRadio->setId(rb2,2);
    gbRadio->setMaximumWidth(100);

    teShow = new QTextEdit();
    teShow->setMaximumWidth(299);
    teShow->setReadOnly(true);

    pbSure = new QPushButton(tr("生成数组"));
    pbClear = new QPushButton(tr("清空"));
    QHBoxLayout *btLayout = new QHBoxLayout;
    btLayout->addWidget(pbSure);
    btLayout->addWidget(pbClear);

    coorX = new QLineEdit();
    coorX->setMaximumWidth(39);
    coorX->setReadOnly(true);
    coorY = new QLineEdit();
    coorY->setMaximumWidth(39);
    coorY->setReadOnly(true);
    pbRevise = new QPushButton(tr("修改"));
    gbCoordinate = new QGroupBox(tr("原点坐标"));
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(coorX);
    hbox->addWidget(coorY);
    QVBoxLayout *rebox = new QVBoxLayout;
    rebox->addLayout(hbox);
    rebox->addWidget(pbRevise);
    gbCoordinate->setLayout(rebox);
    gbCoordinate->setMaximumWidth(100);
    lbDlam = new QLabel(this);
    lbDlam->setPixmap(QPixmap(":/image/dlam.png"));
    pbCopyRight = new QPushButton(tr("关于"));

    gbSpriteName = new QGroupBox(tr("名称"));
    spriteName = new QLineEdit(tr("fzj"));
    //spriteName->setMaximumWidth(150);
    QHBoxLayout *hboxSprite = new QHBoxLayout;
    hboxSprite->addWidget(spriteName);
    gbSpriteName->setLayout(hboxSprite);
    gbSpriteName->setMaximumWidth(150);

    QVBoxLayout *main1=new QVBoxLayout;
    main1->setMargin(5);
    main1->setSpacing(5);
    main1->addWidget(saImage);
    main1->addWidget(lbText);
    main1->addLayout(imCoor);

    QVBoxLayout *main2=new QVBoxLayout;
    main2->setMargin(5);
    main2->setSpacing(5);
    main2->addWidget(gbRadio);
    main2->addWidget(gbCoordinate);
    main2->addWidget(lbDlam);
    main2->addWidget(gbSpriteName);
    main2->addWidget(pbCopyRight);
    main2->addStretch(1);//加个弹簧

    QVBoxLayout *main3=new QVBoxLayout;
    main3->setMargin(5);
    main3->setSpacing(5);
    main3->addWidget(teShow);
    main3->addLayout(btLayout);


    QHBoxLayout *layout=new QHBoxLayout(this);
    layout->addLayout(main2);
    layout->addLayout(main1);
    layout->addLayout(main3);

    connect(lbImage,SIGNAL(clicked(QPoint)),this,SLOT(showPoint(QPoint)));
    connect(lbImage,SIGNAL(release()),this,SLOT(showResult()));
    connect(rb1,SIGNAL(clicked()),this,SLOT(radioChange()));
    connect(rb2,SIGNAL(clicked()),this,SLOT(radioChange()));
    connect(pbImageClear,SIGNAL(clicked()),this,SLOT(resetImage()));
    connect(pbImageBack,SIGNAL(clicked()),this,SLOT(backImage()));
    connect(pbSure,SIGNAL(clicked()),this,SLOT(resultRelease()));
    connect(pbRevise,SIGNAL(clicked()),this,SLOT(reviseCoor()));
    connect(pbClear,SIGNAL(clicked()),this,SLOT(showClear()));
    connect(pbCopyRight,SIGNAL(clicked()),this,SLOT(copyright()));
}

VertexHelp::~VertexHelp()
{
}

bool VertexHelp::eventFilter(QObject *watched, QEvent *event) {

    if (watched == saImage) {
        if (event->type() == QEvent::DragEnter) {
            // [[2]]: 当拖放时鼠标进入label时, label接受拖放的动作
            QDragEnterEvent *dee = dynamic_cast<QDragEnterEvent *>(event);
            dee->acceptProposedAction();
            return true;
        } else if (event->type() == QEvent::Drop) {
            // [[3]]: 当放操作发生后, 取得拖放的数据
            QDropEvent *de = dynamic_cast<QDropEvent *>(event);
            QList<QUrl> urls = de->mimeData()->urls();
            if (urls.isEmpty()) { return true; }
            QString path = urls.first().toLocalFile();
            // [[4]]: 在label上显示拖放的图片
            path = QDir::toNativeSeparators(path);
            QImage image(path); // QImage对I/O优化过, QPixmap对显示优化
            if (!image.isNull()) {
                QPoint t(image.width()/2, image.height()/2);
                coorPoint = t;
                lbImage->setCoorPoint(t);
                lbImage->setPixmap(QPixmap(path));
                lbImage->setPixmap(QPixmap::fromImage(image));
                saImage->setWidget(lbImage);
                coorX->setReadOnly(false);
                coorY->setReadOnly(false);
                radioChange();
                teShow->setText(path + "\n图片加载成功");
            }
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}


void VertexHelp::showPoint(QPoint p)
{
    QString t = QString("coordinate: (%1 , %2)").arg(p.x()).arg(p.y());
    lbText->setText(t);
}

void VertexHelp::radioChange()
{
    switch(bgRadio->checkedId())
    {
    case 1:
        coorX->setText(QString("%1").arg(lbImage->size().width()/2));
        coorY->setText(QString("%1").arg(lbImage->size().height()/2));
        reviseCoor();
        break;
    case 2:
        coorX->setText(QString("%1").arg(0));
        coorY->setText(QString("%1").arg(0));
        reviseCoor();
        break;
    }
}

void VertexHelp::showResult()
{
    vector<QPoint> pointSet = lbImage->getLines();
    QSize imSize = lbImage->size();
    QString stResult = "";
    int i,x,y;
    switch(bgRadio->checkedId())
    {
    case 1:
        for(i=0; i<pointSet.size(); i++)
        {
            QPoint t = pointSet[i];
            x = t.x() - coorPoint.x();
            y = coorPoint.y() - t.y();
            stResult += QString("{%1, %2}\n").arg(x).arg(y);
        }
        teShow->setText(stResult);
        break;
    case 2:
        for(i=0; i<pointSet.size(); i++)
        {
            QPoint t = pointSet[i];
            x = t.x();
            y = t.y();
            stResult += QString("{%1, %2}\n").arg(x).arg(y);
        }
        teShow->setText(stResult);
        break;
    }
}

void VertexHelp::resetImage()
{
    lbImage->reset();
}

void VertexHelp::backImage()
{
    lbImage->back();
    showResult();
}

void VertexHelp::resultRelease()
{
    //int num = 6;
    //b2Vec2 verts[] = {
    //b2Vec2(4.5f / PTM_RATIO, -17.7f / PTM_RATIO),
    //b2Vec2(20.5f / PTM_RATIO, 7.2f / PTM_RATIO),
    //b2Vec2(22.8f / PTM_RATIO, 29.5f / PTM_RATIO),
    //b2Vec2(-24.7f / PTM_RATIO, 31.0f / PTM_RATIO),
    //b2Vec2(-20.2f / PTM_RATIO, 4.7f / PTM_RATIO),
    //b2Vec2(-11.7f / PTM_RATIO, -17.5f / PTM_RATIO)
    //};
    vector<QPoint> pointSet = lbImage->getLines();
    QSize imSize = lbImage->size();
    QString stResult = QString("int num = %1;\nb2Vec2 verts[] = {\n").arg(pointSet.size());
    int i,x,y;
    QString name = spriteName->text();
    switch(bgRadio->checkedId())
    {
    case 1:
        for(i=0; i<pointSet.size(); i++)
        {
            QPoint t = pointSet[i];
            x = t.x() - coorPoint.x();
            y = coorPoint.y() - t.y();
            stResult += QString("b2Vec2(%1.0f / PTM_RATIO, %2.0f / PTM_RATIO),\n").arg(x).arg(y);
        }
        stResult += "};\n\n";


        stResult += QString("<key>%2_num</key>\n<string>%1</string>\n").arg(pointSet.size()).arg(name);
         for(i=0; i<pointSet.size(); i++)
         {
             QPoint t = pointSet[i];
             x = t.x() - coorPoint.x();
             y = coorPoint.y() - t.y();
             stResult += QString("<key>%5_%1_x</key>\n<string>%2</string>\n<key>%5_%3_y</key>\n<string>%4</string>\n").arg(i+1).arg(x).arg(i+1).arg(y).arg(name);
         }

        teShow->setText(stResult);
        break;

    case 2:
        for(i=0; i<pointSet.size(); i++)
        {
            QPoint t = pointSet[i];
            x = t.x();
            y = t.y();
            stResult += QString("b2Vec2(%1f / PTM_RATIO, %2f / PTM_RATIO),\n").arg(x).arg(y);
        }
        stResult += "};";
        teShow->setText(stResult);
        break;
    }


}

void VertexHelp::showClear()
{
    teShow->clear();
}

void VertexHelp::reviseCoor()
{
    coorPoint.setX(coorX->text().toInt());
    coorPoint.setY(coorY->text().toInt());
    lbImage->setCoorPoint(coorPoint);
}

void VertexHelp::copyright()
{
    setExplain = new Explain(this);
    setExplain->show();
}

Explain::Explain(QWidget *parent): QDialog(parent)
{

    setWindowTitle(tr("CrpytFile by fzj v1.0"));
    setWindowIcon(QIcon(":/image/lyd.png"));
    QString ex = "1、本软件遵循LGPL协议，不作为任何商业用途，仅供学习和交流\n"
                /* "2、图片拖动到label上，在xp上可以用，弄到实验室不能用，安装Qt\n"
                 "后还是不能用（因为xp用5.3，实验室用5.4），改了依赖库后实验室能用\n"
                 "了，因为实验室有装Qt所以能找到imageformats，换到其他又不能用，\n"
                 "发现时没有吧imageformats拷到exe的目录下！"*/;
    //QString ex = "1、软件不区分加密及未加密文件，当导入文件未被本软件加密过，则执行加密操作。当导\n入被本软件加密过的文件时则执行解密操作。软件无法对同一个文件连续加密两次\n\n2、在加密时默认强制修改文件名，默认为数字.fzj，多个文件则递增。在自定义中可添加\n文件名前缀，如设置文件名为abc,后缀名为dat。则加密后的文件名为abc1.dat，abc2.\ndat。\n\n3、加密后若提示encrypt success but rename error，则可能由于您设置的文件名\n存在重名的情况，也可能该文件属性为隐藏或系统文件则更名失败\n\n4、解密的时候需要输入正确密码，若密码遗忘则——无解\n\n5、解密后会自动恢复原文件名，若提示decrypt success but rename error，请检\n查文件是否重名\n\n6、本软件遵循LGPL协议，但不作为任何商业用途，仅供学习和交流";
    lbImage = new QLabel();
    lbCopyRight = new QLabel(tr("Copyright@2015,fzj"));
    lbcontext = new QLabel(ex);

    lbImage->setPixmap(QPixmap(":/image/yxy.png"));
    lbImage->setAlignment(Qt::AlignHCenter);
    lbCopyRight->setAlignment(Qt::AlignHCenter);

    QFont ft;
    ft.setPointSize(20);
    lbCopyRight->setFont(ft);

    QHBoxLayout *main1=new QHBoxLayout();
    main1->addWidget(lbImage);

    QHBoxLayout *main2=new QHBoxLayout();
    main2->addWidget(lbCopyRight);

    QHBoxLayout *main3=new QHBoxLayout();
    main3->addWidget(lbcontext);

    QVBoxLayout *layout=new QVBoxLayout(this);
    layout->addLayout(main1);
    layout->addLayout(main2);
    layout->addLayout(main3);

}
Explain::~Explain()
{

}
