#include "navtreeleftwidget.h"
#include "ui_navtreeleftwidget.h"

NavTreeLeftWidget::NavTreeLeftWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NavTreeLeftWidget)
{
    ui->setupUi(this);
}

NavTreeLeftWidget::~NavTreeLeftWidget()
{
    delete ui;
}
