#include "qmyselfvideo.h"
#include<QGraphicsView>

QMySelfVideo::QMySelfVideo(QWidget *parent):QVideoWidget(parent)
{

}

void QMySelfVideo::SetMediaPlayer(QMediaPlayer *player)
{
    //设置播放器操作
    theplayer=player;
}

void QMySelfVideo::keyPressEvent(QKeyEvent *event)//当播放器为全屏的时候，我们按下esc就可以退出全屏
{
    if((event->key()==Qt::Key_Escape)&&(isFullScreen())){
        setFullScreen(false);
        event->accept();
        QVideoWidget::keyPressEvent(event);
    }
}

void QMySelfVideo::mousePressEvent(QMouseEvent *event)//按下左键设置播放和暂停
{
    if(event->button()==Qt::LeftButton){
        if(theplayer->state()==QMediaPlayer::PlayingState){
            theplayer->pause();
        }else{
            theplayer->play();
        }
    }
    QVideoWidget::mousePressEvent(event);
}
