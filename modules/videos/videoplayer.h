#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QtMultimedia>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QSlider>

namespace Ui {
class VideoPlayer;
}

class VideoPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = nullptr);
    ~VideoPlayer();
    bool m_bReLoad;
    void initMedia();

    void stopPlay();

protected:
    void resizeEvent(QResizeEvent *);

public slots:
    void OnSetMediaFile(void);
    void OnSlider(qint64);
    void OnDurationChanged(qint64);
    void OnStateChanged(QMediaPlayer::State);
    void OnSliderValueChanged(int);
    void OnVolumeValueChanged(int);
    void OnVolumeSliderReleased();

private slots:
    void on_btnVoice_clicked();

private:
    Ui::VideoPlayer *ui;
    QVideoWidget    *m_pPlayerWidget;
    QMediaPlayer    *m_pPlayer;
    QSlider *m_pVolSlider;
    QWidget *flowPanel;
};

#endif // VIDEOPLAYER_H
