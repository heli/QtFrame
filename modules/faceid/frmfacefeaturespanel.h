#ifndef FRMFACEFEATURESPANEL_H
#define FRMFACEFEATURESPANEL_H

#include <QWidget>

namespace Ui {
class FrmFaceFeaturesPanel;
}

class FrmFaceFeaturesPanel : public QWidget
{
    Q_OBJECT

public:
    explicit FrmFaceFeaturesPanel(QWidget *parent = nullptr);
    ~FrmFaceFeaturesPanel();

private:
    Ui::FrmFaceFeaturesPanel *ui;
};

#endif // FRMFACEFEATURESPANEL_H
