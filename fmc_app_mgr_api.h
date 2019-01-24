/******************************************************************************
**  Copyright (C) 2015 Flaircomm Microelectronics, Inc.
**
** File Name:
**      fmc_app_msg_api.h
** File Description:
**      This file contains  App Manager  API functions.
** File History:
**-----------------------------------------------------------------------------
**  Ver   Date         Author           Description
**-----------------------------------------------------------------------------
**  1.0   08/27/2016   ChenMH           First Release
*******************************************************************************/


#ifndef _FMC_APP_MGR_API_H_
#define _FMC_APP_MGR_API_H_
/******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************
             INCLUDE FILES SECTION
******************************************************************************/
#include "fmc_api_type.h"
#include "fmc_sdk_api.h"


/******************************************************************************
             GLOBAL EXPORTED TYPE, CONSTANT, MACRO DEFINITIONS SECTION
******************************************************************************/

#define FMC_BT_APP_VALID                    FALSE
#define FMC_TSP_APP_VALID                   TRUE

#define FMC_TSP_APP_MGR_API                 extern
typedef void (* FMC_APP_ALARM_CB_FUNC)(void);
typedef enum
{
    MGR_TIMER_START = 0,
    MGR_APP_TSP_PERIOD_TIMER = MGR_TIMER_START,
    MGR_APP_TSP_VEH_CTRL_TIMER,     /* 控车超时timer */
    MGR_APP_BT_PERIOD_TIMER = 5,    /* 预留一段给tsp扩充 */
    //MGR_QUEUE_TIMER,
    MGR_TIMER_END
} FmcAppMgrTimer_e;

#define E_APP_MGR_BT_BOOKINGID_MAX      5       /* todo待确认有多少钥匙 */
#define E_APP_MGR_BT_BOOKINGID_FULL     0x1F    /* 和E_APP_MGR_BT_BOOKINGID_MAX耦合 */
typedef enum
{
    E_APP_BT_BKID_AUTHORITY_FULL = 0,   /* full authority */
    E_APP_BT_BKID_AUTHORITY_DOOR_ONLY,  /* 门 */
    E_APP_BT_BKID_AUTHORITY_BOOT_ONLY,  /* 后备箱 */
    E_APP_BT_BKID_PER_UNKNOWN,          /* 其它值：无效 */
} FmcAppParaBtBkIdPermission_e;
typedef struct
{
    UINT8 u8KeyType;                    /* 0 - Rescue, 1 - Temporary */
    UINT8 u8KeyValue[16];               /* Key used during the challenge process */
    UINT8 u8AESKey[16];                 /* AES key used to secure the Bluetooth access communications */
    UINT32 u32BookingId;                /* 大端Unique Key reference(booking ID) to the key function, */
    UINT32 u32StartTime;                /* 密钥开始时间 utc存储 */
    UINT32 u32StopTimer;                /* 密钥结束时间 utc存储 */
    UINT8 u8UserAuthority;              /* 权限 FmcAppParaBtBkIdPermission_e */
} FmcAppParaBtBookingIdInfo_t;

/* 写入蓝牙钥匙返回结果 */
typedef enum
{
    E_APP_BT_BKID_WR_PARA_ERR = 0,      /* 0: Message validity failure */
    E_APP_BT_BKID_WR_IS_MAX,            /* 1：操作失败，原因为钥匙个数达到上限 */
    E_APP_BT_BKID_WR_IS_EXISTS,         /* 2：操作失败，原因为钥匙已存在 */
    E_APP_BT_BKID_WR_MODULE_ERR,        /* 3：操作失败，原因为蓝牙模块错误 */
    E_APP_BT_BKID_WR_SUCCESS            /* 4：操作成功 */
} FmcAppParaBtBookingIdWr_e;

