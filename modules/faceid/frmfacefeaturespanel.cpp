#include "frmfacefeaturespanel.h"
#include "ui_frmfacefeaturespanel.h"

FrmFaceFeaturesPanel::FrmFaceFeaturesPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmFaceFeaturesPanel)
{
    ui->setupUi(this);
}

FrmFaceFeaturesPanel::~FrmFaceFeaturesPanel()
{
    delete ui;
}
