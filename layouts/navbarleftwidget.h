#ifndef NAVBARLEFTWIDGET_H
#define NAVBARLEFTWIDGET_H

#include <QWidget>

namespace Ui {
class NavbarLeftWidget;
}

class NavbarLeftWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NavbarLeftWidget(QWidget *parent = nullptr);
    ~NavbarLeftWidget();

private:
    Ui::NavbarLeftWidget *ui;
};

#endif // NAVBARLEFTWIDGET_H
