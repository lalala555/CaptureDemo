#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "previewthread.h"
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void WriteToFile(const QString &filePath, QList<QString> &text);
    void ReadFromFile(const QString &filePath);

signals:
    void  Sigstart(long long wid);
    void  Sigclose();
    void  SigStartRecord(QString path);
    void SigEndRecord();
    void SigSnapshot(QString path);
    void SigUpdateOSD(QString text);
    void SigUpdateOSD2(QString text);
    void SigUpdateOSD1(QString text1,QString text2,QString text);
public slots:
    void  SlotNum(long long number);
    void  SlotStartRecordStatus(int ret);
    void  SlotEndRecordStatus(int ret);
    void  SlotSnapshotStatus(int ret);
    void  SlotIsOpen(int ret);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_PlayerBtn_clicked();
    void updatetime();
    void updatetime1();
    void readyRead_Slot();
    void slot_serialport_delay_recv_timeout();
    void DisConnection_slot();

    void Connection_slot();
private:
    Ui::MainWindow *ui;
    QThread* m_thread;
    PreviewThread *m_pthread;
    QString m_filePath;
    QString m_osdText;
    QTimer * m_timer;
    QTimer * m_timer1;
    QTime * TimeRecord;  //记录时间
    QMessageBox m_Box;
    QList<QString> m_cache;
    QTcpSocket * m_tcp;
    QByteArray m_data;
    QTimer *pTimerRecv;

};
#endif // MAINWINDOW_H