/* 删除蓝牙钥匙返回结果 */
typedef enum
{
    E_APP_BT_BKID_DEL_PARA_ERR = 0,     /* 0：Message validity failure */
    E_APP_BT_BKID_DEL_UN_EXISTS,        /* 1：操作失败，原因为钥匙不存在 */
    E_APP_BT_BKID_DEL_IS_USING,         /* 2：操作失败，原因为钥匙正在使用中 */
    E_APP_BT_BKID_DEL_MODULE_ERR,       /* 3：操作失败，原因为蓝牙模块错误 */
    E_APP_BT_BKID_DEL_SUCCESS           /* 4：操作成功 */
} FmcAppParaBtBookingIdDel_e;

/* 查询蓝牙钥匙返回结果 */
typedef enum
{
    E_APP_BT_BKID_QUERY_SUCCESS = 0,    /* 0：操作成功 */
    E_APP_BT_BKID_QUERY_ERR,            /* 1：操作失败*/
    E_APP_BT_BKID_QUERY_UNKNOWN         /* 5：操作失败，原因为其它错误 */
} FmcAppParaBtBookingIdQuery_e;


/******************************************************************************
             GLOBAL EXPORTED VARIABLES DECLARATIONS SECTION
******************************************************************************/


/******************************************************************************
             TSP GLOBAL EXPORTED FUNCTIONS DECLARATIONS SECTION
******************************************************************************/
FMC_TSP_APP_MGR_API void FmcAppMgrTmStart(FMC_APP_ALARM_CB_FUNC
                                          pCbTimer,
                                          FmcAppMgrTimer_e eTimer,
                                          BOOL bPeriodic, UINT16 u16Res);
FMC_TSP_APP_MGR_API void FmcAppMgrTmStop(FmcAppMgrTimer_e eTimer);
FMC_TSP_APP_MGR_API UINT16 FmcAppUtilToBigU16Int(void *FMC_FAR pBuf);
FMC_TSP_APP_MGR_API UINT32 FmcAppUtilToBigU32Int(void *FMC_FAR pBuf);
FMC_TSP_APP_MGR_API void FmcAppUtilU32IntToBuf(UINT32 u32Val,
                                               void *FMC_FAR pBuf);
FMC_TSP_APP_MGR_API void FmcAppUtilUtilBinary2Hex(FmcOsStrPtr_t pInData,
                                                  FmcOsStrPtr_t pOutData,
                                                  UINT16 u16OutLen,
                                                  UINT16 u16InLen);
FMC_TSP_APP_MGR_API void FmcAppUtilUtilHex2Binary(FmcOsStrPtr_t pData,
                                                  FmcOsStrPtr_t outData,
                                                  UINT16 len);


/******************************************************************************
             TSP GLOBAL EXPORTED FUNCTIONS DECLARATIONS SECTION
******************************************************************************/
FMC_TSP_APP_MGR_API BOOL FmcAppTspL2Init(void);
FMC_TSP_APP_MGR_API BOOL FmcAppTspDispInit(void);
FMC_TSP_APP_MGR_API BOOL FmcAppTspDispSleep(void);
FMC_TSP_APP_MGR_API BOOL FmcAppTspDispWakeup(void);
FMC_TSP_APP_MGR_API BOOL FmcAppTspDispIsBusy(void);

/******************************************************************************
             BT GLOBAL EXPORTED FUNCTIONS DECLARATIONS SECTION
******************************************************************************/
FMC_TSP_APP_MGR_API BOOL FmcAppBtL2Init(void);
FMC_TSP_APP_MGR_API BOOL FmcAppBtDispInit(void);
FMC_TSP_APP_MGR_API BOOL FmcAppBtDispSleep(void);
FMC_TSP_APP_MGR_API BOOL FmcAppBtDispWakeup(void);
FMC_TSP_APP_MGR_API BOOL FmcAppBtDispIsBusy(void);
FMC_TSP_APP_MGR_API UINT32 FmcAppBtDispGetUsingBookingId(void);
FMC_TSP_APP_MGR_API BOOL FmcAppBtDispWriteBookingId(FmcApiBookId_t tBkid);
FMC_TSP_APP_MGR_API BOOL FmcAppBtDispDeleteBookingId(FmcApiBookId_t tBkid);

