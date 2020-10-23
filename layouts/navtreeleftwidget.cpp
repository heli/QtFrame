#include "navtreeleftwidget.h"
#include "ui_navtreeleftwidget.h"

#include <QDebug>

NavTreeLeftWidget::NavTreeLeftWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NavTreeLeftWidget)
{
    ui->setupUi(this);

    this->initForm();
}

NavTreeLeftWidget::~NavTreeLeftWidget()
{
    delete ui;
}

void NavTreeLeftWidget::initForm()
{

    QIcon icon1;
    icon1.addPixmap(QPixmap(":img/icon/camera_web.png"), QIcon::Selected);
    icon1.addPixmap(QPixmap(":img/icon/camera_web.png"), QIcon::Normal);
    ui->navTreeWidget->setRootIsDecorated(false);

    QTreeWidgetItem *rootItem;
    rootItem = new QTreeWidgetItem(ui->navTreeWidget);
    rootItem->setText(0, "菜单0");
    rootItem->setIcon(0, icon1);
    rootItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    rootItem->setData(0, Qt::UserRole, "0");

    QTreeWidgetItem *childItem1;
    childItem1 = new QTreeWidgetItem(ui->navTreeWidget);
    childItem1->setText(0, "菜单1");
    childItem1->setIcon(0, icon1);
    childItem1->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    childItem1->setData(0, Qt::UserRole, "1");

    QTreeWidgetItem *childItem2;
    childItem2 = new QTreeWidgetItem(ui->navTreeWidget);
    childItem2->setText(0, "菜单2");
    childItem2->setIcon(0, icon1);
    childItem2->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    childItem2->setData(0, Qt::UserRole, "2");
}

void NavTreeLeftWidget::on_navTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    int id = item->data(0, Qt::UserRole).value<int>();
    ui->stackedWidget->setCurrentIndex(id);
}
