#ifndef PREVIEWTHREAD_H
#define PREVIEWTHREAD_H

#include <QObject>
#include "QCAP.H"
#include "windows.h"
#include "SrodMediaApi.h"
#include "SrodPlayerApi.h"
#include <QMutex>

class PreviewThread: public QObject
{
    Q_OBJECT
public:
    PreviewThread();
signals:
    void SigNum(long long number);
    void SigStartRecordStatus(int ret);
    void SigEndRecordStatus(int ret);
    void SigSnapshotStatus(int ret);
    //0 没有打开 1 打开
    void SigIsOpen(int ret);
public slots:
    void startPreview(long long p_wid);
    void closePreview();
    void startRecord(QString path);
    void closeRecord();
    void SnapShot(QString path);
    void updateOSD(QString text);
    void updateOSD1(QString text, QString text1, QString text3);
     void updateOSD2(QString text);
private:
     static QRETURN QCAP_EXPORT callbackVideoPreview(PVOID pDevice /*IN*/, double dSampleTime /*IN*/, BYTE* pFrameBuffer /*IN*/, ULONG nFrameBufferLen /*IN*/, PVOID pUserData /*IN*/);
     void callbackVideoPreview(long long number);
private:
   static void*               m_videoDevice;
    static long long number ;
    long long m_PlayerID = 0;
    long long m_MediaHandle = 0;
    QMutex m_mutex;
};

#endif // PREVIEWTHREAD_H
