#include "playerdialog.h"
#include "ui_playerdialog.h"
#include <QFileDialog>
#include <QStyle>
#include <QScreen>
#include <QVideoFrame>
#include <QDateTime>

static QImage imageFromVideoFrame(const QVideoFrame& buffer)
{
    QImage img;
    QVideoFrame frame(buffer);  // make a copy we can call map (non-const) on
    frame.map(QAbstractVideoBuffer::ReadOnly);
    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(
                frame.pixelFormat());
    // BUT the frame.pixelFormat() is QVideoFrame::Format_Jpeg, and this is
    // mapped to QImage::Format_Invalid by
    // QVideoFrame::imageFormatFromPixelFormat
    if (imageFormat != QImage::Format_Invalid) {
        img = QImage(frame.bits(),
                     frame.width(),
                     frame.height(),
                     // frame.bytesPerLine(),
                     imageFormat);
    } else {
        // e.g. JPEG
        int nbytes = frame.mappedBytes();
        img = QImage::fromData(frame.bits(), nbytes);
    }
    frame.unmap();
    return img;
}


PlayerDialog::PlayerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerDialog)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    player=new QMediaPlayer(this);
    player->setNotifyInterval(1000);
    player->setVideoOutput(ui->graphicsView);//视频显示组件
    m_videoSurface = new  VideoSurface(this);

    ui->graphicsView->SetMediaPlayer(player);//设置显示组件的关联播放器
    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(OnStateButtonChanged(QMediaPlayer::State)));
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(OnposTimeChanged(qint64)));
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(OndrtTimeChanged(qint64)));
    ui->horizontalSlide_speedr->installEventFilter(this);

}

PlayerDialog::~PlayerDialog()
{
    delete ui;
}

void PlayerDialog::setPath(const QString &path)
{
    m_path = path;
}

bool PlayerDialog::eventFilter(QObject *obj, QEvent *event)
{
    //解决QSlider点击不能到鼠标指定位置的问题
    if(obj==ui->horizontalSlide_speedr)
    {
        if (event->type()==QEvent::MouseButtonPress)           //判断类型
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
                int value = QStyle::sliderValueFromPosition(ui->horizontalSlide_speedr->minimum(), ui->horizontalSlide_speedr->maximum(), mouseEvent->pos().x(), ui->horizontalSlide_speedr->width());
                ui->horizontalSlide_speedr->setValue(value);
                player->setPosition(value);
            }
        }
    }
    return QObject::eventFilter(obj,event);
}

void PlayerDialog::OnStateButtonChanged(QMediaPlayer::State state)
{

    ui->pushButton_play->setEnabled(!(state==QMediaPlayer::PlayingState));
    ui->pushButton_pause->setEnabled(state==QMediaPlayer::PlayingState);
    ui->pushButton_stop->setEnabled(state==QMediaPlayer::PlayingState);
}

void PlayerDialog::OndrtTimeChanged(qint64 drt)
{
    ui->horizontalSlide_speedr->setMaximum(drt);

    int sec=drt/1000;//总时长
    int min=sec/60;//分
    sec=sec%60;//秒

    drtTime=QString::asprintf("%d:%d",min,sec);
    ui->label_speed->setText(posTime+"|"+drtTime);

}

void PlayerDialog::OnposTimeChanged(qint64 pos)
{
    if(ui->horizontalSlide_speedr->isSliderDown()){
        return;//如果正在拖动滑动条，则直接退出
    }
    ui->horizontalSlide_speedr->setSliderPosition(pos);

    int sec=pos/1000;
    int min=sec/60;
    sec=sec%60;

    posTime=QString::asprintf("%d:%d",min,sec);
    ui->label_speed->setText(posTime+"|"+drtTime);
}

