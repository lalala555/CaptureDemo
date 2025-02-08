#ifndef _SROD_PLAYER_API_H_
#define _SROD_PLAYER_API_H_
#include "SrodCallback.h"

/************************************** player **********************************************************************/
/**
* @brief 设置播放器硬件加速
* @param enable [in] 0 表示不启用硬件加速，非0 表示启用硬件加速
* @note 系统默认不启用硬件加速
*/
SROD_C_API void SROD_Player_Enable_Hardware_Acceleration(int p_enable);

/**
* @brief 初始化播放器（窗口方式）
* @param p_deviceType [in] 设备类型 1数字 2模拟
* @param playWnd [in] 播放窗口句柄
* @return 返回播放器ID
*/
SROD_C_API long long SROD_Player_Init(int p_deviceType, long long p_playWnd);

/**
* @brief 初始化预览播放器（窗口方式）
* @param playWnd [in] 播放窗口句柄
* @param p_playHandle [in] 播放器ID
*/
SROD_C_API void SROD_Preview_Init(long long p_playHandle, long long p_playWnd);

/**
* @brief 关闭预览播放器（窗口方式）
* @param playWnd [in] 播放窗口句柄
* @param p_playHandle [in] 播放器ID
*/
SROD_C_API void SROD_Preview_UnInit(long long p_playHandle);

/**
* @brief 后视暂时关闭/开启
* @param playWnd [in] 播放窗口句柄
* @param p_playHandle [in] 播放器ID
*/
SROD_C_API void SROD_RearCamera_Show(long long p_playHandle, bool flag);

/**
* @brief 反初始化播放器
* @param p_playHandle [in] 播放器ID
*/
SROD_C_API void SROD_Player_Uninit(long long p_playHandle);

/**
* @brief 设置播放状态回调
* @param p_playHandle [in] 播放器ID
* @param p_cbStatus   [in] 状态回调
* @param p_user       [in] 用户数据
*/
SROD_C_API void SROD_Player_SetCBPlayStatus(long long p_playHandle, lpMediaStatusCallback p_cbStatus, void* p_user);

/**
* @brief 窗口拉伸
* @param p_playHandle [in] 播放器ID
* @param p_bStretch   [in] 拉伸标志
* @note true表示拉伸播放，false表示原比例播放
*/
SROD_C_API void SROD_Player_SetStretch(long long p_playHandle, int p_bStretch);

/**
* @brief 窗口大小调整
* @param p_playHandle [in] 播放器ID
* @param p_width      [in] 宽
* @param p_height     [in] 高
*/
SROD_C_API void SROD_Player_ResizeWindow(long long p_playHandle, int p_width, int p_height);

/**
* @brief 打开音频播放
* @param p_playHandle    [in] 播放器ID
*/
SROD_C_API int SROD_Player_AudioOn(long long p_playHandle);

/**
* @brief 关闭音频播放
* @param p_playHandle    [in] 播放器ID
*/
SROD_C_API int SROD_Player_AudioOff(long long p_playHandle);

/**
* @brief 设置OSD
* @param p_playHandle [in] 播放器句柄
* @param p_videoOSD   [in] 序列化的VideoOSD
* @param p_len        [in] p_videoOSD数据长度
*/
SROD_C_API int SROD_Player_SetOSD(long long p_playHandle, void* p_videoOSD, int p_len);

/**
* @brief 设置OSD原窗口大小
* @param p_playHandle [in] 播放器句柄
* @param p_width      [in] 原窗口宽
* @param p_height     [in] 原窗口高
*/
SROD_C_API int SROD_Player_SetOSDWindow(long long p_playHandle, int p_width, int p_height);

/**
* @brief 修改OSD
* @param p_playHandle [in] 播放器句柄
* @param p_osdType    [in] 详见VIDEO_OSD_TYPE
* @param p_osdName    [in] osd名称
* @param p_newText    [in] 修改后的内容
*/
SROD_C_API int SROD_Player_ModifyOSD(long long p_playHandle, int p_osdType, const char* p_osdName, const char* p_newText);

/**
* @brief OSD启禁
* @param p_playHandle [in] 播放器句柄
* @param p_osdType    [in] 详见VIDEO_OSD_TYPE
* @param p_disable    [in] 0 - 禁用，非0 - 启用
*/
SROD_C_API int SROD_Player_DisableOSD(long long p_playHandle, int p_osdType, int p_disable);

/**
* @brief 开始录像
* @param p_playHandle [in] 播放器句柄
* @param p_file       [in] 录像文件名称，utf8
* @param p_cbFunc     [in] 录像状态回调
* @param p_dwUser     [in] 用户数据
*/
SROD_C_API int SROD_Player_StartRecord(long long p_playHandle, const char* p_file, lpRecordStatusCallback p_cbFunc, void* p_dwUser);

/**
* @brief 录像暂停/继续
* @param p_playHandle  [in] 播放器句柄
* @param p_pause       [in] 暂停控制，非0 - 暂停，0 - 继续
*/
SROD_C_API int SROD_Player_PauseRecord(long long p_playHandle, int p_pause);

/**
* @brief 录像停止
* @param p_playHandle      [in] 播放器句柄
* @param p_forceStop       [in] 强制停止，非0 - 强制，0 - 不强制
*/
SROD_C_API int SROD_Player_StopRecord(long long p_playHandle, int p_forceStop);

/**
* @brief 抓拍
* @param p_playHandle      [in] 播放器句柄
* @param p_file            [in] 抓拍文件名称，含路径
*/
SROD_C_API int SROD_Player_Snapshot(long long p_playHandle, const char* p_file);


SROD_C_API int SROD_Player_GetDuration(const char* p_file, long long* p_duration, unsigned char* p_data);

//硬件解码mediaint---测试代码
SROD_C_API int SROD_HWMedia_Init(const char* p_file, long long* p_duration, unsigned char* p_data);


#endif //_SROD_PLAYER_API_H_
