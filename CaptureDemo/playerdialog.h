#ifndef PLAYERDIALOG_H
#define PLAYERDIALOG_H

#include <QDialog>
#include <QMediaPlayer>
#include "videosurface.h"

namespace Ui {
class PlayerDialog;
}

class PlayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerDialog(QWidget *parent = nullptr);
    ~PlayerDialog();
    void setPath(const QString &path);
protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void OnStateButtonChanged(QMediaPlayer::State state);//控制按钮状态
    void OndrtTimeChanged(qint64 drt);//视频文件时间长度，更新变化
    void OnposTimeChanged(qint64 pos);//播放视频当前位置时间更新变化
    void on_pushButton_open_clicked();//打开文件
    void on_horizontalSlide_speedr_valueChanged(int value);
    void on_pushButton_pause_clicked();
    void on_pushButton_play_clicked();
    void on_pushButton_stop_clicked();
    void on_pushButton_cap_clicked();
     void on_pushButton_close_clicked();
     void on_pushButton_forward_clicked();
     void on_pushButton_rewind_clicked();
    void onShowImage(QVideoFrame frame);

private:
    Ui::PlayerDialog *ui;
    QMediaPlayer *player;//播放器
    QString drtTime;//视频文件长度
    QString posTime;//播放视频的当前位置
    VideoSurface    *m_videoSurface=nullptr;
    QString m_path;

};

#endif // PLAYERDIALOG_H
