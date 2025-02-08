#ifndef _SROD_MEDIA_API_H_
#define _SROD_MEDIA_API_H_
#include "SrodCallback.h"

/**
* @brief 修改源视频翻转效果
* @param type    [in]   //镜像  0:中心 1:左右 2:上下 3:无
* * @param p_mediaHanle    [in] 媒体源句柄
*/
SROD_C_API bool SROD_Media_SetVideoMirrorSource(const int type, long long p_playHandle);


/************************************** media **********************************************************************/
/**
* @brief 设置媒体全局参数
* @param sensitivitySec      [in] 断流检测的灵敏度值，单位：秒，默认10s
* @param timeoutSec          [in] 连接超时时间，单位：秒，默认5s
* @param p_autoReconnect     [in] 自动重连标志，0 - 不重连，非0 - 重连, 默认重连
* @param intervalSec         [in] 重连间隔，单位：秒，默认5s
* @note  可选
*/
SROD_C_API void SROD_Media_SetGlobal(int p_sensitivitySec, int p_timeoutSec, int p_autoReconnect, int p_intervalSec);


/**
* @brief 初始化媒体源
* @param p_ip       [in] ip地址
* @param p_user     [in] 用户名
* @param p_pwd      [in] 密码
* @param p_streamID [in] 码流ID，从 0 开始
* @return 操作成功，返回media句柄，失败返回 <= 0
*/
SROD_C_API long long SROD_Media_init(int p_type, const char* p_ip, const char* p_user, const char* p_pwd, int p_streamID);

/**
* @brief 释放媒体源
* @param p_mediaHanle       [in] 媒体源句柄
*/
SROD_C_API void SROD_Media_uninit(long long p_mediaHanle);

/**
* @brief usb摄像头释放一个消费者
* @param p_mediaHanle       [in] 媒体源句柄
*/
SROD_C_API void SROD_Media_uninitone(long long p_mediaHanle);

/**
* @brief 打开视频流
* @param p_mediaHanle    [in] 媒体源句柄
* @param p_playHandle    [in] 播放器ID
*/
SROD_C_API int SROD_Media_OpenStream(long long p_mediaHanle, long long p_playHandle);

/**
* @brief 关闭视频流
* @param p_mediaHanle    [in] 媒体源句柄
* @param p_playHandle    [in] 播放器ID
*/
SROD_C_API int SROD_Media_CloseStream(long long p_mediaHanle, long long p_playHandle);


#endif //_SROD_MEDIA_API_H_
