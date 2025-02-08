#ifndef _SROD_CALLBACK_H_
#define _SROD_CALLBACK_H_


#if (defined _WIN32 || defined _WIN64)
    #define CALLBACK __stdcall
    #define STDCALL __stdcall
#else
    #define CALLBACK
    #define STDCALL
#endif

#ifndef SROD_C_API
    #define SROD_C_API  extern "C" __declspec(dllexport)
#endif


/**
* @brief 授权库回调原型
* @param pUser [in]:用户数据
* @param type [in]:回调消息类型，详见SrodCallBack
* @param error [in]:错误码，详见SrodError
* @param pInParam [in]:回调数据缓冲区，具体数据格式由type确定
* @param inLength [in]:回调缓冲区长度
* @param pOutParam [out]:输出数据缓冲区
* @param outLength [out]:输出缓冲区长度，当长度不足时填写需要的长度，并且回调函数要返回错误
* @return int: 返回值，详见SrodError
*/
typedef int (CALLBACK* lpLicenseCallback)(
    void* pUser,
    int type,
    int error,
    void* pInParam,
    int inLength,
    void* pOutParam,
    int* outLength
);


/**
* @brief 设备库回调原型
* @param pUser [in]:用户数据
* @param type [in]:回调消息类型，详见SrodCallBack
* @param error [in]:错误码，详见SrodError
* @param pInParam [in]:回调数据缓冲区，具体数据格式由type确定
* @param inLength [in]:回调缓冲区长度
* @param pOutParam [out]:输出数据缓冲区
* @param outLength [out]:输出缓冲区长度，当长度不足时填写需要的长度，并且回调函数要返回错误
* @return int: 返回值，详见SrodError
*/
typedef int (CALLBACK* lpDeviceCallback)(
    void* pUser,
    int type,
    int error,
    void* pInParam,
    int inLength,
    void* pOutParam,
    int* outLength
);



/**
* @brief 媒体库回调原型
* @param pUser [in]:用户数据
* @param handle [in]:句柄
* @param type [in]:回调消息类型，详见SrodCallBack
* @param error [in]:错误码，详见SrodError
* @param pInParam [in]:回调数据缓冲区，具体数据格式由type确定
* @param inLength [in]:回调缓冲区长度
* @param pOutParam [out]:输出数据缓冲区
* @param outLength [out]:输出缓冲区长度，当长度不足时填写需要的长度，并且回调函数要返回错误
* @return int: 返回值，详见SrodError
*/
typedef int (CALLBACK* lpMediaCallback)(
    void* pUser,
    int handle,
    int type,
    int error,
    void* pInParam,
    int inLength,
    void* pOutParam,
    int* outLength
);



/**
* @brief 回放库回调原型
* @param pUser [in]:用户数据
* @param handle [in]:句柄
* @param type [in]:回调消息类型，详见SrodCallBack
* @param error [in]:错误码，详见SrodError
* @param pInParam [in]:回调数据缓冲区，具体数据格式由type确定
* @param inLength [in]:回调缓冲区长度
* @param pOutParam [out]:输出数据缓冲区
* @param outLength [out]:输出缓冲区长度，当长度不足时填写需要的长度，并且回调函数要返回错误
* @return int: 返回值，详见SrodError
*/
typedef int (CALLBACK* lpMediaPlaybackCallback)(
    void* pUser,
    int handle,
    int type,
    int error,
    void* pInParam,
    int inLength,
    void* pOutParam,
    int* outLength
);



/**
* @brief PV库回调原型
* @param pUser [in]:用户数据
* @param handle [in]:句柄
* @param type [in]:回调消息类型，详见SrodCallBack
* @param error [in]:错误码，详见SrodError
* @param pInParam [in]:回调数据缓冲区，具体数据格式由type确定
* @param inLength [in]:回调缓冲区长度
* @param pOutParam [out]:输出数据缓冲区
* @param outLength [out]:输出缓冲区长度，当长度不足时填写需要的长度，并且回调函数要返回错误
* @return int: 返回值，详见SrodError
*/
typedef int (CALLBACK* lpPipeVideoCallback)(
    void* pUser,
    int handle,
    int type,
    int error,
    void* pInParam,
    int inLength,
    void* pOutParam,
    int* outLength
);

/**
* @brief media库播放状态回调原型
* @param handle [in]:句柄
* @param error [in]:错误码，详见SrodError
* @param pUser [in]:用户数据
*/
typedef void(CALLBACK* lpMediaStatusCallback)(long long handle, int error, void* pUser);

/**
* @brief media库回放状态回调原型
* @param status [in]:录像状态，详见SrodRecordStatus
* @param error [in]:错误码，详见SrodError
* @param timestamp [in]:录像时间
* @param pUser [in]:用户数据
*/
typedef void(CALLBACK* lpRecordStatusCallback)(int status, int error, long long timestamp, void* dwUser);

/**
* @brief 设备连接状态回调
* @param status [in]:tcp连接状态，0未连接 1连接上
* @param error [in]:错误码，详见SrodError
* @param pUser [in]:用户数据
*/
typedef void(CALLBACK* lpDeviceConnectCallback)(int status, int error, void* dwUser);

/**
* @brief 手柄数据回调
* @param type [in]:回调消息类型，详见SrodCallBack
* @param pOutParam [out]:输出数据缓冲区
* @param outLength [out]:输出缓冲区长度，当长度不足时填写需要的长度，并且回调函数要返回错误
* @param pUser [in]:用户数据
* @return int: 返回值，详见SrodError
*/
typedef int (CALLBACK* lpJoystickCallback)(int type, void* pOutParam, int* outLength, void* pUser);

/**
* @brief wincanVX数据回调
* @param type [in]:回调消息类型，详见SrodCallBack
* @param pOutParam [out]:输出数据缓冲区
* @param outLength [out]:输出缓冲区长度，当长度不足时填写需要的长度，并且回调函数要返回错误
* @param pUser [in]:用户数据
* @return int: 返回值，详见SrodError
*/
typedef int (CALLBACK* lpWincanVXCallback)(void* pOutParam, int* outLength, void* pUser);

/**
* @brief Posm数据回调
* @param type [in]:回调消息类型，详见SrodCallBack
* @param pOutParam [out]:输出数据缓冲区
* @param outLength [out]:输出缓冲区长度，当长度不足时填写需要的长度，并且回调函数要返回错误
* @param pUser [in]:用户数据
* @return int: 返回值，详见SrodError
*/
typedef int (CALLBACK* lpPosmCallback)(const char* buf, int size);

#endif //_SROD_CALLBACK_H_

