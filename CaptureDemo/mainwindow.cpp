#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <iostream>
#include "settingdlg.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QFileDialog>
#include "playerdialog.h"
#include <QProcess>
#include <QWindow>
#include <shellapi.h>
#include <QHostAddress>
#include <QDataStream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);


   ShellExecuteA(NULL, "open", "D:\\soft\\caiji\\caijiServer\\project.exe", NULL, NULL, SW_MINIMIZE);
    QString imagepath = QCoreApplication::applicationDirPath();
    imagepath+= "/123.txt";
    ReadFromFile(imagepath);
    if(m_cache.size() > 0)
        m_filePath = m_cache.at(0);

    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(updatetime()));
    m_timer1 = new QTimer(this);
    connect(m_timer1,SIGNAL(timeout()),this,SLOT(updatetime1()));
    m_timer1->start(1000);
    m_tcp =new QTcpSocket(this);
    m_tcp->connectToHost(QHostAddress("192.168.1.5") , 502);
    m_tcp->waitForConnected(300);
    connect(m_tcp,SIGNAL(readyRead()),this,SLOT(readyRead_Slot()));//若客户端有消息进来的话,会触发信号readyRead_Slot();
    connect(m_tcp, SIGNAL(disconnected()), this, SLOT(DisConnection_slot()));//断开连接的话会触发disconnected();
    connect(m_tcp, SIGNAL(connected()), this, SLOT(Connection_slot()));//断开连接的话会触发disconnected();

    ui->lcdNumber->setDigitCount(8);
    TimeRecord = new QTime(0, 0, 0); //初始化时间
    ui->lcdNumber->display(TimeRecord->toString("hh:mm:ss"));
      ui->lcdNumber->hide();
    // this->setAttribute(Qt::WA_DeleteOnClose);
    long long wid = ui->widget->winId();
    m_thread = new QThread();
    m_pthread = new PreviewThread;
    connect(this,&MainWindow::Sigstart,m_pthread,&PreviewThread::startPreview);
    connect(this,&MainWindow::SigStartRecord,m_pthread,&PreviewThread::startRecord);
    connect(this,&MainWindow::SigEndRecord,m_pthread,&PreviewThread::closeRecord);
    connect(this,&MainWindow::SigSnapshot,m_pthread,&PreviewThread::SnapShot);
    connect(this,&MainWindow::Sigclose,m_pthread,&PreviewThread::closePreview);
    connect(this,&MainWindow::SigUpdateOSD,m_pthread,&PreviewThread::updateOSD);
    connect(this,&MainWindow::SigUpdateOSD1,m_pthread,&PreviewThread::updateOSD1);
    connect(this,&MainWindow::SigUpdateOSD2,m_pthread,&PreviewThread::updateOSD2);
    connect(m_pthread,&PreviewThread::SigNum,this,&MainWindow::SlotNum);
    connect(m_pthread,&PreviewThread::SigStartRecordStatus,this,&MainWindow::SlotStartRecordStatus);
    connect(m_pthread,&PreviewThread::SigEndRecordStatus,this,&MainWindow::SlotEndRecordStatus);
    connect(m_pthread,&PreviewThread::SigSnapshotStatus,this,&MainWindow::SlotSnapshotStatus);
    connect(m_pthread,&PreviewThread::SigIsOpen,this,&MainWindow::SlotIsOpen);
    m_pthread->moveToThread(m_thread);
    m_thread->start();
    emit Sigstart(wid);
    if(m_cache.size() > 1)
        emit SigUpdateOSD(m_cache.at(1));
    m_data.clear();
    m_data.append(char(0x00));
    m_data.append(char(0x00));
    m_data.append(char(0x00));
    m_data.append(char(0x00));
    m_data.append(char(0x00));
    m_data.append(char(0x06));
    m_data.append(char(0x01));
    m_data.append(char(0x03));
    m_data.append(char(0x4F));
    m_data.append(char(0x4C));
    m_data.append(char(0x00));
    m_data.append(char(0x0E));
    pTimerRecv = new QTimer(this);
    pTimerRecv->setTimerType(Qt::PreciseTimer);
    pTimerRecv->setSingleShot(true); //只触发一次
    connect(pTimerRecv, &QTimer::timeout, this, &MainWindow::slot_serialport_delay_recv_timeout);
    ui->textEdit->hide();
    ui->lineEdit->hide();
}

