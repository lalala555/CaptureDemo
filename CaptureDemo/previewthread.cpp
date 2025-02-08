#include "previewthread.h"
#include "QCAP.H"
#include <Windows.h>
#include "windows.h"
#include <QDateTime>
long long PreviewThread::number = 0;
void* PreviewThread::m_videoDevice = nullptr;
PreviewThread::PreviewThread()
{
    //    SROD_Player_Enable_Hardware_Acceleration(true);
    //    SROD_Media_SetGlobal(10, 5, 1, 5);
    //     m_PlayerID = SROD_Player_Init(2, p_wid);
    //      m_MediaHandle = SROD_Media_init(3,0,0,0, 0);
    //      int ret = SROD_Media_OpenStream(m_MediaHandle, m_PlayerID);
     //  int nRet = QCAP_CREATE(dvsName, 0, 0, &m_videoDevice, FALSE, FALSE);
}

void PreviewThread::startPreview(long long p_wid)
{    
//    SROD_Player_Enable_Hardware_Acceleration(true);
//    SROD_Media_SetGlobal(10, 5, 1, 5);
//     m_PlayerID = SROD_Player_Init(2, p_wid);
//      m_MediaHandle = SROD_Media_init(3,0,0,0, 0);
//      int ret = SROD_Media_OpenStream(m_MediaHandle, m_PlayerID);
    HRESULT hr = CoInitialize(nullptr);
    char dvsName[32] = "DC1150 USB";
    //  char dvsName[32] = "MZ0380 PCI";
    int nRet = QCAP_CREATE(dvsName, 0,(HWND)p_wid, &m_videoDevice);
    if (nRet != QCAP_RS_SUCCESSFUL)
    {
        m_videoDevice = nullptr;
        emit SigIsOpen(0);
        return;
    }
    QCAP_SET_VIDEO_STANDARD(m_videoDevice, QCAP_STANDARD_TYPE_PAL_B);


   // nRet = QCAP_SET_VIDEO_REGION_DISPLAY(m_videoDevice, 0, 0, 960, 582);
  // nRet = QCAP_SET_VIDEO_DEFAULT_OUTPUT_FORMAT(m_videoDevice, QCAP_COLORSPACE_TYPE_YUY2, 960, 582, false, 25);
    QCAP_RUN(m_videoDevice);
     emit SigIsOpen(1);
}

void PreviewThread::closePreview()
{
   // QCAP_STOP(m_videoDevice);
    if (m_videoDevice != nullptr)
       {
           //QCAP_STOP(m_videoDevice);
          QCAP_DESTROY(m_videoDevice);
           m_videoDevice = nullptr;
    }
}

void PreviewThread::startRecord(QString path)
{
    int ret = 0;
    path += "/" +  QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + ".mp4";
    std::string  dd = path.toStdString();

    const char *aa = dd.c_str();
     char * cc = const_cast<char*>(aa);
    ret = QCAP_SET_AUDIO_RECORD_PROPERTY( m_videoDevice, 0, QCAP_ENCODER_TYPE_SOFTWARE,QCAP_ENCODER_FORMAT_AAC ); //MP4 use AAC audio
    ret =QCAP_SET_VIDEO_RECORD_PROPERTY( m_videoDevice, 0, QCAP_ENCODER_TYPE_SOFTWARE,QCAP_ENCODER_FORMAT_H264,QCAP_RECORD_MODE_CBR, 8000,12 * 1024 * 1024,  20,0, 0, QCAP_DOWNSCALE_MODE_OFF ); //downscale off (1920x1080)
    ret = QCAP_START_RECORD( m_videoDevice, 0, cc);
    emit SigStartRecordStatus(ret);
}

void PreviewThread::closeRecord()
{
     int ret = QCAP_STOP_RECORD (m_videoDevice,0);
     emit SigEndRecordStatus(ret);
}

void PreviewThread::SnapShot(QString path)
{
    path += "/" +  QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + ".jpg";
    std::string  dd = path.toStdString();

    const char *aa = dd.c_str();
     char * cc = const_cast<char*>(aa);
     int ret = QCAP_SNAPSHOT_JPG( m_videoDevice, cc, 80 );
     emit SigSnapshotStatus(ret);
}