FMC_TSP_APP_MGR_API UINT8 FmcAppParaBtQueryBookingId(UINT32 u32Bkid);
FMC_TSP_APP_MGR_API FmcAppParaBtBookingIdWr_e FmcAppParaBtWriteBookingId(
    FmcAppParaBtBookingIdInfo_t *FMC_FAR ptBkId);
FMC_TSP_APP_MGR_API FmcAppParaBtBookingIdDel_e FmcAppParaBtDeleteBookingId(
    UINT32 u32BkId);
FMC_TSP_APP_MGR_API UINT8 FmcAppParaBtReadListBookingId(FmcOsStrPtr_t pGetBkid);
FMC_TSP_APP_MGR_API FmcAppParaBtBookingIdInfo_t * FMC_FAR FmcAppParaBtGetBookingIdInfo(
    UINT32 u32Bkid);



/******************************************************************************
             CAN GLOBAL EXPORTED FUNCTIONS DECLARATIONS SECTION
******************************************************************************/
/* 车控相关定义 */

/* Auth State */
#define VC_CAN_TBOX_TO_BCM_AUTH_REQUEST     0x01
#define VC_CAN_BCM_TO_TBOX_AUTH_CHALLENGE   0x02
#define VC_CAN_TBOX_TO_BCM_AUTH_RESPONSE    0x03
#define VC_CAN_BCM_TO_TBOX_AUTH_PASSED      0x04
#define VC_CAN_BCM_TO_TBOX_AUTH_FAILED      0x05
#define VC_CAN_BCM_TO_TBOX_AUTH_UPDATE      0x06
#define VC_CAN_TBOX_TO_BCM_AUTH_COMPLETE    0x07

/* Request Type*/
#define VC_REQ_TYPE_FIND_MY_CAR             0x00
#define VC_REQ_TYPE_VEHICLE_LOCK            0x01
#define VC_REQ_TYPE_VEHICLE_UNLOCK          0x02
#define VC_REQ_TYPE_WINDOW_CONTROL          0x03
#define VC_REQ_TYPE_KEY_MANAGEMENT          0x04
#define VC_REQ_TYPE_HEADED_SEAT_CONTROL     0x05
#define VC_REQ_TYPE_CLIMATE_CONTROL         0x06
#define VC_REQ_TYPE_ENGINE_CONTROL          0x11
#define VC_REQ_TYPE_BT_ENGINE_CONTROL       0x12

/* BCMRequestStatus */
#define VC_REQ_STA_PENDING                  0x01
#define VC_REQ_STA_ACTIVE                   0x02
#define VC_REQ_STA_COMPLETED                0x03
#define VC_REQ_STA_FAILED                   0xF0

/* CMRequestFailReason */
#define VC_REQ_REASION_NONE                 0x00
#define VC_REQ_REASION_PWMD_NO_OFF          0x01  /* Power mode !== OFF */

#define BT_ENABLE                           0x01
#define RC_ENABLE                           0x02

/* 远程控制回调 */
typedef BOOL (* FmcSaicMaxusCanCtrlCb)(FmcOsMsgPtr_t);


/* Tbox Request Params*/
/* Request Parameters of FindMyCar*/
typedef struct
{
    WORD   Lights      : 2; //0=Off,1=Dipped bean and Di's Flashing, 2-3=Reserved.
    WORD   Reserved1   : 6;
    //8
    WORD   Horn        : 2; //0=Off,1=Cycle1(Low),2=Cycle2(High),3=Reserved.
    WORD   Reserved2   : 6;
    //16
    WORD   Time        : 4; //Time in 30 secs increments.
    WORD   Reserved3   : 4;
    //24
    UINT8   Res4[2];
    //40
} ParamFindMyCar_t;

/* Request Parameters of Lock*/
typedef struct
{
    /* Byte No.1-5 */
    //Reserved.
    UINT8    Reserved[5];
} ParamLock_t;

