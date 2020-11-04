#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "layouts/framelesswidget.h"

#include<QDateTime>
#include<QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->initForm();
    this->initControl();
    this->initStyle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initForm()
{
    statusBarTimeLabel=new QLabel;
    statusBarMsgLabel=new QLabel;

    QLabel *name = new QLabel(" ©西安米微信息技术有限公司 ", this);
    ui->statusBar->addPermanentWidget(name);
}

void MainWindow::initControl()
{
    FramelessWidget *w = (FramelessWidget*)this->parent();
    connect(w, SIGNAL(showContralFrameNav1()), this, SLOT(showFrame_MultipleVideo()));
    connect(w, SIGNAL(showContralFrameNav2()), this, SLOT(showFrame_LocalVideo()));
    connect(w, SIGNAL(showContralFrameNav3()), this, SLOT(showFrame_FaceFeatures()));
    connect(w, SIGNAL(showContralFrameNav4()), this, SLOT(showFrame_MultipleVideo()));
    connect(w, SIGNAL(showContralFrameNav5()), this, SLOT(showFrame_Settings()));

    QTimer *timer=new QTimer(this);
    timer->start(1000); // 每次发射timeout信号时间间隔为1秒
    connect(timer,SIGNAL(timeout()),this,SLOT(timeUpdate()));
}

void MainWindow::timeUpdate()
{
   QDateTime CurrentTime=QDateTime::currentDateTime();
   QString Timestr=CurrentTime.toString(" yyyy年-MM月-dd日 hh:mm "); //设置显示的格式
   statusBarTimeLabel->setText(Timestr);
   ui->statusBar->addPermanentWidget(statusBarTimeLabel);
   //ui->statusBar->addWidget(statusBarMsgLabel);
}

void MainWindow::showFrame_MultipleVideo()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::showFrame_LocalVideo()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::showFrame_FaceFeatures()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::showFrame_Settings()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::initStyle()
{
    //加载样式表
    QString qss;
    //QFile file(":/qss/psblack.css");
    //QFile file(":/qss/flatwhite.css");
    QFile file(":/qss/lightblue.css");
    if (file.open(QFile::ReadOnly)) {
#if 1
        //用QTextStream读取样式文件不用区分文件编码 带bom也行
        QStringList list;
        QTextStream in(&file);
        //in.setCodec("utf-8");
        while (!in.atEnd()) {
            QString line;
            in >> line;
            list << line;
        }

        qss = list.join("\n");
#else
        //用readAll读取默认支持的是ANSI格式,如果不小心用creator打开编辑过了很可能打不开
        qss = QLatin1String(file.readAll());
#endif
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}
