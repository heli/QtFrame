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
    void initMedia();
    void setMediaUrl(QString url);
    void stopPlay();
    void startPlay();

protected:
    void resizeEvent(QResizeEvent *);

public slots:
    void OnSetMediaFile(void);
    void OnSlider(qint64);
    void OnDurationChanged(qint64);
    void OnSliderValueChanged(int);
    void OnVolumeValueChanged(int);
    void OnVolumeSliderReleased();

private slots:
    void stateChanged(QMediaPlayer::State state);
    void mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void on_btnVoice_clicked();
    void on_btnPlay_clicked();

private:
    Ui::VideoPlayer *ui;
    QVideoWidget    *m_pPlayerWidget;
    QMediaPlayer    *m_pPlayer;
    QSlider *m_pVolSlider;
    QWidget *flowPanel;

    QUrl mediaUrl;
    int mediaVolume = 0;
    int m_cFlowPanelHeight = 80;
    bool m_bReLoad;
    bool m_bPlaying;
};

#endif // VIDEOPLAYER_H
