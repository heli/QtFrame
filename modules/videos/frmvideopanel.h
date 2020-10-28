#ifndef FRMVIDEOPANEL_H
#define FRMVIDEOPANEL_H

#include "videowidget.h"

#include <QGridLayout>
#include <QMenu>
#include <QWidget>

namespace Ui {
class FrmVideoPanel;
}

class FrmVideoPanel : public QWidget
{
    Q_OBJECT

public:
    explicit FrmVideoPanel(QWidget *parent = nullptr);
    ~FrmVideoPanel();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::FrmVideoPanel *ui;
    QGridLayout *gridLayout;    //表格布局存放视频标签
    bool videoMax;              //是否最大化
    int videoCount;             //视频通道个数
    QString videoType;          //当前画面类型
    QMenu *videoMenu;           //右键菜单
    QAction *actionFull;        //全屏动作
    QAction *actionPoll;        //轮询动作
    QList<VideoWidget *> widgets;    //视频标签集合

public:
    QSize sizeHint()            const;
    QSize minimumSizeHint()     const;

private slots:
    void initControl();
    void initForm();
    void initMenu();
    void full();
    void poll();

private slots:
    void play_video_all();
    void snapshot_video_one();
    void snapshot_video_all();

    void show_video_all();
    void show_video_4();
    void show_video_6();
    void show_video_8();
    void show_video_9();
    void show_video_13();
    void show_video_16();
    void show_video_25();
    void show_video_36();
    void show_video_64();

    void hide_video_all();
    void change_video(int index, int flag);
    void change_video_4(int index);
    void change_video_6(int index);
    void change_video_8(int index);
    void change_video_9(int index);
    void change_video_13(int index);
    void change_video_16(int index);
    void change_video_25(int index);
    void change_video_36(int index);
    void change_video_64(int index);

signals:
    void fullScreen(bool full);
};

#endif // FRMVIDEOPANEL_H