void PlayerDialog::on_pushButton_open_clicked()
{
    QString currentpath = m_path;//获得系统当前目录
    QString dlgtitle="Please select video file";
    QString filter="mp4file(*.mp4)";//文件过滤器
    QString strfile=QFileDialog::getOpenFileName(this,dlgtitle,currentpath,filter);

    if(strfile.isEmpty()){
        return;
    }
    QFileInfo fileinfo(strfile);
    ui->label_name->setText(fileinfo.fileName());
    player->setMedia(QUrl::fromLocalFile(strfile));//设置播放文件
    player->play();
    ui->pushButton_play->setStyleSheet("#pushButton_play{ border-image: url(:/prefix1/pause.png);}#pushButton_play:pressed{ border-image: url(:/prefix1/pause1.png); }");
    ui->pushButton_pause->setStyleSheet("#pushButton_pause{ border-image: url(:/prefix1/play.png);}#pushButton_pause:pressed{ border-image: url(:/prefix1/play1.png); }");
}

void PlayerDialog::on_horizontalSlide_speedr_valueChanged(int value)
{
    //   player->setPosition(value);
}

void PlayerDialog::on_pushButton_pause_clicked()
{
    player->pause();
    ui->pushButton_pause->setStyleSheet("#pushButton_play{ border-image: url(:/prefix1/pause.png);}#pushButton_play:pressed{ border-image: url(:/prefix1/pause1.png); }");
    ui->pushButton_play->setStyleSheet("#pushButton_pause{ border-image: url(:/prefix1/play.png);}#pushButton_pause:pressed{ border-image: url(:/prefix1/play1.png); }");
}

void PlayerDialog::on_pushButton_play_clicked()
{
    player->play();
    ui->pushButton_play->setStyleSheet("#pushButton_play{ border-image: url(:/prefix1/pause.png);}#pushButton_play:pressed{ border-image: url(:/prefix1/pause1.png); }");
    ui->pushButton_pause->setStyleSheet("#pushButton_pause{ border-image: url(:/prefix1/play.png);}#pushButton_pause:pressed{ border-image: url(:/prefix1/play1.png); }");
}

void PlayerDialog::on_pushButton_stop_clicked()
{
    player->stop();
}

void PlayerDialog::on_pushButton_cap_clicked()
{
    //    QScreen *screen = QGuiApplication::primaryScreen();

    //        QRect rect;
    //        rect.setX(this->mapToGlobal(this->pos()).x());
    //        rect.setY(this->mapToGlobal(this->pos()).y());
    //        rect.setWidth(this->width());
    //        rect.setHeight(this->height());

    //        QPixmap pixmap =  screen->grabWindow(0,rect.x(),rect.y(),rect.width(),rect.height());

    //    //QScreen *screen = QGuiApplication::primaryScreen();
    //   //QPixmap pixmap =  ui->graphicsView->grab(ui->graphicsView->rect());
    //      // QPixmap pixmap = screen->grabWindow(0, 0,0, 1920, 1080);//抓取widget的图片
    //           // 将QPixmap转换为QImage
    //           QImage image = pixmap.toImage();
    //           // 保存图片到文件
    //           QString filename = QFileDialog::getSaveFileName(ui->graphicsView, tr("Save Screenshot"), QString(), tr("Images (*.png *.jpg)"));
    //           if (!filename.isEmpty()) {
    //               image.save(filename);
    //           }
    connect(m_videoSurface,SIGNAL(showImage(QVideoFrame)),
            this, SLOT(onShowImage(QVideoFrame)), Qt::QueuedConnection);
    player->setVideoOutput(m_videoSurface);

}

void PlayerDialog::on_pushButton_close_clicked()
{
    close();
}

void PlayerDialog::on_pushButton_forward_clicked()
{
    int value = ui->horizontalSlide_speedr->value() +ui->horizontalSlide_speedr->value()*0.1;
    ui->horizontalSlide_speedr->setValue(value);
    player->setPosition(value);
}

void PlayerDialog::on_pushButton_rewind_clicked()
{
    int value = ui->horizontalSlide_speedr->value() -ui->horizontalSlide_speedr->value()*0.1;
    ui->horizontalSlide_speedr->setValue(value);
    player->setPosition(value);
}

void PlayerDialog::onShowImage(QVideoFrame frame)
{
    disconnect(m_videoSurface,SIGNAL(showImage(QVideoFrame)),
               this, SLOT(onShowImage(QVideoFrame)));
    QString path = m_path + "/" +  QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + ".jpg";
    imageFromVideoFrame(frame).save(path);
    player->setVideoOutput(ui->graphicsView);

}
