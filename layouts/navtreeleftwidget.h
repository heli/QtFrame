#ifndef NAVTREELEFTWIDGET_H
#define NAVTREELEFTWIDGET_H

#include <QWidget>

namespace Ui {
class NavTreeLeftWidget;
}

class NavTreeLeftWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NavTreeLeftWidget(QWidget *parent = nullptr);
    ~NavTreeLeftWidget();

private:
    Ui::NavTreeLeftWidget *ui;
};

#endif // NAVTREELEFTWIDGET_H