/* Request Parameters of Unlock*/
typedef struct
{
    /* Byte No.1 */
    //Silent Unlock Flag:0=Off,1=On,2=Cancel,3=Reserved.
    WORD   bit2SilentUnlockFlag        : 2;
    //Reserved.
    WORD   Reserved1                   : 2;
    //Silent Unlock Timer:0=Off,1-15=timer(mins).
    WORD   bit4SilentUnlockTimer       : 4;

    /* Byte No.2 */
    //PowerMode Override Flag:0=Disable,1=Enable.
    WORD   bit2PowerModeOverrideFlag   : 2;
    //Door to Unlock:0=None,1=Reserved,2=Boot Only, 3=All Doors.
    WORD   bit2DoorsToUnlock           : 2;
    //Reserved.
    WORD   Reserved2                   : 4;

    /* Byte No.3-5 */
    //Reserved.
    UINT8   Reserved3[3];
} ParamUnlock_t;

typedef struct
{
    /* Byte No.1 */
    //Engine Request Type:0=stop, 1=start, 2=Reserved, 3=Reserved
    WORD engineReqType    : 2;
    //Reserved
    WORD Reserved1        : 6;
    UINT8 Reserved2[4];
} ParamEngine_t;

typedef struct
{
    /* Byte No.1 */
    //Key Request Type:0=stop, 1=start, 2=Reserved, 3=Reserved
    WORD keyReqType    : 2;
    //Reserved
    WORD Reserved1     : 6;
    UINT8 keyId[2];
    UINT8 Reserved2[2];
} ParamKeyManagement_t;

typedef struct
{
    /* Byte No.1 */
    WORD seatFrontLeftValid   : 4;
    WORD seatFrontLeft        : 4;
    /* Byte No.2 */
    WORD seatFrontRightValid  : 4;
    WORD seatFrontRight       : 4;
    //Reserved
    UINT8 Reserved[3];
} ParamSeatHeat_t;


typedef struct
{
    /* Byte No.1 */
    UINT8 climateValid;
    /* Byte No.2 */
    UINT8 climateType;
    /* Byte No.3 */
    UINT8 climateTargetTemp;
    // Byte No.4 */
    UINT8 climateCancel;
    //Reserved
    UINT8 Reserved;
} ParamClimate_t;
/* Request Paramenter */
typedef union
{
    ParamFindMyCar_t       tFindMyCar;
    ParamLock_t            tLock;
    ParamUnlock_t          tUnlock;
    ParamEngine_t          tEngine;
    ParamSeatHeat_t        tSeat;
    ParamClimate_t         tClimate;
    ParamKeyManagement_t   tKeyManagement;
} TboxRequestParams_u;
/* RC_CAN_TBOX_TO_BCM_AUTH_REQUEST */
typedef struct
{
    UINT8                   u8Cmd;  /* byte0 Auth State */
    UINT8                   u8Id;   /* byte1 RequestId */
    UINT8                   u8Type; /* byte2 RequestType */
    TboxRequestParams_u     uParams;
} FmcCanTboxAuthRequest_t;
typedef struct
{
    UINT8                   u8Cmd;  /* byte0 Auth State */
    UINT8                   u8Id;   /* byte1 RequestId */
    UINT8                   u8Sta;  /* byte2 RequestStatus */
    UINT8                   u8FailReason;   /* byte3 RequestFailReason */
} FmcCanTboxAuthResponse_t;
typedef struct
{
    UINT8                   TODO;//TODO
} FmcCanTboxAuthComplete_t;
/* TBOX --> BCM command structure */
typedef union
{
    FmcCanTboxAuthRequest_t     tRequest;   //Auth State 01
    FmcCanTboxAuthResponse_t    tResponse;  //Auth State 03
    FmcCanTboxAuthComplete_t    tComplete;  //Auth State 07
} FmcCanTboxToBcmCmd_u;





/******************************************************************************/
#ifdef __cplusplus  // close out "C" linkage in case of c++ compiling
}
#endif


/******************************************************************************/
#endif /* _FMC_APP_MGR_API_H_ */
