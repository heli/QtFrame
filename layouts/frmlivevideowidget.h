#ifndef FRMLIVEVIDEOWIDGET_H
#define FRMLIVEVIDEOWIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>

#include <videos/videoplayer.h>

namespace Ui {
class FrmLiveVideoWidget;
}

class FrmLiveVideoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FrmLiveVideoWidget(QWidget *parent = nullptr);
    ~FrmLiveVideoWidget();

    void initForm();

private slots:
    void on_navTreeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::FrmLiveVideoWidget *ui;

    VideoPlayer *videoPlayer;
};

#endif // FRMLIVEVIDEOWIDGET_H