MainWindow::~MainWindow()
{
    emit Sigclose();
    delete ui;
}

void MainWindow::WriteToFile(const QString &filePath,  QList<QString> &text)
{
     QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
    {
           qWarning("Cannot open file for writing.");
           return;
       }
       QTextStream out(&file);
       for(auto value:text)
       {
            value += "\n";
            out << value;
       }
       file.close();
}

void MainWindow::ReadFromFile(const QString &filePath)
{
          m_cache.clear();
          QFile file(filePath);
           if (!file.open(QIODevice::ReadOnly))
           {
               return;
           }

           QTextStream in(&file);
           while (!in.atEnd()) {
                  QString line = in.readLine();
                  m_cache << line; // 输出读取的每一行
              }

           file.close();
}

void MainWindow::SlotNum(long long number)
{
    //ui->label->setText(QString::number(number));
}

void MainWindow::SlotStartRecordStatus(int ret)
{
     if(ret < 0)
     {
          m_Box.setWindowTitle("Tip");
        m_Box.setText("Recording Error ");
      m_Box.setFixedSize(440,150);
      m_Box.exec();
     }
     else
     {
          m_timer->start(1000);
           ui->lcdNumber->show();
     }
}

void MainWindow::SlotEndRecordStatus(int ret)
{

    if(ret < 0)
    {
         m_Box.setWindowTitle("Tip");
        m_Box.setText("Recording Complete Error");
        m_Box.exec();
    }
    else
    {
        m_timer->stop();    //计时器停止
        TimeRecord->setHMS(0,0,0); //时间设为0
        ui->lcdNumber->display(TimeRecord->toString("hh:mm:ss")); //显示00:00:00
        ui->lcdNumber->hide();
    }
}

void MainWindow::SlotSnapshotStatus(int ret)
{
    if(ret < 0)
        m_Box.setText("Screenshot Failed");
    else
    {

        m_Box.setText("Screenshot Successful");
    }

    m_Box.exec();
}

void MainWindow::SlotIsOpen(int ret)
{
    long long wid = ui->widget->winId();
    if(ret == 0)
        emit  Sigstart(wid);
}


void MainWindow::on_pushButton_clicked()
{
    if(m_filePath == "")
    {
        QMessageBox msgBox;
        msgBox.setText("Please Select Save Path");
        msgBox.exec();
        return;
    }
    QDir dir(m_filePath);
    if(!dir.exists())
        dir.mkdir(m_filePath);
    emit SigStartRecord(m_filePath);
}

void MainWindow::on_pushButton_2_clicked()
{
    emit SigEndRecord();
}

void MainWindow::on_pushButton_3_clicked()
{
    if(m_filePath == "")
    {
        QMessageBox msgBox;
        msgBox.setText("Please Select Save Path");
        msgBox.exec();
        return;
    }
    QDir dir(m_filePath);
    if(!dir.exists())
        dir.mkdir(m_filePath);
    emit SigSnapshot(m_filePath);
}

void MainWindow::on_pushButton_4_clicked()
{
    emit Sigclose();
    close();
    QApplication:: quit();
     // pTimerRecv->start(50);
}

void MainWindow::on_pushButton_5_clicked()
{
    QString imagepath = QCoreApplication::applicationDirPath();
    imagepath+= "/123.txt";
    ReadFromFile(imagepath);
    if(m_cache.size() == 1)
        m_cache.append("");
    SettingDlg dlg;
    dlg.setValue(m_cache);
    dlg.exec();
    m_filePath = dlg.path;
    m_osdText = dlg.OSDText;
    m_cache.clear();
    m_cache.append(m_filePath);
    m_cache.append(m_osdText);
    WriteToFile(imagepath,m_cache);
    emit SigUpdateOSD(m_osdText);
}

void MainWindow::on_pushButton_6_clicked()
{
   setWindowState(Qt::WindowMinimized);
}

