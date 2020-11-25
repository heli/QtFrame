#include "frmlivevideowidget.h"
#include "ui_frmlivevideowidget.h"

#include <commonutility.h>

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

    CommonUtility *util= new CommonUtility();
    QString channelsPath = ":/conf/channels.json";
    QJsonObject root = util->readJsonFromFile(channelsPath) ;
    QJsonArray data = root.value("data").toArray();
    if(data.size() > 0) {
        for(int i = 0; i< data.size();i++) {
            QJsonObject item = data.at(i).toObject();
            QString name = item.value("name").toString();
            QString url = item.value("url").toString();

            QTreeWidgetItem *rootItem;
            rootItem = new QTreeWidgetItem(ui->navTreeWidget);
            rootItem->setText(0, name);
            rootItem->setIcon(0, icon1);
            rootItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            rootItem->setData(0, Qt::UserRole, url);
        }
    } else {
        QTreeWidgetItem *rootItem;
        rootItem = new QTreeWidgetItem(ui->navTreeWidget);
        rootItem->setText(0, "CCTV-1");
        rootItem->setIcon(0, icon1);
        rootItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        rootItem->setData(0, Qt::UserRole, "http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8");
    }
}

void FrmLiveVideoWidget::on_navTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    QString u = item->data(0, Qt::UserRole).value<QString>();
    //QString url = "http://ivi.bupt.edu.cn/hls/cctv3hd.m3u8";
    videoPlayer->setMediaUrl(u);
    videoPlayer->startPlay();
}