void PreviewThread::updateOSD(QString text)
{
   // m_mutex.lock();
     if (m_videoDevice != nullptr)
     {
         QStringList list = text.split(" ");
         int j = 0;
         for(int i = 2; i < list.size()+ 2; i++)
         {

             std::string  dd = list.at(j).toStdString();
             const char *aa = dd.c_str();
             char * cc = const_cast<char*>(aa);
             char bb[] = "Arial";
             QCAP_SET_OSD_TEXT( m_videoDevice,
             3+i,
             10, 90+50*j, 0, 0,
              cc, bb,
             QCAP_FONT_STYLE_REGULAR, 18,
                                0xFFFF0000,
                                0x00000000,
             128, 0, 0,
             QCAP_SEQUENCE_STYLE_FOREMOST);
             j++;
         }
       //    m_mutex.unlock();
//         std::string  dd = text.toStdString();

//         const char *aa = dd.c_str();
//         char * cc = const_cast<char*>(aa);
//         char bb[] = "Arial";
//         QCAP_SET_OSD_TEXT( m_videoDevice,
//         2,
//         50, 200, 0, 0,
//          cc, bb,
//         QCAP_FONT_STYLE_BOLD, 18,
//         0xFFFF0000,
//         0xFFFFFFFF,
//         128, 0, 0,
//         QCAP_SEQUENCE_STYLE_FOREMOST);
     }
}

void PreviewThread::updateOSD1(QString text, QString text1,QString text3)
{
    //   m_mutex.lock();
  //  if (m_videoDevice != nullptr)
    {
        std::string  dd2 = text3.toStdString();
        const char *aa2 = dd2.c_str();
        char * cc2 = const_cast<char*>(aa2);
        char bb2[] = "Arial";
        QCAP_SET_OSD_TEXT( m_videoDevice,
        0,
        10,550, 0, 0,
         cc2, bb2,
        QCAP_FONT_STYLE_REGULAR, 18,
                           0xFFFF0000,
                           0x00000000,
        128, 0, 0,
        QCAP_SEQUENCE_STYLE_FOREMOST);

        std::string  dd = text.toStdString();
        const char *aa = dd.c_str();
        char * cc = const_cast<char*>(aa);
        char bb[] = "Arial";
        QCAP_SET_OSD_TEXT( m_videoDevice,
        1,
        10, 10, 0, 0,
         cc, bb,
        QCAP_FONT_STYLE_BOLD, 18,
        0xFFFF0000,
        0x00000000,
        128, 0, 0,
        QCAP_SEQUENCE_STYLE_FOREMOST);

        std::string  dd1 = text1.toStdString();
        const char *aa1 = dd1.c_str();
        char * cc1 = const_cast<char*>(aa1);
        char bb1[] = "Arial";
        QCAP_SET_OSD_TEXT(m_videoDevice,
        2,
        10, 50, 0, 0,
         cc1, bb1,
        QCAP_FONT_STYLE_BOLD, 18,
        0xFFFF0000,
        0x00000000,
        128, 0, 0,
        QCAP_SEQUENCE_STYLE_FOREMOST);
    }
    //   m_mutex.unlock();
}

void PreviewThread::updateOSD2(QString text)
{
    //   m_mutex.lock();
    if (m_videoDevice != nullptr)
    {
            std::string  dd = text.toStdString();
            const char *aa = dd.c_str();
            char * cc = const_cast<char*>(aa);
            char bb[] = "Arial";
            QCAP_SET_OSD_TEXT( m_videoDevice,
            0,
            10,600, 0, 0,
             cc, bb,
            QCAP_FONT_STYLE_REGULAR, 18,
                               0xFFFF0000,
                               0x00000000,
            128, 0, 0,
            QCAP_SEQUENCE_STYLE_FOREMOST);
        }
     //     m_mutex.unlock();
}

QRETURN PreviewThread::callbackVideoPreview(PVOID pDevice, double dSampleTime, BYTE *pFrameBuffer, ULONG nFrameBufferLen, PVOID pUserData)
{
    if (nullptr == pUserData)
        return QCAP_RT_OK;
      number++;
      PreviewThread* obj = (PreviewThread*)pUserData;
     obj->callbackVideoPreview(number);
     return QCAP_RT_OK;
}

void PreviewThread::callbackVideoPreview(long long number)
{
     emit SigNum(number);
}

//QRETURN QCAP_EXPORT PreviewThread::callbackVideoPreview(PVOID pDevice /*IN*/, double dSampleTime /*IN*/, BYTE* pFrameBuffer /*IN*/, ULONG nFrameBufferLen /*IN*/, PVOID pUserData /*IN*/)
//{
//    if (nullptr == pUserData)
//        return QCAP_RT_OK;
//      number++;
//      emit SigNum(number);
////    QcapMediaSource* obj = (QcapMediaSource*)pUserData;
////    //log("media.log", " *************** data len %d\n", nFrameBufferLen);
////    obj->callbackVideoPreview(pDevice, dSampleTime, pFrameBuffer, nFrameBufferLen);
//    return QCAP_RT_OK;
//}
