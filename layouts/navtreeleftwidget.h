#ifndef NAVTREELEFTWIDGET_H
#define NAVTREELEFTWIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>

namespace Ui {
class NavTreeLeftWidget;
}

class NavTreeLeftWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NavTreeLeftWidget(QWidget *parent = nullptr);
    ~NavTreeLeftWidget();

private slots:
    void initForm();

    void on_navTreeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::NavTreeLeftWidget *ui;
};

#endif // NAVTREELEFTWIDGET_H
