#include "videoplayer.h"
#include "ui_videoplayer.h"

#include <QMenu>

VideoPlayer::VideoPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoPlayer)
{
    ui->setupUi(this);

    // Player Widget
    m_pPlayerWidget = new QVideoWidget;
    m_pPlayerWidget->setAutoFillBackground(true);
    QPalette qplte;
    qplte.setColor(QPalette::Window, QColor(0, 0, 0));
    m_pPlayerWidget->setPalette(qplte);
    m_pPlayer = new QMediaPlayer;
    m_pPlayer->setVolume(mediaVolume);
    m_pPlayer->setVideoOutput(m_pPlayerWidget);
    ui->verticalLayout->addWidget(m_pPlayerWidget);

    // Flow Panel
    flowPanel = new QWidget(this);
    flowPanel->setObjectName("flowPanel");
    flowPanel->setVisible(false);
    flowPanel->setGeometry(0, this->height() - 70, this->width() - 10, m_cFlowPanelHeight);

    //用布局顶住,左侧弹簧
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSpacing(2);
    layout->setMargin(5);
    layout->addStretch();
    flowPanel->setLayout(layout);

    // Volume
    m_pVolSlider = new QSlider();
    m_pVolSlider->setMaximum(100);
    m_pVolSlider->setValue(mediaVolume);
    connect(m_pVolSlider, SIGNAL(valueChanged(int)), this, SLOT(OnVolumeValueChanged(int)));
    connect(m_pVolSlider, SIGNAL(sliderReleased()), this, SLOT(OnVolumeSliderReleased()));
    flowPanel->layout()->addWidget(m_pVolSlider);

    //播放.停止
    connect(ui->btnPlay, SIGNAL(clicked()), m_pPlayer, SLOT(play()));

    connect(m_pPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(OnSlider(qint64)));
    connect(m_pPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(OnDurationChanged(qint64)));
    connect(m_pPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(stateChanged(QMediaPlayer::State)));
    connect(m_pPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this, SLOT(mediaStatusChanged(QMediaPlayer::MediaStatus)));

    //设置滑块行为
    m_bReLoad = true;
    ui->slider->setEnabled(false);
    connect(ui->slider, SIGNAL(valueChanged(int)), this, SLOT(OnSliderValueChanged(int)));

    this->initMedia();
}

VideoPlayer::~VideoPlayer()
{
    delete ui;
}

void VideoPlayer::initMedia()
{
    QString aFile = QDir::currentPath();
    QString filename; //= RecordFileHelper::getInstance()->getVideoPlayPath();
    if(filename != NULL) {
        QString filepath = aFile + "/" + filename;
        qDebug() << filepath;
        mediaUrl = QUrl::fromLocalFile(filepath);
    }
}

void VideoPlayer::setMediaUrl(QString url)
{
    mediaUrl = QUrl(url);
}

void VideoPlayer::stopPlay()
{
    m_bPlaying = false;
    m_pPlayer->pause();
    m_pPlayer->stop();

    ui->btnPlay->setText("播放");
    QIcon icon1;
    icon1.addPixmap(QPixmap(":img/icon/paly-play-48.png"), QIcon::Normal);
    ui->btnPlay->setIcon(icon1);
}

void VideoPlayer::startPlay()
{
    m_pPlayer->setMedia(mediaUrl);
    m_bPlaying = true;
    m_pPlayer->play();

    ui->btnPlay->setText("暂停");
    QIcon icon1;
    icon1.addPixmap(QPixmap(":img/icon/play-pause-50.png"), QIcon::Normal);
    ui->btnPlay->setIcon(icon1);
}

