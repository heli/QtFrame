#include "navbarleftwidget.h"
#include "ui_navbarleftwidget.h"

NavbarLeftWidget::NavbarLeftWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NavbarLeftWidget)
{
    ui->setupUi(this);
}

NavbarLeftWidget::~NavbarLeftWidget()
{
    delete ui;
}
