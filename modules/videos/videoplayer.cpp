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
    m_pPlayer->setVideoOutput(m_pPlayerWidget);
    ui->verticalLayout->addWidget(m_pPlayerWidget);

    // Flow Panel
    flowPanel = new QWidget(this);
    flowPanel->setObjectName("flowPanel");
    flowPanel->setVisible(false);
    flowPanel->setGeometry(0, this->height() - 70, this->width() - 20, 100);

    //用布局顶住,左侧弹簧
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSpacing(2);
    layout->setMargin(5);
    layout->addStretch();
    flowPanel->setLayout(layout);

    // Volume
    m_pVolSlider = new QSlider();
    connect(m_pVolSlider, SIGNAL(valueChanged(int)), this, SLOT(OnVolumeValueChanged(int)));
    connect(m_pVolSlider, SIGNAL(sliderReleased()), this, SLOT(OnVolumeSliderReleased()));
    flowPanel->layout()->addWidget(m_pVolSlider);

    //播放
    connect(ui->btnPlay, SIGNAL(clicked()), m_pPlayer, SLOT(play()));
    //停止
    //connect(ui->btnStop, SIGNAL(clicked()), m_pPlayer, SLOT(stop()));
    //connect(m_pPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(OnStateChanged(QMediaPlayer::State)));
    //ui->btnStop->setEnabled(false);

    //设置滑块行为
    m_bReLoad = true;
    ui->slider->setEnabled(false);
    connect(m_pPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(OnSlider(qint64)));
    connect(m_pPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(OnDurationChanged(qint64)));
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
        m_pPlayer->setMedia(QUrl::fromLocalFile(filepath));
        m_bReLoad = true;
        ui->slider->setValue(0);
    }
}

void VideoPlayer::stopPlay()
{
    QMediaPlayer::State status = m_pPlayer->state();
    if(status == QMediaPlayer::PlayingState)
    {
        m_pPlayer->stop();
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

void VideoPlayer::OnStateChanged(QMediaPlayer::State enumState)
{
    if (QMediaPlayer::StoppedState == enumState)
    {
        ui->btnPlay->setEnabled(true);
        //ui->btnStop->setEnabled(false);
        ui->slider->setEnabled(false);
    }
    else if (QMediaPlayer::PlayingState == enumState)
    {
        ui->btnPlay->setEnabled(false);
        //ui->btnStop->setEnabled(true);
        ui->slider->setEnabled(true);
    }
}

void VideoPlayer::OnSliderValueChanged(int val)
{
    m_pPlayer->setPosition(val);
}

void VideoPlayer::OnVolumeValueChanged(int val)
{

}

void VideoPlayer::OnVolumeSliderReleased()
{
    flowPanel->setVisible(false);
}

void VideoPlayer::on_btnVoice_clicked()
{
    int height = 100;
    flowPanel->setGeometry(QRect(0, ui->btnVoice->y()-height , this->width() - 10, height));
    if(flowPanel->isHidden()) {
        flowPanel->setVisible(true);
    } else {
        flowPanel->setVisible(false);
    }

}

void VideoPlayer::resizeEvent(QResizeEvent *)
{
    //重新设置顶部工具栏的位置和宽高,可以自行设置顶部显示或者底部显示
    int height = 100;
    flowPanel->setGeometry(QRect(0, ui->btnVoice->y()-height , this->width() - 10, height));
}
