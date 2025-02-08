#ifndef QMYSELFVIDEO_H
#define QMYSELFVIDEO_H

#include<QVideoWidget>
#include<QObject>
#include<QWidget>
#include<QMediaPlayer>

#include<QKeyEvent>
#include<QMouseEvent>

class QMySelfVideo : public QVideoWidget
{
public:
    QMySelfVideo(QWidget *parent=nullptr);

    void SetMediaPlayer(QMediaPlayer *player);

private:
    QMediaPlayer  *theplayer;

protected:
    void keyPressEvent(QKeyEvent *event);//键盘按键事件，当按键按下esc退出全屏
    void mousePressEvent(QMouseEvent *event);//鼠标按键时间，点击暂停和播放
};


#endif // QMYSELFVIDEO_H