void VideoPlayer::mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    switch (status) {
        case QMediaPlayer::UnknownMediaStatus:
            qDebug() << tr("媒体未知状况！");
            break;
        case QMediaPlayer::NoMedia:
            qDebug() << tr("没有媒体文件！");
            break;
        case QMediaPlayer::BufferingMedia:
            qDebug() << tr("正在缓冲媒体文件！");
            break;
        case QMediaPlayer::BufferedMedia:
            qDebug() << tr("媒体文件缓冲完成！");
            ui->btnPlay->setEnabled(true);
            break;
        case QMediaPlayer::LoadingMedia:
            qDebug() << tr("正在加载媒体！");
            ui->btnPlay->setEnabled(false);
            break;
        case QMediaPlayer::StalledMedia:
            qDebug() << tr("播放停滞！");
            break;
        case QMediaPlayer::EndOfMedia:
            qDebug() << tr("播放结束！");
            break;
        case QMediaPlayer::LoadedMedia:
            qDebug() << tr("媒体加载完成！");
            break;
        case QMediaPlayer::InvalidMedia:
            qDebug() << tr("不可用的媒体文件！");
            break;
        default: break;
    }
}

void VideoPlayer::stateChanged(QMediaPlayer::State state)
{
    switch (state) {
        case QMediaPlayer::StoppedState:
        {
            qDebug() << tr("停止状态！");
            ui->btnPlay->setEnabled(true);
            m_bPlaying = false;
            ui->btnPlay->setText("播放");
            QIcon icon1;
            icon1.addPixmap(QPixmap(":img/icon/paly-play-48.png"), QIcon::Normal);
            ui->btnPlay->setIcon(icon1);
            break;
        }
        case QMediaPlayer::PlayingState:
        {
            qDebug() << tr("播放状态！");
            m_bPlaying = true;
            ui->btnPlay->setText("暂停");
            QIcon icon1;
            icon1.addPixmap(QPixmap(":img/icon/play-pause-50.png"), QIcon::Normal);
            ui->btnPlay->setIcon(icon1);
            break;
        }
        case QMediaPlayer::PausedState:
        {
            qDebug() << tr("暂停状态！");
            m_bPlaying = false;
            ui->btnPlay->setText("播放");
            QIcon icon1;
            icon1.addPixmap(QPixmap(":img/icon/paly-play-48.png"), QIcon::Normal);
            ui->btnPlay->setIcon(icon1);
            break;
        }
        default: break;
    }
}

void VideoPlayer::OnSetMediaFile(void)
{
}

void VideoPlayer::OnSlider(qint64 i64Pos)
{
    ui->slider->setValue(i64Pos);
}

void VideoPlayer::OnDurationChanged(qint64 i64Duration)
{
    if (i64Duration > 0 && m_bReLoad)
    {
        ui->slider->setRange(0, i64Duration);
        m_bReLoad = false;
    }
}

void VideoPlayer::OnSliderValueChanged(int val)
{
    m_pPlayer->setPosition(val);
}

void VideoPlayer::OnVolumeValueChanged(int val)
{
    mediaVolume = val;
    m_pPlayer->setVolume(mediaVolume);
}

void VideoPlayer::OnVolumeSliderReleased()
{
    flowPanel->setVisible(false);
}

void VideoPlayer::on_btnVoice_clicked()
{
    flowPanel->setGeometry(QRect(0, ui->btnVoice->y()-m_cFlowPanelHeight , this->width() - 10, m_cFlowPanelHeight));
    if(flowPanel->isHidden()) {
        flowPanel->setVisible(true);
    } else {
        flowPanel->setVisible(false);
    }

}

void VideoPlayer::resizeEvent(QResizeEvent *)
{
    //重新设置顶部工具栏的位置和宽高,可以自行设置顶部显示或者底部显示
    flowPanel->setGeometry(QRect(0, ui->btnVoice->y()-m_cFlowPanelHeight , this->width() - 10, m_cFlowPanelHeight));
}

void VideoPlayer::on_btnPlay_clicked()
{
    mediaUrl = QUrl("http://ivi.bupt.edu.cn/hls/cctv6hd.m3u8");
    //mediaUrl = QUrl("http://ivi.bupt.edu.cn/hls/cctv3hd.m3u8");
    //mediaUrl = QUrl("http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8");
    //mediaUrl = QUrl("http://ivi.bupt.edu.cn/hls/cctv5hd.m3u8");
    QMediaPlayer::State status = m_pPlayer->state();
    if(status == QMediaPlayer::PlayingState || m_bPlaying)
    {
        stopPlay();
    } else {
        startPlay();
    }
}
