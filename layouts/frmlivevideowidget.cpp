#include "frmlivevideowidget.h"
#include "ui_frmlivevideowidget.h"

FrmLiveVideoWidget::FrmLiveVideoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmLiveVideoWidget)
{
    ui->setupUi(this);

    this->initForm();
}

FrmLiveVideoWidget::~FrmLiveVideoWidget()
{
    delete ui;
}

void FrmLiveVideoWidget::initForm()
{
    videoPlayer = new VideoPlayer();
    ui->centerLayout->addWidget(videoPlayer);

    QIcon icon1;
    icon1.addPixmap(QPixmap(":img/icon/folder_opened.png"), QIcon::Selected);
    icon1.addPixmap(QPixmap(":img/icon/folder_closed.png"), QIcon::Normal);
    ui->navTreeWidget->setRootIsDecorated(false);

    QTreeWidgetItem *rootItem;
    rootItem = new QTreeWidgetItem(ui->navTreeWidget);
    rootItem->setText(0, "CCTV-1");
    rootItem->setIcon(0, icon1);
    rootItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem->setData(0, Qt::UserRole, "http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8");

    QTreeWidgetItem *childItem1;
    childItem1 = new QTreeWidgetItem(ui->navTreeWidget);
    childItem1->setText(0, "CCTV-3");
    childItem1->setIcon(0, icon1);
    childItem1->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    childItem1->setData(0, Qt::UserRole, "http://ivi.bupt.edu.cn/hls/cctv3hd.m3u8");

    QTreeWidgetItem *childItem2;
    childItem2 = new QTreeWidgetItem(ui->navTreeWidget);
    childItem2->setText(0, "CCTV-6");
    childItem2->setIcon(0, icon1);
    childItem2->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    childItem2->setData(0, Qt::UserRole, "http://ivi.bupt.edu.cn/hls/cctv6hd.m3u8");

    QTreeWidgetItem *childItem3;
    childItem2 = new QTreeWidgetItem(ui->navTreeWidget);
    childItem2->setText(0, "CCTV-9");
    childItem2->setIcon(0, icon1);
    childItem2->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    childItem2->setData(0, Qt::UserRole, "http://ivi.bupt.edu.cn/hls/cctv9hd.m3u8");
}

void FrmLiveVideoWidget::on_navTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    QString u = item->data(0, Qt::UserRole).value<QString>();
    //QString url = "http://ivi.bupt.edu.cn/hls/cctv3hd.m3u8";
    videoPlayer->setMediaUrl(u);
    videoPlayer->startPlay();
}