void MainWindow::on_PlayerBtn_clicked()
{
    PlayerDialog dia;
    dia.setPath(m_filePath);
    dia.exec();
//      QString strCurrentPath = QDir::homePath(); //获取系统当前目录
//       QString strDlgTitle = "选择视频文件";
//       QString strFilter = "MP4 File(*.mp4);;All File(*.*)";// 打开视频文件过滤
//       QString strAllFiles = QFileDialog::getOpenFileName(this,strDlgTitle,strCurrentPath,strFilter);

//       if(strAllFiles.isEmpty())
//       {
//           QMessageBox::information(this,"错误","打开视频文件失败，请重新检查",QMessageBox::Yes|QMessageBox::No);
//           return;
//       }


//       QFileInfo fileInfos(strAllFiles); // 获取文件信息
//       ui->label_2->setText(fileInfos.fileName());

//       player->setMedia(QUrl::fromLocalFile(strAllFiles));
//       player->play();
}

void MainWindow::updatetime()
{
    *TimeRecord = TimeRecord->addSecs(1);
     ui->lcdNumber->display(TimeRecord->toString("hh:mm:ss"));
}
void MainWindow::updatetime1()
{
    //获取当前时间
//    QDateTime currentDateTime = QDateTime::currentDateTime();

//    // 设置时间格式
//    // 例如: "yyyy-MM-dd hh:mm:ss" 表示 "年-月-日 时:分:秒"
//    QString format = "yyyy-MM-dd";
//    QString format1 = "hh:mm:ss";

//    // 将日期和时间转换为字符串
//    QString currentTimeString = currentDateTime.toString(format);
//    QString currentTimeString1 = currentDateTime.toString(format1);
//    emit SigUpdateOSD1(currentTimeString,currentTimeString1);
    if(m_tcp != nullptr)
    {
        m_tcp->write(m_data,12);
        //ui->textEdit->append("send success\n");
    }

}

void MainWindow::readyRead_Slot()
{
    pTimerRecv->start(50);
}
 void MainWindow::slot_serialport_delay_recv_timeout()
 {
   QByteArray Recv = m_tcp->readAll();
  //  ui->textEdit->append("recv success\n");
   QByteArray newdata;
   if(Recv.size() == 37)
   {
       newdata.append(Recv.at(31));
       newdata.append(Recv.at(32));
       newdata.append(Recv.at(29));
       newdata.append(Recv.at(30));

       QString ds = QString::fromUtf8(newdata);

       //QByteArray hexArray = QByteArray::fromHex(hexStr.toLatin1());
       float value; // 定义一个浮点数变量value
       //  memcpy(&value, data.constData(), sizeof(value));
       float dd = value;

       QDataStream stream(newdata);
       stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

       float result = 0.0;
       stream >> result;

//       QDataStream stream(&newdata, QIODevice::ReadOnly);
//       // stream.setByteOrder(QDataStream::LittleEndian);
//       float floatValue = 0.0f;

//       // 设置正确的数据流的方式来匹配你的浮点数的大小端
//       // 如果你的数据是大端序，则需要设置为QDataStream::BigEndian
//       // 如果是小端序，则设置为QDataStream::LittleEndian
//       stream.setByteOrder(QDataStream::LittleEndian);

//       // 读取浮点数
//       if (stream.atEnd()) {
//           qDebug() << "Error: Hex string is not long enough to represent a float.";
//       } else {
//           stream >> floatValue;
//       }
       QString text = QString::number(result,'f',1) + "ft";
       QDateTime currentDateTime = QDateTime::currentDateTime();

       // 设置时间格式
       // 例如: "yyyy-MM-dd hh:mm:ss" 表示 "年-月-日 时:分:秒"
       QString format = "yyyy-MM-dd";
       QString format1 = "hh:mm:ss";

       // 将日期和时间转换为字符串
       QString currentTimeString = currentDateTime.toString(format);
       QString currentTimeString1 = currentDateTime.toString(format1);
     //  emit SigUpdateOSD1(currentTimeString,currentTimeString1);
       emit SigUpdateOSD1(currentTimeString,currentTimeString1,text);
       //ui->lineEdit->setText(QString::number(result,'f',1));
      // ui->lineEdit_2->setText(QString::fromUtf8(Recv));
      // ui->textEdit->append(QString::fromUtf8(Recv) + "\n") ;
   }
 }

 void MainWindow::DisConnection_slot()
 {
     m_tcp->connectToHost(QHostAddress("192.168.1.5") , 502);
     ui->textEdit->append("connect failed \n");
 }

 void MainWindow::Connection_slot()
 {
  ui->textEdit->append("connect success \n");
 }


