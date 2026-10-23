#pragma once

#ifdef __linux__
// Linuxƽ̨��GT_API�Ķ���
#define GT_API extern "C" short
typedef void* HANDLE;
/*
Windowsƽ̨�£����ֺ���ʹ����long�������͵ĺ�������
��linuxƽ̨�£���Щ������long���Ͳ�����Ϊint32_t����
Linuxƽ̨ʹ��ϵͳ�ṩ��stdint.hͷ�ļ�������int32_t
*/
#include <stdint.h>

typedef int64_t __int64;
#else
// Windowsƽ̨��GT_API�Ķ���
#define GT_API extern "C" short __stdcall
#include "windows.h"
#endif

/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*                        ��׼�������ܺ���                                */
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

/*-----------------------------------------------------------*/
/* GVN���ٺ˺�ͨ�ú˺궨��                                    */
/*-----------------------------------------------------------*/
#define GP_CORE                  (1)
#define HS_CORE                  (2)

/*-----------------------------------------------------------*/
/* Channel of Command                                        */
/*-----------------------------------------------------------*/
#define CHANNEL_HOST                   (0)
#define CHANNEL_UART                   (1)
#define CHANNEL_SIM                    (2)
#define CHANNEL_ETHER                  (3)
#define CHANNEL_RS232                  (4)
#define CHANNEL_PCIE                   (5)
#define CHANNEL_RINGNET                (6)

/*-----------------------------------------------------------*/
/* Error Code                                                */
/*-----------------------------------------------------------*/
#define CMD_SUCCESS                     (0)

#define CMD_ERROR_READ_LEN              (-2)     /* ��ȡ���ݳ��ȴ��� */
#define CMD_ERROR_READ_CHECKSUM         (-3)     /* ��ȡ����У��ʹ��� */

#define CMD_ERROR_WRITE_BLOCK           (-4)     /* д�����ݿ���� */
#define CMD_ERROR_READ_BLOCK            (-5)     /* ��ȡ���ݿ���� */

#define CMD_ERROR_OPEN                  (-6)     /* ���豸���� */
#define CMD_ERROR_CLOSE                 (-6)     /* �ر��豸���� */
#define CMD_ERROR_DSP_BUSY              (-7)     /* DSPæ */

#define CMD_LOCK_ERROR                  (-8)     /* ���߳���Դæ */
#define CMD_DMA_ERROR                   (-9)     /* DMA������� */
#define CMD_COMM_ERROR                  (-10)    /* pcieͨѶʧ�� */
#define CMD_LOAD_RINGNET_DLL_ERROR      (-11)    /* �Ȼ��������ʧ�� */
#define CMD_RINGNET_STIME_ERROR         (-12)    /* �Ȼ��������ʧ�� */

#define CMD_RINGNET_ENC0_ERROR          (-13)    /* core1��������ʼ��ʧ�� */

#define CMD_RINGNET_ENC1_ERROR          (-14)    /* core2��������ʼ��ʧ�� */

#define CMD_LOAD_RINGNET_ERROR          (-17)    /* �Ȼ�����API����ʧ�� */
#define CMD_MCVERSION_MATCH_ERROR       (-15)    /* �Ȼ���ƥ��ʧ�ܣ���Ҫ���¿� */
#define CMD_LOCK_NULL                   (-20)    /* ���̱߳����򿪾��ʧ�� */
#define CMD_MCVERSION_MATCH_WARNING     (15)     /* �˿ذ汾ƥ��ʧ�ܣ�ĳЩ���ܲ��߱� */
#define CMD_DSPVERSION_MATCH_WARNING    (16)     /* �˿�DSP�汾����,���߱��汾ƥ�书�� */

#define CMD_FILE_MATCH_WARNING          (17)     /* �����ļ���ʽ�����ڲ�ƥ�� */

#define CMD_ERROR_EXECUTE               (1)
#define CMD_ERROR_VERSION_NOT_MATCH     (3)
#define CMD_ERROR_PARAMETER             (7)
#define CMD_ERROR_UNKNOWN               (8)      /* unspported command */

#define MC_NONE                         (-1)

#define MC_LIMIT_POSITIVE               (0)
#define MC_LIMIT_NEGATIVE               (1)
#define MC_ALARM                        (2)
#define MC_HOME                         (3)
#define MC_GPI                          (4)
#define MC_ARRIVE                       (5)
#define MC_EGPI0                        (6)
// #define MC_EGPI1                     (7)
// #define MC_EGPI2                     (8)
#define MC_MPG                          (9)

#define MC_ENABLE                       (10)
#define MC_CLEAR                        (11)
#define MC_GPO                          (12)
// #define MC_EGPO0                     (13)
// #define MC_EGPO1                     (14)
#define MC_AU_ADC                       (17)
#define MC_HSO                          (18)
#define MC_AU_DAC                       (19)


#define MC_DAC                          (20)
#define MC_STEP                         (21)
#define MC_PULSE                        (22)
#define MC_ENCODER                      (23)
#define MC_ADC                          (24)

#define MC_AU_ENCODER                   (26)

#define MC_ABS_ENCODER                  (29)

#define MC_AXIS                         (30)
#define MC_PROFILE                      (31)
#define MC_CONTROL                      (32)
#define MC_ACTVEL                       (33)
#define MC_PRF_VEL                      (34)
#define MC_PRF_POS                      (35)
#define MC_CRD                          (36)
#define MC_DR_FOLLOW_ERROR              (37) // ��������ĸ������
#define MC_COMBINE_AXES                 (38)
#define MC_SERVO_READY                  (39) //�ŷ�ʹ������ź�
#define MC_TRIGGER                      (40)

#define MC_AU_TRIGGER                   (44)
#define MC_SERVO_READY_TO_SWITCH_ON     (49) //�ŷ�׼�������ź�
#define MC_TERMINAL                     (50)                                   // ��վģ��������Դ
#define MC_NET_PORT                     (51)
#define MC_AU_ENCODER_EX                (52)
#define MC_MPG_ENCODER                  (53)
#define MC_SERIAL_NUMBER                (55)                                   // ģ������к���Դ��ʶ
#define MC_REMOTE_AU_ENCODER            (55)
#define MC_SLOTS_NUMBER                 (56)                                   // ģ��֧�ֵĲ�����Ϣ��Դ��ʶ
#define MC_SUB_TERMINAL                 (57)                                   // ��վģ���Ӱ�������Դ
#define MC_EXT_MODULE                   (60)
#define MC_EXT_DI                       (61)
#define MC_EXT_DO                       (62)
#define MC_EXT_AI                       (63)
#define MC_EXT_AO                       (64)
#define MC_EHMI_DI                      (65)
#define MC_EHMI_DO                      (66)
#define MC_LOCAL_TERMINAL_NO_RESOURCE   (67)
#define MC_AXIS_CONNECT                 (68)

#define MC_SCAN_CRD                     (70)
#define MC_LASER                        (71)
#define MC_LASER_AO                     (72)

#define MC_POS_COMPARE                  (80)

#define MC_WATCH_VAR                    (200)
#define MC_WATCH_EVENT                  (201)
#define MC_LIMIT_POSITIVE_RAW           (250)
#define MC_LIMIT_NEGATIVE_RAW           (251)
#define MC_ALARM_RAW                    (252)
#define MC_HOME_RAW                     (253)
#define MC_GPI_RAW                      (254)
#define MC_ARRIVE_RAW                   (255)
#define MC_MPG_RAW                      (259)

#define MC_GROUP                        (500)
#define MC_GROUP_PROFILE                (501)
#define MC_GROUP_SYNTHESIS              (505)
#define MC_GROUP_RTCP                   (510)

#define PROFILE_MODE_NONE               (-1)
#define PROFILE_MODE_TRAP               (0)
#define PROFILE_MODE_JOG                (1)
#define PROFILE_MODE_PT                 (2)
#define PROFILE_MODE_GEAR               (3)
#define PROFILE_MODE_FOLLOW             (4)
#define PROFILE_MODE_CRD                (5)
#define PROFILE_MODE_PVT                (6)
#define PROFILE_MODE_CAM                (7)

#define PROFILE_MODE_FOLLOW_EX          (10)
#define PROFILE_MODE_MOVE_ABSOLUTE      (20)
#define PROFILE_MODE_MOVE_VELOCITY      (30)

#define PROFILE_MODE_MOVE_CONTINUOUS               (40)
#define PROFILE_MODE_MOVE_JOG                      (41)
#define PROFILE_MODE_MOVE_SYNCHRONIZATION          (42)
#define PROFILE_MODE_MOVE_POS                      (48)

#define PROFILE_MODE_GROUP_MOVE_NONE               (100)
#define PROFILE_MODE_GROUP_MOVE_CONTINUOUS         (140)
#define PROFILE_MODE_GROUP_MOVE_JOG                (141)
#define PROFILE_MODE_GROUP_MOVE_SYNCHRONIZATION    (142)
#define PROFILE_MODE_GROUP_MOVE_POS                (148)
#define PROFILE_MODE_GROUP_MOVE_PATH               (150)

#define LIMIT_MODE_EXTERMAL          (0)
#define LIMIT_MODE_SOFT              (1)
#define LIMIT_MODE_ALL              (-1)

#define LIMIT_TYPE_POS              (0)
#define LIMIT_TYPE_NEG              (1)
#define LIMIT_TYPE_ALL              (-1)

typedef struct  
{
    short year;
    short month;
    short day;
    short version;
    short user;
    short reserve1;
    short reserve2;
    short chip;
} TVersion;

#define CORE_MODE_TIMER					(0)
#define CORE_MODE_SYNCH					(1)
#define CORE_MODE_EXTERNAL				(2)

#define CORE_TASK_DEFAULT				(0)
#define CORE_TASK_DLM					(1)

#define SKIP_MODULE_SCAN				(0x001)
#define SKIP_MODULE_POS_COMPARE			(0x002)
#define SKIP_MODULE_CRD					(0x004)

#define SKIP_MODULE_PLC					(0x010)
#define SKIP_MODULE_DLM					(0x020)

#define SKIP_MODULE_AXIS_CALCULATE		(0x100)

#define SKIP_MODULE_WATCH				(0x800)

typedef enum
{
    TIME_ELAPSE_PROFILE = 1000,

    TIME_ELAPSE_INTERRUPT_ERROR_COUNT = 1100,

    TIME_ELAPSE_HOST_COMMAND_EXECUTE = 1220,
    TIME_ELAPSE_ETHER_COMMAND_EXECUTE,

    TIME_ELAPSE_PROFILE_CALCULATE = 6000,
    TIME_ELAPSE_BEFOR_PROFILE_CALCULATE = 6001,

    TIME_ELAPSE_GROUP_CALCULATE = 9100,

    TIME_ELAPSE_FORWARD_KINEMATIC = 9101,
    TIME_ELAPSE_INVERSE_KINEMATIC = 9102,

    TIME_ELAPSE_SCAN = 18000,

    TIME_ELAPSE_AXIS_CHECK = 20000,
    TIME_ELAPSE_AXIS_CALCULATE,
    TIME_ELAPSE_AXIS_FILTER,

    TIME_ELAPSE_ENCODER = 30000,

    TIME_ELAPSE_DI = 31000,

    TIME_ELAPSE_DO = 32000,

    TIME_ELAPSE_AI = 33000,

    TIME_ELAPSE_AO = 34000,

    TIME_ELAPSE_TRIGGER = 38000,

    TIME_ELAPSE_CONTROL = 40000,

    TIME_ELAPSE_WATCH = 52000,

    TIME_ELAPSE_TERMINAL = 53000,

    TIME_ELAPSE_TERMINAL_OPERATION = 53001,

    TIME_ELAPSE_READ_ADC = 54000,

} ETimeElapse;

typedef struct Pid
{
    double kp;
    double ki;
    double kd;
    double kvff;
    double kaff;
    int32_t   integralLimit;
    int32_t   derivativeLimit;
    short  limit;
} TPid;

#define RESET_TYPE_NONE			(-1)
#define RESET_TYPE_IO			(0)

typedef struct
{
    short mode;		// modeΪ1��ʾ���֣�Ϊ0��ʾ��λ����ʼ״̬
}TResetIo;

typedef union
{
    TResetIo resetIo;
    double data[7];
}TResetModePrmUnion;

typedef struct
{
    short axisIndex[2];
    short reserve1[2];
    double radius;
    double center[2];
}TAxisCircularSafetyZone;

typedef struct
{
    short refType;           // ��ȫ���ο����ͣ�MC_ENCODER/MC_AU_ENCODER/MC_AU_ENCODER_EX/MC_MPG_ENCODER
    short refIndex;          // ��ȫ���ο����Ͷ�Ӧ��������
    short reserve1[2];
    double refRatio;         // �ο�������refRatio = (��1mm��Ӧ��������)/(�ο�����1mm��Ӧ��������)
    double limitPositive;    // ��ȫ������Χ����λ������
    double limitNegative;    // ��ȫ������Χ����λ������
}TProfileReferenceSafetyZone;

typedef struct
{
    short hwLmtPositiveEnable;         // ��Ӳ��λʹ��״̬��0���رգ�1����
    short hwLmtNegativeEnable;         // ��Ӳ��λʹ��״̬��0���رգ�1����
    short swLmtPositiveEnable;         // ������λʹ��״̬��0���رգ�1����
    short swLmtNegativeEnable;         // ������λʹ��״̬��0���رգ�1����

    short hwLmtPositiveStatus;         // ��Ӳ��λ����״̬��0��δ������1������
    short hwLmtNegativeStatus;         // ��Ӳ��λ����״̬��0��δ������1������
    short swLmtPositiveStatus;         // ������λ����״̬��0��δ������1������
    short swLmtNegativeStatus;         // ������λ����״̬��0��δ������1������
}TLimitInfo;

GT_API GTN_Open(short channel = 5, short param = 2);
GT_API GTN_Close(void);

GT_API GTN_OpenRingNet(short channel=5,short param=2,char *pFile=NULL,short index=1,int32_t count=1);
GT_API GTN_RingNetInit(short mode,char *pFile,short index);

GT_API GTN_GetChannel(short *pChannel);
GT_API GTN_GetVersion(short core,char **pVersion);
GT_API GTN_GetVersionEx(short core,short type,TVersion *pVersion);
GT_API GTN_SetVersion(short core,short type,TVersion *pVersion);
GT_API GTN_Reset(short core);
GT_API GTN_SetResetMode(short core,short type,TResetModePrmUnion *pResetPrm);
GT_API GTN_GetClock(short core,uint32_t *pClock,uint32_t *pLoop=NULL);
GT_API GTN_GetClockHighPrecision(short core,uint32_t *pClock);
GT_API GTN_ClearTime(short core,ETimeElapse item);
GT_API GTN_GetTime(short core,ETimeElapse item,uint32_t *pTime,uint32_t *pTimeMax,uint32_t *pValue=NULL);
GT_API GTN_SetCoreMode(short core,short mode);
GT_API GTN_GetCoreMode(short core,short *pMode);
GT_API GTN_SetCoreShare(short core,short type,short index,short count);
GT_API GTN_GetCoreShare(short core,short type,short *pIndex,short *pCount);
GT_API GTN_SetCoreTask(short core,short task);
GT_API GTN_GetCoreTask(short core,short *pTask);
GT_API GTN_GetResMax(short core,short type,short *pCount);
GT_API GTN_SetResCount(short core,short type,short count);
GT_API GTN_GetResCount(short core,short type,short *pCount);
GT_API GTN_SetDeviceShareMax(short core,short count);
GT_API GTN_GetDeviceShareMax(short core,short *pCount);
GT_API GTN_GetChipTemperature(double *pTempValue,double *pMinValue,double *pMaxValue);
GT_API GTN_SetTemperatureEnable(short core,short enable);
GT_API GTN_GetTemperature(short core,double *pTemperature);

GT_API GTN_GetSts(short core,short axis,int32_t *pSts,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetStsEx(short core,short axis,int32_t *pSts,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetPrfSts(short core,short profile,int32_t *pSts,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetDriverSts(short core,short axis,int32_t *pSts,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetDriverPosErr(short core,short station,short axis,int32_t *posError);
GT_API GTN_SetDryRunVel(short core, short crd, double vel, double velG0);
GT_API GTN_GetDryRunVel(short core, short crd, double *pVel, double *pVelG0);
GT_API GTN_SetDryRunMode(short core, short crd, short mode);
GT_API GTN_GetDryRunMode(short core, short crd, short *pMode);
GT_API GTN_SetDrvPrfVel(short core,short axis,int32_t *pPrfVel,short count);
GT_API GTN_GetDrvAtlVel(short core,short axis,int32_t *pPrfVel,short count);
GT_API GTN_ClrSts(short core,short axis,short count=1);
GT_API GTN_AxisOn(short core,short axis);
GT_API GTN_AxisOff(short core,short axis);
GT_API GTN_MultiAxisOn(short core,uint32_t mask);
GT_API GTN_MultiAxisOff(short core,uint32_t mask);
GT_API GTN_SetAxisOnDelayTime(short core,unsigned short delayTime);
GT_API GTN_GetAxisOnDelayTime(short core,unsigned short *pDelayTime);
GT_API GTN_Stop(short core,int32_t mask,int32_t option);
GT_API GTN_SetPrfPos(short core,short profile,int32_t prfPos);
GT_API GTN_SetPrfPosEx(short core,short profile,double pos);
GT_API GTN_SynchAxisPos(short core,int32_t mask);
GT_API GTN_ZeroPos(short core,short axis,short count=1);
GT_API GTN_GetLimitStatus(short core,short axis,short *pLimitPositive,short *pLimitNegative);
GT_API GTN_SetSoftLimitMode(short core,short axis,short mode);
GT_API GTN_GetSoftLimitMode(short core,short axis,short *pMode);
GT_API GTN_SetSoftLimit(short core,short axis,int32_t positive,int32_t negative);
GT_API GTN_GetSoftLimit(short core,short axis,int32_t *pPositive,int32_t *pNegative);
GT_API GTN_SetSoftLimitEx(short core,short axis,double positive,double negative);
GT_API GTN_GetSoftLimitEx(short core,short axis,double *pPositive,double *pNegative);
GT_API GTN_GetLimitInfo(short core,short axis,TLimitInfo *pInfo);
GT_API GTN_SetSoftLimitTrimMode(short core,short enable);
GT_API GTN_SetAxisBand(short core,short axis,int32_t band,int32_t time);
GT_API GTN_GetAxisBand(short core,short axis,int32_t *pBand,int32_t *pTime);

GT_API GTN_GetPrfPos(short core,short profile,double *pValue,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetPrfVel(short core,short profile,double *pValue,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetPrfAcc(short core,short profile,double *pValue,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetPrfMode(short core,short profile,int32_t *pValue, short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetAxisPrfPos(short core,short axis,double *pValue,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetAxisPrfPosCompensate(short core,short axis,double *pValue,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetAxisPrfVel(short core,short axis,double *pValue,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetAxisPrfAcc(short core,short axis,double *pValue,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetAxisEncPos(short core,short axis,double *pValue,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetAxisEncVel(short core,short axis,double *pValue,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetAxisEncAcc(short core,short axis,double *pValue,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetAxisError(short core,short axis,double *pValue, short count=1,uint32_t *pClock=NULL);
GT_API GTN_SetControlFilter(short core,short control,short index);
GT_API GTN_GetControlFilter(short core,short control,short *pIndex);
GT_API GTN_SetControlSuperimposed(short core,short control,short superimposedType,short superimposedIndex);
GT_API GTN_GetControlSuperimposed(short core,short control,short *pSuperimposedType,short *pSuperimposedIndex);
GT_API GTN_SetPid(short core,short control,short index,TPid *pPid);
GT_API GTN_GetPid(short core,short control,short index,TPid *pPid);
GT_API GTN_SetKvffFilter(short core,short control,short index,short kvffFilterExp,double accMax);
GT_API GTN_GetKvffFilter(short core,short control,short index,short *pKvffFilterExp,double *pAccMax);
GT_API GTN_Delay(short core,unsigned short ms);
GT_API GTN_DelayHighPrecision(short core,unsigned short profile);
GT_API GTN_SetLimit(short core,short axis,short type,void *pPrm);
GT_API GTN_GetLimit(short core,short axis,short type,void *pPrm);

/**
 * @brief �����ٶȱ���ģʽ
 * @param core �˺�
 * @param mode ģʽ����
 * @return 17056��ģʽ��������
*/
GT_API GTN_SetFeedOverrideMode(short core,short mode);

/**
 * @brief ��ȡ�ٶȱ���ģʽ
 * @param core �˺�
 * @param pMode ģʽ����
 * @return
 */
GT_API GTN_GetFeedOverrideMode(short core,short *pMode);

#define STEP_DIR                        (0)
#define STEP_PULSE                      (1)
#define STEP_ORTHOGONAL                 (2)

GT_API GTN_LoadConfig(short core,char *pFile);
GT_API GTN_AlarmOn(short core,short axis);
GT_API GTN_AlarmOff(short core,short axis);
GT_API GTN_ClearAlarm(short core,short axis,short count,unsigned short delayTime);


#define LIMIT_MODE_EXTERMAL     				(0)
#define LIMIT_MODE_SOFT         				(1)
#define LIMIT_MODE_ALL          				(-1)

GT_API GTN_LmtsOn(short core,short axis,short limitType=-1);
GT_API GTN_LmtsOnEx(short core,short axis,short limitType=-1,short limitMode=-1);
GT_API GTN_LmtsOff(short core,short axis,short limitType=-1);
GT_API GTN_LmtsOffEx(short core,short axis,short limitType=-1,short limitMode=-1);
GT_API GTN_StepDir(short core,short step);
GT_API GTN_StepPulse(short core,short step);
GT_API GTN_StepOrthogonal(short core,short step);
GT_API GTN_SetMtrBias(short core,short dac,short bias);
GT_API GTN_GetMtrBias(short core,short dac,short *pBias);
GT_API GTN_SetMtrLmt(short core,short dac,short limit);
GT_API GTN_GetMtrLmt(short core,short dac,short *pLimit);
GT_API GTN_SetSense(short core,short dataType,short dataIndex,short value);
GT_API GTN_GetSense(short core,short dataType,short dataIndex,short *pValue);
GT_API GTN_EncOn(short core,short encoder);
GT_API GTN_EncOff(short core,short encoder);
GT_API GTN_SetPosErr(short core,short control,int32_t error);
GT_API GTN_GetPosErr(short core,short control,int32_t *pError);
GT_API GTN_SetAxisPosErrLimit(short core,short axis,int32_t errorLimit);
GT_API GTN_GetAxisPosErrLimit(short core,short axis,int32_t *pErrorLimit);
GT_API GTN_SetStopDec(short core,short profile,double decSmoothStop,double decAbruptStop);
GT_API GTN_GetStopDec(short core,short profile,double *pDecSmoothStop,double *pDecAbruptStop);
GT_API GTN_CtrlMode(short core,short axis,short mode);
GT_API GTN_SetStopIo(short core,short axis,short stopType,short inputType,short inputIndex);
GT_API GTN_SetProbeCaptureStopAxis(short core,short encoder,short stopAxis,short stopType,short enable);
GT_API GTN_SetAxisPrfVelFilter(short core,short axis,short filterNumExp);
GT_API GTN_GetAxisPrfVelFilter(short core,short axis,short *pFilterNumExp);
GT_API GTN_SetAxisEncVelFilter(short core,short axis,short filterNumExp);
GT_API GTN_GetAxisEncVelFilter(short core,short axis,short *pFilterNumExp);

GT_API GTN_SetAxisFilterArrivalBand(short core,short axis,double band,int32_t time);
GT_API GTN_GetAxisFilterArrivalBand(short core,short axis,double *pBand,int32_t *pTime);
GT_API GTN_SetProfileScale(short core,short i,int32_t alpha,int32_t beta);
GT_API GTN_GetProfileScale(short core,short i,int32_t *pAlhpa,int32_t *pBeta);
GT_API GTN_SetEncoderScale(short core,short i,int32_t alpha,int32_t beta);
GT_API GTN_GetEncoderScale(short core,short i,int32_t *pAlhpa,int32_t *pBeta);
GT_API GTN_SetAuEncoderScale(short core,short i,int32_t alpha,int32_t beta);
GT_API GTN_GetAuEncoderScale(short core,short i,int32_t *pAlhpa,int32_t *pBeta);
GT_API GTN_SetEncoderMapRelation(short core,short masterEncType,short masterEncIndex,short mapEncType,short mapEncIndex);
GT_API GTN_GetEncoderMapRelation(short core,short masterEncType,short masterEncIndex,short *pMapEncType,short *pMapEncIndex);
GT_API GTN_SetProfilePpr(short core,short profile,double ppr);

/*-----------------------------------------------------------*/
/* Capture and Triggr                                        */
/*-----------------------------------------------------------*/
#define CAPTURE_HOME                    (1)
#define CAPTURE_INDEX                   (2)
#define CAPTURE_PROBE                   (3)
#define CAPTURE_HSIO0                   (6)
#define CAPTURE_HSIO1                   (7)
#define CAPTURE_POSCOMPARE              (6)

typedef struct Trigger
{
    short encoder;
    short probeType;
    short probeIndex;
    short sense;
    int32_t  offset;
    uint32_t loop;
    short windowOnly;
    int32_t firstPosition;
    int32_t lastPosition;
}TTrigger;

typedef struct TriggerEx
{
    short latchType;
    short latchIndex;
    short probeType;
    short probeIndex;
    short sense;
    int32_t  offset;
    uint32_t loop;
    short windowOnly;
    int32_t firstPosition;
    int32_t lastPosition;
}TTriggerEx;

typedef struct TriggerAlign
{
    short encoder;
    short probeType;
    short probeIndex;
    short sense;
    int32_t offset;
    uint32_t loop;
    short windowOnly;
    short pad2;
    int32_t firstPosition;
    int32_t lastPosition;
}TTriggerAlign;

typedef struct TriggerStatus
{
    short execute;
    short done;
    int32_t position;
}TTriggerStatus;

typedef struct TriggerStatusEx
{
    short execute;
    short done;
    int32_t position;
    uint32_t clock;
    uint32_t loopCount;
}TTriggerStatusEx;

typedef struct TriggerPrm
{
    short latchType;    // ��������
                        // MC_ENCODER    (23)
                        // MC_AU_ENCODER (26)
    short latchIndex;   // ����ı��������,������
    short probeType;    // �������ͣ�ȡֵ��Χ[1,3]
                        // CAPTURE_HOME  (1)
                        // CAPTURE_INDEX (2)
                        // CAPTURE_PROBE (3)
    short probeIndex;   // �������Ͷ�Ӧ��DI���
    short sense;        // ������,0:�½��أ�1:������
    short loopType;     // 0��FPGAѭ������DSP������ģ��ѭ���������������������ٹرղ���ʹ��
                        // 1��DSPѭ������DSP������ģ�鵥�ʴ���������ɹ�һ�κ���������һ�Ρ�
    int32_t  offset;    // ����λ��ƫ��ֵ������Ϊ0��ֻ��GTMģ��֧��offsetΪ��0ֵ
    uint32_t loop;      // ����ѭ�����ԣ�0������ѭ������������ѭ������
    short windowOnly;   // ����ʹ�ܣ�0�����������񴰣�1����������
    short pad1;         // ����ֵ������Ϊ0
    int32_t firstPosition;// windowOnly=1ʱ��Ч����������λ�õ����
    int32_t lastPosition;// windowOnly=1ʱ��Ч����������λ�õ��յ�
    short fifoMode;     // ѭ������FIFOģʽ
                        // TRIGGER_RESULT_FIFO_MODE_STATIC(0)����̬ģʽ��FIFO���˾Ͳ�����
                        // TRIGGER_RESULT_FIFO_MODE_LOOP(1)����̬ģʽ��FIFO����֮��ᱻ�����ݸ��ǣ��û������ݶ��ߺ�ὫFIFO�ͷų���
    short pad2[3];      // ����ֵ������Ϊ0
    double pad3;        // ����ֵ������Ϊ0
}TTriggerPrm;

typedef struct
{
    short fifoFull;
    short pad1[3];
    double pad2[2];
}TLatchValueInfo;

#define TRIGGER_RESULT_FIFO_MODE_STATIC  0
#define TRIGGER_RESULT_FIFO_MODE_LOOP    1

typedef struct TriggerLatchPrm
{
    uint32_t latchIndex;//���񴥷���������š�
    int32_t latchValue;//������ֵ����Trigger��������������й�	
    double   userValue;//�û����õ����ݣ���TTriggerPrm�Ĳ���pad3��Ӧ
    double   reserve;//��������������Ϊ0
}TTriggerLatchPrm;

#define LATCH_USER_VAR_DOUBLE          (100)
#define LATCH_USER_VAR_LONG             (101)

GT_API GTN_SetAuTrigger(short core,short index,TTriggerEx *pTrigger);
GT_API GTN_GetAuTrigger(short core,short index,TTriggerEx *pTrigger);
GT_API GTN_DisableAuTrigger(short core, short index);
GT_API GTN_ClearAuTriggerStatus(short core,short index);
GT_API GTN_GetAuTriggerStatus(short core,short index,TTriggerStatusEx *pTriggerStatusEx,short count=1);

GT_API GTN_SetTriggerPrm(short core,short index,TTriggerPrm *pTriggerPrm);
GT_API GTN_GetTriggerPrm(short core,short index,TTriggerPrm *pTriggerPrm);
GT_API GTN_GetTriggerLatchValue(short core,short index,int32_t count,int32_t *pValue,int32_t *pCount,TLatchValueInfo *pInfo);
GT_API GTN_GetTriggerLatchValuePro(short core,short index,int32_t count,TTriggerLatchPrm *pLatchPrm,int32_t *pCount,TLatchValueInfo *pInfo);
GT_API GTN_SetTrigger(short core,short index,TTrigger *pTrigger);
GT_API GTN_GetTrigger(short core,short index,TTrigger *pTrigger);
GT_API GTN_SetTriggerEx(short core,short index,TTriggerEx *pTrigger);
GT_API GTN_GetTriggerEx(short core,short index,TTriggerEx *pTrigger);
GT_API GTN_GetTriggerStatus(short core,short index,TTriggerStatus *pTriggerStatus,short count=1);
GT_API GTN_GetTriggerStatusEx(short core,short index,TTriggerStatusEx *pTriggerStatusEx,short count=1);
GT_API GTN_ClearTriggerStatus(short core,short index);
GT_API GTN_DisableTrigger(short core,short index);


#define TRIGGER_DELTA_MODE_DEFAULT            (0)

#define TRIGGER_DELTA_CHECKPOINT_MODE_AUTO    (0)
#define TRIGGER_DELTA_CHECKPOINT_MODE_MANUAL  (1)

typedef struct Checkpoint
{
    short mode;
    int32_t offset;
    short fifoIndex;
    uint32_t crossCount;
    short fifoDataCount;
    short dataReady;
    int32_t data;
    short dataIndex;
} TCheckpoint;

typedef struct TriggerDeltaPrm
{
    short mode;
    short dir;
    short triggerIndex[2];
} TTriggerDeltaPrm;

typedef struct TriggerDelta
{
    short enable;
    short checkpointCount;
    short fifoDataCount;
    short lostCount;
}TTriggerDeltaInfo;

GT_API GTN_ClearTriggerDelta(short core,short index,short mode=0);
GT_API GTN_AddTriggerDeltaCheckpoint(short core,short index,short mode,int32_t offset,short fifo=0,short *pIndex=NULL);
GT_API GTN_ReadTriggerDeltaCheckpointData(short core,short index,short checkpointIndex,int32_t *pBuf,short count,short *pReadCount);
GT_API GTN_WriteTriggerDeltaCheckpointData(short core,short index,short checkpointIndex,int32_t *pBuf,short count,short *pWriteCount);
GT_API GTN_SetTriggerDeltaPrm(short core,short index,TTriggerDeltaPrm *pPrm);
GT_API GTN_GetTriggerDeltaPrm(short core,short index,TTriggerDeltaPrm *pPrm);
GT_API GTN_GetTriggerDeltaCheckpoint(short core,short index,short checkpointIndex,TCheckpoint *pCheckpoint);
GT_API GTN_GetTriggerDeltaInfo(short core,short index,TTriggerDeltaInfo *pTriggerDelta);
GT_API GTN_TriggerDeltaOn(short core,short index);
GT_API GTN_TriggerDeltaOff(short core,short index);

GT_API GTN_SetCaptureMode(short core,short encoder,short mode);
GT_API GTN_GetCaptureMode(short core,short encoder,short *pMode,short count=1);
GT_API GTN_GetCaptureStatus(short core,short encoder,short *pStatus,int32_t *pValue,short count,uint32_t *pClock);
GT_API GTN_SetCaptureSense(short core,short encoder,short mode,short sense);
GT_API GTN_ClearCaptureStatus(short core,short encoder);
GT_API GTN_SetCaptureRepeat(short core,short encoder,short count);
GT_API GTN_GetCaptureRepeatStatus(short core,short encoder,short *pCount);
GT_API GTN_GetCaptureRepeatPos(short core,short encoder,int32_t *pValue,short startNum,short count);
GT_API GTN_SetCaptureRepeatFifoMode(short core,short encoder,short mode);
GT_API GTN_GetCaptureRepeatFifoMode(short core,short encoder,short *pMode);

GT_API GTN_LinkCaptureOffset(short core,short encoder,short source);
GT_API GTN_SetCaptureOffset(short core,short encoder,int32_t *pOffset,short count,int32_t loop);
GT_API GTN_GetCaptureOffset(short core,short encoder,int32_t *pOffset,short *pCount,int32_t *pLoop);
GT_API GTN_GetCaptureOffsetStatus(short core,short encoder,short *pCount,int32_t *pLoop,int32_t *pCapturePos);

GT_API GTN_AutoCaptureOn(short core,short encoder);
GT_API GTN_AutoCaptureOff(short core,short encoder);

typedef struct
{
    int32_t position1;                    // ������Ⲷ��λ��1����λ������
    int32_t position2;                    // ������Ⲷ��λ��2����λ������
}TToolPosition;

/**
 * @brief ��ȡTrigger���񵽵ĵ���λ��
 * @param core �˺ţ�������1��ʼ
 * @param triggerIndex ��Ҫ��ȡ���񵽵���λ�õ�Trigger��ʼ������������1��ʼ
 * @param pToolPos ����λ�ýṹ������ָ�룬�����СΪcount
 * @param count ��Ҫ��ȡ���񵽵���λ�õ�Trigger�������������0
 * @return 17051��count�������ޣ�ȡֵ��Χ��[1,119]
 *         17052���������Ͳ�֧�֣���֧��Trigger��AuTrigger
 *         17053��������ʼ�������ޣ�ȡֵ��Χ��������������
*/
GT_API GTN_GetTriggerToolPosition(short core,short triggerIndex,TToolPosition *pToolPos,short count=1);

/**
 * @brief ��ȡAuTrigger���񵽵ĵ���λ��
 * @param core �˺ţ�������1��ʼ
 * @param auTriggerIndex ��Ҫ��ȡ���񵽵���λ�õ�AuTrigger��ʼ������������1��ʼ
 * @param pToolPos ����λ�ýṹ������ָ�룬�����СΪcount
 * @param count ��Ҫ��ȡ���񵽵���λ�õ�AuTrigger�������������0
 * @return 17051��count�������ޣ�ȡֵ��Χ��[1,119]
 *         17052���������Ͳ�֧�֣���֧��Trigger��AuTrigger
 *         17053��������ʼ�������ޣ�ȡֵ��Χ��������������
*/
GT_API GTN_GetAuTriggerToolPosition(short core,short auTriggerIndex,TToolPosition *pToolPos,short count=1);

/*-----------------------------------------------------------*/
/* Basic Motion                                              */
/*-----------------------------------------------------------*/
typedef struct TrapPrm
{
    double acc;
    double dec;
    double velStart;
    short  smoothTime;
} TTrapPrm;

typedef struct TTrapTime
{
    double totalTime;
    double remainderTime;
    double pad[2];
} TTrapTime;

GT_API GTN_Update(short core,int32_t mask);
GT_API GTN_SetPos(short core,short profile,int32_t pos);
GT_API GTN_GetPos(short core,short profile,int32_t *pPos);
GT_API GTN_SetVel(short core,short profile,double vel);
GT_API GTN_GetVel(short core,short profile,double *pVel);
GT_API GTN_SetPosArray(short core,short profile,double *pPos,short count);
GT_API GTN_GetPosArray(short core,short profile,double *pPos,short count);

GT_API GTN_PrfTrap(short core,short profile);
GT_API GTN_SetTrapPrm(short core,short profile,TTrapPrm *pPrm);
GT_API GTN_GetTrapPrm(short core,short profile,TTrapPrm *pPrm);
GT_API GTN_GetTrapTime(short core,short profile,TTrapTime *pTime);
GT_API GTN_GetTrapSts(short core,short profile,short *prfsts);
GT_API GTN_ClearTrapSts(short core,short profile);

GT_API GTN_SetTrapOverride(short core,short profile,double velRatio);
GT_API GTN_GetTrapOverride(short core,short profile,double *pVelRatio);

typedef struct JogPrm
{
    double acc;
    double dec;
    double smooth;
} TJogPrm;

GT_API GTN_PrfJog(short core,short profile);
GT_API GTN_SetJogPrm(short core,short profile,TJogPrm *pPrm);
GT_API GTN_GetJogPrm(short core,short profile,TJogPrm *pPrm);

#define PT_MODE_STATIC                  (0)
#define PT_MODE_DYNAMIC                 (1)

#define PT_SEGMENT_NORMAL               (0)
#define PT_SEGMENT_EVEN                 (1)
#define PT_SEGMENT_STOP                 (2)

typedef struct
{
    double prfPos;
    int32_t loop;
    short mode;
    short fifoUse;
    short fifoPlace;
    short segmentNumber;
    uint32_t segmentReceive[2];
    uint32_t segmentExecute[2];
    uint32_t bufferReceive[2];
    uint32_t bufferExecute[2];
} TPtInfo;

//GT_API GTN_PosCurrFeedForward(short core,short profile,double pos,int32_t time,short torque,short type,short fifo=0);

GT_API GTN_PrfPt(short core,short profile,short mode=PT_MODE_STATIC);
GT_API GTN_SetPtLoop(short core,short profile,int32_t loop);
GT_API GTN_GetPtLoop(short core,short profile,int32_t *pLoop);
GT_API GTN_PtSpace(short core,short profile,short *pSpace,short fifo=0);
GT_API GTN_PtSpaceEx(short core,short profile,short *pSpace,short *pListSpace,short fifo=0);
GT_API GTN_PtData(short core,short profile,double pos,int32_t time,short type=PT_SEGMENT_NORMAL,short fifo=0);
GT_API GTN_PtClear(short core,short profile,short fifo=0);
GT_API GTN_PtStart(short core,int32_t mask,int32_t option=0);
GT_API GTN_SetPtMemory(short core,short profile,short memory);
GT_API GTN_GetPtMemory(short core,short profile,short *pMemory);
GT_API GTN_SetPtPrecisionMode(short core,short profile,short precisionMode);
GT_API GTN_GetPtPrecisionMode(short core,short profile,short *pPrecisionMode);
GT_API GTN_GetPtInfo(short core,short profile,TPtInfo *pPtInfo);
GT_API GTN_SetPtLink(short core,short profile,short fifo,short list);
GT_API GTN_GetPtLink(short core,short profile,short fifo,short *pList);
GT_API GTN_PtDoBit(short core,short profile,short doType,short index,short value,short fifo=0);
GT_API GTN_PtAo(short core,short profile,short aoType,short index,double value,short fifo=0);
GT_API GTN_PtSpaceDmaType(short core,short profile,short mode);
GT_API GTN_PtSpaceArray(short core,short profile,short *pSpace,short fifo,short count);
GT_API GTN_GetPtRemainder(short core,short profile,int32_t *pRemainder);
GT_API GTN_PtDataArray(short core,short profile,double *pos,int32_t time,short *type,short fifo,short count);
GT_API GTN_PtSmoothBegin(short core,short profile,int32_t deltaTime,int32_t degree,short fifo);
GT_API GTN_PtSmoothEnd(short core,short profile,short fifo);


typedef struct TPvtTableMovePrm
{
    short tableId;
    int32_t distance;
    double vm;
    double am;
    double jm;
    double time;
} TPvtTableMovePrm;

GT_API GTN_PrfPvt(short core,short profile);
GT_API GTN_SetPvtLoop(short core,short profile,int32_t loop);
GT_API GTN_GetPvtLoop(short core,short profile,int32_t *pLoopCount,int32_t *pLoop);
GT_API GTN_PvtStatus(short core,short profile,short *pTableId,double *pTime,short count=1);
GT_API GTN_PvtStart(short core,int32_t mask);
GT_API GTN_PvtTableSelect(short core,short profile,short tableId);

GT_API GTN_PvtTable(short core,short tableId,int32_t count,double *pTime,double *pPos,double *pVel);
GT_API GTN_PvtTableEx(short core,short tableId,int32_t count,double *pTime,double *pPos,double *pVelBegin,double *pVelEnd);
GT_API GTN_PvtTableComplete(short core,short tableId,int32_t count,double *pTime,double *pPos,double *pA,double *pB,double *pC,double velBegin=0,double velEnd=0);
GT_API GTN_PvtTablePercent(short core,short tableId,int32_t count,double *pTime,double *pPos,double *pPercent,double velBegin=0);
GT_API GTN_PvtPercentCalculate(short core, int32_t count, double* pTime, double* pPos, double* pPercent, double velBegin, double* pVel);
GT_API GTN_PvtTableContinuous(short core,short tableId,int32_t count,double *pPos,double *pVel,double *pPercent,double *pVelMax,double *pAcc,double *pDec,double timeBegin);
GT_API GTN_PvtContinuousCalculate(short core, int32_t count, double* pPos, double* pVel, double* pPercent, double* pVelMax, double* pAcc, double* pDec, double* pTime);

GT_API GTN_PvtTableMove(short core, short tableId, int32_t distance, double vm, double am, double jm, double* pTime = NULL);
GT_API GTN_PvtTableMoveCalculate(short core,int32_t distance,double vm,double am,double *pVm,double *pJm);
GT_API GTN_PvtTableMove2(short core,short tableId,int32_t distance,double vm,double am,double jm,double *pTime=NULL);
GT_API GTN_PvtTableMoveAbsoluteJerk(short core, short profile, short tableId, double* pPos, double* pVelMax, double* pAccMax, double* pJerkMax, double* pTime, short count);
GT_API GTN_PvtTableMove2Calculate(short core,int32_t distance,double vm,double am,double *pVm,double *pJm);
GT_API GTN_PvtTableMovePercent(short core,short tableId,int32_t distance,double vm,
                               double acc,double pa1,double pa2,
                               double dec,double pd1,double pd2,
                               double *pVel=NULL,double *pAcc=NULL,double *pDec=NULL,double *pTime=NULL);
GT_API GTN_PvtTableMovePercentEx(short core,short tableId,int32_t distance,double vm,
                                 double acc,double pa1,double pa2,double ma,
                                 double dec,double pd1,double pd2,double md,
                                 double *pVel=NULL,double *pAcc=NULL,double *pDec=NULL,double *pTime=NULL);

GT_API GTN_PvtTableMoveTogether(short core,short tableCount,TPvtTableMovePrm *pPvtTableMovePrm);

GT_API GTN_SetPvtTableMoveAccList(short core,short tableId,short count,int32_t *pDistance,double *pAccMax);
GT_API GTN_SetPvtTableLoop(short core,short profile,short tableId,int32_t loop,short nextTableId);
GT_API GTN_GetPvtTableLoop(short core,short profile,short tableId,int32_t *pLoopCount,int32_t *pLoop,short *pNextTableId);

GT_API GTN_PvtTableMoveAbsolute(short core,short profile,double *pDistance,double *pVm,
    double *pAcc,double *pPa1,double *pPa2,
    double *pDec,double *pPd1,double *pPd2,
    double *pVelM,double *pAccM,double *pDecM,double *pTime,short count);


#define GEAR_MASTER_ENCODER             (1)
#define GEAR_MASTER_PROFILE             (2)
#define GEAR_MASTER_AXIS                (3)
#define GEAR_MASTER_AU_ENCODER          (4)
#define GEAR_MASTER_MPG_ENCODER         (5)
#define GEAR_MASTER_MPG                 (9)

#define GEAR_MASTER_ENCODER_OTHER       (101)
#define GEAR_MASTER_AXIS_OTHER          (103)
#define GEAR_MASTER_AU_ENCODER_OTHER    (104)
#define GEAR_MASTER_MPG_ENCODER_OTHER   (105)

#define GEAR_EVENT_START                (1)
#define GEAR_EVENT_PASS                 (2)
#define GEAR_EVENT_AREA                 (5)

GT_API GTN_PrfGear(short core,short profile,short dir=0);
GT_API GTN_SetGearMaster(short core,short profile,short masterIndex,short masterType=GEAR_MASTER_PROFILE,short masterItem=0);
GT_API GTN_GetGearMaster(short core,short profile,short *pMasterIndex,short *pMasterType=NULL,short *pMasterItem=NULL);
GT_API GTN_SetGearRatio(short core,short profile,int32_t masterEven,int32_t slaveEven,int32_t masterSlope=0);
GT_API GTN_GetGearRatio(short core,short profile,int32_t *pMasterEven,int32_t *pSlaveEven,int32_t *pMasterSlope=NULL);
GT_API GTN_GearStart(short core,int32_t mask);
GT_API GTN_SetGearEvent(short core,short profile,short event,int32_t startPara0,int32_t startPara1);
GT_API GTN_GetGearEvent(short core,short profile,short *pEvent,int32_t *pStartPara0,int32_t *pStartPara1);

typedef struct{
    unsigned short masterIndex;        // GearInģʽ�������������
    short masterValueSource;           // ����Դ
    short pad1;                        // ����ֵ��������0
    short pad2;                        // ����ֵ��������0
    int32_t ratioNumerator;               // ���ֱȵķ���
    uint32_t ratioDenominator;    // ���ֱȵķ�ĸ
    double acceleration;               // ������ļ��ٶ�
    double deceleration;               // ������ļ��ٶ�
    double jerk;                       // ������ļӼ��ٶ�
    double pad3;                       // ����ֵ��������0
}TGearInParameter;

typedef struct  
{
    short state;
    unsigned short masterIndex;        // GearInģʽ�������������
    unsigned short masterValueSource;  // ����Դ
    short pad1[3];                     // ����ֵ��������0

    int32_t ratioNumerator;               // ���ֱȵķ���
    uint32_t ratioDenominator;    // ���ֱȵķ�ĸ
    int32_t slaveEven;                    // ���Թ�Լ����ĳ��ֱȵķ���
    uint32_t masterEven;          // ���Թ�Լ����ĳ��ֱȵķ�ĸ
    double acceleration;               // ������ļ��ٶ�
    double deceleration;               // ������ļ��ٶ�
    double jerk;                       // ������ļӼ��ٶ�
    double pad2;                       // ����ֵ��������0
}TGearInInfo;

GT_API GTN_SetGearInParameter(short core, short slaveIndex, TGearInParameter *pGearInPrm);
GT_API GTN_GearInStart(short core, uint32_t *pStartMask, unsigned short maskCount);
GT_API GTN_GetGearInInfo(short core, unsigned short slaveIndex, TGearInInfo *pGearInInfo);

#define FOLLOW_SWITCH_SEGMENT			(1)
#define FOLLOW_SWITCH_TABLE				(2)

#define FOLLOW_MASTER_ENCODER           (1)
#define FOLLOW_MASTER_PROFILE           (2)
#define FOLLOW_MASTER_AXIS              (3)
#define FOLLOW_MASTER_AU_ENCODER        (4)

#define FOLLOW_MASTER_ENCODER_OTHER     (101)
#define FOLLOW_MASTER_AXIS_OTHER        (103)

#define FOLLOW_EVENT_START              (1)
#define FOLLOW_EVENT_PASS               (2)

#define FOLLOW_SEGMENT_NORMAL           (0)
#define FOLLOW_SEGMENT_EVEN             (1)
#define FOLLOW_SEGMENT_STOP             (2)
#define FOLLOW_SEGMENT_CONTINUE         (3)

typedef struct
{
    short fifoNum;
    short switchStatus;
    short segNum;
    short pad1;
    double masterPosDelta;
    double slavePosDelta;
    double virtualMasterError;
    double pad2;
    double pad3;
} TFollowInfo;

GT_API GTN_PrfFollow(short core,short profile,short dir=0);
GT_API GTN_SetFollowMaster(short core,short profile,short masterIndex,short masterType=FOLLOW_MASTER_PROFILE,short masterItem=0);
GT_API GTN_GetFollowMaster(short core,short profile,short *pMasterIndex,short *pMasterType=NULL,short *pMasterItem=NULL);
GT_API GTN_SetFollowLoop(short core,short profile,int32_t loop);
GT_API GTN_GetFollowLoop(short core,short profile,int32_t *pLoop);
GT_API GTN_SetFollowEvent(short core,short profile,short event,short masterDir,int32_t pos=0);
GT_API GTN_GetFollowEvent(short core,short profile,short *pEvent,short *pMasterDir,int32_t *pPos=NULL);
GT_API GTN_FollowSpace(short core,short profile,short *pSpace,short fifo=0);
GT_API GTN_FollowData(short core,short profile,int32_t masterSegment,double slaveSegment,short type=FOLLOW_SEGMENT_NORMAL,short fifo=0);
GT_API GTN_FollowClear(short core,short profile,short fifo=0);
GT_API GTN_FollowStart(short core,int32_t mask,int32_t option=0);
GT_API GTN_FollowSwitch(short core,int32_t mask);
GT_API GTN_SetFollowMemory(short core,short profile,short memory);
GT_API GTN_GetFollowMemory(short core,short profile,short *pMemory);
GT_API GTN_GetFollowStatus(short core,short profile,short *pFifoNum,short *pSwitchStatus);
GT_API GTN_SetFollowPhasing(short core,short profile,short profilePhasing);
GT_API GTN_GetFollowPhasing(short core,short profile,short *pProfilePhasing);
GT_API GTN_GetFollowInfo(short core,short profile,TFollowInfo *pFollowInfo);
GT_API GTN_SetFollowVirtualSeg(short core,short profile,short seg,short axis,short fifo);
GT_API GTN_GetFollowVirtualSeg(short core,short profile,short *pSegment,short *pAxis,short fifo);
GT_API GTN_GetFollowVirtualErr(short core,short profile,double *pVirtualErr);
GT_API GTN_ClearFollowVirtualErr(short core,short profile);


GT_API GTN_PrfFollowEx(short core,short profile,short dir=0);
GT_API GTN_SetFollowMasterEx(short core,short profile,short masterIndex,short masterType=FOLLOW_MASTER_PROFILE,short masterItem=0);
GT_API GTN_GetFollowMasterEx(short core,short profile,short *pMasterIndex,short *pMasterType=NULL,short *pMasterItem=NULL);
GT_API GTN_SetFollowLoopEx(short core,short profile,int32_t loop);
GT_API GTN_GetFollowLoopEx(short core,short profile,int32_t *pLoop);
GT_API GTN_SetFollowEventEx(short core,short profile,short event,short masterDir,int32_t pos=0);
GT_API GTN_GetFollowEventEx(short core,short profile,short *pEvent,short *pMasterDir,int32_t *pPos=NULL);
GT_API GTN_FollowSpaceEx(short core,short profile,short *pSpace,short fifo=0);
GT_API GTN_FollowDataPercentEx(short core,short profile,double masterSegment,double slaveSegment,short type=FOLLOW_SEGMENT_NORMAL,short percent=0,short fifo=0);
GT_API GTN_FollowClearEx(short core,short profile,short fifo=0);
GT_API GTN_FollowStartEx(short core,int32_t mask,int32_t option=0);
GT_API GTN_FollowSwitchEx(short core,int32_t mask);
GT_API GTN_SetFollowMemoryEx(short core,short profile,short memory);
GT_API GTN_GetFollowMemoryEx(short core,short profile,short *pMemory);
GT_API GTN_GetFollowStatusEx(short core,short profile,short *pFifoNum,short *pSwitchStatus);
GT_API GTN_SetFollowPhasingEx(short core,short profile,short profilePhasing);
GT_API GTN_GetFollowPhasingEx(short core,short profile,short *pProfilePhasing);
GT_API GTN_FollowSwitchNowEx(short core,short profile,short method,short buffer=0,short fifo=0);
GT_API GTN_FollowDataPercent2Ex(short core,short profile,double masterSegment,double slaveSegment,double velBeginRatio,double velEndRatio,short percent=100,short *pPercent1=NULL,short fifo=0);
GT_API GTN_GetFollowDataPercent2Ex(short core,double masterPos,double v1,double v2,double p,double p1,double *pSlavePos);
GT_API GTN_FollowDoBitEx(short core,short profile,short doType,short index,short value,short fifo=0);
GT_API GTN_FollowDelayEx(short core,short profile,uint32_t delayTime,short fifo=0);
GT_API GTN_FollowDiBitEx(short core,short profile,short diType,short index,short value,uint32_t time=0,short fifo=0);

/**
 * @brief Follow������������չģ�飬ִ�и�ָ��ǰ����Ҫ�ȳ�ʼ����չģ�飬������չģ��Ŀ���Ȩ�л������������磺sRtn = GTN_ExtModuleInit(CORE_1,100);
 * @param core �˺�
 * @param profile Follow�������
 * @param doIndex ������չģ��DO����ʼ����
 * @param value ������չģ��DO��ֵ����bitλ����
 * @param mask ������չģ��DO��ֵ�Ŀ������룬��bitλ������bitΪ1ʱ�������Ӧvalue��bit��ֵ
 * @param fifo Follow�������ţ�Follow������һ����������
 * @return��
            7���������� / ��չģ��δ��ʼ��
            1��ִ�д��󣬸�����δ����FollowEx�滮ģʽ / ���˶�ָ���������16��
*/
GT_API GTN_FollowExtDoEx(short core,short profile,short doIndex,int32_t value,int32_t mask, short fifo);
GT_API GTN_SetAxisFollowErrorMode(short core,short axis,short followErrorMode);
GT_API GTN_GetAxisFollowErrorMode(short core,short axis,short *pFollowErrorMode);

GT_API GTN_SetFollowRegist(short core,short profile,short segment,short fifo);
GT_API GTN_GetFollowRegist(short core,short profile,short *pSegment,short fifo);
GT_API GTN_GetFollowRegistCount(short core,short profile,uint32_t *pCount);

typedef struct
{
    int32_t pos;
    double vel;
    double acc;
    double dec;
    short percent;
} TMoveAbsolutePrm;

typedef struct
{
    int32_t pos;
    double vel;
    double acc;
    double dec;
    short percent;
    double velStart;
    double velEnd;
    short accStartPercent;
    short decEndPercent;
} TMoveAbsolutePrmEx;

GT_API GTN_MoveAbsolute(short core,short profile,TMoveAbsolutePrm *pPrm);
GT_API GTN_GetMoveAbsolute(short core,short profile,TMoveAbsolutePrm *pPrm);

GT_API GTN_MoveAbsoluteEx(short core,short profile,TMoveAbsolutePrmEx *pPrm);
GT_API GTN_GetMoveAbsoluteEx(short core,short profile,TMoveAbsolutePrmEx *pPrm);

typedef struct
{
    double vel;
    double acc;
    double dec;
    double jerkBegin;
    double jerkEnd;
    short direction;
} TMoveVelocityPrm;

GT_API GTN_MoveVelocity(short core,short profile,TMoveVelocityPrm *pPrm);
GT_API GTN_GetMoveVelocity(short core,short profile,TMoveVelocityPrm *pPrm);

#define LISTINFO_RESERVE2_USERTAG                           (0)
typedef struct
{
    short list;
    short reserve1[2];
    short modal;
    int32_t segNum;
    int32_t reserve2[3];
    double reserve3[4];
}TListInfo;
/*-----------------------------------------------------------*/
/* Move                                                      */
/*-----------------------------------------------------------*/
#define VEL_PROFILE_MODE_TRAP               (1)
#define VEL_PROFILE_MODE_SMOOTH             (40)
#define VEL_PROFILE_MODE_SMOOTH_EX          (41)
#define VEL_PROFILE_MODE_JERK               (46)

typedef struct
{
    double accTime;              // ���ٶȱ仯ʱ��
    double k;                    // ��̬
    double reserve[18];
} TVelProfileModeSmooth;

typedef struct
{
    double value;                // �Ӽ��ٶ�
    double beginPercent;	
    double endPercent;	
    double reserve[17];
} TVelProfileModeJerk;

typedef union
{
    TVelProfileModeSmooth smooth;
    TVelProfileModeJerk jerk;
    double data[20];
} TVelProfileModeParameter;

typedef struct
{
    short mode;			// ģʽ
    short reserve[3];
    TVelProfileModeParameter parameter;
} TVelProfileMode;

typedef struct
{
    double pos;
    double vel;
    double velEnd;
    double acc;
    double dec;
    short  direction;
    short overrideSelect;
    short reserve;
    short velProfileMode;
    TVelProfileModeParameter velProfile;
} TMoveContinuousAbsolutePrm;

typedef struct
{
    double distance;
    double vel;
    double velEnd;
    double acc;
    double dec;
    short  direction;
    short overrideSelect;
    short reserve;
    short velProfileMode;
    TVelProfileModeParameter velProfile;
} TMoveContinuousRelativePrm;

typedef struct  
{
	short profile;
	short reserve[3];
	short group;
	short cmdCoord;
	short oriMode;
	short configIndex;
	TMoveContinuousAbsolutePrm prm;
} TTaskMoveContinuousAbsolute;
GT_API GTN_MoveContinuousAbsolute(short core,short profile,TMoveContinuousAbsolutePrm *pPrm,TListInfo *pListInfo=NULL,short group=0);
GT_API GTN_MoveContinuousRelative(short core,short profile,TMoveContinuousRelativePrm *pPrm,TListInfo *pListInfo=NULL,short group=0);

#define MOVE_JOG_MODE_GENERAL    0  //JOGģʽ
typedef struct
{
    short overrideSelect;
    short reserve1[3];
    double vel;
    double acc;
    double dec;
    short reserve[44];
}TJogParameter;

typedef union
{
    TJogParameter jog;
    short reserve[60];
}TMoveJogPrmUnion;

typedef struct
{
    short mode;
    short reserve[3];
    TMoveJogPrmUnion data;
}TMoveJogPrm;

GT_API GTN_MoveJog(short core,short index,TMoveJogPrm *pPrm,TListInfo *pListInfo=NULL,short group=0);
GT_API GTN_MoveTrap(short core,short profile,double pos,double vel,TTrapPrm *pPrm,TListInfo *pList=NULL);

/*-----------------------------------------------------------*/
/* Command Array                                             */
/*-----------------------------------------------------------*/
GT_API GTN_SetVelArray(short core,short profile,double *pVel,short count);
GT_API GTN_SetTrapPrmArray(short core,short profile,TTrapPrm *pPrm,short count);
GT_API GTN_ClearTriggerStatusArray(short core,short trigger,short count);


/*-----------------------------------------------------------*/
/* MovePos                                                   */
/*-----------------------------------------------------------*/
typedef struct
{
    short value;
}TMovePosPercent;

typedef struct
{
    short value;
}TMovePosSmoothTime;

typedef union
{
    TMovePosPercent percent;
    TMovePosSmoothTime smoothTime;
    double value[2];
}TMovePosUnion;

typedef struct
{
    double pos;
    double vel;
    double acc;
    double dec;
    short direction;
    short overrideSelect;
    short pad;
    short mode;
    TMovePosUnion data;
}TMovePosParameter;

typedef struct
{
    double pos[2];
    double vel[2];
    double acc;
    double dec;
    short direction;
    short overrideSelect;
    short pad;
    short mode;
    TMovePosUnion data;
}TMovePosTwoSegmentParameter;

typedef struct
{
    short profile;
    short pad1[3];
    double pos;
    double vel;
    double acc;
    double dec;
    short direction;
    short overrideSelect;
    short pad2;
    short mode;
    TMovePosUnion data;
}TMultiMovePosParameter;

typedef struct
{
    short profile;
    short pad1[3];
    double pos[2];
    double vel[2];
    double acc;
    double dec;
    short direction;
    short overrideSelect;
    short pad2;
    short mode;
    TMovePosUnion data;
}TMultiMovePosTwoSegmentParameter;

GT_API GTN_MovePos(short core,short profile,TMovePosParameter *pMovePos,TListInfo *pListInfo=NULL,short group=0);
GT_API GTN_MovePosTwoSegment(short core,short profile,TMovePosTwoSegmentParameter *pMovePos,TListInfo *pListInfo=NULL,short group=0);
GT_API GTN_MultiMovePos(short core,TMultiMovePosParameter *pMovePos,short count=1,TListInfo *pListInfo=NULL,short group=0);
GT_API GTN_MultiMovePosTwoSegment(short core,TMultiMovePosTwoSegmentParameter *pMovePos,short count=1,TListInfo *pListInfo=NULL,short group=0);

#define MOTION_RESTRICT_PROFILE_MAX                     (8)

#define MOTION_TIME_RESTRICT_MODE_DIRECT                (1)
#define MOTION_TIME_RESTRICT_MODE_ATTENTION_PROFILE     (2)

typedef struct
{
    short condition[MOTION_RESTRICT_PROFILE_MAX];
    double time[MOTION_RESTRICT_PROFILE_MAX];
}TMotionTimeRestrictDirect;

typedef struct
{
    short condition;
    short attentionProfileCount;
    short attentionProfile[MOTION_RESTRICT_PROFILE_MAX];
    short reserve1[6];
    double settlingTime;
}TMotionTimeRestrictAttentionProfile;

typedef union
{
    TMotionTimeRestrictDirect direct;
    TMotionTimeRestrictAttentionProfile attentionProfile;
    double data[32];
}TMotionTimeRestrictUnion;

typedef struct
{
    short profileCount;
    short profile[MOTION_RESTRICT_PROFILE_MAX];
    short pad1[7];
    double profilePos[MOTION_RESTRICT_PROFILE_MAX];

    short mode;
    short pad2[3];
    TMotionTimeRestrictUnion parameter;
}TMotionTimeRestrict;
GT_API GTN_SetMotionTimeRestrict(short core,short restrictIndex,TMotionTimeRestrict *pRestrict,TListInfo *pListInfo=NULL);
GT_API GTN_GetMotionTimeRestrict(short core,short restrictIndex,TMotionTimeRestrict *pRestrict);

#define MOVE_SYNCHRONIZATION_MODE_GEAR    0  //gearģʽ(λ��ͬ��ģʽ)
#define MOVE_SYNCHRONIZATION_MODE_MPG     1  //mpgͬ��ģʽ(λ��ͬ��ģʽ���ٶ�ͬ��ģʽ1�л�)
#define MOVE_SYNCHRONIZATION_MODE_FOLLOW  2  //followͬ��ģʽ(�ٶȸ���ģʽ(�ٶ�ͬ��ģʽ2))
#define MOVE_SYNCHRONIZATION_MODE_GEAR_POS  3  //λ��ģʽ(λ��ͬ��ģʽ)
typedef struct
{
    short type;     // ����
    short index;    //����
    short subIndex; // ��������
    short reserve[5];
}TProfileItem;

typedef struct
{
	double masterEven;          // ����������
    double slaveEven;           // �����ȴ���
	double slope;               // �����λ��
	short  slopeType;           // �����λ�������������ỹ�Ǵ���
	short  dir;
	short  startMode;
	short  startPrmType;        // ������������������Ϣʱ���ỹ�Ǵ���
	double startPrm[6];

	double deltaSlaveEven;      // ���ӱȵı仯��
	double deltaSlope;          // ���ӱȱ仯ʱ�������λ��
	short  deltaSlopeType;      // ���ӱȱ仯ʱ�������λ�������������ỹ�Ǵ���
	short  deltaLoop;           // ���ӱȱ仯������0������ѭ��
	short  reserve2[10]; 
}TGearParameter;

#define MOVE_SYNCH_MPG_RESERVE_MASTER_VEL_LIMIT     (0) // ���������������٣���λpusle/ms
typedef struct
{
    double masterEven;          //���������ᣬ��λ��pulse
    double slaveEven;            //�����ȴ��ᣬ��λ��mm
    double masterFilterTime;// �����˲�ʱ��
    double sampleTime;    // �������ʱ��
    double stopWaitTime;   // ֹͣ�ȴ�ʱ��
    double acceleration;    // �����˶����ٶ�
    double deceleration;    // �����˶����ٶ�
    double maxVel;        // �����˶�����ٶ�
    short reserve[28];
}TMpgParameter;

typedef struct
{
    double masterEven;          //���������ᣬ��λ��pulse
    double slaveEven;            //�����ȴ��ᣬ��λ��mm
    short reserve[52];
}TFollowParameter;

#define GEAR_POS_RESERVE_SLAVE_VEL_LIMIT_MODE        (4)
typedef struct
{
    double pos;            // �����յ�λ��
    double masterLength;   // ����λ��
    short reserve[52];
}TGearPosParameter;

typedef union
{
    TGearParameter gear;
    TMpgParameter mpg;
    TFollowParameter follow;
    TGearPosParameter gearPos;
    short reserve[60];
}TMoveSynchronizationUnion;

typedef struct
{
    short mode;          // ͬ���˶�ģʽ
    short enable;        // �Ƿ�ʹ��ͬ���˶�����
    short softDirCheck;  //0:�رշ��������жϹ��� 1���������������жϹ���
    short reserve;
    TMoveSynchronizationUnion prm;
}TMoveSynchronizationPrm;

typedef struct  
{
	short info1[8];
	int32_t info2[8];
	double info3[8];
}TMoveSynchronizationInfo;

GT_API GTN_MoveSynchronization(short core,TProfileItem slave,TProfileItem master,TMoveSynchronizationPrm *pPrm,TListInfo *pListInfo=NULL);
GT_API GTN_GetMoveSynchronizationInfo(short core,TProfileItem slave,TMoveSynchronizationInfo *pInfo);

typedef struct
{
    short source;
    short enable;
    short x;
    short y;
    double theta;		// degree
} TTransformOrthogonal;

GT_API GTN_SetTransformOrthogonal(short core,short index,TTransformOrthogonal *pOrthogonal);
GT_API GTN_GetTransformOrthogonal(short core,short index,TTransformOrthogonal *pOrthogonal);
GT_API GTN_GetTransformOrthogonalPosition(short core,short index,double *pPositionX,double *pPositionY);

typedef struct
{
    short source;
    short enable;
    short x;
    short y;
    short z;
    double alpha;		// Z���XYƽ��ļн�
    double beta;		// Z����XYƽ���ͶӰ��X��ļн�
    double gama;		// XY��֮��ļн�
} TTransformPerpendicularity;

GT_API GTN_SetTransformPerpendicularity(short core,short index,TTransformPerpendicularity *pPerpendicularity);
GT_API GTN_GetTransformPerpendicularity(short core,short index,TTransformPerpendicularity *pPerpendicularity);
GT_API GTN_GetTransformPerpendicularityPosition(short core,short index,double *pPositionX,double *pPositionY,double *pPositionZ);

/*-----------------------------------------------------------*/
/* Comp                                                      */
/*-----------------------------------------------------------*/

#define COMP_TYPE_COORD_SYNC	(0)

typedef struct
{
    double translateion[2];	//��������ϵ���ԭʼ����ϵ��ƽ��
    double theta;	//��������ϵ���ԭʼ����ϵ����ת
}TCoordTransformPrm;

typedef struct
{
    short enable;	//�Ƿ�ʹ������ϵת������
    short refType;	//�ο����ͣ���������ΪMC_CRD��MC_GROUP��MC_PROFILE��
    short index;	//����ο�����ΪMC_CRD��д������ϵ��
    short refIndex[2];	//�ο���ţ�ָ������ϵ�е�ĳ�����ᣬ����profile��������
    double offset[2];	//������X2��Y2�����Բο�����ϵX1��Y1����ƫ��
    TCoordTransformPrm refTrans;	//�ο���������ϵ���ԭ����ϵ��ƽ�ƺ���ת
    TCoordTransformPrm syncTrans;	//ͬ����������ϵ���ԭ����ϵ��ƽ�ƺ���ת
    short reserve1[4];
    double reserve2[4];
}TCoordSyncCompPrm;

typedef struct
{
    short type;	//�������ͣ�����ͬ��������
    short index;	//һ������������ͬ������֧�����������������ϵ����������ʾ�ڼ���ͬ������
    short subIndex;	//���������������һ��ͬ�������ĵ�һ����
    short reserve1[5];
    double reserve2[4];
}TPrfComp;

GT_API GTN_PrfComp(short core,short profile,TPrfComp *pComp);
GT_API GTN_PrfCompEnable(short core,short profile,short enable,short enableType = 0);
GT_API GTN_BufPrfCompEnable(short core,short crd,short fifo,short profile,short enable,short enableType = 0);
GT_API GTN_BufPrfCompEnableEx(short core,short crd,short fifo,short profile,short enable,short enableType = 0);
GT_API GTN_SetCoordSyncCompPrm(short core,short index,TCoordSyncCompPrm *pPrm);
GT_API GTN_GetCoordSyncCompPrm(short core,short index,TCoordSyncCompPrm *pPrm);
GT_API GTN_GetCoordSyncCompValue(short core,short index,double x,double y,double *pCompX,double *pCompY);

/*-----------------------------------------------------------*/
/* Home                                                      */
/*-----------------------------------------------------------*/
#define HOME_STAGE_IDLE                           (0)
#define HOME_STAGE_START                          (1)
#define HOME_STAGE_ON_HOME_LIMIT_ESCAPE           (2)
#define HOME_STAGE_ON_HOME_ESCAPE                 (3)

#define HOME_STAGE_SEARCH_LIMIT                   (10)
#define HOME_STAGE_SEARCH_LIMIT_STOP              (11)

#define HOME_STAGE_SEARCH_LIMIT_ESCAPE            (13)

#define HOME_STAGE_SEARCH_LIMIT_RETURN            (15)
#define HOME_STAGE_SEARCH_LIMIT_RETURN_STOP       (16)

#define HOME_STAGE_SEARCH_HOME                    (20)

#define HOME_STAGE_SERCH_HOME_STOP                (22)
#define HOME_STAGE_SEARCH_HOME_OPPOSITE           (23)
#define HOME_STAGE_SEARCH_HOME_AGAIN              (24)
#define HOME_STAGE_SEARCH_HOME_RETURN             (25)

#define HOME_STAGE_SEARCH_INDEX                   (30)

#define HOME_STAGE_SEARCH_GPI                     (40)

#define HOME_STAGE_SEARCH_GPI_RETURN              (45)

#define HOME_STAGE_GO_HOME                        (80)

#define HOME_STAGE_END                            (100)

#define HOME_ERROR_NONE                           (0)
#define HOME_ERROR_NOT_TRAP_MODE                  (1)
#define HOME_ERROR_DISABLE                        (2)
#define HOME_ERROR_ALARM                          (3)
#define HOME_ERROR_STOP                           (4)
#define HOME_ERROR_STAGE                          (5)
#define HOME_ERROR_HOME_MODE                      (6)
#define HOME_ERROR_SET_CAPTURE_HOME               (7)
#define HOME_ERROR_NO_HOME                        (8)
#define HOME_ERROR_SET_CAPTURE_INDEX              (9)
#define HOME_ERROR_NO_INDEX                       (10)
#define HOME_ERROR_LIMIT                          (11)
#define HOME_ERROR_ESCAPE                         (12)

#define HOME_MODE_LIMIT                           (10)
#define HOME_MODE_LIMIT_HOME                      (11)
#define HOME_MODE_LIMIT_INDEX                     (12)
#define HOME_MODE_LIMIT_HOME_INDEX                (13)
#define HOME_MODE_LIMITPOS_INDEX		          (14)
#define HOME_MODE_HOME                            (20)

#define HOME_MODE_HOME_INDEX                      (22)

#define HOME_MODE_HOME_LEVEL                      (24)                               // ʹ��HOME��ƽ����(������û��HOME����������)

#define HOME_MODE_INDEX                           (30)
#define HOME_MODE_FORCED_HOME                     (40)
#define HOME_MODE_FORCED_HOME_INDEX               (41)
#define HOME_MODE_DRIVER_HOME                     (42)
typedef struct
{
    short mode;
    short moveDir;
    short indexDir;
    short edge;
    short triggerIndex;
    short pad1[3];
    double velHigh;
    double velLow;
    double acc;
    double dec;
    short smoothTime;
    short pad2[3];
    int32_t homeOffset;
    int32_t searchHomeDistance;
    int32_t searchIndexDistance;
    int32_t escapeStep;
    int32_t pad3[2];
} THomePrm;

typedef struct
{
    short run;
    short stage;
    short error;
    short pad1;
    int32_t capturePos;
    int32_t targetPos;
} THomeStatus;

GT_API GTN_GoHome(short core,short axis,THomePrm *pHomePrm);
GT_API GTN_GetHomePrm(short core,short axis,THomePrm *pHomePrm);
GT_API GTN_GetHomeStatus(short core,short axis,THomeStatus *pHomeStatus);

GT_API GTN_HandwheelInit(short core,short mode=0);
GT_API GTN_SetHandwheelStopDec(short core,short slave,double decSmoothStop,double decAbruptStop);
GT_API GTN_StartHandwheel(short core,short slave,short master,short masterEven,short slaveEven,short intervalTime,double acc,double dec,double vel,short stopWaitTime);
GT_API GTN_EndHandwheel(short core,short slave);

/*-----------------------------------------------------------*/
/* PLC                                                       */
/*-----------------------------------------------------------*/
#define PLC_THREAD_MAX					(32)
#define PLC_PAGE_MAX					(32)
#define PLC_LOCAL_VAR_MAX				(1024)
#define PLC_ACCESS_VAR_COUNT_MAX        (8)

#define PLC_TIMER_TT					(0)
#define PLC_TIMER_TF					(1)
#define PLC_TIMER_TTF					(2)

#define PLC_COUNTER_EQ					(0)
#define PLC_COUNTER_LE					(1)
#define PLC_COUNTER_GE					(2)

#define PLC_COUNTER_EDGE_UP				(0)
#define PLC_COUNTER_EDGE_DOWN			(1)
#define PLC_COUNTER_EDGE_UP_DOWN		(2)

#define PLC_FLANK_UP					(0)
#define PLC_FLANK_DOWN					(1)
#define PLC_FLANK_UP_DOWN				(2)

typedef enum
{
    PLC_BIND_NONE,
    PLC_BIND_DI,
    PLC_BIND_DO,
    PLC_BIND_TIMER,
    PLC_BIND_COUNTER,
    PLC_BIND_FLANK,
    PLC_BIND_SRFF,
} EPlcBind;

typedef struct VarInfo
{
    short id;
    short dataType;
    char  name[32];
} TVarInfo;

typedef struct
{
    short diType;
    short index;
    short reverse;
} TBindDi;

typedef struct
{
    short doType;
    short index;
    short reverse;
} TBindDo;

typedef struct
{
    short timerType;
    int32_t delay;
    short inputVarId;
} TBindTimer;

typedef struct
{
    short counterType;
    short edge;
    int32_t init;
    int32_t target;
    int32_t begin;
    int32_t end;
    short dir;
    int32_t unit;
    short inputVarId;
    short resetVarId;
} TBindCounter;

typedef struct
{
    short flankType;
    short inputVarId;
} TBindFlank;

typedef struct
{
    short setVarId;
    short resetVarId;
} TBindSrff;

typedef struct CompileInfo
{
    char  *pFileName;
    short *pLineNo;
    char  *pMessage;
} TCompileInfo;

typedef struct ThreadSts
{
    short  run;
    short  error;
    double result;
    short  line;
} TThreadSts;

GT_API GTN_Compile(char *pFileName,TCompileInfo *pWrongInfo);
GT_API GTN_Download(short core,char *pFileName);
GT_API GTN_GetFunId(char *pFunName,short *pFunId);
GT_API GTN_GetVarId(char *pFunName,char *pVarName,TVarInfo *pVarInfo);
GT_API GTN_Bind(short core,short thread,short funId,short page);
GT_API GTN_RunThread(short core,short thread);
GT_API GTN_RunThreadPeriod(short core,short thread,short ms,short priority=4);
GT_API GTN_StepThread(short core,short thread);
GT_API GTN_StopThread(short core,short thread);
GT_API GTN_PauseThread(short core,short thread);
GT_API GTN_GetThreadSts(short core,short thread,TThreadSts *pThreadSts);
GT_API GTN_GetThreadTime(short core,short thread,short *pPeriod,double *pExecuteTime,double *pExecuteTimeMax);
GT_API GTN_RunThreadToBreakpoint(short core,short thread,short line);
GT_API GTN_SetVarValue(short core,short page,TVarInfo *pVarInfo,double *pValue,short count=1);
GT_API GTN_GetVarValue(short core,short page,TVarInfo *pVarInfo,double *pValue,short count=1);


GT_API GTN_UnbindVar(short core,short thread);
GT_API GTN_BindDi(short core,short thread,TVarInfo *pVarInfo,TBindDi *pBindDi);
GT_API GTN_BindDo(short core,short thread,TVarInfo *pVarInfo,TBindDo *pBindDo);
GT_API GTN_BindTimer(short core,short thread,TVarInfo *pVarInfo,TBindTimer *pBindTimer);
GT_API GTN_BindCounter(short core,short thread,TVarInfo *pVarInfo,TBindCounter *pBindCounter);
GT_API GTN_BindFlank(short core,short thread,TVarInfo *pVarInfo,TBindFlank *pBindFlank);
GT_API GTN_BindSrff(short core,short thread,TVarInfo *pVarInfo,TBindSrff *pBindSrff);

GT_API GTN_GetBindDi(short core,TVarInfo *pVarInfo,TBindDi *pBindDi);
GT_API GTN_GetBindDo(short core,TVarInfo *pVarInfo,TBindDo *pBindDo);
GT_API GTN_GetBindTimer(short core,TVarInfo *pVarInfo,TBindTimer *pBindTimer,int32_t *pCount);
GT_API GTN_GetBindCounter(short core,TVarInfo *pVarInfo,TBindCounter *pBindCounter,int32_t *pUnitCount,int32_t *pCount);
GT_API GTN_GetBindFlank(short core,TVarInfo *pVarInfo,TBindFlank *pBindFlank);
GT_API GTN_GetBindSrff(short core,TVarInfo *pVarInfo,TBindSrff *pBindSrff);

GT_API GTN_GetBindDiCount(short core,short thread,short *pCount);
GT_API GTN_GetBindDoCount(short core,short thread,short *pCount);
GT_API GTN_GetBindTimerCount(short core,short thread,short *pCount);
GT_API GTN_GetBindCounterCount(short core,short thread,short *pCount);
GT_API GTN_GetBindFlankCount(short core,short thread,short *pCount);
GT_API GTN_GetBindSrffCount(short core,short thread,short *pCount);

GT_API GTN_GetBindDiInfo(short core,short thread,short index,short *pVar,TBindDi *pBindDi);
GT_API GTN_GetBindDoInfo(short core,short thread,short index,short *pVar,TBindDo *pBindDo);
GT_API GTN_GetBindTimerInfo(short core,short thread,short index,short *pVar,TBindTimer *pBindTimer);
GT_API GTN_GetBindCounterInfo(short core,short thread,short index,short *pVar,TBindCounter *pBindCounter);
GT_API GTN_GetBindFlankInfo(short core,short thread,short index,short *pVar,TBindFlank *pBindFlank);
GT_API GTN_GetBindSrffInfo(short core,short thread,short index,short *pVar,TBindSrff *pBindSrff);

typedef struct ThreadStatus
{
    short link;
    uint32_t  address;
    short size;
    uint32_t  page;
    short delay;
    short priority;
    short ptr;
    short status;
    short error;
    short result[4];
    short resultType;
    short breakpoint;
    short period;
    short count;
    short function;
} TThreadStatus;
GT_API GTN_GetThread(short core,short thread,TThreadStatus *pThread);

GT_API GTN_ClearPlc(short core);
GT_API GTN_LoadPlc(short core,short id,short returnType);
GT_API GTN_LoadPlcCommand(short core,short id,short count,short *pData);

/*-----------------------------------------------------------*/
/* Interpolation                                             */
/*-----------------------------------------------------------*/
#define INTERPOLATION_AXIS_MAX                   (8)

#define CRD_OPERATION_DATA_EXT_MAX               (2)


#define CRD_BUFFER_MODE_DYNAMIC_DEFAULT          (0)
#define CRD_BUFFER_MODE_DYNAMIC_KEEP             (1)

#define CRD_BUFFER_MODE_STATIC_INPUT             (11)
#define CRD_BUFFER_MODE_STATIC_READY             (12)
#define CRD_BUFFER_MODE_STATIC_START             (13)

#define INTERPOLATION_CIRCLE_PLAT_XY             (0)
#define INTERPOLATION_CIRCLE_PLAT_YZ             (1)
#define INTERPOLATION_CIRCLE_PLAT_ZX             (2)

#define INTERPOLATION_HELIX_CIRCLE_XY_LINE_Z     (0)
#define INTERPOLATION_HELIX_CIRCLE_YZ_LINE_X     (1)
#define INTERPOLATION_HELIX_CIRCLE_ZX_LINE_Y     (2)

#define INTERPOLATION_CIRCLE_DIR_CW              (0)
#define INTERPOLATION_CIRCLE_DIR_CCW             (1)

#define CRD_AXIS_X                               (1) // �岹����ϵx��
#define CRD_AXIS_Y                               (2) // �岹����ϵy��
#define CRD_AXIS_Z                               (3) // �岹����ϵz��
#define CRD_AXIS_A                               (4) // �岹����ϵa��
#define CRD_AXIS_C                               (5) // �岹����ϵc��
#define CRD_AXIS_U                               (6) // �岹����ϵu��
#define CRD_AXIS_V                               (7) // �岹����ϵv��
#define CRD_AXIS_W                               (8) // �岹����ϵw��

typedef struct CrdPrm
{
    short dimension;
    short profile[8];
    double synVelMax;
    double synAccMax;
    short evenTime;
    short setOriginFlag;
    int32_t originPos[8];
}TCrdPrm;

typedef struct CrdBufOperation
{
    short flag;
    unsigned short delay;
    short doType;
    unsigned short doMask;
    unsigned short doValue;
    unsigned short dataExt[CRD_OPERATION_DATA_EXT_MAX];
}TCrdBufOperation;

typedef struct CrdData
{
    short motionType;
    short circlePlat;
    int32_t pos[INTERPOLATION_AXIS_MAX];
    double radius;
    short circleDir;
    double center[3];
    double vel;
    double acc;
    short velEndZero;
    TCrdBufOperation operation;

    double cos[INTERPOLATION_AXIS_MAX];
    double velEnd;
    double velEndAdjust;
    double r;
}TCrdData;

typedef struct
{
    double time;
    int32_t segmentUsed;
    int32_t segmentHead;
    int32_t segmentTail;
} TCrdTime;

typedef struct
{
    short crdAxis;
    short masterIndex;
    short masterType;
} TBufFollowMaster;

typedef struct
{
    int32_t masterPos;
    int32_t pad;
} TBufFollowEventCross;

typedef struct
{
    short triggerIndex;
    int32_t triggerOffset;
    int32_t pad;
} TBufFollowEventTrigger;

typedef struct
{
    double velRatioMax;
    double accRatioMax;
    int32_t masterLead;
    int32_t masterEven;
    int32_t slaveEven;
    short dir;
    short smoothPercent;
    short synchAlign;
} TCrdFollowPrm;

typedef struct
{
    short stage;
    double slavePos;
    double slaveVel;
    int32_t masterFrameWidth;
    int32_t masterFrameIndex;
    uint32_t loopCount;
} TCrdFollowStatus;

// �岹�û�ָ��ֹͣģʽ����
#define BUF_CMD_TYPE_ALL               (-1) // ����֧������ֹͣģʽ��Bufָ������ͽ�֧������ΪDefault��Continueģʽ
#define BUF_CMD_TYPE_BUF_MOVE          (0)  // BufMoveģָ̬������ͽ�֧������ΪDefault��Continueģʽ
#define BUF_CMD_TYPE_BUF_GEAR          (1)  // BufGearָ������ͽ�֧������ΪDefault��Continueģʽ
#define BUF_CMD_TYPE_BUF_IO            (2)  // BufIoָ�������֧������ΪDefault��Continue��Holdģʽ
// ע�⣺��Continue��Holdģʽ�£�ֻ��ָ��GT_SetBufIoHoldValue����doMask��0ʱ����Ч

#define BUF_CMD_STOP_MODE_DEFAULT      (0)  // Ĭ��ģʽ
#define BUF_CMD_STOP_MODE_CONTINUE     (1)  // ��ͣ�ָ�ģʽ��ע�⣺BufIo��ͣʱ���ָ��GT_SetBufIoHoldValue���õ�doֵ���ָ��˶�ʱ�����ͣǰ״̬��doMask��0ʱ��Ч
#define BUF_CMD_STOP_MODE_HOLD         (2)  // ��ͣ�������ֵ�����ָ���ͣǰ״̬����BufIo֧�֣���ͣ�岹�˶�ʱ�����ָ��GT_SetBufIoHoldValue���õ�doֵ�����ָ���doMask��0ʱ��Ч

// ���ò岹�˶���ͣ���쳣ֹͣʱ��do��������ض�ֵ
// crd���岹����ϵ�ţ���ǰָ�����ý��ڶ�Ӧ����ϵ��Ч
// doType����Ҫ������ͣ���������do���ͣ���֧�֣�MC_ENABLE��MC_CLEAR��MC_GPO
// doMask����ͣʱ��������ض�ֵ��do�������룬ͬʱҲ��ʾ�ָ��˶�ʱ��Ҫ�ָ�ԭ�����ֵ��do�������룬��λָʾ��0����ʾ��Ч��1����ʾ��Ч
// doValue����ͣʱ����������ض�ֵ����λָʾ
// ע�⣺��doMask=0ʱ����ʹBufIO����Ϊcontinue����holdģʽ����ͣ����������˶��ָ����������Ч��
GT_API GTN_SetBufIoHoldValue(short core,short crd,short doType,unsigned short doMask,unsigned short doValue);
GT_API GTN_GetBufIoHoldValue(short core,short crd,short doType,unsigned short *pDoMask,unsigned short *pDoValue);

// ���ò岹�û���ָ��ֹͣģʽ
// crd���岹����ϵ�ţ���ǰָ�����ý��ڶ�Ӧ����ϵ��Ч
// bufCmdType���岹�û���ָ�����ͣ���֧�֣�BUF_CMD_TYPE_ALL��BUF_CMD_TYPE_BUF_MOVE��BUF_CMD_TYPE_BUF_GEAR��BUF_CMD_TYPE_BUF_IO
// mode��ֹͣģʽ
GT_API GTN_SetBufCmdStopMode(short core,short crd,short bufCmdType,short mode);
GT_API GTN_GetBufCmdStopMode(short core,short crd,short bufCmdType,short *pMode);

/**
 * @brief ���ò岹��ӡlog��Ϣʹ�ܱ�־
 * @param core �˺ţ�������1��ʼ
 * @param crd �岹����ϵ�ţ�������1��ʼ
 * @param enable ʹ�ܱ�־��0-����ӡ��1-��ӡ
 * @return ���㣬����ʧ��
*/
GT_API GTN_SetCrdPrintLogEnable(short core,short crd,short enable);

/**
 * @brief ��ȡ�岹��ӡlog��Ϣʹ�ܱ�־
 * @param core �˺ţ�������1��ʼ
 * @param crd �岹����ϵ�ţ�������1��ʼ
 * @param pEnable ʹ�ܱ�־��0-����ӡ��1-��ӡ
 * @return ���㣬��ȡʧ��
*/
GT_API GTN_GetCrdPrintLogEnable(short core,short crd,short *pEnable);

GT_API GTN_SetCrdPrm(short core,short crd,TCrdPrm *pCrdPrm);
GT_API GTN_GetCrdPrm(short core,short crd,TCrdPrm *pCrdPrm);
GT_API GTN_CrdSpace(short core,short crd,int32_t *pSpace,short fifo=0);
GT_API GTN_CrdData(short core,short crd,TCrdData *pCrdData,short fifo=0);
GT_API GTN_SetCrdLaserLevelDelay(short core,short crd,double highLevelDelay,double lowLevelDelay,short channel);

GT_API GTN_LnXY(short core,short crd,int32_t x,int32_t y,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_LnXYOverride2(short core,short crd,int32_t x,int32_t y,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_LnXYWN(short core,short crd,int32_t x,int32_t y,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);
GT_API GTN_LnXYOverride2WN(short core,short crd,int32_t x,int32_t y,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);

GT_API GTN_LnXYG0(short core,short crd,int32_t x,int32_t y,double synVel,double synAcc,short fifo=0);
GT_API GTN_LnXYG0Override2(short core,short crd,int32_t x,int32_t y,double synVel,double synAcc,short fifo=0);
GT_API GTN_LnXYG0WN(short core,short crd,int32_t x,int32_t y,double synVel,double synAcc,int32_t segNum=0,short fifo=0);
GT_API GTN_LnXYG0Override2WN(short core,short crd,int32_t x,int32_t y,double synVel,double synAcc,int32_t segNum=0,short fifo=0);

GT_API GTN_LnXYZ(short core,short crd,int32_t x,int32_t y,int32_t z,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_LnXYZOverride2(short core,short crd,int32_t x,int32_t y,int32_t z,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_LnXYZWN(short core,short crd,int32_t x,int32_t y,int32_t z,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);
GT_API GTN_LnXYZOverride2WN(short core,short crd,int32_t x,int32_t y,int32_t z,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);

GT_API GTN_LnXYZG0(short core,short crd,int32_t x,int32_t y,int32_t z,double synVel,double synAcc,short fifo=0);
GT_API GTN_LnXYZG0Override2(short core,short crd,int32_t x,int32_t y,int32_t z,double synVel,double synAcc,short fifo=0);
GT_API GTN_LnXYZG0WN(short core,short crd,int32_t x,int32_t y,int32_t z,double synVel,double synAcc,int32_t segNum=0,short fifo=0);
GT_API GTN_LnXYZG0Override2WN(short core,short crd,int32_t x,int32_t y,int32_t z,double synVel,double synAcc,int32_t segNum=0,short fifo=0);

GT_API GTN_LnXYZA(short core,short crd,int32_t x,int32_t y,int32_t z,int32_t a,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_LnXYZAOverride2(short core,short crd,int32_t x,int32_t y,int32_t z,int32_t a,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_LnXYZAWN(short core,short crd,int32_t x,int32_t y,int32_t z,int32_t a,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);
GT_API GTN_LnXYZAOverride2WN(short core,short crd,int32_t x,int32_t y,int32_t z,int32_t a,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);

GT_API GTN_LnXYZAG0(short core,short crd,int32_t x,int32_t y,int32_t z,int32_t a,double synVel,double synAcc,short fifo=0);
GT_API GTN_LnXYZAG0Override2(short core,short crd,int32_t x,int32_t y,int32_t z,int32_t a,double synVel,double synAcc,short fifo=0);
GT_API GTN_LnXYZAG0WN(short core,short crd,int32_t x,int32_t y,int32_t z,int32_t a,double synVel,double synAcc,int32_t segNum=0,short fifo=0);
GT_API GTN_LnXYZAG0Override2WN(short core,short crd,int32_t x,int32_t y,int32_t z,int32_t a,double synVel,double synAcc,int32_t segNum=0,short fifo=0);

GT_API GTN_LnXYZACUVW(short core,short crd,int32_t *pPos,short posMask,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_LnXYZACUVWOverride2(short core,short crd,int32_t *pPos,short posMask,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_LnXYZACUVWWN(short core,short crd,int32_t *pPos,short posMask,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);
GT_API GTN_LnXYZACUVWOverride2WN(short core,short crd,int32_t *pPos,short posMask,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);

GT_API GTN_LnXYZAC(short core,short crd,int32_t *pPos,short posMask,double synVel,double synAcc,double velEnd,short fifo);
GT_API GTN_LnXYZACOverride2(short core,short crd,int32_t *pPos,short posMask,double synVel,double synAcc,double velEnd,short fifo);
GT_API GTN_LnXYZACWN(short core,short crd,int32_t *pPos,short posMask,double synVel,double synAcc,double velEnd,int32_t segNum,short fifo);
GT_API GTN_LnXYZACOverride2WN(short core,short crd,int32_t *pPos,short posMask,double synVel,double synAcc,double velEnd,int32_t segNum,short fifo);

GT_API GTN_LnXYZACG0(short core,short crd,int32_t *pPos,short posMask,double synVel,double synAcc,short fifo);
GT_API GTN_LnXYZACG0Override2(short core,short crd,int32_t *pPos,short posMask,double synVel,double synAcc,short fifo);
GT_API GTN_LnXYZACG0WN(short core,short crd,int32_t *pPos,short posMask,double synVel,double synAcc,int32_t segNum,short fifo);
GT_API GTN_LnXYZACG0Override2WN(short core,short crd,int32_t *pPos,short posMask,double synVel,double synAcc,int32_t segNum,short fifo);


GT_API GTN_ArcXYR(short core,short crd,int32_t x,int32_t y,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_ArcXYROverride2(short core,short crd,int32_t x,int32_t y,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_ArcXYRWN(short core,short crd,int32_t x,int32_t y,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);
GT_API GTN_ArcXYROverride2WN(short core,short crd,int32_t x,int32_t y,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);

GT_API GTN_ArcXYC(short core,short crd,int32_t x,int32_t y,double xCenter,double yCenter,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_ArcXYCOverride2(short core,short crd,int32_t x,int32_t y,double xCenter,double yCenter,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_ArcXYCWN(short core,short crd,int32_t x,int32_t y,double xCenter,double yCenter,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);
GT_API GTN_ArcXYCOverride2WN(short core,short crd,int32_t x,int32_t y,double xCenter,double yCenter,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);

GT_API GTN_ArcYZR(short core,short crd,int32_t y,int32_t z,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_ArcYZROverride2(short core,short crd,int32_t y,int32_t z,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_ArcYZRWN(short core,short crd,int32_t y,int32_t z,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);
GT_API GTN_ArcYZROverride2WN(short core,short crd,int32_t y,int32_t z,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);

GT_API GTN_ArcYZC(short core,short crd,int32_t y,int32_t z,double yCenter,double zCenter,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_ArcYZCOverride2(short core,short crd,int32_t y,int32_t z,double yCenter,double zCenter,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_ArcYZCWN(short core,short crd,int32_t y,int32_t z,double yCenter,double zCenter,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);
GT_API GTN_ArcYZCOverride2WN(short core,short crd,int32_t y,int32_t z,double yCenter,double zCenter,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);

GT_API GTN_ArcZXR(short core,short crd,int32_t z,int32_t x,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_ArcZXROverride2(short core,short crd,int32_t z,int32_t x,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_ArcZXRWN(short core,short crd,int32_t z,int32_t x,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);
GT_API GTN_ArcZXROverride2WN(short core,short crd,int32_t z,int32_t x,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);

GT_API GTN_ArcZXC(short core,short crd,int32_t z,int32_t x,double zCenter,double xCenter,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_ArcZXCOverride2(short core,short crd,int32_t z,int32_t x,double zCenter,double xCenter,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_ArcZXCWN(short core,short crd,int32_t z,int32_t x,double zCenter,double xCenter,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);
GT_API GTN_ArcZXCOverride2WN(short core,short crd,int32_t z,int32_t x,double zCenter,double xCenter,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);

GT_API GTN_ArcXYZ(short core,short crd,int32_t x,int32_t y,int32_t z,double interX,double interY,double interZ,double synVel,double synAcc,double velEnd,short fifo=0);
GT_API GTN_ArcXYZWN(short core,short crd,int32_t x,int32_t y,int32_t z,double interX,double interY,double interZ,double synVel,double synAcc,double velEnd,int32_t segNum,short fifo=0);
GT_API GTN_ArcXYZOverride2WN(short core,short crd,int32_t x,int32_t y,int32_t z,double interX,double interY,double interZ,double synVel,double synAcc,double velEnd,int32_t segNum,short fifo=0);



GT_API GTN_HelixXYRZ(short core,short crd,int32_t x,int32_t y,int32_t z,double radius,short circleDir,double synVel,double synAcc,double velEnd,short fifo=0);
GT_API GTN_HelixXYRZOverride2(short core,short crd,int32_t x,int32_t y,int32_t z,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_HelixXYRZWN(short core,short crd,int32_t x,int32_t y,int32_t z,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);
GT_API GTN_HelixXYRZOverride2WN(short core,short crd,int32_t x,int32_t y,int32_t z,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);

GT_API GTN_HelixXYCZ(short core,short crd,int32_t x,int32_t y,int32_t z,double xCenter,double yCenter,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_HelixXYCZOverride2(short core,short crd,int32_t x,int32_t y,int32_t z,double xCenter,double yCenter,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_HelixXYCZWN(short core,short crd,int32_t x,int32_t y,int32_t z,double xCenter,double yCenter,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);
GT_API GTN_HelixXYCZOverride2WN(short core,short crd,int32_t x,int32_t y,int32_t z,double xCenter,double yCenter,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);

GT_API GTN_HelixYZRX(short core,short crd,int32_t x,int32_t y,int32_t z,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_HelixYZRXOverride2(short core,short crd,int32_t x,int32_t y,int32_t z,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_HelixYZRXWN(short core,short crd,int32_t x,int32_t y,int32_t z,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);
GT_API GTN_HelixYZRXOverride2WN(short core,short crd,int32_t x,int32_t y,int32_t z,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);

GT_API GTN_HelixYZCX(short core,short crd,int32_t x,int32_t y,int32_t z,double yCenter,double zCenter,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_HelixYZCXOverride2(short core,short crd,int32_t x,int32_t y,int32_t z,double yCenter,double zCenter,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_HelixYZCXWN(short core,short crd,int32_t x,int32_t y,int32_t z,double yCenter,double zCenter,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);
GT_API GTN_HelixYZCXOverride2WN(short core,short crd,int32_t x,int32_t y,int32_t z,double yCenter,double zCenter,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);

GT_API GTN_HelixZXRY(short core,short crd,int32_t x,int32_t y,int32_t z,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_HelixZXRYOverride2(short core,short crd,int32_t x,int32_t y,int32_t z,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_HelixZXRYWN(short core,short crd,int32_t x,int32_t y,int32_t z,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);
GT_API GTN_HelixZXRYOverride2WN(short core,short crd,int32_t x,int32_t y,int32_t z,double radius,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);

GT_API GTN_HelixZXCY(short core,short crd,int32_t x,int32_t y,int32_t z,double zCenter,double xCenter,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_HelixZXCYOverride2(short core,short crd,int32_t x,int32_t y,int32_t z,double zCenter,double xCenter,short circleDir,double synVel,double synAcc,double velEnd=0,short fifo=0);
GT_API GTN_HelixZXCYWN(short core,short crd,int32_t x,int32_t y,int32_t z,double zCenter,double xCenter,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);
GT_API GTN_HelixZXCYOverride2WN(short core,short crd,int32_t x,int32_t y,int32_t z,double zCenter,double xCenter,short circleDir,double synVel,double synAcc,double velEnd=0,int32_t segNum=0,short fifo=0);

GT_API GTN_HelixXYRMultiZ(short core,short crd,int32_t *pPos,double radius,short circleDir,double synVel,double synAcc,double velEnd,int32_t segNum,short override2,short fifo);
GT_API GTN_HelixYZRMultiX(short core,short crd,int32_t *pPos,double radius,short circleDir,double synVel,double synAcc,double velEnd,int32_t segNum,short override2,short fifo);
GT_API GTN_HelixZXRMultiY(short core,short crd,int32_t *pPos,double radius,short circleDir,double synVel,double synAcc,double velEnd,int32_t segNum,short override2,short fifo);

GT_API GTN_HelixXYCMultiZ(short core,short crd,int32_t *pPos,double xCenter,double yCenter,short circleDir,double synVel,double synAcc,double velEnd,int32_t segNum,short override2,short fifo);
GT_API GTN_HelixYZCMultiX(short core,short crd,int32_t *pPos,double yCenter,double zCenter,short circleDir,double synVel,double synAcc,double velEnd,int32_t segNum,short override2,short fifo);
GT_API GTN_HelixZXCMultiY(short core,short crd,int32_t *pPos,double zCenter,double xCenter,short circleDir,double synVel,double synAcc,double velEnd,int32_t segNum,short override2,short fifo);

GT_API GTN_HelixXYRMultiZEx(short core,short crd,double *pPos,double radius,short circleDir,double synVel,double synAcc,int32_t segNum,short override2,short fifo);
GT_API GTN_HelixYZRMultiXEx(short core,short crd,double *pPos,double radius,short circleDir,double synVel,double synAcc,int32_t segNum,short override2,short fifo);
GT_API GTN_HelixZXRMultiYEx(short core,short crd,double *pPos,double radius,short circleDir,double synVel,double synAcc,int32_t segNum,short override2,short fifo);

GT_API GTN_HelixXYCMultiZEx(short core,short crd,double *pPos,double xCenter,double yCenter,short circleDir,double synVel,double synAcc,int32_t segNum,short override2,short fifo);
GT_API GTN_HelixYZCMultiXEx(short core,short crd,double *pPos,double yCenter,double zCenter,short circleDir,double synVel,double synAcc,int32_t segNum,short override2,short fifo);
GT_API GTN_HelixZXCMultiYEx(short core,short crd,double *pPos,double zCenter,double xCenter,short circleDir,double synVel,double synAcc,int32_t segNum,short override2,short fifo);


GT_API GTN_BufIO(short core,short crd,unsigned short doType,unsigned short doMask,unsigned short doValue,short fifo=0);
GT_API GTN_BufDelay(short core,short crd,unsigned short delayTime,short fifo=0);
GT_API GTN_BufDA(short core,short crd,short chn,short daValue,short fifo=0);
GT_API GTN_BufAuDA(short core,short crd,short chn,short daValue,short fifo=0);
GT_API GTN_BufLmtsOn(short core,short crd,short axis,short limitType,short fifo=0);
GT_API GTN_BufLmtsOff(short core,short crd,short axis,short limitType,short fifo=0);
GT_API GTN_BufSetStopIo(short core,short crd,short axis,short stopType,short inputType,short inputIndex,short fifo=0);
GT_API GTN_BufMove(short core,short crd,short moveAxis,int32_t pos,double vel,double acc,short modal,short fifo=0);
GT_API GTN_BufGear(short core,short crd,short gearAxis,int32_t pos,short fifo=0);
GT_API GTN_BufGearPercent(short core,short crd,short gearAxis,int32_t pos,short accPercent,short decPercent,short fifo=0);
GT_API GTN_BufStop(short core,short crd,int32_t mask,int32_t option,short fifo);
GT_API GTN_BufStopEx(short core,short crd,int32_t mask,int32_t option,short fifo);
GT_API GTN_BufMoveJog(short core,short crd,short moveAxis,double vel,double acc,short modal,short fifo);
GT_API GTN_BufMoveJogEx(short core,short crd,short moveAxis,double vel,double acc,short modal,short fifo);
GT_API GTN_BufStopMotion(short core,short crd,short fifo=0);
GT_API GTN_BufSetVarValue(short core,short crd,short pageId,TVarInfo *pVarInfo,double value,short fifo=0);
GT_API GTN_BufJumpNextSeg(short core,short crd,short axis,short limitType,short fifo=0);
GT_API GTN_BufSynchPrfPos(short core,short crd,short encoder,short profile,short fifo=0);
GT_API GTN_BufVirtualToActual(short core,short crd,short fifo=0);
GT_API GTN_BufEnableDoBitPulse(short core,short crd,short doType,short doIndex,unsigned short highLevelTime,unsigned short lowLevelTime,int32_t pulseNum,short firstLevel,short fifo);
GT_API GTN_BufDisableDoBitPulse(short core,short crd,short doType,short doIndex,short fifo);
GT_API GTN_BufTrend(short core,short crd,uint32_t trendSegNum,double trendDistance,double trendVelEnd,short fifo);
//�岹��������չģ��ָ��
GT_API GTN_BufExtIO(short core,short crd,unsigned short doIndex,unsigned short doMask,unsigned short doValue,short fifo);
GT_API GTN_BufExtDA(short core,short crd,short chn,short daValue,short fifo);
GT_API GTN_BufExtAoEx(short core,short crd,short aoIndex,double aoValue,short fifo);
GT_API GTN_BufExtDoBitEx(short core,short crd,unsigned short doIndex,unsigned short doValue,short fifo);
GT_API GTN_BufExtDoBit(short core,short crd,unsigned short doIndex,unsigned short doValue,short fifo);
GT_API GTN_BufExtAo(short core,short crd,short aoIndex,double aoValue,short fifo);

GT_API GTN_BufGearListBegin(short core,short crd,short gearAxis,double pos,short fifo);
GT_API GTN_BufGearListAdd(short core,short crd,float k,float percent,short fifo);
GT_API GTN_BufGearListEnd(short core,short crd,short fifo);

typedef struct
{
    double pos;
    double vel;
    double acc;
    double velMax;
    double reserve1[4];
    short smoothTime;
    short enableRatio;
    short modal;
    short fifo;
    short dir;
    short reserve2[3];
    int32_t segNum;
    int32_t reserve3[3];
}TBufMoveAbsPrm;
GT_API GTN_BufMoveAbsoluteEx(short core,short crd,short moveAxis,TBufMoveAbsPrm *pPrm);

typedef struct
{
    short time;
    short aheadOfTime;
    short shape;
    short reverseSmooth;
    double velDelta;
} TCrdBlend;
GT_API GTN_BufSetCrdBlend(short core,short crd,TCrdBlend *pCrdBlend,short fifo);
GT_API GTN_BufCrdBlendOn(short core,short crd,short fifo);
GT_API GTN_BufCrdBlendOff(short core,short crd,short fifo);

/**
 * @brief �岹����������������أ�ע�⣺ֻ�������˶�ֹͣʱ�������ز���Ч
 * @param core �˺ţ�������1��ʼ
 * @param crd �岹����ϵ�ţ�������1��ʼ
 * @param axis ���
 * @param prfTorque ��������
 * @param fifo �岹����ϵ�������ţ�ȡֵ��Χ��[0,1]
 * @return 
*/
GT_API GTN_BufSetPrfTorque(short core,short crd,short axis,short prfTorque,short fifo);

/**
 * @brief �岹ǰհ����������������أ�ע�⣺ֻ�������˶�ֹͣʱ�������ز���Ч
 * @param core �˺ţ�������1��ʼ
 * @param crd �岹����ϵ�ţ�������1��ʼ
 * @param axis ���
 * @param prfTorque ��������
 * @param fifo �岹����ϵ�������ţ�ȡֵ��Χ��[0,1]
 * @return 
*/
GT_API GTN_BufSetPrfTorqueEx(short core,short crd,short axis,short prfTorque,short fifo);
GT_API GTN_CrdStart(short core,short mask,short option);
GT_API GTN_CrdStartStep(short core,short mask,short option);
GT_API GTN_CrdStepMode(short core,short mask,short option);
GT_API GTN_SetOverride(short core,short crd,double synVelRatio);
GT_API GTN_SetOverride2(short core,short crd,double synVelRatio);
GT_API GTN_InitLookAhead(short core,short crd,short fifo,double T,double accMax,short n,TCrdData *pLookAheadBuf);
/**
 * @brief ������ǰհ��С�γ����ڳ�ʼ����ǰհ֮�����
 * @param core �˺�
 * @param crd ����ϵ��
 * @param fifo fifo��
 * @param minSegmentLength ��С�γ�������û���ѹ�����ݶγ�С�ڴ�ֵ����᷵��102�����һ�Ѹö����ݴ��ڲ�fifo���޳�,��λ��pulse
 * @return ����ֵ��1��δ��ʼ����ǰհ��0���ɹ�
*/
GT_API GTN_SetLookAheadMinSegmentLength(short core,short crd,short fifo,double minSegmentLength);

GT_API GTN_GetLookAheadSpace(short core,short crd,int32_t *pSpace,short fifo=0);
GT_API GTN_GetLookAheadSegCount(short core,short crd,int32_t *pSegCount,short fifo=0);
GT_API GTN_CrdClear(short core,short crd,short fifo);
GT_API GTN_CrdStatus(short core,short crd,short *pRun,int32_t *pSegment,short fifo=0);
GT_API GTN_SetUserSegNum(short core,short crd,int32_t segNum,short fifo=0);
GT_API GTN_GetUserSegNum(short core,short crd,int32_t *pSegment,short fifo=0);
GT_API GTN_GetUserSegNumWN(short core,short crd,int32_t *pSegment,short fifo=0);
GT_API GTN_GetRemainderSegNum(short core,short crd,int32_t *pSegment,short fifo=0);
GT_API GTN_GetRemainderSegNumEx(short core,short crd,int32_t *pSegment,short fifo);
GT_API GTN_SetCrdStopDec(short core,short crd,double decSmoothStop,double decAbruptStop);
GT_API GTN_GetCrdStopDec(short core,short crd,double *pDecSmoothStop,double *pDecAbruptStop);
GT_API GTN_SetCrdLmtStopMode(short core,short crd,short lmtStopMode);
GT_API GTN_GetCrdLmtStopMode(short core,short crd,short *pLmtStopMode);
GT_API GTN_GetUserTargetVel(short core,short crd,double *pTargetVel);
GT_API GTN_GetSegTargetPos(short core,short crd,int32_t *pTargetPos);
GT_API GTN_GetCrdPos(short core,short crd,double *pPos);
GT_API GTN_GetCrdVel(short core,short crd,double *pSynVel);
GT_API GTN_SetCrdSingleMaxVel(short core,short crd,double *pMaxVel);
GT_API GTN_GetCrdSingleMaxVel(short core,short crd,double *pMaxVel);

#define DIMENSION_MAX                   (8)                 // ÿ������ϵ�����ά��
typedef struct
{
    int32_t segNumUserSet;
    int32_t segNumInCmd;
    double synPrfVel;
    double prfPosCrd[DIMENSION_MAX];
}TCrdSegSyncInfo;
GT_API GTN_GetCrdSegSyncInfo(short core,short crd,short fifo,TCrdSegSyncInfo *pSegInfo);

typedef struct
{
    short runEmpty;
    int32_t segUseCount;
    int32_t segReceiveCount;
    short pad1[2];
    int32_t pad2[2];
    double pad3[2];
}TCrdStatusEx;
GT_API GTN_CrdStatusEx(short core,short crd,TCrdStatusEx *pCrdStatus,short fifo);

typedef struct
{
    double receive;
    double travel;
    double left;
} TCrdSegmentLength;
GT_API GTN_GetCrdSegmentLength(short core,short crd,TCrdSegmentLength *pSegmentLength,short fifo);

GT_API GTN_SetArcAllowError(short core,short crd, double error);
GT_API GTN_SetArcAllowErrorLa(short core,short crd,double error);

/*-----------------------------------------------------------*/
/* Laser Follow	                                            */
/*-----------------------------------------------------------*/
typedef struct
{
    short laserFollowMode;
    double maxFrq;
    double minFrq;
    double maxDuty;
    double minDuty;
    short pad1[7];
    double pad2[8];
}TLaserFollowPrm;

typedef struct
{
    uint32_t onCount;
    uint32_t offCount;
    uint32_t onCountInFpga;
    uint32_t offCountInFpga;
    uint32_t pad[4];
}TLaserOnOffCount;

typedef struct
{
    double ratio;                                          // ϵ��
    double laserPowerFollowVelMax;                         // mm/s
    double laserPowerFollowFreqMax;                        // KHz
    double laserFollowPulseMax;                            // us
    double pad1[4];
}TLaserFollowSpline2Prm;
GT_API GTN_SetLaserFollowMode(short core,TLaserFollowPrm *pPrm,short channel);
GT_API GTN_LaserFollowOff(short core,short crd,short fifo,short channel);
GT_API GTN_SetLaserFollowTable(short core,short tableId,int32_t n,double *pVel,double *pPower,short channel);
GT_API GTN_GetLaserFollowTable(short core,short tableId,int32_t n,double *pVel,double *pPower,int32_t *pCount,short channel);
GT_API GTN_SetLaserFollowSpline(short core,short tableId,int32_t n,double *pX,double *pY,double beginValue,double endValue,short channel);
GT_API GTN_GetLaserFollowSpline(short core,short tableId,int32_t n,double *pX,double *pY,double *pA,double *pB,double *pC,int32_t *pCount,short channel);
GT_API GTN_GetLaserOnOffCount(short core,short channel,TLaserOnOffCount *pLaserCount);
GT_API GTN_ClearLaserOnOffCount(short core,short channel);

GT_API GTN_BufLaserOn(short core,short crd,short fifo=0,short channel=0);
GT_API GTN_BufLaserOff(short core,short crd,short fifo=0,short channel=0);
GT_API GTN_BufLaserPrfCmd(short core,short crd,double laserPower,short fifo=0,short channel=0);
GT_API GTN_BufLaserFollowMode(short core,short crd,short source,short fifo,short channel,double startPower);
GT_API GTN_BufLaserFollowRatio(short core,short crd,double ratio,double minPower,double maxPower,short fifo,short channel);
GT_API GTN_BufLaserFollowOff(short core,short crd,short fifo,short channel);
GT_API GTN_BufLaserFollowSpline(short core,short crd,short tableId,double minPower,double maxPower,short fifo,short channel);
GT_API GTN_BufLaserFollowTable(short core,short crd,short tableId,double minPower,double maxPower,short fifo,short channel);


GT_API GTN_BufFollowMaster(short core,short crd,TBufFollowMaster *pBufFollowMaster,short fifo=0);
GT_API GTN_BufFollowEventCross(short core,short crd,TBufFollowEventCross *pEventCross,short fifo=0);
GT_API GTN_BufFollowEventTrigger(short core,short crd,TBufFollowEventTrigger *pEventTrigger,short fifo=0);
GT_API GTN_BufFollowStart(short core,short crd,int32_t masterSegment,int32_t slaveSegment,int32_t masterFrameWidth,short fifo=0);
GT_API GTN_BufFollowNext(short core,short crd,int32_t width,short fifo=0);
GT_API GTN_BufFollowReturn(short core,short crd,double vel,double acc,short smoothPercent,short fifo=0);

GT_API GTN_BufLaserOnEx(short core,short crd,short fifo=0,short channel=0);
GT_API GTN_BufLaserOffEx(short core,short crd,short fifo=0,short channel=0);
GT_API GTN_BufLaserFollowModeEx(short core,short crd,short source,short fifo,short channel,double startPower=0);
GT_API GTN_BufLaserFollowTableEx(short core,short crd,short tableId,double minPower,double maxPower,short fifo,short channel);
GT_API GTN_BufLaserFollowOffEx(short core,short crd,short fifo,short channel);
GT_API GTN_BufLaserFollowSpline2Ex(short core,short crd,TLaserFollowSpline2Prm *pPrm,short fifo,short channel);
GT_API GTN_BufLaserPrfCmdEx(short core,short crd,double laserPower,short fifo=0,short channel=0);
GT_API GTN_BufSetPulseWidthEx(short core,short crd,unsigned short width,short fifo=0,short channel=0);
GT_API GTN_BufLaserFollowRatioEx(short core,short crd,double ratio,double minPower,double maxPower,short fifo,short channel);

typedef struct
{
    short frqTableId;
    short dutyTableId;
    double pad1[8];
    short pad2[8];
}TLaserFollowDuoTablePrm;
GT_API GTN_BufLaserFollowDuoTableEx(short core,short crd,TLaserFollowDuoTablePrm *pPrm,short fifo,short channel);

/*-----------------------------------------------------------*/
/* �����������ο������                                      */
/*-----------------------------------------------------------*/

typedef struct
{
    short tableId;
    short channel;
    short enable;
    short loopCount;
    int32_t intervalTime;
    short pad[2];
}TLaserPowerWave;

typedef struct
{
	short tableId;
	short enable;
	short loopIndex;
	short pad;
	double power;
}TLaserPowerWaveStatus;

/**
 * @brief ��ѹ�����������ο��Ʊ�
 * @param core �˺�
 * @param tableId ��ID
 * @param pTime ���ο���ʱ����
 * @param pPower ʱ�����Ӧ�ļ�������������ʱ���֮��Ĳ����������Թ��ɱ仯
 * @param count �����������Ʊ������ݵĸ��������50����
 * @param mode ������������������Ϊ0
 * @return ������
*/
GT_API GTN_SetLaserPowerWaveTable(short core, short tableId, int32_t* pTime, double* pPower, short count, short mode);

/**
 * @brief ����ָ���������������������
 * @param core �˺�
 * @param pLaserPowerWave �����������β�������Ҫѡ���α�ID������ͨ�������ò���ѭ��������ѭ�����
 * @return ������
*/
GT_API GTN_SetLaserPowerWaveEnable(short core, TLaserPowerWave* pLaserPowerWave);

/**
 * @brief �岹�������������������������
 * @param core �˺�
 * @param crd ����ϵ��
 * @param pLaserPowerWave �����������β�������Ҫѡ���α�ID������ͨ�������ò���ѭ��������ѭ�����
 * @param fifo ����ϵfifo��
 * @return
*/
GT_API GTN_BufSetLaserPowerWaveEnable(short core, short crd, TLaserPowerWave* pLaserPowerWave, short fifo);

/**
 * @brief �岹ǰհ�������������������������
 * @param core �˺�
 * @param crd ����ϵ��
 * @param pLaserPowerWave �����������β�������Ҫѡ���α�ID������ͨ�������ò���ѭ��������ѭ�����
 * @param fifo ����ϵfifo��
 * @return ������
*/
GT_API GTN_BufSetLaserPowerWaveEnableEx(short core, short crd, TLaserPowerWave* pLaserPowerWave, short fifo);

/**
 * @brief ����ָ���ȡ���������������״̬
 * @param core �˺�
 * @param laserChannel ����ͨ����
 * @param pLaserPowerWaveStatus ����״̬�������
 * @return ������
*/
GT_API GTN_GetLaserPowerWaveStatus(short core,short laserChannel,TLaserPowerWaveStatus *pLaserPowerWaveStatus);

/*-----------------------------------------------------------*/
/* Crd					                                              */
/*-----------------------------------------------------------*/
GT_API GTN_SetG0Mode(short core,short crd,short mode);
GT_API GTN_GetG0Mode(short core,short crd,short *pMode);

GT_API GTN_SetCrdMapBase(short core,short crd,short base);
GT_API GTN_GetCrdMapBase(short core,short crd,short *pBase);
GT_API GTN_SetCrdBufferMode(short core,short crd,  short bufferMode,short fifo=0);
GT_API GTN_GetCrdBufferMode(short core,short crd,short *pBufferMode,short fifo=0);
GT_API GTN_GetCrdSegmentTime(short core,short crd,int32_t segmentIndex,double *pSegmentTime,int32_t *pSegmentNumber,short fifo=0);
GT_API GTN_GetCrdTime(short core,short crd,TCrdTime *pTime,short fifo=0);
GT_API GTN_SetCrdFollowLoop(short core,short crd,uint32_t loop);
GT_API GTN_GetCrdFollowLoop(short core,short crd,uint32_t *pLoop);
GT_API GTN_SetCrdFollowPrm(short core,short crd,TCrdFollowPrm *pPrm);
GT_API GTN_GetCrdFollowPrm(short core,short crd,TCrdFollowPrm *pPrm);
GT_API GTN_GetCrdFollowStatus(short core,short crd,TCrdFollowStatus *pStatus);


GT_API GTN_SetCrdBlend(short core,short crd,TCrdBlend *pCrdBlend);
GT_API GTN_GetCrdBlend(short core,short crd,TCrdBlend *pCrdBlend);
GT_API GTN_CrdBlendOn(short core,short crd);
GT_API GTN_CrdBlendOff(short core,short crd);
GT_API GTN_CrdEnableVariableCircle(short core,short crd,short fifo);
GT_API GTN_CrdDisableVariableCircle(short core,short crd,short fifo);



GT_API GTN_SetCrdContourErrorControl(short core,short crd,short enable,double percent);
GT_API GTN_GetCrdContourErrorControl(short core,short crd,short *pEnable,double *pPercent);

//////////////////////////////////////////////////////////////////////////
//Smooth
//////////////////////////////////////////////////////////////////////////
GT_API GTN_SetCrdJerkMode(short core, short crd,double jerkMax, short mode);
GT_API GTN_GetCrdJerkMode(short core, short crd,double *pJerkMax, short *pMode);
GT_API GTN_SetCrdJerk(short core,short crd,double jerkMax);
GT_API GTN_GetCrdJerk(short core,short crd,double *pJerkMax);
GT_API GTN_SetCrdJerkTime(short core,short crd,double jerkTime,double coef);
GT_API GTN_GetCrdJerkTime(short core,short crd,double *pJerkTime,double *pCoef);
GT_API GTN_SetCrdJerkEx(short core,short crd,double jerkMax,double acc);
GT_API GTN_GetCrdJerkEx(short core,short crd,double *pJerkMax,double *pAcc);
GT_API GTN_SetCrdAccTime(short core,short crd,short time,short k);
GT_API GTN_GetCrdAccTime(short core,short crd,short *pTime,short *pK);

typedef struct
{
    short percent;
    short accStartPercent;
    short decEndPercent;
    double reserve;
} TCrdSmooth;
GT_API GTN_SetCrdSmooth(short core,short crd,TCrdSmooth *pCrdSmooth);
GT_API GTN_GetCrdSmooth(short core,short crd,TCrdSmooth *pCrdSmooth);
GT_API GTN_SetCrdSmoothTime(short core,short crd,short smoothType,double *pPrm);
GT_API GTN_GetCrdSmoothTime(short core,short crd,short *pSmoothType,double *pPrm);

GT_API GTN_SetAxisPrfVelSmooth(short core,short index,short type,short k);
GT_API GTN_GetAxisPrfVelSmooth(short core,short index,short *pType,short *pK);
GT_API GTN_SetAxisPrfVelSmoothEx(short core,short index,double w,double t,double n);
GT_API GTN_GetAxisPrfVelSmoothEx(short core,short index,double *pW,double *pT,double *pN);
GT_API GTN_SetMotionSmoothWorkMode(short core,short type,short index,short mode);
GT_API GTN_GetMotionSmoothWorkMode(short core,short type,short index,short *pMode);
GT_API GTN_SetAxisMotionSmooth(short core,short axis,double time,double k);
GT_API GTN_GetAxisMotionSmooth(short core,short axis,double *pTime,double *pK);
typedef struct
{
    short optimizeMode;
    short blendingType;
    short pad[2];
    double tolerance;
    double blendingPrm;
    double blendingMinAngle;
    double blendingMaxAngle;
} TPathOptimizePrm;
//�켣�Ż�
GT_API GTN_SetPathOptimizePrmLa(short core,short crd,short enable,short mode,void *pPrm);

typedef struct
{
    short mode;                  //ƽ��ģʽ
    short reserve[3];            //����ֵ
    double prm[6];               //����
}TMotionSmooth;
GT_API GTN_SetMotionSmooth(short core,short index,TMotionSmooth *pSmooth,short count);
GT_API GTN_GetMotionSmooth(short core,short index, TMotionSmooth *pSmooth,short count,short *pCountReturn);

//���ñ��˵�Ӳ��ƽ����Դ����������һ����Ϊ��������ȥ��������
GT_API GTN_SetMotionSmoothFpgaResCount(short core,short count);
GT_API GTN_GetMotionSmoothFpgaResCount(short core,short *pCount);

// Input shaping
GT_API GTN_SetAxisInputShaping(short core,short axis,short enable,short count,double k);
GT_API GTN_SetAxisInputShapingPro(short core,short axis,short enable,double freq,double z);

GT_API GTN_SetPathShaping(short core, short axis, short enable, double t1, double t2);
GT_API GTN_GetPathShaping(short core, short axis, short *pEnable, double *pT1, double *pT2);
GT_API GTN_SetPathShapingPara(short core, short axis, double coef, short level);

/*-----------------------------------------------------------*/
/* Compensate                                                */
/*-----------------------------------------------------------*/
typedef struct
{
    short enable;
    int32_t compValue;
    int32_t compTime;
    short dir;
}TBacklashComp;

typedef struct
{
    short run;
    short pad1[3];
    int32_t  pad2[2];
    double pad3[2];
}TLeadScrewCompStatus;

GT_API GTN_SetBacklash(short core,short axis,int32_t value,double changeValue,int32_t dir);
GT_API GTN_GetBacklash(short core,short axis,int32_t *pValue,double *pChangeValue,int32_t *pDir);
GT_API GTN_SetBacklashComp(short core,short axis,TBacklashComp *pBacklash);
GT_API GTN_GetBacklashComp(short core,short axis,TBacklashComp *pBacklash);
GT_API GTN_SetLeadScrewComp(short core,short axis,short n,int32_t startPos,int32_t lenPos,int32_t *pPositive,int32_t *pNegative);
GT_API GTN_EnableLeadScrewComp(short core,short axis,short mode);
GT_API GTN_SetLeadScrewCrossComp(short core,short axis,short n,int32_t startPos,int32_t lenPos,int32_t *pPositive,int32_t *pNegative,short link);
GT_API GTN_EnableLeadScrewCrossComp(short core,short axis,short mode);
GT_API GTN_SetLeadScrewLink(short core,short axis,short link);
GT_API GTN_GetLeadScrewLink(short core,short axis,short *pLink);
GT_API GTN_GetLeadScrewCompStatus(short core,short axis,TLeadScrewCompStatus *pSts);
GT_API GTN_GetCompensate(short core,short axis,double *pPitchError,double *pCrossError,double *pBacklashError,double *pEncPos,double *pPrfPos);
GT_API GTN_SetLeadScrewCompMode(short core,short axis,short cycleMode,short revCompCycle);
GT_API GTN_SetLeadScrewCompCycleMode(short core,short axis,short cycleMode);
GT_API GTN_GetLeadScrewCompMode(short core,short axis,short *pCycleMode,short *pRevCompCycle);
GT_API GTN_SetFriction(short core,short axis,short gain,double compTime);
GT_API GTN_GetFriction(short core,short axis,short *pGain,double *pCompTime);
GT_API GTN_EnableFriction(short core,short axis);
GT_API GTN_DisableFriction(short core,short axis);
GT_API GTN_SetZeroVelThreshold(short core,short axis,double zeroVelThreshold);
GT_API GTN_GetZeroVelThreshold(short core,short axis,double *pZeroVelThreshold);


typedef struct
{
    short n;
    int32_t startPos;
    int32_t lenPos;
    int32_t *pCompPos;
    int32_t *pCompNeg;
} TLeadScrewPrm;

GT_API GTN_SetLeadScrewTable(short core,short axis,TLeadScrewPrm *pPrm);
GT_API GTN_EnableLeadScrewTable(short core,short axis,int32_t error=0);
GT_API GTN_DisableLeadScrewTable(short core,short axis);
GT_API GTN_GetLeadScrewTablePrfPosCount(short core,int32_t encPos,TLeadScrewPrm *pPrm,short *pCountPositive,short *pCountNegative);
GT_API GTN_GetLeadScrewTablePrfPosPositive(short core,int32_t encPos,TLeadScrewPrm *pPrm,short index,int32_t *pPrfPosPositive);
GT_API GTN_GetLeadScrewTablePrfPosNegative(short core,int32_t encPos,TLeadScrewPrm *pPrm,short index,int32_t *pPrfPosNegative);
GT_API GTN_GetPrfPosBeforeLeadScrewComp(short core,short axis,short dir,double endPos,double *pOriginPos);
typedef struct
{
    short count[2];
    int32_t posBegin[2];
    int32_t step[2];
} TCompensate2DTable;

typedef struct
{
    short enable;
    short tableIndex;
    short axisType[2];
    short axisIndex[2];
} TCompensate2D;

GT_API GTN_SetCompensate2DTable(short core,short tableIndex,TCompensate2DTable *pTable,int32_t *pData,short extend);
GT_API GTN_GetCompensate2DTable(short core,short tableIndex,TCompensate2DTable *pTable,short *pExtend);
GT_API GTN_SetCompensate2DTableRotationAngle(short core,short tableIndex,short enable,double rotationAngle);
GT_API GTN_GetCompensate2DTableRotationAngle(short core,short tableIndex,short *pEnable,double *pRotationAngle);
GT_API GTN_SetCompensate2D(short core,short axis,TCompensate2D *pComp2d);
GT_API GTN_GetCompensate2D(short core,short axis,TCompensate2D *pComp2d);
GT_API GTN_GetCompensate2DValue(short core,short axis,double *pValue);
GT_API GTN_SetCompensate2DMode(short core,short axis,short mode);
GT_API GTN_GetCompensate2DMode(short core,short axis,short *pMode);

GT_API GTN_SetCompensateLimit(short core,short compensateIndex,short compensateType,double minLimit,double maxLimit);
GT_API GTN_GetCompensateLimit(short core,short compensateIndex,short compensateType,double *pMinLimit,double *pMaxLimit);


/*-----------------------------------------------------------*/
/* IO and Encoder                                            */
/*-----------------------------------------------------------*/
typedef struct
{
    short pad1[2];
    int32_t reverseTime;
    int32_t pad2[3];
    double pad3[2];
}TDoBit;

GT_API GTN_SetDo(short core,short doType,int32_t value);
GT_API GTN_SetDoEx(short core,short doType,int32_t *pValue,short count);
GT_API GTN_SetDoBit(short core,short doType,short doIndex,short value);
GT_API GTN_SetDoMultiBit(short core,short doType,int32_t *pValue,int32_t *pMask,short count=1);
GT_API GTN_GetDo(short core,short doType,int32_t *pValue);
GT_API GTN_GetDoEx(short core,short doType,int32_t *pValue,short count);
GT_API GTN_SetDoBitReverse(short core,short doType,short doIndex,short value,short reverseTime);
GT_API GTN_SetDoBitReverseEx(short core,short doType,short doIndex,short value,TDoBit *pDoBit);
GT_API GTN_EnableDoBitPulse(short core,short doType,short doIndex,unsigned short highLevelTime,unsigned short lowLevelTime,int32_t pulseNum,short firstLevel);
GT_API GTN_DisableDoBitPulse(short core,short doType,short doIndex);
GT_API GTN_GetDi(short core,short diType,int32_t *pValue);
GT_API GTN_GetDiBit(short core,short diType,short diIndex,short *pValue);
GT_API GTN_GetDiReverseCount(short core,short diType,short diIndex,uint32_t *pReverseCount,short count=1);
GT_API GTN_SetDiReverseCount(short core,short diType,short diIndex,uint32_t *pReverseCount,short count=1);
GT_API GTN_GetDiRaw(short core,short diType,int32_t *pValue);
GT_API GTN_GetDiEx(short core,short diType,int32_t *pValue,short count);

GT_API GTN_SetGtmDoBit(short core,short station,short slot,short doIndex,short *pValue,short count=1);
GT_API GTN_GetGtmDoBit(short core,short station,short slot,short doIndex,short *pValue,short count=1);
GT_API GTN_GetGtmDiBit(short core,short station,short slot,short diIndex,short *pValue,short count=1);
GT_API GTN_SetDacScale(short core,short dac,int32_t scale);
GT_API GTN_GetDacScale(short core,short dac,int32_t *pScale);
GT_API GTN_SetDac(short core,short dac,short *pValue,short count=1);
GT_API GTN_GetDac(short core,short dac,short *pValue,short count=1,uint32_t *pClock=NULL);
GT_API GTN_SetAuDac(short core,short dac,short *pValue,short count=1);
GT_API GTN_GetAuDac(short core,short dac,short *pValue,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetAdc(short core,short adc,double *pValue,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetAdcValue(short core,short adc,short *pValue,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetAuAdc(short core,short adc,double *pValue,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetAuAdcValue(short core,short adc,short *pValue,short count=1,uint32_t *pClock=NULL);

GT_API GTN_SetAdcFilter(short core,short adc,short filterTime);
GT_API GTN_SetAdcFilterPrm(short core,short adc,double k);
GT_API GTN_GetAdcFilterPrm(short core,short adc,double *pk);
GT_API GTN_SetAuAdcFilterPrm(short core,short adc,double k);
GT_API GTN_GetAuAdcFilterPrm(short core,short adc,double *pk);

GT_API GTN_SetAdcBias(short core,short adc,short bias);
GT_API GTN_GetAdcBias(short core,short adc,short *pBias);
GT_API GTN_SetAuAdcBias(short core,short auAdc,short bias);
GT_API GTN_GetAuAdcBias(short core,short auAdc,short *pBias);


#define DIGITAL_OUTPUT_MODE_NORMAL                    (0)
#define DIGITAL_OUTPUT_MODE_REVERSE_TIME              (10)

typedef struct
{
    double time;
    double reserve[9];
}TDoReverseParameter;

typedef union
{
    TDoReverseParameter doReverse;
    double data[10];
}TDigitalOutputMode;

typedef struct
{
    double distance;
    double delayTime;
    double reserve[8];
}TAtParameter;

typedef struct
{
    double distance;
    double reserve[9];
}TPsoParameter;

typedef struct
{
    double time;
    double reserve[9];
}TTsoParameter;

typedef struct
{
    TAtParameter atPrm;
    TPsoParameter psoPrm;
    TTsoParameter tsoPrm;
    TDoReverseParameter doReverse;
    double data[10];
}TWriteDigitalOutputMode;

typedef struct
{
    short mode;              //Do���ģʽ
    short doType;
    short doIndex;
    short doCount;
    short *pValue;
    short reverse1[2];
    int32_t  reserve2[2];
    TWriteDigitalOutputMode prm;
}TDigitalOutput;

typedef struct
{
    short mode;              //Do���ģʽ
    short doType;
    short doIndex;
    short doValue;
	short reverseTime;
	short reverse1[3];
    int32_t  reserve2[2];
	TWriteDigitalOutputMode prm;
}TDigitalOutputBit;

typedef struct
{
    double delayTime;
    short reserve1[4];
    int32_t reserve2[2];
    double reserve3[2];
}TDelay;

typedef struct
{
    short type;					// type=0:�������distance��Do�����type=1:�����յ�distanceʱDo���
    short motionType;			// ����������Ϊ0��Ŀǰֻ֧�ֲ岹�˶�ָ�
    int32_t delayTime;				// ����������Ϊ0

    double distance;			// �˶�distance��Do�������λmm
}TDigitalOutputProByMoveDistance;

typedef struct
{
    short type;					// type=0:��ʼ�˶�����ʱdelayTime��Do�����type1:�˶�����ǰ��ǰdelayTimeDo���
    short motionType;			// ����������Ϊ0��Ŀǰֻ֧�ֲ岹�˶�ָ�
    short reserve1[2];			// ����������Ϊ0
    double delayTime;			// ʱ��,��λms
}TDigitalOutputProByMoveTime;

typedef struct
{
    double time;				// ��ʱ�����ʱ�䣬��λms
}TDigitalOutputProDelay;

typedef union
{
    double data[30];
    TDigitalOutputProDelay delay;					// ����ʱ���
    TDigitalOutputProByMoveTime moveTime;			// ��ʼ�˶��󣬸����˶�ʱ�������
    TDigitalOutputProByMoveDistance moveDistance;  // ��ʼ�˶��󣬸����˶����������
}TWriteDigitalOutputProPrmUnion;

typedef struct
{
    // Do���ģʽ:
    // ģʽ1����ʱ���;
    // ģʽ2��ִ����һ���岹ָ��ʱ�������趨�ľ����ǰ�ӳ�������߶�ĩ��ǰ���;
    // ģʽ3��ִ����һ���岹ָ��ʱ�������趨��ʱ���ǰ�ӳ�������߶�ĩ��ǰ���;
    short mode;              // Do���ģʽ
    short doType;		     // Do����
    short doIndex;			 // Do����
    short doCount;			 // Do�������
    short *pValue;			 // Do���ֵ��
    short reserve1[2];		 // ����������Ϊ0
    int32_t  reserve2[2];		 // ����������Ϊ0
    TWriteDigitalOutputProPrmUnion prm;
}TDigitalOutputPro;

typedef struct
{
    short aoType;
    short aoIndex;
    short count;
    short reserve1;
    double *pValue;
    int32_t reserve2[3];
}TAnalogOutput;

typedef struct
{
    short diType;
    short diIndex;
    short diCount;
    short *pValue;
    short reverse1[3];
    int32_t  reserve2[2];
}TDigitalInput;

typedef struct  
{
	short inputType;
	short inputIndex;
	short mode;
	short modePrm;
	short reserve1[4];
	double resuerve2[4];
}TStopIoPrm;

GT_API GTN_ReadDigitalInput(short core,short diType,short diIndex,short *pDi,short diCount=1);
GT_API GTN_WaitDigitalInput(short core,TDigitalInput *pDi,TListInfo *pListInfo);
GT_API GTN_WriteDigitalOutput(short core,TDigitalOutput *pDo,TListInfo *pListInfo=NULL);
GT_API GTN_WriteDigitalOutputBit(short core,TDigitalOutputBit *pDoBit,TListInfo *pListInfo=NULL);
GT_API GTN_ReadDigitalOutput(short core,short doType,short doIndex,short *pValue,short doCount=1);
GT_API GTN_ReadAnalogInput(short core,short adcType,short adcIndex,double *pValue,short adcCount);
GT_API GTN_ReadAnalogOutput(short core,short aoType,short aoIndex,double *pValue,short aoCount);
GT_API GTN_WriteAnalogOutput(short core,TAnalogOutput *pAo,TListInfo *pListInfo);
GT_API GTN_SetDelay(short core,TDelay *pDelay,TListInfo *pListInfo);


GT_API GTN_SetAuMtrBias(short core,short dac,short bias);
GT_API GTN_GetAuMtrBias(short core,short dac,short *pBias);
GT_API GTN_SetAuMtrLmt(short core,short dac,short limit);
GT_API GTN_GetAuMtrLmt(short core,short dac,short *pLimit);

GT_API GTN_SetEncPrm(short core,short encoder,int32_t lineNum,short type);
GT_API GTN_GetEncPrm(short core,short encoder,int32_t *pLineNum,short *pType);
GT_API GTN_GetEncLineNum(short core,short encoder,int32_t *pLineNum,short count,uint32_t *pClock);
GT_API GTN_GetEncType(short core,short encoder,short *pType,short count,uint32_t *pClock);
GT_API GTN_SetGratingScale(short core,short index,short *pScale,short count=1);
GT_API GTN_GetGratingScale(short core,short index,short *pScale,short count=1);
GT_API GTN_SetEncPos(short core,short encoder,int32_t encPos);
GT_API GTN_SetEncPosEx(short core,short encoder,double pos);
GT_API GTN_GetEncPos(short core,short encoder,double *pValue,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetEncPosPre(short core,short encoder,double *pValue,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetEncPosRegist(short core,short encoder,double *pValue,short count,uint32_t *pClock);
GT_API GTN_GetEncVel(short core,short encoder,double *pValue,short count=1,uint32_t *pClock=NULL);

GT_API GTN_EncSns(short core,unsigned short sense);
GT_API GTN_LmtSns(short core,unsigned short sense);
GT_API GTN_GpiSns(short core,unsigned short sense);


GT_API GTN_SetPlsPos(short core,short encoder,int32_t encPos);
GT_API GTN_GetPlsPos(short core,short pulse,double *pValue,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetPlsVel(short core,short pulse,double *pValue,short count=1,uint32_t *pClock=NULL);

GT_API GTN_SetAuEncPos(short core,short encoder,int32_t encPos);
GT_API GTN_GetAuEncPos(short core,short encoder,double *pValue,short count=1,uint32_t *pClock=NULL);
GT_API GTN_GetAuEncVel(short core,short encoder,double *pValue,short count=1,uint32_t *pClock=NULL);

GT_API GTN_GetAbsEncPos(short core,short encoder,int32_t *pValue,short mode=0,short param=0);
GT_API GTN_GetAbsEncPosEx(short core,short encoder,short mode,__int64 *pValue);

typedef struct
{
    short type;
    short index;
}TEncoderSource;
GT_API GTN_SetEncoderSource(short core,short encoder,TEncoderSource *pEncoderSource);
GT_API GTN_GetEncoderSource(short core,short encoder,TEncoderSource *pEncoderSource);

typedef struct
{
    short probeType;            // ��������
    short probeIndex;           // ��������
    short latchType;            // ��������
    short latchIndex;           // ��������

    short sense;                // �����ƽ
    short pad[3];
    double filterWidth;         // ������С����
}TSignalDetect;

typedef struct
{
    short status;               // ��ɱ�־,0��δ������1�����У�2�������
    short pad[3];
    double latchWidth;          // ��������ֵ
}TSignalDetectStatus;

GT_API GTN_SetSignalTimeFilter(short core,short type,short index,double filterWidth);
GT_API GTN_GetSignalTimeFilter(short core,short type,short index,double *pFilterWidth);
GT_API GTN_ClearSignalDetect(short core,short index);
GT_API GTN_SetSignalDetect(short core,short index,short enable,TSignalDetect *pPrm);
GT_API GTN_GetSignalDetect(short core,short index,short *pEnable,TSignalDetect *pPrm);
GT_API GTN_GetSignalDetectStatus(short core,short index,TSignalDetectStatus *pPrm);


/*-----------------------------------------------------------*/
/* ExtModule                                                 */
/*-----------------------------------------------------------*/
GT_API GTN_ExtModuleInit(short core,short method=1);
GT_API GTN_SetILinkManuMode(short core,short station);
GT_API GTN_GetILinkManuId(short core,short station,short autoId,short *manuId);
GT_API GTN_GetILinkAutoId(short core,short station,short manuId,short *autoId);
GT_API GTN_SetExtDoBit(short core,short doIndex,short value);
GT_API GTN_GetExtDoBit(short core,short doIndex,short *pValue);
GT_API GTN_SetExtDo(short core,short doIndex,int32_t value,int32_t mask);
GT_API GTN_GetExtDo(short core,short doIndex,int32_t *pValue);
GT_API GTN_GetExtDi(short core,short diIndex,int32_t *pValue);
GT_API GTN_GetExtDiBit(short core,short diIndex,short *pValue);
GT_API GTN_SetExtAoValue(short core,short index,short *pValue,short count=1);
GT_API GTN_GetExtAiValue(short core,short index,short *pValue,short count=1);
GT_API GTN_SetExtAo(short core,short index,double *pValue,short count=1);
GT_API GTN_GetExtAo(short core,short index,double *pValue,short count=1);
GT_API GTN_GetExtAi(short core,short index,double *pValue,short count=1);


GT_API GTN_SetILinkDo(short core,short station,short module,unsigned short data,unsigned short mask);
GT_API GTN_GetILinkDi(short core,short station,short module,unsigned short *data);
GT_API GTN_SetILinkAo(short core,short station,short module,short channel,double data);
GT_API GTN_GetILinkAi(short core,short station,short module,short channel,double *data);

GT_API GTN_SetEHMIType(short core,int32_t length);
GT_API GTN_InitialEHMIIO(short core,char* pCfgFile, char cfgType);
GT_API GTN_InitialEHMIPrm(short core,short inputCount,short outputCount);
GT_API GTN_GetEHMIDo(short core,unsigned char *data,unsigned short offset,unsigned short count);
GT_API GTN_SetEHMIDo(short core,unsigned char *data,unsigned short offset,unsigned short count);
GT_API GTN_GetEHMIDi(short core,unsigned char *data,unsigned short offset,unsigned short count);



/*-----------------------------------------------------------*/
/* Config of Ext-Module                                      */
/*-----------------------------------------------------------*/
typedef struct
{
    short active;
    short checkError;
    short linkError;
    short packageErrorCount;
    short pad[8];
} TExtModuleStatus;

typedef struct
{
    short type;
    short input;
    short output;
} TExtModuleType;

typedef struct
{
    short station;
    short module;
    short index;
} TExtIoMap;

GT_API GTN_OpenExtMdl(short core,char *pDllName);
GT_API GTN_CloseExtMdl(short core);
GT_API GTN_ResetExtMdl(short core);
GT_API GTN_LoadExtConfig(short core,char *pFileName);
GT_API GTN_SetExtIoValue(short core,short module,unsigned short value);
GT_API GTN_GetExtIoValue(short core,short module,unsigned short *pValue);
GT_API GTN_LoadExtModuleConfig(short core,char *pFile);
GT_API GTN_SaveExtModuleConfig(short core,char *pFile);
GT_API GTN_SaveRingNetConfig(short core,char *pFile);
GT_API GTN_ExtModuleOn(short core,short station);
GT_API GTN_ExtModuleOff(short core,short station);
GT_API GTN_GetExtModuleStatus(short core,short station,TExtModuleStatus *pStatus);
GT_API GTN_SetExtModuleId(short core,short station,short count,short *pId);
GT_API GTN_GetExtModuleId(short core,short station,short count,short *pId);
GT_API GTN_SetExtModuleReverse(short core,short station,short module,short inputCount,short *pInputReverse,short outputCount,short *pOutputReverse);
GT_API GTN_GetExtModuleReverse(short core,short station,short module,short inputCount,short *pInputReverse,short outputCount,short *pOutputReverse);
GT_API GTN_GetExtModuleCount(short core,short station,short *pCount);
GT_API GTN_GetExtModuleType(short core,short station,short module,TExtModuleType *pModuleType);
GT_API GTN_SetExtIoMap(short core,short type,short index,TExtIoMap *pMap);
GT_API GTN_GetExtIoMap(short core,short type,short index,TExtIoMap *pMap);
GT_API GTN_ClearExtIoMap(short core,short type);
GT_API GTN_SetExtAoRange(short core,short index,double max,double min);
GT_API GTN_GetExtAoRange(short core,short index,double *pMax,double *pMin);
GT_API GTN_SetExtAiRange(short core,short index,double max,double min);
GT_API GTN_GetExtAiRange(short core,short index,double *pMax,double *pMin);

/*-----------------------------------------------------------*/
/* Pos Compare                                               */
/*-----------------------------------------------------------*/
#define POS_COMPARE_MODE_FIFO                       (0)
#define POS_COMPARE_MODE_LINEAR                     (1)
#define POS_COMPARE_MODE_EQUIDISTANT                (2)
#define POS_COMPARE_MODE_EQUIDISTANT_BUFFER_PERMIT  (3)	// PSO�ȴ���λ����ģʽ
#define POS_COMPARE_MODE_PSO7                       (7) // PSO7ģʽ

#define POS_COMPARE_OUTPUT_PULSE                    (0)
#define POS_COMPARE_OUTPUT_LEVEL                    (1)
#define POS_COMPARE_OUTPUT_AUTO                     (2)

#define POS_COMPARE_SOURCE_ENCODER                  (0)
#define POS_COMPARE_SOURCE_PULSE                    (1)


typedef struct
{
    short mode;
    short dimension;
    short sourceMode;
    short sourceX;
    short sourceY;
    short outputMode;
    short outputCounter;
    unsigned short outputPulseWidth;
    unsigned short errorBand;
} TPosCompareMode;

typedef struct
{
    uint32_t count;
    unsigned short hso;
    unsigned short gpo;

    int32_t startPos;
    int32_t interval;
} TPosCompareLinear;

typedef struct
{
    uint32_t count;
    unsigned short hso;
    unsigned short gpo;

    int32_t startPosX;
    int32_t startPosY;
    int32_t intervalX;
    int32_t intervalY;
} TPosCompareLinear2D;


typedef struct
{
    int32_t pos;
    unsigned short hso;
    unsigned short gpo;
    uint32_t segmentNumber;
} TPosCompareData;

typedef struct
{
    int32_t posX;
    int32_t posY;
    unsigned short hso;
    unsigned short gpo;
    uint32_t segmentNumber;
} TPosCompareData2D;

typedef struct
{
    unsigned short mode;
    unsigned short run;
    unsigned short space;
    uint32_t pulseCount;
    unsigned short hso;
    unsigned short gpo;
    uint32_t segmentNumber;
} TPosCompareStatus;

typedef struct
{
    unsigned short config;
    unsigned short fifoEmpty;
    unsigned short head;
    unsigned short tail;
    uint32_t commandReceive;
    uint32_t commandSend;
    int32_t posX;
    int32_t posY;
} TPosCompareInfo;

typedef struct
{
    uint32_t count;
    unsigned short hso;
    unsigned short gpo;
    int32_t startPosX;
    int32_t startPosY;
    int32_t syncPos;
    int32_t time;
    short reserve[20];
} TPosComparePsoPrm;

typedef struct
{
    uint32_t count;
    unsigned short hso;
    unsigned short gpo;
    int32_t startPosX;
    int32_t startPosY;
    int32_t syncPos;
    int32_t time;
    short pulseWidth;
    short pad;
} TPosComparePsoPrmPro;

typedef struct
{
    short mode;
    unsigned short count;
    short highLevel;
    short lowLevel;
    short resver[20];
} TPosCompareContinueMode;

typedef struct
{
    short	referenceX;
    short	referenceY;
    short	pad1[2];
    double	pad2[2];
} TPosCompareReferencePrm;

typedef struct
{
    short mode;          // 0���������1����Ĭ�����������2�����յ�ǰָ��������Ϣ���
    short timeScale;     // ʱ�侫�ȣ�0��1us��1:0.1us
    short pad1[2];
    double pulseWidth;
    double pad2[3];
}THsoPulsePrm;

typedef struct
{
    short outputMode;
    short level;
    short reserve1[2];
    double highLevelTime;
    double lowLevelTime;
    double reserve2[4];
}TPosComparePulse;

typedef struct
{
    short outputMode;
    short level;
    int32_t count;
    double highLevelTime;
    double lowLevelTime;
    double reserve2[4];
}TPosCompareMultiPulse;

typedef struct
{
    int32_t count;
    short reserve1[2];
    double reserve2[4];
}TPosComparePulseStatus;

typedef struct
{
    uint32_t count;
    unsigned short hso;
    unsigned short gpo;
    int32_t startPosX;
    int32_t startPosY;
    int32_t time;
    short multiNumber;
    short pad1;
    int32_t syncPosArray[256];
} TPosCompareMultiPsoPrm;

typedef struct
{
    short sourceMode;                  // λ�ñȽϵ�����Դѡ��-1��ȡ�����ӣ�0����������1�����������
    short additionX;                   // λ�ñȽ�x��ĵ���������
    short additionY;                   // λ�ñȽ�y��ĵ���������
    short additionZ;                   // λ�ñȽ�z��ĵ���������
}TPosCompareAdditionPrm;

GT_API GTN_PosCompareStart(short core,short posCompareIndex);
GT_API GTN_PosCompareStop(short core,short posCompareIndex);
GT_API GTN_PosCompareClear(short core,short posCompareIndex);
GT_API GTN_PosCompareStatus(short core,short posCompareIndex,TPosCompareStatus *pStatus);
GT_API GTN_PosCompareData(short core,short posCompareIndex,TPosCompareData *pData);
GT_API GTN_PosCompareData2D(short core,short posCompareIndex,TPosCompareData2D *pData);
GT_API GTN_PosComparePulse(short core,short posCompareIndex,short outputMode,short level,unsigned short outputPulseWidth);
GT_API GTN_SetPosComparePulseCount(short core,short posCompareIndex,int32_t count);
GT_API GTN_PosComparePulseEx(short core,short posCompareIndex,TPosComparePulse *pPosComparePulse);
GT_API GTN_PosCompareMultiPulse(short core,short posCompareIndex,TPosCompareMultiPulse *pPosComparePulse);
GT_API GTN_GetPosComparePulseStatus(short core,short posCompareIndex,TPosComparePulseStatus *pPosComparePulseStatus);
GT_API GTN_SetPosCompareMode(short core,short posCompareIndex,TPosCompareMode *pMode);
GT_API GTN_GetPosCompareMode(short core,short posCompareIndex,TPosCompareMode *pMode);
GT_API GTN_SetPosCompareContinueMode(short core,short posCompareIndex,TPosCompareContinueMode *pMode);
GT_API GTN_GetPosCompareContinueMode(short core,short posCompareIndex,TPosCompareContinueMode *pMode);
GT_API GTN_SetPosCompareLinear(short core,short posCompareIndex,TPosCompareLinear *pLinear);
GT_API GTN_GetPosCompareLinear(short core,short posCompareIndex,TPosCompareLinear *pLinear);
GT_API GTN_SetPosCompareLinearBuf(short core,short posCompareIndex,TPosCompareLinear *pLinear);
GT_API GTN_SetPosCompareLinear2D(short core,short posCompareIndex,TPosCompareLinear2D *pLinear);
GT_API GTN_GetPosCompareLinear2D(short core,short posCompareIndex,TPosCompareLinear2D *pLinear);
GT_API GTN_SetPosCompareLinear2DBuf(short core,short posCompareIndex,TPosCompareLinear2D *pLinear);
GT_API GTN_PosCompareInfo(short core,short posCompareIndex,TPosCompareInfo *pInfo);
GT_API GTN_PosCompareHsOn(short core,short posCompareIndex,short link,unsigned short threshold=200);
GT_API GTN_PosCompareHsOff(short core,short posCompareIndex);
GT_API GTN_PosCompareSpace(short core,short posCompareIndex,unsigned short *pSpace);
GT_API GTN_SetPosComparePsoPrm(short core,short posCompareIndex,TPosComparePsoPrm *pPrm);
GT_API GTN_GetPosComparePsoPrm(short core,short posCompareIndex,TPosComparePsoPrm *pPrm);
GT_API GTN_SetPosCompareMultiPsoPrm(short core,short posCompareIndex,TPosCompareMultiPsoPrm *pPrm);
GT_API GTN_GetPosCompareMultiPsoPrm(short core,short posCompareIndex,TPosCompareMultiPsoPrm *pPrm);
GT_API GTN_SetPosComparePsoOffDistance(short core,short posCompareIndex,int32_t distance);
GT_API GTN_SetPosCompareStartLevel(short core,short posCompareIndex,short type,short startLevel);
GT_API GTN_SetPosCompareReference(short core,short posCompareIndex,TPosCompareReferencePrm *pPrm);
GT_API GTN_GetPosCompareReference(short core,short posCompareIndex,TPosCompareReferencePrm *pPrm);
GT_API GTN_SetPosCompareAddition(short core,short posCompareIndex,TPosCompareAdditionPrm *pPrm);
GT_API GTN_GetPosCompareAddition(short core,short posCompareIndex,TPosCompareAdditionPrm *pPrm);
GT_API GTN_SetHsoPulsePrm(short core,short station,short hsoIndex,THsoPulsePrm *pPem,short hsoCount=1);
GT_API GTN_GetHsoPulsePrm(short core,short station,short hsoIndex,THsoPulsePrm *pPem,short hsoCount=1);
GT_API GTN_SetPosComparePulseDuty(short core,short posCompareIndex,double duty);
GT_API GTN_PosCompareVariablePsoData(short core,short posCompareIndex,TPosCompareData *pData);
GT_API GTN_BufPosCompareData2D(short core,short crd,short posCompareIndex,TPosCompareData2D *pData,short fifo);
GT_API GTN_BufPosCompareData2DEx(short core,short crd,short posCompareIndex,TPosCompareData2D *pData,short fifo);

#define POS_COMPARE_THRESHOLD_DEFAULT             (0)     //λ�ý����û����õ�������Χ�󣬸��������㷨�ҵ����ŵ������
#define POS_COMPARE_THRESHOLD_ZERO	              (1)     //λ�ý����û����õ�������Χ���������    
#define POS_COMPARE_THRESHOLD_FPGA	              (2)     //λ�ý����û����õ�������Χ�󣬸�������Ӧ�㷨�ҵ����ŵ������
GT_API GTN_SetPosCompareThresholdMode(short core,short index,short mode);
GT_API GTN_GetPosCompareThresholdMode(short core,short index,short *pMode);
GT_API GTN_SetPosCompareThresholdValue(short core,short index,short thresholdValue);
GT_API GTN_GetPosCompareThresholdValue(short core,short index,short *pThresholdValue);
typedef struct
{
    short mode;                         // 0��FIFOģʽ��1��Linearģʽ 2���ȼ�����ģʽ
    short dimension;                    // 1��1D��2��2D
    short sourceMode;                   // 0���������� 1�����������
    short source[8];                    // �������Ƚ�Դ
    short outputMode;                   // ���ģʽ��0:���� 1:��ƽ2����ƽ�Զ���ת
                                        // (��ƽģʽ���������ƽ�Զ���ת������posCompareData��ƽӰ��)
    short outputCounter;                // ����
    unsigned short outputPulseWidth;    // ����������,��λΪ1us����ƽģʽ�ò�����Ч
    unsigned short errorBand;           // ��άλ�ñȽ��������
    short reserve1[2];
    double reserve2[16];
} TPosCompareModeEx;

typedef struct
{
    uint32_t count;
    unsigned short hso;
    unsigned short gpo;
    int32_t startPosX;
    int32_t startPosY;
    int32_t time;

    short pad1;
    short multiNumber;
    int32_t scale[6];
    double syncPosArray[256];
} TPosComparePsoPrmEx;

GT_API GTN_SetPosCompareModeEx(short core,short posCompareIndex,TPosCompareModeEx *pMode);
GT_API GTN_GetPosCompareModeEx(short core,short posCompareIndex,TPosCompareModeEx *pMode);
GT_API GTN_SetPosComparePsoPrmEx(short core,short posCompareIndex,TPosComparePsoPrmEx *pPrm);
GT_API GTN_GetPosComparePsoPrmEx(short core,short posCompareIndex,TPosComparePsoPrmEx *pPrm);

GT_API GTN_ComparePulse(short core,short level,short outputType,short time);
GT_API GTN_CompareStop(short core);
GT_API GTN_CompareStatus(short core,short *pStatus,int32_t *pCount);
GT_API GTN_CompareData(short core,short encoder,short source,short pulseType,short startLevel,short time, int32_t *pBuf1,short count1,int32_t *pBuf2,short count2);
GT_API GTN_CompareLinear(short core,short encoder,short channel,int32_t startPos,int32_t repeatTimes,int32_t interval,short time,short source);
GT_API GTN_EnablePoscomparePsoPulseWidthFollow(short core,short index,short enable,double velMin,double velMax,double cmpPulseWidthMax);

/*-----------------------------------------------------------*/
/* Config of Position Compare                                */
/*-----------------------------------------------------------*/
typedef struct
{
    short module;
    short fifo;
} TPosCompareMap;

GT_API GTN_SetPosCompareMap(short core,short index,TPosCompareMap *pMap);
GT_API GTN_GetPosCompareMap(short core,short index,TPosCompareMap *pMap);
GT_API GTN_ClearPosCompareMap(short core);

#define POS_COMPARE_MODE_PSO_SYNC_EXTERNAL_SIGNAL	(1)
#define POS_COMPARE_MODE_PSO_SYNC_INTERNAL_SIGNAL	(2)

GT_API GTN_SetPosComparePsoSyncPrm(short core,short posCompareIndex,short psoSyncMode,double frq=100);

#define COMPARE_SEND_DATA_MAX			(30)
#define COMPARE_DATA_MAX				(4096)
#define COMPARE_STEP_MAX				(0x1fff)
#define COMPARE_MAX_NUM					(0x3fffffff)

typedef struct
{
    unsigned short velCompCoeff[3];
    short reserve1[2];
    unsigned short accCompCoeff[3];
    short reserve2[2];
}TPosCompareCompensateCoeff;
GT_API GTN_SetPosCompareCompensateCoeff(short core,short posCompareIndex,TPosCompareCompensateCoeff *pCoeff);
GT_API GTN_GetPosCompareCompensateCoeff(short core,short posCompareIndex,TPosCompareCompensateCoeff *pCoeff);

typedef struct
{
    short index;              // λ�ñȽ�������
    short enable;             // �����ر�
    int32_t  reserve[3];      // ��������
}TPosCompareEnablePro;

typedef struct
{
    short index;
    short pulseWidth;
    short reserve[2];
    uint32_t count;
    int32_t syncPos;
    int32_t time;
} TPosComparePrmPro;

GT_API GTN_SetPosCompareEnablePro(short core,short group,TPosCompareEnablePro *pPrm,TListInfo *pListInfo);
GT_API GTN_SetPosComparePrmPro(short core,short group,TPosComparePrmPro *pPrm,TListInfo *pListInfo);
GT_API GTN_SetPosCompareData2DPro(short core,short index,TPosCompareData2D *pData,TListInfo *pListInfo);

/*-----------------------------------------------------------*/
/* Laser and Scan                                            */
/*-----------------------------------------------------------*/
#define FIFO_MODE_STATIC                  (0)
#define FIFO_MODE_DYNAMIC                 (1)

#define SCAN_STATUS_WAIT                  (0)
#define SCAN_STATUS_RUN	                  (1)
#define SCAN_STATUS_DONE                  (2)

struct TScanInit
{
    int lookAheadNum;
    double time;
    double radiusRatio;
};

typedef struct
{
    uint32_t segmentNumber;
    unsigned short commandNumber;
    unsigned short prfVel;
    unsigned short fifoEmpty;
    unsigned short head;
    unsigned short tail;
    uint32_t commandReceive;
    uint32_t commandSend;
    uint32_t reserve[6];
} TScanInfo;

typedef struct
{
    short enable;
    short superposeSrc;
    short superposeAxisX;
    short superposeAxisY;
    double xCoefficient;
    double yCoefficient;
    double xVelCoefficient;
    double yVelCoefficient;
}TScanPosSuperposeParameter;

typedef struct
{
    unsigned short hso;
    unsigned short powerMode;
    unsigned short power;
    unsigned short powerMax;
    unsigned short powerMin;
    unsigned short frequency;
    unsigned short pulseWidth;
} TLaserInfo;

typedef struct
{
    short n;
    double startVel;
    double power;
}TLaserPowerPrm;

typedef struct
{
    short n;
    double startVel;
    double velStep;
    double *power;
}TLaserPowerTable;

typedef struct
{
    short corrX[65][65];
    short corrY[65][65];
}TScanCorrectionTableData;

GT_API GTN_ScanInit(short core,TScanInit *pScanInit=NULL,double jumpAcc=0,double markAcc=0,short scan=1);
GT_API GTN_ScanCrdDataEnd(short core,short scan=1);
GT_API GTN_SetScanLaserLink(short core,short link,short scan=1);
GT_API GTN_GetScanLaserLink(short core,short *pLink,short scan=1);
GT_API GTN_SetScanMode(short core,short mode,short scan=1);
GT_API GTN_GetScanMode(short core,short *pMode,short scan=1);
GT_API GTN_ClearScanStatus(short core,short scan=1);
GT_API GTN_ScanGetCrdPos(short core,short *pPos,short scan=1);
GT_API GTN_ScanJump(short core,short x,short y,double vel,short scan=1);
GT_API GTN_ScanJumpPoint(short core,short x,short y,double vel,int32_t motionDelayTime,int32_t laserDelayTime,short scan=1);
GT_API GTN_ScanTimeJump(short core,short x,short y,unsigned short time,short scan=1);
GT_API GTN_ScanTimeJumpPoint(short core,short x,short y,unsigned short time,int32_t motionDelayTime,int32_t laserDelayTime,short scan=1);
GT_API GTN_ScanMark(short core,short x,short y,double vel,short scan=1);
GT_API GTN_ScanTimeMark(short core,short x,short y,unsigned short time,short scan=1);
GT_API GTN_ScanBufLaserPrfCmd(short core,double laserPower,short scan=1);
GT_API GTN_ScanBufIO(short core,unsigned short doType,unsigned short doMask,unsigned short doValue,short scan=1);
GT_API GTN_ScanBufDelay(short core,int32_t time,short scan=1);
GT_API GTN_ScanBufDA(short core,unsigned short chn,short value,short scan=1);
GT_API GTN_ScanBufAO(short core,unsigned short chn,double voltage,short scan=1);
GT_API GTN_ScanBufLaserDelay(short core,short laserOnDelay,short laserOffDelay,short scan=1);
GT_API GTN_ScanBufLaserDelayLong(short core,int32_t laserOnDelay,int32_t laserOffDelay,short scan=1);
GT_API GTN_ScanBufLaserOutFrq(short core,double outFrq,short scan=1);
GT_API GTN_ScanBufSetPulseWidth(short core,unsigned short width,short scan=1);
GT_API GTN_ScanBufLaserOn(short core,short scan=1);
GT_API GTN_ScanBufLaserOff(short core,short scan=1);
GT_API GTN_ScanBufStop(short core,short scan=1);
GT_API GTN_ScanLaserIntervalOnList(short core,int32_t time,short scan=1);
GT_API GTN_SetScanDelayTime(short core,unsigned short maxJumpDelay,unsigned short markDelay,unsigned short multiMarkDelayConst,short scan=1);
GT_API GTN_SetScanDelayMode(short core,short multiMarkDelayMode,unsigned short multiMarkLaserOffDelay,unsigned short minJumpDelay,unsigned short jumpDelayLengthLimit,short scan=1);
GT_API GTN_ScanStop(short core,short stopType,short scan=1);
GT_API GTN_ScanCrdSpace(short core,short *pSpace,short scan=1);
GT_API GTN_ScanCrdStart(short core,short scan=1);
GT_API GTN_ScanCrdClear(short core,short scan=1);
GT_API GTN_ScanCrdStatus(short core,short *pRun,short *pCmdId,short scan=1);

GT_API GTN_SetScanPosSuperposeParameter(short core,short scan,TScanPosSuperposeParameter param);
GT_API GTN_GetScanPosSuperposeParameter(short core,short scan,TScanPosSuperposeParameter *pParam);
GT_API GTN_ScanSetCorrectionTable(short core,short scan,TScanCorrectionTableData *pParam);
GT_API GTN_ScanCorrectionOn(short core,short scan);
GT_API GTN_ScanCorrectionOff(short core,short scan);
GT_API GTN_ScanGenerateCorrectionTable(short core,double paraX,double paraY,short rangeX,short rangeY,TScanCorrectionTableData *pParam);
GT_API GTN_GetScanPosSuperposeEncPos(short core,short scan,double *pXPos,double *pYPos);


GT_API GTN_SetScanDaType(short core,short type,short scan);

GT_API GTN_ScanInfo(short core,TScanInfo *pScanInfo,short scan=1);
GT_API GTN_GetScanExecuteTime(short core,short scan,double *pExecuteTime);
GT_API GTN_ClearScanExecuteTime(short core,short scan=1);
GT_API GTN_ScanHsOn(short core,short scan=1,short link=1,unsigned short threshold=200);
GT_API GTN_ScanHsOff(short core,short scan=1);

/*
*   ����˵����ʹ��FPK���ܣ����������ƹ��ܣ�
*   core��         �˺ţ�ȡֵ��Χ��[1,32]
*   time1��        ��ʾFPK�źŵ���Ч��ƽ����ʱ�䣬ȡֵ��Χ��[0,65535]����λ��us
*   time2��        ��ʾFPK�źſ�ʼ����������źſ�ʼ���֮��ļ��ʱ�䣬��������ʱʱ�䣬ȡֵ��Χ��[0,65535]����λ��us
*   laserOffDelay����ʾ����ر���ʱʱ�䣬ȡֵ��Χ��[0,65535]����λ��us
*   channel��      ��Ҫʹ��FPK���ܵļ���ͨ���ţ�ȡֵ��Χ��[0,9]
*/
GT_API GTN_EnaFPK(short core,unsigned short time1,unsigned short time2,unsigned short laserOffDelay,short channel=0);

/*
*   ����˵�����ر�FPK���ܣ����������ƹ��ܣ�����������屣��ʱ�����0����Ҫ�����ع���ʱ����
*   core��         �˺ţ�ȡֵ��Χ��[1,32]
*   channel����Ҫ�ر�FPK���ܵļ���ͨ���ţ�ȡֵ��Χ��[0,9]
*/
GT_API GTN_DisFPK(short core,short channel=0);

GT_API GTN_LaserOn(short core,short laserChannel=0);
GT_API GTN_LaserOff(short core,short laserChannel=0);
GT_API GTN_LaserOnStatus(short core,unsigned short *pValue,short laserChannel=0);
GT_API GTN_LaserPowerMode(short core,short laserPowerMode,double maxValue,double minValue,short laserChannel=0);
GT_API GTN_LaserPrfCmd(short core,double power,short laserChannel=0);
GT_API GTN_LaserOutFrq(short core,double outFrq,short laserChannel=0);
GT_API GTN_SetPulseWidth(short core,unsigned short width,short laserChannel=0);
GT_API GTN_SetLevelDelay(short core,uint32_t highLevelDelay,uint32_t lowLevelDelay,short laserChannel=0);
GT_API GTN_LaserInfo(short core,TLaserInfo *pLaserInfo,short laserChannel=0);
GT_API GTN_WriteLaserPrfCmd(short core,double power,short channel);
GT_API GTN_SetWaitPulse(short core,unsigned short mode,double waitPulseFrq,double waitPulseDuty,short channel);

/**
 * @brief ���ü��⿪�ع��ź���ģ�����źŰ󶨹�ϵ
 * @param core �˺�
 * @param laserChannel ����ͨ���ţ�������0��ʼ
 * @param link �󶨹�ϵ��0�����󶨣�1����
 * @return 17053������ͨ����������
 *         17055���˺Ų�������Ŀǰÿ�ſ�ֻ�е�һ����֧�ּ��⹦��
 *         17500��link��������
 *         11091��������û�нӴ����⹦�ܵĴ�վ
*/
GT_API GTN_SetLaserOnAndVoltageLink(short core,short laserChannel,short link);

/**
 * @brief ��ȡ���⿪�ع��ź���ģ�����źŰ󶨹�ϵ
 * @param core �˺�
 * @param laserChannel ����ͨ���ţ�������0��ʼ
 * @param pLink �󶨹�ϵ��0�����󶨣�1����
 * @return 17053������ͨ����������
 *         17055���˺Ų�������Ŀǰÿ�ſ�ֻ�е�һ����֧�ּ��⹦��
 *         11091��������û�нӴ����⹦�ܵĴ�վ
*/
GT_API GTN_GetLaserOnAndVoltageLink(short core,short laserChannel,short *pLink);

typedef struct
{
    short run;
    short mode;
    double power;
    double frequency;
    double pulseWidth;
    double pad1[9];
    short pad2[8];
} TLaserStatus;
GT_API GTN_GetLaserStatus(short core,short channel,TLaserStatus *pStatus);

GT_API GTN_ScanLaserOn(short core,short scan=1);
GT_API GTN_ScanLaserOff(short core,short scan=1);
GT_API GTN_ScanLaserOnStatus(short core,unsigned short *pValue,short scan=1);
GT_API GTN_ScanSetLaserMode(short core,unsigned short laserMode, short scan=1);
GT_API GTN_ScanLaserPowerMode(short core,short laserPowerMode,double maxValue,double minValue, short scan=1);
GT_API GTN_ScanLaserPrfCmd(short core,double power, short scan=1);
GT_API GTN_ScanLaserOutFrq(short core,double outFrq, short scan=1);
GT_API GTN_ScanSetPulseWidth(short core,unsigned short width, short scan=1);
GT_API GTN_ScanSetLevelDelay(short core,unsigned short highLevelDelay,unsigned short lowLevelDelay, short scan=1);
GT_API GTN_ScanSetDa(short core,short chn,short value,short scan=1);
GT_API GTN_ScanLaserInfo(short core,TLaserInfo *pLaserInfo, short scan=1);

GT_API GTN_ScanSetMotionWithLaserControl(short core,short laserCtrlEnable,short scan=1);
GT_API GTN_ScanGetMotionWithLaserControl(short core,short *pLaserCtrlEnable,short scan=1);

GT_API GTN_SetHsoPwmLink(short core,short station,short hsoIndex);
GT_API GTN_GetHsoPwmLink(short core,short station,short *pHsoIndex);

GT_API GTN_ScanSynchOn(short core);
GT_API GTN_ScanSynchOff(short core);
GT_API GTN_SetScanSynchModePrm(short core,short masterScan,short count,short *synchScan,short synchSignalSource);
GT_API GTN_GetScanWorkMode(short core,short scan,short *pMode);
/*-----------------------------------------------------------*/
/* DLM                                                       */
/*-----------------------------------------------------------*/
#define DLM_FUNCTION_EVENT							(0)
#define DLM_FUNCTION_TIMER							(1)
#define DLM_FUNCTION_BACKGROUND						(2)
#define DLM_FUNCTION_COMMAND						(3)

#define DLM_FUNCTION_PROCEDURE						(7)

#define DLM_FUNCTION_PROFILE_EVENT					(8)
#define DLM_FUNCTION_PROFILE						(9)
#define DLM_FUNCTION_PROFILE_SUPERIMPOSED			(10)
#define DLM_FUNCTION_PROFILE_FILTER					(11)

#define DLM_FUNCTION_SERVO_EVENT					(16)
#define DLM_FUNCTION_SERVO							(17)
#define DLM_FUNCTION_SERVO_SUPERIMPOSED				(18)
#define DLM_FUNCTION_SERVO_FILTER					(19)

#define DLM_LOAD_MODE_NONE							(0)
#define DLM_LOAD_MODE_COMMAND						(1)
#define DLM_LOAD_MODE_BOOT							(2)
#define DLM_LOAD_MODE_RUN							(3)

typedef struct TDlmStatus
{
    int32_t version;
    int32_t date;
    short enable;
    int32_t function;
} TDlmStatus;

typedef struct TDlmFunction
{
    short function;
    short enable;
    int32_t value;
} TDlmFunction;

GT_API GTN_LoadDlm(short core,int32_t vender,int32_t module,char *fileName,short *pId);
GT_API GTN_ProgramDlm(short core,short id,short loadMode);
GT_API GTN_GetDlmLoadMode(short core,short id,short *pLoadMode);
GT_API GTN_RunDlm(short core,short id);
GT_API GTN_StopDlm(short core,short id);
GT_API GTN_GetDlmStatus(short core,short id,TDlmStatus *pStatus);
GT_API GTN_SetDlmFunction(short core,short id,TDlmFunction *pFunction);
GT_API GTN_GetDlmFunction(short core,short id,TDlmFunction *pFunction);

GT_API GTN_DlmCommandInit(short core,short code,int32_t index);
GT_API GTN_DlmCommandAdd16(short core,short value);
GT_API GTN_DlmCommandAdd32(short core,int32_t value);
GT_API GTN_DlmCommandAddFloat(short core,float value);
GT_API GTN_DlmCommandAddDouble(short core,double value);
GT_API GTN_SendDlmCommand(short core,short id,short *pReturnValue);
GT_API GTN_DlmCommandGet16(short core,short *pValue);
GT_API GTN_DlmCommandGet32(short core,int32_t *pValue);
GT_API GTN_DlmCommandGetFloat(short core,float *pValue);
GT_API GTN_DlmCommandGetDouble(short core,double *pValue);
/*-----------------------------------------------------------*/
/* Event-Task                                                */
/*-----------------------------------------------------------*/
#define TASK_SET_DO_BIT                          (0x1101)
#define TASK_SET_DAC                             (0x1120)

#define TASK_STOP                                (0x1303)

#define TASK_TRIGGER_CALLBACK_FUNCTION           (0x119c)

#define TASK_UPDATE_POS                          (0x2002)
#define TASK_UPDATE_VEL                          (0x2004)
#define TASK_UPDATE_DISTANCE                     (0x2022)


#define TASK_PT_START                            (0x2306)
#define TASK_PVT_START                           (0x2346)
#define TASK_MOVE_ABSOLUTE                       (0x2500)

#define TASK_MOVE_CONTINUOUS_ABSOLUTE            (0x2560)

#define TASK_GEAR_START                          (0x3005)

#define TASK_FOLLOW_START                        (0x310A)
#define TASK_FOLLOW_SWITCH                       (0x310B)

#define TASK_CRD_START                           (0x4004)
#define TASK_CRD_OVERRIDE                        (0x4006)

#define TASK_CRD_STEP_MODE                       (0x4015)
#define TASK_SCAN_START                          (0x4102)

#define TASK_START_COMMAND_LIST                  (0x4825)

#define TASK_STOP_COMMAND_LIST                   (0x482B)

#define TASK_MOVE_ESCAPE                         (0x5000)

#define TASK_UPDATE_SERVO_GAIN                   (0x6000)
#define	TASK_SET_TRIGGER_PRM                     (0x6001)

#define TASK_SET_DO_BIT_MODE_NONE                (0)
#define TASK_SET_DO_BIT_MODE_TIME                (10)
#define TASK_SET_DO_BIT_MODE_DISTANCE            (20)

//�����˿ر��������Լ����������������
#define TASK_SAVE_MC_VAR_MAX                     (5)
#define TASK_SAVE_MC_VAR_EX_MAX                 (8)
#define TASK_SAVE_MC_VAR                         (50)
#define TASK_ADJUST_MOVE_JOG_ANGLE_VELOCITY      (51)
#define TASK_SAVE_MC_VAR_EX                     (52)

typedef struct
{
    unsigned short type;
    unsigned short index;
    unsigned short id;
} TWatchVar;

typedef struct
{
    short doType;
    short doIndex;
    short doValue;
    short mode;
    int32_t parameter[8];
} TTaskSetDoBit;

typedef struct
{
    short dac;
    short value;
} TTaskSetDac;

typedef struct
{
    int32_t mask;
    int32_t option;
} TTaskStop;

typedef struct
{
    short type;
    short index;
    short operation;
    short data[20];
} TTaskFifoOperation;

typedef struct
{
    short profile;
    int32_t pos;
} TTaskUpdatePos;

typedef struct
{
    short profile;
    short triggerIndex;
    int32_t distance;
} TTaskUpdateDistance;

typedef struct
{
    short profile;
    double vel;
} TTaskUpdateVel;

typedef struct
{
    int32_t mask;
    int32_t option;
} TTaskPtStart;

typedef struct
{
    int32_t mask;
} TTaskPvtStart;

typedef struct
{
    int32_t mask;
} TTaskGearStart;

typedef struct
{
    int32_t mask;
    int32_t option;
} TTaskFollowStart;

typedef struct
{
    int32_t mask;
} TTaskFollowSwitch;

typedef struct
{
    short profile;
    int32_t pos;
    double vel;
    double acc;
    double dec;
    short percent;
} TTaskMoveAbsolute;

typedef struct
{
    short mask;
    short option;
} TTaskCrdStart;

typedef struct
{
    short crd;
    double synVelOverride;
} TTaskCrdOverride;

typedef struct  
{
    short mask;
    short option;
} TTaskCrdStepMode;

typedef struct
{
    short port;
    short index;
    short count;
} TTaskScanStart;

//����ָ����
typedef struct  
{
    short list;
    short reserve1[23];
} TTaskStartCommandList;

typedef struct  
{
    short option;
    short reserve;
}TTaskTriggerCallbackFunction;

typedef struct
{
    short count;
    TWatchVar var[TASK_SAVE_MC_VAR_MAX];
}TTaskSaveMcVar;

// ���ݲο�Դ�����ٶȣ�����MoveJog�ᣨ��ת�ᣩ�Ľ��ٶȣ�ʹ�ο�Դ���ٶȱ��ֺ㶨
#define TASK_ADJUST_JOG_VEL_RESERVE1_GROUP       (0) // ����jog���ٶ�ʱ��Ҫͬʱ�����岹�ٶȵ�group��
#define TASK_ADJUST_JOG_VEL_RESERVE1_TARGET_TYPE (1) // ������Ŀ�꣺0��jog���ٶ� 1��dac��ѹ
#define TASK_ADJUST_JOG_VEL_RESERVE2_ORIGIN_VEL  (0) // jog���ԭʼ�ٶ�
#define TASK_ADJUST_JOG_VEL_RESERVE2_DAC_RATIO   (1) // �ٶȺ͵�ѹ�ı�����ϵ��ÿ����Ӧ���ٶȣ���λ��(��/s)/��

typedef struct
{
    short profile;                     // ��reserve1[1]Ϊ0ʱ����ʾ��Ҫ�������ٶȵ�MoveJog�Ĺ滮���ţ�����ΪMoveJogģʽ����reserve1[1]ΪMC_DAC����MC_AU_DACʱ����ʾ��Ҫ������dacͨ����
    short refType;                     // �ο�Դ������
    short refIndex;                    // �ο�Դ��������������1��ʼ��û�ж��û����õ�����������
    short refSubIndex;                 // �ο�Դ�Ķ����������������вο�Դ���ж���������������1��ʼ
    short reserve1[4];

    double refPosition;                // �ο�λ�ã�������ο�Դ��ǩλ��������õ�Բ�뾶����λ��mm
    double refLinearVelocity;          // �ο�ԴĿ�����ٶȣ�������ת����ٶȵ�Ŀ���Ǳ������ٶ�ά�����ֵ���䣬��λ��mm/s
    double minAngleVelocity;           // ���ٶ���С���ƣ�������Сֵ������Сֵ��������λ����/s
    double maxAngleVelocity;           // ���ٶ�������ƣ��������ֵ�������ֵ��������λ����/s
    double reserve2[4];
}TTaskAdjustMoveJogAngleVelocity;

typedef struct
{
	short fifo;
	short count;
	TWatchVar var[TASK_SAVE_MC_VAR_EX_MAX];
}TTaskSaveMcVarEx;
typedef struct
{
    uint32_t loop;
    TWatchVar var;
    unsigned short condition;
    double value;
} TEvent;

GT_API GTN_ClearEvent(short core);
GT_API GTN_ClearTask(short core);
GT_API GTN_ClearEventTaskLink(short core);
GT_API GTN_DeleteEvent(short core,short eventIndex);
GT_API GTN_DeleteTask(short core,short taskIndex);
GT_API GTN_DeleteEventTaskLink(short core,short linkIndex);
GT_API GTN_AddEvent(short core,TEvent *pEvent,short *pEventIndex);
GT_API GTN_AddTask(short core,short taskType,void *pTaskData,short *pTaskIndex);
GT_API GTN_AddEventTaskLink(short core,short eventIndex,short taskIndex,short *pLinkIndex);
GT_API GTN_SetEvent(short core,TEvent *pEvent,short eventIndex);
GT_API GTN_SetTask(short core,short taskType,void *pTaskData,short taskIndex);
GT_API GTN_SetEventTaskLink(short core,short eventIndex,short taskIndex,short linkIndex);
GT_API GTN_GetEventCount(short core,short *pCount);
GT_API GTN_GetEvent(short core,short eventIndex,TEvent *pEvent);
GT_API GTN_GetEventLoop(short core,short eventIndex,uint32_t *pEventLoop);
GT_API GTN_GetTaskCount(short core,short *pCount);
GT_API GTN_GetTask(short core,short taskIndex,short *pTaskType,void *pTaskData);
GT_API GTN_GetEventTaskLinkCount(short core,short *pCount);
GT_API GTN_GetEventTaskLink(short core,short linkIndex,short *pEventIndex,short *pTaskIndex);
GT_API GTN_EventOn(short core,short eventIndex,short count);
GT_API GTN_EventOff(short core,short eventIndex,short count);
GT_API GTN_GetTaskSaveMcVarResult(short core,short taskIndex,TWatchVar *pVar,double *pValue,short count,short *pReadCount);
GT_API GTN_GetTaskSaveMcVarResultEx(short core,short index,TWatchVar *pVar,double *pValue,short count,short *pReadCount);
GT_API GTN_SetEventWaitTime(short core,double waitTime);


#define WAIT_TIMEOUT_MODE_INFINITY          (0)
#define WAIT_TIMEOUT_MODE_SKIP              (1)
#define WAIT_TIMEOUT_MODE_STOP              (2)

typedef struct
{
    TWatchVar var;
    unsigned short condition;
    double value;
} TWatchCondition;

typedef struct
{
    unsigned short operation;
    unsigned short varType;
    unsigned short result;
    unsigned short lhs;
    unsigned short rhs;
} TVarCalculate;

typedef struct
{
    short varIndex;
    short reserve[3];
    TWatchCondition watchCondition;
} TVarCondition;

typedef struct
{
    int32_t time;				// ��ʱʱ��
    short mode;		        // ��ʱ�����Ϊ��0�����޵ȴ���1��������ǰ�ȴ���������ִ��ָ������2��ָֹͣ����
    short reserve1;
    double reserve2[4];
} TWaitTimeout;

typedef struct
{
    short enable;
    short loop;
    short reserve[2];
} TConditionTaskEnable;

typedef struct
{
    short halt;
    short reserve1[15];
} TCommandListStopParameter;

//ָֹͣ����
typedef struct
{
    short stopList;
    short stopMode;
    short triggerSource;
    short reserve[5];
    TCommandListStopParameter prm;
} TTaskStopCommandList;

GT_API GTN_SetVarBoolCondition(short core,short varIndex,TWatchCondition *pWatchCondition);
GT_API GTN_GetVarBoolCondition(short core,short varIndex,TWatchCondition *pWatchCondition);
GT_API GTN_LoadVarCalculate(short core,TVarCalculate *pVarCalculate,short count,TListInfo *pListInfo=NULL);
GT_API GTN_AddVarCalculate(short core,TVarCalculate *pVarCalculate,short *pIndex);
GT_API GTN_GetVarCalculate(short core,short index,TVarCalculate *pVarCalculate);
GT_API GTN_GetVarCalculateCount(short core,short *pCount);
GT_API GTN_SetVarCondition(short core,short varIndex,TWatchCondition *pWatchCondition,short conditionCount,short operation,TListInfo *pListInfo);
GT_API GTN_GetVarCondition(short core,short varIndex,TWatchCondition *pWatchCondition,short *pConditionCount,short *pOperation);
GT_API GTN_ClearVar(short core);

GT_API GTN_GetMcVar(short core,const TWatchVar *pVar,double *pValue);
GT_API GTN_SetMcVar(short core, const TWatchVar* pVar, double value, TListInfo* pListInfo = NULL);
GT_API GTN_GetMcVarEx(short core,const TWatchVar *pVar,double *pValue,short count);
GT_API GTN_SetMcVarEx(short core, const TWatchVar* pVar, double* pValue, short count, TListInfo* pListInfo = NULL);

GT_API GTN_WaitForCondition(short core,TWatchCondition *pWatchCondition,short conditionCount,short operation,TWaitTimeout *pTimeout,TListInfo *pListInfo=NULL);
GT_API GTN_GetWaitForCondition(short core,short list,TWatchCondition *pWatchCondition,short *pConditionCount,short *pOperation,TWaitTimeout *pTimeout,short *pConditionResult,short *pConditionDone);

GT_API GTN_SetConditionTask(short core,short conditionTaskindex,TWatchCondition *pWatchCondition,short conditionCount,short operation,short taskType,void *pTaskData,TConditionTaskEnable *pEnable,TListInfo *pListInfo);
GT_API GTN_GetConditionTask(short core,short conditionTaskIndex,TWatchCondition *pWatchCondition,short *pConditionCount,short *pOperation,short *pTaskType,void *pTaskData,TConditionTaskEnable *pEnable);
GT_API GTN_ConditionTaskEnable(short core,short conditionTaskIndex,TConditionTaskEnable *pEnable,TListInfo *pListInfo);
GT_API GTN_ConditionStopCommandList(short core,TWatchCondition *pWatchCondition,short conditionCount,short operation,TTaskStopCommandList *pTask,TListInfo *pListInfo);

GT_API GTN_GetGroupConditionTriggerPos(short core,short group,short index,double *pValue,short count,short coordSystem,short oriMode);
GT_API GTN_GetAxisConditionTriggerPos(short core,short type,short axis,double *pValue,short count);


/*--------- -------------------------------------------------*/
/* Group                                                     */
/*-----------------------------------------------------------*/

#define COORD_SYSTEM_PCS				(0)
#define COORD_SYSTEM_MCS				(1)
#define COORD_SYSTEM_ACS				(2)
#define COORD_SYSTEM_TCS				(3)
#define COORD_SYSTEM_VCS				(4)
#define COORD_SYSTEM_FCS				(5)
#define COORD_SYSTEM_MVCS				(10)
#define COORD_SYSTEM_TCS_USER_DEFINE    (20)
#define COORD_SYSTEM_PCS_USER_DEFINE    (30)  // �û����幤������ϵ��������ʵ����б��ӹ���Ӧ��

#define COORD_SYSTEM_POLAR              (40)
#define COORD_SYSTEM_CYNLINDER          (41)


#define ORI_MODE_NONE				    (0)
#define ORI_MODE_EULER				    (1)
#define ORI_MODE_QUAD				    (2)
#define ORI_MODE_VECTOR				    (3)
#define ORI_MODE_ROTATE_AXIS_POS	    (4)
#define ORI_MODE_SPACE_ROTATE           (5)

#define VEL_MODE_DEFAULT                (0)
#define VEL_MODE_PERCENT                (1)

#define ORI_PROFILE_MODE_MINOR          (0) // �岹ָ����㵽�յ����̬�仯����Ϊ�ӻ�
#define ORI_PROFILE_MODE_MAJOR          (1) // �岹ָ����㵽�յ����̬�仯����Ϊ�Ż�
#define ORI_PROFILE_MODE_COMMAND_DIR    (2) // �岹ָ����㵽�յ����̬�仯������ݲ岹ָ�����õķ������

#define GROUP_PROGRAM_COORD_SYSTEM_TABLE         (0)       // ����̨����ϵģʽ
#define GROUP_PROGRAM_COORD_SYSTEM_PIECE         (1)       // ��������ϵģʽ

#define GROUP_PCS_ROTATE_AXIS_POS_MODE_ORI       (0)       // PCS�µ���ת��λ�������������PCS����ϵ����̬
#define GROUP_PCS_ROTATE_AXIS_POS_MODE_DIRECT    (1)       // PCS�µ���ת��λ�ú�MCS����һ��

#define PCS_USER_DEFINE_COORD_TRANS_COUNT_MAX    (4)       // �û�����ϵ�任�����Ӹ��� 

#define COORD_TRANS_TYPE_EULER          (1)
#define COORD_TRANS_TYPE_QUAD           (2)
#define COORD_TRANS_TYPE_VECTOR	        (3)
#define COORD_TRANS_TYPE_ROTATE_AXIS_POS (4)
#define COORD_TRANS_TYPE_ACS_POS        (5)
#define COORD_TRANS_TYPE_EULER_FIX      (11)
#define COORD_TRANS_TYPE_TOOL_DIR       (20)               // �����᷽��
#define COORD_TRANS_TYPE_OFFSET         (30)               // ƫ��ģʽ
#define COORD_TRANS_TYPE_POINTS         (40)               // ����ģʽ
#define COORD_TRANS_TYPE_TWO_VECTORS    (50)               // ����ʸ��ģʽ
#define COORD_TRANS_TYPE_PROJECT_ANGLE  (60)               // ͶӰ��ģʽ

#define GROUP_INCLINED_PLANE_MODE_ORI_UNCHANGED     (0)    // ����̬б��ӹ�
#define GROUP_INCLINED_PLANE_MODE_ORI_CHANGED       (1)    // ����̬б��ӹ�

#define EULER_MODE_ZYX                  (0)
#define EULER_MODE_ZXZ	                (3)
#define EULER_MODE_XYZ	                (4)

#define ORI_PROFILE_MODE_MINOR          (0) // �岹ָ����㵽�յ����̬�仯����Ϊ�ӻ�
#define ORI_PROFILE_MODE_MAJOR          (1) // �岹ָ����㵽�յ����̬�仯����Ϊ�Ż�
#define ORI_PROFILE_MODE_COMMAND_DIR    (2) // �岹ָ����㵽�յ����̬�仯������ݲ岹ָ�����õķ������
#define VEL_MODE_DEFAULT                (0)
#define VEL_MODE_PERCENT                (1)

#define GROUP_PROGRAM_COORD_SYSTEM_TABLE         (0)       // ����̨����ϵģʽ
#define GROUP_PROGRAM_COORD_SYSTEM_PIECE         (1)       // ��������ϵģʽ

#define GROUP_PCS_ROTATE_AXIS_POS_MODE_ORI       (0)       // PCS�µ���ת��λ�������������PCS����ϵ����̬
#define GROUP_PCS_ROTATE_AXIS_POS_MODE_DIRECT    (1)       // PCS�µ���ת��λ�ú�MCS����һ��
#define KIN_TYPE_ORTHOGONAL             (0)
#define KIN_TYPE_NON_ORTHOGONAL         (1)
#define KIN_TYPE_PARALLEL               (2)
#define KIN_TYPE_ROBOT                  (10)
#define KIN_TYPE_FIVE_AXIS              (20)
#define KIN_TYPE_MULTI_AXIS             (30)
#define KIN_TYPE_CYLINDER               (40)

#define ROBOT_TYPE_SCARA                (0)
#define ROBOT_TYPE_SIX_REVOLUTE         (1)
#define ROBOT_TYPE_FOUR_REVOLUTE        (2)
#define ROBOT_TYPE_PALLETIZE            (3)
#define ROBOT_TYPE_POSITIONER           (4)    //��λ��
#define ROBOT_TYPE_FIVE_REVOLUTE        (5)    //5R������
#define ROBOT_TYPE_XYZRR                (6)    //XYZRR
#define ROBOT_TYPE_SEVEN_REVOLUTE       (7)    //7R
#define ROBOT_TYPE_UR                   (10)   //UR������
#define ROBOT_TYPE_CYLINDER             (20)   //Բ��������
#define CYLINDER_TYPE_NORMAL            (0)
#define ROBOT_TYPE_DELTA                (100)  //Delta������
#define DELTA_TYPE_BASIC                (0)    //��ģ�ͣ�4������
#define DELTA_TYPE_COMMON               (1)    //ͨ��ģ�ͣ�9������
#define DELTA_TYPE_COMMON_PRO           (2)    //ͨ��ģ�ͣ�����������ģ�ͣ�20������

#define SCARA_TYPE_RRPR                 (0)
#define SCARA_TYPE_PRRR                 (1)
#define SCARA_TYPE_RPRR                 (2)
#define SCARA_TYPE_RRRP                 (3)

#define PALLETIZE_TYPE_RPPR             (0)

// ��λ��ROBOT_TYPE_POSITIONER��ģʽ
#define POSITIONER_TYPE_SINGLE          (0)     //�����λ��
#define POSITIONER_TYPE_DUAL            (10)    //˫���λ��

// ���������ROBOT_TYPE_XYZRR����ģʽ
#define XYZRR_TYPE_LIKE_SCARA           (0)     // XYZ+SCARA
#define XYZRR_TYPE_DT_C_ON_A            (100)   // ���Ʊ�׼����˫��ͷ������

// ƽ������ģʽ
#define PARALLEL_INDEPENDENT             (0)    // ƽ����֮��Ϊ������ϵ
#define PARALLEL_SUPERPOSITION           (1)    // ƽ����֮��Ϊ���ӹ�ϵ

// ��������
#define  RW_C_ON_B                      (0) //˫ת̨��B Ϊ��һ��ת�ᣬC Ϊ�ڶ���ת��
#define  RW_B_ON_A                      (1) //˫ת̨��A Ϊ��һ��ת�ᣬB Ϊ�ڶ���ת��
#define  RW_A_ON_B                      (2) //˫ת̨��B Ϊ��һ��ת�ᣬA Ϊ�ڶ���ת��
#define  RW_C_ON_A                      (3) //˫ת̨��A Ϊ��һ��ת�ᣬC Ϊ�ڶ���ת��
#define  DT_B_ON_A                      (4) //˫��ͷ��A Ϊ��һ��ת�ᣬB Ϊ�ڶ���ת��
#define  DT_A_ON_B                      (5) //˫��ͷ��B Ϊ��һ��ת�ᣬA Ϊ�ڶ���ת��
#define  DT_A_ON_C                      (6) //˫��ͷ��C Ϊ��һ��ת�ᣬA Ϊ�ڶ���ת��
#define  DT_B_ON_C                      (7) //˫��ͷ��C Ϊ��һ��ת�ᣬB Ϊ�ڶ���ת��
#define  T_A_W_B                        (8) //ת̨��ͷ��A Ϊ��һ��ת�ᣬB Ϊ�ڶ���ת��
#define  T_B_W_A                        (9) //ת̨��ͷ��B Ϊ��һ��ת�ᣬA Ϊ�ڶ���ת��
#define  T_A_W_C                        (10) //ת̨��ͷ��A Ϊ��һ��ת�ᣬC Ϊ�ڶ���ת��
#define  T_B_W_C                        (11) //ת̨��ͷ��B Ϊ��һ��ת�ᣬC Ϊ�ڶ���ת��
#define  RW_A_ON_C                      (20) //˫ת̨��C Ϊ��һ��ת�ᣬA Ϊ�ڶ���ת��
#define  RW_B_ON_C                      (21) //˫ת̨��C Ϊ��һ��ת�ᣬB Ϊ�ڶ���ת��
typedef struct
{
    short type;
    short subType;          //������
    short dir[8];           //�ؽڷ���0:�붨�巽��ͬ��1���붨�巽����
    short reserve1[6];
    double prm[20];         //�ṹ�������˳�
    double offset[8];       //�ؽ�ƫ�ƣ�ʵ�ʳ�ʼ��̬�붨��ĳ�ʼ��̬��ƫ��(ʵ�ʳ�ʼ��̬�ڶ�������ϵ�µ�λ��)
                            //��λ����ת�᣺�Ƕȣ�ֱ���᣺����
    int32_t reserve2[10];
    double reserve3[11];
}TRobotKinematicParameter;

typedef struct
{
    short type;                          //��������
    short reserve1[3];                   //��������
    double primaryAxisPoint[3];          //��һ��ת��������MCS������
    double slaveAxisPoint[3];            //�ڶ���ת��������MCS������
    double toolLocationPoint[3];         //��������ϵ������MCS������
    short dirMode;                       //��������ģʽ
    short reserve2[2];                   //��������
    short dir[5];                        //���᷽��
    double axisVector[5][3];             //�������߷���
    int32_t reserve3[10];
    double reserve4[16];
}TFiveAxisKinematicParameter;

typedef struct
{
    short axisCount;                     //����
    short reserve1[3];                   //��������
    int32_t reserve2[10];
    double reserve3[42];
}TMultiAxisKinematicParameter;

typedef struct
{
    short subType;                       //0:ƽ����Ϊ������ϵ��1��ƽ����Ϊ���ӹ�ϵ
    short axisCount;                     //����
    short mode;
    short majorAxis[3];
    short reserve1[6];
    short parallelAxis[8];
    int32_t reserve2[10];
    double reserve3[38];
}TParallelParameter;

typedef union
{
    TRobotKinematicParameter robot;
    TFiveAxisKinematicParameter fiveAxis;
    TMultiAxisKinematicParameter multiAxis;
    double data[48];
} TKinematicParameter;

typedef struct
{
    short type;                    //�ṹ����
    short reserve[3];
    TKinematicParameter kinPrm;    //�ṹ����
}TKinematicTransform;

typedef struct
{
    double velMax;
    double accMax;
    double decMax;
    double jerkMax;
    double reserve[10];
} TGroupMotionConstraint;

typedef struct
{
    double oriVelMax;
    double oriAccMax;
    double oriDecMax;
    double oriJerkMax;
    double reserve[10];
} TGroupOrientationConstraint;

typedef struct
{
    double transX;
    double transY;
    double transZ;
    double rotAngle1;
    double rotAngle2;
    double rotAngle3;
}TCartesianParameter;

typedef struct
{
    double vel;				        // λ���ٶȣ���λmm/s
    double oriVel;                  // ��̬�ٶȣ���λ��/s
    double reserve[18];
} TCartesianTransformVelConstraint;

typedef union
{
    TCartesianTransformVelConstraint velConstraint;
    double value[20];
} TCartesianTransformConstraintUnion;

typedef struct
{
    short mode;			// ģʽ
    short reserve[3];
    TCartesianTransformConstraintUnion data;
} TCartesianTransformConstraint;

typedef struct
{
    double prm[8];
    double reserve[12];
}TCoordinateTransformAcsPos;

typedef struct
{
    double transX;             // ���PCSԭ���X��ƽ����
    double transY;             // ���PCSԭ���Y��ƽ����
    double transZ;             // ���PCSԭ���Z��ƽ����
    double rotAngle1;          // ���߲��һ����ת�����ת��
    double rotAngle2;          // ���߲�ڶ�����ת�����ת��
    double alpha;              // ��Z����ת�ĽǶ�
    double reserve[14];
}TCoordinateTransformToolDir;

typedef struct
{
    double prm[8];
    double reserve[12];
}TCoordinateTransformOffset;

// ����ƽ���ڵ�������ָ����ʼ��������ϵ�����ڳ�ʼ��������ϵ�Ͻ���ƽ�ƺ���ת�õ����յ���������ϵ
typedef struct
{
    double point1[3];          // ��1�㣬��ʼ��������ϵ����㣬����ֵΪ���ԭʼPCS��λ��
    double point2[3];          // ��2�㣬��ʼ��������ϵX���������ϵĵ㣬����ֵΪ���ԭʼPCS��λ��
    double point3[3];          // ��3�㣬����ֵΪ���ԭʼPCS��λ��
    double offset[3];          // ������������ϵ��ԭ����Ե�1���ƫ������ƫ��ֵΪ��Գ�ʼ��������ϵ��λ��
    double gama;               // ����������ϵZ����ת�ĽǶ�
    double reserve[7];
}TCoordinateTransformPoints;

// ��������ʸ��ָ������ϵ��ͨ��Zʸ�������Xʸ�������ʸ�����õ�Y�᷽���ٸ���XY�����ַ���õ�Z����
typedef struct
{
    double offset[3];          // ��������ϵ��ԭ�����ԭʼPCS��λ��
    double vector1[3];         // ��������ϵX�������ʸ�����򣬵�λΪ����1
    double vector2[3];         // ��������ϵZ�������ʸ�����򣬵�λΪ����1
    double reserve[11];
}TCoordinateTransformTwoVectors;

// ����ͶӰ��ָ������ϵ
typedef struct
{
    double offset[3];          // ��������ϵ��ԭ�����ԭʼPCS��λ��
    double alpha;              // X����ԭʼ����ϵ��Y����ת�ĽǶ�
    double beta;               // Y����ԭʼ����ϵ��X����ת�ĽǶ�
    double gama;               // ����������ϵZ����ת�ĽǶ�
    double reserve[14];
}TCoordinateTransformProjectAngle;

typedef union
{
    TCoordinateTransformAcsPos acsPos;
    TCartesianParameter euler;
    TCoordinateTransformToolDir toolDir;
    TCoordinateTransformOffset offset;
    TCoordinateTransformPoints points;
    TCoordinateTransformTwoVectors twoVectors;
    TCoordinateTransformProjectAngle projectAngle;
    double value[20];
} TCoordinateTransformUnion;

#define COORDINATE_TRANSFORM_RESERVE_SUB_MODE    (0)

typedef struct
{
    short mode;
    short reserve[3];
    TCoordinateTransformUnion data;
}TCoordinateTransform;

// ��̬����ϵ�任����
typedef struct
{
    short masterType;
    short masterIndex;
    short masterMoveType;
    short trackMode;
    double originPrfPos;
    TCartesianParameter masterOrigin;
    TCartesianParameter pcsToMasterTcs;
    TCartesianParameter dynamicPcsToSlaveMcs;            //����ָ������øò��������ڶ�ȡʵʱ�Ķ�̬PCS��Ϣ
}TDynamicCoordinateTransformData;

typedef union
{
    TDynamicCoordinateTransformData trans;
    double reserve[60];
}TDynamicCoordinateTransformUnion;

typedef struct
{
    short mode;
    short pad[3];
    TDynamicCoordinateTransformUnion prm;
}TDynamicCoordinateTransform;

typedef struct
{
    short masterType;                // ��������
    short masterIndex;               // ��������
    short reserve1[7];
    short commandPosCoord;           // λ����������ϵ
    short commandOrientationMode;    // λ��������̬
    short commandConfigIndex;        // λ�ù��ͽ�
    double pos[8];                   // λ��
    int32_t  reserve2[8];
    double reserve3[8];
}TDynamicCoordinateTransformMasterPos;

// ����ѧ��������
typedef struct
{
    short source;
    short reserve1[7];
    short enableFriction[8];
    short enableCompensate[8];
    int32_t reserve2[8];
    double reserve3[8];
}TGroupDynamicsCompensate;

typedef struct
{
	short master;
	short slave;
	short reserve[2];
	double alpha;
	double beta;
}TGroupCoupleParameter;

typedef struct  
{
	short positiveLimitEnable;
	short negativeLimitEnable;

	short positiveLimitMode;
	short negativeLimitMode;

	double positiveLimit;
	double negativeLimit;
} TGroupSoftLimit;

#define	GROUP_STATE_DISABLED			(0)
#define	GROUP_STATE_ERROR_STOP			(1)
#define	GROUP_STATE_STANDBY				(6)
#define	GROUP_STATE_HOMING				(10)
#define	GROUP_STATE_MOVING				(20)
#define	GROUP_STATE_STOPPING			(30)
#define GROUP_STATUS_RESERVE1_ERROR_STOP_STATE        (0)

typedef struct  
{
	short run;
	short state;
	short stopInfo;	
	short reserve1[13];
	int32_t  reserve2[4];
} TGroupStatus;

typedef struct
{
	double time;				// ���ٶȱ仯ʱ��
	double k;					// ��̬
} TGroupMotionSmooth;

typedef union
{
	TGroupMotionSmooth smooth;
	double value[20];
} TGroupMotionSmoothUnion;

typedef struct 
{
	short mode;
	short reserve[3];	
	TGroupMotionSmoothUnion data;
} TGroupMotionSmoothPrm;

typedef struct
{
    int32_t userTag;
    int32_t segNum;
    double segmentTravel;
    double segmentLength;
    double totalTravel;
    short reserve1[8];
    double reserve2[8];
}TGroupMoveSegmentInfo;

#define OVERRIDE_TYPE_VEL                        (0)
#define OVERRIDE_TYPE_ACC                        (1)

GT_API GTN_AddAxisToGroup(short core,short group,short profile,short identInGroup,TListInfo *pListInfo=NULL);
GT_API GTN_RemoveAxisFromGroup(short core,short group,short identInGroup,TListInfo *pListInfo=NULL);
GT_API GTN_UngroupAllAxes(short core,short group,TListInfo *pListInfo=NULL);
GT_API GTN_GroupEnable(short core,short group,TListInfo *pListInfo=NULL);
GT_API GTN_GroupDisable(short core,short group,TListInfo *pListInfo=NULL);
GT_API GTN_SetGroupVelProfileMode(short core,short group,TVelProfileMode *pSmooth,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupVelProfileMode(short core,short group,TVelProfileMode *pSmooth);
GT_API GTN_GetGroupStatus(short core, short group, TGroupStatus* pStatus);
GT_API GTN_GroupStop(short core,short group,TListInfo *pListInfo=NULL);
GT_API GTN_ClearGroupStatus(short core,short group,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupStatus(short core,short group,TGroupStatus *pStatus);
GT_API GTN_GetProfileGroupInfo(short core,short profile,short *pGroup,short *pIndentInGroup);
GT_API GTN_GetGroupProfilePos(short core,short group,short index,double *pValue,short count=1,short coordSystem=COORD_SYSTEM_ACS,short oriMode=ORI_MODE_NONE);
GT_API GTN_GetGroupProfileVel(short core,short group,short index,double *pValue,short count=1,short coordSystem=COORD_SYSTEM_ACS);
GT_API GTN_GetGroupTargetPos(short core,short group,short index,double *pValue,short count=1,short coordSystem=COORD_SYSTEM_ACS,short oriMode=ORI_MODE_NONE);
GT_API GTN_GetGroupSyntheticVel(short core,short group,double *pValue,short coordSystem=COORD_SYSTEM_ACS);
GT_API GTN_GetGroupBreakPos(short core,short group,short index,double *pValue,short count=1,short coordSystem=COORD_SYSTEM_ACS,short oriMode=ORI_MODE_NONE);
GT_API GTN_GetGroupMoveSegmentInfo(short core,short group,TGroupMoveSegmentInfo *pInfo);
GT_API GTN_GetGroupKinematicConfigIndex(short core,short group,short *pConfigIndex);
GT_API GTN_GetGroupConditionTriggerPos(short core,short group,short index,double *pValue,short count,short coordSystem=COORD_SYSTEM_ACS,short oriMode=ORI_MODE_NONE);
GT_API GTN_SetCommandListLinkGroup(short core,short list,uint32_t linkGroupMask);
GT_API GTN_GetCommandListLinkGroup(short core,short list,uint32_t *pLinkGroupMask);
GT_API GTN_SetGroupLinkCommandList(short core,short group,uint32_t linkListMask);
GT_API GTN_GetGroupLinkCommandList(short core,short group,uint32_t *pLinkListMask);
GT_API GTN_SetGroupMotionConstraint(short core, short group, TGroupMotionConstraint* pPrm, TListInfo* pListInfo = NULL);
GT_API GTN_GetGroupMotionConstraint(short core, short group, TGroupMotionConstraint* pPrm);
GT_API GTN_SetGroupOrientationConstraint(short core, short group, TGroupOrientationConstraint* pPrm, TListInfo* pListInfo = NULL);
GT_API GTN_GetGroupOrientationConstraint(short core, short group, TGroupOrientationConstraint* pPrm);
GT_API GTN_SetGroupCartesianTransform(short core, short group, short coordSystem, short enable, TCartesianParameter* pPrm, TListInfo* pListInfo = NULL);
GT_API GTN_GetGroupCartesianTransform(short core, short group, short coordSystem, short* pEnable, TCartesianParameter* pPrm);
GT_API GTN_SetGroupCoordinateTransform(short core, short group, short coordSystem, short enable, TCoordinateTransform* pPrm, TListInfo* pListInfo = NULL);
GT_API GTN_GetGroupCoordinateTransform(short core, short group, short coordSystem, short* pEnable, TCoordinateTransform* pPrm);
GT_API GTN_SetGroupCoordinateTransformPrm(short core, short group, short coordSystem, short enable, TCoordinateTransform* pPrm, short count = 1, TListInfo* pListInfo = NULL);
GT_API GTN_GetGroupCoordinateTransformPrm(short core, short group, short coordSystem, short* pEnable, TCoordinateTransform* pPrm, short* pCount);
GT_API GTN_SetGroupCartesianTransformConstraint(short core, short group, short coordSystem, short enable, TCartesianTransformConstraint* pConstraint, TListInfo* pListInfo = NULL);
GT_API GTN_GetGroupCartesianTransformConstraint(short core, short group, short coordSystem, short* pEnable, TCartesianTransformConstraint* pConstraint);



GT_API GTN_SetGroupDynamicCoordinateTransform(short core, short group, short enable, TDynamicCoordinateTransform* pTrans, TListInfo* pListInfo = NULL);
GT_API GTN_GetGroupDynamicCoordinateTransform(short core, short group, short* pEnable, TDynamicCoordinateTransform* pTrans);
GT_API GTN_SetGroupDynamicCoordinateParameter(short core, short group, short mode, void* pPrm, TListInfo* pListInfo = NULL);
GT_API GTN_GetGroupDynamicCoordinateParameter(short core, short group, short mode, void* pPrm);
GT_API GTN_SetGroupKinematicTransform(short core, short group, TKinematicTransform* pTransform, TListInfo* pListInfo = NULL);
GT_API GTN_GetGroupKinematicTransform(short core, short group, TKinematicTransform* pTransform);
GT_API GTN_SetGroupDynamicsParameter(short core, short group, short count, double* pPrm, TListInfo* pListInfo = NULL);
GT_API GTN_GetGroupDynamicsParameter(short core, short group, short* pCount, double* pPrm);
GT_API GTN_SetGroupDynamicsCompensate(short core,short group,short mode,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupDynamicsCompensate(short core,short group,short *pMode);
GT_API GTN_SetGroupDynamicsSource(short core,short group,short source,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupDynamicsSource(short core,short group,short *pSource);
GT_API GTN_SetGroupDynamicCoordinateMasterPos(short core, short group, short enable, TDynamicCoordinateTransformMasterPos* pMasterPos);

GT_API GTN_SetGroupAcsOriginPos(short core,short group,double originPos[],TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupAcsOriginPos(short core,short group,short index,double originPos[],short count);
GT_API GTN_SetGroupAcsKinematicOffset(short core,short group,double offset[],TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupAcsKinematicOffset(short core,short group,short index,double *pValue,short count);
GT_API GTN_SetGroupAcsVelLimit(short core,short group,short motionMode,short enable,double *pAcsVelLimit,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupAcsVelLimit(short core,short group,short motionMode,short *pEnable,double *pAcsVelLimit);
GT_API GTN_SetGroupAcsMoveMode(short core,short group,short index,short mode,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupAcsMoveMode(short core,short group,short index,short *pMode);
GT_API GTN_SetGroupCouple(short core,short group,short count,TGroupCoupleParameter *pGroupCouplePrm,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupCouple(short core,short group,short *pCount,TGroupCoupleParameter *pGroupCouplePrm);
GT_API GTN_GetGroupCouplePos(short core,short group,short index,double *pValue,short count=1);
GT_API GTN_SetGroupVelModifyByTaskMode(short core,short group,short mode,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupVelModifyByTaskMode(short core,short group,short *pMode);

GT_API GTN_SetGroupCommandPosDefine(short core,short group,short coordSystem,short orientationMode,short configIndex,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupCommandPosDefine(short core,short group,short *pCoordSystem,short *pOrientationMode,short *pConfigIndex);
GT_API GTN_SetGroupCommandVelDefine(short core,short group,short type,short mode,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupCommandVelDefine(short core,short group,short type,short *pMode);
GT_API GTN_SetGroupProfileCoordinateSystem(short core,short group,short coordSystem,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupProfileCoordinateSystem(short core,short group,short *pCoordSystem);
GT_API GTN_SetGroupOrientationProfileMode(short core,short group,short profileMode,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupOrientationProfileMode(short core,short group,short *pProfileMode);
GT_API GTN_SetGroupOrientationMotionRatio(short core,short group,double ratio,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupOrientationMotionRatio(short core,short group,double *pRatio);
GT_API GTN_SetGroupOrientationMotionMode(short core,short group,short mode,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupOrientationMotionMode(short core,short group,short *pMode);
GT_API GTN_SetGroupProgramCoordinateSystem(short core,short group,short mode,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupProgramCoordinateSystem(short core,short group,short *pMode);
GT_API GTN_SetGroupPcsRotateAxisPosMode(short core,short group,short mode,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupPcsRotateAxisPosMode(short core,short group,short *pMode);
GT_API GTN_SetGroupCommandVelRefAxis(short core,short group,int32_t velAxisMask,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupCommandVelRefAxis(short core,short group,int32_t *pVelAxisMask);
GT_API GTN_SetGroupCommandVelRefRatio(short core,short group,short ident,double *pRatio,short count=1,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupCommandVelRefRatio(short core,short group,short ident,double *pRatio,short count=1);
GT_API GTN_SetGroupMaxOverride(short core,short group,short type,double override,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupMaxOverride(short core,short group,short type,double *pMaxOverride);
GT_API GTN_SetGroupSoftLimit(short core,short group,short coordSystem,short index,TGroupSoftLimit *pPrm,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupSoftLimit(short core,short group,short coordSystem,short index,TGroupSoftLimit *pPrm);
GT_API GTN_SetGroupMotionSmooth(short core,short group,TGroupMotionSmoothPrm *pPrm,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupMotionSmooth(short core,short group,TGroupMotionSmoothPrm *pPrm);
GT_API GTN_SetGroupCircularParameter(short core,short group,short type,void *pData,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupCircularParameter(short core,short group,short type,void *pData);
GT_API GTN_SetGroupErrorStopRatio(short core,short group,double errorStopRatio);
GT_API GTN_GetGroupErrorStopRatio(short core,short group,double *pErrorStopRatio);

typedef struct
{
    TKinematicTransform kinTrans;

    short enablePcsTrans;
    short enableTcsTrans;
    short reserve1[2];
    TCartesianParameter pcsTrans;
    TCartesianParameter tcsTrans;
    double acsKinOffset[8];

    short inputCoordSystem;
    short inputOriMode;
    short configIndex;
    short outputOriMode;
    double preAcsPos[8];

    short reserve2[4];
    double reserve3[8];
}TCoordinateTransformParameter;

typedef struct
{
    TKinematicTransform kinTrans;

    short enablePcsTrans;
    short enableTcsTrans;
    short enableUserPcsTrans;
    short reserve1[5];
    TCoordinateTransform pcsTrans;
    TCoordinateTransform tcsTrans;
    TCoordinateTransform userPcsTrans;
    double acsKinOffset[8];

    short inputCoordSystem;
    short inputOriMode;
    short configIndex;
    short outputOriMode;
    double preAcsPos[8];

    short reserve2[4];
    double reserve3[8];
}TCoordinateTransformParameterEx;

#define GROUP_TRANSFORM_PRM_RESERVE2_ACS_POS_TYPE        (0)
#define GROUP_TRANSFORM_PRM_RESERVE2_PROGRAM_MODE        (2)
typedef struct
{
    TKinematicTransform kinTrans;

    short enablePcsTrans;
    short enableTcsTrans;
    short enableUserPcsTrans;
    short userPcsTransCount;
    short inclinedPlaneMode;
    short inclinedPlaneConfigIndex;
    short reserve1[2];
    TCoordinateTransform pcsTrans;
    TCoordinateTransform tcsTrans;
    TCoordinateTransform userPcsTrans[4];
    double acsKinOffset[8];
    double preRotateAxisPos[2];

    short inputCoordSystem;
    short inputOriMode;
    short configIndex;
    short outputOriMode;
    double preAcsPos[8];

    short reserve2[4];
    double reserve3[8];
}TGroupPosTransformPrm;

typedef struct
{
    double pcsPos[8];
    double mcsPos[8];
    double acsPos[8];
}TCoordinatePos;

GT_API GTN_GroupCoordinateTransform(short core, TCoordinateTransformParameter* pPrm, double* pInputPos, TCoordinatePos* pCoordPos, short* pConfigIndex);
GT_API GTN_GroupCoordinateTransformEx(short core, TCoordinateTransformParameterEx* pPrm, double* pInputPos, TCoordinatePos* pCoordPos, short* pConfigIndex);
GT_API GTN_UTL_GroupPosTransform(short core, TGroupPosTransformPrm* pPrm, double* pInputPos, TCoordinatePos* pCoordPos, short* pConfigIndex);

#define GROUP_TRANSFORM_INPUT_RESERVE1_ACS_POS_TYPE        (7)
typedef struct  
{
	short coordSystem;
	short oriMode;
	short configIndex;
	short targetOriMode;
	short reserve1[8];
	double inputPos[8];
	double preAcsPos[8];
	double reserve2[24];
}TGroupPosTransformInput;

typedef struct  
{
	short configIndex;
	short singularity;
	short reserve1[10];
	double pcsPos[8];
	double mcsPos[8];
	double acsPos[8];
	double reserve2[16];
}TGroupPosTransformOutput;

GT_API GTN_GroupPosTransform(short core,short group,TGroupPosTransformInput *pInput,TGroupPosTransformOutput *pOutput);
typedef struct
{
    double deceleration;
    double jerk;
    short reserve1[4];
    double reserve2[5];
} TGroupStopParameter;

#define GROUP_INDENT_MAX                         (8)

// �岹ģʽ
#define GROUP_PATH_MODE_GENERAL                  (0)     // ͨ�ò岹ģʽ
#define GROUP_PATH_MODE_POLAR                    (1)     // ���岹ģʽ
#define GROUP_PATH_MODE_CYNLINDER                (2)     // Բ���岹ģʽ

// �岹ƽ��
#define GROUP_PATH_PLANE_XY                      (0)
#define GROUP_PATH_PLANE_YZ                      (1)
#define GROUP_PATH_PLANE_ZX                      (2)

typedef struct
{
    short plane;                       // �岹ƽ��
    short reserve1[5];
    short rotateIdent;                 // ��ת����group�е����
    short setOriginFlag;               // ��������ʶ��0��������ϵ�����λ�ڹ�������ϵ����㣬1��������ϵ�����ͨ��originPos����
    double origin[3];                  // ������ϵ��������MCSҲ��������ACS��ƫ����
    double rotateOrigin;               // ��ת����㣬��������λ�ڼ�����ϵX��ʱ��ת�������ACSλ��
	double reserve2[14];
} TGroupPathPolar;

typedef struct
{
    short plane;                       // �岹ƽ��
    short reserve1[4];
    short linearIdent;                 // ֱ������group�е����
    short rotateIdent;                 // ��ת����group�е����
    short setOriginFlag;               // ��������ʶ��0��Բ������ϵ�����λ�ڹ�������ϵ����㣬1��Բ������ϵ�����ͨ��originPos����
    double r;                          // Բ���뾶
    double origin[3];                  // Բ������ϵ��������MCSҲ��������ACS��ƫ����
    double rotateOrigin;               // ��ת����㣬��������λ��Բ������ϵ���ʱ��ת�������ACSλ��
	double reserve2[13];
} TGroupPathCynlinder;

typedef union
{
    TGroupPathPolar polar;
    TGroupPathCynlinder cynlinder;
    double value[20];
} TGroupPathUnion;

typedef struct
{
    short mode;
    short reserve[3];
    TGroupPathUnion data;
} TGroupPathPrm;


GT_API GTN_SetGroupStopParameter(short core, short group, short type, TGroupStopParameter* pPrm, TListInfo* pListInfo = NULL);
GT_API GTN_GetGroupStopParameter(short core, short group, short type, TGroupStopParameter* pPrm);
GT_API GTN_SetGroupPathMode(short core, short group, TGroupPathPrm* pPrm, TListInfo* pListInfo = NULL);
GT_API GTN_GetGroupPathMode(short core, short group, TGroupPathPrm* pPrm);

// GTN_SetGroupLookAheadFunc
#define LA_FUNC_MODE_DV_MAX_LIMIT      (1) // ����dvmaxԼ������ز���
#define LA_FUNC_MODE_SOFTLIMIT_CHECK   (2) // ����λ���
#define LA_FUNC_MODE_DV_MAX_THRESHOLD  (3) // ����dvmaxԼ������ֵ
#define LA_FUNC_MODE_GEOMETRY_LIMIT    (4) // ���ü���Լ������Чģʽ��0����������ϵ��1��������ϵ��2�����ʺͼнǶ���Լ��
#define LA_FUNC_MODE_LA_PRM_TYPE       (99)// ���õ�ǰհ�������ͣ�0��ʱ�䳣��������ϵ����1����������ϵ��

typedef struct
{
    int32_t lookAheadNum;					//ǰհ����
    short reserve1[6];
    int32_t reserve2[4];
    double time;						//ʱ�䳣��
    double radiusRatio;					//�������Ƶ��ڲ���
    double reserve3[7];
}TGroupLookAheadParameter;

typedef struct
{
    int32_t segNum;
    int32_t userTag;
    double data[32];
}TLookAheadErrorInfo;

#define BLEND_MODE_NONE                  0       // �޹켣����
#define BLEND_MODE_ARC                   1       // Բ������
#define BLEND_MODE_BIARC                 2       // ˫Բ������
#define BLEND_MODE_SPLINE                3       // ��������

#define BLEND_PARA_TYPE_ERROR            0       // ���ɲ���Ϊ���ֵ
#define BLEND_PARA_TYPE_RADIUS           1       // ���ɲ���Ϊ�뾶
#define BLEND_PARA_TYPE_DISTANCE         2       // ���ɲ���Ϊ����ɵ�ľ���

#define VEL_BLEND_MODE_NONE              0       // �������ٶ�blending���Ե�һ�ε��ٶȹ��ɣ��Ҳ����й켣blending
#define VEL_BLEND_MODE_BUFFERER          1       // ���ٵ�0���Ҳ����й켣blending
#define VEL_BLEND_MODE_LOW               2       // ����������͵��ٶȹ��ɣ����ݹ켣blending�������й켣����
#define VEL_BLEND_MODE_PREVIOUS          3       // �Ե�һ�ε��ٶȹ��ɣ����ݹ켣blending�������й켣����
#define VEL_BLEND_MODE_NEXT              4       // �Եڶ��ε��ٶȹ��ɣ����ݹ켣blending�������й켣����
#define VEL_BLEND_MODE_HIGH              5       // ����������ߵ��ٶȹ��ɣ����ݹ켣blending�������й켣����

typedef struct
{
    short blendType;
    short prmType;
    short reserve1[2];
    double prm;
    double reserve2[8];
    double minAngle;
    double maxAngle;
} TPathBlendingParameter;

typedef struct
{
    short blendType;                   // �ٶ�blending������
    short prmType;                     // ��������
    short reserve[5];
    short percentMode;                 // �ٶȰٷֱ�ģʽ��0�������ٶ�Ϊ��blendType�������ٶȣ�1�������ٶ�Ϊ��blendType�������ٶ�*���õİٷֱȡ�
    double percent;                    // �ٶȰٷֱȣ���percentModeΪ1ʱ��Ч����Χ��[0,1]��
    double prm[17];
} TVelBlendingParameter;

typedef union
{
    TPathBlendingParameter pathBlendingPrm;
    TVelBlendingParameter velBlendingPrm;
    double data[20];
} TBlendingParameter;

typedef struct
{
    short mode;			// ģʽ
    short reserve[3];
    TBlendingParameter prm;
} TGroupBlendingParameter;

#define GEOMETRY_LIMIT_MODE_WORK    (0)    //���ݹ�������ϵ�����ʺͼнǽ�������
#define GEOMETRY_LIMIT_MODE_AXIS    (1)    //����������ϵ�����ʺͼнǽ�������
#define GEOMETRY_LIMIT_MODE_NONE    (2)    //���ʺͼнǶ���Լ��

typedef struct
{
	short type;                         // 0: ��Լ��ģʽ��1����Լ��ģʽ
	short optMode;                      // �Ƿ��dvmaxԼ�������Ż�
}TGroupDvMaxLimit;

GT_API GTN_GroupLookAheadEnable(short core, short group, TListInfo* pListInfo=NULL);
GT_API GTN_GroupLookAheadDisable(short core, short group, TListInfo* pListInfo=NULL);
GT_API GTN_SetGroupLookAheadParameter(short core, short group, TGroupLookAheadParameter* pLookAheadPrm, TListInfo* pListInfo=NULL);
GT_API GTN_GetGroupLookAheadSegCount(short core,short group,int32_t *pSegCount);
GT_API GTN_GetLookAheadErrorInfo(short core, short group, TLookAheadErrorInfo* pLaErrorInfo);
GT_API GTN_SetGroupBlendingParameter(short core, short group, TGroupBlendingParameter* pPrm, TListInfo* pListInfo=NULL);
GT_API GTN_SetGroupCartesianCoordinateAxisLimit(short core,short group,short enable,TListInfo *pListInfo=NULL);
GT_API GTN_SetGroupLookAheadFunc(short core,short group,short mode,void *pLookAheadFunc,TListInfo *pListInfo=NULL);
GT_API GTN_SetGroupMinLinearLength(short core,short group,short type,double value,TListInfo *pListInfo=NULL);

typedef struct
{
    double value[2];
    double reserve[14];
}TRotateAxisPos;

typedef struct
{
    double value[3];
    double reserve[13];
}TToolVector;

typedef union
{
    TRotateAxisPos rotateAxisPos;
    TToolVector toolVector;
    double value[16];
}TInclinePlaneRotateAxisInfoUnion;

typedef struct
{
    short mode;
    short pad[3];
    TInclinePlaneRotateAxisInfoUnion data;
}TInclinedPlaneRotateAxisInfo;

typedef struct
{
    short configIndex;
    short reserve1[3];
    double reserve2[9];
}TSelectConfig;

typedef union
{
    TSelectConfig select;
    double value[10];
}TGroupInclinedPlanePrmUnion;

typedef struct
{
    short mode;
    short reserve[3];
    TGroupInclinedPlanePrmUnion data;
}TGroupInclinedPlanePrm;

GT_API GTN_SetGroupInclinedPlaneRotateAxisPos(short core, short group, TInclinedPlaneRotateAxisInfo* pInfo, double* pRotateAxisPos, short activeRotateAxis = 1, TListInfo* pListInfo = NULL);
GT_API GTN_GetGroupInclinedPlaneRotateAxisPos(short core, short group, double* pRotateAxisPos);
GT_API GTN_CalGroupInclinedPlaneRotateAxisPos(short core, short group, TToolVector* pToolVector, double* pRotateAxisPos1, double* pRotateAxisPos2, TListInfo* pListInfo = NULL);
GT_API GTN_SetGroupInclinedPlanePrm(short core, short group, TGroupInclinedPlanePrm* pPrm, TListInfo* pListInfo=NULL);
GT_API GTN_GetGroupInclinedPlanePrm(short core, short group, TGroupInclinedPlanePrm* pPrm);
GT_API GTN_SetGroupInclinedPlaneMode(short core,short group,short mode,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupInclinedPlaneMode(short core,short group,short *pMode);

#define GROUP_MOVE_PRM_RESERVE2_POS_MASK                    (0) // λ����Ч�ᣬ0���������λ�ö���Ч����0��ָ�����λ����Ч
#define GROUP_MOVE_PRM_RESERVE2_START_POINT_MODE            (2) // ���λ��ģʽ��0�����Ϊ��һ�ε��յ㣬1�����Ϊִ�е���ָ��ʱʵʱ��ȡ�ĵ�ǰ��λ��
typedef struct
{
    double velocity;			// ��������ٶȣ��������ٶȱ������
    double acceleration;        // ���ٶ�
	double reserve1[3];
    double deceleration;        // ���ٶ�
    short  overrideSelect;		// ����ѡ��
    short  endVelocityMode;     // �յ��ٶ�ģʽ��0����Ч��1�����ٵ��㣬2��Ϊָ�����յ��ٶȣ�������
    short  orientationDir;      // ��̬�仯����0����·������1����·������
    short  reserve2[3];
    int32_t   reserve3[3];
} TGroupMoveParameter;

// Բ������
#define CIRCULAR_PARAMETER_MAX_ERROR             (0) // Բ������������
#define CIRCULAR_PARAMETER_ORIENTAION_PASS_MODE  (1) // Բ���Ƿ񾭹��м�����̬
#define CIRCULAR_PARAMETER_AUXILIARY_START_MASTER_POS (2) // Բ�����Ķ�̬����ϵ����λ��
#define CIRCULAR_PARAMETER_AUXILIARY_MASTER_POS  (3) // Բ��������Ķ�̬����ϵ����λ��

//Բ������ģʽ
#define CIRCULAR_MODE_PLANE_CENTER_DIR           (0) //�յ�+Բ��+��������ƽ��Բ��
#define CIRCULAR_MODE_PLANE_RADIUS_DIR           (1) //�յ�+�뾶(�з��ţ�������/�ӻ�)+��������ƽ��Բ��
#define CIRCULAR_MODE_SPACE_BORDER               (2) //�յ�+�м�㣬���ڿռ�Բ��
#define CIRCULAR_MODE_SPACE_CENTER               (3) //�յ�+Բ��+��/�ӻ������ڿռ�Բ��
#define CIRCULAR_MODE_SPACE_RADIUS               (4) //�յ�+��ֱƽ�������+�뾶(�з��ţ�������/�ӻ�)+�������ڿռ�Բ��
#define CIRCULAR_MODE_PLANE_RELATIVE_CENTER_DIR  (5) //�յ�+���Բ��+��������ƽ��Բ��
#define CIRCULAR_MODE_SPACE_BORDER_FOUR          (6) //�յ�+�м��+������㣬�����ĵ�ռ�Բ��
#define CIRCULAR_MODE_PLANE_CENTER_DIR_SPIRAL              (10) //�յ�+Բ��+�������������岹
#define CIRCULAR_MODE_PLANE_RELATIVE_CENTER_DIR_SPIRAL     (11) //�յ�+���Բ��+�������������岹

//Բ���岹ƽ��
#define CIRCULAR_PLANE_XY                        (0)
#define CIRCULAR_PLANE_YZ                        (1)
#define CIRCULAR_PLANE_ZX                        (2)
#define CIRCULAR_PLANE_XYZ                       (3)
#define CIRCULAR_PLANE_XY_HELIX                  (10)
#define CIRCULAR_PLANE_YZ_HELIX                  (11)
#define CIRCULAR_PLANE_ZX_HELIX                  (12)

//�յ�ָ��ģʽ
#define CIRCULAR_END_POINT_MODE_END_POINT        (0) //�յ����յ�λ��ָ��
#define CIRCULAR_END_POINT_MODE_CENTRAL_ANGLE    (1) //�յ���Բ�Ľ�ָ��

#define CIRCULAR_PATH_CHOICE_CW					 (0) //˳ʱ��
#define CIRCULAR_PATH_CHOICE_CCW				 (1) //��ʱ��

typedef struct
{
    short endPointMode;        //Բ���յ�ָ��ģʽ��0���յ�Ϊ������յ�λ�ã�1���յ���Բ�ĽǾ���
    short arcPlane;            //Բ���岹ƽ�棬XY,YZ,ZX
    short arcPathChoice;       //Բ��·��ѡ��ƽ��Բ��ʱΪ����(1����ʱ�룬-1��˳ʱ��)���ռ�Բ��Ϊ���ӻ�(1���ӻ���-1���Ż�)
    short pad;
    double centralAngle;       //Բ�Ľ�
    double centerPoint[8];     //Բ��Բ��
}TCircularPlaneCenterDirData;

typedef struct
{
    short endPointMode;        //Բ���յ�ָ��ģʽ��0���յ�Ϊ������յ�λ�ã�1���յ���Բ�ĽǾ���
    short arcPlane;            //Բ���岹ƽ�棬XY,YZ,ZX
    short arcPathChoice;       //Բ��·��ѡ��ƽ��Բ��ʱΪ����(1����ʱ�룬-1��˳ʱ��)���ռ�Բ��Ϊ���ӻ�(1���ӻ���-1���Ż�)
    short pad;
    double centralAngle;       //Բ�Ľ�
    double arcRadius;          //Բ���뾶
}TCircularPlaneRadiusDirData;

typedef struct
{
    short endPointMode;        //Բ���յ�ָ��ģʽ��0���յ�Ϊ������յ�λ�ã�1���յ���Բ�ĽǾ���
    short pad[3];
    double centralAngle;       //Բ�Ľ�
    double auxPoint[8];        //�м��
}TCircularSpaceBorderData;

typedef struct
{
    short endPointMode;                 //Բ���յ�ָ��ģʽ��0���յ�Ϊ������յ�λ�ã�1���յ���Բ�ĽǾ���
    short auxPointCommandCoord;         //�м��λ����������ϵ
    short auxPointOrientationMode;      //�м��λ��������̬
    short auxPointConfigIndex;          //�м�㹹�ͽ�
    short auxStartPointCommandCoord;    //�������λ����������ϵ
    short auxStartPointOrientationMode; //�������λ��������̬
    short auxStartPointConfigIndex;     //������㹹�ͽ�
    short pad;
    double centralAngle;       //Բ�Ľ�
    double auxPoint[8];        //�м��
    double auxStartPoint[8];   //�������λ�ã���������Բ��
}TCircularSpaceBorderFourData;

typedef struct
{
    short endPointMode;        //Բ���յ�ָ��ģʽ��0���յ�Ϊ������յ�λ�ã�1���յ���Բ�ĽǾ���
    short arcPlane;            //Բ���岹ƽ�棬XY,YZ,ZX
    short arcPathChoice;       //Բ��·��ѡ��ƽ��Բ��ʱΪ����(1����ʱ�룬-1��˳ʱ��)���ռ�Բ��Ϊ���ӻ�(1���ӻ���-1���Ż�)
    short periodCount;         //Ȧ��
    double centralAngle;       //Բ�Ľ�
    double centerPoint[8];     //Բ��Բ��
    double periodDeltaRadius;  //һȦ��Ӧ�İ뾶�仯��
}TCircularPlaneCenterDirSpiralData;

typedef union
{
    TCircularPlaneCenterDirData centerDir;       //��Բ��ģʽΪԲ�ķ��򣬻������Բ�ķ���ʱ�����øýṹ��
    TCircularPlaneRadiusDirData radiusDir;
    TCircularSpaceBorderData spaceBorder;
    TCircularSpaceBorderFourData spaceBorderFour;
    TCircularPlaneCenterDirSpiralData spiral;    //��Բ��ģʽΪԲ�ķ��򣬻������Բ�ķ���ʱ�����øýṹ��
    double data[32];
}TCircularModeUnion;

typedef struct
{
    short arcMode;             //Բ������ģʽ
    short pad[3];
    TCircularModeUnion data;
}TCircularParameter;

#define GATE_MODE_NORMAL                         (0)

typedef struct
{
	double h1;     // ��㴹ֱ�����߶�
	double h2;     // �յ㴹ֱ�½��߶�
	double h3;     // �������߶ε���С���ɸ߶�
	double k1;     // �������߶�ƽ����ռƽ�ƶεİٷֱ�
	double k2;     // �½����߶�ƽ����ռƽ�ƶεİٷֱ�
	short curveMode;       // ��������ģʽ
	short oriChangeMode;   // ��̬�仯ģʽ
	short reserve1[6];
	double reserve2[8];
}TGate;

typedef union
{
	TGate gate;
	double data[32];
}TGateUnion;

typedef struct
{
	short mode;             //���͹켣����ģʽ
	short reserve[3];
	TGateUnion data;
}TGatePrm;

GT_API GTN_MoveGateAbsolute(short core,short group,double endPoint[],TGatePrm *pGatePrm,TGroupMoveParameter *pPrm,TListInfo *pListInfo=NULL);
GT_API GTN_MoveLinearAbsolute(short core, short group, double pos[], short dir[], TGroupMoveParameter* pPrm, TListInfo* pListInfo = NULL);
GT_API GTN_MoveCircularAbsolute(short core, short group, double endPoint[], TCircularParameter* pCircularPrm, TGroupMoveParameter* pPrm, TListInfo* pListInfo = NULL);


#define WEAVE_TYPE_SINE                            (0)
#define WEAVE_TYPE_SINE_DIR_X                      (WEAVE_TYPE_SINE+100)

// �����ڻ����ͼ�����
typedef struct  
{
	short type;           // �ڻ�����
	short weaveMode;      // �ڻ�ģʽ��0���ýṹ�����Ϊ�ڻ�������1���ýṹ�����ΪԤ�ڻ�����
	short frequencyMode;  // Ƶ��ģʽ��0�������ڻ�ΪͬһƵ�ʣ�1�������ڻ�ͨ��weavePrm[0]��weavePrm[1]����Ƶ�ʱ���
	short pad1;
	double amplitude;     // �ڻ��������λ��mm 
	double frequency;     // �ڻ�Ƶ�ʣ���λ��Hz
	double weavePrm[10];  // �ڻ����β���
	short startPosition;  // �ڻ���ʼλ��
	short dweelFullStop;  // ��ȫֹͣʹ��
	short pad2[2];
	double dweelLeft;     // �ڻ���ͣ��ʱ�䣬��λ��ms
	double dwellMid;      // �ڻ���ͣ��ʱ�䣬��λ��ms
	double dwellRight;    // �ڻ���ͣ��ʱ�䣬��λ��ms
	short oriControlMode; // �ڻ���̬����ģʽ
	short pad3[3];
	double rotateAngleX;  // ����ǣ���λ����
	double rotateAngleY;  // ǰ��ǣ���λ����
	double rotateAngleZ;  // ��ת�ǣ���λ����
}TGroupWeaveParameter;

#define GROUP_SUPERPOSITION_TABLE_MAX       (4)    // �����ӱ�����
#define GROUP_SUPERPOSITION_TABLE_DATA_MAX  (128)  // ���ӱ���������ݸ���

typedef struct
{
	short mode;              // ģʽ��Ŀǰֻ֧������Ϊ0
	short dataCount;         // ���ӱ������ݵ����
	short reserve1[6];       
	double period;           // ���ӱ�������
	double reserve2[5];
} TGroupSuperpositionTablePrm;

typedef struct
{
	double value[8];
} TGroupSuperpositionTableData;

typedef struct
{
	short workIndex;
	short reserve1[7];
	double reserve2[14];
} TGroupSuperpositionTableStatus;

#define GROUP_SUPERPOSITION_MODE_DIRECT            (0)  // ֱ�ӵ���ģʽ
#define GROUP_SUPERPOSITION_MODE_WEAVE             (1)  // �ڻ�����ģʽ
#define GROUP_SUPERPOSITION_MODE_WEAVE_EX          (2)  // �ڻ�������չģʽ
#define GROUP_SUPERPOSITION_MODE_TABLE             (3)  // �������ģʽ
#define GROUP_SUPERPOSITION_MODE_DIRECT_RELATIVE   (10) // ��Ե���ģʽ

// ����ֱ�ӵ���ֵ
typedef struct  
{
	double value[8];                         // ����ֵ
	double reserve[24];
}TGroupSuperpositionValueDirect;

#define GROUP_SUPERPOSITON_WEAVE_EX_RESERVE_STOP_VEL	   (0)       // �ڻ�����ֹͣ�ٶ�
typedef struct
{
	short mode;                              // �ڻ�������ģʽ 0���ڻ�����ģʽ 1��Ԥ�ڻ�ģʽ
	short pad[3];                            // ����
	double time;                             // Ԥ�ڻ�ģʽ�ĳ���ʱ��
	double velocity;                         // Ԥ�ڻ�ģʽ���ٶ�
	double reserve[29];
}TGroupSuperpositionWeaveEx;

#define GROUP_SUPERPOSITON_TABLE_RESERVE2_STOP_VEL	       (0)        // �ڻ�����ֹͣ�ٶ�
typedef struct
{
	short mode;                              // ���������ģʽ 0����ͨ����ģʽ 1��Ԥ����ģʽ
	short startIndex;                        // ��ʼ���ӱ�������
	short count;                             // ���ӱ�������count=1ʱ����ʾѭ����������ΪstartIndex�ı���count>1ʱ�����ʾ���ε��Ӵ�startIndex��ʼ��count����
	short reserve1[5];                       
	double time;                             // Ԥ����ģʽ�ĳ���ʱ��
	double velocity;                         // Ԥ����ģʽ���ٶ�
	double reserve2[28];
}TGroupSuperpositionTable;

typedef union  
{
	TGroupSuperpositionValueDirect direct;   // ֱ�ӵ���ֵ
	TGroupSuperpositionWeaveEx weaveEx;      // �ڻ�������չģʽ
	TGroupSuperpositionTable table;          // �������ģʽ
	double data[32];
}TGroupSuperpositionUnion;

typedef struct  
{
	short enable;         // �����Ƿ�ʹ��
	short mode;           // ����ģʽ 0��ֱ�ӵ��� 1������ʱ����аڻ����� 2���ڻ�������չģʽ
	short pad[2];
	double smoothTime;    // ƽ��ʱ��
	TGroupSuperpositionUnion data;
}TGroupSuperposition;

GT_API GTN_SetGroupWeaveParameter(short core,short group,TGroupWeaveParameter *pWeave,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupWeaveParameter(short core,short group,TGroupWeaveParameter *pWeave);
GT_API GTN_SetGroupSuperpositionTable(short core,short group,short tableIndex,TGroupSuperpositionTablePrm *pTablePrm,TGroupSuperpositionTableData *pData);
GT_API GTN_GetGroupSuperpositionTable(short core,short group,short tableIndex,TGroupSuperpositionTablePrm *pTablePrm,TGroupSuperpositionTableData *pData);
GT_API GTN_GetGroupSuperpositionTableStatus(short core,short group,TGroupSuperpositionTableStatus *pTableStatus);
GT_API GTN_SetGroupSuperposition(short core,short group,short coordSystem,short index,TGroupSuperposition *pGroupSuperposition,TListInfo *pListInfo=NULL);
GT_API GTN_GetGroupSuperposition(short core,short group,short coordSystem,short index,TGroupSuperposition *pGroupSuperposition);
GT_API GTN_GetGroupSuperpositionValue(short core,short group,short coordSystem,short index,double *pValue);

/*-----------------------------------------------------------*/
/* CBT Command                                               */
/*-----------------------------------------------------------*/
#define CBT_MODE_CONTINUOUS  (0)
#define CBT_MODE_INTERMITTEN (1)

#define CBT_EXECUTE_MODE_AUTO          (0)    // �Զ�ģʽ
#define CBT_EXECUTE_MODE_COMMAND       (1)    // ָ������ģʽ

#define CBT_MASTER_MOTION_TYPE_LINEAR  (0)    // ֱ�ߴ��ʹ�
#define CBT_MASTER_MOTION_TYPE_ROTATE  (1)    // ��ת���ʹ�

typedef struct
{
	short masterMode;     // ����ģʽ0���������ʹ���1����Ъ���ʹ�
	short masterType;     // ��������
	short masterIndex;    // ��������
	short cbtTag;         // ���ʹ���ʶ����ӦTCbtPieceData�е�cbtTag�����ڱ�ʶ�����Ƿ�Ϊ���ʹ���Ҫ�����Ĺ���

	double detectPos;     // ���ʹ����λ��Դ��ʹ�����ϵ����X��ƫ����
	double parkPos;       // ���ʹ�����λ��Դ��ʹ�����ϵ����X��ƫ����
	double stopPos;       // ���ʹ�ֹͣλ��Դ��ʹ�����ϵ����X��ƫ����
	double delay;         // ͬ��������ִ��ǰ����ʱʱ��
	double sampleTime;    // ���ʹ��ٶȲ���ʱ��
	double velMax;        // ���������׷���ٶ�
	double acc;           // ������׷�ϼ��ٶ�
	double cbOrigin[6];   // ���ʹ�����ϵ�����Ի�����MCS��ƫ�ƺ���ת

	short group;          // ����������
	short masterMotionType;// �����˶����ͣ�0��ֱ�ߴ��ʹ���1����ת���ʹ�
	short masterMotionDir; // ��Դ��ʹ�����ϵ���˶����򣬽�����ת���ʹ���Ч��0��˳ʱ�룬1����ʱ��
	short reserve1[5];
	double reserve2[10];
}TCbtPrm;

typedef struct
{
	short group;
	short pieceConfigIndex;// �������ڴ��ʹ��ϵĹ�������ϵ�Ͻ��й���ʱ������ͬ����λ�㣩�Ĺ��ͽ�
	short waitMode;        // 0����ԭ�صȴ�������1�����ȴ�λ�ȴ�����
	short waitProfileCoord;
	short waitCmdPosCoord;
	short waitConfigIndex;// �����˴��ڵȴ�λ�Ĺ��ͽ�
	short reserve1[2];

	double locatePoint[6];// �������˶������ʹ��ϵĹ�����λ�㣬ΪPCS�µ�λ�ú���̬
	double waitPoint[6];  // ���ʹ�û�й������߹�����δ����ʱ�������˻ص��ȴ�λ��ΪMCS�µ�λ�ú���̬

	double groupVel;      // �������˶��ٶ�
	double groupAcc;      // �������˶����ٶ�
	double groupDec;      // �������˶����ٶ�

	short reserve2[8];
	double reserve3[10];
}TCbtGroupPrm;

typedef struct
{
	short cbtTag;            // ���ʹ���ʶ����ӦTCbtPrm�е�cbtTag�����ڱ�ʶ�������Ƿ�ΪcbtIndex��Ӧ�Ĵ��ʹ���Ҫ�����Ĺ���   
	short pieceTag;          // ������ʶ���������ڱ�ʶÿһ������
	short reserve1[2];
	double masterPos;        // �����������λʱ������λ��
	double pose[6];          // ������Դ��ʹ�����ϵ��λ�ú���̬
	double reserve2[5];
	double processTime;      // ������ͬ�����Ĵ���ʱ��
}TCbtPieceData;

typedef struct
{
	short cbtIndex1;
	short cbtIndex2;
	short reserve1[2];
	double reserve2[10];
}TCoupleCbtPrm;

typedef struct
{
	short executeMode;
	short reserve1[3];
	double reserve2[10];
}TStartCbtPrm;

#define CBT_STATE_IDLE                    (0) //����״̬
#define CBT_STATE_BACK_TO_WAIT_POINT      (10) //û�й������ص��ȴ�λ
#define CBT_STATE_WAITTING_PIECE          (20) //��ԭλ���ߵȴ�λ�ȴ�����
#define CBT_STATE_LOCATING                (110) //�ȴ���е�ֵ�λ
#define CBT_STATE_WAITING_SYNCHRONIZATION (120) //�ȴ���е�ֺʹ��ʹ�ͬ��
#define CBT_STATE_SYNCHRONIZATION         (130) //ͬ��״̬
#define CBT_STATE_DELAY                   (140) //��ʱ״̬
#define CBT_STATE_EXECUTING_TASK          (150) //ͬ������ִ��״̬
#define CBT_STATE_EXITING_SYNCHRONIZATION (160) //�˳�ͬ����
#define CBT_STATE_STOPPING                (300) //ֹͣ״̬
#define CBT_STATE_DONE                    (400) //���״̬

// CBTֹͣ����ϸ��Ϣ
#define CBT_STOP_INFO_NONE                               (0)
#define CBT_STOP_INFO_CU_OUT_OF_RANGE                    (1)
#define CBT_STOP_INFO_GET_CU_INFO                        (2)
#define CBT_STOP_INFO_ENABLE_GROUP_DYNAMICA_TRANSFORM    (3)
#define CBT_STOP_INFO_DISABLE_GROUP_DYNAMICA_TRANSFORM   (4)
#define CBT_STOP_INFO_START_GROUP_LOCATE_MOTION          (5)
#define CBT_STOP_INFO_START_GROUP_WAIT_MOTION            (6)
#define CBT_STOP_INFO_START_CU                           (7)
#define CBT_STOP_INFO_USER_STOP                          (10)
#define CBT_STOP_INFO_USER_STOP_COMMAND_LIST             (11)
#define CBT_STOP_INFO_USER_STOP_IN_LIST                  (12)
#define CBT_STOP_INFO_GROUP_ERROR                        (50)
#define CBT_STOP_INFO_PROFILE_ERROR                      (51)

typedef struct
{
	short execute;                    // ���ʹ��Ƿ�������
	short state;                      // ���ʹ���ִ��״̬
	short stopInfo;                   // ���ʹ�����ֹͣʱ����ϸ��Ϣ
	short reserve1[3];
	short pieceTag;                   // ��ǰ���ڴ����Ĺ�����ʶ  
	short pieceEmpty;                 // ����fifo�Ƿ�Ϊ��
	uint32_t pieceReceive;       // ���ʹ����ܵ������й�������
	uint32_t pieceRemainder;     // ���ʹ�ʣ�໹δ�����Ĺ�������
	uint32_t pieceProcess;       // ���ʹ��Ѵ����Ĺ������������������Ĺ�������
	uint32_t validPieceProcess;  // ���ʹ���Ч�����Ĺ������� 
	uint32_t reserve2[6];

	double catchUpStartPos;          // ׷��������λ����Դ��ʹ�����ϵ��λ��
	double actualPiecePos;           // ʵ�ʹ�����Դ��ʹ�����ϵ��λ��
	double virtualPiecePos;          // ��׷������ŵ����⹤����Դ��ʹ�����ϵ��λ��
}TCbtInfo;

GT_API GTN_SetCbtPrm(short core,short cbtIndex,TCbtPrm *pPrm);
GT_API GTN_GetCbtPrm(short core,short cbtIndex,TCbtPrm *pPrm);
GT_API GTN_SetCbtGroupPrm(short core,short cbtIndex,TCbtGroupPrm *pPrm);
GT_API GTN_GetCbtGroupPrm(short core,short cbtIndex,TCbtGroupPrm *pPrm);
GT_API GTN_ClearCbtPieceData(short core,short cbtIndex,short type);
GT_API GTN_SetCbtPieceData(short core,short cbtIndex,TCbtPieceData *pCbtPieceData,short count=1);
GT_API GTN_GetCbtDiscardPieceData(short core,short cbtIndex,short count,TCbtPieceData *pCbtPieceData,short *pActualCount);
GT_API GTN_SetCbtTask(short core,short cbtIndex,short taskType,void *pTaskData);
GT_API GTN_GetCbtTask(short core,short cbtIndex,short *pTaskType,void *pTaskData);
GT_API GTN_StartCoupleCbt(short core,short coupleCbtIndex,TCoupleCbtPrm *pPrm);
GT_API GTN_StopCoupleCbt(short core,short coupleCbtIndex);
GT_API GTN_GetCbtInfo(short core,short cbtIndex,TCbtInfo *pInfo);
GT_API GTN_ClearCbtInfo(short core,short beltIndex);
GT_API GTN_StartCbt(short core,short cbtIndex,TStartCbtPrm *pStartCbtPrm,TListInfo *pListInfo=NULL);
GT_API GTN_StopCbt(short core,short cbtIndex,TListInfo *pListInfo=NULL);
GT_API GTN_WaitCbtPiece(short core,short cbtIndex,TListInfo *pListInfo=NULL);

/*-----------------------------------------------------------*/
/* CollisionCheck Command                                    */
/*-----------------------------------------------------------*/
#define COLLISION_CHECK_MAX            (8)       // ��ײ�����������
#define COLLISION_CHECK_OBJECT_MAX     (16)      // ��ײ�������������

#define OBJECT_TYPE_NONE               (-1)      // û������
#define OBJECT_TYPE_CUBOID             (1)       // ������
#define OBJECT_TYPE_CYLINDER           (2)       // Բ����

#define OBJECT_LOCATE_FIX              (0)       // ������̶�����
#define OBJECT_LOCATE_TOOL             (1)       // ������λ�ڹ��߲�
#define OBJECT_LOCATE_WORK_PIECE       (2)       // ������λ�ڹ�����

#define AXIS_SIDE_TOOL                 (0)       // ֱ����λ�ڹ��߲�
#define AXIS_SIDE_WORK_PIECE           (1)       // ֱ����λ�ڹ�����

// ������������Ϣ
typedef struct
{
    double axis[3][3];                           // �������3����������������ʸ����Ϊ1
    double length[3];                            // �������3������ĳ���
} TObjectCuboid;

// Բ����������Ϣ
typedef struct
{
    double axis[3];                              // Բ�������������������ʸ����Ϊ1
    double radius;                               // Բ����뾶
    double height;                               // Բ����ĸ߶�
} TObjectCylinder;

// ���������״��Ϣ
typedef union
{
    TObjectCuboid cuboid;                        // ������������Ϣ
    TObjectCylinder cylinder;                    // Բ����������Ϣ
    double data[32];
} TObjectShape;

// ��ײ������Ĳ���
typedef struct
{
    short shapeType;                             // �����������
    short reserve1[3];                           // ����ֵ����������Ϊ0
    TObjectShape shape;                          // ���������״������Ϣ

    short source;                                // �������λ�òο�Դ��MC_GROUP_PROFILE��MC_PROFILE��MC_NONE��
                                                 // �ο�ԴΪgroup����ʱ����������group�е���������ο�����ϵΪgroup��MCS����ϵ
                                                 // �ο�ԴΪMC_PROFILE���������ɹ滮��������ο�����ϵΪ�滮�����
                                                 // �ο�ԴΪMC_NONEʱ��������̶��������ο�����ϵΪ������

    short index[3];                              // �ο�Դ����
                                                 // �ο�ԴΪgroup����ʱ��index[0]Ϊgroup������index[1~2]����Ϊ0
                                                 // �ο�ԴΪMC_PROFILE��index[0~3]�ֱ�ָʾ���ż�������XYZ�����˶������������������ά��û�����˶������ó�0
                                                 // �ο�ԴΪMC_NONEʱ��index[0~3]����Ϊ0

    short locate;                                // ���ο�ԴΪgroup����ʱ����Ҫ���ü���������λ������
                                                 // OBJECT_LOCATE_FIX��������̶�����
                                                 // OBJECT_LOCATE_TOOL��������λ�ڹ��߲࣬�ɹ��߲��������˶�
                                                 // OBJECT_LOCATE_WORK_PIECE��������λ�ڹ����࣬�ɹ������������˶�
    short side[3];                               // ���ο�ԴΪgroup����ʱ����Ҫ����ֱ����������λ��ֱ����λ�ڹ��߲໹�ǹ����࣬0�����߲࣬1��������

    double offset[3];                            // ������������Բο�Դ����ƫ��
                                                 // �ο�ԴΪgroup����ʱ����locateΪOBJECT_LOCATE_TOOLʱ�����õ�ƫ����Ϊ���group�����幤��ĩ�˵����꣬locateΪ��������ʱ�����õ�ƫ����Ϊ���MCS��������
                                                 // �ο�ԴΪprofile����ʱ���ο�Դ���Ϊ�����
                                                 // �ο�ԴΪMC_NONEʱ���ο�Դ���Ϊ���������

    short reserve2[4];                           // ����ֵ����������Ϊ0
} TCollisionCheckObjectPrm;

typedef struct
{
    short objectIndex[2];                        // ������ײ�������������������
    short reserve1[2];                           // ����ֵ����������Ϊ0
    short rotateMode;                            // ����λ�òο�Դ�������Ƿ������ת��0��û����ת��ֻ��ͬ����߷���ͨ��dir�������ã�1������ת��ͨ������ָ�����ã�Ŀǰ��֧��ģʽ0.
    short dir[3];                                // �����������λ�òο�ԴXYZ�ķ����Ƿ���0��ͬ��1������
                                                 // �������ο�Դ��ͬ�����ߴ��ڹ̶������ο�Դ����ʱ����Ȼͬ��

    double originOffset[3];                      // ��λ�òο�Դ��һ��ʱ�����ý�����ײ��������������Ĳο�����ƫ�ƣ�����ο�Դһ�����ò�������Ϊ0
                                                 // ���ƫ��Ϊ�ڶ������������Ե�һ����������ϵ���ͷ����ƫ�ƾ���

    double distance;                             // ��ײ������
    double reserve2[8];                          // ����ֵ����������Ϊ0
} TCollisionCheckPrm;

typedef struct
{
    short enable;                                // ��ײ���ʹ�ܱ�־
    short checkResult;                           // ������ײ�������Ƿ��������ײ��ⷶΧ
    short reserve1[6];
    double reserve2[4];
}TCollisionCheckStatus;

/**
 * @brief ������ײ������Ĳ���
 * @param core �˺�
 * @param objectIndex ��ײ���������������1��ʼ
 * @param pPrm ��ײ������Ĳ���
 * @return 
*/
GT_API GTN_SetCollisionCheckObjectPrm(short core,short objectIndex,TCollisionCheckObjectPrm *pPrm);
GT_API GTN_GetCollisionCheckObjectPrm(short core,short objectIndex,TCollisionCheckObjectPrm *pPrm);

/**
 * @brief ������ײ���Ĳ���
 * @param core �˺�
 * @param checkIndex ��ײ������������1��ʼ
 * @param pPrm ��ײ���Ĳ���
 * @return 
*/
GT_API GTN_SetCollisionCheckPrm(short core,short checkIndex,TCollisionCheckPrm *pPrm);
GT_API GTN_GetCollisionCheckPrm(short core,short checkIndex,TCollisionCheckPrm *pPrm);

/**
 * @brief ʹ�ܻ�ر���ײ��⹦��
 * @param core �˺�
 * @param checkIndex ��ײ������������1��ʼ
 * @param enable ʹ�ܲ���
 * @param pListInfo ָ��������
 * @return 
*/
GT_API GTN_SetCollisionCheckEnable(short core,short checkIndex,short enable,TListInfo *pListInfo=NULL);

/**
 * @brief ��ȡ��ײ��⹦�ܵ�״̬
 * @param core �˺�
 * @param checkIndex ��ײ������������1��ʼ
 * @param pStatus ��ײ���ģ��״̬
 * @return 
*/
GT_API GTN_GetCollisionCheckStatus(short core,short checkIndex,TCollisionCheckStatus *pStatus);

/**
 * @brief �����ײ��⹦�ܵ�״̬
 * @param core �˺�
 * @param checkIndex ��ײ������������1��ʼ
 * @return 
*/
GT_API GTN_ClearCollisionCheckStatus(short core,short checkIndex);
/*--------- -------------------------------------------------*/
/* Gantry                                                    */
/*-----------------------------------------------------------*/
#define GANTRY_MODE_NONE                                (-1)
#define GANTRY_MODE_OPEN_LOOP_GANTRY                    (1)
#define GANTRY_MODE_DECOUPLE_POSITION_LOOP              (2)
#define GANTRY_MODE_RINGNET_DRIVER                      (10)

GT_API GTN_SetGantryMode(short core, short group, short master, short slave, short mode, int32_t syncErrorLimit = 1000);
GT_API GTN_GetGantryMode(short core, short group, short* pMaster, short* pSlave, short* pMode, int32_t* pSyncErrorLimit);
GT_API GTN_SetGantryPid(short core, short group, TPid* pGantryPid, TPid* pYawPid);
GT_API GTN_GetGantryPid(short core, short group, TPid* pGantryPid, TPid* pYawPid);
GT_API GTN_GantryAxisOn(short core, short group);
GT_API GTN_GantryAxisOff(short core, short group);

GT_API GTN_SetAxisInputShapeVerI(short core, short axis, short enable, short freq, double z);

typedef struct
{
    short windowSize;                                    // ���ڴ�С
    short lostSize;                                      // ʹ�ܺ�������Ժ�ʼ���
    int32_t torqueLimitMax;                                 // ���ֵ
    int32_t torqueLimitMin;                                 // ��Сֵ

    short continuousProtectCount;                        // ������Χ�ڣ�ʵ�ʵ���������ô���ĳ������ֵ������Сֵ�򱣻�����
    short oscillationPositiveProtectCount;               // ������Χ�ڣ�ʵ�ʵ����ܹ���ô���Ĵ������ֵ�򱣻�����
    short oscillationNegativeProtectCount;               // ������Χ�ڣ�ʵ�ʵ����ܹ���ô����С����Сֵ�򱣻�����
    short reserve[15];
} TGantryTorqueProtectPrm;
GT_API GTN_SetGantryProtectPrm(short core, short group, short torqueProtectType, TGantryTorqueProtectPrm* pPrm);
GT_API GTN_GetGantryProtectPrm(short core, short group, short torqueProtectType, TGantryTorqueProtectPrm* pPrm);
GT_API GTN_GantryProtectEnable(short core, short group, short enable, short protectType, short subProtectType);

typedef struct
{
    int32_t torqueProtectSts;                               // ����״̬
    int32_t torqueProtectEnable;                            // ����ʹ��״̬
    short reserve[20];
} TGantryInf;
GT_API GTN_GetGantryInf(short core, short group, TGantryInf* pPrm);

GT_API GTN_SetGantrySynchErrorCompensate2DTable(short core, short tableIndex, TCompensate2DTable* pTable, int32_t* pData, short extend);
GT_API GTN_GetGantrySynchErrorCompensate2DTable(short core, short tableIndex, TCompensate2DTable* pTable, short* pExtend);
GT_API GTN_SetGantrySynchErrorCompensate2D(short core, short group, TCompensate2D* pComp2d);
GT_API GTN_GetGantrySynchErrorCompensate2D(short core, short group, TCompensate2D* pComp2d);
GT_API GTN_GetGantrySynchErrorCompensate2DValue(short core, short group, double* pValue);

typedef struct SecondOrderFilterPara
{
    short active;

    double a0;
    double a1;
    double a2;

    double b1;
    double b2;

} TSecondOrderFilterPara;

#define TYPE_CONTROL_OUTPUT_FILTER          (1)
#define TYPE_YAW_CONTROL_OUTPUT_FILTER      (2)
#define FILTER_COUNT_MAX                    (2)

GT_API GTN_SetSecondOrderFilterPara(short core, short control, short type, short index, TSecondOrderFilterPara* pFilterPrm);
GT_API GTN_GetSecondOrderFilterPara(short core, short control, short type, short index, TSecondOrderFilterPara* pFilterPrm);

typedef struct _OCA_CTRL_GEN_
{
    short  s16Gain;
    short  s16Offset;
    double dFrq;
    int32_t   u32RunPeriod;
    short  u16SigType;
} OCA_CTRL_GEN;

typedef struct ExcitationPara
{
    short gain;
    short offset;
    short frq;      // hz
    double runTime; // s
} TExcitationPara;

typedef struct ExcitationTrapPara
{
    double vel;
    double acc;
    double dec;
    double runTime;  // s
} TExcitationTrpPara;

#define NO_EXCIT                        (0xff)
#define OPEN_LOOP_EXCIT                 (1)
#define SIGNAL_TYPE_STEP                (3)
#define SIGNAL_TYPE_SIN                 (0x10)
#define SIGNAL_TYPE_TRAP                (0x11)
#define SIGNAL_TYPE_NOTHING             (0xFF)

GT_API GTN_SetGenerator(short core, OCA_CTRL_GEN* pGenStr);
GT_API GTN_GetGenerator(short core, OCA_CTRL_GEN* pGenStr);
GT_API GTN_StepResponse(short core, short control, short gain, double time);
GT_API GTN_SetExctLoopMode(short core, short control, short exciteLoopMode);
GT_API GTN_GetExctLoopMode(short core, short control, short* pExciteLoopMode);


/*-----------------------------------------------------------*/
/* DMA                                                       */
/*-----------------------------------------------------------*/
GT_API GTN_CrdHsOn(short core,short crd,short fifo,short dmaBuf=1,unsigned short threshold=200,short lookAheadInMc=0);
GT_API GTN_CrdHsOff(short core,short crd,short fifo);
GT_API GTN_GetCrdHsPrm(short core,short crd,short fifo,short *pEnable,short *pLink,unsigned short *pThreshold,short *pLookAheadInMc);


/*-----------------------------------------------------------*/
/* Others                                                    */
/*-----------------------------------------------------------*/
GT_API GTN_SetRetainValue(short core,uint32_t address,short count,short *pData);
GT_API GTN_GetRetainValue(short core,uint32_t address,short count,short *pData);

typedef struct
{
    short direction;
    short reserve[3];
} TGPIOConfig;
GT_API GTN_SetGPIOConfig(short core,short station,int32_t effectiveLevel,int32_t direction);
GT_API GTN_SetGPIOConfigEx(short core,short station,short index,TGPIOConfig *pGPIOConfig,short count);
GT_API GTN_GetGPIOConfigEx(short core,short station,short index,TGPIOConfig *pGPIOConfig,short count);
GT_API GTN_GetGPIOStatus(short core,short station,short type,short *pStatus,short index,short count);

GT_API GTN_PosCurrFeedForward(short core,short profile,double pos,int32_t gtime,short torque,short gtype,short fifo=0);
GT_API GTN_SetMotionMode(short core,short axis,short motionMode);
GT_API GTN_GetMotionMode(short core,short axis,short *motionMode);
GT_API GTN_PosCurrFeedForwardArray(short core,short profile,double *pPos,int32_t time,short *pTorque,short *pType,short fifo,short count);
GT_API GTN_GetNetStatus(short core,short *pNetSts);

GT_API GTN_GetPowerSts(short core,int32_t *pSts);
GT_API GTN_SynchPrfPosWithEncPos(short core,short profile,short encoder);

GT_API GTN_SetServoTime(short core, int32_t servoTime, int32_t delay, int32_t stepCoef);
GT_API GTN_GetServoTime(short core, int32_t* pServoTime, int32_t* pDelay, int32_t* pStepCoef);
GT_API GTN_SetProfileTime(short core,int32_t profileTime,int32_t delay,int32_t stepCoef);
GT_API GTN_GetProfileTime(short core,int32_t *pProfileTime,int32_t *pDelay,int32_t *pStepCoef);
GT_API GTN_SetCoreTime(short core,int32_t profileTime,int32_t delay,int32_t stepCoef);
GT_API GTN_GetCoreTime(short core,int32_t *pProfileTime,int32_t *pDelay,int32_t *pStepCoef);
GT_API GTN_SetCorePeriod(short core,double period);
GT_API GTN_GetCorePeriod(short core,double *pPeriod,short *pFlag,short *pInfo);
typedef struct ControlInfo
{
    double refPos;
    double refPosFilter;
    double refPosFilter2;
    double cntPos;
    double cntPosFilter;

    double error;
    double refVel;
    double refAcc;

    short value;
    short valueFilter;

    short offset;
} TControlInfo;

typedef struct
{
    uint32_t notify;
    uint32_t receive;
    uint32_t execute;
    uint32_t retry;
    uint32_t receiveError;
    uint32_t echo;
} TCommandCount;

GT_API GTN_ClearCommandCount(short core);
GT_API GTN_GetCommandCount(short core,TCommandCount *pCommandCount);
GT_API GTN_GetControlInfo(short core,short control,TControlInfo *pControlInfo);


GT_API GTN_SetLongVar(short core,short index,int32_t value);
GT_API GTN_GetLongVar(short core,short index,int32_t *pValue);
GT_API GTN_SetDoubleVar(short core,short index,double value);
GT_API GTN_GetDoubleVar(short core,short index,double *pValue);

GT_API GTN_GetBufWaitDiStatus(short core,short crd,short *pDiType,unsigned short *pDiIndex,unsigned short *pLevel, short *pContinueTime,int32_t *pOverTime,short *pFlagMode,int32_t *pSegNum,short *pEnable,int32_t *pCount,short fifo);
GT_API GTN_GetBufWaitLongVarStatus(short core,short crd,short *pIndex,int32_t *pValue,short *pFlagMode,int32_t *pSegNum,short *pEnable,short *pStatus,short fifo);
GT_API GTN_ClearBufWaitStatus(short core,short crd,short fifo);
GT_API GTN_BufWaitDi(short core, short crd, short diType, unsigned short diIndex, unsigned short level, short continueTime, int32_t overTime, short flagMode, int32_t segNum, short fifo);
GT_API GTN_BufWaitLongVar(short core, short crd, short index, int32_t value, int32_t overTime, short flagMode, int32_t segNum, short fifo);
GT_API GTN_BufWaitWatchVar(short core, short crd, TWatchCondition* pWatchCondition, TWaitTimeout* pWaitTimeout, int32_t segNum, short fifo);

GT_API GTN_BufDoBit(short core,short crd,unsigned short doType,unsigned short index,short value,short fifo);
GT_API GTN_BufDoBitDelay(short core,short crd,unsigned short doType,unsigned short index,short value,int32_t delayTime,short fifo);
GT_API GTN_BufSetOverride(short core,short crd,double synVelRatio,short mode,short fifo);

typedef struct
{
    double stopPos;
    short mode;
    short pad[3];
}TStopPos;
GT_API GTN_BufStopPos(short core,short crd,short profile,TStopPos *pStopPos,short modal,short fifo);
GT_API GTN_BufSetSoftLimit(short core,short crd,short axis,int32_t positive,int32_t negative,short fifo);

typedef struct
{
    short type;
    short enable;
    short flagMode;
    short diType;
    short diIndex;
    short diValue;
    unsigned short continueTime;
    unsigned short trigDelay;
    uint32_t overTime;
    uint32_t counter;
    int32_t longVar;
    int32_t segNum;
    short stop;
    short overTimeStop;
    short pad1[2];
}TBufWaitDiStatusEx;
GT_API GTN_GetBufWaitDiStatusEx(short core,short crd,short fifo,TBufWaitDiStatusEx *pStatus);



//////////////////////////////////////////////////////////////////////////
//Standard Home
//////////////////////////////////////////////////////////////////////////

#define STANDARD_HOME_STAGE_IDLE              (0)   //δ������ԭ��
#define STANDARD_HOME_STAGE_START             (1)   //������ԭ��
#define HOME_STAGE_ON_HOME_LIMIT_ESCAPE       (2)
#define STANDARD_HOME_STAGE_SEARCH_HOME       (20)  //��������Home
#define STANDARD_HOME_STAGE_SEARCH_INDEX      (30)  //��������Index
#define STANDARD_HOME_STAGE_GO_HOME           (80)  //�����˶���ԭ��
#define STANDARD_HOME_STAGE_END               (100) //��ԭ�����
#define STANDARD_HOME_STAGE_START_CHECK       (-1)  //������ԭ��ǰ�Լ�
#define STANDARD_HOME_STAGE_CHECKING          (-2)  //�Լ���

#define STANDARD_HOME_ERROR_NONE              (0)   //δ��������
#define STANDARD_HOME_ERROR_DISABLE           (10)  //ִ�л�ԭ�����δʹ��
#define STANDARD_HOME_ERROR_ALARM             (20)  //ִ�л�ԭ����ᱨ��
#define STANDARD_HOME_ERROR_STOP              (30)  //δ��ɻ�ԭ�㣬��ֹͣ�˶�
#define STANDARD_HOME_ERROR_ON_LIMIT          (40)  //��������λ�޷�����
#define STANDARD_HOME_ERROR_NO_HOME           (50)  //δ�ҵ�Home
#define STANDARD_HOME_ERROR_NO_INDEX          (60)  //δ�ҵ�Index
#define STANDARD_HOME_ERROR_NO_LIMIT          (70)  //δ�ҵ���λ
#define STANDARD_HOME_ERROR_ENCODER_DIR_SCALE (-1)  //�滮����������������෴���ߵ�����һ��


typedef struct
{
    short mode;		      // ��ԭ��ģʽȡֵ��Χ1~36
    double highSpeed;     // ����Home���ٶȣ���λpulse/ms
    double lowSpeed;	  // ����Index���ٶȣ���λpulse/ms
    double acc;		      // ������ٶȣ���λpulse/ms^2
    int32_t offset;       // ����ƫ��������λpulse
    short check;          // �Ƿ������Լ칦�ܣ�1-���ã�����ֵ-������
    short autoZeroPos;    // ��������Ƿ��Զ����㣬1-�Զ����㣬����ֵ-������
    int32_t motorStopDelay; //�����λ��ʱ����λ����������
    short pad1[3];	      // ����������Ҫ���ã�
} TStandardHomePrm;

typedef struct
{
    short run;           // �����ڽ��л�ԭ�㣬0����ֹͣ�˶���1-���ڻ�ԭ��
    short stage;         // ��ԭ���˶��Ľ׶�
    short error;         // ��ԭ����̵ķ����Ĵ���
    short pad1[3];       // �������޾��庬�壩
    int32_t capturePos;  // ����Home��Indexʱ�̵ı�����λ��
    int32_t targetPos;   // ��Ҫ�˶�����Ŀ��λ�ã�ԭ��λ�û���ԭ��λ��+ƫ��������������Limitʱ��������Home��Indexʱ�����õ���������Ϊ0����ô��ֵ��ʾΪ805306368
} TStandardHomeStatus;

GT_API GTN_ExecuteStandardHome(short core,short axis,TStandardHomePrm *pHomePrm);
GT_API GTN_GetStandardHomePrm(short core,short axis,TStandardHomePrm *pHomePrm);
GT_API GTN_GetStandardHomeStatus(short core,short axis,TStandardHomeStatus *pHomeStatus);

#define POS_COMPARE_RESULT_FIFO_MODE_STATIC                (0)
#define POS_COMPARE_RESULT_FIFO_MODE_LOOP                  (1)

GT_API GTN_SetPosCompareFifoMode(short core,short index,short mode);
GT_API GTN_GetPosCompareFifoMode(short core,short index,short *pMode);
GT_API GTN_GetPosCompareLatchValue(short core,short index,int32_t count,int32_t *pDataX,int32_t *pDataY,int32_t *pCount,TLatchValueInfo *pInfo);



/*-----------------------------------------------------------*/
/* Event Task                                                */
/*-----------------------------------------------------------*/
typedef struct
{
    uint32_t profileMask;
    int32_t offset;
    double vel;
    double acc;
}TTaskMoveEscape;

typedef struct
{
    short eventHit;
    short occupyStatus;
    short enableStatus;
    short pad1;
    int32_t pad2[2];
    double pad3[2];
}TEventStatus;

typedef struct
{
    short start;
    short execute;
    short occupyStatus;
    short executeCount;
    int32_t pad2[2];
    double pad3[2];
}TTaskStatus;

GT_API GTN_GetEventStatus(short core,short index,TEventStatus *pStatus);
GT_API GTN_GetTaskStatus(short core,short index, TTaskStatus *pStatus);
GT_API GTN_SetTriggerMoveEscape(short core,short trigger,TTaskMoveEscape *pPrm);
GT_API GTN_GetPrfRemainderPos(short core,short profile,double *pValue,short count,uint32_t *pClock);


/*-----------------------------------------------------------*/
/* MPG                                                       */
/*-----------------------------------------------------------*/
typedef struct
{
    double pos;
    double vel;
    double reserve[2];
    int32_t di;
    int32_t reserve1[3];
}TMpgInfo;

GT_API GTN_EnableMpgRoundOff(short core,short mpgIndex,short count=1);
GT_API GTN_DisableMpgRoundOff(short core,short mpgIndex,short count=1);
GT_API GTN_ReadMpgInfo(short core,short mpg,TMpgInfo *pMpgInfo);
GT_API GTN_WriteMpgPos(short core,short mpg,double *pPos,short count=1);
GT_API GTN_ReadAuEncPos(short core,short encoder,double *pPos,short count=1);
GT_API GTN_WriteAuEncPos(short core,short encoder,double *pPos,short count=1);


GT_API GTN_ClearMcStatus(short core);
GT_API GTN_SetMcInfo(short core,int32_t info,int32_t index,uint32_t data);
GT_API GTN_GetMcInfo(short core,int32_t info,int32_t index,uint32_t *pData);
GT_API GTN_SetMcMode(short core,short mode,short value);
GT_API GTN_GetMcMode(short core,short mode,short *pValue);



GT_API GTN_GetRNMasterInfo(short core,unsigned short *pPhyId,unsigned short *pType,unsigned short *pInfo);
GT_API GTN_SetRNMasterInfo(short core,unsigned short phyId,unsigned short type,unsigned short info);
GT_API GTN_DmaWriteBlock(short core,uint64_t offsetBytes, void *pBuf, uint32_t bytes,int wait);

GT_API GTN_RN_MltPcPduRd(short core,unsigned char* pData, unsigned char des_id,unsigned short byte_start_offset,unsigned short byte_num);
GT_API GTN_RN_MltPcPduRdUpdate(short core,unsigned char des_id);
GT_API GTN_RN_MltPcPduWr(short core,unsigned char* pData, unsigned char des_id, unsigned short byte_start_offset,unsigned short byte_num);
GT_API GTN_RN_MltPcPduWrUpdate(short core,unsigned char des_id);



//////////////////////////////////////////////////////////////////////////
//Command List
//////////////////////////////////////////////////////////////////////////

#define LIST_STATUS_RESERVE2_REVERSE_LAST_USER_TAG          (4)      // ָ��������ʱ�����������һ�ε��û���ǩ
#define COMMAND_LIST_MODE_STATIC        (0)
#define COMMAND_LIST_MODE_DYNAMIC       (1)

typedef struct
{
    short execute;
    short empty;
    short stopInfo;
    short reserve1;
    short motionDone;
    short commandType;
    short command;
    short direction;
    int32_t executeSegNum;
    int32_t remainderSegCount;
	int32_t userTag;
	int32_t reserve2[5];
} TCommandListStatus;

typedef struct
{
    short mode;
    short elementSize;
    short reserve1[6];
    int32_t forwardSpace;
    int32_t reverseSpace;
    int32_t reserve2[6];
} TCommandListConfig;

typedef struct
{
    short command;
    short index[2];
    short reserve[5];
} TCommandListLink;

typedef struct
{
    short startMode;
    short reserve1[15];
} TCommandListStartParameter;

typedef struct  
{
    uint32_t loop;
    short reserve1[10];
    int32_t reserve2[2];
} TCommandListStaticParameter;

typedef struct  
{
	double velOverride;
	double reserve[40];
} TCommandListEstimatePrm;

typedef struct  
{
	short mode;
	short reserve1[3];
	double time;
	double reserve2[8];
} TCommandListEstimateInfo;

GT_API GTN_GetCommandListSpace(short core,short list,int32_t *pSpace);
GT_API GTN_GetCommandListStatus(short core,short list,TCommandListStatus *pStatus);
GT_API GTN_ClearCommandListData(short core,short list,TListInfo *pListInfo=NULL);
GT_API GTN_CommandListDataEnd(short core,short list);
GT_API GTN_StartCommandList(short core,short list,TListInfo *pListInfo=NULL);
GT_API GTN_StartMultiCommandList(short core,uint32_t mask,TListInfo *pListInfo=NULL);
GT_API GTN_StopCommandList(short core,short index,short stopMode,TListInfo *pListInfo=NULL);
GT_API GTN_SetCommandListStartParameter(short core,short list,TCommandListStartParameter *pPrm,TListInfo *pListInfo);
GT_API GTN_GetCommandListStartParameter(short core,short list,TCommandListStartParameter *pPrm);
GT_API GTN_StopMultiCommandList(short core,uint32_t mask,short stopMode,TListInfo *pListInfo=NULL);
GT_API GTN_ClearCommandListStatus(short core, short index, TListInfo* pListInfo = NULL);
GT_API GTN_SetCommandListConfig(short core,short index,TCommandListConfig *pConfig);
GT_API GTN_GetCommandListConfig(short core,short index,TCommandListConfig *pConfig);
GT_API GTN_SetCommandListLink(short core,short linkId,short list,TCommandListLink *pLink);
GT_API GTN_GetCommandListLink(short core,short linkId,short *pList,TCommandListLink *pLink);
GT_API GTN_ClearCommandListLink(short core,short index);
GT_API GTN_DeleteCommandListLink(short core,short linkId);
GT_API GTN_SetCommandListStopParameter(short core,short list,TCommandListStopParameter *pPrm,TListInfo *pListInfo);
GT_API GTN_GetCommandListStopParameter(short core,short list,TCommandListStopParameter *pPrm);
GT_API GTN_SetCommandListDirection(short core,short index,short direction,TListInfo *pListInfo);
GT_API GTN_GetCommandListDirection(short core,short index,short *pDirection);
GT_API GTN_CommandListDataPush(short core,short list);
GT_API GTN_SetCommandListLinkGroup(short core,short list,uint32_t linkGroupMask);
GT_API GTN_GetCommandListLinkGroup(short core,short list,uint32_t *pLinkGroupMask);
GT_API GTN_SetCommandListStaticParameter(short core,short list,TCommandListStaticParameter *pPrm);
GT_API GTN_GetCommandListStaticParameter(short core,short list,TCommandListStaticParameter *pPrm);
GT_API GTN_SetCommandListEstimateMode(short core,short list,short mode,TCommandListEstimatePrm *pEstimatePrm);
GT_API GTN_GetCommandListEstimateInfo(short core,short list,TCommandListEstimateInfo *pEstimateInfo);

// �¼ܹ�DMAָ�
GT_API GTN_CommandListHsMode(short core,short list,short hsEnable,short link,unsigned short threshold=1,short lookAheadInMc=0);
GT_API GTN_BatchListCommandBegin(short core,short list);
GT_API GTN_BatchListCommandEnd(short core,short list);

#define COMMAND_LIST_MPG_MODE_BIDIRECTION				        (0)			//�����򶼿��Թ̶�������ģʽ
#define COMMAND_LIST_MPG_MODE_POS						        (1)			//MPG������ת�� ����岹
#define COMMAND_LIST_MPG_MODE_NEG						        (-1)		//MPG������ת�� ����岹
#define COMMAND_LIST_MPG_MODE_WINDOW 					        (2)			//�����򶼿��Թ���������ģʽ
#define COMMAND_LIST_MPG_MODE_SIM						        (100)

#define COMMAND_LIST_MPG_FIXED_VEL_COUNT_MAX     (8)
typedef struct
{
	short enable;                                                    // ʹ�ܱ�־
	short master;                                                    // ���������
	short filterTime;                                                // ���������˲�ʱ��
	short mode;                                                      // ���ֵ�ģʽ
	short fixedMpgVelCount;                                          // ���������ĵ�λ����
	short pad1[3];
	int32_t masterEven;                                              // �����������
	int32_t slaveEven;                                               // ���ִ������
	int32_t pad2[2];
	double fixedMpgVel[COMMAND_LIST_MPG_FIXED_VEL_COUNT_MAX];        // ���������ĵ�λRatioֵ
	double ratioUpdateTime;                                          // ������������ˢ��ʱ��
	double pad3[3];
}TCommandListMpgPrm;

GT_API GT_SetCommandListMpgMode(short list,TCommandListMpgPrm *pCommandListMpgPrm,TListInfo *pListInfo);
GT_API GT_GetCommandListMpgMode(short list,TCommandListMpgPrm *pCommandListMpgPrm);
GT_API GTN_SetCommandListMpgMode(short core,short list,TCommandListMpgPrm *pCommandListMpgPrm,TListInfo *pListInfo);
GT_API GTN_GetCommandListMpgMode(short core,short list,TCommandListMpgPrm *pCommandListMpgPrm);
typedef struct
{
    short  count;
    short  reverse1[3];
    double alpha[4];
    double beta[4];
}TProfileScale;
GT_API GTN_SetAxisScale(short core,short profile,TProfileScale *pScale,TListInfo *pListInfo=NULL);
GT_API GTN_GetAxisScale(short core,short profile,TProfileScale *pScale);

/*-----------------------------------------------------------*/
/* Axis                                                      */
/*-----------------------------------------------------------*/
#define AXIS_MOTION_CONSTRAINT_RESERVE1_DV_MAX_LIMIT       (0) // ��������dvmax��Լ���Ƿ���Ч��0������ģ��Ĭ�ϣ�1����Ч��-1������Ч
typedef struct
{
    double velMax;
    double accMax;
    double decMax;
    double jerkMax;
    double dvMax;
    short reverseLimitMode;
    short reserve1[3];
    double reserve2[8];
} TAxisMotionConstraint;
GT_API GTN_SetAxisMotionConstraint(short core,short axis,TAxisMotionConstraint *pPrm,TListInfo *pListInfo);
GT_API GTN_GetAxisMotionConstraint(short core,short axis,TAxisMotionConstraint *pPrm);

typedef struct
{
    short  count;
    short  reserve[3];
    double alpha[4];
    double beta[4];
}TScaleParameter;
GT_API GTN_SetScaleParameter(short core,short type,short index,TScaleParameter *pScalePrm,TListInfo *pListInfo);
GT_API GTN_GetScaleParameter(short core,short type,short index,TScaleParameter *pScalePrm);

GT_API GTN_SetAxisGearRatio(short core,short profile,double *pGearRatio,short count,TListInfo *pListInfo);
GT_API GTN_GetAxisGearRatio(short core,short profile,double *pGearRatio,short count);

typedef struct
{
    double currentToTorqueCoef;
    double ratedCurrent;
    double reserve[4];
} TAxisMotorParameter;
GT_API GTN_SetAxisMotorParameter(short core,short profile,TAxisMotorParameter *pPrm,TListInfo *pListInfo);
GT_API GTN_GetAxisMotorParameter(short core,short profile,TAxisMotorParameter *pPrm);

typedef struct
{
    double deceleration;
    double jerk;
    short reserve1[4];
    double reserve2[5];
} TAxisStopParameter;
GT_API GTN_SetAxisStopParameter(short core,short profile,short type,TAxisStopParameter *pPrm,TListInfo *pListInfo);
GT_API GTN_GetAxisStopParameter(short core,short profile,short type,TAxisStopParameter *pPrm);
GT_API GTN_GetProfileGroupInfo(short core,short profile,short *pGroup,short *pIndentInGroup);

GT_API GTN_SetVelOverride(short core,short index,double velRatio,TListInfo *pListInfo);
GT_API GTN_GetVelOverride(short core,short index,double *pVelRatio);

/*-----------------------------------------------------------*/
/* New Watch  Code                                           */
/*-----------------------------------------------------------*/
#define WATCH_GROUP_TIMER					(0)
#define WATCH_GROUP_BACKGROUND				(1)

#define WATCH_MODE_STATIC					(0)
#define WATCH_MODE_LOOP						(1)
#define WATCH_MODE_DYNAMIC					(2)

#define WATCH_EVENT_MAX						(8)

#define WATCH_EVENT_RUN						(1)
#define WATCH_EVENT_START					(10)
#define WATCH_EVENT_STOP					(20)
#define WATCH_EVENT_OFF						(30)

#define WATCH_CONDITION_NONE				(0)

#define WATCH_CONDITION_EQ					(1)
#define WATCH_CONDITION_NE					(2)
#define WATCH_CONDITION_GE					(3)
#define WATCH_CONDITION_LE					(4)
#define WATCH_CONDITION_GT  				(5)
#define WATCH_CONDITION_LT  				(6)
#define WATCH_CONDITION_CHANGE_TO			(11)
#define WATCH_CONDITION_CHANGE				(12)
#define WATCH_CONDITION_UP					(13)
#define WATCH_CONDITION_DOWN				(14)
#define WATCH_CONDITION_CHANGE_BEYOND		(15)
#define WATCH_CONDITION_CHANGE_MAX			(16)

#define WATCH_CONDITION_REMAIN_AT			(21)
#define WATCH_CONDITION_REMAIN				(22)
#define WATCH_CONDITION_CROSS_POSITIVE		(23)
#define WATCH_CONDITION_CROSS_NEGATIVE		(24)

#define WATCH_CONDITION_NEAREST				(31)
#define WATCH_CONDITION_DELTA				(32)


#define WATCH_VAR_NONE						(0)

#define WATCH_VAR_UUID						(1000)
#define WATCH_VAR_USER_TIMER_COUNT          (1010)
#define WATCH_VAR_USER_TIMER_MS             (1011)
#define WATCH_VAR_POWER_ON_COUNT			(1060)

#define WATCH_VAR_DSP_PROGRAM_COUNT			(1070)

#define WATCH_VAR_DSP_TEMPERATURE			(1072)

#define WATCH_VAR_FPGA_PROGRAM_COUNT		(1080)

#define WATCH_VAR_CLOCK						(1200)
#define WATCH_VAR_PRF_LOOP					(1201)
#define WATCH_VAR_PRF_PERIOD				(1205)
#define WATCH_VAR_PRF_TIME					(1206)

#define WATCH_VAR_SKIP_MODULE				(1211)
#define WATCH_VAR_TEST_MODE					(1212)

#define WATCH_VAR_COMMAND_CODE				(1220)
#define WATCH_VAR_COMMAND_DATA				(1221)
#define WATCH_VAR_COMMAND_COUNT				(1222)
#define WATCH_VAR_COMMAND_READ_FLAG			(1223)

#define WATCH_VAR_LINK_PORT_TX_USE			(1660)
#define WATCH_VAR_LINK_PORT_TX_REQUIRE		(1661)
#define WATCH_VAR_LINKPORT_TX_STATUS		(1662)
#define WATCH_VAR_LINKPORT_TX_ERROR_COUNT	(1663)
#define WATCH_VAR_LINKPORT_TX_SKIP_MAX		(1664)

#define WATCH_VAR_SPORT_STATUS				(1682)
#define WATCH_VAR_SPORT_ERROR_COUNT			(1683)


#define WATCH_VAR_PRF_POS					(6000)
#define WATCH_VAR_PRF_VEL					(6001)
#define WATCH_VAR_PRF_ACC					(6002)
#define WATCH_VAR_PRF_POS_RAW				(6003)
#define WATCH_VAR_PRF_VEL_RAW				(6004)

#define WATCH_VAR_PRF_VEL_F32				(6011)
#define WATCH_VAR_PRF_ACC_F32				(6012)
#define WATCH_VAR_PRF_JERK_F32				(6013)

#define WATCH_VAR_PRF_VEL_64				(6021)
#define WATCH_VAR_PRF_VEL_MS				(6031)
#define WATCH_VAR_PRF_ACC_MS				(6032)

#define WATCH_VAR_PRF_RUN					(6200)
#define WATCH_VAR_LIMIT_POSITIVE_STATUS     (6201)
#define WATCH_VAR_LIMIT_NEGATIVE_STATUS     (6202)

// 6600 Trap

#define WATCH_VAR_PT_PRF_POS_F64			(6650)
#define WATCH_VAR_PT_SPACE					(6660)
#define WATCH_VAR_PT_RECEIVE				(6662)
#define WATCH_VAR_PT_EXECUTE				(6663)

#define WATCH_VAR_TRAP_TOTAL_TIME           (6670)
#define WATCH_VAR_TRAP_REMAIN_TIME          (6671)

// 6700 PVT

// 6750 Follow

// 7000 MoveAbsolute
#define WATCH_VAR_MOVE_ABSOLUTE_DONE		(7008)

// 7050 MoveVelocity
#define WATCH_VAR_MOVE_VELOCITY_IN_VELOCITY	(7058)

#define WATCH_VAR_CRD_PRF_POS				(8000)
#define WATCH_VAR_CRD_PRF_VEL				(8001)
#define WATCH_VAR_CRD_PRF_ACC				(8002)
#define WATCH_VAR_CRD_PRF_VEL_RAW			(8003)

#define WATCH_VAR_CRD_PRF_TEMP_DATA         (8010)

#define WATCH_VAR_CRD_PRF_VEL_MS			(8031)
#define WATCH_VAR_CRD_PRF_ACC_MS			(8032)

#define WATCH_VAR_CRD_RUN					(8200)

#define WATCH_VAR_CRD_SEGMENT_NUMBER		(8202)
#define WATCH_VAR_CRD_SEGMENT_NUMBER_USER	(8203)
#define WATCH_VAR_CRD_COMMAND_RECEIVE		(8204)
#define WATCH_VAR_CRD_COMMAND_EXECUTE		(8205)

#define WATCH_VAR_CRD_FOLLOW_SLAVE_POS		(8600)
#define WATCH_VAR_CRD_FOLLOW_SLAVE_VEL		(8601)

#define WATCH_VAR_CRD_FOLLOW_STAGE			(8610)

#define WATCH_VAR_CONTOUR_PEDAL_POS			(8800)
#define WATCH_VAR_CONTOUR_PRF_POS			(8801)
#define WATCH_VAR_CONTOUR_PRF_POS_SHAPING	(8802)
#define WATCH_VAR_CONTOUR_ENC_POS			(8803)
#define WATCH_VAR_CONTOUR_DAC               (8804)
#define WATCH_VAR_CONTOUR_ERROR				(8805)
#define WATCH_VAR_CONTOUR_FIFO_POINT_COUNT	(8808)
#define WATCH_VAR_CONTOUR_FIFO_POINT_MAX	(8809)
#define WATCH_VAR_PCS_PRF_POS_UI            (9000)
#define WATCH_VAR_PCS_PRF_POS_FILTER_UI     (9003)
#define WATCH_VAR_PCS_ENC_POS_UI            (9006)
#define WATCH_VAR_MCS_PRF_POS_UI            (9010)
#define WATCH_VAR_MCS_PRF_POS_FILTER_UI     (9013)
#define WATCH_VAR_MCS_ENC_POS_UI            (9016)
#define WATCH_VAR_ACS_PRF_POS_UI            (9020)
#define WATCH_VAR_ACS_PRF_POS_FILTER_UI     (9023)
#define WATCH_VAR_ACS_ENC_POS_UI            (9026)

#define WATCH_VAR_GROUP_PRF_VEL_MS			(9031)
#define WATCH_VAR_GROUP_PCS_SYN_VEL_MS  	(9032)
#define WATCH_VAR_GROUP_MCS_SYN_VEL_MS		(9033)
#define WATCH_VAR_GROUP_ACS_SYN_VEL_MS		(9034)

#define WATCH_VAR_PCS_PRF_POS               (9100)
#define WATCH_VAR_PCS_PRF_VEL               (9101)
#define WATCH_VAR_PCS_PRF_ACC               (9102)

#define WATCH_VAR_PCS_PRF_POS_FILTER        (9103)
#define WATCH_VAR_PCS_PRF_VEL_FILTER        (9104)
#define WATCH_VAR_PCS_PRF_ACC_FILTER        (9105)

#define WATCH_VAR_PCS_ENC_POS               (9106)
#define WATCH_VAR_PCS_ENC_VEL               (9107)
#define WATCH_VAR_PCS_ENC_ACC               (9108)

#define WATCH_VAR_MCS_PRF_POS               (9110)
#define WATCH_VAR_MCS_PRF_VEL               (9111)
#define WATCH_VAR_MCS_PRF_ACC               (9112)

#define WATCH_VAR_MCS_PRF_POS_FILTER        (9113)
#define WATCH_VAR_MCS_PRF_VEL_FILTER        (9114)
#define WATCH_VAR_MCS_PRF_ACC_FILTER        (9115)

#define WATCH_VAR_MCS_ENC_POS               (9116)
#define WATCH_VAR_MCS_ENC_VEL               (9117)
#define WATCH_VAR_MCS_ENC_ACC               (9118)

#define WATCH_VAR_ACS_PRF_POS               (9120)
#define WATCH_VAR_ACS_PRF_VEL               (9121)
#define WATCH_VAR_ACS_PRF_ACC               (9122)

#define WATCH_VAR_ACS_PRF_POS_FILTER        (9123)
#define WATCH_VAR_ACS_PRF_VEL_FILTER        (9124)
#define WATCH_VAR_ACS_PRF_ACC_FILTER        (9125)

#define WATCH_VAR_ACS_ENC_POS               (9126)
#define WATCH_VAR_ACS_ENC_VEL               (9127)
#define WATCH_VAR_ACS_ENC_ACC               (9128)

#define WATCH_VAR_GROUP_AXIS_TORQUE         (9130)

#define WATCH_VAR_GROUP_RUN					(9200)

#define WATCH_VAR_LIST_EXECUTE				(9240)
#define WATCH_VAR_LIST_SEG_NUM              (9250)

#define WATCH_VAR_CATCH_UP_STATE                           (12000)
#define WATCH_VAR_CATCH_UP_COMMAND                         (12001)
#define WATCH_VAR_CATCH_UP_MASTER_POS                      (12002)
#define WATCH_VAR_CATCH_UP_MASTER_VEL                      (12003)
#define WATCH_VAR_CATCH_UP_SLAVE_POS                       (12004)
#define WATCH_VAR_CATCH_UP_SLAVE_VEL                       (12005)
#define WATCH_VAR_CATCH_UP_PIECE_POS                       (12006)
#define WATCH_VAR_CATCH_UP_PIECE_ID                        (12007)
#define WATCH_VAR_CATCH_UP_PIECE_COUNT                     (12008)
#define WATCH_VAR_CATCH_UP_PIECE_FIFO_COMMAND_RECEIVE      (12009)
#define WATCH_VAR_CATCH_UP_PIECE_FIFO_COMMAND_SEND         (12010)
#define WATCH_VAR_CATCH_UP_SYNCH_DISTANCE                  (12011)
#define WATCH_VAR_CATCH_UP_SYNCN_TIME                      (12012)
#define WATCH_VAR_CATCH_UP_PIECE_START_POS                 (12013)
#define WATCH_VAR_CATCH_UP_PIECE_SYNCH_POS                 (12014)
#define WATCH_VAR_CATCH_UP_SLAVE_START_POS                 (12015)
#define WATCH_VAR_CATCH_UP_SLAVE_SYNCH_POS                 (12016)

#define WATCH_VAR_POS_COMPARE_COMMAND_RECEIVE	(17422)
#define WATCH_VAR_POS_COMPARE_COMMAND_SEND		(17423)
#define WATCH_VAR_POS_COMPARE_COMMAND_LEFT		(17424)
#define WATCH_VAR_POS_COMPARE_COMMAND_TX		(17425)
#define WATCH_VAR_POS_COMPARE_PULSE_COUNT		(17426)
#define WATCH_VAR_POS_COMPARE_PSO_ON_OFF		(17427)
#define WATCH_VAR_POS_COMPARE_PSO_REG			(17430)
#define	WATCH_VAR_POS_COMPARE_PSO_REG_EXT		(17431)
#define	WATCH_VAR_POS_COMPARE_ENC_PSO_ON_OFF	(17432)

#define WATCH_VAR_SCAN_PRF_POS				(18000)
#define WATCH_VAR_SCAN_PRF_VEL				(18001)
#define WATCH_VAR_SCAN_PRF_ACC				(18002)

#define WATCH_VAR_SCAN_PRF_POS_X			(18010)
#define WATCH_VAR_SCAN_PRF_POS_Y			(18020)
#define WATCH_VAR_SCAN_PRF_POS_Z			(18030)

#define WATCH_VAR_SCAN_RUN					(18200)

#define WATCH_VAR_SCAN_SEGMENT_NUMBER		(18202)

#define WATCH_VAR_SCAN_COMMAND_RECEIVE		(18422)
#define WATCH_VAR_SCAN_COMMAND_SEND			(18423)
#define WATCH_VAR_SCAN_COMMAND_LEFT			(18424)
#define WATCH_VAR_SCAN_COMMAND_TX			(18425)

#define WATCH_VAR_LASER_HSIO				(18600)
#define WATCH_VAR_LASER_POWER				(18601)
#define WATCH_VAR_LASER_WORK_RATIO			(18602)

#define WATCH_VAR_AXIS_PRF_POS				(20000)
#define WATCH_VAR_AXIS_PRF_VEL				(20001)
#define WATCH_VAR_AXIS_PRF_ACC				(20002)

#define WATCH_VAR_AXIS_PRF_POS_OTHER		(20004)
#define WATCH_VAR_AXIS_PRF_VEL_OTHER		(20005)

#define WATCH_VAR_AXIS_PRF_POS_FILTER		(20010)
#define WATCH_VAR_AXIS_PRF_VEL_FILTER		(20011)

#define WATCH_VAR_AXIS_TEMP_PRF_POS_FILTER  (20012)
#define WATCH_VAR_AXIS_PRF_POS_FILTER_BEFORE_COMP (20013)

#define WATCH_VAR_AXIS_PRF_VEL_64			(20021)
#define WATCH_VAR_AXIS_PRF_VEL_MS			(20031)
#define WATCH_VAR_AXIS_PRF_ACC_MS			(20032)

#define WATCH_VAR_AXIS_STATUS		        (20100)

#define WATCH_VAR_AXIS_RUN		            (20200)

#define WATCH_VAR_AXIS_ENC_POS_FILTER		(20310)
#define WATCH_VAR_AXIS_ENC_VEL_FILTER		(20311)

#define WATCH_VAR_AXIS_ENC_VEL_64_FILTER	(20321)

#define WATCH_VAR_AXIS_PREDICTION_POS_IN    (20350)
#define WATCH_VAR_AXIS_PREDICTION_POS_IN_2  (20351)
#define WATCH_VAR_AXIS_PREDICTION_POS_OUT   (20352)

#define WATCH_VAR_AXIS_PREDICTION_VEL_IN    (20355)
#define WATCH_VAR_AXIS_PREDICTION_VEL_IN_2  (20356)
#define WATCH_VAR_AXIS_PREDICTION_VEL_OUT   (20357)

#define WATCH_VAR_AXIS_PREDICTION_OUT       (20360)
#define WATCH_VAR_AXIS_PREDICTION_FILTER_POS                    (20361)
#define WATCH_VAR_AXIS_PREDICTION_FILTER_VEL                    (20362)

#define WATCH_VAR_POSCOMPARE_PREDICTION_ENABLE                  (20370)
#define WATCH_VAR_POSCOMPARE_PREDICTION_WORK                    (20371)
#define WATCH_VAR_POSCOMPARE_PREDICTION_OUTPUT_COUNT_TOTAL      (20372)

#define WATCH_VAR_DRIVER_ACT_VEL			(20400)
#define WATCH_VAR_STIMULATE_DATA			(20401)
#define WATCH_VAR_DRIVER_CURRENT_KVFF		(20402)

#define WATCH_VAR_CONTROL_ERROR				(20500)

#define WATCH_VAR_BACKLASH_VALUE			(21000)
#define WATCH_VAR_LEADSCREW_VALUE			(21001)
#define WATCH_VAR_FRICTION_VALUE			(21003)

#define WATCH_VAR_ENC_POS					(30000)
#define WATCH_VAR_ENC_VEL					(30001)
#define WATCH_VAR_AU_ENC_POS				(30002)
#define WATCH_VAR_AU_ENC_VEL				(30003)

#define WATCH_VAR_PULSE_POS					(30010)

#define WATCH_VAR_ENC_VEL_64				(30021)
#define WATCH_VAR_AU_ENC_VEL_64				(30022)
#define WATCH_VAR_ENC_VEL_64_1MS			(30023)
#define WATCH_VAR_AU_ENC_VEL_64_1MS			(30024)

#define WATCH_VAR_MPG_INFO					(30200)
#define WATCH_VAR_AU_ENCODER_EX_POS         (30201)
#define WATCH_VAR_AU_ENCODER_EX_VEL         (30202)
#define WATCH_VAR_MPG_ENCODER_POS           (30203)
#define WATCH_VAR_MPG_ENCODER_VEL           (30204)

#define WATCH_VAR_GPI						(31000)
#define WATCH_VAR_LIMIT_POSITIVE			(31010)
#define WATCH_VAR_LIMIT_NEGATIVE			(31020)
#define WATCH_VAR_ALARM                     (31030)
#define WATCH_VAR_HOME                      (31040)
#define WATCH_VAR_ARRIVE                    (31050)
#define WATCH_VAR_ARRIVE_DI                                (31055)  // ��λ�����ź�
#define WATCH_VAR_SERVO_READY_DI                           (31056)  // �ŷ�ʹ����������ź�
#define WATCH_VAR_SERVO_READY_TO_SWITCH_ON_DI              (31057)  // �ŷ�ʹ��׼�����������ź�
#define WATCH_VAR_BANK_GPI					(31060)

#define WATCH_VAR_GPI_RAW                   (31100)
#define WATCH_VAR_LIMIT_POSITIVE_RAW        (31110)
#define WATCH_VAR_LIMIT_NEGATIVE_RAW        (31120)
#define WATCH_VAR_ALARM_RAW                 (31130)
#define WATCH_VAR_HOME_RAW                  (31140)
#define WATCH_VAR_ARRIVE_RAW                (31150)

#define WATCH_VAR_GPO						(32000)
#define WATCH_VAR_ENABLE					(32010)
#define WATCH_VAR_CLEAR 					(32020)

#define WATCH_VAR_AI                        (33000)
#define WATCH_VAR_AU_AI                     (33100)

#define WATCH_VAR_AO                        (34000)

#define WATCH_VAR_TRIGGER_EXECUTE			(38000)
#define WATCH_VAR_TRIGGER_STATUS			(38001)
#define WATCH_VAR_TRIGGER_POSITION			(38002)

#define WATCH_VAR_TRIGGER_COUNT				(38010)

#define WATCH_VAR_TRIGGER_NOTIFY_ENABLE			(38020)
#define WATCH_VAR_TRIGGER_NOTIFY_STATUS_ECHO	(38021)
#define WATCH_VAR_TRIGGER_NOTIFY_CLEAR_WAIT		(38022)

#define WATCH_VAR_TRIGGER_DELTA_CROSS_COUNT		(38110)


#define WATCH_VAR_POS_LOOP_ERROR			(40000)
#define WATCH_VAR_POS_LOOP_REF_POS			(40001)
#define WATCH_VAR_POS_LOOP_FILTER_VALUE		(40002)

#define WATCH_VAR_FIR_POS_IN				(48000)
#define WATCH_VAR_FIR_POS_OUT				(48001)

#define WATCH_VAR_WATCH_ENABLE				(52000)
#define WATCH_VAR_WATCH_TIME				(52001)
#define WATCH_VAR_WATCH_EVENT_VALUE_WORK	(52002)

#define WATCH_VAR_INT32						(52020)
#define WATCH_VAR_INT64						(52021)
#define WATCH_VAR_FLOAT						(52022)
#define WATCH_VAR_DOUBLE					(52023)
#define WATCH_VAR_BOOL						(52024)


#define WATCH_VAR_TERMINAL_LIMIT_POSITIVE		(53000)
#define WATCH_VAR_TERMINAL_LIMIT_NEGATIVE		(53001)
#define WATCH_VAR_TERMINAL_ALARM				(53002)
#define WATCH_VAR_TERMINAL_HOME					(53003)
#define WATCH_VAR_TERMINAL_GPI					(53004)
#define WATCH_VAR_TERMINAL_ARRIVE				(53005)
#define WATCH_VAR_TERMINAL_MPG					(53009)

#define WATCH_VAR_TERMINAL_ENABLE				(53010)
#define WATCH_VAR_TERMINAL_CLEAR				(53011)
#define WATCH_VAR_TERMINAL_GPO					(53012)

#define WATCH_VAR_TERMINAL_DAC					(53020)

#define WATCH_VAR_TERMINAL_PULSE				(53022)
#define WATCH_VAR_TERMINAL_ENCODER				(53023)
#define WATCH_VAR_TERMINAL_ADC					(53024)

#define WATCH_VAR_TERMINAL_AU_ENCODER			(53026)

#define WATCH_VAR_TERMINAL_PRF_POS				(53030)

#define WATCH_VAR_TERMINAL_TRIGGER_POSITION     (53040)
#define WATCH_VAR_TERMINAL_TRIGGER_STATUS       (53041)

#define WATCH_VAR_TERMINAL_COMMAND				(53100)
#define WATCH_VAR_TERMINAL_STATUS				(53101)

#define WATCH_VAR_DRIVER_FOLLOW_ERROR	        (53112)//��ȡ��������ʵ�ʸ������Ǹ��ݱ����������λ�������ꡣ

#define WATCH_VAR_EVENT_HIT						(60000)
#define WATCH_VAR_TASK_START					(61000)
#define WATCH_VAR_TASK_WORK						(61001)

#define WATCH_VAR_ATL_TORQUE			        (61201)//��ȡ��������ʵ�ʵ�����������ϵΪ��ֵ1000��Ӧ�������������

typedef struct
{
	short enable;						// �ɼ�ʹ��
	short run;							// �ɼ�״̬
	uint32_t time;					// �ɼ�����
	uint32_t head;					// ͷָ��
	uint32_t threshold;			// ������ɲɼ�����

	short interval;						// �ɼ����
	short mode;							// �ɼ�ģʽ
	unsigned short countBeforeEvent;	// �¼�����֮ǰ�Ĳɼ�����
	unsigned short countAfterEvent;		// �¼������Ժ�Ĳɼ�����
	unsigned short varCount;			// �ɼ���������
	unsigned short eventCount;			// �ɼ��¼�����
} TWatchInfo;

typedef struct
{
	short width;
	short precision;
	char seperator;
	short hex;
} TWatchFormat;

GT_API GTN_GetWatchInfo(short core,TWatchInfo *pInfo);
GT_API GTN_SetWatchFormat(short core,const TWatchFormat *pFormat);
GT_API GTN_GetWatchFormat(short core,TWatchFormat *pFormat);
GT_API GTN_SetWatchFormatEx(short core,short group,const TWatchFormat *pFormat);
GT_API GTN_GetWatchFormatEx(short core,short group,TWatchFormat *pFormat);
GT_API GTN_GetWatchInfoEx(short core,short group,TWatchInfo *pInfo);

#define WATCH_GROUP_TIMER					(0)
#define WATCH_GROUP_BACKGROUND				(1)

#define WATCH_LOAD_MODE_NONE				(0)
#define WATCH_LOAD_MODE_BOOT				(2)
#define WATCH_LOAD_MODE_RUN					(3)

#define WATCH_MODE_STATIC					(0)
#define WATCH_MODE_LOOP						(1)
#define WATCH_MODE_DYNAMIC					(2)

#define WATCH_EVENT_RUN						(1)
#define WATCH_EVENT_START					(10)
#define WATCH_EVENT_STOP					(20)
#define WATCH_EVENT_OFF						(30)

#define WATCH_CONDITION_NONE				(0)

#define WATCH_CONDITION_EQ					(1)
#define WATCH_CONDITION_NE					(2)
#define WATCH_CONDITION_GE					(3)
#define WATCH_CONDITION_LE					(4)
#define WATCH_CONDITION_GT  				(5)
#define WATCH_CONDITION_LT  				(6)

#define WATCH_CONDITION_CHANGE_TO			(11)
#define WATCH_CONDITION_CHANGE				(12)
#define WATCH_CONDITION_UP					(13)
#define WATCH_CONDITION_DOWN				(14)
#define WATCH_CONDITION_CHANGE_BEYOND		(15)
#define WATCH_CONDITION_CHANGE_MAX			(16)

#define WATCH_CONDITION_REMAIN_AT			(21)
#define WATCH_CONDITION_REMAIN				(22)
#define WATCH_CONDITION_CROSS_POSITIVE		(23)
#define WATCH_CONDITION_CROSS_NEGATIVE		(24)

#define WATCH_CONDITION_NEAREST				(31)
#define WATCH_CONDITION_DELTA				(32)
//typedef struct
//{
//	unsigned short type;
//	unsigned short index;
//	unsigned short id;
//} TWatchVar;

typedef struct
{
	unsigned short type;
	unsigned short loop;
	unsigned short watchCount;
	TWatchVar var;
	unsigned short condition;
	double value;
} TWatchEvent;

typedef struct
{
	uint32_t *pAddress;
	unsigned short length;
	short fraction;
	unsigned short format;
	unsigned short hex;
	unsigned short sign;
	unsigned short bit;
} TWatchVarInfo;

GT_API GTN_SetWatchGroup(short core,short group);
GT_API GTN_GetWatchGroup(short core,short *pGroup);
GT_API GTN_LoadWatchConfig(short core,char *pFile);
GT_API GTN_SaveWatchConfig(short core,short group,char *pFile);
GT_API GTN_PrintWatch(short core,const char *pFileName,int32_t start=0,uint32_t printCount=0);
GT_API GTN_ReadWatch(short core,short varIndex,double *pBuffer,uint32_t bufferSize,uint32_t *pReadCount);
GT_API GTN_ProgramWatch(short core,short loadMode);
GT_API GTN_GetWatchLoadMode(short core,short group,short *pLoadMode);

GT_API GTN_ClearWatch(short core,short mode=0);
GT_API GTN_AddWatchVar(short core,const TWatchVar *pVar);
GT_API GTN_AddWatchEvent(short core,const TWatchEvent *pEvent);
GT_API GTN_WatchOn(short core,short interval=0,short mode=WATCH_MODE_STATIC,unsigned short count=0);
GT_API GTN_WatchOff(short core);

GT_API GTN_GetWatchEvent(short core,short index,TWatchEvent *pEvent);
GT_API GTN_GetWatchVar(short core,short index,TWatchVar *pVar,TWatchVarInfo *pVarInfo);
GT_API GTN_SetWatchModeEx(short core,short group,short mode);
GT_API GTN_SetWatchIntervalEx(short core,short group,short interval);

#define VAR_FORMAT_INT						(1)
#define VAR_FORMAT_FLOAT					(2)
#define VAR_FORMAT_DOUBLE					(3)

#define WATCH_LOAD_MODE_NONE				(0)
#define WATCH_LOAD_MODE_BOOT				(2)
#define WATCH_LOAD_MODE_RUN					(3)



#define VAR_CALCULATE_MAX					(32)

#define VAR_CALCULATE_NONE					(0)
#define VAR_CALCULATE_OR					(1)
#define VAR_CALCULATE_AND					(3)
#define VAR_CALCULATE_NOT					(5)

#define VAR_CALCULATE_ADD					(11)
#define VAR_CALCULATE_SUB					(12)
#define VAR_CALCULATE_MUL					(13)
#define VAR_CALCULATE_DIV					(14)

// �û��ӿڸ��ٶ�Ԫ�ؽṹ��
typedef struct
{
    int32_t code;                                      // ��Ҫ��ȡ�ĸ��ٶ�Ԫ�ر���,�μ�WATCH��������
    short index;                                    // ��Ҫ��ȡ�ĸ��ٶ�Ԫ������,��1��ʼ
    short subIndex;                                 // ��Ҫ��ȡ�ĸ��ٶ�Ԫ��������,��1��ʼ
    short pad1[2];                                  // Ԥ��
}TReadHsCommand;
GT_API GTN_AddReadHs(short core,TReadHsCommand *pCommand);
GT_API GTN_LoadReadHsConfig(short core,char *pFile);
GT_API GTN_ReadHsOn(short core,short enable,short mode,double interval);
GT_API GTN_ClearReadHs(short core);
GT_API GTN_SetReadHs(short core,short enable,short mode,short interval);
GT_API GTN_ReadHsReadBuffer(short core,short *pData,int32_t count);
GT_API GTN_FlushReadHs(short core,short wait);


typedef struct
{
    short mode;
    short pad0;
    int32_t band;		//�������жϵ�λ����
    int32_t time;		//�������жϵ�λʱ��
    int32_t pad1[2];
}TAxisArrivePrm;
GT_API GTN_SetAxisArriveMode(short core,short axis,TAxisArrivePrm *pPrm);
GT_API GTN_GetAxisArriveMode(short core,short axis,TAxisArrivePrm *pPrm);


#define MAX_CRDMPG_FIXEDMPGVEL 8
typedef struct
{
    short enable;                                                        //ʹ�ܱ�־
    short master;                                                        //���������
    short filterTime;                                                    //���������˲�ʱ��
    short mode;                                                          //���ֵ�ģʽ
    short fixedMpgVelCount;                                              //���������ĵ�λ����
    short pad1[3];
    int32_t masterEven;                                                     //�����������
    int32_t slaveEven;                                                      //���ִ������
    int32_t pad2[2];
    double fixedMpgVel[MAX_CRDMPG_FIXEDMPGVEL];                          //���������ĵ�λRatioֵ
    double ratioUpdateTime;                                              //������������ˢ��ʱ��
    double pad3[3];
}TCrdMpgPrm;
GT_API GTN_SetCrdMPGMode(short core,short crd,short enable,short master,int32_t masterEven,int32_t slaveEven,short filterTime,short mode);
GT_API GTN_GetCrdMPGMode(short core,short crd,short *pEnable,short *pMaster,int32_t *pMasterEven,int32_t *pSlaveEven,short *pFilterTime,short *pMode,short *pFifoEnd);
GT_API GTN_SetCrdMPGModeEx(short core,short crd,TCrdMpgPrm *pMpgPrm);
GT_API GTN_GetCrdMPGModeEx(short core,short crd,short *pFifoEnd,TCrdMpgPrm *pCrdMpgPrm);


typedef struct
{
    short mode;     //�˶�����,0-��λ��6-PVT������������ʱ��֧��
    short enable;   //�Ƿ�ʹ�ܣ�0-��ʹ�ܣ�1-ʹ��
    short trigger;  //trigger������ȡֵ��1��ʼ
    short pad1;     //����
    int32_t distance;  //����ʱƫ�����������ɸ�����λ������
    int32_t posLimit;  //���¹滮�󣬴���λ��+ƫ�������ܳ�����ֵ
    double vel;     //Ŀ���ٶȣ����¹滮��Ŀ���ٶȣ���λ������/ms
    double acc;     //��Ҫ����ʱ�ļ��ٶȣ���λ������/ms
    double dec;     //�˶�������ƫ�����ļ��ٶȣ���λ������/ms
    double percent; //���ٶ�S������ʱ��ٷֱȣ�����60��ʾ60%
    double reserve[4];
}TTriggerProfilePrm;

typedef struct
{
    short mode;
    short enable;
    short execute;          //�Ƿ�ִ����,0-δִ�У�1-ִ��
    short status;           //ִ�й����е�״̬������Ϊ0���쳣�򷵻ش�����
    int32_t endPos;         //�յ�λ�ã�����+ƫ������
    int32_t reserve[7];
}TTriggerProfileStatus;

#define TRIGGER_PROFILE_STATUS_NONE              (0)                 // ״̬����
#define TRIGGER_PROFILE_STATUS_ERROR_END_POS     (1)                 // ���񵽵�λ�û������õ�λ���쳣
#define TRIGGER_PROFILE_STATUS_VEL               (2)                 // ���õ�Ŀ���ٶ�С�ڵ�ǰ�˶��ٶ�

GT_API GTN_SetTriggerProfilePrm(short core,short profile,TTriggerProfilePrm *pPrm);
GT_API GTN_GetTriggerProfileStatus(short core,short profile,TTriggerProfileStatus *pSts);


/*-----------------------------------------------------------*/
/* DEBUG INFO                                                */
/*-----------------------------------------------------------*/
GT_API GTN_PrintLogInfo(short core, const char* pFileName, int32_t start = 0, int32_t count = 0);
GT_API GTN_PrintLogInfoDebug(short core, const char* pFileName, int32_t start = 0, int32_t count = 0);
GT_API GTN_PrintMcStsInfo(short core,const char *pFileName,short type,short index,short count);
GT_API GTN_PrintCommandInfo(short core,const char *pFileName,int32_t start,int32_t count);

#define COMMANDINFO_DATA_MAX       (225)
typedef struct
{
    uint32_t   commandCode;                        //��־��ָ����
    short   commandRtn;                            //2word����
    short   errorCode;
    uint32_t  clockTime;                           //��������ʱ��
    int32_t    segmentNum;                         //�κ�
    int32_t    userTag;                            //�û���ǩ
    short   dataLength;
    unsigned short  data16[COMMANDINFO_DATA_MAX];  //
} TCommandInfoData;
//��ȡָ�������Ϣ
GT_API GTN_GetLastCommandError(short core, TCommandInfoData* getCommandInfoData, int32_t start = -1, int32_t count = 1);

/*-----------------------------------------------------------*/
/* ILC                                                       */
/*-----------------------------------------------------------*/
struct TIlcResult
{
    double ErrorMax;
    double ErrorAvg;
    double ErrorRms;
    double pad1[9];
    short  pad2[10];
};

GT_API GTN_InitIlc(short core);
GT_API GTN_StartIlc(short core,short crd);
GT_API GTN_StopIlc(short core,short crd,TIlcResult *pPrm);
GT_API GTN_SaveIlcFile(short core,char *pIlcFile);
GT_API GTN_LoadIlcFile(short core,short crd,char *filePath);

GT_API GTN_SetIterationLearnData(short core,short axis,double *pData,uint32_t count);
GT_API GTN_EnableIterationLearn(short core,short axis,short mode,double k);

GT_API GTN_SetIteraionData(short core,int32_t count,double xPrf,double yPrf,double xEnc,double yEnc,short pso);
GT_API GTN_GetIteraionData(short core,int32_t count,double *xPrf,double *yPrf,double *xEnc,double *yEnc,double *xRef,double *yRef,double *error,double *xErr,double *yErr, short *pso,int32_t *index);

/*----------------*/
/*�񾵼������ָ��*/
/*----------------*/
#define    SCAN_LASER_MODE_DUTY_RATIO          (0)
#define    SCAN_LASER_MODE_FREQUENCY           (1)
#define    SCAN_LASER_MODE_ANALOG              (2)
#define    SCAN_LASER_MODE_PARALLEL            (4)
#define    SCAN_LASER_MODE_NONE               (10)

/*ռ�ձ�ģʽ�̶�����*/
typedef struct
{
    double minDutyRatio;
    double maxDutyRatio;
    double frequency;
}TLaserDutyRatioModeParameterPro;
/*Ƶ��ģʽ�̶�����*/
typedef struct
{
    double minFrequency;
    double maxFrequency;
    double pulseWidth;
}TLaserFrequencyModeParameterPro;
/*����ʽ�̶�����*/
typedef struct
{
    double minParallel;                                    // ���ڼ���ģʽ�µĲ��ڼ�����С����ֵ
    double maxParallel;                                    // ���ڼ���ģʽ�µĲ��ڼ����������ֵ
}TlasetParallelModeParameterPro;
/*ģ����ģʽ�̶�����*/
typedef struct
{
    double minVoltage;
    double maxVoltage;
}TlaserAnalogModeParameterPro;
/*�������ģʽ�̶�����*/
typedef union
{
    TLaserDutyRatioModeParameterPro dutyRatioModePrm;
    TLaserFrequencyModeParameterPro frequencyModePrm;
    TlaserAnalogModeParameterPro analogModePrm;
    TlasetParallelModeParameterPro parallelModePrm;
    double data[8];
}TLaserParameterUnionPro;
/*������Ϣ����*/
typedef struct
{
    unsigned short laserOn;   //���⿪��״̬
    unsigned short laserMode; //PWM���ģʽ���궨��
    short pad[2];             //����
    double power;             //��������
    TLaserParameterUnionPro laserPrm;
}TLaserInfoPro;

typedef struct
{
    unsigned short laserMode; //PWM���ģʽ�������
    short pad[3];             //����
    TLaserParameterUnionPro laserPrm;
}TLaserParameterPro;

GT_API GTN_GetScanLaserLinkPro(short core,short scanCrd,short *pLaserChannel);
GT_API GTN_SetScanLaserLinkPro(short core,short scanCrd,short laserChannel,TListInfo *pListInfo=NULL);//�񾵼����,laserChannelΪ0���ǽ��
GT_API GTN_GetScanLaserInfoPro(short core,short scanCrd,TLaserInfoPro *pPrm);
GT_API GTN_SetScanLaserEnablePro(short core,short scanCrd,short laserEnable,TListInfo *pListInfo=NULL);//���⿪�ع�
GT_API GTN_SetScanLaserPrmPro(short core,short scanCrd,TLaserParameterPro *pLaserPrm,TListInfo *pListInfo=NULL);//����ģʽ�͹̶���������
GT_API GTN_SetScanLaserPowerPro(short core,short scanCrd,double power,TListInfo *pListInfo=NULL);//������������
GT_API GTN_SetScanLaserDelayPro(short core,short scanCrd,double laserOnDelay,double laserOffDelay,TListInfo *pListInfo);

/*----------------*/
/*�°��񾵼������ָ�PWM�����ڡ�ģ��������ͬʱ�ڻ������л�������ָ����п���*/
/*----------------*/
typedef struct
{
    double minDuty;                              // ռ�ձ�����������Сֵ��ȡֵ��Χ��[0,100]����λ��%
    double maxDuty;                              // ռ�ձ������������ֵ��ȡֵ��Χ��[0,100]����λ��%
    double minFrequency;                         // Ƶ������������Сֵ��ȡֵ��Χ��[0,1562.5]����λ��kHz
    double maxFrequency;                         // Ƶ�������������ֵ��ȡֵ��Χ��[0,1562.5]����λ��kHz
    double minPulseWidth;                        // ��������������Сֵ��ȡֵ��Χ��[0,65535]����λ��us
    double maxPulseWidth;                        // ���������������ֵ��ȡֵ��Χ��[0,65535]����λ��us
}TLaserPwmPrmPro;
GT_API GTN_SetScanLaserPwmPrmPro(short core,short scanCrd,TLaserPwmPrmPro *pPrm,TListInfo *pListInfo);
GT_API GTN_GetScanLaserPwmPrmPro(short core,short scanCrd,TLaserPwmPrmPro *pPrm);

GT_API GTN_SetScanLaserPwmDutyPro(short core,short scanCrd,double duty,TListInfo *pListInfo);
GT_API GTN_SetScanLaserPwmFrequencyPro(short core,short scanCrd,double frequency,TListInfo *pListInfo);
GT_API GTN_SetScanLaserPwmPulseWidthPro(short core,short scanCrd,double pulseWidth,TListInfo *pListInfo);

GT_API GTN_SetScanLaserVoltagePrmPro(short core,short scanCrd,double minVoltage,double maxVoltage,TListInfo *pListInfo);
GT_API GTN_GetScanLaserVoltagePrmPro(short core,short scanCrd,double *pMinVoltage,double *pMaxVoltage);
GT_API GTN_SetScanLaserVoltagePro(short core,short scanCrd,double voltage,TListInfo *pListInfo);

GT_API GTN_SetScanLaserParallelPrmPro(short core,short scanCrd,double minParallel,double maxParallel,TListInfo *pListInfo);
GT_API GTN_GetScanLaserParallelPrmPro(short core,short scanCrd,double *pMinParallel,double *pMaxParallel);
GT_API GTN_SetScanLaserParallelPro(short core,short scanCrd,double parallel,TListInfo *pListInfo);

/*----------------*/
/*�����ָ��    */
/*----------------*/
#define    SCAN_MOTION_MODE_NONE                (0)
#define    SCAN_MOTION_MODE_JUMP                (1)
#define    SCAN_MOTION_MODE_JUMP_POINT          (2)
#define    SCAN_MOTION_MODE_JUMP_TIME           (3)
#define    SCAN_MOTION_MODE_JUMP_TIME_POINT     (4)
#define    SCAN_MOTION_MODE_MARK                (5)
#define    SCAN_MOTION_MODE_MARK_TIME           (6)

#define    SCAN_MOTION_CIRCLE_DIR_CW            (0)
#define    SCAN_MOTION_CIRCLE_DIR_CCW           (1)
/*��ǰհ����*/
typedef struct
{
    short lookAheadNum;   //ǰհ����
    short highSpeedMode;
    short pad[2];         //����
    double time;          //ʱ�䳣��
    double radiusRatio;   //�������Ƶ��ڲ���
    double reserve[2];    //����
}TScanLookAheadParameterPro;

/*��״̬*/
typedef struct
{
    short run;                    //���˶���־
    short space;
    unsigned short fifoEmpty;     //�ܿձ�־
    short pad1;                   //����
    uint32_t segmentNumber;       //ִ�жκ�
    uint32_t commandReceive;      //���յ���ָ����
    uint32_t commandSend;         //�ѷ��͵�ָ����
    int32_t pad2;                 //����
    double prfVel;                //�ϳɹ滮�ٶ�
}TScanStatusPro;

//Jump�˶���Mark�˶�
typedef struct
{
    double acc;
    double dec;
    double vel;
}TVelModePro;

typedef struct
{
    double acc;
    double dec;
    uint32_t time;
    int32_t pad;//����
}TTimeModePro;

typedef struct
{
    double acc;
    double dec;
    double vel;
    uint32_t motionDelayTime;
    uint32_t laserDelayTime;
}TVelPointModePro;

typedef struct
{
    double acc;
    double dec;
    uint32_t time;
    uint32_t motionDelayTime;
    uint32_t laserDelayTime;
    int32_t pad;//����
}TTimePointModePro;

typedef union
{
    TVelModePro velMode;
    TTimeModePro timeMode;
    TVelPointModePro velPointMode;
    TTimePointModePro timePointMode;
    double data[8];
}TScanMotionPrmUnionPro;

typedef struct
{
    double pos[3];
    double reserve;
    TScanMotionPrmUnionPro motionPrm;
}TScanLinearMotionPro;

typedef struct
{
    double endPos[3];
    double radius;//�뾶���������Ż��ӻ�
    short dir;
    short pad[3];//����
    TScanMotionPrmUnionPro motionPrm;
}TScanCircularMotionPro;

typedef struct
{
    short multiMarkDelayMode;
    unsigned short jumpDelayLengthLimit;
    short pad[2];//����
    double multiMarkLaserOffDelay;
    double multiMarkDelayConst;
    double markDelay;
    double minJumpDelay;
    double maxJumpDelay;
}TScanDelayParameterPro;

typedef struct  
{
	double endPos[3];               // �յ�λ��
	double centerPos[3];            // Բ��λ�ã�����������λ�õ�ƫ����
	short circleDir;                // �˶�����
	short pad[3];//����
	TScanMotionPrmUnionPro motionPrm;
}TScanArcMotionPro;

GT_API GTN_ScanInitPro(short core,short scanCrd,TScanLookAheadParameterPro *pPrm,TListInfo *pListInfo);
GT_API GTN_GetScanCrdPosPro(short core,short scanCrd,double *pPos);
GT_API GTN_GetScanStatusPro(short core,short scanCrd,TScanStatusPro *pPrm);
GT_API GTN_ScanLinearPro(short core,short scanCrd,short motionMode,TScanLinearMotionPro *pPrm,TListInfo *pListInfo);
GT_API GTN_ScanCircularPro(short core,short scanCrd,short motionMode,TScanCircularMotionPro *pPrm,TListInfo *pListInfo);
GT_API GTN_ScanArcMotionPro(short core,short scanCrd,short motionMode,TScanArcMotionPro *pPrm,TListInfo *pListInfo);

#define SCAN_MARK_DELAY_MODE_CONST              (0) // �̶�ʱ����ʱģʽ
#define SCAN_MARK_DELAY_MODE_CHANGE             (1) // ����ʱģʽ

GT_API GTN_SetScanDelayPrmPro(short core,short scanCrd,TScanDelayParameterPro *pPrm,TListInfo *pListInfo=NULL);
GT_API GTN_SetScanMotionDelayPro(short core,short scanCrd,double delayTime,TListInfo *pListInfo);
GT_API GTN_GetScanExecuteTimePro(short core,short scanCrd,double *pExecuteTime);
GT_API GTN_ClearScanExecuteTimePro(short core,short scanCrd);

#define LASER_ENABLE_DO	                       (76) //������ʹ���ź�
#define LASER_RED_LED_DO                       (77) //���������ָʾ�ź�
#define LASER_POWER_LATCH_DO                   (78) //���������������ź�
GT_API GTN_SetScanLaserIOPro(short core, short scanCrd, short doType, int32_t doValue, TListInfo* pListInfo = NULL);

//20200713ͬ��GTS�ı������ƣ����������߼��
GT_API GTN_SetEncResponseCheck(short core,short control,short dacThreshold,double minEncVel,int32_t time);
GT_API GTN_GetEncResponseCheck(short core,short control,short *pDacThreshold,double *pMinEncVel,int32_t *pTime);
GT_API GTN_EnableEncResponseCheck(short core,short control);
GT_API GTN_DisableEncResponseCheck(short core,short control);

/************************************************************************/
/* ��ת�Ṧ��                                                           */
/************************************************************************/
#define ROTARY_DIRECTION_SELECT_MODE_DEFAULT                  (0)
#define ROTARY_DIRECTION_SELECT_MODE_SMART                    (1)

typedef enum 
{
	MC_POSITIVE_DIRECTION,
	MC_NEGATIVE_DIRECTION,
	MC_CURRENT_DIRECTION,
	MC_SHORTEST_WAY,
	MC_BY_POS,
} EMcDirection;

typedef struct
{
    short rotary;
    short pad[3];
    double start;
    double length;
    double reserve;
    double pulse;
} TRotaryConfig;

typedef struct
{
    short fifo;
    short overrideNum;
    short g0Mode;
    short reserve1[5];
    int32_t segNum;
    int32_t reserve2[3];
    double vel;
    double acc;
    double velEnd;
    double velLimit;
    double reserve3[8];
} TLineAbsolutePrm;

GT_API GTN_GetAxisPrfPosRotary(short core,short axis,double *pTheta,double *pRound,short count=1);
GT_API GTN_GetProfileRotaryConfig(short core,short profile,TRotaryConfig *pConfig);
GT_API GTN_GetPrfPosRotary(short core,short profile,double *pTheta,double *pRound,short count=1);
GT_API GTN_SetCrdScale(short core,short crd,short dimension,double alpha,double beta);
GT_API GTN_GetCrdScale(short core,short crd,short dimension,double *pAlpha,double *pBeta);
GT_API GTN_GetCrdRotaryConfig(short core,short crd,short dimension,TRotaryConfig *pConfig);
GT_API GTN_GetCrdPosRotary(short core,short crd,short dimension,double *pTheta,double *pRound,short count=1);
GT_API GTN_GetEncoderRotaryConfig(short core,short encoder,TRotaryConfig *pConfig);
GT_API GTN_GetEncPosRotary(short core,short encoder,double *pTheta,double *pRound,short count=1);
GT_API GTN_SetAxisRotaryConfig(short core,short axis,TRotaryConfig *pConfig);
GT_API GTN_GetAxisRotaryConfig(short core,short axis,TRotaryConfig *pConfig);
GT_API GTN_ZeroAxisRotaryRound(short core,short axis,short count=1);
GT_API GTN_LineAbsoluteEx(short core,short crd,double *pPos,short *pDir,TLineAbsolutePrm *pPrm);
GT_API GTN_SetAxisRotaryDirectionSelectMode(short core,short axis,short mode);
GT_API GTN_GetAxisRotaryDirectionSelectMode(short core,short axis,short *pMode);

typedef struct
{
	double pos;
	double vel;
	double acc;
	double dec;
	short percent;
	short pad1[3];
	double velStart;
	double velEnd;
	short accStartPercent;
	short decEndPercent;
	short dir;
	short pad2;
	short reserve[10];
} TMoveAbsoluteProPrm;
GT_API GTN_MoveAbsolutePro(short core,short profile,TMoveAbsoluteProPrm *pPrm);

/*-----------------------------------------------------------*/
//ԭconfig.h�����ù��ܣ�����������ģ��                       */
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
/* conifg of controller                                      */
/*-----------------------------------------------------------*/
#define RES_LIMIT                       (8)
#define RES_ALARM                       (8)
#define RES_HOME                        (8)
#define RES_GPI                         (16)
#define RES_ARRIVE                      (8)
#define RES_MPG                         (7)
#define RES_ENABLE                      (8)
#define RES_CLEAR                       (8)
#define RES_GPO                         (16)
#define RES_DAC                         (12)
#define RES_STEP                        (8)
#define RES_PULSE                       (8)
#define RES_ENCODER                     (11)
#define RES_LASER                       (2)
#define AXIS_MAX                        (8)
#define PROFILE_MAX                     (8)
#define CONTROL_MAX                     (8)
#define PRF_MAP_MAX                     (2)
#define ENC_MAP_MAX                     (2)

typedef struct DiConfig
{
    short active;
    short reverse;
    short filterTime;
} TDiConfig;

typedef struct CountConfig
{
    short active;
    short reverse;
    short filterType;

    short captureSource;
    short captureHomeSense;
    short captureIndexSense;
} TCountConfig;

typedef struct DoConfig
{
    short active;
    short axis;
    short axisItem;
    short reverse;
} TDoConfig;

typedef struct StepConfig
{
    short active;
    short axis;
    short mode;
    short parameter;
    short reverse;
} TStepConfig;

typedef struct DacConfig
{
    short active;
    short control;
    short reverse;
    short bias;
    short limit;
} TDacConfig;

typedef struct AdcConfig
{
    short active;
    short reverse;
    double a;
    double b;
    short filterMode;
} TAdcConfig;

typedef struct ControlConfig
{
    short active;
    short axis;
    short encoder1;
    short encoder2;
    int32_t  errorLimit;
    short filterType[3];
    short encoderSmooth;
    short controlSmooth;
} TControlConfig;

typedef struct ControlConfigEx
{
    short refType;
    short refIndex;

    short feedbackType;
    short feedbackIndex;

    int32_t  errorLimit;
    short feedbackSmooth;
    short controlSmooth;
} TControlConfigEx;

typedef struct ProfileConfig
{
    short  active;
    double decSmoothStop;
    double decAbruptStop;
} TProfileConfig;

typedef struct AxisConfig
{
    short active;
    short alarmType;
    short alarmIndex;
    short limitPositiveType;
    short limitPositiveIndex;
    short limitNegativeType;
    short limitNegativeIndex;
    short smoothStopType;
    short smoothStopIndex;
    short abruptStopType;
    short abruptStopIndex;
    int32_t  prfMap;
    int32_t  encMap;
    short prfMapAlpha[PRF_MAP_MAX];
    short prfMapBeta[PRF_MAP_MAX];
    short encMapAlpha[ENC_MAP_MAX];
    short encMapBeta[ENC_MAP_MAX];
} TAxisConfig;

#define PROFILE_MAX                     (8)

typedef struct McConfig
{
    TProfileConfig profile[PROFILE_MAX];
    TAxisConfig    axis[AXIS_MAX];
    TControlConfig control[CONTROL_MAX];
    TDacConfig     dac[RES_DAC];
    TStepConfig    step[RES_STEP];
    TCountConfig   encoder[RES_ENCODER];
    TCountConfig   pulse[RES_PULSE];
    TDoConfig      enable[RES_ENABLE];
    TDoConfig      clear[RES_CLEAR];
    TDoConfig      gpo[RES_GPO];
    TDiConfig      limitPositive[RES_LIMIT];
    TDiConfig      limitNegative[RES_LIMIT];
    TDiConfig      alarm[RES_ALARM];
    TDiConfig      home[RES_HOME];
    TDiConfig      gpi[RES_GPI];
    TDiConfig      arrive[RES_ARRIVE];
    TDiConfig      mpg[RES_MPG];
} TMcConfig;

GT_API GTN_SetMcConfig(short core,TMcConfig *pMc);
GT_API GTN_GetMcConfig(short core,TMcConfig *pMc);
GT_API GTN_SetMcConfigToFile(short core,TMcConfig *pMc,char *pFile);
GT_API GTN_GetMcConfigFromFile(short core,TMcConfig *pMc,char *pFile);


GT_API GTN_SaveConfig(short core,char *pFile);
GT_API GTN_SetDiConfig(short core,short diType,short diIndex,TDiConfig *pDi);
GT_API GTN_GetDiConfig(short core,short diType,short diIndex,TDiConfig *pDi);
GT_API GTN_SetDoConfig(short core,short doType,short doIndex,TDoConfig *pDo);
GT_API GTN_GetDoConfig(short core,short doType,short doIndex,TDoConfig *pDo);
GT_API GTN_SetStepConfig(short core,short step,TStepConfig *pStep);
GT_API GTN_GetStepConfig(short core,short step,TStepConfig *pStep);
GT_API GTN_SetDacConfig(short core,short dac,TDacConfig *pDac);
GT_API GTN_GetDacConfig(short core,short dac,TDacConfig *pDac);
GT_API GTN_SetAdcConfig(short core,short adc,TAdcConfig *pAdc);
GT_API GTN_GetAdcConfig(short core,short adc,TAdcConfig *pAdc);
GT_API GTN_SetCountConfig(short core,short countType,short countIndex,TCountConfig *pCount);
GT_API GTN_GetCountConfig(short core,short countType,short countIndex,TCountConfig *pCount);
GT_API GTN_SetControlConfig(short core,short control,TControlConfig *pControl);
GT_API GTN_GetControlConfig(short core,short control,TControlConfig *pControl);
GT_API GTN_SetControlConfigEx(short core,short control,TControlConfigEx *pControl);
GT_API GTN_GetControlConfigEx(short core,short control,TControlConfigEx *pControl);
GT_API GTN_SetProfileConfig(short core,short profile,TProfileConfig *pProfile);
GT_API GTN_GetProfileConfig(short core,short profile,TProfileConfig *pProfile);
GT_API GTN_SetAxisConfig(short core,short axis,TAxisConfig *pAxis);
GT_API GTN_GetAxisConfig(short core,short axis,TAxisConfig *pAxis);
GT_API GTN_ProfileScale(short core,short axis,short alpha,short beta);
GT_API GTN_EncScale(short core,short axis,short alpha,short beta);

/*-----------------------------------------------------------*/
/* Config of Laser and Scan                                  */
/*-----------------------------------------------------------*/
struct TScanCommandMotion
{
    int32_t segmentNumber;
    short x;
    short y;
    int32_t deltaX;
    int32_t deltaY;
    int32_t vel;
    int32_t acc;
};

struct TScanCommandMotionDelay
{
    int32_t delay;
};

struct TScanCommandDo
{
    short doType;
    short doMask;
    short doValue;
};

struct TScanCommandDoDelay
{
    int32_t delay;
};

struct TScanCommandLaser
{
    short mask;
    short value;
} ;

struct TScanCommandLaserDelay
{
    int32_t laserOnDelay;
    int32_t laserOffDelay;
} ;

struct TScanCommandLaserPower
{
    int32_t power;
} ;

struct TScanCommandLaserFrequency
{
    int32_t frequency;
} ;

struct TScanCommandLaserPulseWidth
{
    int32_t pulseWidth;
} ;

struct TScanCommandDa
{
    short daIndex;
    short daValue;
} ;

typedef struct
{
    short module;
    short fifo;
} TScanMap;

GT_API GTN_SetScanMap(short core,short scan,TScanMap *pMap);
GT_API GTN_GetScanMap(short core,short scan,TScanMap *pMap);
GT_API GTN_ClearScanMap(short core);
GT_API GTN_UpdateScanMap(short core);

/*-----------------------------------------------------------*/
//ԭringnet.h���͵Ȼ���������ع��ܵ�ָ��                    */
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
/* Ringnet                                                  */
/*-----------------------------------------------------------*/
#define RTN_SUCCESS                                        (0)
#define RTN_MALLOC_FAIL                                    (-100) /* malloc memory fail */
#define RTN_FREE_FAIL                                      (-101) /* free memory or delete the object fail */
#define RTN_NULL_POINT                                     (-102) /* the param point input is null */
#define RTN_ERR_ORDER                                      (-103) /* call the function order is wrong, some msg isn't validable */
#define RTN_PCI_NULL                                       (-104) /* the pci address is empty, can't access the pci device*/
#define RTN_PARAM_OVERFLOW                                 (-105) /* the param input is too larget*/
#define RTN_LINK_FAIL                                      (-106) /* the two ports both link fail*/
#define RTN_IMPOSSIBLE_ERR                                 (-107) /* it means the system or same function work wrong*/
#define RTN_TOPOLOGY_CONFLICT                              (-108) /* the id conflict*/
#define RTN_TOPOLOGY_ABNORMAL                              (-109) /* scan the net abnormal*/
#define RTN_STATION_ALONE                                  (-110) /* the device no id, it means the device id is 0xF0 */
#define RTN_WAIT_OBJECT_OVERTIME                           (-111) /* multi thread wait for object overtime */
#define RTN_ACCESS_OVERFLOW                                (-112) /* data[i];  i is larger than the define */
#define RTN_NO_STATION                                     (-113) /* the station accessed not existent */
#define RTN_OBJECT_UNCREATED                               (-114) /* the object not created yet*/
#define RTN_PARAM_ERR                                      (-115) /* the param input is wrong*/
#define RTN_PDU_CFG_ERR                                    (-116) /*Pdu DMA Cfg Err*/
#define RTN_PCI_FPGA_ERR                                   (-117) /*PCI op err or FPGA op err*/
#define RTN_CHECK_RW_ERR                                   (-118) /*data write to reg, then rd out, and check err */
#define RTN_REMOTE_UNEABLE                                 (-119) /*the device which will be ctrl by net can't be ctrl by net function*/

#define RTN_NET_REQ_DATA_NUM_ZERO                          (-120) /*mail op or pdu op req data num can't be 0*/
#define RTN_WAIT_NET_OBJECT_OVERTIME                       (-121) /* net op multi thread wait for object overtime */
#define RTN_WAIT_NET_RESP_OVERTIME                         (-122) /* Can't wait for resp */
#define RTN_WAIT_NET_RESP_ERR                              (-123) /*wait mailbox op err*/
#define RTN_INITIAL_ERR                                    (-124) /*initial the device err*/
#define RTN_PC_NO_READY                                    (-125) /*find the station'pc isn't work*/
#define RTN_STATION_NO_EXIST                               (-126)
#define RTN_MASTER_FUNCTION                                (-127) /* this funciton only used by master */

#define RTN_NOT_ALL_RETURN                                 (-128) /* the GT_RN_PtProcessData funciton fail return */
#define RTN_NUM_NOT_EQUAL                                  (-129) /* the station number of RingNet do not equal  the station number of CFG */

#define RTN_CHECK_STATION_ONLINE_NUM_ERR                   (-130) /*Check no slave*/
#define RTN_FILE_ERR_OPEN                                  (-131) /*open file error*/
#define RTN_FILE_ERR_FORMAT                                (-132) /*parse file error*/
#define RTN_FILE_ERR_MISSMATCH                             (-133) /*file info is not match with the actual ones*/
#define RTN_DMALIST_ERR_MISSMATCH                          (-134) /*can't find the slave*/

#define RTN_REQUSET_MAIL_BUS_OVERTIME                      (-150) /*Requset Mail Bus Err*/
#define RTN_INSTRCTION_ERR                                 (-151) /*instrctions err*/
#define RTN_MAIL_RESP_REQ_ERR                              (-152) /*RN_MailRespReq  err*/
#define RTN_CTRL_SRC_ERR                                   (-153) /* the controlled source  is error */
#define RTN_PACKET_ERR                                     (-154) /*packet is error*/
#define RTN_STATION_ID_ERR                                 (-155) /*the device id is not in the right rang*/
#define RTN_WAIT_NET_PDU_RESP_OVERTIME                     (-156) /*net pdu op wait overtime*/
#define RTN_ETHCAT_ENC_POS_ERR                             (-157) /**/

#define RTN_IDLINK_PACKET_ERR                              (-200) /*ilink master  decode err! packet_length is not match*/
#define RTN_IDLINK_PACKET_END_ERR                          (-201) /* the ending of ilink packet is not 0xFF*/
#define RTN_IDLINK_TYPER_ERR                               (-202) /* the type of ilink module is error*/
#define RTN_IDLINK_LOST_CNT                                (-203) /* the ilink module has lost connection*/
#define RTN_IDLINK_CTRL_SRC_ERR                            (-204) /* the controlled source of ilink module is error */
#define RTN_IDLINK_UPDATA_ERR                              (-205) /* the ilink module updata error*/
#define RTN_IDLINK_NUM_ERR                                 (-206) /* the ilink num larger the IDLINK_MAX_NUM(30) */
#define RTN_IDLINK_NUM_ZERO                                (-207) /* the ilink num is zero */

#define RTN_NO_PACKET                                      (301)  /* no valid packet */
#define RTN_RX_ERR_PDU_PACKET                              (-302) /* ERR PDU PACKET */
#define RTN_STATE_MECHINE_ERR                              (-303)
#define RTN_PCI_DSP_UN_FINISH                              (304)
#define RTN_SEND_ALL_FAIL                                  (-305)
#define RTN_STATION_CLOSE                                  (310)
#define RTN_STATION_RESP_FAIL                              (311)

#define RTN_UPDATA_MODAL_ERR                               (-330) /* update the modal in normal way fail*/

#define RTN_NO_MAIL_DATA                                   (340) /*There is no mail data*/
#define RTN_NO_PDU_DATA                                    (341) /*There is no pdu data*/

#define RTN_FILE_PARAM_NUM_ERR                             (-500)
#define RTN_FILE_PARAM_LEN_ERR                             (-501)
#define RTN_FILE_MALLOC_FAIL                               (-502)
#define RTN_FILE_FREE_FAIL                                 (-503)
#define RTN_FILE_PARAM_ERR                                 (-504)
#define RTN_FILE_NOT_EXSITS                                (505)
#define RTN_FILE_CREATE_FAIL                               (510)
#define RTN_FILE_DELETE_FAIL                               (511)
#define RTN_FIFE_CRC_CHECK_ERR                             (-512)
#define RTN_FIFE_FUNCTION_ID_RETURN_ERR                    (-600)
#define RTN_DLL_WINCE                                      (-800)
#define RTN_DLL_WIN32                                      (-801)
#define RTN_XML_STATION_ERR                                (-900)//dma config file confilit with slave type


GT_API GTN_LoadRingNetConfig(short core,char*pFile);
GT_API GTN_SaveRingNetConfig(short core,char *pFile);
GT_API GTN_CheckRingNetStructure(short core,char *pFile,unsigned short *pStatus);


/*-----------------------------------------------------------*/
/* ��ȡSPORT������                                           */
/*-----------------------------------------------------------*/
#define SPORT_COUNT                     (256)

typedef struct
{
    uint32_t terminalTxBuf[SPORT_COUNT];
    uint32_t terminalRxBuf[SPORT_COUNT];
}TTerminalData;

GT_API GTN_ReadTerminalData(short core,TTerminalData *pTerminalData);

/*-----------------------------------------------------------*/
/* Config of module                                          */
/*-----------------------------------------------------------*/
#define TERMINAL_OPERATION_NONE             (0)
#define TERMINAL_OPERATION_SKIP             (1)
#define TERMINAL_OPERATION_CLEAR            (2)
#define TERMINAL_OPERATION_RESET_MODULE     (3)

#define TERMINAL_OPERATION_PROGRAM          (11)

typedef struct
{
    uint32_t portACrcOkCnt;
    unsigned short portACrcErrorCnt;
    uint32_t portBCrcOkCnt;
    unsigned short portBCrcErrorCnt;
    uint32_t reserve;//Ŀǰ���ڶ�ȡFLASH�����ݳ���
} TRingNetCrcStatus;

typedef struct
{
    unsigned short errorCountReceive;
    unsigned short errorCountPackageDown;
    unsigned short errorCountPackageUp;
    unsigned short reserve[13];
} TTerminalError;

typedef struct
{
    short moduleDataType;
    short moduleDataIndex;
    short dataIndex;
    short dataCount;
} TTerminalMap;

GT_API GTN_LoadTerminalConfig(short core,char *pFile);
GT_API GTN_SaveTerminalConfig(short core,char *pFile);
GT_API GTN_TerminalOn(short core,short index);
GT_API GTN_TerminalSynch(short core,short index);
GT_API GTN_TerminalSynchEx(short core,short index,short synchEnable,short synchSource);
GT_API GTN_GetRingNetCrcStatus(short core,short index,TRingNetCrcStatus *pRingNetCrcStatus);
GT_API GTN_GetTerminalError(short core,short index,TTerminalError *pTerminalError);

GT_API GTN_GetTerminalPhyId(short core,short count,short *pPhyId);
GT_API GTN_GetTerminalLinkStatus(short core,short count,short *ringNetType,short *pLinkStatus);
GT_API GTN_SetTerminalMap(short core,short dataType,short moduleIndex,TTerminalMap *pMap);
GT_API GTN_GetTerminalMap(short core,short dataType,short moduleIndex,TTerminalMap *pMap);
GT_API GTN_ClearTerminalMap(short core,short dataType);
GT_API GTN_SetTerminalMode(short core,short station,unsigned short mode);
GT_API GTN_GetTerminalMode(short core,short station,unsigned short *pMode);
GT_API GTN_SetTerminalTest(short core,short station,short index,unsigned short value);
GT_API GTN_GetTerminalTest(short core,short station,short index,unsigned short *pValue);
GT_API GTN_SetTerminalOperation(short core,short operation);
GT_API GTN_GetTerminalOperation(short core,short *pOperation);



#define TERMINAL_LOAD_MODE_NONE             (0)
#define TERMINAL_LOAD_MODE_BOOT             (2)

typedef struct
{
    unsigned short type;
    short id;
    int32_t status;
    uint32_t synchCount;
    uint32_t ringNetType;
    uint32_t portStatus;
    uint32_t sportDropCount;
    uint32_t reserve[7];
} TTerminalStatus;

GT_API GTN_TerminalInit(short core,short detect=1);
GT_API GTN_GetTerminalVersion(short core,short index,TVersion *pTerminalVersion);
GT_API GTN_SetTerminalPermit(short core,short index,short dataType,unsigned short permit);
GT_API GTN_GetTerminalPermit(short core,short index,short dataType,unsigned short *pPermit);
GT_API GTN_SetTerminalPermitEx(short core,short station,short dataType,short *permit,short index,short count);
GT_API GTN_GetTerminalPermitEx(short core,short station,short dataType,short *pPermit,short index,short count);

GT_API GTN_SetTerminalSafeMode(short core,short index,short safeMode);
GT_API GTN_GetTerminalSafeMode(short core,short index,short *pSafeMode);
GT_API GTN_ClearTerminalSafeMode(short core,short index);
GT_API GTN_GetTerminalStatus(short core,short index,TTerminalStatus *pTerminalStatus);
GT_API GTN_GetTerminalType(short core,short count,unsigned short *pType,short *pTypeConnect=NULL);
GT_API GTN_SetTerminalType(short core,short count,short *pType);
GT_API GTN_GetTerminalMapCount(short core,short dataType,short moduleIndex,short *pMapCount);
GT_API GTN_GetTerminalMapData(short core,short dataType,short moduleIndex,short mapIndex,TTerminalMap *pMap);

GT_API GTN_FindStation(short core,short station,uint32_t time);

GT_API GTN_ProgramTerminalConfig(short core,short loadMode);
GT_API GTN_GetTerminalConfigLoadMode(short core,short *pLoadMode);




GT_API GTN_SetMailbox(short core,short station,unsigned short byteAddress,unsigned short *pData,unsigned short wordCount,unsigned short dataMode,unsigned short desId,unsigned short type);
GT_API GTN_GetMailbox(short core,short station,unsigned short byteAddress,unsigned short *pData,unsigned short wordCount,unsigned short dataMode,unsigned short desId,unsigned short type);

/*-----------------------------------------------------------*/
/* UUID                                                      */
/*-----------------------------------------------------------*/
GT_API GTN_SetUuid(short core,char *pUuid,short count);
GT_API GTN_GetUuid(short core,char *pCode,short count);

/*-----------------------------------------------------------*/
/* FLASH                                                     */
/*-----------------------------------------------------------*/
GT_API GTN_SetFlashValue(short core,uint32_t address,short count,short *pData);
GT_API GTN_GetFlashValue(short core,uint32_t address,short count,short *pData);

/*-----------------------------------------------------------*/
/* ����ָ�ָ��                                              */
/*-----------------------------------------------------------*/
GT_API GTN_RN_RingNetRecover(short core,short station);
/*-----------------------------------------------------------*/
/* GSHD�����С��������                                      */
/*-----------------------------------------------------------*/
typedef struct
{
    unsigned short torqueMax;
    unsigned short torquePostive;
    unsigned short torqueNegitive;
    short reserve1;
    double reserve2[4];
}TTorqueLimit;
GT_API GTN_RN_SetMaxTorqueLimit(short core,unsigned short station, short axis, unsigned short torqueMax, unsigned short torquePostive,unsigned short torqueNegitive);
GT_API GTN_RN_GetMaxTorqueLimit(short core,unsigned short station,short axis, unsigned short* torqueMax, unsigned short* torquePostive,  unsigned short* torqueNegitive);
GT_API GTN_RN_SetTorqueLimit(short core,short axis,TTorqueLimit *pTorqueLimit);
GT_API GTN_RN_GetTorqueLimit(short core,short axis, TTorqueLimit *pTorqueLimit);

GT_API GTN_SetPrfTorque(short core,short axis,short prfTorque);
GT_API GTN_GetAtlTorque(short core,short axis,short *atlTorque);
GT_API GTN_SetPrfTorqueArray(short core,short axis,short *prfTorque,short count);
GT_API GTN_GetAtlTorqueArray(short core,short axis,short *pAtlTorque,short count);
GT_API GTN_GetSafeTorqueOffStatus(short core,int32_t *pSts);

typedef struct TorqueTriggerPrm
{
    short enable;
    short latchType;
    short latchIndex;
    short probeType;
    short probeIndex;
    short windowOnly;
    int32_t firstPosition;
    int32_t lastPosition;
    int32_t continueTime;
    double currentValue;
    double pad2[3];
}TTorqueTriggerPrm;
GT_API GTN_SetTorqueTriggerPrm(short core,short index,TTorqueTriggerPrm *pPrm);
GT_API GTN_GetTorqueTriggerPrm(short core,short index,TTorqueTriggerPrm *pPrm);





/*-----------------------------------------------------------*/
/* GSHD�ջ���������                                          */
/*-----------------------------------------------------------*/
typedef struct
{
    double value;
    double reverse[4];
}TServoPosLoopPidMode0;

typedef union
{
    TServoPosLoopPidMode0 servoPosLoopPidMode0;
}TServoPosLoopPidUnion;

typedef struct
{
    short mode;
    TServoPosLoopPidUnion servoPosLoopPidPrm;
}TServoPosLoopPid;

GT_API GTN_RN_SetServoPosLoopPid(short core,short axis,TServoPosLoopPid *pServoPosLoopPid);
GT_API GTN_RN_GetServoPosLoopPid(short core,short axis,TServoPosLoopPid *pServoPosLoopPid);

typedef struct
{
    double value;
    double reverse[4];
}TServoSpdLoopPidMode0;

typedef union
{
    TServoSpdLoopPidMode0 servoSpdLoopPidMode0;
}TServoSpdLoopPidUnion;

typedef struct
{
    short mode;
    short reverse[3];
    TServoSpdLoopPidUnion servoSpdLoopPidPrm;
}TServoSpdLoopPid;

GT_API GTN_RN_SetServoSpdLoopPid(short core,short axis,TServoSpdLoopPid *pServoSpdLoopPid);
GT_API GTN_RN_GetServoSpdLoopPid(short core,short axis,TServoSpdLoopPid *pServoSpdLoopPid);

#define SERBVO_POS_LOOP                   (0)   // ������λ�û�
#define SERBVO_SPD_LOOP                   (1)   // �������ٶȻ�

GT_API GTN_RN_GetServoPid(short core,short axis,short loop,short mode,void *pServoPid);
GT_API GTN_RN_SetServoPid(short core,short axis,short loop,short mode,void *pServoPid);
GT_API GTN_RN_SetServoPidRatio(short core,short axis,double ratio);
GT_API GTN_RN_GetServoPidRatio(short core,short axis,double *pRatio);


/*-----------------------------------------------------------*/
/* ��ȫģʽ����                                              */
/*-----------------------------------------------------------*/
GT_API GTN_RN_ClearStationSafeModeStatus(short cardIndex,short stationPhyId);
GT_API GTN_RN_IlinkSetSafeModeControl(short cardIndex,short stationPhyId,short modulePhyId,short enable,short clearMode);
GT_API GTN_RN_IlinkClearSafeModeStatus(short cardIndex,short stationPhyId,short modulePhyId);
GT_API GTN_RN_IlinkSetSafeModeOut(short cardIndex,short stationPhyId,short modulePhyId,short type,short index,short *pEnable,double *pValue,short count);
GT_API GTN_RN_GetStationOfflineCount(short cardIndex,int32_t *pStationPhyId,short count,short *pStationOfflineCount);

/*-----------------------------------------------------------*/
//ԭLookAheadEx.h����ǰհ��ع��ܵ�ָ��                      */
/*-----------------------------------------------------------*/
#define LA_AXIS_NUM           (8)
#define LA_WORK_AXIS_NUM      (6)
#define LA_MACHINE_AXIS_NUM   (5)

//��Ĳ�����Ϣ����������ٶȣ����������ٶȣ���������ٶȱ仯�����Ƿ������ٶ�ģʽ
#define AXIS_LIMIT_NONE       (0)       //��������
#define AXIS_LIMIT_MAX_VEL    (1)       //������ٶ�����
#define AXIS_LIMIT_MAX_ACC    (2)       //�������ٶ�����
#define AXIS_LIMIT_MAX_DV     (4)       //������ٶ�����������

#define KIN_MSG_BUFFER_SIZE   32

//�ٶȹ滮ģʽ
enum EVelMode
{
    T_CURVE=0,
    S_CURVE,
    S_CURVE_NEW,                  //���ݼӼ��ٶȡ������ٶȽ���S�����ٶ�ǰհ��2015.11.16
    S_CURVE_SMOOTH,

    VEL_MODE_MAX=0x10000,         //ȷ������Ϊ4Byte
};

//��������ϵ�¹켣�Ƿ������ٶ�ģʽ
enum EWorkLimitMode
{
    WORK_LIMIT_INVALID=0,       //��������ϵ��Ϣ������
    WORK_LIMIT_VALID,           //��������ϵ������Ч

    WORK_LIMIT_MODE_MAX=0x10000,//ȷ������Ϊ4Byte
};

//���õ��ٶȶ������
enum EVelSettingDef
{
    NORMAL_DEF_VEL=0,             //����Ϊ������ϵ������ĺϳ��ٶ�
    NUM_DEF_VEL,                  //��NUMϵͳ�Ĺ�����
    CUT_DEF_VEL,                  //�ٶ�Ϊ�����ٶ�

    VEL_SETTING_DEF_MAX=0x10000,  //ȷ������Ϊ4Byte
};

//���õļ��ٶȶ������
enum EAccSettingDef
{
    NORMAL_DEF_ACC=0,             //���뼴���
    LONG_AXIS_ACC,                //��������ٶ�

    ACC_SETTING_DEF_MAX=0x10000,  //ȷ������Ϊ4Byte
};

//��������
enum EMachineMode
{
    NORMAL_THREE_AXIS=0,      //��׼�������ģʽ
    MULTI_AXES,               //��������ģʽ
    FIVE_AXIS,                //�������ģʽ,������ϵΪ������������ϵΪ��
    FIVE_AXIS_WORK,           //�������ģʽ����������ϵΪ����������ϵΪ��
    ROBOT,                    //������ģʽ��������ϵΪ������������ϵΪ����2014.12.3
    ROBOT_WORK,

    MACHINE_MODE_MAX=0x10000, //ȷ������Ϊ4Byte
};

//ǰհ�����ṹ��
struct TLookAheadParameter
{
    int lookAheadNum;					//ǰհ����
    double time;						//ʱ�䳣��
    double radiusRatio;					//�������Ƶ��ڲ���
    double vMax[LA_AXIS_NUM];			//���������ٶ�
    double aMax[LA_AXIS_NUM];			//����������ٶ�
    double DVMax[LA_AXIS_NUM];			//���������ٶȱ仯������ʱ�䳣���ڣ�
    double scale[LA_AXIS_NUM];			//��������嵱��
    short axisRelation[LA_AXIS_NUM];	//����������ڲ�����Ķ�Ӧ��ϵ
    char machineCfgFileName[128];		//���������ļ���
};

//////////////////////////////////////
typedef struct
{
    short RobotType;
    short reserved1;

    short KinParUse[18];
    double KinPar[18];
    short KinLimitUse[12];
    double KinLimitMin[12];
    double KinLimitMax[12];
    double KinLimitMinShift[12];
    double KinLimitMaxShift[12];

    short AxisUse[8];
    char AxisPosSignSwitch[8];
    double AxisPosOffset[8];

    short CartUnitUse[6];
    char CartPosKCSSignSwitch[6];
    short reserved2[3];
    double CartPosKCSOffset[6];
}RC_KIN_CONFIG;

typedef struct
{
    char Error;
    short ErrorID;
    char Message[129];
}RC_ERROR_INTERFACE;

typedef struct
{
    short ErrorID;
    char Message[129];
    char LogTime[32];
    int32_t InternalID;
}RC_MSG_BUFFER_ELEMENT;

typedef struct
{
    short LastMsgIndex;
    RC_MSG_BUFFER_ELEMENT MsgElement[KIN_MSG_BUFFER_SIZE];
    int32_t LastMsgID;
}RC_MSG_BUFFER;

//����ⷽ��
enum ETransDir
{
    FORWARD_TRANS=0,            //����
    INVERSE_TRANS,              //���

    TRANS_DIR_MAX = 0x10000,	// ȷ������Ϊ4Byte
};

//��ת�᷶Χ����
struct TRotationAxisRange
{
    int primaryAxisRangeOn;              //��һ��ת���޶���Χ�Ƿ���Ч��0������Ч��1����Ч
    int slaveAxisRangeOn;                //�ڶ���ת���޶���Χ�Ƿ���Ч��0������Ч��1����Ч
    double maxPrimaryAngle;              //��һ��ת�����ֵ
    double minPrimaryAngle;              //��һ��ת����Сֵ
    double maxSlaveAngle;                //�ڶ���ת�����ֵ
    double minSlaveAgnle;                //�ڶ���ת����Сֵ
};

//ѡ�����
enum EGroupSelect
{
    Continuous=0,
    Group_1,
    Group_2,
};

enum OptimizeState
{
    OPT_OFF=0,
    OPT_ON,
};

enum OptimizeMethod
{
    NO_OPT=0,
    OPT_BLENDING,
    OPT_CIRCLEFITTING,
    OPT_CUBICSPLINE,
    OPT_BSPLINE,
};

enum ErrorID
{
    INIT_ERROR=1,                           //û�н��в�����ʼ��
    PASSWORD_ERROR,                         //����������ڹ̸��˶�����ƽ̨������
    INDATA_ERROR,                           //�������ݴ��󣨼��Բ�������Ƿ���ȷ��
    PRE_PROCESS_ERROR,
    TOOL_RADIUS_COMPENSATE_ERROR_INOUT,     //���߰뾶�������󣺽���/����������������Բ��
    TOOL_RADIUS_COMPENSATE_ERROR_NOCROSS,   //���߰뾶�����������ݲ��������޷����㽻��
    USERDATA_ERROR,
};

//�켣�Ż������ṹ��
typedef struct OptimizeParamUser
{
    OptimizeState usePathOptimize;  //�Ƿ�ʹ��·���Ż���OPT_OFF:��ʹ��	OPT_ON:ʹ��

    float tolerance;                //����(suggest: rough:0.1, pre-finish:0.05, finish:0.01)

    OptimizeMethod optimizeMethod;  //ѡ�������Ż���ʽ

    OptimizeState keepLargeArc;     //�Ƿ�����Բ����OPT_OFF���������� OPT_ON������

    float blendingMinError;         //blending����С�趨���

    float blendingMaxAngle;         //blending�����Ƕ����ƣ������߶������Ƕȴ��ڸýǶ�ʱ������blending����λ���ȣ�

}TOptimizeParamUser;

struct TErrorInfo
{
    ErrorID errorID;                //�����(INIT_ERROR:δ��ʼ��������PRE_PROCESS_ERROR:Ԥ����ģ�����
    //TOOL_RADIUS_COMPENSATE_ERROR:���߰뾶��������)
    int32_t errorRowNum;            //�����к�
};

struct TPreStartPos
{
    double Pos[LA_AXIS_NUM];
};

enum EMachineType
{
    //W:�����࣬T�����߲࣬L��45��
    //˫ת̨
    MT_RW_C_ON_B=0,//B Ϊ��һ��ת�ᣬC Ϊ�ڶ���ת��
    MT_RW_B_ON_A,	//A Ϊ��һ��ת�ᣬB Ϊ�ڶ���ת��
    MT_RW_A_ON_B,	//B Ϊ��һ��ת�ᣬA Ϊ�ڶ���ת��
    MT_RW_C_ON_A,	//A Ϊ��һ��ת�ᣬC Ϊ�ڶ���ת��
    //˫��ͷ
    MT_DT_B_ON_A,	//A Ϊ��һ��ת�ᣬB Ϊ�ڶ���ת��
    MT_DT_A_ON_B,	//B Ϊ��һ��ת�ᣬA Ϊ�ڶ���ת��
    MT_DT_A_ON_C,	//C Ϊ��һ��ת�ᣬA Ϊ�ڶ���ת��
    MT_DT_B_ON_C,	//C Ϊ��һ��ת�ᣬB Ϊ�ڶ���ת��
    //ת̨��ͷ�����߲�Ϊ��һ��ת�ᣬ������Ϊ�ڶ���ת��
    MT_T_A_W_B,	//A Ϊ��һ��ת�ᣬB Ϊ�ڶ���ת��
    MT_T_B_W_A,	//B Ϊ��һ��ת�ᣬA Ϊ�ڶ���ת��
    MT_T_A_W_C,	//A Ϊ��һ��ת�ᣬC Ϊ�ڶ���ת��
    MT_T_B_W_C,	//B Ϊ��һ��ת�ᣬC Ϊ�ڶ���ת��
};
struct TMachCfgInfo
{
    EMachineType machineType;            //��������
    short reserve1[2];                   //��������
    double primaryAxisPoint[3];          //��һ��ת��������MCS������
    double slaveAxisPoint[3];            //�ڶ���ת��������MCS������
    double toolLocationPoint[3];         //��������ϵ������MCS������
    short dirMode;                       //��������ģʽ
    short reserve2[2];                   //��������
    short dir[5];                        //���᷽��
    double axisVector[5][3];             //�������߷���
};

struct TPos
{
    double machinePos[LA_MACHINE_AXIS_NUM];
    double workPos[LA_WORK_AXIS_NUM];
};

GT_API GTN_SetupLookAheadCrd(short core,short crd,EMachineMode machineMode);
GT_API GTN_SetAxisFollowModeLa(short core,short crd,int *pFollowMode);
GT_API GTN_SetMinEvenVelTimeLa(short core,short crd, double evenTime);
GT_API GTN_SetMinDccAngle(short core,short crd,double dccAngle);
GT_API GTN_SetMinDccAngleLa(short core,short crd,double dccAngle);
GT_API GTN_SetVelDefineModeLa(short core,short crd,EVelSettingDef velDefMode);
GT_API GTN_SetAccDefineModeLa(short core,short crd,EAccSettingDef accDefMode);
GT_API GTN_SetMaxOverrideLa(short core,short crd,double maxSynVelRatio);
GT_API GTN_SetAxisLimitModeLa(short core,short crd,int *pAxisLimitMode);
GT_API GTN_SetWorkLimitModeLa(short core,short crd,EWorkLimitMode workLimitMode);
GT_API GTN_SetAxisVelValidModeLa(short core,short crd,int velValidAxis);
GT_API GTN_SetAngleCoefTableLa(short core,short crd,short count,double *pAngle,double *pCoef);
GT_API GTN_SetVelModeLa(short core,short crd,EVelMode velMode);
GT_API GTN_SetVelSmoothModeLa(short core,short crd,short smoothMode);
GT_API GTN_SetVelLimitAngleThresholdLa(short core,short crd,double angleThreshold);
GT_API GTN_SetRadiusRatioTableLa(short core,short crd,short count,double *pRadius,double *pRatio);
GT_API GTN_SetCurveVelLimitModeLa(short core,short crd,short mode);
GT_API GTN_PrintLACmdLa(short core,short crd,int printFlag, int clearFile);
GT_API GTN_UpdateMachineBuildingFileLa(short core,short crd, int update);
GT_API GTN_InitialMachineBuilding(short core,short crd, char *pMachineCfgFileName,double *machineCoordCenter, double *workCoordCenter, double toolLength);
GT_API GTN_InitialMachineBuildingEx(short core,short crd, char *pMachineCfgFileName,double *machineCoordCenter, double *workCoordCenter, double toolLength);
GT_API GTN_InitialMachineBuildingPara(short core,short crd, TMachCfgInfo *pMachCfgInfo,double *machineCoordCenter, double *workCoordCenter, double toolLength);
GT_API GTN_GetLookAheadParaEx(short core,short crd,short fifo,TLookAheadParameter *pLookAheadPrm,short *pMotionMode);

// ����
GT_API GTN_CrdRTCPOn(short core,short crd,short fifo=0);
GT_API GTN_CrdRTCPOff(short core,short crd,short fifo=0);
GT_API GTN_SetNonlinearErrorControl(short core,short crd, int enable, double nonlinearError);
GT_API GTN_EnableDiscreateArc(short core,short crd,short enable,double arcError);
GT_API GTN_MachineForwardTrans(short core,short crd, double *pMachinePos, double *pWorkPos);
GT_API GTN_MachineRTCPTrans(short core,short crd, double *pInputPos, double *pMachinePos, double *pWorkPos);
GT_API GTN_SetCompToolLength(short core,short crd, double compToolLength);
GT_API GTN_SetCompWorkCoordOffset(short core,short crd, double *pCompWorkOffset);
GT_API GTN_UpdateMachineBuildingFile(short core,short crd, int update);
GT_API GTN_SetRotationAxisRange(short core,short crd, TRotationAxisRange *pRotationAxisRange);
GT_API GTN_SetInverseSolutionSelectPara(short core,short crd, EGroupSelect groupSelect, int priorAxisSet);
GT_API GTN_SetPowerOffDo(short core,short mode,short doIndex,short doValue);
GT_API GTN_MachineTransformation(short core,short crd, int posType, double *pPrePos, double *pPos, int *pPosNum, TPos **pReturnPos);
GT_API GTN_SetStartPointProcessMode(short core,short crd,short enable, double z,short fifo);
GT_API GTN_SetWorkCrdLaserFollowMode(short core,short crd,short enbale,short fifo,short chn);

GT_API GTN_SetAxisVelValidCompModeLa(short core,short crd, int enable, int *pCompAxis);
GT_API GTN_SetFollowAxisProcessModeLa(short core,short crd,int AxisFollowMode);
GT_API GTN_SetCmdVelLimitLa(short core,short crd, int enable, int n1, int n2, int mode);
GT_API GTN_InitLookAheadEx(short core,short crd,TLookAheadParameter *pLookAheadParameter,short fifo, short motionMode=0,TPreStartPos *pPreStartPos=NULL);
GT_API GTN_InitLookAheadPara(short core,short crd,int32_t lookAheadNum,double time,double radiusRatio,double scale,short fifo);
GT_API GTN_SetFollowAxisParaLa(short core,short crd,int *pAxisLimitMode,double *pVmax,double *pAmax,double *pDVmax);
GT_API GTN_SetFollowAxisParaLaPro(short core,short crd,int *pAxisLimitMode,double *pVmax,double *pAmax,double *pDVmax,short count);

GT_API GTN_SetBlendingParaLa(short core,short crd, short paraType, double para, double minAngle, double maxAngle);


GT_API GTN_GetLookAheadSegCountEx(short core,short crd,int32_t *pSegCount,short fifo=0);
GT_API GTN_GetMotionTimeEx(short core,short crd,double *pTime,short fifo);
GT_API GTN_SetUserSegNumEx(short core,short crd,int32_t segNum,short fifo);
GT_API GTN_CrdDataEx(short core,short crd,TCrdData *pCrdData,short fifo=0);

GT_API GTN_LnXYEx(short core,short crd,double x,double y,double synVel,double synAcc,int32_t segNum,short override2,short fifo=0);
GT_API GTN_LnXYG0Ex(short core,short crd,double x,double y,double synVel,double synAcc,int32_t segNum,short override2,short fifo=0);
GT_API GTN_LnXYZEx(short core,short crd,double x,double y,double z,double synVel,double synAcc,int32_t segNum,short override2,short fifo=0);
GT_API GTN_LnXYZG0Ex(short core,short crd,double x,double y,double z,double synVel,double synAcc,int32_t segNum,short override2,short fifo=0);
GT_API GTN_LnXYZAEx(short core,short crd,double x,double y,double z,double a,double synVel,double synAcc,int32_t segNum,short override2,short fifo=0);
GT_API GTN_LnXYZAG0Ex(short core,short crd,double x,double y,double z,double a,double synVel,double synAcc,int32_t segNum,short override2,short fifo=0);
GT_API GTN_LnXYZACEx(short core,short crd,double *pPos,short posMask,double synVel,double synAcc,int32_t segNum,short override2,short fifo);
GT_API GTN_LnXYZACG0Ex(short core,short crd,double *pPos,short posMask,double synVel,double synAcc,int32_t segNum,short override2,short fifo);
GT_API GTN_LnXYZACUVWEx(short core,short crd,double *pPos,short posMask,double synVel,double synAcc,int32_t segNum,short override2,short fifo);
GT_API GTN_LnXYZACUVWG0Ex(short core,short crd,double *pPos,short posMask,double synVel,double synAcc,int32_t segNum,short override2,short fifo);
GT_API GTN_ArcXYREx(short core,short crd,double x,double y,double radius,short circleDir,double synVel,double synAcc,int32_t segNum,short override2,short fifo=0);
GT_API GTN_ArcYZREx(short core,short crd,double y,double z,double radius,short circleDir,double synVel,double synAcc,int32_t segNum,short override2,short fifo=0);
GT_API GTN_ArcZXREx(short core,short crd,double z,double x,double radius,short circleDir,double synVel,double synAcc,int32_t segNum,short override2,short fifo=0);
GT_API GTN_ArcXYCEx(short core,short crd,double x,double y,double xCenter,double yCenter,short circleDir,double synVel,double synAcc,int32_t segNum,short override2,short fifo=0);
GT_API GTN_ArcYZCEx(short core,short crd,double y,double z,double yCenter,double zCenter,short circleDir,double synVel,double synAcc,int32_t segNum,short override2,short fifo=0);
GT_API GTN_ArcZXCEx(short core,short crd,double z,double x,double zCenter,double xCenter,short circleDir,double synVel,double synAcc,int32_t segNum,short override2,short fifo=0);
GT_API GTN_ArcXYZEx(short core,short crd,double x,double y,double z,double interX,double interY,double interZ,double synVel,double synAcc,int32_t segNum,short override2,short fifo=0);
GT_API GTN_ArcXYRACEx(short core,short crd,double x,double y,double a,double c,double radius,short circleDir,double synVel,double synAcc,int32_t segNum,short override2,short fifo=0);
GT_API GTN_ArcXYCACEx(short core,short crd,double x,double y,double a,double c,double xCenter,double yCenter,short circleDir,double synVel,double synAcc,int32_t segNum,short override2,short fifo=0);
GT_API GTN_ArcXYZACEx(short core,short crd,double x,double y,double z,double a,double c,double interX,double interY,double interZ,double interA,double interC,double synVel,double synAcc,int32_t segNum,short override2,short fifo=0);
GT_API GTN_HelixXYRZEx(short core,short crd,double x,double y,double z,double radius,short circleDir,double synVel,double synAcc,int32_t segNum,short override2,short fifo=0);
GT_API GTN_HelixXYCZEx(short core,short crd,double x,double y,double z,double xCenter,double yCenter,short circleDir,double synVel,double synAcc,int32_t segNum,short override2,short fifo=0);
GT_API GTN_BufDelayEx(short core,short crd,unsigned short delayTime,short fifo=0);
GT_API GTN_BufGearEx(short core,short crd,short gearAxis,double deltaPos,short fifo=0);
GT_API GTN_BufMoveEx(short core,short crd,short moveAxis,double pos,double vel,double acc,short modal,short fifo=0);
GT_API GTN_BufMoveSpEx(short core,short crd,short moveAxis,double pos,double vel,short smoothTime,short modal,short enableRatio,short fifo);
GT_API GTN_BufMoveSpSetPrmEx(short core,short crd,short moveAxis,double acc,double dec,double velMax,short fifo);
GT_API GTN_BufIOEx(short core,short crd,unsigned short doType,unsigned short doMask,unsigned short doValue,short fifo=0);
GT_API GTN_BufEnableDoBitPulseEx(short core,short crd,short doType,short doIndex,unsigned short highLevelTime,unsigned short lowLevelTime,int32_t pulseNum,short firstLevel,short fifo);
GT_API GTN_BufDisableDoBitPulseEx(short core,short crd,short doType,short doIndex,short fifo);
GT_API GTN_BufDAEx(short core,short crd,short chn,short daValue,short fifo=0);
GT_API GTN_BufAuDAEx(short core,short crd,short chn,short daValue,short fifo=0);

GT_API GTN_BufFollowMasterEx(short core,short crd,TBufFollowMaster *pBufFollowMaster,short fifo=0);
GT_API GTN_BufFollowEventCrossEx(short core,short crd,TBufFollowEventCross *pEventCross,short fifo=0);
GT_API GTN_BufFollowEventTriggerEx(short core,short crd,TBufFollowEventTrigger *pEventTrigger,short fifo=0);
GT_API GTN_BufFollowStartEx(short core,short crd,int32_t masterSegment,int32_t slaveSegment,int32_t masterFrameWidth,short fifo=0);
GT_API GTN_BufFollowNextEx(short core,short crd,int32_t width,short fifo=0);
GT_API GTN_BufFollowReturnEx(short core,short crd,double vel,double acc,short smoothPercent,short fifo=0);


// Smart Cutter
typedef struct
{
    short x;						// X���Ӧ�Ĺ滮��
    short y;						// Y���Ӧ�Ĺ滮��
    short c;						// C���Ӧ�Ĺ滮��

    short tableRadiusIndex;			// �뾶����������
    short tableAngleIndex;			// C�Ჹ��������

    short directionReverse;			// Ĭ�Ϲ滮λ������ʱ�Ƕ�Ҳ�������

    int32_t offset;		            // C����ת�Ƕ�Ϊ0ʱ�Ĺ滮λ��
    int32_t resolution;				// C��ÿת������

    short adcIndex;					// ADC����
    double adcThreshold;			// ADC������������ֵ
} TSmartCutterPrm;

typedef struct
{
    short enable;
    short execute;
    double radiusValue;
    double angleValue;
} TSmartCutterInfo;

GT_API GTN_SmartCutterOn(short core,short index);
GT_API GTN_SmartCutterOff(short core,short index);
GT_API GTN_SetSmartCutterPrm(short core,short index,TSmartCutterPrm *pPrm);
GT_API GTN_GetSmartCutterPrm(short core,short index,TSmartCutterPrm *pPrm);
GT_API GTN_BufSmartCutterOn(short core,short crd,short smartCutterIndex,short fifo);
GT_API GTN_BufSmartCutterOff(short core,short crd,short smartCutterIndex,short fifo);
GT_API GTN_BufSmartCutterOnEx(short core,short crd,short index,short fifo=0);
GT_API GTN_BufSmartCutterOffEx(short core,short crd,short index,short fifo=0);
GT_API GTN_GetSmartCutterInfo(short core,short index,TSmartCutterInfo *pInfo);
GT_API GTN_SetSmartCutterValue(short core,short index,double radiusValue,double angleValue);
GT_API GTN_SmartCutterStart(short core,short index);


GT_API GTN_BufWaitDiEx(short core,short crd, short diType, unsigned short diIndex,unsigned short level, short continueTime, int32_t overTime, short flagMode,int32_t segNum, short fifo);
GT_API GTN_BufWaitLongVarEx(short core,short crd, short index,int32_t value,int32_t overTime,short flagMode,int32_t segNum,short fifo);
GT_API GTN_BufWaitWatchVarEx(short core,short crd,TWatchCondition *pWaitCondition,TWaitTimeout *pWaitTimeout,int32_t segNum,short fifo);
GT_API GTN_BufSetWaitLongtVarEx(short core,short crd,short index,int32_t value,short fifo);

GT_API GTN_BufDoBitEx(short core,short crd,unsigned short doType,unsigned short index,short value,short fifo);
GT_API GTN_BufDoBitDelayEx(short core,short crd,unsigned short doType,unsigned short index,short value,int32_t delayTime,short fifo);
GT_API GTN_BufSetOverrideEx(short core,short crd,double synVelRatio,short mode,short fifo);
GT_API GTN_BufStopPosEx(short core,short crd,short profile,TStopPos *pStopPos,short modal,short fifo);
GT_API GTN_BufSetSoftLimitEx(short core,short crd,short axis,double positive,double negative,short fifo);

// ������λ�ñȽ�
GT_API GTN_BufPosComparePsoPrm(short core,short crd,short index,TPosComparePsoPrm *pPrm,short fifo);
GT_API GTN_BufPosComparePsoPrmPro(short core,short crd,short index,TPosComparePsoPrmPro *pPrmPro,short fifo);
GT_API GTN_BufPosCompareStart(short core,short crd,short fifo,short index);
GT_API GTN_BufPosCompareStop(short core,short crd,short fifo,short index);

GT_API GTN_BufPosComparePsoPrmEx(short core,short crd,short index,TPosComparePsoPrm *pPrm,short fifo);
GT_API GTN_BufPosComparePsoPrmProEx(short core,short crd,short index,TPosComparePsoPrmPro *pPrmPro,short fifo);
GT_API GTN_BufPosCompareStartEx(short core,short crd,short fifo,short index);
GT_API GTN_BufPosCompareStopEx(short core,short crd,short fifo,short index);

GT_API GTN_BufPosComparePulse(short core,short crd,short index,short outputMode,short level,unsigned short outputPulseWidth,short fifo);
GT_API GTN_BufPosComparePulseEx(short core,short crd,short index,short outputMode,short level,unsigned short outputPulseWidth,short fifo);

GT_API GTN_BufPosCompareMultiPulse(short core,short crd,short index,TPosCompareMultiPulse *pPosComparePulse,short fifo);
GT_API GTN_BufPosCompareMultiPulseEx(short core,short crd,short index,TPosCompareMultiPulse *pPosComparePulse,short fifo);

GT_API GTN_BufPsoStart(short core,short crd,short fifo,short index,int32_t x,int32_t y);
GT_API GTN_BufPsoStop(short core,short crd,short fifo,short index,int32_t x,int32_t y);

GT_API GTN_BufPsoStartEx(short core,short crd,short fifo,short index,double x,double y);
GT_API GTN_BufPsoStopEx(short core,short crd,short fifo,short index,double x,double y);

/*-----------------------------------------------------------*/
/* ѹ������                                            */
/*-----------------------------------------------------------*/
typedef struct
{
    double kp;
    double ki;
    double kd;
    double integralLimit;	//���ּ���
    double derivativeLimit;	//΢�ּ���
    double limit;			//�������ƣ������ѹ��
    double pad1[4];
}TAxisPressPid;

#define PRESS_COMPENSATE_MODE_LINEAR                       (0)                           // ���Բ���
#define PRESS_COMPENSATE_MODE_TABLE	                       (1)                           // �������
#define PRESS_COMPENSATE_MODE_REGION_LEARN                 (2)                           // ��������ѧϰ����

typedef struct
{
    short enable;		           //�Ƿ�ʹ�ܣ�0-�رգ�1-ʹ��
    short type;			           //�������ͣ���ѹ������ģ������
    short dimension;	           //���������ά�ȣ����3ά
    short index[3];		           //���������,DAC��1��ʼ��ECAT IOģ��վ�Ŵ�0��ʼ
    short subIndex[3];             //�������������,DAC�ò�����Ч��ECAT IOģ���IOMAP��0��ʼ
    short mode;			           //ģʽ�����Ի��ǲ��
    short revolveAxis;             //����������ת�Ƕȵ����
    short regionAxisIndex;         //��������������Ч�Ĳο���
    short relatedMasterIndex;      //�涯���������
    short pad1[3];
    double target;			       //Ŀ�������ѹ
    double thredshold;		       //thredshold��ʲôʱ��ʼ����
    double deadZone;		       //���������ѹ�������ڲ�����
    double factor;			       //����λ�Ƶ�ת��ϵ��
    double revolveOffset;	       //��ʼ��ת����������Ĭ�Ϻϳɷ����ingdex[0]�ķ����غ�
    double revolveScale;	       //��ת���һȦ������
    TAxisPressPid pid;
    int32_t compPosMaxP;           //�������λ������[N,P]�Ķ˵�P
    int32_t compPosMaxN;           //�������λ������[N,P]�Ķ˵�N
    double k;	                   //�������˲�ϵ�� 0-1 ��ֵԽ���˲�Խǿ
    double pad2[4];
    int32_t activeRegionP;          //����������Ч�Ĺ滮λ������[N,P]�Ķ˵�P
    int32_t activeRegionN;          //����������Ч�Ĺ滮λ������[N,P]�Ķ˵�N
    int32_t activeRegionInterval;   //����������Ч�Ĺ滮λ�������ڵ���ѧϰ�������modeΪ��ѧϰPRESS_COMPENSATE_MODE_REGION_LEARNʱ��Ч
    int32_t relatedMasterEven;      //�涯����ı���
    int32_t relatedSlaveEven;       //�涯����ı���
    int32_t pad3[3];
} TAxisPressCompensate;

GT_API GTN_SetAxisPressCompensate(short core,short axis,TAxisPressCompensate *pPressComp);
GT_API GTN_GetAxisPressCompensate(short core,short axis,TAxisPressCompensate *pPressComp);
GT_API GTN_SetAxisPressCompensateTable(short core,short axis,short index,int32_t count,double *pPressData,double *pPosData);
GT_API GTN_SelectAxisPressCompensateTable(short core,short axis,short index);

typedef struct
{
    short type;			      //�������ͣ���ѹ������ģ������
    short dimension;	      //���������ά�ȣ����3ά
    short index[3];		      //���������,DAC��1��ʼ��ECAT IOģ��վ�Ŵ�0��ʼ
    short subIndex[3];        //�������������,DAC�ò�����Ч��ECAT IOģ���IOMAP��0��ʼ

    double targetMax;	      //�궨�������ֵ���ﵽ�򳬹���ֵʱ�궨����
    double targetMin;	      //�궨������Сֵ���ﵽ��С�ڸ�ֵʱ�궨����
    double factor;		      //����λ�Ƶ�ת��ϵ��������ʱ����0,��ȡ״̬ʱ�õ��궨ֵ��

    int32_t fixRegionP;        //�궨�滮λ������[N,P]�Ķ˵�P������λ�õ����λ��
    int32_t fixRegionN;        //�궨�滮λ������[N,P]�Ķ˵�N������λ�õ����λ��
    int32_t fixRegionInterval; //�궨�滮λ�������ڵı궨���

    int32_t tmp[16];
} TAxisPressCompensateFixFactor;

GT_API GTN_StartAxisPressCompensateFixFactor(short core,short axis,TAxisPressCompensateFixFactor *pPressComp);
GT_API GTN_GetAxisPressCompensateFixFactorStatus(short core,short axis,short *pFixFactorSts,TAxisPressCompensateFixFactor *pPressComp);

typedef struct
{
    short type;			 //�������ͣ���ѹ������ģ������
    short dimension;     //���������ά�ȣ����3ά
    short index[3];		 //���������,DAC��1��ʼ��ECAT IOģ��վ�Ŵ�0��ʼ
    short subIndex[3];   //�������������,DAC�ò�����Ч��ECAT IOģ���IOMAP��0��ʼ

    double target;		 //Ŀ�������ѹ
    double factor;		 //����λ�Ƶ�ת��ϵ��
    TAxisPressPid pid;

    int32_t fixPosLimitP;  //�궨λ������[N,P]�Ķ˵�P
    int32_t fixPosLimitN;  //�궨����λ������[N,P]�Ķ˵�N
    double thredshold;   //thredshold��ʲôʱ��ʼ����
    double deadZone;	 //���������ѹ�������ڲ�����

    //�������ڲ�����������ʹ�ã������û��ӿ�û�иò���
    double Knp;			 //ѹ����ȫ������
    double K1;			 //ȫ���������ϵ��1
    double K2;			 //ȫ���������ϵ��2
    double K3;			 //ȫ���������ϵ��3
    double Krise;		 //����ϵ��
    double Kpeak;		 //��ֵϵ��
    double Tset;		 //Ŀ����Ӧʱ��
    double Td;			 //������Ӧʱ��

    double tmp[8];
} TAxisPressCompensateFixPid;

GT_API GTN_StartAxisPressCompensateFixPid(short core,short axis,TAxisPressCompensateFixPid *pPressComp);
GT_API GTN_GetAxisPressCompensateFixPidStatus(short core,short axis,short *pFixPidSts,TAxisPressCompensateFixPid *pPressComp);

GT_API GTN_AxisPressCompensateEnable(short core,short axis,short enable,double deadZone,double factor,TListInfo *pListInfo);
GT_API GTN_SetAxisPressCompensateTarget(short core,short axis,double target,double thredshold,TListInfo *pListInfo);

GT_API GTN_BufAxisPressCompensatePrmEx(short core,short crd,short axis,double target,double thredshold,short fifo=0);
GT_API GTN_BufAxisPressCompensateEx(short core,short crd,short axis,short enable,double deadZone,double factor,short fifo=0);

GT_API GTN_SetCrdUserDataEndVelLa(short core,short crd, short crdUserDataType,double endVel);

/*-----------------------------------------------------------*/
/* PVTģʽ�������������                                      */
/*-----------------------------------------------------------*/
#define PVT_OPERATION_TYPE_LASER_ON					(2)
#define PVT_OPERATION_TYPE_BUF_DA					(4)
#define PVT_OPERATION_TYPE_LASER_CMD				(5)
#define PVT_OPERATION_TYPE_LASER_FOLLOW_RATIO		(6)
#define PVT_OPERATION_TYPE_LASER_FOLLOW_MODE		(25)
#define PVT_OPERATION_TYPE_LASER_FOLLOW_OFF			(26)
#define PVT_OPERATION_TYPE_BUF_DO_BIT				(94)
#define CRD_OPERATION_TYPE_BUF_POS_COMPARE_START 	(90)
#define CRD_OPERATION_TYPE_BUF_POS_COMPARE_STOP 	(91)

typedef struct
{
    short doType;
    short index;
    short value;
}TPVTDoBit;

typedef struct
{
    short chn;
    short daValue;
}TPVTDA;

typedef struct
{
    short chn;
    short enable;
}TPVTLaserSwitch;

typedef struct
{
    short chn;
    double power;
}TPVTLaserPrfCmd;

typedef struct
{
    short  chn;
    double ratio;
    double minPower;
    double maxPower;
}TPVTLaserFollowRatio;

typedef struct
{
    short  chn;
}TPVTLaserFollowOff;

typedef struct
{
    short  chn;
    short  source;
    double startPower;
}TPVTLaserFollowMode;


/*-----------------------------------------------------------*/
/* ����ֵ������	                                            */
/*-----------------------------------------------------------*/
GT_API GTN_RN_GetAbsEncPosEx(short core,short encoder, int64_t *pEncPos);
GT_API GTN_RN_SetEncMultiLinesEx(short core, short encoder,uint64_t multiLines);

GT_API GTN_RN_SetEncMultiLines(short core, short stationId, short axis,uint64_t multiLines);
GT_API GTN_SetAbsEncMultiTurnRange(short cardIndex,short encoder,double range);
GT_API GTN_ReadAbsEncPos(short core,short encoder,double *pPos);
GT_API GTN_RN_GetAbsEncMultiAndSinglePos(short cardIndex,short stationPhyId,short encoder,uint32_t *pMultiPos,uint32_t *pSinglePos);
/*-----------------------------------------------------------*/
/* ���ܹ���	                                            		*/
/*-----------------------------------------------------------*/
typedef struct
{
    char uuid[32];   // ԭʼ��Կ
    char mcInf[32];  //
}TEncryptConfigPrm;

typedef struct
{
    char keyValue[32];      // ��Կ
    char data[32];          // ��ȡ���Ļ���д��ȥ���µ�����
}TEncryptData;

typedef struct
{
    short type;                     // оƬ����
    short userKeySlotOffset;        // ��Կ��ƫ��
    short userDataSlotOffset;       // ���ݲ�ƫ��
    short cardType;                 // ���ƿ�����
    short reverse1[8];
}TEncryptChipInf;

typedef struct
{
    char sn[9];                     // оƬ���к�
    char random[32];                // ���ص������
    TEncryptChipInf chipInf;        // оƬ������Ϣ
}TEncryptAuxInf;

typedef struct
{
    char data[32];                  // ��ȡ���ļ�������
    char hMac[32];                  //
}TEncryptDataPro;

GT_API GTN_SetEncryptConfig(short core,TEncryptConfigPrm *pConfigPrm, short *pSts);
// �����汾���ܹ���
//  ���ܶ�д����
GT_API GTN_GetEncryptData(short core,TEncryptData *pReadPrm);
GT_API GTN_SetEncryptData(short core,TEncryptData *pWritePrm);
// �����汾�����Ž��ܺ������û����ݶ�ȡ�����ġ����õ���Կ����
GT_API GTN_GetEncryptAuxInf(short core,TEncryptAuxInf *pAuxInf,short *pSts);
GT_API GTN_SetEncryptDataPro(short core,short slotIndex,short block,TEncryptDataPro *pWritePrm,short *pSts);
GT_API GTN_GetEncryptDataPro(short core,short slotIndex,short block,TEncryptDataPro *pReadPrm,short *pSts);

// �����汾��������Կ
typedef struct
{
    char oldKey[32];         // ԭʼ��Կ
    char newKey[32];         // ����Կ
}TEncryptKey;

GT_API GTN_UpdateEncryptKey(short core,TEncryptKey *pKeyInf,short *pSts);

/*-----------------------------------------------------------*/
/* press                                                     */
/*-----------------------------------------------------------*/
#define LOOP_MODE_POSITION               (0)
#define LOOP_MODE_PRESS                  (1)
#define LOOP_MODE_NONE                   (2)

#define LIMIT_TYPE_PRESS                (7)
#define LIMIT_TYPE_TORQUE               (8)

#define MC_PRESS                        (600)
#define MC_TORQUE                       (601)

typedef struct
{
    short loopMode;
    short pressProfileMode;
    short pad[2];
} TLoopMode;

typedef struct
{
    short active;            // ����ʹ��
    short pad1;
    int32_t scale;          // ������������1ţ��N��ת��������ĵ�����
    short linkAxis;         // ѹ���滮�����Ǹ����������
    short pad2[3];
} TPressPrm;

typedef struct
{
    double acc;             // ���ؼ��ٶ�
    double dec;             // ���ؼ��ٶ�
    double pressStart;      // ��������
    short  smoothTime;      // ƽ��ʱ��
    short pad[3];
} TPressTargetPrm;

typedef struct
{
    double pressTarget;     // Ŀ��ѹ��
    int32_t pressTime;      // ����ʱ�� ms��λ
    int32_t holdTime;       // ����ʱ��
} TPressArrayData;

typedef struct
{
    short count;
    short pad1[3];
    TPressArrayData buffer[4];
    short exit;             // �滮��ɺ��Ƿ��л���λ�ñջ�ģʽ
    short pad2[3];
} TPressArray;

typedef struct
{
    double kp;
    double ki;
    double kd;
    double kvff;
    double kaff;
    int32_t integralLimit;
    int32_t derivativeLimit;
    short limitMax;
    short limitMin;
    short pad[2];
} TPressPid;

typedef struct
{
    short limit1;
    short limit2;
    short time;
    short triggerCondition;        // ѹ����ͣ����������PRESS_GREATER_THAN_LIMIT,PRESS_LESS_THAN_LIMIT,
    short loopMode;                // �������л���ʲôģʽ��ʲô�滮��
    short pressProfileMode;
    short pad[2];
} TPressAutoSwitchPrm;

typedef struct
{
    int32_t distance;              // ���˾���
    short pad[2];
    double vel;                    // ���ٶ�
    double acc;                    // ���˼��ٶ�
} TStopOffset;

GT_API GTN_SetLoopMode(short core,short axis,TLoopMode *pMode);
GT_API GTN_GetLoopMode(short core,short axis,TLoopMode *pMode);
GT_API GTN_SetPressPrm(short core,short pressAxis,TPressPrm *pPressPrm);
GT_API GTN_GetPressPrm(short core,short pressAxis,TPressPrm *pPressPrm);
GT_API GTN_SetPressTarget(short core,short pressProfile,double value,TPressTargetPrm *pPressTargetPrm);
GT_API GTN_GetPressTarget(short core,short pressProfile,double *pValue,TPressTargetPrm *pPressTargetPrm);
GT_API GTN_SetPressArray(short core,short pressProfile,TPressArray *pPressArray);
GT_API GTN_GetPressArray(short core,short pressProfile,TPressArray *pPressArray);
GT_API GTN_SetPressPid(short core,short pressControl,TPressPid *pPid);
GT_API GTN_GetPressPid(short core,short pressControl,TPressPid *pPid);
GT_API GTN_GetPrfPress(short core,short pressProfile,double *pValue,double *pValueFilter);
GT_API GTN_GetAtlPress(short core,short pressAxis,double *pValue);
GT_API GTN_GetPressStatus(short core,short pressAxis,int32_t *pStatus);
GT_API GTN_SetPressAutoSwitchPrm(short core,short pressAxis,TPressAutoSwitchPrm *pPrm);
GT_API GTN_GetPressAutoSwitchPrm(short core,short pressAxis,TPressAutoSwitchPrm *pPrm);
GT_API GTN_PressAutoSwitchEnable(short core,short pressAxis,short enable);
GT_API GTN_GetPressFeedbackType(short core,short pressAxis,short *pFbType,short *pFbIndex);
GT_API GTN_SetPressFeedbackType(short core,short pressAxis,short fbType,short fbIndex);
GT_API GTN_SetPrfPress(short core,short pressProfile,double prfPressValue);
GT_API GTN_SetStopOffset(short core,short axis,short mode,TStopOffset *pStopOffset);
GT_API GTN_GetStopOffset(short core,short axis,short mode,TStopOffset *pStopOffset);
GT_API GTN_SetPressRange(short core,short pressAxis,short centerSynch,int32_t range);
GT_API GTN_GetPressRange(short core,short pressAxis,int32_t *pCenterPos,int32_t *pRange);
GT_API GTN_SetPressCross(short core,short pressAxis,short dir,int32_t pos);
GT_API GTN_GetPressCross(short core,short pressAxis,short *pDir,int32_t *pPos);
GT_API GTN_SetPressTrigger(short core,short pressAxis,short pressThread,short triggerCondition);
GT_API GTN_GetPressTrigger(short core,short pressAxis,short *pPressThread,short *pTriggerCondition);
GT_API GTN_PressTriggerOn(short core,short pressAxis);
GT_API GTN_PressTriggerOff(short core,short pressAxis);
GT_API GTN_GetPressTriggeredPos(short core,short pressAxis,short *pEnable,double *pCntPos,short *pTriggeredPress);

/*-----------------------------------------------------------*/
/* Command                                                  */
/*-----------------------------------------------------------*/
GT_API GTN_GetCommandExecuteTime(short core,short mode,double *pTime);
GT_API GTN_ClearCommandExecuteTime(short core,short mode);
GT_API GTN_GetCmdCount(short core,short crd,short *pResult,short fifo);
GT_API GTN_InitCmdExExtern(short core,short cmd);
GT_API GTN_GetFloat64ExExtern(short core,double *pData);
GT_API GTN_AddFloat64ExExtern(short core,double data);
GT_API GTN_SendCommandExExtern(short core);


typedef struct
{
    short master[2];
    short masterValueSource[2];
    int32_t gearRatioNumerator[2];
    int32_t gearRatioDenominator[2];
} TCombineAxes;

typedef struct
{
    short enable;
    double slavePos;
    double slaveVel;
} TCombineAxesStatus;

GT_API GTN_SetCombineAxes(short core,short index,TCombineAxes *pCombineAxes);
GT_API GTN_GetCombineAxes(short core,short index,TCombineAxes *pCombineAxes);
GT_API GTN_CombineAxesOn(short core,short index);
GT_API GTN_CombineAxesOff(short core,short index);
GT_API GTN_GetCombineAxesStatus(short core,short index,TCombineAxesStatus *pCombineAxesStatus);

typedef struct
{
    short type;
    short index[2];
} TAddition;

typedef struct
{
	double pos;
	double vel;
} TAdditionStatus;

GT_API GTN_SetAxisAddition(short core,short axis,short dataType,TAddition *pAddition);
GT_API GTN_GetAxisAddition(short core,short axis,short dataType,TAddition *pAddition);
GT_API GTN_GetAxisAdditionStatus(short core,short axis,short dataType,TAdditionStatus *pAdditionStatus);
GT_API GTN_ZeroAxisAdditionPos(short core,short axis,short dataType,short count=1);

typedef struct
{
    short profileType[3];
    short profileIndex[3];
    short profileId[3];
    short encoderType[3];
    short encoderIndex[3];
    short encoderId[3];
} TContourConfig;

typedef struct
{
    double kp[3];
    double ki[3];
    short errorWindow[3];
    short limit[3];
} TContourControl;

typedef struct
{
    short cornerStepIn;
    short cornerStepOut;
    short reserved1[2];
    double cornerTheta;
    short reserved2[4];
    double window;
    double para;
} TContourMode;

GT_API GTN_SetContourConfig(short core,short index,TContourConfig *pContourConfig);
GT_API GTN_GetContourConfig(short core,short index,TContourConfig *pContourConfig);
GT_API GTN_SetContourControl(short core,short index,TContourControl *pContourControl);
GT_API GTN_GetContourControl(short core,short index,TContourControl *pContourControl);
GT_API GTN_SetContourMode(short core,short index,TContourMode *pContourMode);
GT_API GTN_GetContourMode(short core,short index,TContourMode *pContourMode);
GT_API GTN_SetContourEnable(short core,short index,short enable);
GT_API GTN_SetControlAddition(short core,short index,TAddition *pAddition);
GT_API GTN_GetControlAddition(short core,short index,TAddition *pAddition);

GT_API GTN_SetDisplayDip(short core,short mode);
GT_API GTN_GetDisplayDip(short core,short *pMode);



GT_API GTN_SetMcOverride(short core,short axis,short mode,double override,double smoothTime);
GT_API GTN_GetMcOverride(short core,short axis,short mode,double *pOverrideTarget,double *pSmoothTime,double *pOverride);

typedef struct
{
    short  index;
}TPVTPosCompareStart;

typedef struct
{
    short  index;
}TPVTPosCompareStop;
/*-----------------------------------------------------------*/
/* ���ߺ������߼�������ת��                                    */
/*-----------------------------------------------------------*/
typedef struct
{
    short index;
    short id;
    short reverse1[2];
    double reverse2[4];
}TResPhyInfo;
GT_API GTN_GetResPhyInfo(short core,short type,short index,TResPhyInfo *pStationPhyInfo);

// �߼���Ϣ�ṹ��
typedef struct
{
    short core;                                  // �߼��˺�,��1��ʼ
    short dataType;                              // ��Ҫת������Դ����
    short index;                                 // �߼�������,��1��ʼ
    short reserve[5];                            // �����ռ�
} TLogicInfo;

// ������Ϣ�ṹ��
typedef struct
{
    short cardIndex;                             // ��������,��1��ʼ
    short stationPhyId;                          // ����վ��
    short modulePhyId;                           // ��չģ��վ��
    short dataType;                              // ��Ҫת������Դ����
    short index;                                 // ����������
    short reserve[3];                            // �����ռ�
} TPhysicInfo;

#define PORT_A_GENERAL_GLINK_II     (1)
#define PORT_B_GENERAL_GLINK_II     (2)
#define PORT_C_HIGH_SPEED_GLINK_II  (3)
#define PORT_D_ETHER_CAT            (4)

GT_API GTN_ReadPhysicalMap(void);
GT_API ConvertPhysical(short core,short dataType,short terminal,short index);
GT_API ConvertLogical(TLogicInfo *pLogicInfo,TPhysicInfo *pPhysicInfo);

/*---------------------------------------------------------------------------------------------*/
/* ����ͨѶָ�ͨ��485/232ͨ��ָ���gts.lib�е������Ƽ�ʹ�ã�                                   */
/*---------------------------------------------------------------------------------------------*/
GT_API GTN_RN_ComSerialOpen(short cardIndex, short stationPhyId, short comIndex);
GT_API GTN_RN_ComSerialClose(short cardIndex, short stationPhyId, short comIndex);
GT_API GTN_RN_ComSerialRead(short cardIndex, short stationPhyId, short comIndex, uint32_t  readLen, uint32_t *pResLen, unsigned char *pData);
GT_API GTN_RN_ComSerialReadFast(short cardIndex, short stationPhyId, short comIndex, uint32_t readLen, uint32_t *pResLen, unsigned char *pData);
GT_API GTN_RN_ComSerialWrite(short cardIndex, short stationPhyId, short comIndex,uint32_t writeLen, uint32_t *pResLen, unsigned char *pData);
GT_API GTN_RN_ComSerialGetState(short cardIndex, short stationPhyId, short comIndex, unsigned char *pState);
GT_API GTN_RN_ComSerialSetSettings(short cardIndex, short stationPhyId, short comIndex, uint32_t baudrate, unsigned char stopBits, unsigned char parity);
GT_API GTN_RN_ComSerialClearErr(short cardIndex, short stationPhyId, short comIndex, unsigned char flag);
GT_API GTN_RN_ComSerialSetMode(short cardIndex, short stationPhyId, short comIndex, unsigned short comMode);
GT_API GTN_RN_ComSerialGetRecvFifoCnt(short cardIndex, short stationPhyId, short comIndex,short *pCount);

//��չģ������Ѱַָ�
GT_API GTN_RN_SetExtDiDoReversePhysical(short cardIndex, short stationPhyId, short moduleId, int32_t* pInputReverse, int32_t inputCount,int32_t *pOutputReverse,int32_t outputCount);
GT_API GTN_RN_GetExtDiDoReversePhysical(short cardIndex, short stationPhyId, short moduleId, int32_t* pInputReverse, int32_t inputCount,int32_t *pOutputReverse,int32_t outputCount);
GT_API GTN_RN_GetExtAoPhysical(short cardIndex, short stationPhyId, short moduleId, int32_t aoIndex,double* pValue, int32_t count);
GT_API GTN_RN_GetExtAoValuePhysical(short cardIndex, short stationPhyId, short moduleId, int32_t aoIndex,int32_t* pValue, int32_t count);
GT_API GTN_RN_GetExtAiPhysical(short cardIndex, short stationPhyId, short moduleId, int32_t aiIndex,double* pValue, int32_t count);
GT_API GTN_RN_GetExtAiValuePhysical(short cardIndex, short stationPhyId, short moduleId, int32_t aiIndex,int32_t* pValue, int32_t count);
GT_API GTN_RN_SetExtAoValuePhysical(short cardIndex, short stationPhyId, short moduleId, int32_t aoIndex,int32_t* pValue, int32_t count);
GT_API GTN_RN_SetExtAoPhysical(short cardIndex, short stationPhyId, short moduleId, int32_t aoIndex,double* pValue, int32_t count);
GT_API GTN_RN_GetExtDiBitPhysical(short cardIndex, short stationPhyId, short moduleId, int32_t diIndex, uint32_t* pValue, int32_t count);
GT_API GTN_RN_GetExtDiPhysical(short cardIndex, short stationPhyId, short moduleId, uint32_t* pValue, int32_t count);
GT_API GTN_RN_GetExtDoPhysical(short cardIndex, short stationPhyId, short moduleId,uint32_t* pValue, int32_t count);
GT_API GTN_RN_SetExtDoBitPhysical(short cardIndex,short stationPhyId,short moduleId,int32_t doIndex,uint32_t* pValue,int32_t count);
GT_API GTN_RN_SetExtDoPhysical(short cardIndex, short stationPhyId, short moduleId, uint32_t* pValue, int32_t count);
GT_API GTN_RN_SetExtModuleMode(short cardIndex,short mode);
GT_API GTN_RN_GetExtModuleMode(short cardIndex,short *pMode);

GT_API GTN_RN_UpdateExtModuleFirmware(short cardIndex, short stationPhyId, short moduleId, const char* pFile);
GT_API GTN_RN_SetExtModuleComLedSts(short cardIndex, short stationPhyId, short moduleId, int32_t value);
GT_API GTN_RN_GetExtModuleInfo(short cardIndex, short stationPhyId, short moduleId, short infoType, int32_t* pValue);























/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*                        �����汾���ܺ���                                */
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

// �û��ֶ�����(XML)��ʼ������ָ��
GT_API GTN_OpenCard(short channel=5,void *pPrm=NULL,char *pFileName=NULL);
/**
 * @brief ��ȡ�豸���
 * @param cardNum ���ţ�ȡֵ��Χ[1,8]
 * @param pHandle �����豸���
 * @return 0��ʾ�����ɹ�����0��ʾ����ʧ��
 * @notice ��7�����ų�����Χ
 *         ��-6���豸δ��
*/
GT_API GTN_GetHandle(short cardNum,HANDLE *pHandle);
GT_API GTN_InitRingNet(short mode,char *pFileName);
GT_API GTN_SetJtGshdCount(short core,short gshdCount,short lastStationAxisCount);
GT_API GTN_GetCardType(uint32_t *pCardTypeArray,short cardTypeArraySize,short *pCardTypeCount);

#define NET_INIT_MODE_AUTO                       (0)    // �Զ�ɨ�����磬Ĭ��ģʽ
#define NET_INIT_MODE_SKIP_TERMINAL              (1)    // ֧��ECAT xml�ļ���վģʽ��
#define NET_INIT_MODE_MULT_OPEN                  (2)    // ˫��ģʽ��

#define NET_INIT_MODE_XML_STRICT                 (100)  // XML�ϸ񿪿�ģʽ

#define NO_NET                                   (0xf)
#define RING_NET                                 (6)
#define ETHERCAT_NET                             (8)
#define ETHERCAT_RING_MISC_NET                   (9)

#define NET_SRC_NONE                             (NO_NET)
#define NET_SRC_FROM_RING_NET                    (RING_NET)
#define NET_SRC_FROM_ECAT_NET                    (ETHERCAT_NET)
typedef struct  
{
    short relateEnable;
    short netSrc;                                // ������Դ��Ӧ���ⲿ���硣��Դ��RingNet����EtherCAT,�����������硣
    short netSrcIndex;                           // �ⲿ�����Ӧ��������
    short reserve1[9];
    double reserve2[3];
}TSlaveRelateInfo;

GT_API GTN_NetInit(short mode=0,void *pPrm=NULL,short overTime=0,int32_t *pStatus=NULL);
GT_API GTN_SetMcSrcToSlaveRelateInfo(short core,short mcType,TSlaveRelateInfo *pSlaveInfo,short count);
GT_API GTN_GetMcSrcToSlaveRelateInfo(short core,short mcIndex,short type,TSlaveRelateInfo *pSlaveInfo,short count);

GT_API GTN_SetAxisCircularSafetyZone(short core,short safetyZoneIndex,short enable,TAxisCircularSafetyZone *pPrm);
GT_API GTN_GetAxisCircularSafetyZone(short core,short safetyZoneIndex,short *pEnable,TAxisCircularSafetyZone *pPrm);
GT_API GTN_SetPrfRefSafetyZone(short core,short profile,short enable,TProfileReferenceSafetyZone *pPrm);
GT_API GTN_GetPrfRefSafetyZone(short core,short profile,short *pEnable,TProfileReferenceSafetyZone *pPrm);
GT_API GTN_GetPrfRefSafetyZoneSts(short core,short profile,int32_t *pSts);
GT_API GTN_GetAuEncVelFilter(short core,short type,short encoder,short *pFilterNum);
GT_API GTN_SetAuEncVelFilter(short core,short type,short encoder,short filterNum);

GT_API GTN_SetPosEx(short core,short profile,double pos);
GT_API GTN_GetPosEx(short core,short profile,double *pPos);

GT_API GTN_PrfTrapEx(short core,short profile);
GT_API GTN_GetTrapRunTime(short core,short profile,TTrapPrm *pPrm,double currentPos,double targetPos,double targetVel,double runPos,double *pRunTime);
GT_API GTN_GetTrapRunPos(short core,short profile,TTrapPrm *pPrm,double currentPos,double targetPos,double targetVel,double runTime,double *pRunPos);

GT_API GTN_PvtTableUserData(short core,short tableId,short userDataType,double time,void *pData);

typedef struct
{
    double distance;
    double vM;              // ���õ�����ٶ�
    double acc;             // ���õ�z�����ٶ�
    double pa1;             // ���ٰٷֱ�1
    double pa2;             // ���ٰٷֱ�2
    double dec;             // ���õ�z�����ٶ�
    double pd1;             // ���ٶȰٷֱ�1
    double pd2;             // ���ٶȰٷֱ�2

    double velM;            // ʵ���ܴﵽ������ٶ�,���ض�ȡ��
    double accM;            // ʵ���ܴﵽ�������ٶ�,���ض�ȡ��
    double decM;            // ʵ���ܴﵽ�������ٶ�,���ض�ȡ��
    double time;            // ʵ�ʹ滮ʱ�䣬���ض�ȡ��
}TPvtTableMoveAbsolutePrm;
GT_API GTN_PvtTableMoveAbsoluteTwoSegment(short core,short profile,TPvtTableMoveAbsolutePrm *pTargetPos1,double *pDelay,TPvtTableMoveAbsolutePrm *pTargetPos2,short count);

/*-----------------------------------------------------------*/
/* Command Array                                             */
/*-----------------------------------------------------------*/
GT_API GTN_SetTriggerArray(short core,short trigger,TTrigger *pTrigger,short count);

GT_API GTN_GetFunIdPro(short core,char *pFunName,short *pFunId);
GT_API GTN_GetVarIdPro(short core,char *pFunName,char *pVarName,TVarInfo *pVarInfo);

GT_API GTN_SetVarValueEx(short core,short page,TVarInfo *pVarInfo,double *pValue,short count=1);
GT_API GTN_GetVarValueEx(short core,short page,TVarInfo *pVarInfo,double *pValue,short count=1);

#define SLAVE_MIDDLE_POS_DIMENSION_MAX             (3)
typedef struct
{
    double targetPos;             // ����Ŀ��λ��
    double safetyPos;             // ��ȫ����λ��
    double slaveMiddlePos[SLAVE_MIDDLE_POS_DIMENSION_MAX];             // �����м��λ����Ϣ
} TBufLeapFrogInfo;

GT_API GTN_BufLeapFrog(short core,short crd,short axis,TBufLeapFrogInfo *pLeapFrogInfo,short modal,short fifo);
GT_API GTN_BufLeapFrogEx(short core,short crd,short axis,TBufLeapFrogInfo *pLeapFrogInfo,short modal,short fifo=0);
GT_API GTN_SetCrdBufCommandDelay(short core,short crd,short fifo,short enable);

GT_API GTN_SetCrdStopMode(short core,short crd,short stopMode);
GT_API GTN_GetCrdStopMode(short core,short crd,short *pStopMode);

typedef struct
{
    double synDistance;             // ��ǰ�κϳɾ���
    double movedsynDistance;        // ��ǰ�����˶���ɵľ���
    double reserve1[10];            // ����
}TCrdMoveInfo;

GT_API GTN_GetCrdMoveInfo(short core,short crd,TCrdMoveInfo *pCrdMoveInfo,short fifo=0);

GT_API GTN_LaserFollowMode(short core,short laserChannel,short *pLaserFollowSource,double *pLaserFollowStartPower,short laserCount);
GT_API GTN_LaserFollowRatio(short core,short laserChannel,double *pLaserFollowRatio,double *pLaserFollowMinPower,double *pLaserFollowMaxPower,short laserCount);

GT_API GTN_BufMultiLaserFollowOn(short core,short crd,int32_t laserChannelMask,short fifo);
GT_API GTN_BufMultiLaserFollowOff(short core,short crd,int32_t laserChannelMask,short fifo);
GT_API GTN_BufMultiLaserOn(short core,short crd,int32_t laserChannelMask,short fifo);
GT_API GTN_BufMultiLaserOff(short core,short crd,int32_t laserChannelMask,short fifo);

GT_API GTN_BufMultiLaserFollowOnEx(short core,short crd,int32_t laserChannelMask,short fifo);
GT_API GTN_BufMultiLaserFollowOffEx(short core,short crd,int32_t laserChannelMask,short fifo);
GT_API GTN_BufMultiLaserOnEx(short core,short crd,int32_t laserChannelMask,short fifo);
GT_API GTN_BufMultiLaserOffEx(short core,short crd,int32_t laserChannelMask,short fifo);

GT_API GTN_SetCrdContourErrorControlPrm(short core,short crd,short crdAxis,short enable,double *pCoef,short coefCount);
GT_API GTN_GetCrdContourErrorControlPrm(short core,short crd,short crdAxis,short *pEnable,double *pCoef,short *pCoefCount);

GT_API GTN_SetAxisMotionSmoothParameter(short core,short mode,void *pPrm,int32_t axisMask,TListInfo *pListInfo);
GT_API GTN_GetAxisMotionSmoothParameter(short core,short axis,short *pMode,void *pPrm,short count);

GT_API GTN_SetStopSmoothTime(short core,short profile,short smoothTime);
GT_API GTN_GetStopSmoothTime(short core,short profile,short *pSmoothTime);

GT_API GTN_SetCrossCompMode(short core,short axis,short cycleMode,short revCompCycle);
GT_API GTN_GetCrossCompMode(short core,short axis,short *pCycleMode,short *pRevCompCycle);

GT_API GTN_WriteDigitalOutputPro(short core,TDigitalOutputPro *pDo,TListInfo *pListInfo);
GT_API GTN_SetStopIoPro(short core,short axis,short stopType,TStopIoPrm *pPrm,short count,TListInfo *pListInfo);
GT_API GTN_GetStopIoPro(short core,short axis,short stopType,TStopIoPrm *pPrm,short *pCount);
GT_API GTN_SetStopIoPrm(short core,short axis,short stopType,short inputType,short inputIndex,short mode,short modePrm);

GT_API GTN_InitFPGAEncoder(short core);
GT_API GTN_SetFPGAEncoder(short core,short enable,int32_t intervalTime,short reverseMask);
GT_API GTN_GetFPGAEncoder(short core,int32_t *pDataChn1,int32_t *pDataChn2,int32_t *pDataChn3,int32_t *pDataChn4,int32_t *pCount,short *pOverFlowFlag);

GT_API GTN_SetExtModuleAccessMode(short core,short mode);
GT_API GTN_GetExtModuleAccessMode(short core,short *pMode);

typedef struct
{
    short followMode;     //λ�ñȽ���������ģʽ,0����������
    short hsoOutputMode;  //hso���ģʽ��0���������1������λ�ñȽ�ָ�����ò��������2�����ո���ָ������ֵ�����
    short timeScale;      //ʱ�侫�ȣ�0��1us��1��0.1us
    short pad;
    double maxValue;
    double minValue;
    double k;
    double b;
}TPosCompareFollowCrd;
GT_API GTN_SetCrdPosCompareFollowPulseWidthPrm(short core,short crd,short posCompareIndex,short hsoIndex,TPosCompareFollowCrd *pPosCompareFollowCrd,short count);
GT_API GTN_CrdPosCompareFollowPulseWidthEnable(short core,short crd,short posCompareIndex,short enable);

typedef struct
{
    short index;              //λ�ñȽ�������
    short enable;
    short reserve1[2];
    int32_t  reserve2[2];
}TPosCompareOnOffList;
GT_API GTN_PosCompareOnOffList(short core,short group,TPosCompareOnOffList *pPosCompareOnOff,TListInfo *pListInfo);

typedef struct
{
    short index;
    short reserve[3];
    uint32_t count;
    int32_t syncPos;
    int32_t time;
} TPosComparePsoPrmList;
GT_API GTN_PosComparePsoPrmList(short core,short group,TPosComparePsoPrmList *pPrm,TListInfo *pListInfo);

GT_API GTN_SetScanAlarmAutoStopMode(short core,short mode,uint32_t errorcodeCheckMask,uint32_t errorcodeCheckRef,short crd);
GT_API GTN_GetScanAlarmAutoStopMode(short core,short *pMode,uint32_t *pErrorcodeCheckMask,uint32_t *pErrorcodeCheckRef,short crd);
GT_API GTN_GetScanErrorCode(short core,uint32_t *pErrorCode,short crd);
GT_API GTN_LoadScanCorrectionTable(short core,short scan,char *pFile,short type);

GT_API GTN_AddTaskPro(short core,short taskType,void *pTaskData,short *pTaskIndex);

typedef struct
{
    unsigned short resType;         // watch����������
    unsigned short resIndex;        // watch����������
    unsigned short resSubIndex;     // watch������������
    unsigned short resCount;        // һ������Ҫ��ȡwatch����������
    double resValue[256];           // ��ȡ����watch������ֵ
} TMcVarResInfo;
GT_API GTN_GetMcVarArray(short core,short resInfoCount,TMcVarResInfo *pResInfo);

typedef struct
{
    TWatchVar var;
    unsigned short condition;
    double value;
    double continueTime;
} TWatchConditionVar;

typedef struct
{
    short conditionDone;
    short modal;
    short reserve1[2];
    int32_t segNum;
    int32_t userTag;
    int32_t reserve2[8];
}TWaitForConditionInfo;

GT_API GTN_WaitForConditionVar(short core,TWatchConditionVar *pWaitConditionVarList,short conditionCount,short operation,TWaitTimeout *pTimeout,TWatchVar *pWaitResultVar,TListInfo *pListInfo);
GT_API GTN_GetWaitForConditionInfo(short core,short list,TWaitForConditionInfo *pWaitForConditionInfo);

GT_API GTN_BufSetLongVar(short core,short crd,short index,int32_t value,short fifo);
GT_API GTN_BufSetDoubleVar(short core,short crd,short index,double value,short fifo);

GT_API GTN_SetGantryModePro(short core,short group,short master,short slave,short mode,int32_t syncErrorLimit);

#define PREDICTION_MODE_AXIS_VELOCITY_TO_FOLLOWERROR                 (0)
#define PREDICTION_MODE_AXIS_VELOCITY_TO_VELOCITY                    (1)
#define PREDICTION_MODE_AXIS_POSITION_TO_POSITION                    (2)
GT_API GTN_SetAxisPrediction(short core,short axis,short mode,short enable,double *pCoef,short count1,short count2);
GT_API GTN_GetAxisPrediction(short core,short axis,short *pMode,short *pEnable,double *pCoef,short *pCount1,short *pCount2);

GT_API GTN_InitializeCommandListConfig(short core,TCommandListConfig *pConfig,short count=2);

/*-----------------------------------------------------------*/
/* TIMER�������                                      */
/*-----------------------------------------------------------*/

#define  START_TIMER_MAX		32

typedef struct
{
    short mode;				// ������ֻ��Ϊ0
    short clear;			// �Ƿ������ʼ��¼ֵ��0���������ʼֵ��1�������ʼֵ�����¼�¼��ʼֵ
    short reserve[2];
}TStartTimerPrm;

typedef struct
{
    short run;
    short reserve[3];
    double value;
}TTimerInfo;

GT_API GTN_StartTimer(short core,short index,TStartTimerPrm *pStartTimerPrm,short count,TListInfo *pListInfo);
GT_API GTN_StopTimer(short core,short index,short count,TListInfo *pListInfo);
GT_API GTN_GetTimerInfo(short core,short index,TTimerInfo *pInfo,short count);

GT_API GTN_CheckTerminalLicenseRingNet(short core,short station,short fuctionType,int32_t *pInfo);
/*-----------------------------------------------------------*/
/* ����ָ�ָ��                                              */
/*-----------------------------------------------------------*/
GT_API GTN_RN_Recover(short cardIndex);
/*-----------------------------------------------------------*/
/* GSHD�����С��������                                      */
/*-----------------------------------------------------------*/
GT_API GTN_SetTorqueLimit(short core,short axis,TTorqueLimit *pTorqueLimit);
GT_API GTN_GetTorqueLimit(short core,short axis, TTorqueLimit *pTorqueLimit);

GT_API GTN_SetServoPosLoopPid(short core,short axis,TServoPosLoopPid *pServoPosLoopPid);
GT_API GTN_GetServoPosLoopPid(short core,short axis,TServoPosLoopPid *pServoPosLoopPid);

typedef struct
{
    uint32_t objectIndex;        //һ��ָ����
    unsigned short subIndex;     //����ָ����
    unsigned short reserve;      //����λ
    short byteSize;              //�ֽڳߴ�
    short memType;               //����洢λ�� 0-RAM  1-FLASH
}TServoParamReader;
GT_API GTN_ReadServoParamInfo(short core,short axis, TServoParamReader *pTServoParamReader, unsigned char* pData);
GT_API GTN_WriteServoParamInfo(short core,short axis, TServoParamReader *pTServoParamReader, unsigned char* pData);
GT_API GTN_RN_GetServoAlarmInfo(short core,short axis,uint32_t *pAlarmCode);

GT_API GTN_WriteServo35thHomingFlag(short core, short axis, short flag);

GT_API GTN_SetServoSpdLoopPid(short core,short axis,TServoSpdLoopPid *pServoSpdLoopPid);
GT_API GTN_GetServoSpdLoopPid(short core,short axis,TServoSpdLoopPid *pServoSpdLoopPid);

GT_API GTN_SetServoPid(short core,short axis,short loop,short mode,void *pServoPid);
GT_API GTN_GetServoPid(short core,short axis,short loop,short mode,void *pServoPid);
GT_API GTN_SetServoPidRatio(short core,short axis,double ratio);
GT_API GTN_GetServoPidRatio(short core,short axis,double *pRatio);

typedef struct
{
    double gain1;  // һ������
    double gain2;  // ��������
    double smoothTime; // ƽ��ʱ�䣬��λms
    double spdLimitUpper; // �ٶ����ޣ���λrpm
    double spdLimitLower; // �ٶ����ޣ���λrpm
    double reserved[4]; //����
}TServoNonlinearGlobalGain;
GT_API GTN_RN_GetServoNonlinearGlobalGain(short core,short axis,short mode,short dataType,TServoNonlinearGlobalGain *pServoPid);
GT_API GTN_RN_SetServoNonlinearGlobalGain(short core,short axis,short mode,short dataType,TServoNonlinearGlobalGain *pServoGlobalGain);


/*-----------------------------------------------------------*/
/* ��ȫģʽ����                                              */
/*-----------------------------------------------------------*/
GT_API GTN_RN_SetStationSafeModeControl(short cardIndex,short stationPhyId,short enable,short clearMode);
GT_API GTN_RN_SetStationSafeModeOut(short cardIndex,short stationPhyId,short type,short index,short *pEnable,double *pValue,short count);

GT_API GTN_SetVelLookAheadModeLa(short core, short crd, int VelMode);  //���ٶ�ǰհģʽģʽ
GT_API GT_SetMaxOverrideLa(short crd,double maxSynVelRatio);
GT_API GTN_SetProfileModeLa(short core,short crd,short profileMode);


GT_API GTN_BufSetLongVarEx(short core,short crd,short index,int32_t value,short fifo);
GT_API GTN_BufSetDoubleVarEx(short core,short crd,short index,double value,short fifo);


typedef struct
{
    int32_t segmentNumber;
    int32_t posX;
    int32_t posY;
    short gpo;					// 24V
    short hso;					// 5V
    short reserve[4];			// ȷ��ָ���Ϊ16Word
} TPosCompareCommandPos;

typedef struct
{
    int32_t segmentNumber;
    int32_t time;
    short pad[2];
    short gpo;
    short hso;
}TPosCompareCommandTime;

typedef union
{
    TPosCompareCommandPos pos;
    TPosCompareCommandTime time;
    short data16[12];
}TPosComparePredictiondataUnion;

typedef struct
{
    short type;
    short pad[3];
    TPosComparePredictiondataUnion data;
}TPosComparePredictionData;

GT_API GTN_SetPosComparePredictionDataToDsp(short core,short posCompareIndex,short count,TPosComparePredictionData *pData,short *pWriteCount);

/*-----------------------------------------------------------*/
/* ����ֵ�������������                                      */
/*-----------------------------------------------------------*/
GT_API GTN_SetAuAbsEncMultiTurnRange(short core,short encoder,double range);
GT_API GTN_ReadAuAbsEncPos(short core,short encoder,double *pPos);

GT_API GTN_SetEncryptConfigRingNet(short core,short station,TEncryptConfigPrm *pConfigPrm, short *pSts);
GT_API GTN_GetEncryptDataRingNet(short core,short station,TEncryptData *pReadPrm);
GT_API GTN_SetEncryptDataRingNet(short core,short station,TEncryptData *pWritePrm);

GT_API GTN_ClearPressStatus(short core,short pressAxis);

/*-----------------------------------------------------------*/
/* ��Բ�岹ָ��                                              */
/*-----------------------------------------------------------*/
#define ELLIPSE_AUX_POINT_COUNT                 (5)

#define ELLIPSE_MODE_AUX_POINT                  (0)
#define ELLIPSE_MODE_STANDARD                   (1)

#define ELLIPSE_MODE_AUX_POINT_2D               (0)
#define ELLIPSE_MODE_STANDARD_2D                (1)

typedef struct
{
    double pos[ELLIPSE_AUX_POINT_COUNT][INTERPOLATION_AXIS_MAX];    // ��Բ�ϸ���������
}TEllipseAuxPoint;

typedef struct
{
    double centerPoint[INTERPOLATION_AXIS_MAX];// ��ԲԲ������
    double theta;                              // ��Բ��ת�Ƕ�
    double a;                                  // ��Բ����
    double b;                                  // ��Բ����
}TEllipseStandard;

typedef union
{
    TEllipseAuxPoint auxPoint;                 // ������ģʽ����
    TEllipseStandard standard;                 // ��׼ģʽ����

    double reserve[60];
} TEllipseParameterUnion;

typedef struct
{
    double endPoint[INTERPOLATION_AXIS_MAX];   // �յ�����
    short plane;                               // ��Բƽ��ѡ��0��XY��1��YZ��2��ZX
    short dir;                                 // ��Բ����0��˳ʱ�룻1����ʱ��
    short overrideSelect;                      // �ٶȱ���ѡ��0����1�鱶�ʣ�1����2�鱶��
    short mode;                                // ��Բģʽ��Ŀǰֻ֧�ֲ���0(������ģʽ)

    TEllipseParameterUnion data;               // ��������
} TEllipseParameter;

//-------------------------------------------------------
//����˵������Բ�岹��������,ģʽ��ELLIPSE_MODE_AU_POINT_2D
//plane--------------��Բƽ��ѡ��INTERPOLATION_CIRCLE_PLAT_XY(0)��XY��INTERPOLATION_CIRCLE_PLAT_YZ(1)��YZ��INTERPOLATION_CIRCLE_PLAT_ZX(2)��ZX
//dir----------------��Բ����0��˳ʱ�룻1����ʱ��
//overrideSelect-----�ٶȱ���ѡ��0����1�鱶�ʣ�1����2�鱶��
//pad----------------ռλ����������Ҫ����
//endPoint1----------�յ�����1,�������plane���������palneΪXYƽ�棬��endPoint1��pos1ΪX���꣬endPoint2��pos2ΪY����
//endPoint2----------�յ�����2
//pos1---------------��Բ�ϸ���������1
//pos2---------------��Բ�ϸ���������2
//-------------------------------------------------------
typedef struct
{
    short plane;
    short dir;
    short overrideSelect;
    short pad;

    double endPoint1;
    double endPoint2;

    double pos1[ELLIPSE_AUX_POINT_COUNT];
    double pos2[ELLIPSE_AUX_POINT_COUNT];
} TEllipseAuxPoint2D;

//-------------------------------------------------------
//����˵������Բ�岹��������,ģʽ��ELLIPSE_MODE_STANDARD_2D
//plane--------------��Բƽ��ѡ��INTERPOLATION_CIRCLE_PLAT_XY(0)��XY��INTERPOLATION_CIRCLE_PLAT_YZ(1)��YZ��INTERPOLATION_CIRCLE_PLAT_ZX(2)��ZX
//dir----------------��Բ����0��˳ʱ�룻1����ʱ��
//overrideSelect-----�ٶȱ���ѡ��0����1�鱶�ʣ�1����2�鱶��
//pad----------------ռλ����������Ҫ����
//endPoint1----------�յ�����1,�������plane���������palneΪXYƽ�棬��endPoint1ΪX���꣬endPoint2ΪY����
//endPoint2----------�յ�����2
//centerPoint1-------��ԲԲ������1���������plane���������palneΪXYƽ�棬��centerPoint1ΪX���꣬centerPoint2ΪY����
//centerPoint2-------��ԲԲ������2
//theta--------------��Բ��ת�Ƕȣ���λ����
//a------------------��Բ����
//b------------------��Բ���ᣬ�������ȳ����
//-------------------------------------------------------
typedef struct
{
    short plane;
    short dir;
    short overrideSelect;
    short pad;

    double endPoint1;
    double endPoint2;

    double centerPoint1;
    double centerPoint2;

    double theta;
    double a;
    double b;
}TEllipseStandard2D;

GT_API GTN_Ellipse(short core,short crd,TEllipseParameter *pEllipse,double synVel,double synAcc,double velEnd,int32_t segNum,short fifo=0);
GT_API GTN_EllipseEx(short core,short crd,TEllipseParameter *pEllipse,double synVel,double synAcc,double velEnd,int32_t segNum,short fifo=0);

GT_API GTN_EllipsePro(short core,short crd,short mode,void *pData,double synVel,double synAcc,double velEnd,int32_t segNum,short fifo=0);
GT_API GTN_EllipseProEx(short core,short crd,short mode,void *pData,double synVel,double synAcc,double velEnd,int32_t segNum,short fifo=0);


/*-----------------------------------------------------------*/
/* ������ָ���        	                                   */
/*-----------------------------------------------------------*/
#define BATCH_COMMAND_END_MODE_DEFAULT                     (0)
#define BATCH_COMMAND_END_MODE_GET_MC_VAR_EX               (1)

typedef struct
{
    short commandCount;                // ��ǰ������ָ������
    short errorCommandNumber;          // ִ�г�����ָ�����
    short errorCode;                   // ִ�г�����ָ�������ϸ��Ϣ������ָ������ϸ��Ϣ��
    short reserve[5];
}TBatchCommandResult;

GT_API GTN_BatchCommandBegin(short core);
GT_API GTN_BatchCommandEnd(short core,TBatchCommandResult *pResult,short mode,void *pPrm,void *pValue,short count);

/*-----------------------------------------------------------*/
/* ������ָ��           	                                   */
/*-----------------------------------------------------------*/
// ��������غ���
#define MC_HEIGHT_FREQUENCY            (450)
// ���á���ȡ���������Ʋ���
typedef struct
{
   short active;                 // �߶ȿ��Ƶ�ʹ�ܱ�־��
   short ctlMode;                // �߶ȱջ����ƻ��ǿ���������
   short linkHeightCtlGroup;     // �����ڼ���߶ȿ��ơ�
   short feedbackType;           // �߶ȿ��Ƶķ������ͣ�����������Ϊ0,�ȷ�������Ϊ�߶�Ƶ���ź�
   short feedbackIndex;          // �߶ȿ��Ƶķ������Ͷ�Ӧ��������
   short interval;				// �������ʱ�䣬�ж�����Ϊ��λ��
   int32_t errorLimit;              // ������
   short reserve[8];             // ��������������Ϊ0��
}THeightControlPrm;

GT_API GTN_SetAxisHeightControlPrm(short core,short axis,THeightControlPrm *pPrm);
GT_API GTN_GetAxisHeightControlPrm(short core,short axis,THeightControlPrm *pPrm);

// ���á���ȡ��������ֵ��
GT_API GTN_SetHeightInterpolationTable(short core, short heightCtlGroup, int32_t n, double* pPosEnc, double* pPosHeight);
GT_API GTN_GetHeightInterpolationTable(short core, short heightCtlGroup, int32_t n, double* pPosEnc, double* pPosHeight, int32_t* pRealCount);

GT_API GTN_SetAxisHeightControlPid(short core,short axis,TPid *pPid);
GT_API GTN_ZerophaseFilter(short core,int32_t dataLen,double inputdata[],double smoothArray[]);

GT_API GTN_GetAxisErrorStatusLink(short core,short axis,short *pLinkAxis,short *pLinkMode,short *pCcount);
GT_API GTN_SetAxisErrorStatusLink(short core,short axis,short *pLinkAxis,short *pLinkMode,short count);

typedef struct
{
    short type;					// �ο������Ǳ�����λ�û��ǹ滮λ�û��ǵ��ݸ߶�
    short index;				// ���������߹滮������
    int32_t  crossPos;			// �������߹رո��湦�ܵĴ�Խ�߶�
    short dir;					// �������߹رյĴ�Խ����
    short pad1[3];
}THeightCrossPrm;

typedef struct
{
    short keepEnable;				// 0:�˶���ָ���߶�,1:�˶���ָ���߶Ⱥ󣬱��ָ߶ȸ���
    short pad1[3];
    THeightCrossPrm enableData;		// �Զ������߶ȸ������
    THeightCrossPrm disableData;	// �Զ��رո߶ȸ������
}THeightFollowPrm;

#define HEIGHT_DIR_CROSS_POSITIVE            (1)
#define HEIGHT_DIR_CROSS_NEGATIVE            (2)
#define HEIGHT_DIR_CROSS_EQUAL               (3)

#define HEIGHT_FOLLOW_ENABLE_MODE_MANUAL						(0)
#define HEIGHT_FOLLOW_ENABLE_MODE_AUTO							(1)
// �Զ�����/�رո��湦�ܻ���Ӧ�ó����������߹رո߶ȸ��湦��
GT_API GTN_SetAxisHeightFollowMode(short core,short axis,short mode,THeightFollowPrm *pPrm);


// ������λ�ø��湦�ܴ򿪡��ر�
GT_API GTN_AxisHeightControlEnable(short core,short axis,short enable,int32_t pos=10);
// ��ȡ������λ��
GT_API GTN_GetHeightInterpolationPos(short core, short heightCtlGroup, double* pHeightFrq, double* pHeightPosRaw, double* pInterpolationPos);
// ��ȡ������״̬��Ϣ

typedef struct
{
    short ctlMode;			// ��ǰ��ջ�ģʽ������������ջ������ǵ�����Ƶ�ʱջ���
    short errorSts;			// ����״̬��
    double cmpValue;		// ����ֵ
}THeightInf;
GT_API GTN_GetAxisHeightInf(short core,short axis,THeightInf *pHeightInf);
// ���������״̬
GT_API GTN_ClearAxisHeightSts(short core,short axis);

//FIR�˲���
#define HEIGHT_FILTER_TYPE_FREQUENCY			(1)
#define HEIGHT_FILTER_TYPE_CMP_VALUE			(2)
GT_API GTN_GetAxisHeightFrqFilter(short core,short axis,short type,short *pFilterNum);
GT_API GTN_SetAxisHeightFrqFilter(short core,short axis,short type,short filterNum);


// �궨����

#define CALIBRATION_MODE_DIFFERENT_STEP		(1)
// �궨stage
#define DIFFERENT_STEP_CALIBRATION_STAGE_NONE						(-1)//����
#define DIFFERENT_STEP_CALIBRATION_STAGE_HOME_SEARCH				(1)//�������
#define DIFFERENT_STEP_CALIBRATION_STAGE_GO_OFFSET					(2)//�˶�ƫ��
#define DIFFERENT_STEP_CALIBRATION_STAGE_CALIBRATION_INIT			(3)//��ʼ�궨ǰ�ĳ�ʼ��
#define DIFFERENT_STEP_CALIBRATION_STAGE_CALIBRATION				(4)//�궨����
#define DIFFERENT_STEP_CALIBRATION_STAGE_CALIBRATION_DONE			(5)//�궨���
#define DIFFERENT_STEP_CALIBRATION_STAGE_CALIBRATION_STOP			(6)//�궨ֹͣ

#define DIFFERENT_STEP_CALIBRATION_STAGE_HOME_START_ERROR			(100)
#define DIFFERENT_STEP_CALIBRATION_STAGE_HOME_SEARCH_ERROR			(101)
#define DIFFERENT_STEP_CALIBRATION_STAGE_GO_OFFSET_ERROR			(102)
#define DIFFERENT_STEP_CALIBRATION_STAGE_CALIBRATION_ERROR			(103)
#define DIFFERENT_STEP_CALIBRATION_STAGE_NOT_AXIS_ON				(104)
#define DIFFERENT_STEP_CALIBRATION_STAGE_SET_TABLE_ERROR			(105)

// ���궨������
#define DIFFERENT_STEP_CALIBRATION_STEP_MAX							(4000)

#define CALIBRATION_MODE_DIFFERENT_STEP		(1)
#define CALIBRATION_STEP_MAX			(50)

typedef struct
{
   short heightCtlGroup;                 // �߶ȿ��Ƶ���ţ��ڼ�·�߶ȷ�������
    short motorEncoder;						// �ڼ�·������
   short pad[2];                         // ��������Ϊ0

   double homeVel;                      // ������ٶ� ������/���룩,����0
    double homeDir;							// ������˶�����
   int32_t frqMutationStopValue;           // ����ʱƵ��ͻ��ֹͣ��ֵ,����0
   int32_t offset;                         // �������ͣ��ƫ�á���ͣ��λ�ÿ�ʼ�궨������0

   double distance;                     // �궨���� (���嵥λ��,����0
   double calibrationVel;               // �궨�ٶ�,����0
   double calibrationStepCount;         // �궨����,����0
   double calibrationCountPerStep[CALIBRATION_STEP_MAX]; // ÿ�α궨����,����0���ܵ������4000���㡣
   double reserve[4];                   // ��������Ϊ0
}TDifferentStepCalibration;

typedef union
{
    TDifferentStepCalibration differentStep;
}THeightCalibration;

typedef struct
{
    short mode;							// Ŀǰֻ���Ǳ䲽�����Ա궨��CALIBRATION_MODE_DIFFERENT_STEP
    THeightCalibration prm;
}THeightCalibrationPrm;

GT_API GTN_ClearAxisHeightCalibrationSts(short core,short axis);
GT_API GTN_StopAxisHeightCalibration(short core,short axis);
GT_API GTN_RunAxisHeightCalibration(short core,short axis,short *pStage);
GT_API GTN_SetAxisHeightCalibration(short core,short axis,THeightCalibrationPrm *pPrm);

typedef struct
{
    int32_t positiveMutationValue;		// �ӽ�����ʱ��������Ƶ��ͻ������ֵ����������
    short positiveMutationStopLinkLimitType;// �ӽ�����ʱ,Ƶ��ͻ��ֹͣ�������������λ���͡�
    int32_t negativeMutationValue;		//Զ�뵲��ʱ��������Ƶ��ͻ������ֵ����������
    short negativeMutationStopLinkLimitType;// Զ�뵲��ʱ,Ƶ��ͻ��ֹͣ�������������λ���͡�
}TFrqMutationStopPrm;
GT_API GTN_HeightFrqMutationStopEnable(short core, short axis, short enable, TFrqMutationStopPrm* pMutationStopPrm);
GT_API GTN_GetHeightFrqMutationStopEnable(short core,short axis,short *pEnable,TFrqMutationStopPrm *pMutationStopPrm);

GT_API GTN_GoToAxisFollowHeight(short core, short axis, int32_t followCmd, THeightFollowPrm* pFollowPrm, double trapVel, TTrapPrm* pTrapPrm);

GT_API GTN_GetAxisHeightBand(short core,short axis,int32_t *pBand,int32_t *pTime);
GT_API GTN_SetAxisHeightBand(short core,short axis,int32_t band,int32_t time);

#define HEIGHT_FINDEDGE_LATCH_MAX   4

typedef struct
{
    short type;
    short moveAxis;
    short latchNum;
    short reserve1;
    short latchType[HEIGHT_FINDEDGE_LATCH_MAX];
    short latchIndex[HEIGHT_FINDEDGE_LATCH_MAX];
    int32_t  heightDiff;
    int32_t reserve2;
    double findTime;
}THeightFindEdgePrm;

typedef struct
{
    short findEdgeSts;
    short error;
    double latchValue[HEIGHT_FINDEDGE_LATCH_MAX];
}THeightFindEdgeResult;

GT_API GTN_SetHeightFindEdgePrm(short core, short heightFbIndex, THeightFindEdgePrm* pFindEdgePrm);
GT_API GTN_GetHeightFindEdgeResult(short core,short heightFbIndex,THeightFindEdgeResult *pFindEdgeResult);
GT_API GTN_GetHeightFindEdgeCoef(short core,short heightFbIndex,double* alpha,double* beta);
GT_API GTN_CloseHeightFindEdge(short core,short heightFbIndex);
GT_API GTN_SetHeightFindEdgeStopMask(short core,short heightFbIndex,int32_t mask,int32_t option);
GT_API GTN_GetHeightFindEdgeStopMask(short core,short heightFbIndex,int32_t* mask,int32_t* option);

typedef struct
{
    double vel;			// �����ٶ�
    double acc;			// �������ٶ�
    double dec;			// �������ٶ�
    double smoothTime;  // ƽ��ʱ��

    double safetyVel;	// �˶�����ȫ���ո߶�ʱ���ٶ�

    short slaveType;					// ��������͡�
    short slaveIndex;					// �����Ӧ��������
    int32_t followCmd;		// ����߶�
    short followEnable;	// �˶�������߶��Ƿ񱣳֡�
    short enable;		// ����ʹ��
    short reserve1[2];
    double reserve2[4];
}TSetAxisLeapFrogPrm;
GT_API GTN_SetAxisLeapFrogPrm(short core,short axis,TSetAxisLeapFrogPrm* pAxisLeapFrogPrm);

GT_API GTN_SetLightPowerCtrlPara(short core,unsigned short ctrlMode,unsigned short *pDutyCycle,unsigned short *pPulseWidth);
GT_API GTN_GetLightPowerCtrlPara(short core,unsigned short *pCtrlMode,unsigned short *pDutyCycle,unsigned short *pPulseWidth);

GT_API GTN_UTL_ConvertPhysicToLogic(TPhysicInfo *pPhysicInfo,TLogicInfo *pLogicInfo);
GT_API GTN_OpenSimulation(short core,double time,double ratio);
GT_API GTN_CloseSimulation(short core);
GT_API GTN_GetSimulationStatus(short core,short *pSts);

//-------------------------------------------------------------------------------------------------
// ·����������
//-------------------------------------------------------------------------------------------------
// ·��������ṹ��
typedef struct
{
    double pos[2];                               // x�ᡢy��λ��
    double compensateValue;	                     // z�Ჹ��λ��
}TCompensatePathPoint;

// ·���������ṹ��
typedef struct
{
    short tableIndex;                            // ·������������
    short axisType[2];                           // ��ѯ·��������X��Y����λ�����ͣ�MC_PROFILE:�滮λ�� MC_ENCODER:������λ��
    short axisIndex[2];                          // ��ѯ·��������X��Y������ʹ�õ����						
    short reserve1[3];                            // ����ֵ������Ϊ0
    double offset[2];                            // x�ᡢy��ƫ��
    double compensateVelMax;                     // ����ֵ�仯������ٶ� ����λ��pulse/ms�����ڣ�1����������ʱ����������ֵ�Ĺ��̣�2����������������ʱ������ֵ�仯�Ĺ���
    double approachRadius;                       // ������ʼ��Ͳ����յ����Ч����뾶
    double workBand;                             // ��������ʱ������
    double workHeight;                           // z�Ṥ���߶�
    double reserve2[2];							 // ����ֵ������Ϊ0
}TCompensatePathParameter;

// ·������״̬�ṹ��
typedef struct{
    short enable;								 // ·������ʹ�ܱ�־
    short state;								 // ·������״̬
    short errorStatus;                           // ·�������Ƿ񳬳�errorBand  0:δ�������� 1����������
    short pointIndex;                            // ·��������ǰ��Ĳ����������
    double compensateStartPos[2];                // ·��������ǰ��Ĳ������λ��
    double compensateValue;                      // ·��������ǰ��Ĳ�����
    double reserve1[2];                          // ����ֵ��Ϊ0
}TCompensatePathStatus;

// ����·��������
GT_API GTN_SetCompensatePathTable(short core,short tableIndex, TCompensatePathPoint *pCompensatePathPoint, short pointCount);
// ����·����������
GT_API GTN_SetCompensatePathParameter(short core,short axis, TCompensatePathParameter *pCompensatePath);
// ��ȡ·����������
GT_API GTN_GetCompensatePathParameter(short core,short axis, TCompensatePathParameter *pCompensatePath);
// ����·������
GT_API GTN_StartCompensatePath(short core,short axis, short startMode = 0, void* pParameter = NULL);
// �ر�·������
GT_API GTN_StopCompensatePath(short core,short axis, short stopMode = 0, void* pParameter = NULL);
// ��ȡ·������״̬
GT_API GTN_GetCompensatePathStatus(short core,short axis, TCompensatePathStatus *pCompensatePathStatus);

/*-----------------------------------------------------------*/
/* ��������ֵ������                                          */
/*-----------------------------------------------------------*/
//-----------------------------------------------------------------------------------
// ����˵�������ø�������ֵ�������Ķ�Ȧ��Χ����ָ������������������֣����������ӿ�
// input��cardIndex----���ţ�ȡֵ��Χ��[1,16]
// input��stationPhyId----����վ�ţ�ȡֵ��Χ��[0,64]
// input��encoder----�����������ڵ�ǰվ��������ţ�ȡֵ��Χ��[1,8]
// input��range----������������Ȧ���������ֵ�����磺��������Ȧ��16λ�ģ���range=65536��
//-----------------------------------------------------------------------------------
GT_API GTN_RN_SetAuAbsEncMultiTurnRange(short cardIndex,short stationPhyId,short encoder,double range);

//-----------------------------------------------------------------------------------
// ����˵������ȡ��������ֵ��������λ�ã���ָ������������������֣����������ӿ�
// input��cardIndex----���ţ�ȡֵ��Χ��[1,16]
// input��stationPhyId----����վ�ţ�ȡֵ��Χ��[0,64]
// input��encoder----�����������ڵ�ǰվ��������ţ�ȡֵ��Χ��[1,8]
// output��pPos----��ȡ�ľ���ֵ������������λ��ֵ
//-----------------------------------------------------------------------------------
GT_API GTN_RN_ReadAuAbsEncPos(short cardIndex,short stationPhyId,short encoder,double *pPos);

//-----------------------------------------------------------------------------------
// ����˵�������þ���ֵ�������Ķ�Ȧ��Χ�����������ӿ�
// input��cardIndex----���ţ�ȡֵ��Χ��[1,16]
// input��stationPhyId----����վ�ţ�ȡֵ��Χ��[0,64]
// input��encoder----�������ڵ�ǰվ��������ţ�ȡֵ��Χ��[1,8]
// input��range----��������Ȧ���������ֵ�����磺��������Ȧ��16λ�ģ���range=65536��
//-----------------------------------------------------------------------------------
GT_API GTN_RN_SetAbsEncMultiTurnRange(short cardIndex,short stationPhyId,short encoder,double range);

//-------------------------------------------------------------------------------------------------------
// ����˵������ȡ����ֵ��������λ��ֵ�����������ӿ�
// input��cardIndex----���ţ�ȡֵ��Χ��[1,16]
// input��stationPhyId----����վ�ţ�ȡֵ��Χ��[0,64]
// input��encoder----�������ڵ�ǰվ��������ţ�ȡֵ��Χ��[1,8]
// output��pPos----��ȡ�ľ���ֵ��������λ��ֵ
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_ReadAbsEncPos(short cardIndex,short stationPhyId,short encoder,double *pPos);

/*-----------------------------------------------------------*/
/* ����ͨѶָ�����485/232ͨ��ָ�  (������gt_rn.lib�����Ƽ�ʹ��)*/
/*-----------------------------------------------------------*/
short GT_RN_ComOpen(short index);
short GT_RN_ComClose(short index);
short GT_RN_ComRead(short index, uint32_t readLen, uint32_t* pResLen, unsigned char * pData);
short GT_RN_ComWrite(short index, uint32_t writeLen , uint32_t* pResLen, unsigned char * pData);
short GT_RN_ComGetState(short index, unsigned char * pState);
short GT_RN_ComSetSettings(short index, uint32_t baudrate, unsigned char stopBits, unsigned char parity);
short GT_RN_ComClearErr(short index, unsigned char flag);
short GT_RN_ComSetMode(short index,unsigned short comMode);


/*-----------------------------------------------------------*/
/* ����ͨѶָ�ͨ��485/232ͨ��ָ�(������gt_rn.lib�����Ƽ�ʹ��)*/
/*-----------------------------------------------------------*/
short GTN_RN_SerialComOpen(short cardIndex, short stationphyId, short comIndex);
short GTN_RN_SerialComClose(short cardIndex, short stationphyId, short comIndex);
short GTN_RN_SerialComRead(short cardIndex, short stationphyId, short comIndex, uint32_t readLen, uint32_t* pResLen, unsigned char* pData);
short GTN_RN_SerialComWrite(short cardIndex, short stationphyId, short comIndex, uint32_t writeLen, uint32_t* pResLen, unsigned char* pData);
short GTN_RN_SerialComGetState(short cardIndex, short stationphyId, short comIndex, unsigned char* pState);
short GTN_RN_SerialComSetSettings(short cardIndex, short stationphyId, short comIndex, uint32_t baudrate, unsigned char stopBits, unsigned char parity);
short GTN_RN_SerialComClearErr(short cardIndex, short stationphyId, short comIndex, unsigned char flag);
short GTN_RN_SerialComSetMode(short cardIndex, short stationphyId, short comIndex, unsigned short comMode);

//��ȡ���縨��������
GT_API GTN_RN_GetRemotAuEncPos(short cardIndex, short stationPhyId, short auEncIndex,double *pAuEncPos,short anEncCount);

//-------------------------------------------------------------------------------------------------------
//��ȡ��ģ��LED��ʾģʽ
//GTN_RN_ReadLedDispalyMode(short cardIndex, short stationPhyId, unsigned char *pMode, unsigned char *pRadix)
// mode:�ư��������ʾģʽ�� 
//0������ģʽ(�ϵ��ʼ״̬��ʾ�㣬��ʹ�ܺ���ʾС���㣬�����л���ʽ����)��  
//1��վ��ģʽ(��ʾվ�ţ�������ʾ����䶯)��  
//2������ģʽ(Ԥ��)��
//radix:�ư��������ʾ���ƣ� 0�������ƣ�  1���˽��ƣ�  2��ʮ���ƣ�  3��ʮ�����ƣ�
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_ReadLedDispalyMode(short cardIndex, short stationPhyId, unsigned char *pMode, unsigned char *pRadix);
//-------------------------------------------------------------------------------------------------------
//������ģ��LED��ʾģʽ
//GTN_RN_WriteLedDisplayMode(short cardIndex, short stationPhyId, unsigned char mode, unsigned char radix)
// mode:�ư��������ʾģʽ�� 
//0������ģʽ(�ϵ��ʼ״̬��ʾ�㣬��ʹ�ܺ���ʾС���㣬�����л���ʽ����)��  
//1��վ��ģʽ(��ʾվ�ţ�������ʾ����䶯)��  
//2������ģʽ(Ԥ��)��
//radix:�ư��������ʾ���ƣ� 0�������ƣ�  1���˽��ƣ�  2��ʮ���ƣ�  3��ʮ�����ƣ�
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_WriteLedDisplayMode(short cardIndex, short stationPhyId, unsigned char mode, unsigned char radix);
//-------------------------------------------------------------------------------------------------------
//�����ŷ�����
//GTN_RN_ExportServoParams(short cardIndex, short stationPhyId, short axis, char *pFilePath, char *pFileName)
// cardIndex:��1��ʼ
// stationPhyId:��0��ʼ
// axis:���
// pFilePath��ģ���ļ���·��
// pFileName���������ļ�·��������
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_ExportServoParams(short cardIndex, short stationPhyId, short axis, char *pFilePath, char *pFileName);
//-------------------------------------------------------------------------------------------------------
//�����ŷ�����
//GTN_RN_ImportServoParams(short cardIndex, short stationPhyId, short axis, char *pFilePath, char *pFileName)
// cardIndex:��1��ʼ
// stationPhyId:��0��ʼ
// axis:���
// pFilePath��ģ���ļ���·��
// pFileName���������ļ�·��������
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_ImportServoParams(short cardIndex, short stationPhyId, short axis, char *pFilePath, char *pFileName);

//��ȡ�������ֵ������
typedef struct 
{
    short stationId;
    short axis;
    uint64_t multiLines;
    double pos;
}StAbsEncPos;
GT_API GTN_RN_GetMultiAbsEncPos(short cardIndex,StAbsEncPos* pStAbsEncPos,short count);

//-------------------------------------------------------------------------------------------------------
// ���ñ�������Ȧ/��Ȧλ����Ŀǰ��402֧�֣�
// cardIndex������
// stationPhyId��վ��
// singleBitNum����Ȧ����ֵλ����Ŀǰ֧��25λ
// multiBitNum����Ȧ����ֵλ���� Ŀǰд0
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_SetAbsEncRange(short cardIndex, short stationPhyId, short singleBitNum, short multiBitNum);

//-------------------------------------------------------------------------------------------------------
// ���ñ�����������Ϣ
// cardIndex������
// stationPhyId��վ��
// encoder���������
// type����������
// 0����������Ȧ����
// 1������������״̬��
// 2��������Э������
// 3��������������Ϣ
// 4������������
// 5�������Ҳ�ֵ����
// 6����Ȧ���������λ��������
// pData:д������ݣ���ϸ˵����ο�ָ��˵��
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_SetEncoderInfo(short cardIndex, short stationPhyId, short encoder, short type, uint32_t *pData);

//-------------------------------------------------------------------------------------------------------
// ��ȡ������������Ϣ
// cardIndex������
// stationPhyId��վ��
// encoder���������
// type����������
// 0����������Ȧ����
// 1������������״̬��
// 2��������Э������
// 3��������������Ϣ
// 4������������
// 5�������Ҳ�ֵ����
// 6����Ȧ���������λ��������
// pData:��ȡ�����ݣ���ϸ˵����ο�ָ��˵��
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_GetEncoderInfo(short cardIndex, short stationPhyId, short encoder, short type, uint32_t *pData);

//-------------------------------------------------------------------------------------------------------
// ��ʼ��PC��DLL Buffer��С
// cardIndex:��1��ʼ
// stationPhyId:��0��ʼ
// bufferAddrWidth������DLL Buffer�Ŀռ��С
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_ScanCmpInitialWrBuffer(short cardIndex, short stationPhyId, unsigned short bufferAddrWidth);
//-------------------------------------------------------------------------------------------------------
// ��ȡ��ǰDLL Buffer�е���Ч�������ͻ��ж���ʣ��ռ����д��
// cardIndex:��1��ʼ
// stationPhyId:��0��ʼ
// pValidWordNum����ǰDLL Buffer���ж���word�ռ�����ݣ�û�з��͵���ģ��
// pRemainsWordSpase: ��ǰDLL Buffer���ж���word�ռ�����ݣ������û�д��
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_ScanCmpGetWrBufferStatus(short cardIndex, short stationPhyId, uint32_t *pValidWordNum, uint32_t *pRemainsWordSpase);
//-------------------------------------------------------------------------------------------------------
// ������д��DLL Buffer��
// cardIndex:��1��ʼ
// stationPhyId:��0��ʼ
// pData��Ҫд�������ָ��
// pWordNumVaild: ����д������ݵ�word�ĸ���
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_ScanCmpWrBufferData(short cardIndex, short stationPhyId, unsigned short *pData, uint32_t wordNum, uint32_t *pWordNumVaild);
//-------------------------------------------------------------------------------------------------------
// ������ģ���buffer״̬����DLL Buffer�е����ݶ�ȡ�����µ���ģ�黺������
// cardIndex:��1��ʼ
// stationPhyId:��0��ʼ
// dataType����Ҫѹ�뻺��������������: 0��SCAN�����������1��CMP��λ�ñȽ��������
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_ScanCmpUpdateBufferDataToFPGA(short cardIndex, short stationPhyId, short dataType);
//-------------------------------------------------------------------------------------------------------
// ʹ����ģ�黺������ʹ�ܺ���ģ���ָ�������ȡָ�ֻӦ�����񾵣�
// cardIndex:��1��ʼ
// stationPhyId:��0��ʼ
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_ScanEnableFifo(short cardIndex, short stationPhyId);
//-------------------------------------------------------------------------------------------------------
// �ر���ģ�黺�������رպ���ģ����ͣ�ӻ�������ȡָ�ֻӦ�����񾵣�
// cardIndex:��1��ʼ
// stationPhyId:��0��ʼ
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_ScanDisableFifo(short cardIndex, short stationPhyId);
//-------------------------------------------------------------------------------------------------------
// ���������ڲ�������ȡ��xml�ļ���
// cardIndex:		    ����
// stationPhyId:        վ��
// path:                ��Ҫд���xml�ļ�·��+����
// tpfUpdataProgressPt: �ص�������������¼��ȡ������xml�ļ�����
// ptrv:                �ص�����tpfUpdataProgressPt��һ������
// progress:            �ص�����tpfUpdataProgressPt�ڶ��������� ��ʾ����
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_UploadServoParaFile(short cardIndex, short stationPhyId, char *path, void(*tpfUpdataProgressPt)(void*, short*), void* ptrv, short& progress);
//-------------------------------------------------------------------------------------------------------
// ��xml�ļ�����д��������
// cardIndex:		    ����
// stationPhyId:        վ��
// path:                ��Ҫд���xml�ļ�·��+����
// tpfUpdataProgressPt: �ص�������������¼��ȡ������xml�ļ�����
// ptrv:                �ص�����tpfUpdataProgressPt��һ������
// progress:            �ص�����tpfUpdataProgressPt�ڶ��������� ��ʾ����
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_DownloadServoParaFile(short cardIndex,  short stationPhyId, char* path, void(*tpfUpdataProgressPt)(void*, short*), void* ptrv, short& progress);
//-------------------------------------------------------------------------------------------------------
// ��ȡ������������
// cardIndex:		    ����
// stationPhyId:        վ��
// progress:            ��ȡ���Ľ���,ȡֵ��Χ[0..100]
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_UpdateProgress(short cardIndex, short stationPhyId, unsigned short progress);

//��ȡ��ֹͣ��ϸ��Ϣ����
GT_API GTN_GetAxisStopInfo(short core,short axis,int32_t *pInfo,double *pPos,short count=1);
GT_API GTN_ClearAxisStopInfo(short core,short axis,short count=1);
GT_API GTN_SetAxisStopInfoMode(short core,short axis,short *pMode,short count);
GT_API GTN_GetAxisStopInfoMode(short core,short axis,short *pMode,short count);

typedef struct TPvtLinePrm
{
    short mode;  //������Чģʽ
    short smoothTimer;  //ƽ��ʱ��
    int32_t moveTime;  //�˶�ʱ��
    int32_t pad;       //����λ
    double synVel;   //�ϳ�Ŀ���ٶ�
    double synAcc;  //�ϳɼ��ٶ�
    double synJeck; //�ϳɼӼ��ٶ�
}TPvtLinePrm;
GT_API GTN_PvtLine(short core,short axisCount,short *moveAxis,int32_t *pos,TPvtLinePrm *pPrm);

GT_API GTN_GetTerminalLinkCount(short core,unsigned short *pTerminalLinkCount);


//-------------------------------------------------------------------------------------------------------
// ���ñ�����ID
// cardIndex:		����
// stationPhyId:    վ�ţ���0��ʼ
// regionId:        ��Ҫд��ı�����ID��ȡֵ��Χ[0..15]������֮ǰĬ��Ϊ240��
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_SetLocalHubID(short cardIndex, short stationPhyId, short regionId);

//-------------------------------------------------------------------------------------------------------
// ��ȡ������ID
// cardIndex:		����
// stationPhyId:    վ�ţ���0��ʼ
// pRegionId:       ��ȡ���ı�����ID��ȡֵ��Χ[0..15]
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_GetLocalHubID(short cardIndex, short stationPhyId, short *pRegionId);

//-------------------------------------------------------------------------------------------------------
// ����������hub��Ϣ
// cardIndex:		����
// stationPhyId:    վ�ţ���0��ʼ
// regionLocalId:   ���ñ�����ID��ȡֵ��Χ[0..15]
// pRegionID:       ���������д��ڵ���ID�� ȡֵ��Χ[0..15]
// regionNums:      ������������ĸ�����ȡֵ��Χ[0..16]
// comByteSize:     ������֮���ͨ���ֽ���(bytes)��ȡֵ��Χ[0..240]
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_SetMultiHubCfgInfo(short cardIndex, short stationPhyId, short regionLocalId, short* pRegionID, short regionNums, short comByteSize);

//-------------------------------------------------------------------------------------------------------
// ��ȡ������hub��Ϣ
// cardIndex:		����
// stationPhyId:    վ�ţ���0��ʼ
// pRegionLocalId:  ��ȡ������ID��ȡֵ��Χ[0..15]
// pRegionID:       ��ȡ�����д��ڵ���ID�� ȡֵ��Χ[0..15]
// pRegionNums:     ��ȡ��������ĸ�����ȡֵ��Χ[0..16]
// pComByteSize:    ��ȡ��֮���ͨ���ֽ���(bytes)��ȡֵ��Χ[0..240]
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_GetMultiHubCfgInfo(short cardIndex, short stationPhyId, short *pRegionLocalId, short* pRegionID, short* pRegionNums, short *pComByteSize);

//-------------------------------------------------------------------------------------------------------
// д���ݵ�Ŀ����
// cardIndex:		����
// stationPhyId:    վ�ţ���0��ʼ
// regionId:        д���Ŀ����ID��ȡֵ��Χ[0..15]
// pData:           д�������
// byteOffset:      д�����ݵĵ�ַƫ�ã���ֵΪ4�ı�����ȡֵ��Χ[0..240]
// byteNum:         Ҫд��������ֽ�������ֵΪ4�ı�����ȡֵ��Χ[0..240]
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_MultiHubPcComWr(short cardIndex, short stationPhyId, short regionId, unsigned char* pData, unsigned short byteOffset, unsigned short byteNum);

//-------------------------------------------------------------------------------------------------------
// ��Ŀ�����ȡ����
// cardIndex:		����
// stationPhyId:    վ�ţ���0��ʼ
// regionId:        д���Ŀ����ID��ȡֵ��Χ[0..15]
// pData:           д�������
// byteOffset:      д�����ݵĵ�ַƫ�ã���ֵΪ4�ı�����ȡֵ��Χ[0..240]
// byteNum:         Ҫд��������ֽ�������ֵΪ4�ı�����ȡֵ��Χ[0..240]
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_MultiHubPcComRd(short cardIndex, short stationPhyId, short regionId, unsigned char* pData, unsigned short byteOffset, unsigned short byteNum);

//-------------------------------------------------------------------------------------------------------
// ��ȡEeprom���ݡ�
// cardIndex:		����
// stationPhyId:    վ�ţ���0��ʼ
// ofst:            ��Ҫ��ȡ��Eeprom��ַ
// pValue:          ��ȡ����ֵ
// num:             ��Ҫ��ȡ�ĸ���
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_ReadEepromData(short cardIndex, short stationPhyId, unsigned short ofst, unsigned char* pValue, unsigned short num);

//-------------------------------------------------------------------------------------------------------
// д��Eeprom���ݡ�
// cardIndex:		����
// stationPhyId:    վ�ţ���0��ʼ
// ofst:            ��Ҫд���Eeprom��ַ
// pValue:          ��Ҫд���ֵ
// num:             ��Ҫд��ĸ���
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_WriteEepromData(short cardIndex, short stationPhyId, unsigned short ofst, unsigned char* pValue, unsigned short num);

//-------------------------------------------------------------------------------------------------------
// ��ȡ������Դ������Ϣ
// cardIndex:		����
// stationPhyId:    վ�ţ���0��ʼ
// slotInfo:        [15--8]��ʾ�忨���ͣ� 1: �װ壻2���Ӱ壻3��ͨѶ�� [7--0]��ʾ�忨��ţ��߰�λΪ1(�װ�)ʱ��ȡֵ��Χ 1���߰�λΪ2���Ӱ壩ʱ��ȡֵ��Χ[1..7]; �߰�λΪ3��ͨѶ�壩ʱ��ȡֵ��Χ 1
// mcDef:           ��Դ�궨�壬��ϸ˵���ο���¼I 
// pData:           ��ȡ������Դֵ��16λ��ֵ��
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_GetStationSlotResourceEx(short cardIndex, short stationPhyId, short slotInfo, short mcDef, unsigned short *pData);

GT_API GTN_RN_GetStationInfomation(short cardIndex, short stationPhyId, unsigned char infoType, unsigned char infoCount, uint32_t* pInfo);

//-------------------------------------------------------------------------------------------------------
// 500���������������л�����cpu��Ilinkģ�����Ȩ��Ĭ�ϴ�cpu�ɿأ���cpu��ģ�鷢����ʱ������Ȩ�л�����cpu
// cardIndex:		����
// stationPhyId:    վ�ţ���0��ʼ
// moduleId:        Ilinkģ��Id��ȡֵ��Χ[0..63]
// data:            д������ֵ��bit0����0��1��ת������10ms����ת����Ϊû����������
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_IlinkSetHeartbeat(short cardIndex, short stationPhyId, short moduleId, unsigned short data);

//-------------------------------------------------------------------------------------------------------
// 500��������CPUͨ��д
// cardIndex:		����
// stationPhyId:    վ�ţ���0��ʼ
// dataCount:       һ��ͨѶд���������������ȡֵ��Χ[1..256]dword
// data:            д�������
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_IlinkPcComWr(short cardIndex, short stationPhyId, unsigned short dataCount, uint32_t* data);

//-------------------------------------------------------------------------------------------------------
// 500��������CPUͨ�Ŷ�
// cardIndex:		����
// stationPhyId:    վ�ţ���0��ʼ
// dataCount:       һ��ͨѶ��ȡ��������������ȡֵ��Χ[1..256]dword
// data:            ��ȡ��������
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_IlinkPcComRd(short cardIndex, short stationPhyId, unsigned short dataCount, uint32_t* data);

//-------------------------------------------------------------------------------------------------------
// 	��ȡ����������Դ������Ϣ
// cardIndex:		����
// stationPhyId:    վ�ţ���0��ʼ
// pData:           ��ȡ������Դ������Ϣ
// dataCount:       ��Ҫ��ȡ����Դ������Ϣ����
// pResCount:       ʵ�ʻ�ȡ����Դ������Ϣ����
// slotInfo:        [15--8]��ʾ�忨���ͣ�
//  1: �װ壻2���Ӱ壻3��ͨѶ��
//	[7--0]��ʾ�忨��ţ�
//	�߰�λΪ1(�װ�)ʱ��ȡֵ��Χ 1��
//	�߰�λΪ2���Ӱ壩ʱ��ȡֵ��Χ[1..7];
//  �߰�λΪ3��ͨѶ�壩ʱ��ȡֵ��Χ 1
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_GetStationSlotResource(short cardIndex, short stationPhyId, uint32_t* pData, short dataCount, short* pResCount, short slotInfo);

GT_API GTN_RN_WriteResourceTable(short cardIndex, uint32_t *pResDef, short count, char* pData, short* pDataSize);
//-------------------------------------------------------------------------------------------------------
// �����˲���������
// cardIndex:		    ����
// stationPhyId:        վ��
// fltLength:           ����ƽ���˲�������Ĭ��ֵ100�����㷽ʽ��fltLength = 0.443*����Ƶ��/��ֹƵ��
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_SamplingFilterSet(short cardIndex, short stationPhyId, short fltLength);

//-------------------------------------------------------------------------------------------------------
// �����˲�������ȡ
// cardIndex:		    ����
// stationPhyId:        վ��
// fltLength:           ��ȡ���Ļ���ƽ���˲�������Ĭ��ֵ100�����㷽ʽ��fltLength = 0.443*����Ƶ��/��ֹƵ��
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_SamplingFilterGet(short cardIndex, short stationPhyId, short *pFltLength);

//-------------------------------------------------------------------------------------------------------
// PC������������˿�
// cardIndex:		    ����
// callBackFun:         �ص�����
// pParamA:             �ص�����������NULL
//-------------------------------------------------------------------------------------------------------
typedef short (*FunCallBack)(void*, int32_t, void*);
GT_API GTN_RN_InitialUserCallBack(short cardIndex,FunCallBack callBackFun, void* pParamA);

//-------------------------------------------------------------------------------------------------------
// PCͨѶд����
// cardIndex:		    ����
// phyStationId:        PCͨѶʱ����Ҫ���ͶԶ˵�ID��������Ͷ�λPC�ˣ�id��ȡֵ��Χ[0,31]��������Ͷ�Ϊ�������ˣ�id=0xF2
// pData:               �ص�����������NULL
// byteNum��            PCͨ���ֽ�����ȡֵ��Χ[0,240]
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_UserOverRnWrite(short cardIndex, short phyStationId, unsigned char* pData, int32_t byteNum);

//-------------------------------------------------------------------------------------------------------
// дphy�Ĵ�����ֵ
// cardIndex:		    ����
// stationPhyId:        վ��
// phyIndex:            phyоƬ������ȡֵ��Χ[1..2]
// phyAddr:             phyоƬ��ַ�� ȡֵ0
// regAddr:             phy�Ĵ�����ַ
// data:               Ҫд��Ĵ�������ֵ
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_WritePhyRegValue(short cardIndex, short stationPhyId, short phyIndex, short phyAddr, short regAddr, short data);

//-------------------------------------------------------------------------------------------------------
// ��phy�Ĵ�����ֵ
// cardIndex:		    ����
// stationPhyId:        վ��
// phyIndex:            phyоƬ������ȡֵ��Χ[1..2]
// phyAddr:             phyоƬ��ַ�� ȡֵ0
// regAddr:             phy�Ĵ�����ַ
// pData:               ��ȡ���ļĴ���ֵ
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_ReadPhyRegValue(short cardIndex, short stationPhyId, short phyIndex, short phyAddr, short regAddr, short* pData);

//-------------------------------------------------------------------------------------------------------
// ��phy�Ĵ�����ֵ
// cardIndex:		    ����
// stationPhyId:        վ��
// phyIndex:            phyоƬ������ȡֵ��Χ[1..2]
// pData:               ��ȡ��״ֵ̬ �����ݶ���Ϊ��
//                      [15]=wr_active/wr_ing(1��ʾ����д����)  
//                      [12:8]=reg_addr(�Ĵ�����ַ)  
//                      [7]=rd_active/rd_ing(1��ʾ���ڶ�����)  
//                      [4:0]=phy_addr(phyоƬ��ַ)
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_ReadPhySts(short cardIndex, short stationPhyId, short phyIndex, short* pData);

//-------------------------------------------------------------------------------------------------------
// ��ʼ����
// cardIndex:          ����
// stationPhyId:        վ��
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_ScanInitial(short cardIndex, short stationPhyId);

// ����������״�ṹ�壺 
typedef struct {
    unsigned short type;        //����������0 : ֱ��1 : Բ��  
    unsigned short closewise;  //Բ�����򣬽�Բ��ʹ��  
    uint32_t cutEnable;    //�Ƿ��и0: ���и1:�и�  
    double targetPosX;          //X��Ŀ��λ�ã���λmm  
    double targetPosY;          //Y��Ŀ��λ�ã���λmm  
    double circleCenterX;       //Բ������X�����꣬��λmm (��Բ��ʹ��) 
    double circleCenterY;       //Բ������Y�����꣬��λmm(��Բ��ʹ��) 
}StBatteryTargetSegment;

#define MAX_SEGMENT_NUM (100)  
typedef struct {
    unsigned short segmentNum;//һ�������Ĺ��ɶ���  
    unsigned short cycleNum;//���ٸ���������һ����ѭ��  
    StBatteryTargetSegment batteryTargetSegment[MAX_SEGMENT_NUM];//����ÿһ��������Ϣ  
    double segmentIncreaseX[MAX_SEGMENT_NUM]; //��λmm--��n+1�������͵�n��������ÿһ���岹�ε�x����仯������������ǹ̶����䣬���ֵΪ0�� 
    double segmentIncreaseY[MAX_SEGMENT_NUM]; //��λmm--��n+1�������͵�n��������ÿһ���岹�ε�y����仯������������ǹ̶����䣬���ֵΪ0�� 
}StScanShape;

//-------------------------------------------------------------------------------------------------------
// ����������״
// cardIndex:          ����
// stationPhyId:        վ��
// pParam:             ����������״�ṹ��
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_ScanBatteryShape(short cardIndex, short stationPhyId, StScanShape* pParam);

typedef struct {
    int32_t encAxisSrc; //�����������ģ�����һ�����ϣ�0��X�᣻1��Y�ᡣ              
    int32_t prfEncSel;//����Դѡ��0��ʹ�ñ�������Ϊ����Դ��1��ʹ�ù滮����Ϊ����Դ��             
    double encPulsePreDistance;  //ʵ�ʼ���mm��Ӧ���������������(pulse/mm),����������Ϊ��Ƶ��ġ�             
    double scanPulsePreDistance;  //ʵ�ʼ���mm��Ӧ����������bit/mm�� 
} StScanBatteryParam;

//-------------------------------------------------------------------------------------------------------
// ��������ز���
// cardIndex:          ����
// stationPhyId:        վ��
// pParam:             ����������״�ṹ��
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_SetScanBatteryParam(short cardIndex, short stationPhyId, StScanBatteryParam* pParam);

//-------------------------------------------------------------------------------------------------------
// ��ȡ����ز���
// cardIndex:          ����
// stationPhyId:        վ��
// pParam:             ����������״�ṹ��
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_GetScanBatteryParam(short cardIndex, short stationPhyId, StScanBatteryParam* pParam);

//�����Բ��������ڽ���񾵰�װ����������������⣺ 
typedef struct {
    unsigned short followMode : 1;    //����ģʽ��0���񾵰����趨�ٶ��˶���1���񾵰��ո������ٶ��˶�  
    unsigned short followAxisSel : 1; //�񾵸�����ѡ��0��X�᣻ 1��Y��  
    unsigned short reserveBit2 : 1;  
    unsigned short fdbackReverse : 1;  //�����и�ĺϳ��˶�����ʼ�㿪ʼ�˶��ķ�����X���������Ǹ���1������0������ 
    unsigned short axisXReverse : 1;  //����axi_src_sel��axi_x_selѡ���X����ʵ�����������෴����ȡ��������ȡ���� 
    unsigned short axisYReverse : 1;  //����axi_src_sel��axi_x_selѡ���Y����ʵ�����������෴����ȡ��������ȡ����
    unsigned short reserveBit7to6 : 2;   
    unsigned short scanXReverse : 1; //�񾵵�X�ᰲװ�Ƿ��ʵ�����������෴��1��ȡ����0����ȡ���� 
    unsigned short scanYReverse : 1; //�񾵵�Y�ᰲװ�Ƿ��ʵ�����������෴��1��ȡ����0����ȡ���� 
    unsigned short scanZReverse : 1; //�񾵵�Z�ᰲװ�Ƿ��ʵ�����������෴��1��ȡ����0����ȡ���� 
    unsigned short scanXYSwitch : 1; //�񾵵�XY����Ƿ�Ҫ������1��������0����������  
    unsigned short scanBXReverse : 1;  //�����񾵵�X�ᰲװ�Ƿ��ʵ�����������෴��1��ȡ����0����ȡ����  
    unsigned short scanBYReverse : 1;  //�����񾵵�Y�ᰲװ�Ƿ��ʵ�����������෴��1��ȡ����0����ȡ���� 
    unsigned short scanBZReverse : 1;  //�����񾵵�Z�ᰲװ�Ƿ��ʵ�����������෴��1��ȡ����0����ȡ���� 
    unsigned short scanBXYSwitch : 1;  //�����񾵵�XY����Ƿ�Ҫ������1��������0���������� 
}StScanAttributeCfg;

//-------------------------------------------------------------------------------------------------------
// ����������
// cardIndex:          ����
// stationPhyId:        վ��
// pParam:             �����Բ���
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_SetScanAttribute(short cardIndex, short stationPhyId, StScanAttributeCfg* pParam);

//-------------------------------------------------------------------------------------------------------
// ��ȡ������
// cardIndex:          ����
// stationPhyId:        վ��
// pParam:             �����Բ���
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_GetScanAttribute(short cardIndex, short stationPhyId, StScanAttributeCfg* pParam);

//-------------------------------------------------------------------------------------------------------
// ����������״
// cardIndex:          ����
// stationPhyId:        վ��
// type:               �񾵹켣���ͣ� 1��������  2��������
// pParam:             ������дNULL
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_ScanShapeType(short cardIndex, short stationPhyId, uint32_t type, StScanShape* pParam = NULL);

//-------------------------------------------------------------------------------------------------------
// �����񾵹���ģʽ
// cardIndex:          ����
// stationPhyId:        վ��
// mode:               0������ģʽ����ͣ��ǰ����ִ�еĳ��� 1������ģʽ�������ڹ���״̬ 2����λģʽ����λ�����й���״̬��
// pParam:             ������дNULL
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_GetScanBatteryMode(short cardIndex, short stationId, uint32_t* pMode, void* pParam = NULL);

//-------------------------------------------------------------------------------------------------------
// ��ȡ�񾵹���ģʽ
// cardIndex:          ����
// stationPhyId:        վ��
// mode:               0������ģʽ����ͣ��ǰ����ִ�еĳ��� 1������ģʽ�������ڹ���״̬ 2����λģʽ����λ�����й���״̬��
// pParam:             ������дNULL
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_SetScanBatteryMode(short cardIndex, short stationPhyId, uint32_t mode, void* pParam = NULL);

//-------------------------------------------------------------------------------------------------------
// �����������ķֱ���
// cardIndex:          ����
// stationPhyId:       վ��
// axis:               ���
// resolution:         ���תnȦ��Ӧ���ٸ�����
// n:                  ���ת��Ȧ��
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_WriteFollowResolution(short cardIndex, short stationPhyId, short axis, uint32_t resolution, unsigned short n);

//-------------------------------------------------------------------------------------------------------
// �����Ƿ���ȫ�ջ�
// cardIndex:          ����
// stationPhyId:       վ��
// axis:               ���
// en:                 �Ƿ���ȫ�ջ���0���ر�ȫ�ջ���1������ȫ�ջ�
// assoPosErr:         �Ƿ����������0������������
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_EnablePosCloseLoop(short cardIndex, short stationPhyId, short axis, bool en, bool assoPosErr);



/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*                        EtherCAT����Э�鹦�ܺ���		                    */
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

//EtherCAT
#define ECAT_STATE_OP    (2)

#define ECAT_AXIS_MAX		12
#define ECAT_MODE_HOMING	6
#define ECAT_MODE_CSP		8
#define ECAT_MODE_CSV		9
#define ECAT_MODE_CST		10
#define ECAT_MODE_PV		3
#define ECAT_MODE_PT		4

#define ECAT_PROBE_TRIGGER_TYPE_FIRST_EVENT	0
#define ECAT_PROBE_TRIGGER_TYPE_CONTINUES	1

#define ECAT_PROBE_TRIGGER_LEVEL_POS		1
#define ECAT_PROBE_TRIGGER_LEVEL_NEG		-1
#define ECAT_PROBE_TRIGGER_LEVEL_DUL		0

#define  ECAT_ACT_ENC_POS	0
#define  ECAT_ACT_ENC_VEL	1
#define  ECAT_ACT_CURRENT	2
#define  ECAT_ACT_TORQUE	3
#define  ECAT_ACT_CT		4

#define ERROR_CODE_NO_SLAVE		-10
#define ERROR_CODE_NO_ENI		-9
#define ERROR_CODE_CONFIG_FAIL	-8
#define ERROR_CODE_ENI_ERROR	-1

typedef struct
{
    int32_t slave_cnt;
    int32_t slave_type;
    int32_t motion_cnt;
    int32_t io_nmap;
    int32_t io_length;
    uint32_t Vid;
    uint32_t Pid;
    int io_type;             //1 ����  2 ���  3 �������
    int dump[10];
} TSlaveInfo;

typedef struct
{
    short dcError; 
    short workingCountErrorCnt; //���ֶ��߼���
    short ecatCommStatus;      //����ͨѶ״̬
    short workingCount;        //��ǰWorkingCountֵ
    short offlineFlag;         //���߱�־
    short rootOfflineFlag;    //�������߱�־
    short workingCountFirstError;  //���ֶ���ʱ�ļ���
    short profileTimeOutFlag;      //�滮��ʱ��־
    short dump[20];
} TEcatErrInfo;

//EtherCAT interface
// ����Home������������ָ��Ϊ�գ�����Ҫ��sdoָ�� [Thunder-2020-9-24]
GT_API GTN_SetEcatHomingPrmPro( short core, short axis,short method,double speed1,double speed2,double acc,int32_t offset,unsigned short probeFunction,unsigned short mask);
GT_API GTN_SetEcatHomingPrmEx( short core, short axis,short *psMethod,double *pdSpeed1,double *pdSpeed2,double *pdAcc,int32_t *plOffset,unsigned short *pusProbeFunction );
GT_API GTN_SetEcatHomingPrm(short core,short axis,short method,double speed1,double speed2,double acc,int32_t offset,unsigned short probeFunction);
GT_API GTN_StartEcatHoming(short core,short axis);
GT_API GTN_SetHomingMode(short core,short axis,short mode);
GT_API GTN_GetEcatHomingStatus(short core,short axis,unsigned short *homingStatus);
GT_API GTN_StopEcatHoming(short core,short axis);
GT_API GTN_SetTouchProbeFunction(short core,short axis,short ProbePrm);
GT_API GTN_SetTouchProbeFunctionEx(short core,short axis,short Probe1Enable,short Probe1TriggerType,short Probe1TriggerLevel,short Probe2Enable,short Probe2TriggerType,short Probe2TriggerLevel);
GT_API GTN_GetTouchProbeStatus(short core,short axis,unsigned short *probeStatus,int32_t *probe1PosValue,int32_t *probe1NegValue,int32_t *probe2PosValue,int32_t *probe2NegValue);
GT_API GTN_SetEcatGpioConfig(short core,short effectiveLevel,short direction);
GT_API GTN_SetEcatAxisOnThreshold(short core,short axis,unsigned short threshold);
GT_API GTN_GetEcatAxisOnThreshold(short core,short axis,unsigned short* threshold);
GT_API GTN_InitEcatComm(short core);
GT_API GTN_InitEcatCommEx(short core,char *eniFilePath);
GT_API GTN_StartEcatComm(short core);
GT_API GTN_IsEcatReady(short core,short *pStatus);
GT_API GTN_TerminateEcatComm(short core);
GT_API GTN_GetEcatErrorCode(short core,short axis,unsigned short *pErrorCode);
GT_API GTN_GetDcError(short core,short *pError);
GT_API GTN_GetEcatDcErrorEx(short core,TEcatErrInfo *pEcatErrorInfo);
GT_API GTN_SetEcatAxisMode(short core,short axis,short mode);
GT_API GTN_GetEcatAxisMode(short core,short axis,unsigned short *drvMode);
GT_API GTN_SetEcatAxisPV(short core,short axis,int32_t velocity);
GT_API GTN_SetEcatAxisPT(short core,short axis,short torque);
GT_API GTN_GetEcatEncPos(short core,short axis,int32_t *pEncPos);
GT_API GTN_GetEcatAuxEncPos(short core,short axis,int32_t *pAuxEncPos);
GT_API GTN_GetEcatEncVel(short core,short axis,int32_t *pVelocity);
GT_API GTN_GetEcatAxisAtlCurrent(short core,short axis,short *pCur);
GT_API GTN_GetEcatAxisAtlTorque(short core,short axis,short *pTorque);
GT_API GTN_GetEcatAxisAV(short core,short axis,int32_t *pVel);
GT_API GTN_GetEcatAxisACT(short core,short axis,short *pCur,short *pTorque);
GT_API GTN_GetEcatMCType(short core,short *pType);
GT_API GTN_SetMcEcatAxisNum(short core,short Num);
GT_API GTN_GetMcEcatAxisNum(short core,short *pNum);
GT_API GTN_SetPosScale(short core,short axis,unsigned short posScale);
GT_API GTN_GetPosScale(short core,short axis,unsigned short *posScale);
GT_API GTN_GetEcatAxisAI(short core,short axis,short channel,short *pValue);
GT_API GTN_SetEcatAxisAO(short core,short axis,unsigned short AoValue);
GT_API GTN_GetEcatAxisAO(short core,short axis,unsigned short *pAo);
GT_API GTN_GetEcatAxisDI(short core,short axis,uint32_t *pDi);
GT_API GTN_GetEcatAxisDIEx(short core,short axis,uint32_t *pDi,short count);
GT_API GTN_SetEcatAxisDO(short core,short axis,uint32_t DoValue);
GT_API GTN_GetEcatAxisDO(short core,short axis,uint32_t *pDo);
GT_API GTN_SetEcatAxisDOBit(short core,short axis,short bitOffset,char DoBitValue);
GT_API GTN_GetEcatAxisDOBit(short core,short axis,short bitOffset,char *pDoBitValue);
GT_API GTN_GetEcatSlaves(short core,short *pSlaveMotionCnt,short *pSlaveIOCnt);
GT_API GTN_GetEcatSlaveInfo(short core,short slaveIndex,TSlaveInfo *pSlaveinfo);
GT_API GTN_GetEcatAxisPE(short core,short axis,int32_t *pPosErr);
GT_API GTN_SetEcatRawData(short core,unsigned short offset,unsigned short nByteSize,unsigned char *pValue);
GT_API GTN_GetEcatRawData(short core,unsigned short offset,unsigned short nByteSize,unsigned char *pValue);
GT_API GTN_SetEcatAxisTorqueOffset(short core,short axis,short torqueOffset);
GT_API GTN_GetEcatAxisTorqueOffset(short core,short axis,short *pTorqueOffset);
GT_API GTN_GetEcatPdoLength(short core,short *pPdoLen);
GT_API GTN_EcatSDODownload(short core,unsigned short slave_position,unsigned short index,unsigned char subindex,unsigned char *data,unsigned int data_size,unsigned int *abort_code);
GT_API GTN_EcatSDOUpload(short core,unsigned short slave_position,unsigned short index,unsigned char subindex,unsigned char *target,unsigned int target_size,unsigned int *result_size,unsigned int *abort_code);
GT_API GTN_EcatSDODownloadEx(short core,unsigned short axisNumber,unsigned short index,unsigned char subindex,unsigned char *data,unsigned int data_size,unsigned int *abort_code);
GT_API GTN_EcatSDOUploadEx(short core,unsigned short axisNumber,unsigned short index,unsigned char subindex,unsigned char *target,unsigned int target_size,unsigned int *result_size,unsigned int *abort_code);
GT_API GTN_EcatIOReadInput(short core,unsigned short slaveno,unsigned short offset,unsigned short nSize,unsigned char *pValue);
GT_API GTN_EcatIOReadOutput(short core,unsigned short slaveno,unsigned short offset,unsigned short nSize,unsigned char *pValue);
GT_API GTN_EcatIOWriteOutput(short core,unsigned short slaveno,unsigned short offset,unsigned short nSize,unsigned char *pValue);
GT_API GTN_EcatIOBitReadInput(short core,unsigned short slaveno,unsigned short offset,unsigned short Index,unsigned char *pValue);
GT_API GTN_EcatIOBitReadOutput(short core,unsigned short slaveno,unsigned short offset,unsigned short Index,unsigned char *pValue);
GT_API GTN_EcatIOBitWriteOutput(short core,unsigned short slaveno,unsigned short offset,short Index,unsigned char value);
GT_API GTN_EcatIOSynch(short core);
GT_API GTN_EcatIOUpdateUpload(short core);
GT_API GTN_EcatIOUpdateDnload(short core);
GT_API GTN_GetEcatAxisPdoData(short core,short axis,unsigned short object,unsigned char *pValue);
GT_API GTN_SetEcatSlaveObjectData(short core,short slaveIndex,unsigned short object,unsigned short objectSubIndex,unsigned char *pValue,unsigned int data_size,unsigned char *pOpMode);
GT_API GTN_GetEcatSlaveObjectData(short core,short slaveIndex,unsigned short object,unsigned short objectSubIndex,unsigned char *pValue,unsigned int data_size,unsigned char *pOpMode);

typedef struct 
{
    unsigned short skip_count;
	unsigned short netOpenSts;
	unsigned short *slave_position;
	char *eniFilePath;
	unsigned short reserve2[20];
}TEcatInitPrm;

GT_API GTN_InitEcatComm_MultiTask(short core,TEcatInitPrm *pPrm);
GT_API GTN_InitEcatComm_PhysicalID(short core);

// ������CSVģʽ�£�Ŀ���ٶ�60ff�����ֵ����λ������60ff��λ[Thunder-2019-10-11]
GT_API GTN_SetEcatAxisMaxTargetVel(short core,short axis,uint32_t targetMaxVel);
GT_API GTN_GetEcatAxisMaxTargetVel(short core,short axis,uint32_t *targetMaxVel);

//�����Զ����˶�����0x6040�ĸ�8λʱ������8λ��ֵ����ָ��ڲ��͵�8λλ������
GT_API GTN_SetEcatAxisCtrlwordEx(short core,short axis,unsigned short ctrlex);
GT_API GTN_GetEcatAxisCtrlwordEx(short core,short axis,unsigned short *ctrlex);

GT_API GTN_SetEcatAxisLmtHomeIndex(short core,short axis,short index_LimitN,short index_LimitP,short index_Home);
GT_API GTN_GetEcatAxisLmtHomeIndex(short core,short axis,short *index_LimitN,short *index_LimitP,short *index_Home);
GT_API GTN_RelateEcatIOSlaveToMCIOModule(short core,short slaveindex,short IOModuleindex);
GT_API GTN_SetMCIOModuleValue(short core,short IOModuleindex,short iomapindex,int32_t *val,short cnt);
GT_API GTN_GetMCIOModuleValue(short core,short IOModuleindex,short iomapindex,int32_t *val,short cnt);

// ��������ռλ���ָ��
GT_API GTN_InitMcAxisGap(short core);
GT_API GTN_SetMcAxisGap(short core,short axis,short count);
GT_API GTN_GetMcAxisGap(short core,short axis,short *actualAxisNo,short count);
GT_API GTN_RelateEcatSlaveToMcAuEncoder(short core,short auenc,short ecatAxisIndex);
GT_API GTN_RelateEcatSlaveToMcMpgEncoder(short core,short mpg,short ecatAxisIndex);
GT_API GTN_RelateEcatSlaveToMcAuEncoderEx(short core,short auenc,short ecatIndex,short ecatType,short pdoOffset,short pdoByteLength);
GT_API GTN_RelateEcatSlaveToMcMpgDi(short core,short mpg,short ecatAxisIndex,short bitoffset);
GT_API GTN_RelateEcatSlaveToMcMpgDiEx(short core,short mpg,short ecatIndex,short ecatType,short bitoffset,short pdoOffset);
GT_API GTN_RelateEcSlvToMcAuEnc(short core,short auenc,short ecatAxisIndex);         //CPAC�������ƹ���
GT_API GTN_RelateEcSlvToMcMpgEnc(short core,short mpg,short ecatAxisIndex);
GT_API GTN_RelateEcatSlaveToMcMpgEncoderEx(short core,short mpg,short ecatIndex,short ecatType,short pdoOffset,short pdoByteLength);
GT_API GTN_RelateEcatSlaveToMcAdc(short core,short adc,short ecatIndex,short ecatType,short pdoOffset,short pdoByteLength);
GT_API GTN_RelateEcatSlaveToMcAuAdc(short core,short auadc,short ecatIndex,short ecatType,short pdoOffset,short pdoByteLength);
GT_API GTN_RelateEcatSlaveToMcGpiBit(short core,short gpi,short ecatIndex,short ecatType,short bitoffset,short pdoOffset);
GT_API GTN_RelateEcatSlaveToMcGpoBit(short core,short gpo,short ecatIndex,short ecatType,short bitoffset,short pdoOffset);
GT_API GTN_LoadRelateEcatSlaveConfig(short core,char *pFile);
GT_API GTN_RelateEcatSlaveToMcDac(short core,short dac,short ecatIndex,short ecatType,short pdoOffset,short pdoByteLength);
GT_API GTN_RelateEcatSlaveToMcAuDac(short core,short auDac,short ecatIndex,short ecatType,short pdoOffset,short pdoByteLength);
GT_API GTN_GetMcRelateEcatSlaveInfo(short core,short mcType,short index,short *pEcatIndex,short *pEcatType,short *pPdoOffset,short *pBitoffset,short *pdPoByteLength);
GT_API GTN_GetAxisModuleInfo(short core,short axis,short *pModule,short *pSubAxis);

typedef void(* TCallbackFunction)(const short data[512],void *pUserDataBack);
GT_API GTN_SetCallbackFunctionParameter(short core,TCallbackFunction callbackFunction);
GT_API GTN_StopCallbackFunction(short core);
GT_API GTN_RegisterCallbackFunction(short core,TCallbackFunction callbackFunction,void *pUserData=NULL);

GT_API GTN_RN_ReadEEPROM(short cardIndex, short stationPhyId, short axis, unsigned short ofst, unsigned char* pValue, unsigned short num);
GT_API GTN_RN_WriteEEPROM(short cardIndex, short stationPhyId, short axis, unsigned short ofst, unsigned char* pValue, unsigned short num);
GT_API GTN_RN_ResetServoDSP(short cardIndex, short stationPhyId, short axis);
GT_API GTN_ResetServoDSP(short core, short axis);
GT_API GTN_RN_WriteSetId(short cardIndex, short stationPhyId, short setId);
GT_API GTN_RN_ReadSetId(short cardIndex, short stationPhyId, short *pSetId);
GT_API GTN_RN_DisableSetId(short cardIndex, short stationPhyId);
GT_API GTN_RN_FORWrite(short cardIndex,short stationPhyId, short* pData, uint32_t dataCount, uint32_t* pDataCount, char* pFileName);
GT_API GTN_RN_SetStationSlotResourceEx( short cardIndex, short stationPhyId, char* pFileName, short slotInfo);
GT_API GTN_GetCoreInfo(short cardIndex, short* pCoreIndex, short* pCoreCount, short* pCoreValidFlag, short cardCount);

typedef struct
{
    short resType;//ʵ����Դ����
    short resIndex;//ʵ����Դ���
    //short mapType;
    short mapIndex;
    short mapCount;
} TResTypeMapInfo;

typedef struct
{
    short resMapType;//�߼���Դ����
    short resMapCount;//�߼���Դ����
    TResTypeMapInfo resmapInfo[64];//ÿ����Դ�����resMap����
} TTerminalResMapInfo;

typedef struct
{
    short netType;
    unsigned short terminalType;
    unsigned short terminalSubType;
    short phyId;
    short slotCount;
    unsigned short slotType[16];
    unsigned short slotSubType[16];	           //��ǰվÿ�����������Ӱ�������ͣ�û��Ĭ��Ϊ0
    short stationResMapCount;
    TTerminalResMapInfo terminalResMapInfo[64];//ÿ��վ�������Դ����
} TTerminalInfo;
GT_API GTN_GetTerminalInfo(short core,short index,TTerminalInfo *pTerminalInfo);

/*-----------------------------------------------------------*/
/* RemoteChannel                                             */
/*-----------------------------------------------------------*/

#define RING_NET_PDU_FAST_LINK_TYPE_NONE                   (0)
#define RING_NET_PDU_FAST_LINK_TYPE_REMOTE_AU_ENCODER      (1)
#define RING_NET_PDU_FAST_LINK_TYPE_POS_COMPARE_LINEAR     (2)

typedef struct
{
    short stationPhyId;
    short index;
    short type;
} TRemoteChannelPrm;

typedef struct
{
    short enableFlag;
    short occupy;
    short type;
    short index;
    short lastReceiveError;
    short lastSendError;
    unsigned short errorCount;
    unsigned short continueErrorCount;
} TRemoteChannelInfo;

GT_API GTN_GetRemoteChannelResult(short core,double *pValue,short channelIndex,short channelCount);
GT_API GTN_GetRemoteChannelInfo(short core,TRemoteChannelInfo *pInfo,short channelIndex,short channelCount);
GT_API GTN_GetRemoteChannelPrm(short core,TRemoteChannelPrm *pPrm,short channelIndex,short channelCount);
GT_API GTN_SetRemoteChannelPrm(short core,TRemoteChannelPrm *pPrm,short *pChannelIndex,short channelCount);
GT_API GTN_ClearRemoteChannel(short core,short channelIndex,short channelCount);
//---------------------------------------------------------
// LaserPro
//---------------------------------------------------------

// �����ģʽ
#define LASER_ON_MODE_DEFAULT                    (0)

// ����ر�ģʽ
#define LASER_OFF_MODE_POWER_OFF                 (0)  // ����ر�ʱ������Ҳ�ر�
#define LASER_OFF_MODE_POWER_HOLD                (1)  // ����ر�ʱ������������������ֵ

// ������������ģʽ
#define LASER_FOLLOW_MODE_NONE                   (0)  // δ������������
#define LASER_FOLLOW_MODE_RATIO                  (1)  // ������ϵ��������������
#define LASER_FOLLOW_MODE_TABLE                  (2)  // �����������������������
#define LASER_FOLLOW_MODE_DUO_TABLE              (3)  // ˫����������

#define LASER_FOLLOW_POWER_TYPE_DUTY             (0)
#define LASER_FOLLOW_POWER_TYPE_FREQUENCY        (1)
#define LASER_FOLLOW_POWER_TYPE_PULSE_WIDTH      (2)
#define LASER_FOLLOW_POWER_TYPE_VOLTAGE          (3)
#define LASER_FOLLOW_POWER_TYPE_PARALLEL         (4)

// ������������ϳ��ٶ�Դ
#define LASER_FOLLOW_SYNCH_VEL_SOURCE_PROFILE              (0)
#define LASER_FOLLOW_SYNCH_VEL_SOURCE_ENCODER              (1)

typedef struct
{
    short laserOn;                               // ���⿪�ع��ź�
    short laserEnable;                           // ������Ԥʹ���ź�
    short laserRed;                              // ���������ָʾ�ź�
    short laserPowerLatch;                       // ���������������ź�
    double duty;                                 // ��ǰPWM��ռ�ձ�ֵ����λ��%
    double frequency;                            // ��ǰPWM��Ƶ��ֵ����λ��kHz
    double pulseWidth;                           // ��ǰPWM������ֵ����λ��us
    double voltage;                              // ��ǰ����ģ����ֵ����λ��V
    double parallel;                             // ��ǰ���Ⲣ������ֵ
}TLaserPowerPro;

typedef struct
{
    short laserOn;                               // ���⿪�ع��ź�
    short laserEnable;                           // ������Ԥʹ���ź�
    short laserRed;                              // ���������ָʾ�ź�
    short laserPowerLatch;                       // ���������������ź�
    double duty;                                 // ��ǰPWM��ռ�ձ�ֵ����λ��%
    double frequency;                            // ��ǰPWM��Ƶ��ֵ����λ��kHz
    double pulseWidth;                           // ��ǰPWM������ֵ����λ��us
    double voltage;                              // ��ǰ����ģ����ֵ����λ��V
    double parallel;                             // ��ǰ���Ⲣ������ֵ

    double minDuty;                              // ռ�ձ�����������Сֵ��ȡֵ��Χ��[0,100]����λ��%
    double maxDuty;                              // ռ�ձ������������ֵ��ȡֵ��Χ��[0,100]����λ��%
    double minFrequency;                         // Ƶ������������Сֵ��ȡֵ��Χ��[0,1562.5]����λ��kHz
    double maxFrequency;                         // Ƶ�������������ֵ��ȡֵ��Χ��[0,1562.5]����λ��kHz
    double minPulseWidth;                        // ��������������Сֵ��ȡֵ��Χ��[0,65535]����λ��us
    double maxPulseWidth;                        // ���������������ֵ��ȡֵ��Χ��[0,65535]����λ��us
    double minVoltage;                           // ����ģ������ѹ��Сֵ��ȡֵ��Χ��[0,10]����λ��V
    double maxVoltage;                           // ����ģ������ѹ���ֵ��ȡֵ��Χ��[0,10]����λ��V
    double minParallel;                          // ���Ⲣ��������Сֵ��ȡֵ��Χ��[0,255]
    double maxParallel;                          // ���Ⲣ���������ֵ��ȡֵ��Χ��[0,255]

    double laserOnDelay;                         // ���⿪����ʱʱ�䣬��λ��us
    double laserOffDelay;                        // ����ع���ʱʱ�䣬��λ��us
}TLaserPro;

typedef struct
{
    short powerType;                             // ������������������ź����ͣ�0��ռ�ձȣ�1��Ƶ�ʣ�2��������3��ģ������4������
    short group;                                 // �������������group��
    short source;                                // ������������ϳ��ٶ�Դ��0���滮���ϳ��ٶȣ�1���������ϳ��ٶ�
    short coordSystem;                           // ������������ϳ��ٶȵ�����ϵ
    double ratio;                                // ���������������ϵ��
    double minPower;                             // ������������������С����ֵ
    double maxPower;                             // �����������������������ֵ
}TLaserFollowPrmPro;

typedef struct
{
    short powerType;                             // ������������������ź����ͣ�0��ռ�ձȣ�1��Ƶ�ʣ�2��������3��ģ������4������
    short group;                                 // �������������group��
    short source;                                // ������������ϳ��ٶ�Դ��0���滮���ϳ��ٶȣ�1���������ϳ��ٶ�
    short coordSystem;                           // ������������ϳ��ٶȵ�����ϵ
    short tableId;                               // ��������������ı��ţ�ȡֵ��Χ��[1,2]
    short pad[3];
    double minPower;                             // ������������������С����ֵ
    double maxPower;                             // �����������������������ֵ
}TLaserFollowTablePrmPro;

typedef struct
{
    short group;                                 // �������������group��
    short source;                                // ������������ϳ��ٶ�Դ��0���滮���ϳ��ٶȣ�1���������ϳ��ٶ�
    short coordSystem;                           // ������������ϳ��ٶȵ�����ϵ
    short dutyTableId;                           // ������������ռ�ձȱ��ı��ţ�ȡֵ��Χ��[1,2]
    short frequencyTableId;                      // ������������Ƶ�ʱ��ı��ţ�ȡֵ��Χ��[1,2]
    short pad[3];
    double minDuty;                              // ������������ռ�ձ���С����ֵ��ȡֵ��Χ��[0,100]����λ��%
    double maxDuty;                              // ������������ռ�ձ��������ֵ��ȡֵ��Χ��[0,100]����λ��%
    double minFrequency;                         // ������������Ƶ����С����ֵ��ȡֵ��Χ��[0,1562.5]����λ��kHz
    double maxFrequency;                         // ������������Ƶ���������ֵ��ȡֵ��Χ��[0,1562.5]����λ��kHz
}TLaserFollowDuoTablePrmPro;

typedef struct
{
    short enable;                                // ʹ��
    short mode;                                  // ������������ģʽ
    short errorCode;                             // ���������������ܵĴ�����Ϣ����Ҫ��ʶ�����ĵط�
    short returnValue;                           // ���������������ܳ����ط��ķ���ֵ

    double power;                                // ��ǰ����ʵ���������ֵ
    double powerAnother;                         // ͬʱ������������ʱ����һ������ֵ

    TLaserFollowPrmPro ratioPrm;                 // ��mode=LASER_FOLLOW_MODE_RATIOʱ��Ӧ�Ĳ���
    TLaserFollowTablePrmPro tablePrm;            // ��mode=LASER_FOLLOW_MODE_TABLEʱ��Ӧ�Ĳ���
    TLaserFollowDuoTablePrmPro duoTablePrm;      // ��mode=LASER_FOLLOW_MODE_DUO_TABLEʱ��Ӧ�Ĳ���
}TLaserFollowPro;

GT_API GTN_SetLaserEnablePro(short core,short laserChannel,short enable,short mode=0,TListInfo *pListInfo=NULL);
GT_API GTN_SetLaserDelayPro(short core,short laserChannel,double laserOnDelay,double laserOffDelay,TListInfo *pListInfo=NULL);
GT_API GTN_SetLaserPwmPrmPro(short core,short laserChannel,TLaserPwmPrmPro *pPrm,TListInfo *pListInfo=NULL);
GT_API GTN_SetLaserPwmDutyPro(short core,short laserChannel,double duty,TListInfo *pListInfo=NULL);
GT_API GTN_SetLaserPwmFrequencyPro(short core,short laserChannel,double frequency,TListInfo *pListInfo=NULL);
GT_API GTN_SetLaserPwmPulseWidthPro(short core,short laserChannel,double pulseWidth,TListInfo *pListInfo=NULL);
GT_API GTN_SetLaserVoltagePrmPro(short core,short laserChannel,double minVoltage,double maxVoltage,TListInfo *pListInfo=NULL);
GT_API GTN_SetLaserVoltagePro(short core,short laserChannel,double voltage,TListInfo *pListInfo=NULL);
GT_API GTN_SetLaserParallelPrmPro(short core,short laserChannel,double minParallel,double maxParallel,TListInfo *pListInfo=NULL);
GT_API GTN_SetLaserParallelPro(short core,short laserChannel,double parallel,TListInfo *pListInfo=NULL);
GT_API GTN_SetLaserIoPro(short core,short laserChannel,short doType,short doValue,TListInfo *pListInfo=NULL);
GT_API GTN_GetLaserPowerPro(short core,short laserChannel,TLaserPowerPro *pLaserPowerPro);
GT_API GTN_GetLaserPro(short core,short laserChannel,TLaserPro *pLaserPro);
GT_API GTN_SetLaserFollowEnablePro(short core,short laserChannel,short enable,TListInfo *pListInfo=NULL);
GT_API GTN_SetLaserFollowPrmPro(short core,short laserChannel,TLaserFollowPrmPro *pPrm,TListInfo *pListInfo=NULL);
GT_API GTN_SetLaserFollowTablePrmPro(short core,short laserChannel,TLaserFollowTablePrmPro *pPrm,TListInfo *pListInfo=NULL);
GT_API GTN_SetLaserFollowDuoTablePrmPro(short core,short laserChannel,TLaserFollowDuoTablePrmPro *pPrm,TListInfo *pListInfo=NULL);
GT_API GTN_ClearLaserFollowTablePro(short core,short laserChannel,short tableId);
GT_API GTN_SetLaserFollowTablePro(short core,short laserChannel,short tableId,int32_t count,double *pSynchVel,double *pPower);
GT_API GTN_GetLaserFollowTablePro(short core,short laserChannel,short tableId,int32_t count,double *pSynchVel,double *pPower,int32_t *pReadCount);
GT_API GTN_GetLaserFollowPro(short core,short laserChannel,TLaserFollowPro *pLaserFollowPro);
GT_API GTN_SetLaserPowerLatchIoPrameterPro(short core,short laserChannel,double waitTime,double pulseWidth,double enable,TListInfo *pListInfo=NULL);

#define SCAN_START_IN_LIST_MODE_INDIVIDUAL                 (0)
#define SCAN_START_IN_LIST_MODE_CHECK                      (1)

/**
 * @brief �������˶���֧��ָ����ģʽ
 * @param core �˺ţ�������1��ʼ
 * @param scanCrd ������ϵ�ţ�������1��ʼ
 * @param pListInfo ָ������Ϣ�ṹ�����ָ��
 * @param pListInfo->reserve1[1] ָ������������ģʽ��0������ģʽ��1�����ģʽ��ָ����ִ�й���������񾵳�������ָֹͣ����
 * @return 17001��TListInfo�ṹ����list��������
 *         17002��TListInfo�ṹ����modal��������
 *         17053��scanCrd������ϵ�Ų�������
 *         17501��TListInfo�ṹ����reserve1[1]������ģʽ��������
 *         11001�����ù�GTN_CommandListDataEnd����ָ������δִ����ɣ�����Ҫѹ����
 *         11002��ָ�������������ˣ�������ѹ����
 *         11003����ǰָ�����ݴ�С����ָ��������Ԫ�ش�С����Ҫ����ָ��GTN_SetCommandListConfig��������Ԫ�ش�С
 *         11004����ǰָ����û�з��仺�����ռ䣬��Ҫ����ָ��GTN_SetCommandListConfig����ָ�����������ռ�
 *         11091����ǰ������û�ж�Ӧ������Դ
 *         11915����������ʹ�õ�ǰָ������������ѹ����������ָֹͣ��
*/
GT_API GTN_ScanCrdStartPro(short core,short scanCrd,TListInfo *pListInfo);

/**
 * @brief ֹͣ���˶���֧��ָ����ģʽ
 * @param core �˺ţ�������1��ʼ
 * @param scanCrd ������ϵ�ţ�������1��ʼ
 * @param stopType ��ֹͣģʽ��0����λֹͣ������ֹͣ���Ҹ�λ�񾵣�1������ֹͣ��2��ֹͣ����ĩ
 * @param pListInfo ָ������Ϣ�ṹ�����ָ��
 * @return 17001��TListInfo�ṹ����list��������
 *         17002��TListInfo�ṹ����modal��������
 *         17052��stopType��ֹͣģʽ��������
 *         17053��scanCrd������ϵ�Ų�������
 *         11001�����ù�GTN_CommandListDataEnd����ָ������δִ����ɣ�����Ҫѹ����
 *         11002��ָ�������������ˣ�������ѹ����
 *         11003����ǰָ�����ݴ�С����ָ��������Ԫ�ش�С����Ҫ����ָ��GTN_SetCommandListConfig��������Ԫ�ش�С
 *         11004����ǰָ����û�з��仺�����ռ䣬��Ҫ����ָ��GTN_SetCommandListConfig����ָ�����������ռ�
 *         11091����ǰ������û�ж�Ӧ������Դ
 *         11915����������ʹ�õ�ǰָ������������ѹ����������ָֹͣ��
*/
GT_API GTN_ScanCrdStopPro(short core,short scanCrd,short stopType,TListInfo *pListInfo);

typedef struct  
{
    double kp;
    double ki;
    double kd;
    double kvff;
    double kaff;
    int32_t   integralLimit;
    int32_t   derivativeLimit;
    short  limit;
    short  reserve[3];
}TPidAlign;

typedef struct  
{
    short mode;
    short master;
    short slave;
    short reserve[3];
    int32_t syncErrorLimit;
    TPidAlign gantryMasterPid;
    TPidAlign gantrySlavePid;
    TPidAlign masterPid;
    TPidAlign slavePid;
}TGantryPrmPro;

GT_API GTN_SetGantryPrmPro(short core,short group,TGantryPrmPro *pGantryPrmPro);

//---------------------------------------------------------
// KeSai
//---------------------------------------------------------
typedef struct
{
    uint16_t axis_id;
    uint16_t axis_mode;   // fixed to 1 for Gear
    uint16_t axis_ctrl;   // 0: IDLE; 1: stop; 2: fast_stop; 3: run 
    uint16_t mode;        // 0 : IDLE�� 1���ҿ���run����2������ 3��
    uint16_t reserve;     // must be 0.
    uint16_t reserve2;    // must be 0.
    int32_t modify_delta;
    int32_t ratio_a;      // ����Ϊ��ֵ
    int32_t ratio_b;      // ����Ϊ��ֵ
}TStGearParam;

typedef struct
{
    uint16_t axis_id;
    uint16_t axis_mode;   // fixed to 2 for Trap
    uint16_t axis_ctrl;   // 0: IDLE; 1: stop; 2: fast_stop; 3: run;  
    uint16_t reserve;     // must be 0.
    int64_t target_pos;
    uint32_t max_vel;
    uint16_t reserve2[2]; // must be 0.
}TStTrapParam;

typedef struct
{
    uint16_t axis_id;
    uint16_t axis_mode;   // fixed to 3 for Jog
    uint16_t axis_ctrl;   // 0: IDLE; 1: stop; 2: fast_stop; 3: run;  
    uint16_t reserve;     // must be 0.

    int32_t target_vel;
    uint32_t max_acc;
    uint32_t reserve1;
    uint16_t reserve2[2]; // must be 0.
}TStJogParam;

typedef struct
{
    uint16_t axis_id;
    uint16_t axis_mode;   // fixed to 8 for grantry trap
    uint16_t axis_ctrl;   // 0: IDLE; 1: stop; 2: fast_stop; 3: run;  
    uint16_t reserve;     // must be 0.

    int64_t target_pos;
    uint32_t max_vel;

    int32_t main_axis_shift;
    int32_t second_axis_shift;
    uint16_t reserve2[2];  // must be 0.
}TStGantrayTrapParam;

typedef struct
{
    uint16_t axis_id;
    uint16_t axis_mode;   // fixed to 16 for driver vel
    uint16_t axis_ctrl;   // 0: IDLE; 1: stop; 2: fast_stop; 3: run ;  
    uint16_t reserve;     // must be 0.

    int32_t target_vel;
    uint16_t reserve3[2]; // must be 0.
    int64_t reserve2;
}TStDriverVelParam;

typedef struct
{
    uint16_t axis_id;
    uint16_t axis_mode;   // fixed to 17 for driver acc
    uint16_t axis_ctrl;   // 0: IDLE; 1: stop; 2: fast_stop; 3: run ;  
    uint16_t reserve;     // must be 0.

    int32_t target_acc;
    uint16_t reserve3[2]; // must be 0.
    int64_t reserve2;
}TStDriverCurParam;

typedef struct
{
    int16_t profileMode;
    uint16_t reserve2[3]; //must be 0.
    TStTrapParam trapPrm;
    TStJogParam jogPrm;
    TStGearParam gearPrm;
    TStGantrayTrapParam gantrayTrapPrm;
    TStDriverVelParam driverVelPrm;
    TStDriverCurParam driverCurPrm;
}TSetMultiMcFunctionPrm;

typedef struct
{
    uint16_t prmErrorInf;
    int16_t readCommandVarTableIndex;     // ��ָ�������������
    int16_t readCount;                    // Ҫ���ı�����������
    int16_t pad[2];                       // �ֽڶ��룬����
    int16_t realReadCount;                // ʵ�ʶ�����������
    double* pVarValue;                    // ��������ֵ
}TMultiMcFunctionReadPrm;

GT_API GTN_StartMcMultiFunction(short core, unsigned short axisCount, unsigned short writeEnable, TSetMultiMcFunctionPrm* pSetPrm, TMultiMcFunctionReadPrm* pGetPrm);
GT_API GTN_LoadReadCommandVarTable(short core, short tableIndex, char* pFile);
GT_API GTN_ReadCommandVarTable(short core, short tableIndex, double* pVarValue, short count, short* pRealCount);

//---------------------------------------------------------
// Axis Simulation
//---------------------------------------------------------

#define AXISSIMULATION_RESERVE1_SUBMODE           (0)

typedef struct
{
    short enable;
    short reserve1[3];
    double reserve2[4];
} TAxisSimulationParameter;

GT_API GTN_SetAxisSimulationParameter(short core,short profile,TAxisSimulationParameter *pPrm,short count);
GT_API GTN_GetAxisSimulationParameter(short core,short profile,TAxisSimulationParameter *pPrm,short count);
GT_API GTN_GetAxisSimulationBeginPos(short core,short profile,double *pBeginPos,short count);
//---------------------------------------------------------
// User Flash
//---------------------------------------------------------
//����д��Flash����
GT_API GTN_ProgramCardNumToFlash(short core,short coreNum);
GT_API GTN_ReadCardNumFromFlash(short core,short *pCardNum);

//������������д��Flash����
#define PORT_D_ETHER_CAT                (4)  // D��

#define PORT_NET_TYPE_DEFAULT           (-1) // Ĭ����������       (�˿ض��壬�������ı�ԭ��������)
#define PORT_NET_TYPE_GLINKII_IN        (0)  // GlinkII������      (FPGA����)
#define PORT_NET_TYPE_ECAT              (2)  // Ecat����           (FPGA����)

GT_API GTN_SetPortNetTypeInfo(short core,short port,short netType);
GT_API GTN_GetPortNetTypeInfo(short core,short port,short *pNetType,short *pFlag,short *pInfo);

//---------------------------------------------------------
// RingNet Sampling
//---------------------------------------------------------

//�Ȼ�����������
typedef struct
{
    short varId;
    short stationId;
    short varType;
    short varIndex;
}StSamplingVar;
GT_API GTN_RN_SamplingInit(short cardIndex,short stationPhyId);
GT_API GTN_RN_SamplingAddVar(short cardIndex, short stationPhyId, StSamplingVar stVar);
GT_API GTN_RN_SamplingReadData(short cardIndex,short stationPhyId,short varIdndex,double* pBuffer,int32_t bufSize,int32_t* pReadCount);
GT_API GTN_RN_SamplingClear(short cardIndex, short stationPhyId, short mode);
GT_API GTN_RN_SamplingPrintData(short cardIndex, short stationPhyId, const char* pFileName, int32_t startIndex, uint32_t printCount);
GT_API GTN_RN_SamplingGetInfo(short cardIndex, short stationPhyId, short infoType, uint32_t *pInfo);
//-------------------------------------------------------------------------------------------------------
// ���ݲɼ����ܣ����������ļ�
// cardIndex:��1��ʼ
// stationPhyId:��0��ʼ
// pFileName���������ļ�·��������
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_LoadFileConfig(short cardIndex,short stationPhyId,char *pFileName);
//-------------------------------------------------------------------------------------------------------
// ���ݲɼ����ܣ���ȡ�ɼ�����
// cardIndex:��1��ʼ
// stationPhyId:��0��ʼ
// pData�����ݷ��أ��û���Ҫ���������
// dataCount��������Ҫ�ض������ݸ�����ȡֵ��Χ[0,4096]
// pResDataCount������ʵ�ʶ��������ݸ���
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_HighSpeedSamplingGetAllData(short cardIndex,short stationPhyId,unsigned short *pData,uint32_t dataCount,uint32_t*pResDataCount);
//-------------------------------------------------------------------------------------------------------
// ���ݲɼ����ܣ��ر�DMA���ݲɼ�
// cardIndex:��1��ʼ
// stationPhyId:��0��ʼ
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_HighSpeedSamplingOffAll(short cardIndex,short stationPhyId);
//-------------------------------------------------------------------------------------------------------
// ���ݲɼ����ܣ�����DMA���ݲɼ�
// cardIndex:��1��ʼ
// stationPhyId:��0��ʼ
//-------------------------------------------------------------------------------------------------------
GT_API GTN_RN_HighSpeedSamplingOnAll(short cardIndex,short stationPhyId);

//initMode����0ΪĬ����Ϊ���ٴο���ʱ�Ḵλ����ʼ״̬��initMode����1Ϊ����ģʽ���ٴο���������һ�������ֵ��
GT_API GTN_SetExtModuleInitMode(short core,short initMode);
GT_API GTN_GetExtModuleInitMode(short core,short *pInitMode);

//-----------------------------------------------------------------------------------
// ��ȡIlink��չģ������
// input��cardIndex----���ţ�ȡֵ��Χ��[1,16]���ڶ����������У�������1
// input��stationPhyId----����վ�ţ�ȡֵ��Χ��[0,64]
// input��moduleId----��չģ��ID��ȡֵ��Χ��[0,63]
// input��address----��չģ���ַ
// output��data----��ȡ��ֵ
// output��dwordNum----��ȡ�����ݸ���
//-----------------------------------------------------------------------------------
GT_API GTN_RN_IlinkRdPduData32(short cardIndex, short stationPhyId, unsigned char moduleId, uint32_t address, uint32_t* data, uint32_t dwordNum);

//-----------------------------------------------------------------------------------
// дIlink��չģ������
// input��cardIndex----���ţ�ȡֵ��Χ��[1,16]���ڶ����������У�������1
// input��stationPhyId----����վ�ţ�ȡֵ��Χ��[0,64]
// input��moduleId----��չģ��ID��ȡֵ��Χ��[0,63]
// input��address----��չģ���ַ
// output��data----��ȡ��ֵ
// output��dwordNum----��ȡ�����ݸ���
//-----------------------------------------------------------------------------------
GT_API GTN_RN_IlinkWrPduData32(short cardIndex, short stationPhyId, unsigned char moduleId, uint32_t address, uint32_t* data, uint32_t dwordNum);

/*-----------------------------------------------------------*/
/* Catch Up                                                  */
/*-----------------------------------------------------------*/
#define CATCH_UP_STATE_IDLE                                                (0)   // ����״̬
#define CATCH_UP_STATE_WAIT                                                (100) // �ȴ�����׷��
#define CATCH_UP_STATE_CATCH_UP                                            (200) // ׷�����ᣬ��δ�ﵽͬ��
#define CATCH_UP_STATE_SYNCH                                               (300) // �㽺ͷ�͹���ͬ��
#define CATCH_UP_STATE_STOP_SYNCH                                          (400) // �㽺ͷ����ֹͣ
#define CATCH_UP_STATE_STOP_SYNCH_DONE                                     (500) // �㽺ͷ����ֹͣ

//-----------------------------------------------------------------------------
// 0 �ȴ��û���������ָ��
//-----------------------------------------------------------------------------
#define CATCH_UP_STATE_IDLE                                                (0)  // ����״̬

//-----------------------------------------------------------------------------
// 100 �ȴ�����׷��
//-----------------------------------------------------------------------------
#define CATCH_UP_STATE_WAIT                                                (100)

#define CATCH_UP_STATE_WAIT_FOR_PIECE_IN_SITU_VIA_FOLLOW                   (CATCH_UP_STATE_WAIT+12)  // ��ԭλ�ȴ���������

#define CATCH_UP_STATE_WAIT_FOR_PIECE_IN_SITU_SYNCH_ONLY_VIA_FOLLOW        (CATCH_UP_STATE_WAIT+22)  // ��ԭλ�ȴ���������
#define CATCH_UP_STATE_WAIT_FOR_START_IN_SITU_SYNCH_ONLY_VIA_FOLLOW        (CATCH_UP_STATE_WAIT+23)  // ��ԭλ�ȴ�������Խ����λ

#define CATCH_UP_STATE_WAIT_FOR_PIECE_IN_SITU_VIA_TRAP                     (CATCH_UP_STATE_WAIT+32)  // ��ԭλ�ȴ�������������λ
#define CATCH_UP_STATE_WAIT_FOR_START_IN_SITU_VIA_TRAP                     (CATCH_UP_STATE_WAIT+33)  // ��ԭλ�ȴ�������������λ

#define CATCH_UP_STATE_WAIT_FOR_PIECE_IN_SITU_SYNCH_ONLY_VIA_TRAP          (CATCH_UP_STATE_WAIT+42)  // ��ԭλ�ȴ�������������λ
#define CATCH_UP_STATE_WAIT_FOR_START_IN_SITU_SYNCH_ONLY_VIA_TRAP          (CATCH_UP_STATE_WAIT+43)  // ��ԭλ�ȴ�������������λ

#define CATCH_UP_STATE_TO_PARKING_NO_PIECE_VIA_FOLLOW                      (CATCH_UP_STATE_WAIT+70) // û�й�����FOLLOW�˶�������λ
#define CATCH_UP_STATE_TO_PARKING_VIA_FOLLOW                               (CATCH_UP_STATE_WAIT+71) // ����λ��С�ڲ���λ��FOLLOW�˶�������λ
#define CATCH_UP_STATE_WAIT_FOR_PIECE_IN_PARKING_VIA_FOLLOW                (CATCH_UP_STATE_WAIT+72) // �ڲ���λ�ȴ���������
#define CATCH_UP_STATE_WAIT_FOR_START_IN_PARKING_VIA_FOLLOW                (CATCH_UP_STATE_WAIT+73) // �ڲ���λ�ȴ�������Խ����λ��

#define CATCH_UP_STATE_TO_PARKING_NO_PIECE_VIA_TRAP                        (CATCH_UP_STATE_WAIT+80) // û�й�������λ�˶�������λ
#define CATCH_UP_STATE_TO_PARKING_VIA_TRAP                                 (CATCH_UP_STATE_WAIT+81) // û�й�������λ�˶�������λ
#define CATCH_UP_STATE_WAIT_FOR_PIECE_IN_PARKING_VIA_TRAP                  (CATCH_UP_STATE_WAIT+82) // �ڲ���λ�ȴ���������
#define CATCH_UP_STATE_WAIT_FOR_START_IN_PARKING_VIA_TRAP                  (CATCH_UP_STATE_WAIT+83) // �ڲ���λ�ȴ�������Խ����λ��
#define CATCH_UP_STATE_TO_RETURN_POSITION_VIA_TRAP                         (CATCH_UP_STATE_WAIT+84) // �����ڹ�Ǯǰ����sa+so�������ҷ���λ�ô��ڲ���λ����λ�˶�����Ŀ��λ��
#define CATCH_UP_STATE_WAIT_FOR_START_IN_RETURN_POSITION_VIA_TRAP          (CATCH_UP_STATE_WAIT+85) // �ڷ���λ�õȴ�������Խ����λ��
#define CATCH_UP_STATE_CALCULATE_RETURN_POS_TO_PARKING_VIA_TRAP            (CATCH_UP_STATE_WAIT+86)	// �ڷ��ز����Ĺ������й���ѹ�룬��̬���㷵�صĺ��ʵ�Ŀ��λ��

//-----------------------------------------------------------------------------
// 200 ׷�����ᣬ��δ�ﵽͬ��
//-----------------------------------------------------------------------------
#define CATCH_UP_STATE_CATCH_UP                                            (200)

#define CATCH_UP_STATE_CATCH_UP_VIA_FOLLOW                                 (CATCH_UP_STATE_CATCH_UP+12) // ��������׷��

#define CATCH_UP_STATE_RETURN_CATCH_UP_VIA_FOLLOW                          (CATCH_UP_STATE_CATCH_UP+16) // �㽺ͷ����Ŀ��λ�ò���������׷��

#define CATCH_UP_STATE_TO_PIECE_NO_SLOPE_VIA_TRAP                          (CATCH_UP_STATE_CATCH_UP+20) // ������ֹ����λ�˶�������λ�ã�û�������
#define CATCH_UP_STATE_TO_PIECE_SLOPE_ESCAPE_VIA_TRAP                      (CATCH_UP_STATE_CATCH_UP+21) // û�������������ֹͣ�ˣ�ǿ�ƽ���Gearͬ��������λ�˶�������λ��
#define CATCH_UP_STATE_CATCH_UP_IN_SLOPE_VIA_TRAP                          (CATCH_UP_STATE_CATCH_UP+22) // �����˶�����λͬ���˶�������λ��
#define CATCH_UP_STATE_CATCH_UP_SLOPE_DONE_VIA_TRAP                        (CATCH_UP_STATE_CATCH_UP+23) // ������ֹ����λ�˶�������λ�ã�û�������

#define CATCH_UP_STATE_RETURN_CATCH_UP_IN_SLOPE_VIA_TRAP                   (CATCH_UP_STATE_CATCH_UP+26) // ��λ�����˶�������λ��

#define CATCH_UP_STATE_STOPPING_TO_RETURN_POS_VIA_TRAP                     (CATCH_UP_STATE_CATCH_UP+28) // �ڷ��ز����Ĺ������й���ѹ�룬�ں���λ��ֹͣ������׷��

//-----------------------------------------------------------------------------
// 300 ����������Ѿ�ͬ��
//-----------------------------------------------------------------------------
#define CATCH_UP_STATE_SYNCH                                               (300) // �㽺ͷ�͹���ͬ��

#define CATCH_UP_STATE_PROCESS                                             (CATCH_UP_STATE_SYNCH+14) // �㽺ͷִ�в岹�˶�
#define CATCH_UP_STATE_PROCESS_DONE                                        (CATCH_UP_STATE_SYNCH+16) // �㽺ͷ�岹���

//-----------------------------------------------------------------------------
// 400 �������������ͬ��
//-----------------------------------------------------------------------------
#define CATCH_UP_STATE_STOP_SYNCH                                          (400) // �㽺ͷ����ֹͣ

#define CATCH_UP_STATE_USER_STOPPING                                       (CATCH_UP_STATE_STOP_SYNCH+10) // �û����ù���ģ��ָֹͣ���������ֹͣ������

#define CATCH_UP_STATE_OUT_OF_RANGE_STOPPING                               (CATCH_UP_STATE_STOP_SYNCH+12) // �㽺ͷ����ֹͣλ
#define CATCH_UP_STATE_ERROR_STOPPING                                      (CATCH_UP_STATE_STOP_SYNCH+13) // cuģ�鴦������ֹͣ

//-----------------------------------------------------------------------------
// 500 �������������ͬ�����
//-----------------------------------------------------------------------------
#define CATCH_UP_STATE_STOP_SYNCH_DONE                                     (500) // �㽺ͷ����ֹͣ

#define CATCH_UP_STATE_USER_STOP_DONE                                      (CATCH_UP_STATE_STOP_SYNCH_DONE+10) // �û����ù���ģ��ָֹͣ������Ѿ�ֹͣ��ɡ��ڸ�״̬������������ģ��
#define CATCH_UP_STATE_OUT_OF_RANGE_STOP_DONE                              (CATCH_UP_STATE_STOP_SYNCH_DONE+12) // �㽺ͷ����ֹͣλ��ͣ���
#define CATCH_UP_STATE_ERROR_STOP_DONE                                     (CATCH_UP_STATE_STOP_SYNCH_DONE+13) // cuģ�鴦������ֹͣ���


#define CATCH_UP_RETURN_MODE_FOLLOW                                  (0)
#define CATCH_UP_RETURN_MODE_TRAP                                    (1)

#define CATCH_UP_FIFO_EMPTY_ACTION_TO_PARKING                        (0)
#define CATCH_UP_FIFO_EMPTY_ACTION_IDLE                              (1)

#define CATCH_UP_STOP_MODE_DEFAULT                                   (0) // Ĭ��ֹͣģʽ���û�����ָ��ֹͣCatchUp��CatchUp����ʹ��״̬
#define CATCH_UP_STOP_MODE_DISABLE                                   (1) // �ر�ʹ��ֹͣģʽ���û�����ָ��ֹͣCatchUp�󣬹ر�CatchUpʹ��

#define CATCH_UP_MASTER_MODE_CONTINUOUS                              (0)
#define CATCH_UP_MASTER_MODE_INTERMITTENT                            (1)

#define CATCH_UP_SLAVE_MODE_DEFAULT                                  (0)
#define CATCH_UP_SLAVE_MODE_SYNCH_ONLY                               (1)

#define CATCH_UP_OUT_OF_RANGE_ACTION_STOP_MASTER                     (0)
#define CATCH_UP_OUT_OF_RANGE_ACTION_STOP_SLAVE                      (1)
#define CATCH_UP_OUT_OF_RANGE_ACTION_STOP_ALL                        (2)

#define CATCH_UP_STOP_INFO_NONE                                      (0)
#define CATCH_UP_STOP_INFO_STOP_SYNCH                                (1)
#define CATCH_UP_STOP_INFO_USER_STOP                                 (2)
#define CATCH_UP_STOP_INFO_OUT_OF_RANGE_STOP                         (3)
#define CATCH_UP_STOP_INFO_ERROR_STOP                                (4)

#define CATCH_UP_ERROR_CODE_NONE                                                     (0)
#define CATCH_UP_ERROR_CODE_MASTER_IS_NONE                                           (1)
#define CATCH_UP_ERROR_CODE_SLAVE_IS_NONE                                            (2)
#define CATCH_UP_ERROR_CODE_START_MOTION_STATE                                       (3)
#define CATCH_UP_ERROR_CODE_START_MOTION_MODE                                        (4)
#define CATCH_UP_ERROR_CODE_START_MOTION_RUN                                         (5)
#define CATCH_UP_ERROR_CODE_START_MOTION_PROFILE_MODE                                (6)
#define CATCH_UP_ERROR_CODE_START_MOTION_FOLLOW_CLEAR                                (7)
#define CATCH_UP_ERROR_CODE_START_MOTION_FOLLOW_DATA                                 (8)
#define CATCH_UP_ERROR_CODE_START_MOTION_SLAVE_TYPE                                  (9)
#define CATCH_UP_ERROR_CODE_START_MOTION_FOLLOW_START                                (10)
#define CATCH_UP_ERROR_CODE_STOP_MOTION_MODE                                         (11)
#define CATCH_UP_ERROR_CODE_OUT_OF_RANGE_STOP_MOTION_MODE                            (12)
#define CATCH_UP_ERROR_CODE_START_PROCESS_MODE                                       (13)
#define CATCH_UP_ERROR_CODE_START_PROCESS_CRD_START                                  (14)
#define CATCH_UP_ERROR_CODE_STOP_SYNCH_MODE                                          (15)
#define CATCH_UP_ERROR_CODE_IS_STOP_SYNCH_DONE_STATE                                 (16)
#define CATCH_UP_ERROR_CODE_IS_PARKING_MOTION_DONE_VIA_FOLLOW_STATE                  (17)
#define CATCH_UP_ERROR_CODE_IS_CATCH_UP_MOTION_DONE_VIA_FOLLOW_STATE                 (18)
#define CATCH_UP_ERROR_CODE_IS_RETURN_CATCH_UP_MOTION_DONE_VIA_FOLLOW_STATE          (19)
#define CATCH_UP_ERROR_CODE_IS_PROCESS_DONE_STATE                                    (20)
#define CATCH_UP_ERROR_CODE_POP_FIFO_PIECE_COUNT                                     (21)
#define CATCH_UP_ERROR_CODE_POP_FIFO_PIECE_SET_PRF_POS                               (22)
#define CATCH_UP_ERROR_CODE_ALLOCATE_MEMORY_POOL                                     (23)
#define CATCH_UP_ERROR_CODE_STATE_WAIT_MODE                                          (24)
#define CATCH_UP_ERROR_CODE_START_SLAVE_ADDITION_TRAP_MOTION_SET_POS                 (25)
#define CATCH_UP_ERROR_CODE_START_SLAVE_ADDITION_TRAP_MOTION_TYPE                    (26)
#define CATCH_UP_ERROR_CODE_START_SLAVE_ADDITION_TRAP_MOTION_UPDATE                  (27)
#define CATCH_UP_ERROR_CODE_START_SLAVE_GEAR_MOTION_SET_GEAR_RATIO                   (28)
#define CATCH_UP_ERROR_CODE_START_SLAVE_GEAR_MOTION_TYPE                             (29)
#define CATCH_UP_ERROR_CODE_START_SLAVE_GEAR_MOTION_GEAR_START                       (30)
#define CATCH_UP_ERROR_CODE_START_SLAVE_GEAR_MOTION_SET_GEAR_SLOPE_END               (31)
#define CATCH_UP_ERROR_CODE_IS_SLOPE_DONE_PROFILE_MODE                               (32)
#define CATCH_UP_ERROR_CODE_IS_SLAVE_ADDITION_TRAP_MOTION_DONE_PROFILE_MODE          (33)
#define CATCH_UP_ERROR_CODE_IS_SLAVE_ADDITION_TRAP_MOTION_DONE_POS                   (34)
#define CATCH_UP_ERROR_CODE_IS_TO_PIECE_VIA_TRAP_MOTION_DONE_STATE                   (35)
#define CATCH_UP_ERROR_CODE_IS_TO_PIECE_VIA_TRAP_MOTION_DONE_PROFILE_MODE            (36)
#define CATCH_UP_ERROR_CODE_IS_PARKING_VIA_TRAP_MOTION_DONE_STATE                    (37)
#define CATCH_UP_ERROR_CODE_GET_GEAR_SLOPE_LEFT_PROFILE_MODE                         (38)
#define CATCH_UP_ERROR_CODE_CU_STATE                                                 (39)
#define CATCH_UP_ERROR_CODE_CU_MASTER_MODE                                           (40)
#define CATCH_UP_ERROR_CODE_START_MOTION_PRF_FOLLOW                                  (41)
#define CATCH_UP_ERROR_CODE_START_MOTION_SET_FOLLOW_MASTER                           (42)
#define CATCH_UP_ERROR_CODE_MASTER_VEL_ZERO                                          (43)
#define CATCH_UP_ERROR_CODE_MASTER_VEL_GREATER_THAN_SLAVE_VEL_MAX                    (44)
#define CATCH_UP_ERROR_CODE_MASTER_MOVE_DIRECTION                                    (45)
#define CATCH_UP_ERROR_CODE_START_SLAVE_TRAP_MOTION_PRF_TRAP                         (46)
#define CATCH_UP_ERROR_CODE_START_SLAVE_TRAP_MOTION_SET_TRAP_PRM                     (47)
#define CATCH_UP_ERROR_CODE_START_SLAVE_TRAP_MOTION_SET_VEL                          (48)
#define CATCH_UP_ERROR_CODE_START_SLAVE_TRAP_MOTION_SET_POS                          (49)
#define CATCH_UP_ERROR_CODE_START_SLAVE_TRAP_MOTION_UPDATE                           (50)
#define CATCH_UP_ERROR_CODE_START_SLAVE_TRAP_MOTION_SLAVE_TYPE                       (51)
#define CATCH_UP_ERROR_CODE_IS_SLAVE_TRAP_MOTION_DONE_PROFILE_MODE                   (52)
#define CATCH_UP_ERROR_CODE_IS_SLAVE_TRAP_MOTION_DONE_POS                            (53)
#define CATCH_UP_ERROR_CODE_IS_SLAVE_TRAP_STOP_DONE_PROFILE_MODE                     (54)

typedef struct  
{
    short masterMode;                  // �����˶�ģʽ��0�������˶���
                                       // 1����Ъ�˶�,������Ҫ2��������
    short masterType;                  // �������ͣ�MC_ENCODER��MC_AU_ENCODER
    short masterIndex;                 // ��������

    short slaveMode;                   // ����ģʽ��0����ȫ���ƴ����˶���1������ֻ���������ﵽ�ٶ�ͬ����λ��ͬ��
    short slaveType;                   // �������ͣ�����ʽ������/��Ŀǰֻ֧�ִ�������Ϊ��MC_VIRTUAL_PROFILE
    short slaveIndex;                  // ��������
    short slaveAdditionType;           // ������������ͣ�����ʽ������/��Ŀǰֻ֧�ִ������������Ϊ��MC_VIRTUAL_PROFILE
    short slaveAdditionIndex;          // �������������
    short slaveLink;                   // ������ӵ�������������0��ʾ�����ӣ�������һ�������ᣩ

    short outOfRangeAction;            // ���ᳬ���ӹ���Χ����Ϊ��0��ֹͣ���ᣬ1��ֹͣ���ᣬ2��ֹͣ����ʹ���

    short trapSmoothTime;              // ����ʱ��λ�˶���ƽ��ʱ��,��λ��ms
    short followSmoothPercent;         // ����׷�ٴ��ʹ�ʱ��follow�˶���S������ռ����ʱ��İٷֱȣ�Ŀǰ��֧�֣�������0

    double synchOffset;                // ͬ��λ��ƫ�ƣ�mm
    double detectPos;                  // �������λ�ã�mm
    double parkPos;                    // ����λ��mm
    double stopPos;                    // ֹͣλ��mm

    double slaveVelMax;                // ��������ٶȣ�mm/s
    double slaveAcc;                   // ������ٶȣ�mm/s^2

    double sampleTime;                 // �ٶȲ���ʱ�䣬ms

    double reserve2[5];
} TCatchUpPrm;

typedef struct  
{
    short mode;                        // ����ģʽ��0��Followģʽ���أ�1�õ�λģʽ����
    short fifoEmptyAction;             // ����������Ϊ��ʱ������Ϊ��0�����᷵�ز���λ
                                       // 1���ȴ�ѹ�빤��λ���Ժ��پ�������Ķ���
    short reserve1[2];
    int32_t reserve2[4];
    double reserve3[4];
} TStartCatchUpPrm;

typedef struct  
{
    short mode;                        // ֹͣģʽ
    short reserve1[3];
    int32_t reserve2[4];
    double reserve3[4];
} TStopCatchUpPrm;

typedef struct  
{
    short mode;                        // ����ģʽ��0ÿ���������û�ѹ��岹���ݣ�����ģ��ֻ���������岹
    short crdIndex;                    // ����ϵ����
    short reserve1[2];
    int32_t reserve2[4];
    double reserve3[4];
} TStartCatchUpProcessPrm;

typedef struct  
{
    short mode;                        // ֹͣģʽ��0����slaveAcc��ͣ
    short reserve1[3];
    int32_t reserve2[4];
    double reserve3[4];
} TStopCatchUpSynchPrm;

typedef struct  
{
    uint32_t id;                  // ����ID
    int32_t reserve1[3];
    double pos;                        // ������Ӧ�����������λ��
    double reserve2[3];
} TCatchUpPieceFifo;

typedef struct  
{
    short state;                       // ��ǰ״̬
    short stopInfo;                    // ֹͣԭ��
    short errorCode;                   // ִ�г���������
    short reserve1[5];
    uint32_t id;                  // ��ǰ����ID
    uint32_t pieceCount;          // �ӹ���������
    int32_t reserve2[6];
    double synchDistance;              // ����ͬ������λ��
    double synchTime;                  // ����ͬ������ʱ��
    double reserve3[6];
} TCatchUpStatus;

typedef struct  
{
    short state;
    short stopInfo;                    // ֹͣԭ��
    short errorCode;                   // ִ�г���������
    short reserve1[5];
    int32_t reserve2[8];
    double pieceStartPos;
    double slaveStartPos;
    double pieceSynchPos;
    double slaveSynchPos;
    double pieceDistanceMin;           // ����ͬ���㲻��Ĺ�����С���    
    double reserve3[8];
} TCatchUpInfo;

GT_API GTN_SetCatchUpPrm(short core,short catchUpIndex,TCatchUpPrm *pPrm);
GT_API GTN_GetCatchUpPrm(short core,short catchUpIndex,TCatchUpPrm *pPrm);
GT_API GTN_StartCatchUp(short core,short catchUpIndex,TStartCatchUpPrm *pPrm);
GT_API GTN_StopCatchUp(short core,short catchUpIndex,TStopCatchUpPrm *pPrm);
GT_API GTN_StartCatchUpProcess(short core,short catchUpIndex,TStartCatchUpProcessPrm *pPrm);
GT_API GTN_StopCatchUpSynch(short core,short catchUpIndex,TStopCatchUpSynchPrm *pPrm);
GT_API GTN_PushCatchUpPieceFifo(short core,short catchUpIndex,TCatchUpPieceFifo *pFifo);
GT_API GTN_GetCatchUpStatus(short core,short catchUpIndex,TCatchUpStatus *pStatus);
GT_API GTN_GetCatchUpInfo(short core,short catchUpIndex,TCatchUpInfo *pInfo);
GT_API GTN_ClearCatchUpStatus(short core,short catchUpIndex);


#define DI_STOP_VALUE_LOW_LEVEL                            (0)  // Di����ֵ����ƽ��������Чֵ0
#define DI_STOP_VALUE_HIG_LEVEL                            (1)  // Di����ֵ����ƽ��������Чֵ1
#define DI_STOP_VALUE_FALLING_EDGE                         (2)  // Di����ֵ���ش������½���
#define DI_STOP_VALUE_RISING_EDGE                          (3)  // Di����ֵ���ش�����������

#define DI_STOP_AXSI_STOP_TYPE_NONE                        (-1)                                  // Di���������޲���
#define DI_STOP_AXIS_STOP_TYPE_ABRUPT                      (0)                                   // Di�����������ֹͣ
#define DI_STOP_AXIS_STOP_TYPE_SMOOTH                      (1)                                   // Di��������ƽ��ֹͣ
#define DI_STOP_AXIS_STOP_TYPE_ABRUPT_THEN_AXIS_OFF        (DI_STOP_AXIS_STOP_TYPE_ABRUPT + 10)  // Di�����������ֹͣ����ʹ��
#define DI_STOP_AXIS_STOP_TYPE_SMOOTH_THEN_AXIS_OFF        (DI_STOP_AXIS_STOP_TYPE_SMOOTH + 10)  // Di��������ƽ��ֹͣ����ʹ��

//-------------------------------------------------------------------------------------------------------
// ����di����ֹͣ��
// core���˺�
// diType��di����
// diIndex��di����
// diValue��di����ֵ,0����ƽ��������Чֵ0��1����ƽ��������Чֵ1��2���ش������½��أ�3���ش�����������
// stopType��ֹͣ���͡�-1��ȡ�����ܣ�0������ֹͣ��1��ƽ��ֹͣ��10������ֹͣ����ʹ�ܣ�11��ƽ��ֹͣ����ʹ��
// pLinkAxisMask��di��������Ҫֹͣ������������ָ��
// axisMaskCount�������������С
//-------------------------------------------------------------------------------------------------------
GT_API GTN_SetStopIoLinkAxes(short core,short diType,short diIndex,short diValue,short stopType,uint32_t *pLinkAxisMask,short axisMaskCount=1);
GT_API GTN_GetStopIoLinkAxes(short core,short diType,short diIndex,short *pDiValue,short *pStopType,uint32_t *pLinkAxisMask,short *pAxisMaskCount);

//-------------------------------------------------------------------------------------------------------
// ����di�������ֵ
// core���˺�
// diType��di����
// diIndex��di����
// diValue��di����ֵ,0����ƽ��������Чֵ0��1����ƽ��������Чֵ1��2���ش������½��أ�3���ش�����������
// doType��di��������Ҫ�����do���ͣ�MC_NONE��ȡ������
// pDoMask��di��������Ҫ�����do������������ָ��
// pDoValue��di��������Ҫ�����doֵ��������ָ��
// doMaskCount��do���������С
//-------------------------------------------------------------------------------------------------------
GT_API GTN_SetStopIoLinkDo(short core,short diType,short diIndex,short diValue,short doType,uint32_t *pDoMask,uint32_t *pDoValue,short doMaskCount=1);
GT_API GTN_GetStopIoLinkDo(short core,short diType,short diIndex,short *pDiValue,short *pDoType,uint32_t *pDoMask,uint32_t *pDoValue,short *pDoMaskCount);

//-------------------------------------------------------------------------------------------------------
// ���ù滮�˶����Ʋ��������嵥λ
// core���˺�
// profile���滮����
// velMax���滮�˶�����ٶ����ƣ���λ������/ms
// accMax���滮�˶������ٶ����ƣ���λ������/ms^2
// ע�⣺
// ��1�����滮�˶�����������ƣ���滮������ֹͣ
// ��2�����û�����velMax����accMax����һ��Ϊ0�����ʾȡ���滮�˶�������Ƽ��
// ��3����ָ��GTN_SetAxisMotionConstraint����һ����������һ��Ϊ���嵥λ��һ����������λ�����������ö���Ч
//-------------------------------------------------------------------------------------------------------
GT_API GTN_SetProfileMotionConstraint(short core, short profile, double velMax, double accMax);
GT_API GTN_GetProfileMotionConstraint(short core, short profile, double *pVelMax, double *pAccMax);

//����λ�ñȽ�����Ƚ�Դ�Ƿ���Ч����
GT_API GTN_PosCompareBufCmdEnable(short core,short posCompareIndex, short enable);
typedef struct
{
    uint32_t segmentNumber;
    short xAxisEnable;
    short yAxisEnable;
    short zAxisEnable;
    short reserve[5];
}TPosCompareBufSourceEnable;
GT_API GTN_PosCompareBufSourceEnable(short core,short posCompareIndex, TPosCompareBufSourceEnable *pSourceEnable);
typedef struct
{
    short bufCmdEnable;
    short xAxisEnable;
    short yAxisEnable;
    short zAxisEnable;
    short reserve[4];
}TPosCompareBufEnableInfo;
GT_API GTN_GetPosCompareBufEnableInfo(short core,short posCompareIndex, TPosCompareBufEnableInfo *pEnableInfo);


//-------------------------------------------------------------------------------------------------------
// ���Ϲ��ܹ��ߺ���
// ������㡢�յ㡢�м�㣬�Լ��˶���������PVT������
//-------------------------------------------------------------------------------------------------------
#define MP_POINT_MAX                        (16)        // ���������8�����Ѿ��㹻��2����12�����Ѿ��㹻

#define MP_ERROR_NONE                       (0)
#define MP_ERROR_VEL                        (700)
#define MP_ERROR_ACC                        (701)
#define MP_ERROR_DEC                        (702)
#define MP_ERROR_POS_END                    (703)
#define MP_ERROR_POS_OUT_OF_RANGE           (704)
#define MP_ERROR_PERCENT                    (705)
#define MP_ERROR_ROOT                       (706)
#define MP_ERROR_SQRT                       (707)
#define MP_ERROR_SEGMENT_TYPE               (708)
#define MP_ERROR_TIME_NOT_FIND              (709)

#define MP_SEGMENT_ASCEND_1                 (1)
#define MP_SEGMENT_ASCEND_TRAP              (2)
#define MP_SEGMENT_ASCEND_3                 (3)
#define MP_SEGMENT_EVEN                     (4)
#define MP_SEGMENT_DESCEND_5                (5)
#define MP_SEGMENT_DESCEND_TRAP             (6)
#define MP_SEGMENT_DESCEND_7                (7)
#define MP_SEGMENT_END                      (8)

struct TMpParameter
{
    double posBegin;
    double posEnd;
    double acc;                             // ���ٶ�
    double dec;                             // ���ٶ�
    double percentAcc;                      // ���ٶΰٷֱ�
    double percentDec;                      // ���ٶΰٷֱ�

    double vel;                             // ����ٶ�
};

struct TMp2Parameter
{
    double posBegin;
    double posEnd;
    double acc;                             // ���ٶ�
    double dec;                             // ���ٶ�
    double percentAcc;                      // ���ٶΰٷֱ�
    double percentDec;                      // ���ٶΰٷֱ�

    double vel1;                            // vel1��һ�ε�����ٶ�
    double vel2;                            // vel2�ڶ��ε�����ٶȣ���vel1=vel2ʱ������һ���ټ���
    double posMiddle;                       // posMiddle�����ٶ��л�ʱ��λ�ã����������λ�ú��յ�λ��֮��
};

struct TMpPoint
{
    double time;                            // ��ǰ�ε����ʱ��
    double vel;                             // ��ǰ�ε�����ٶ�
    double pos;                             // ��ǰ�ε����λ��

    double accDir;                          // ��ǰ�εļ��ٶȷ���
    double am;                              // ��ǰ�ε������ٶ�
    double jerk;                            // ��ǰ�εļӼ��ٶ�
    unsigned short segmentType;             // ��ǰ�����ͣ�1-7
};

struct TMpResult
{
    short dir;                              // 1�������˶���-1�������˶�
    unsigned short pad[2];
    unsigned short knotCount;               // �ڵ�����
    TMpPoint knot[MP_POINT_MAX];            // S�������нڵ��λ�á��ٶȡ�ʱ��
};

typedef struct
{
    short type;
    short pad1[3];

    double pos;                             // �յ�λ��
    double time;                            // �˶�ʱ��

    double vel;                             // ����ٶ�
    double acc;                             // ���ٶ�
    double dec;                             // ���ٶ�

    double percentAcc;                      // ���ٶ�S���߰ٷֱ�
    double percentDec;                      // ���ٶ�S���߰ٷֱ�

    double pad2[4];
} TMpPtParameter;

typedef struct
{
    short errorPosition;                    // ������
    short errorIndex;                       // ����λ��
    short pad1[2];

    int32_t commandIndex;                      // ���ִ����ָ������
} TMpError;

/**
 * @brief �����ٶ����߸����ڵ��λ�á��ٶȺ�ʱ��
 * @param mpp �˶�����
 * @param mpr �ٶ����߸����ڵ��λ�á��ٶȺ�ʱ��
 * @return ������
*/
GT_API GTN_UTL_MovePercentShape(const TMpParameter* pMp, TMpResult* pMpr);

/**
 * @brief �����ٶ����߸����ڵ��λ�á��ٶȺ�ʱ��
 * @param mpp �˶�����
 * @param mpr �ٶ����߸����ڵ��λ�á��ٶȺ�ʱ��
 * @return ������
*/
GT_API GTN_UTL_MovePercent2Shape(const TMp2Parameter* pMp2, TMpResult* pMpr);

/**
 * @brief ����������̬����ֹ��λ�ã����㲻ͬ�м�����Ϣ
 * @param mpr �ٶ����߸����ڵ��λ�á��ٶȺ�ʱ��
 * @param posBegin ���λ��
 * @param posEnd �յ�λ��
 * @param posMiddle �ٶ����߸����ڵ��λ�á��ٶȺ�ʱ��
 * @param pPoint �м���˶���Ϣ
 * @return ������
*/
GT_API GTN_UTL_MovePercentTime(const TMpResult* pMpr, double posBegin, double posEnd, double posMiddle, TMpPoint* pPoint);

GT_API GTN_UTL_MovePercentPt(double posBegin, double timeBegin, const TMpPtParameter* pPtArray, int32_t ptArrayCount,
    TMpPoint* pPointArray, int32_t pointArraySize, int32_t* pPointArrayCount, TMpError* pError);

GT_API GTN_UTL_QueryMovePercentPointAccordingTime(double time, const TMpPoint* pPointArray, int32_t pointArrayCount, TMpPoint* pResult);

GT_API GTN_UTL_QueryMovePercentPointAccordingPos(double pos, const TMpPoint* pPointArray, int32_t pointArrayCount, TMpPoint* pResult);

//-----------------------------------------------------------------------------------
// ���úͶ�ȡ�������ı�����������ֱ���
//-----------------------------------------------------------------------------------
GT_API GTN_RN_GetGlink2OutputResolution(short cardIndex, short stationPhyId, short axis, uint32_t  *pValue);
GT_API GTN_RN_SetGlink2OutputResolution(short cardIndex, short stationPhyId, short axis, uint32_t  value);
//-------------------------------------------------------------------------------------------------------
// ����XML������Ϣ������ָ����ܣ�����
//-------------------------------------------------------------------------------------------------------
typedef struct
{
    short stationId;
    unsigned short stationType;
    unsigned short subType;
    short reserve1;
    short reserve2;
    short reserve3;
    short reserve4;
    short reserve5;
}TOnlineStationType;
GT_API GTN_RN_RingNetRecoverEx(short cardIndex,short stationPhyId,short mode,short *pParam);
GT_API GTN_RN_GetOnlineDeviceNum(short cardIndex,short *pOnlineDeviceNum);
GT_API GTN_RN_GetOnlineStationType(short cardIndex,TOnlineStationType *pOnlineStationType,short stationNums,short *pResNums);
GT_API GTN_InsertCallbackEvent(short core,short motionMode,short index,short eventNumber,TListInfo *pListInfo);
// ��PC�࿪
short GT_TcpServerPortInit(char *hostIp,unsigned short hostPort); 
short GT_TcpServerPortDeInit(void);
short GT_TcpClientPortInit(char *hostIp,unsigned short hostPort);
short GT_TcpClientPortDeInit(void);

//-------------------------------------------------------------------------------------------------
// ��·�л������ṹ��
//-------------------------------------------------------------------------------------------------
typedef struct
{
    short enable;                      // ʹ�ܻ��߽��û�·�л�����,0: ���û�·�л�����,1: ���û�·�л�����
    short mode;                        // �л�ģʽ,0: �ɱջ��л�������,1: �ɿ����л����ջ�

    int32_t dir;                          // �ջ��п���ʱ��ֵ���жϷ���,0: С����ֵʱ�����л�,1: ������ֵʱ�����л�
    int32_t threshold;                    // ��·�л�����ֵ,λ�û�������������ֵʱ�л���·,��λ: ����
    int32_t openLoopDac;                  // �ӱջ��л�������֮���dac���ֵ,��λ: dac��bitλ
    double overTime;                   // ��·�л�������ʱʱ��,������������ֵ��������ʱ���,�����л�

    int32_t posOffset;                    // �����л��ջ�ʱ���滮λ������ڱ�����λ�õ�ƫ����,��λ: ����
    short reserve[2];                  // ����
}TSwitchLoopParameter;

//-------------------------------------------------------------------------------------------------
// �ݲ������������ṹ��
//-------------------------------------------------------------------------------------------------
typedef struct
{
    int32_t loopFlag;                     // �Ƿ���Ҫ����ѭ������,���ڼ���ѭ����ÿȦѭ�������ʹ��,����ʹ����ͬ�Ĳ�����ѭ������,0: ������ѭ������,1: ѭ������
    int32_t tableMax;                     // �ݲ������������������ֵ,������ͷ��������������һ��

    double startPos;                   // ���гݲ��������ı������������ʼλ��ֵ(�����indexλ��),��λ: ����
    double length;                     // ���гݲ��������ı���������ĳ���,��λ: ����
    double refPos;                     // �ο�λ��ֵ,����ǰλ��ϵͳ��index�źŵ�λ��ֵ,��λ: ����

    double positiveOffset;             // ���򲹳�ʱ,����ֵƫ����,��λ: ���������λ,��ֵ���������ڵ���Ħ����
    double positiveScale;              // ���򲹳�ʱ,��������,�ñ������Բ���������ֵ,��Ϊ����ֵ�������

    double negativeOffset;             // ���򲹳�ʱ,����ֵƫ����,��λ: ���������λ,��ֵ���������ڵ���Ħ����
    double negativeScale;              // ���򲹳�ʱ,��������,�ñ������Բ���������ֵ,��Ϊ����ֵ�������
}TTorqueForceCompensatePara;
GT_API GTN_SetVelLoopPid(short core,short control,short index,TPid *pPid);
GT_API GTN_GetVelLoopPid(short core,short control,short index,TPid *pPid);
GT_API GTN_SetVelLoopLowpassPara(short core,short control,short index,short enableFlag,double freq,double damping);
GT_API GTN_GetVelLoopLowpassPara(short core,short control,short index,short *pEnableFlag,double *pFreq,double *pDamping);
GT_API GTN_SetVelLoopNotchPara(short core,short control,short index,short enableFlag,double centerFreq,double bandWidth,double notchDepth);
GT_API GTN_GetVelLoopNotchPara(short core,short control,short index,short *pEnableFlag,double *pCenterFreq,double *pBandWidth,double *pNotchDepth);
GT_API GTN_SetVelLoopKjff(short core,short control,short index,double kjff);
GT_API GTN_GetVelLoopKjff(short core,short control,short index,double *pKjff);
GT_API GTN_SetSwitchLoopParameter(short core,short control,TSwitchLoopParameter *pSwitchLoopPara);
GT_API GTN_GetSwitchLoopParameter(short core,short control,TSwitchLoopParameter *pSwitchLoopPara);
GT_API GTN_SetForceValue(short core,short control,short index,double forceValue);
GT_API GTN_GetForceValue(short core,short control,short index,double *pForceValue);
GT_API GTN_SetLoopOutputProtect(short core,short control,double outputValueMax,int32_t overTime);
GT_API GTN_GetLoopOutputProtect(short core,short control,double *pOutputValueMax,int32_t *pOverTime,short *pStatus);
GT_API GTN_SwitchControlLoopMode(short core,short control,short index,short loopMode,double loopOutput,short switchMode);
GT_API GTN_SetFeedForwordValueLimit(short core,short control,double velMax,double accMax,double jerkMax);
GT_API GTN_GetFeedForwordValueLimit(short core,short control,double *pVelMax,double *pAccMax,double *pJerkMax);
GT_API GTN_GetControlLoopMode(short core,short control,short index,short *loopMode);

GT_API GTN_SetSpringCompensatePara(short core,short control,short enable,int32_t refPos,double k,double b,double limit);
GT_API GTN_GetSpringCompensatePara(short core,short control,short *pEnable,int32_t *pRefPos,double *pK,double *pB,double *pLimit);
GT_API GTN_SetVelLoopCrossCompPara(short core,short control,short enable,short sourceType,short sourceIndex,double k);
GT_API GTN_GetVelLoopCrossCompPara(short core,short control,short *pEnable,short *pSourceType,short *pSourceIndex,double *pK);
GT_API GTN_SetTorqueForceComp(short core,short control,TTorqueForceCompensatePara *pPara,double *pPositiveComp,double *pNegativeComp);
GT_API GTN_EnableTorqueForceComp(short core,short control,short mode);

#define FILTER_LOCATION_FEEDBACK_POS                 (0)
#define FILTER_LOCATION_VEL_LOOP_ERROR               (1)
#define FILTER_LOCATION_VEL_LOOP_OUTPUT              (2)
#define FILTER_LOCATION_FEEDBACK_VEL                 (3)
#define FILTER_LOCATION_FORCE_CONTROL_OUTPUT         (4)
GT_API GTN_SetLowpassFilter(short core,short control,short index,short filterLocation,short filterIndex,short enableFlag,double freq,double damping);
GT_API GTN_GetLowpassFilter(short core,short control,short index,short filterLocation,short filterIndex,short *pEnableFlag,double *pFreq,double *pDamping);
GT_API GTN_SetLowpassFilterFirstOrder(short core,short control,short index,short filterLocation,short filterIndex,short enableFlag,double freq);
GT_API GTN_GetLowpassFilterFirstOrder(short core,short control,short index,short filterLocation,short filterIndex,short *pEnableFlag,double *pFreq);
GT_API GTN_SetLowpassFilterSecondOrder(short core,short control,short index,short filterLocation,short filterIndex,short enableFlag,double freq,double damping);
GT_API GTN_GetLowpassFilterSecondOrder(short core,short control,short index,short filterLocation,short filterIndex,short *pEnableFlag,double *pFreq,double *pDamping);
GT_API GTN_SetNotchFilter(short core,short control,short index,short filterLocation,short filterIndex,short enableFlag,double centerFreq,double bandWidth,double notchDepth);
GT_API GTN_GetNotchFilter(short core,short control,short index,short filterLocation,short filterIndex,short *pEnableFlag,double *pCenterFreq,double *pBandWidth,double *pNotchDepth);


typedef struct
{
    short masterIndex;                  // ��������
    short slaveIndex[2];                // ��������
    short pad1;                         // ��������������Ϊ0

    double stopDec;                     // X1���ֹͣ���ٶ�
    double stopJerk;                    // X1���ֹͣjerk

    double borderPositive[2];           // ��������߽�
    double borderNegative[2];           // ���Ḻ��߽�
}TDualAxisParameter;

typedef struct 
{
    short enable;
    short errorId;
    short pad1[2];

    short state[2];
    short border[2];

    double pad2[6];
}TDualAxisStatus;
GT_API GTN_SetDualAxisParameter(short core,short index,TDualAxisParameter *pPrm);
GT_API GTN_GetDualAxisParameter(short core,short index,TDualAxisParameter *pPrm);
GT_API GTN_EnableDualAxis(short core,short index,short enable);
GT_API GTN_GetDualAxisStatus(short core,short index,TDualAxisStatus *pSts);
GT_API GTN_ResetDualAxis(short core,short index);

typedef struct
{
    double pos;                        // Ŀ��λ��
    double vel;                        // ����ٶ�
    double acc;                        // �����ٶ�
    double dec;                        // �����ٶ�
    double jerkAcc;                    // ���ٶ����jerk
    double jerkDec;                    // ���ٶ����jerk

	double velEvenTime;                // ��δʵ�֣�����Ϊ0
    double accEvenTime;                // ��δʵ�֣�����Ϊ0
    double decEvenTime;                // ��δʵ�֣�����Ϊ0

	unsigned short bufferMode;         // ��δʵ�֣�����Ϊ0
	unsigned short pad1;               // ��������������Ϊ0
	unsigned short pad2;               // ��������������Ϊ0
	unsigned short pad3;               // ��������������Ϊ0

    double reserve1;                   // ��������������Ϊ0
	double reserve2;                   // ��������������Ϊ0
	double reserve3;                   // ��������������Ϊ0
	double reserve4;                   // ��������������Ϊ0
}TMoveAbsoluteSineParameter;

GT_API GTN_MoveAbsoluteSine(short core,short profile,TMoveAbsoluteSineParameter *pPrm,TListInfo *pListInfo=NULL,short group=0);
GT_API GTN_GetMoveAbsoluteSineParameter(short core,short profile,TMoveAbsoluteSineParameter *pPrm);

typedef struct
{
    double pos;                        // Ŀ��λ��
    double vel;                        // ����ٶ�
    double acc;                        // �����ٶ�
    double dec;                        // �����ٶ�
    double jerkAcc;                    // ���ٶ����jerk
    double jerkDec;                    // ���ٶ����jerk

	double velEvenTime;                // ��δʵ�֣�����Ϊ0
    double accEvenTime;                // ��δʵ�֣�����Ϊ0
    double decEvenTime;                // ��δʵ�֣�����Ϊ0

	unsigned short bufferMode;         // ��δʵ�֣�����Ϊ0
	unsigned short pad1;               // ��������������Ϊ0
	unsigned short pad2;               // ��������������Ϊ0
	unsigned short pad3;               // ��������������Ϊ0

    double reserve1;                   // ��������������Ϊ0
	double reserve2;                   // ��������������Ϊ0
	double reserve3;                   // ��������������Ϊ0
	double reserve4;                   // ��������������Ϊ0
}TMoveAbsoluteJerkParameter;

typedef struct
{
   	unsigned short motionDone;         // �˶���ɱ�־��1��ʾ�˶����
	unsigned short pad1[3];            // ��������

	double timeElapse;                 // ����ʱ��
	double timeLeft;                   // ʣ��ʱ��

    double aimPos;                     // Ŀ��λ��
    double prfPos;                     // ��ǰ�滮λ��
    double prfVel;                     // ��ǰ�滮�ٶ�
    double prfAcc;                     // ��ǰ�滮���ٶ�

    double reserve1[4];                // ��������
}TMoveAbsoluteJerkStatus;
GT_API GTN_MoveAbsoluteJerk(short core,short profile,TMoveAbsoluteJerkParameter *pPrm,TListInfo *pListInfo=NULL,short group=0);
GT_API GTN_GetMoveAbsoluteJerkParameter(short core,short profile,TMoveAbsoluteJerkParameter *pPrm);
GT_API GTN_GetMoveAbsoluteJerkStatus(short core,short profile,TMoveAbsoluteJerkStatus *pStatus);
GT_API GTN_MultiMoveAbsoluteJerk(short core,short *pProfileArray,TMoveAbsoluteJerkParameter *pPrmArray,short count,short mode,TListInfo *pListInfo=NULL,short group=0);
GT_API GTN_GetMultiMoveAbsoluteJerkTime(short core,short *pProfileArray,TMoveAbsoluteJerkParameter *pPrmArray,short count,short mode,double *pTimeArray);
GT_API GTN_QueryMoveAbsoluteJerkStatusAccordingTime(short core,short profile,TMoveAbsoluteJerkParameter* pPrm,short count,double posBegin,double time,TMoveAbsoluteJerkStatus *pStatus);
GT_API GTN_QueryMoveAbsoluteJerkStatusAccordingPos(short core,short profile,TMoveAbsoluteJerkParameter* pPrm,short count,double posBegin,double pos,TMoveAbsoluteJerkStatus *pStatus);

typedef struct  
{
    short enable;           // 1��ʹ����ά������0���ر���ά����
    short tableIndex;       // ��ά����������
    short axisType[3];      // ��ά�����ο�������
    short axisIndex[3];     // ��ά�����ο�������
    short reserve1[4];      // ��������������Ϊ0
} TCompensate3D;

typedef struct
{
    int32_t count[3];          // count[0]��X�᷽�򲹳�����
                            // count[1]��Y�᷽�򲹳�����
                            // count[2]��Z�᷽�򲹳�����

    int32_t pad1[5];           // ��������������Ϊ0

    double posBegin[3];     // posBegin[0]����������X�����
                            // posBegin[1]����������Y�����
                            // posBegin[2]����������Z�����

    double step[3];         // step[0]����������X�᷽�򲹳�����
                            // step[1]����������Y�᷽�򲹳�����
                            // step[2]����������Z�᷽�򲹳�����

    double reserve1[4];     // ��������������Ϊ0
} TCompensate3DTable;

typedef struct
{
    int32_t pointIndex[3];     // pointIndex[0]��������X������
                            // pointIndex[1]��������Y������
                            // pointIndex[2]��������Z������

    int32_t pad1;              // ��������������Ϊ0
    double pointValue;      // ����ֵ
} TCompensate3DPoint;

typedef struct
{
    int32_t rangeIndex[3];     // rangeIndex[0]��X�᷽��ض���������ʼ������
                            // rangeIndex[1]��Y�᷽��ض���������ʼ������
                            // rangeIndex[2]��Z�᷽��ض���������ʼ������

    int32_t rangeCount[3];     // rangeCount[0]��X�᷽��ض�����������
                            // rangeCount[1]��Y�᷽��ض�����������
                            // rangeCount[2]��Z�᷽��ض�����������
} TCompensate3DPointRange;

GT_API GTN_SetCompensate3D(short core, short axis, TCompensate3D* pCompensate3D);
GT_API GTN_GetCompensate3D(short core, short axis, TCompensate3D* pCompensate3D);
GT_API GTN_SetCompensate3DTable(short core, short tableIndex, TCompensate3DTable* pTable,TCompensate3DPoint *pPointArray,int32_t pointCount,short extend);
GT_API GTN_GetCompensate3DTable(short core, short tableIndex, TCompensate3DTable* pTable,TCompensate3DPoint *pPointArray,TCompensate3DPointRange* pPointRange,short *pExtend);
GT_API GTN_GetCompensate3DValue(short core, short axis, double *pValue);

typedef struct
{
    uint16_t mode;                      // ����ģʽ��0�������ٶ����ߣ�1��S���ٶ�����
    uint16_t pad1[3];                   // ��������������Ϊ0

    double sampleTime;                 // ����ʱ�䣬��λms��������ڹ滮���ڵ�2��

    double smoothCoef;                 // ƽ��ϵ����[0,1),0��ʾ�ر�ƽ��

    double reserve1[4];                // ��������������Ϊ0
}TTrackParameter;

GT_API GTN_PrfTrack(int16_t core,int16_t profile,TTrackParameter *pPrm);
GT_API GTN_SetTrackParameter(int16_t core, int16_t profile, TTrackParameter* pPrm);
GT_API GTN_GetTrackParameter(int16_t core,int16_t profile,TTrackParameter *pPrm);
GT_API GTN_SetTrackPosition(int16_t core,int16_t profile,double pos);


typedef struct
{
	short enable;             // ׼ͣ����ʹ�ܱ�־��ֻ��Ϊ0����1��
	short reserve1[3]; 		  // ����������Ϊ0
	double stopPos;			  // ׼ͣλ�ã���λ����
	double reserve2[8]; 	  // ����������Ϊ0
}TExactStopPrm;

GT_API GTN_SetAxisExactStopPrm(short core,short axis,short mode,TExactStopPrm *pPrm,TListInfo *pListInfo=NULL);
GT_API GTN_GetAxisExactStopPrm(short core,short axis,short *pMode,TExactStopPrm *pPrm);

typedef struct
{
	unsigned short cfgSize; 
	unsigned short pduWrEn;
	unsigned short pduWrSize;
	unsigned short pduRdEn;
	unsigned short pduRdSize;
	unsigned short cmdEn;
	unsigned short fifoWrEn;
	unsigned short fifoRdEn;
}StRnMailSlaveDeviceCfg;

typedef struct
{
	unsigned short cfgSize; 
	unsigned short pduWrEn;
	unsigned short pduRdEn;
	unsigned short cmdEn;
	unsigned short fifoWrEn;
	unsigned short fifoRdEn;
}StRnMailSlaveDeviceUpDateParam;

/**
 * @brief  ͨѶ���á�
 * @param cardIndex ���š�
 * @param stationPhyId ����վID��
 * @param pParam ������
 * @return
*/
GT_API GTN_RN_MailSlaveDeviceCfg(short cardIndex,short stationPhyId,unsigned short *pParam);
/**
 * @brief  ����ͨѶ��
 * @param cardIndex ���š�
 * @param stationPhyId ����վID��
 * @param pParam ������NULL��ʾ��������ͨѶ��ʽ��
 * @return
*/
GT_API GTN_RN_MailSlaveDeviceUpdate(short cardIndex,short stationPhyId,unsigned short *pParam);

/**
 * @brief  д�����ݡ�
 * @param cardIndex ���š�
 * @param stationPhyId ����վID��
 * @param pData д�����ݡ�
 * @param wordOffset ����ʼ��ַ��ƫ�ơ�
 * @param wordNum Ҫд�ĸ�����
 * @param pWordNumValid ʵ��д�ĸ�����
 * @return
*/
GT_API GTN_RN_MailSlaveDeviceWrSeg(short cardIndex, short stationPhyId, unsigned short *pData, unsigned short wordOffset, unsigned short wordNum, unsigned short* pWordNumValid);
/**
 * @brief  �������ݡ�
 * @param cardIndex ���š�
 * @param stationPhyId ����վID��
 * @param pData �����Ķ����ݡ�
 * @param wordOffset ����ʼ��ַ��ƫ�ơ�
 * @param wordNum Ҫ���ĸ�����
 * @param pWordNumValid ʵ�ʶ��ĸ�����
 * @return
*/
GT_API GTN_RN_MailSlaveDeviceRdSeg(short cardIndex, short stationPhyId, unsigned short *pData, unsigned short wordOffset, unsigned short wordNum, unsigned short* pWordNumValid);
/**
 * @brief  д���������ݡ�
 * @param cardIndex ���š�
 * @param stationPhyId ����վID��
 * @param pData д�����ݡ�
 * @param wordNum Ҫд�ĸ�����
 * @param pWordNumValid ʵ��д�ĸ�����
 * @return
*/
GT_API GTN_RN_MailSlaveDeviceWrCmd(short cardIndex, short stationPhyId, unsigned short *pData, unsigned short wordNum,unsigned short* pWordNumValid);
/**
 * @brief  ��ȡӦ�����ݡ�
 * @param cardIndex ���š�
 * @param stationPhyId ����վID��
 * @param pData ���������ݡ�
 * @param wordNum Ҫ���ĸ�����
 * @param pWordNumValid ʵ�ʶ����ĸ�����
 * @param pCmdRtn Ӧ��ģʽ�ķ���ֵ��
 * @return
*/
GT_API GTN_RN_MailSlaveDeviceRdCmd(short cardIndex, short stationPhyId, unsigned short *pData, unsigned short wordNum,unsigned short* pWordNumValid, unsigned short* pCmdRtn);
/**
 * @brief  д�������ݡ�
 * @param cardIndex ���š�
 * @param stationPhyId ����վID��
 * @param pData д�����ݡ�
 * @param wordNum Ҫд�ĸ�����
 * @param pWordNumValid ʵ��д�ĸ�����
 * @return
*/
GT_API GTN_RN_MailSlaveDeviceWrBlock(short cardIndex, short stationPhyId, unsigned short *pData, unsigned short wordNum, unsigned short* pWordNumValid);
/**
 * @brief  ���������ݡ�
 * @param cardIndex ���š�
 * @param stationPhyId ����վID��
 * @param pData ���������ݡ�
 * @param wordNum Ҫ���ĸ�����
 * @param pWordNumValid ʵ�ʶ����ĸ�����
 * @return
*/
GT_API  GTN_RN_MailSlaveDeviceRdBlock(short cardIndex, short stationPhyId, unsigned short *pData, unsigned short wordNum, unsigned short* pWordNumValid);
/**
 * @brief  ��ȡд�Ŀ���״̬��
 * @param cardIndex ���š�
 * @param stationPhyId ����վID��
 * @param pValidWordNum д�Ŀ�����Ч(δ�·�)������
 * @param pRemainsWordSpase д�Ŀ���ʣ�������
 * @return
*/
GT_API GTN_RN_MailSlaveDeviceGetWrBlockStatus(short cardIndex, short stationPhyId,  unsigned short* pValidWordNum, unsigned short* pRemainsWordSpase);
/**
 * @brief  ��ȡ���Ŀ���״̬��
 * @param cardIndex ���š�
 * @param stationPhyId ����վID��
 * @param pValidWordNum ���Ŀ�����Ч(δ�·�)������
 * @param pRemainsWordSpase ���Ŀ���ʣ�������
 * @return
*/
GT_API GTN_RN_MailSlaveDeviceGetRdBlockStatus(short cardIndex, short stationPhyId,  unsigned short* pValidWordNum, unsigned short* pRemainsWordSpase);

/**
 * @brief  ��ȡӦ��ģʽ״̬����
 * @param cardIndex ���š�
 * @param stationPhyId ����վID��
 * @param pCmdStatus Ӧ��ģʽ��״̬����
 * @param pCmdRtn Ӧ��ģʽ�ķ���ֵ��
 * @return
*/
GT_API GTN_RN_MailSlaveDeviceGetCmdStatus(short cardIndex, short stationPhyId,  unsigned short* pCmdStatus, unsigned short* pCmdRtn);

/**
 * @brief  ��ȡ����IO�������á�
 * @param cardIndex ���š�
 * @param stationPhyId ����վID��
 * @param axis ������ţ���0��ʼ��
 * @param inputIndex ����IO��ţ�ȡֵ��Χ[0,15]��
 * @param pFuncIndex IO���ܶ��壺
					 0�� OUTPUT_FUNC_NULL,
					 1�� OUTPUT_FUNC_ALARM,
					 2�� OUTPUT_FUNC_MOVING,
					 3�� OUTPUT_FUNC_HOME_FINISH,
					 4�� OUTPUT_FUNC_VEL_ACHIEVE,
					 5�� OUTPUT_FUNC_PHASE_SEARCH_FINISH,
					 6�� OUTPUT_FUNC_SERVO_READY,
					 7�� OUTPUT_FUNC_INDEX_SEARCHED,
					 8�� OUTPUT_FUNC_RESERVED,
					 9�� OUTPUT_FUNC_CURRENT_OVER_LIMIT,
					 10��OUTPUT_FUNC_BRAKE,
					 11��OUTPUT_FUNC_POS_FIXED,
					 12��OUTPUT_FUNC_IO_POS_0,
					 13��OUTPUT_FUNC_IO_POS_1,
					 14��OUTPUT_FUNC_IO_POS_2,
					 15��OUTPUT_FUNC_IO_POS_3,
					 16��OUTPUT_FUNC_IO_POS_4,
					 17��OUTPUT_FUNC_IO_POS_5,
					 18��OUTPUT_FUNC_CURRENT_LEVEL,
					 19��OUTPUT_FUNC_LIMIT_WARNING
 * @param pReverse ��IO�Ƿ�ȡ����0��δȡ��,1��ȡ��
 * @return
*/
GT_API GTN_RN_GetOutputFunc(short cardIndex,short stationPhyId,short axis,short outputIndex,short *pFuncIndex,bool *pReverse);
/**
 * @brief  ��ȡ����IO�������á�
 * @param cardIndex ���š�
 * @param stationPhyId ����վID��
 * @param axis ������ţ���0��ʼ��
 * @param inputIndex ����IO��ţ�ȡֵ��Χ[0,15]��
 * @param pFuncIndex IO���ܶ��塣
					 0�� INPUT_FUNC_NULL,
					 1�� INPUT_FUNC_SERVO_ON,
					 2�� INPUT_FUNC_STOP,
					 3�� INPUT_FUNC_CLR_ALARM,
					 4�� INPUT_FUNC_MODE_SWITCH,
					 5�� INPUT_FUNC_FIX_POS,
					 6�� INPUT_FUNC_HOME,
					 7�� INPUT_FUNC_POSITIVE_LIMIT,
					 8�� INPUT_FUNC_NEGATIVE_LIMIT,
					 9�� INPUT_FUNC_HOME_SWITCH,
					 10��INPUT_FUNC_IO_POS_MOTION_0,
					 11��INPUT_FUNC_IO_POS_MOTION_1,
					 12��INPUT_FUNC_IO_POS_MOTION_2,
					 13��INPUT_FUNC_IO_POS_MOTION_3,
					 14��INPUT_FUNC_IO_POS_MOTION_4,
					 15��INPUT_FUNC_IO_POS_MOTION_5,
					 16��INPUT_FUNC_IO_START_POS_MOTION,
					 17��INPUT_FUNC_IO_TASK_0,
					 18��INPUT_FUNC_IO_TASK_1,
					 19��INPUT_FUNC_IO_TASK_2,
					 20��INPUT_FUNC_IO_TASK_3,
					 21��INPUT_FUNC_IO_MOTION_PAUSE_OR_RESUME,
					 22��INPUT_FUNC_PID_SWITCH
 * @param pReverse ��IO�Ƿ�ȡ����0��δȡ��,1��ȡ��
 * @return
*/
GT_API GTN_RN_GetInputFunc(short cardIndex, short stationPhyId,short axis, short inputIndex, short *pFuncIndex, bool *pReverse);
/**
 * @brief  ��ȡ����������ֱ��ʡ�
 * @param cardIndex ���š�
 * @param stationPhyId ����վID��
 * @param axis ������ţ���0��ʼ��
 * @param pValue ����������ֱ��ʡ�
 * @return
*/
GT_API GTN_RN_GetGlink2InputResolution(short cardIndex,short stationPhyId,short axis,uint32_t *pValue);
/**
 * @brief  ���ñ���������ֱ��ʡ�
 * @param cardIndex ���š�
 * @param stationPhyId ����վID��
 * @param axis ������ţ���0��ʼ��
 * @param value ����������ֱ��ʡ�
 * @return
*/
GT_API GTN_RN_SetGlink2InputResolution(short cardIndex, short stationPhyId,short axis,uint32_t value);
/**
 * @brief  ���ñ������˲�������
 * @param core �˺š�
 * @param type ���������͡�
 * @param encoder ��������š�
 * @param filterTime �˲�ʱ�䣬us��
 * @return
*/
GT_API GTN_SetTerminalEncoderFilterTime(short core,short type,short encoder, double filterTime);
/**
 * @brief ��ȡ�������˲�������
 * @param core �˺š�
 * @param station �߼�վ�ţ�������ҪmailBox��������Ҫ���߼�վ�š�
 * @param type ���������͡�
 * @param encoder ��������š�
 * @param filterTime �˲�ʱ�䣬us��
 * @return
*/
GT_API GTN_GetTerminalEncoderFilterTime(short core,short type,short encoder, double *pFilterTime);
/**
 * @brief  ��ȡ��ͨ���ɼ�����(���б�����ֵΪ����ֵ)��
 * @param cardIndex ���š�
 * @param stationPhyId ����վID��
 * @param varIdndex ��Ҫ��ȡ�ı�������(��1��ʼ��ȡֵ��GTN_RN_SamplingAddVarָ�����ӵ�˳�����)��
 * @param pBuffer ��ȡ�����ݴ�ŵ����顣
 * @param bufSize ��Ҫ��ȡ�����ݸ�����
 * @param pReadCount ʵ�ʷ��صĶ�ȡ������
 * @return
*/
GT_API GTN_RN_SamplingReadDataEx(short cardIndex,short stationPhyId, short varIdndex, double *pBuffer,uint32_t bufSize, uint32_t *pReadCount);
/**
 * @brief  ��ӡ���вɼ����ݵ��ļ�(��ӡǰ��رղɼ�, ���б�����ֵΪ����ֵ)��
 * @param cardIndex ���š�
 * @param stationPhyId ����վID��
 * @param pFileName ��ӡ������ļ�·����
 * @param startIndex ��ӡ����ʼ��ַ��ȡֵ��Χ>=0��
 * @param printCount ��Ҫ��ӡ�ĸ�����ȡֵ��Χ>0��
 * @return
*/
GT_API GTN_RN_SamplingPrintDataEx(short cardIndex, short stationPhyId, const char* pFileName, uint32_t startIndex, uint32_t printCount);
/**
 * @brief ��ͨ���ɼ���ʼ����
 * @param cardIndex ���š�
 * @param group ��ʼ���ڼ���ɼ���ȡֵ��Χ:1����samplMode=0ʱ��groupȡֵ[1,2]
                2����samplMode=1ʱ��groupȡֵ[1,n](��δʵ��)��
 * @param samplMode ����ģʽ��0������ģʽ��1������ģʽ(��δʵ��)
 * @return
*/
GT_API GTN_RN_MultiSamplingInit(short cardIndex, short group, short samplMode);
/**
 * @brief ��ʼ�ɼ���
 * @param cardIndex ���š�
 * @param group ��ʼ���ڼ���ɼ���ȡֵ��Χ:1����samplMode=0ʱ��groupȡֵ[1,2]
                2����samplMode=1ʱ��groupȡֵ[1,n](��δʵ��)��
 * @return
*/
GT_API GTN_RN_MultiSamplingOn(short cardIndex, short group);
/**
 * @brief �����ɼ���
 * @param cardIndex ���š�
 * @param group ��ʼ���ڼ���ɼ���ȡֵ��Χ:1����samplMode=0ʱ��groupȡֵ[1,2]
                2����samplMode=1ʱ��groupȡֵ[1,n](��δʵ��)��
 * @return
*/
GT_API GTN_RN_MultiSamplingOff(short cardIndex, short group);
/**
 * @brief ��ӡ�ɼ����ݵ��ļ�(��ӡǰ��رղɼ�, ���б�����ֵΪ�Ĵ���ԭʼֵ)��
 * @param cardIndex ���š�
 * @param group ��ʼ���ڼ���ɼ���ȡֵ��Χ:1����samplMode=0ʱ��groupȡֵ[1,2]
                2����samplMode=1ʱ��groupȡֵ[1,n](��δʵ��)��
 * @param pFileName ��ӡ������ļ�·����
 * @param startIndex ��ӡ����ʼ��ַ��ȡֵ��Χ>=0��
 * @param printCount ��Ҫ��ӡ�ĸ�����ȡֵ��Χ>0��
 * @return
*/
GT_API GTN_RN_MultiSamplingPrint(short cardIndex, short group, const char* pFileName, uint32_t startIndex, uint32_t printCount);
/**
 * @brief �������ݲɼ�������
 * @param cardIndex ���š�
 * @param group ��ʼ���ڼ���ɼ���ȡֵ��Χ:1����samplMode=0ʱ��groupȡֵ[1,2]
                2����samplMode=1ʱ��groupȡֵ[1,n](��δʵ��)��
 * @param stVar �������͡�
 * @return
*/
GT_API GTN_RN_MultiSamplingAddVar(short cardIndex, short group, StSamplingVar stVar);
/**
 * @brief ��ȡ�����ɼ�����(���б�����ֵΪ�Ĵ���ԭʼֵ)��
 * @param cardIndex ���š�
 * @param group ��ʼ���ڼ���ɼ���ȡֵ��Χ:1����samplMode=0ʱ��groupȡֵ[1,2]
                2����samplMode=1ʱ��groupȡֵ[1,n](��δʵ��)��
 * @param varIdndex ��Ҫ��ȡ�ı�������(��1��ʼ��ȡֵ��GTN_RN_MultiSamplingAddVarָ�����ӵ�˳�����)��
 * @param pBuffer ��ȡ�����ݴ�ŵ����顣
 * @param bufSize ��Ҫ��ȡ�����ݸ�����
 * @param pReadCount ʵ�ʷ��صĶ�ȡ������
 * @return
*/
GT_API GTN_RN_MultiSamplingRead(short cardIndex, short group, short varIdndex, double* pBuffer, uint32_t bufSize, uint32_t* pReadCount);
/**
 * @brief ���״̬��������Ϣ��
 * @param cardIndex ���š�
 * @param group ��ʼ���ڼ���ɼ���ȡֵ��Χ:1����samplMode=0ʱ��groupȡֵ[1,2]
                2����samplMode=1ʱ��groupȡֵ[1,n](��δʵ��)��
 * @param mode ȡֵ��1�����GTN_RN_MultiSamplingAddVar���ӵĲɼ�������

 * @return
*/
GT_API GTN_RN_MultiSamplingClear(short cardIndex, short group, short mode);
/**
 * @brief ��ȡ�����ɼ�����(���б�����ֵΪ����ֵ)��
 * @param cardIndex ���š�
 * @param group ��ʼ���ڼ���ɼ���ȡֵ��Χ:1����samplMode=0ʱ��groupȡֵ[1,2]
                2����samplMode=1ʱ��groupȡֵ[1,n](��δʵ��)��
 * @param varIdndex ��Ҫ��ȡ�ı�������(��1��ʼ��ȡֵ��GTN_RN_MultiSamplingAddVarָ�����ӵ�˳�����)��
 * @param pBuffer ��ȡ�����ݴ�ŵ����顣
 * @param bufSize ��Ҫ��ȡ�����ݸ�����
 * @param pReadCount ʵ�ʷ��صĶ�ȡ������
 * @return
*/
GT_API GTN_RN_MultiSamplingReadEx(short cardIndex, short group, short varIdndex, double* pBuffer, uint32_t bufSize, uint32_t* pReadCount);
/**
 * @brief ��ȡ�����ɼ�����(���б�����ֵΪ����ֵ)��
 * @param cardIndex ���š�
 * @param group ��ʼ���ڼ���ɼ���ȡֵ��Χ:1����samplMode=0ʱ��groupȡֵ[1,2]
                2����samplMode=1ʱ��groupȡֵ[1,n](��δʵ��)��
 * @param varIdndex ��Ҫ��ȡ�ı�������(��1��ʼ��ȡֵ��GTN_RN_MultiSamplingAddVarָ�����ӵ�˳�����)��
 * @param pBuffer ��ȡ�����ݴ�ŵ����顣
 * @param bufSize ��Ҫ��ȡ�����ݸ�����
 * @param pReadCount ʵ�ʷ��صĶ�ȡ������
 * @return
*/
GT_API GTN_RN_MultiSamplingPrintEx(short cardIndex, short group, const char* pFileName, uint32_t startIndex, uint32_t printCount);
/**
 * @brief ��ȡ�ɼ���Ϣ��
 * @param cardIndex ���š�
 * @param group ��ʼ���ڼ���ɼ���ȡֵ��Χ:1����samplMode=0ʱ��groupȡֵ[1,2]
                2����samplMode=1ʱ��groupȡֵ[1,n](��δʵ��)��
 * @param infoType ��Ҫ��ȡ����Ϣ���ͣ�
                   0: �ɼ�ʹ����Ϣ
                   1���ɼ���������������������������ʽ��
                   2���ɼ����ĵ�ͨ��������������������
                   3����ȡ��������
                   4����ȡFIFO���״̬
 * @param pInfo ��ȡ������Ϣ��
 * @return
*/
GT_API  GTN_RN_MultiSamplingGetInfo(short cardIndex, short group, short infoType, uint32_t *pInfo);
/**
 * @brief  ���õ�ǰ����������ֵ������GTN_RN_HighSpeedSamplingOnAllָ��ǰ���ã���
 * @param core �˺š�
 * @param encoder ��������š�
 * @param pos ������λ�á�
 * @return
*/
GT_API GTN_SamplingSetEncPos(short core,short encoder,double pos);
/**
 * @brief  ���ñ��������򣨵���GTN_RN_HighSpeedSamplingOnAllָ��ǰ���ã���
 * @param core �˺š�
 * @param encoder ��������š�
 * @param dir д��ı���������0����ת1����ת��
 * @return
*/
GT_API GTN_SamplingSetEncDir(short core,short encoder,short dir);

/**
 * @brief  ���õ�ǰ��������������ֵ������GTN_RN_HighSpeedSamplingOnAllָ��ǰ���ã���
 * @param core �˺š�
 * @param auEncoderType �������������͡�
 * @param auEncoder ������������š�
 * @param pValue ����������λ�á�
 * @return
*/
GT_API GTN_SamplingSetAuEncPos(short core,short auEncoderType,short auEncoder,double pos);
/**
 * @brief  ���ø������������򣨵���GTN_RN_HighSpeedSamplingOnAllָ��ǰ���ã���
 * @param core �˺š�
 * @param auEncoderType �������������͡�
 * @param encoder ������������š�
 * @param dir ��������������
 * @return
*/
GT_API GTN_SamplingSetAuEncDir(short core,short auEncoderType,short auEncoder,short dir);
/**
 * @brief  ��ȡ���������ŷ�״ֵ̬������������Ӳ�������źţ��� 
 * @param core �˺š�
 * @param axis ��ʼ��š�
 * @param pSts �ŷ�״̬����ֵ��bit0���ŷ�׼�������źţ�Ӳ��ΪGTM���Ӱ��°����Ӳ����PIN-21��
                          bit1���ŷ�ʹ������źţ�Ӳ��ΪGTM���Ӱ��°����Ӳ����PIN-3����Ӳ�������ź�ʱ��0��������Ч��1��������Ч��
 * @param count ��ȡ��������
 * @param pClock ��ȡ�Ŀ��ƿ�ʱ�ӡ�
 * @return
*/
GT_API GTN_GetServoStatus(short core,short axis,int32_t *pSts,short count,uint32_t *pClock);
/**
 * @brief   ��������ʵ����ʹ��״̬����GT_GetSts��bit9��ʾʵ����������ʹ��״̬
 * @param core �˺� 
 * @param axis ��Ŵ�1��ʼ��ָ�����ù��ܵ���
 * @param diType Di��Դ����
 * @param diIndex Di��Դ������,��1��ʼ
 * @return ָ���ֵ�б� 7:�������� ���Di����Խ��
 */
GT_API GTN_ServoReadyOn(short core,short axis,short diType,short diIndex);
/**
 * @brief   �ر�������ʵ����ʹ��״̬��GT_GetSts��bit9��ʾGT_AxisEnable��ָ��״̬
 * @param core �˺� 
 * @param axis ��Ŵ�1��ʼ��ָ�����ù��ܵ���
 * @return ָ���ֵ�б� 7:�������� ������Խ��
 */
GT_API GTN_ServoReadyOff(short core,short axis);

/**
 * @brief ��ȡ����ֵ��ֻ��ȡ��Ȧֵ
 * @param cardNum ����
 * @param stationId ����վ��
 * @param encoder ������ţ�ȡֵ��Χ[1..4]
 * @param pValue ��ȡ���ĸ���ֵ��32λ����
 * @return
*/
GT_API GTN_RN_GetCommAuEncPos(short cardIndex, short stationPhyId, short encoder, int32_t* pValue);

//-------------------------------------------------------------------
// Waveform�����ο��ƹ���
//-------------------------------------------------------------------
// ���ο��ƹ���ģʽ
#define WAVEFORM_WORK_MODE_DEFAULT                         (0)       // Ĭ��ģʽ��һ·��������ܺ��������
#define WAVEFORM_WORK_MODE_LINK_POS_COMPARE                (1)       // ����λ�ñȽ�ģʽ��һ·�������ǰվ�ϵ�һ·λ�ñȽ����һ��������һ������
typedef struct
 {
     double time;                      // ���ο���ʱ���ᣬ��λ��ms�����ο��ƹ���ʹ�ܵ�ʱ��ʱ����Ϊ0��
     double value;                     // ���ο���Ŀ�������������ȡֵ��Χȡ������������͡�
                                       // Ŀǰ��֧�����ģ������ȡֵ��Χ��[-10,10]V
 }TWaveformParameter;                  // ���ο��Ʋ����ṹ��

typedef struct
{
    short type;                        // ���ο�������������ͣ�Ŀǰ��֧��һ������
                                       // MC_DAC(20)����ģ����
                                       // MC_AU_DAC(19)������ģ����
                                       // MC_LASER_AO(72)������ģ����
    short index;                       // ���ο��������������������������1��ʼ
    short laserOn;                     // �Զ����Ƽ��⿪�ع⣬�������������ʱ�Զ��������⿪���źţ����������رռ��⿪���ź�
    short pad;                         // �����������������ó�0
}TWaveformOutput;                      // ���ο�����������ṹ��

 typedef struct
 {
     short enable;                     // ���ο���ʹ��״̬��0���رգ�1�����
     short outputType;                 // ���ο�������������ͣ�Ŀǰ��֧��һ������
                                       // MC_DAC(20)����ģ����
                                       // MC_AU_DAC(19)������ģ����
                                       // MC_LASER_AO(72)������ģ����
     short outputIndex;                // ���ο�������������Ͷ�Ӧ��������ȡֵ��Χȡ���ڶ�Ӧ������
     short laserOn;                    // ���⿪�ع��ź�
     short loopCount;                  // �Ѿ�ѭ���Ĵ���
     short pad[3];                     // ��������
     double outputValue;               // ��ǰ���������ֵ
 }TWaveformStatus;                     // ���ο���״̬�����ṹ��
 
/**
 * @brief ���ز��ο�������
 * @param core �˺ţ�������1��ʼ
 * @param index ���ο���������������1��ʼ
 * @param pPrm ���ο������ݽṹ������
 * @param count ���ο������ݸ���
 * @param loopCount ���ο���ѭ������
 * @return 17051�����ο�����������count���ޣ�ȡֵ��Χ��[1,50]
 *         17053��������������
 *         17055���˺Ų�������Ŀǰÿ�ſ�ֻ�е�һ����֧�ֲ��ο��ƹ���
 *         17061��ѭ��������������
 *         17501�����ο���ʱ���������ʱ�����Ϊ����
 *         17502�����ο�������ֵ������������������Ϊģ��������λ��V
 *         11059�����ι����Ѿ�ʹ�ܣ�������������������
 *         11087������Fifo�Ѿ�ѹ���ˣ���Ҫ�������ݵ�����
*/
GT_API GTN_LoadWaveformParameter(short core,short index,TWaveformParameter *pPrm,short count,short loopCount);

/**
 * @brief ʹ�ܲ��ο��ƿ���
 * @param core �˺ţ�������1��ʼ
 * @param index ���ο���������������1��ʼ
 * @param pOutput ���ο��������������
 * @param enable ���ο���ʹ�ܣ�0���رգ�1-��
 * @return 17053��������������
 *         17054��ʹ�ܲ�������ȡֵ��Χ��[0,1]
 *         17055���˺Ų�������Ŀǰÿ�ſ�ֻ�е�һ����֧�ֲ��ο��ƹ���
 *         17100�����ο�����������ṹ��TWaveformOutput��pad�������󣬱���Ϊ0
 *         17503�����ο�����������ṹ��TWaveformOutput��type��������
 *         17504�����ο�����������ṹ��TWaveformOutput��index��������
 *         17505�����ο�����������ṹ��TWaveformOutput��laserOn��������
 *         11050�����ι������ڹ��������ʸ���������ͺ�����
 *         11055�����ι��ܹ���ģʽ���ԣ�����ʹ�ܣ����Waveform��WaveformPairָ���Ƿ����
 *         11059�����ι����Ѿ�ʹ�ܣ�����������������ͺ�����
 *         11091��������û�нӴ����ο��ƹ��ܵĴ�վ
 *         11501������������������������ʹ�ܲ��ο���
 *         11502�����ο������������Դû��ӳ��
 *         11503�����ο��ƹ�����Դ�����������Դ����ͬһ����վ��
 *         11504�����ο�������Ϊ0��������ʹ�ܲ��ο���
*/
GT_API GTN_EnableWaveform(short core,short index,TWaveformOutput *pOutput,short enable);

/**
 * @brief ��ȡ���ο��ƹ���״̬
 * @param core �˺ţ�������1��ʼ
 * @param index ���ο���������������1��ʼ
 * @param pStatus ���ο��ƹ���״̬�ṹ��ָ��
 * @return 17053��������������
 *         17055���˺Ų�������Ŀǰÿ�ſ�ֻ�е�һ����֧�ֲ��ο��ƹ���
*/
GT_API GTN_GetWaveformStatus(short core,short index,TWaveformStatus *pStatus);

/**
 * @brief ���ο��ƿ���ʹ��
 * @param core �˺ţ�������1��ʼ
 * @param crd ����ϵ�ţ�������1��ʼ
 * @param index ���ο��������ţ�������1��ʼ
 * @param pOutput ���ο�������źŲ����ṹ��ָ��
 * @param enable ���ο���ʹ���źţ�ȡֵ��Χ��[0,1]
 * @param modal ģ̬������ȡֵ��Χ��[0,1]
 * @param fifo �岹����ϵ�������ţ�ȡֵ��Χ��[0,1]
 * @return 
*/
GT_API GTN_BufEnableWaveform(short core,short crd,short index,TWaveformOutput *pOutput,short enable,short modal,short fifo);

/**
 * @brief ���ο��ƿ���ʹ��
 * @param core �˺ţ�������1��ʼ
 * @param crd ����ϵ�ţ�������1��ʼ
 * @param index ���ο��������ţ�������1��ʼ
 * @param pOutput ���ο�������źŲ����ṹ��ָ��
 * @param enable ���ο���ʹ���źţ�ȡֵ��Χ��[0,1]
 * @param modal ģ̬������ȡֵ��Χ��[0,1]
 * @param fifo �岹����ϵ�������ţ�ȡֵ��Χ��[0,1]
 * @return 
*/
GT_API GTN_BufEnableWaveformEx(short core,short crd,short index,TWaveformOutput *pOutput,short enable,short modal,short fifo);

/**
 * @brief ���ò��ο��ƹ���ģʽ
 * @param core �˺ţ�������1��ʼ
 * @param index ���ο���������������1��ʼ
 * @param pOutput ���ο��������������
 * @param enable ���ο���ʹ�ܣ�0���رգ�1-��
 * @return 17053��������������
 *         17055���˺Ų�������Ŀǰÿ�ſ�ֻ�е�һ����֧�ֲ��ο��ƹ���
 *         17056��ģʽ��������
 *         11059�����ι����Ѿ�ʹ�ܣ�����������ģʽ
 *         4����ǰ���ƿ��̼��ͺŲ�֧�����õ�ģʽ����Ҫ�����ɸ��߼����ܵĿ��̼�
*/
GT_API GTN_SetWaveformMode(short core,short index,short mode);

/**
 * @brief ��ȡ���ο��ƹ���ģʽ
 * @param core �˺ţ�������1��ʼ
 * @param index ���ο���������������1��ʼ
 * @param pOutput ���ο��������������
 * @param enable ���ο���ʹ�ܣ�0���رգ�1-��
 * @return 17053��������������
 *         17055���˺Ų�������Ŀǰÿ�ſ�ֻ�е�һ����֧�ֲ��ο��ƹ���
*/
GT_API GTN_GetWaveformMode(short core,short index,short *pMode);


//-------------------------------------------------------------------
// WaveformPair�����ο�����·�������
// ��1����һ·���Ϊ���β�����������Ϊ��ֵ���͵�ƽʱ��͸ߵ�ƽʱ��
// ��2���ڶ�·���Ϊ���Ⲩ�Σ���������Ϊ��ֵ��ÿ����ֵ��������β�����/�����ض�Ӧ
// ��3��������������ĳһ·����Ŀ���Ȩ�����ڲ�����������У��Ƿ񰴲��ο���ģ�����ֵ���
//-------------------------------------------------------------------

#define RECTANGLE_WAVE_START_MODE_LOW_LEVEL          (0)   // ���β����ģʽ�����������������͵�ƽ��������ߵ�ƽ
#define RECTANGLE_WAVE_START_MODE_HIGH_LEVEL         (1)   // ���β����ģʽ�����������������ߵ�ƽ��������͵�ƽ

typedef struct
{
    short startMode;                   // ���β����ģʽ������������������Ϊ��
                                       // 0�����������������͵�ƽ��������ߵ�ƽ
                                       // 1�����������������ߵ�ƽ��������͵�ƽ
    short pad[3];                      // ����
    double voltage;                    // ���β�����ߵ�ƽ��Ӧ�ĵ�ѹֵ��ȡֵ��Χ��(0,10]����λ��V
    double highLevelTime;              // ���β�����ߵ�ƽ�����ֵΪvoltage������ʱ�䣬�������0����λ��ms
    double lowLevelTime;               // ���β�����͵�ƽ�����ֵΪ0V������ʱ�䣬�������0����λ��ms
}TRectangleWavePrm;                    // ����������β������ṹ��

typedef struct
{
    short startMode;                   // ���β����ģʽ������������������Ϊ��
                                       // 0�����������������͵�ƽ��������ߵ�ƽ
                                       // 1�����������������ߵ�ƽ��������͵�ƽ
    short pad[3];                      // ����
    double voltage;                    // ���β�����ߵ�ƽ��Ӧ�ĵ�ѹֵ��ȡֵ��Χ��(0,10]����λ��V
    double frequency;                  // ���β����Ƶ�ʣ�ȡֵ��Χ��(0,100)����λ��kHz
    double dutyRatio;                  // ���β����ռ�ձȣ����͵�ƽʱ��ռ������ʱ��ı�����ȡֵ��Χ��(0,100)����λ��%
}TRectangleWaveDutyMode;               // ����������β�ռ�ձ������ṹ��

typedef struct
{
    short stepCount;                   // ̨�ײ����̨�׸�����ȡֵ��Χ��[1,4000]
    short pad[3];                      // ����
    double voltageStart;               // ̨�ײ������ʼ��ѹֵ��ȡֵ��Χ��(0,10]����λ��V
    double voltageEnd;                 // ̨�ײ�����յ��ѹֵ��ȡֵ��Χ��(0,10]����λ��V
    double aheadTime;                  // ̨�ײ��ﵽĿ��̨��ֵ����ǰʱ�䣬ȡֵ��Χ����β�������أ���λ��ms
}TStageWavePrm;                        // �������̨�ײ������ṹ��

typedef struct
{
    short enable;                      // ���ο���ʹ��״̬��0���رգ�1�����
    short laserOn;                     // ���⿪�ع��ź�
    short loopCount;                   // �Ѿ�ѭ���Ĵ���
    short rectOutputType;              // ���β��������
    short rectOutputIndex;             // ���β�������͵�����
    short rectOutputValid;             // ���β������Ч״̬
    short outputType;                  // �ڶ�·���������������
    short outputIndex;                 // �ڶ�·��������������͵�����
    short outputValid;                 // �ڶ�·�������������Ч״̬
    short pad[3];                      // ����
    double rectVoltage;                // ���β������ѹֵ
    double outputVoltage;              // �ڶ�·�������������ѹֵ
}TWaveformPairStatus;                  // ���ο�����·���״̬�ṹ��

/**
 * @brief ���ò��ο�����·������β���
 * @param core �˺ţ�������1��ʼ
 * @param index ���ο���������������1��ʼ
 * @param pRectWave ���β����β����ṹ��ָ��
 * @param pVoltageData �ڶ�·���������ѹֵ�������飬�����СΪdataCount��ÿ���������ʱ�䰴˳������β����������½��ض���
 * @param dataCount �ڶ�·���������ѹֵ���������С
 * @param loopCount ѭ���������
 * @return 17051�����ο�����������dataCount���ޣ�ȡֵ��Χ��[1,50]
 *         17053��������������
 *         17055���˺Ų�������Ŀǰÿ�ſ�ֻ�е�һ����֧�ֲ��ο��ƹ���
 *         17061��ѭ��������������
 *         17100�����β��ṹ��TRectangleWavePrm��Ա����pad�������󣬱���Ϊ0
 *         17502�����ο�������ֵpVoltageData��������
 *         17510�����β��ṹ��TRectangleWavePrm��Ա����startMode��������
 *         17511�����β��ṹ��TRectangleWavePrm��Ա����voltage��������
 *         17512�����β��ṹ��TRectangleWavePrm��Ա����highLevelTime��������
 *         17513�����β��ṹ��TRectangleWavePrm��Ա����lowLevelTime��������
 *         11059�����ι����Ѿ�ʹ�ܣ�������������������
 *         11087������Fifo�Ѿ�ѹ���ˣ���Ҫ�������ݵ�����
*/
GT_API GTN_SetWaveformPairPrm(short core,short index,TRectangleWavePrm *pRectWave,double *pVoltageData,short dataCount,short loopCount);

/**
 * @brief ���ò��ο�����·�����ǰģʽ���β���
 * @param core �˺ţ�������1��ʼ
 * @param index ���ο���������������1��ʼ
 * @param pRectWave ���β�����ռ�ձ�ģʽ�����ṹ��ָ��
 * @param pStageWave ̨�ײ����β����ṹ��ָ��
 * @param loopCount ѭ���������
 * @return 17053��������������
 *         17055���˺Ų�������Ŀǰÿ�ſ�ֻ�е�һ����֧�ֲ��ο��ƹ���
 *         17061��ѭ��������������
 *         17100�����β��ṹ��TRectangleWaveDutyMode��Ա����pad�������󣬱���Ϊ0
 *         17100��̨�ײ��ṹ��TStageWavePrm��Ա����pad�������󣬱���Ϊ0
 *         17510�����β��ṹ��TRectangleWaveDutyMode��Ա����startMode��������
 *         17511�����β��ṹ��TRectangleWaveDutyMode��Ա����voltage��������
 *         17515�����β��ṹ��TRectangleWaveDutyMode��Ա����frequency��������
 *         17516�����β��ṹ��TRectangleWaveDutyMode��Ա����dutyRatio��������
 *         17517��̨�ײ��ṹ��TStageWavePrm��Ա����stepCount��������
 *         17518��̨�ײ��ṹ��TStageWavePrm��Ա����voltageStart��������
 *         17519��̨�ײ��ṹ��TStageWavePrm��Ա����voltageEnd��������
 *         17520��̨�ײ��ṹ��TStageWavePrm��Ա����aheadTime��������
 *         17521��̨�ײ�����̨��������С���������0.0003V
 *         17522��̨�ײ���̨��ʱ��С��10us
 *         11059�����ι����Ѿ�ʹ�ܣ�������������������
*/
GT_API GTN_SetWaveformPairAhead(short core,short index,TRectangleWaveDutyMode *pRectWave,TStageWavePrm *pStageWave,short loopCount);
/**
 * @brief ʹ�ܲ��ο�����·�������
 * @param core �˺ţ�������1��ʼ
 * @param index ���ο���������������1��ʼ
 * @param pRectOutput ���β���������ṹ��ָ��
 * @param pOutput2 �ڶ�·����������ṹ��ָ��
 * @param enable ���ο���ʹ�ܣ�0���رգ�1-��
 * @return 17053��������������
 *         17054��ʹ�ܲ�������ȡֵ��Χ��[0,1]
 *         17055���˺Ų�������Ŀǰÿ�ſ�ֻ�е�һ����֧�ֲ��ο��ƹ���
 *         17100�����ο�����������ṹ��TWaveformOutput��pad�������󣬱���Ϊ0
 *         17503�����ο��Ƶڶ�·��������ṹ��TWaveformOutput��type��������
 *         17504�����ο��Ƶڶ�·��������ṹ��TWaveformOutput��index��������
 *         17505�����ο��Ƶڶ�·��������ṹ��TWaveformOutput��laserOn��������
 *         17507�����ο��ƾ��β���������ṹ��TWaveformOutput��type��������
 *         17508�����ο��ƾ��β���������ṹ��TWaveformOutput��index��������
 *         17509�����ο��ƾ��β���������ṹ��TWaveformOutput��laserOn��������
 *         11050�����ι������ڹ�����������ʹ��
 *         11055�����ι��ܹ���ģʽ���ԣ�����ʹ�ܣ����Waveform��WaveformPairָ���Ƿ����
 *         11059�����ι����Ѿ�ʹ�ܣ�����������������ͺ�����
 *         11087�����ο�������Fifo�Ѿ����ˣ��û����ݹ���
 *         11091��������û�нӴ����ο��ƹ��ܵĴ�վ
 *         11502�����ο��Ƶڶ�·���������Դû��ӳ��
 *         11503�����ο��ƹ�����Դ�͵ڶ�·���������Դ����ͬһ����վ��
 *         11504�����ο�������Ϊ0��������ʹ�ܲ��ο���
 *         11506�����ο��ƾ��β����������Դû��ӳ��
 *         11507�����ο��ƹ�����Դ�;��β����������Դ����ͬһ����վ��
 *         11508��ȡ����ʧ�ܣ��ڲ�ִ�д���
*/
GT_API GTN_EnableWaveformPair(short core,short index,TWaveformOutput *pRectOutput,TWaveformOutput *pOutput,short enable);

/**
 * @brief ��������Ӳ�������Ϊ���ο�����Ч/��Ч
 * @param core �˺ţ�������1��ʼ
 * @param index ���ο���������������1��ʼ
 * @param pOutput ���ο���������������ṹ��ָ��
 * @param valid ��Ӧ��Ӳ������ڿ���ȨΪ���ο��ƹ�����Ч��־
 *              0��ʾ��Ӳ������ڲ����ղ��ο��ƹ������õ��������
 *              1��ʾ��Ӳ������ڰ��ղ��ο��ƹ������õ��������
 * @return 17053��������������
 *         17055���˺Ų�������Ŀǰÿ�ſ�ֻ�е�һ����֧�ֲ��ο��ƹ���
 *         17514����Ч��־��������ȡֵ��Χ��[0,1]
 *         11055�����ι��ܹ���ģʽ���ԣ�����ʹ�ܣ����Waveform��WaveformPairָ���Ƿ����
 *         11091��û�е���ָ��GTN_EnableWaveformPairʹ�ܲ�����������߲�������Ѿ�����
 *         11505�����õ�������Ͳ��ڲ��ο��ƹ�����
*/
GT_API GTN_SetWaveformPairOutputValid(short core,short index,TWaveformOutput *pOutput,short valid);

/**
 * @brief ��ȡ���ο�����·�������״̬
 * @param core �˺ţ�������1��ʼ
 * @param index ���ο���������������1��ʼ
 * @param pStatus ���ο�����·�������״̬�ṹ��ָ��
 * @return 17053��������������
 *         17055���˺Ų�������Ŀǰÿ�ſ�ֻ�е�һ����֧�ֲ��ο��ƹ���
*/
GT_API GTN_GetWaveformPairStatus(short core,short index,TWaveformPairStatus *pStatus);
typedef struct
{
    unsigned short enable;             // ʹ�ܶ�̬����

    unsigned short dimension;          // Ŀǰֻ��Ϊ2
    unsigned short moveAxis1;          // �˶���1����
    unsigned short moveAxis2;          // �˶���2����
    unsigned short source;             // 31:���˶���Ĺ滮λ�ü��㲹������23�����˶���ı�����λ�ü��㲹����

    unsigned short compensateAxis;     // ����������

    unsigned short mode;               // ����ģʽ
                                       // 0���㽺ͷ��̬����ģʽ

    unsigned short pad1;               // ��������������Ϊ0

    double reserve1;                   // ��������������Ϊ0
    double reserve2;                   // ��������������Ϊ0
    double reserve3;                   // ��������������Ϊ0
    double reserve4;                   // ��������������Ϊ0
}TDynamicCompensateParameter;

typedef struct
{
    unsigned short pointType;         // ���ݵ����ͣ�����Ϊ0
    unsigned short pad1;              // ��������������Ϊ0
    unsigned short pad2;              // ��������������Ϊ0
    unsigned short pad3;              // ��������������Ϊ0

    double compensateValue;            // ����ֵ
    double compensateDistance;         // �������䳤��

    double reserve1;                   // ��������������Ϊ0
    double reserve2;                   // ��������������Ϊ0
    double reserve3;                   // ��������������Ϊ0
    double reserve4;                   // ��������������Ϊ0
}TDynamicCompensatePoint;

typedef struct
{
    unsigned short enable;               // ��̬����ʹ��״̬
    unsigned short execute;              // ��̬����������
    unsigned short pad1;                 // ��������
    unsigned short pad2;                 // ��������

    uint32_t pointReceive;         // ���յ�������������
    uint32_t pointUse;             // �ù��Ĳ���������

    TDynamicCompensatePoint point;      // ��ǰ����ʹ�õĲ�����

    double pos1;                       // ��ǰλ��1
    double pos2;                       // ��ǰλ��2
    double travelDistance;             // ��ǰ�߹��ĺϳ�λ�ƣ�����һ����������Ϊ��㣩
    double compensateValue;            // ��ǰ����ֵ

    double reserve1;                   // ��������
    double reserve2;                   // ��������
    double reserve3;                   // ��������
    double reserve4;                   // ��������
}TDynamicCompensateStatus;

GT_API GTN_SetDynamicCompensateParameter(short core, short dcIndex, TDynamicCompensateParameter* pPrm);
GT_API GTN_GetDynamicCompensateParameter(short core, short dcIndex, TDynamicCompensateParameter* pPrm);
GT_API GTN_SetDynamicCompensatePoint(short core, short dcIndex, TDynamicCompensatePoint* pPoint);
GT_API GTN_GetDynamicCompensateStatus(short core, short dcIndex, TDynamicCompensateStatus* pStatus);

GT_API GT_RN_GetEcatEncPosEx(short axis, int32_t* pEncPos);

GT_API GTN_GetDiPhysicCustom(short core, short stationId, short diType, short diIndex, short* pValue, short count);
GT_API GTN_GetDoPhysicCustom(short core, short stationId, short doType, short doIndex, short* pValue, short count);

// ����ͬ���������������ܲ���
typedef struct
{
    short enable;			// ��������ʹ�ܱ�־
    short mode;				// ����ģʽ������Ŀǰֻ����0������滮�ٶȴ����趨��ֵprfVelThread������ͬ���������������������������ٶȵ�ƫ�����encVelDeltaʱ��������������ֹͣ��
    short filterTime;		// ��ͬ���������ķ���Դ���˲�ʱ�䡣��λms��
    short reserve1[5];		// ��������������Ϊ0��
    double prfVelThread;	// ����滮�ٶ���ֵ��������ڵ���0����λ������/ms������滮�ٶȴ��ڸ�ֵʱ���ż��ͬ���������������������������ٶȵ�ƫ��encVelDelta��
    double encVelDelta;		// ͬ���������������������������ٶȵ�ƫ���λ������/ms��
    short errorKeepTimeMax;	// ��������errorKeepTimeMaxʱ��󣬻��Ǵ��ڴ���״̬���򱨾�����ֹͣ�˶���Ŀǰֻ����0��
    short reserve2[7];		// ��������������Ϊ0��
    double reserve3[8];
} TGantrySynchCtlFeedbackProtect;

GT_API GTN_SetGantrySynchCtlFeedbackProtectPrm(short core, short gantryGroup, TGantrySynchCtlFeedbackProtect* pPrm);
GT_API GTN_GetGantrySynchCtlFeedbackProtectPrm(short core, short gantryGroup, TGantrySynchCtlFeedbackProtect* pPrm);
GT_API GTN_SetGantrySynErrCmp2DTable(short core, short tableIndex, TCompensate2DTable* pTable, int32_t* pData, short extend);
GT_API GTN_GetGantrySynErrCmp2D(short core, short group, TCompensate2D* pComp2d);
GT_API GTN_SetGantrySynErrCmp2D(short core, short group, TCompensate2D* pComp2d);

// ͬ����������������Դ��Ϣ������ʹ��������ͬ����Ҳ����ʹ�ø������ͬ����
typedef struct
{
    int16_t masterType;		// ͬ����������������Դ������ʹ��������ͬ����Ҳ����ʹ�ø������ͬ����
    int16_t masterIndex;	// ������
    int16_t slaveType;		// ͬ����������������Դ������ʹ��������ͬ����Ҳ����ʹ�ø������ͬ����
    int16_t slaveIndex;		// ������
} TGantrySyncCtlSrcPrm;
GT_API GTN_SetGantrySynchCtlSrcPrm(short core, short group, TGantrySyncCtlSrcPrm* pGantrySyncCtlSrcPrm);
GT_API GTN_GetGantrySynchCtlSrcPrm(short core, short group, TGantrySyncCtlSrcPrm* pGantrySyncCtlSrcPrm);

GT_API GTN_GetGantrySynErrCmp2DValue(short core, short group, double* pValue);

#define PVT_TABLE_MOVE_ABSOLUTE_COUNT_MAX			7
#define PVT_MOVE_ABSOLUTE_MULTI_SEGMENT_MAX			4
#define PVT_MOVE_ABSOLUTE_MULTI_SEGMENT_AXIS_MAX	6	
#define PVT_MOVE_RELATIVE_SET_PRM_COUNT_MAX			29				   // ���ö�����Զ��˶�����֧�ֵ��������
#define PVT_MOVE_RELATIVE_SEGMENT_MAX				1                  // ��������˶�֧�ֵ��˶��ε�������
#define PVT_MOVE_RELATIVE_COUNT_MAX					119				   // ������Զ��˶�֧�ֵ��������
typedef struct
{
    double pos[PVT_MOVE_ABSOLUTE_MULTI_SEGMENT_MAX];       // ÿ���˶����յ�λ��
    double velMax[PVT_MOVE_ABSOLUTE_MULTI_SEGMENT_MAX];    // ÿ���˶�������ٶ�
    double vel[PVT_MOVE_ABSOLUTE_MULTI_SEGMENT_MAX];       // ÿ���˶��Ķ˵��ٶ�
    double acc;                                            // ���õļ��ٶ�
    double percentAcc;                                     // ���õļ��ٶε�S���߰ٷֱ�
    double dec;                                            // ���õļ��ٶ�
    double percentDec;                                     // ���õļ��ٶε�S���߰ٷֱ�     
}TPvtMoveAbsoluteMultiSegmentPrm;

GT_API GTN_PvtMoveAbsoluteMultiSegment(short core, short segment, TPvtMoveAbsoluteMultiSegmentPrm* pMultiSegmentPrm, uint32_t mask);
GT_API GTN_SetDoPhysicCustom(short core, short stationId, short doType, short doIndex, short* pValue, short count);
GT_API GTN_SetPrfRefSafetyZone(short core, short profile, short enable, TProfileReferenceSafetyZone* pPrm);
GT_API GTN_SetEncoderDeltaLimit(short core, short encType, short encIndex, int32_t deltaLimit);


GT_API GTN_RN_ReadMotorTemperatureEx(short cardIndex, short stationPhyId, short phyAxis, double* pRes);

/**
 * @brief ������չģ��ģ��������
 * @param cardIndex ����
 * @param stationPhyId ����վ��
 * @param moduleId ��չģ��ID��ȡֵ��Χ[0..63]
 * @param mode
 ILINK_CFG_AO_RANGE(1): ����ģ�����������
ILINK_CFG_AI_RANGE(2): ����ģ������������
 * @param pParam
 * #define  USER_ILINK_NUM_AO_CHANNL_V1    (32) //USER_��ͷ�궨�岻�ɸ���
//Ilink ģ������Χ
#define EXT_RANGE_0V_5V                  0
#define EXT_RANGE_N5V_P5V                1  // -5V ~ +5V
#define EXT_RANGE_0V_10V                 2
#define EXT_RANGE_N10V_P10V              3 // -10V ~ +10V
#define EXT_RANGE_0MA_20MA               4
#define EXT_RANGE_4MA_20MA               5
�����
typedef struct
{
    int AO_Range;
    int AO_Offset;
    int AO_Scaling;
    int ErrMode;���ߺ��ͨ��״̬
    int RrrVal;
    int revsd0;
    int default_value;
    int revsd1;
}IdLinkAoChannle;
typedef struct
{
    IdLinkAoChannle iLink_AO_Channl[USER_ILINK_NUM_AO_CHANNL_V1];
}IdLinkAoCfgVer1;
���룺
typedef struct
{
    int AI_Range;
    int AI_Offset;//16
    int AI_Scaling;//16
    int revsd0;//
    int revsd1;//
}IdLinkAiChannle;
typedef struct
{
    IdLinkAiChannle		iLink_AI_Channl[USER_ILINK_NUM_AI_CHANNL_V1];
}IdLinkAiCfgVer1;
 * @return
*/
GT_API GTN_RN_IlinkRangeCfg(short cardIndex, short stationPhyId, short moduleId, short mode, void* pParam);

/**
 * @brief profinetͨѶд
 * @param cardIndex ����
 * @param stationPhyId ����վ��
 * @param slotIndex ���ۺţ�ȡֵ��Χ[1..14]
 * @param pData д�������
 * @param byteNum д�����ݵĳ��ȣ���λbyte��ȡֵ��Χ[0..64]
 * @return
*/
GT_API GTN_RN_WritePNData(short cardIndex, short stationPhyId, short slotIndex, unsigned char* pData, unsigned short byteNum);

/**
 * @brief profinetͨѶ��
 * @param cardIndex ����
 * @param stationPhyId ����վ��
 * @param slotIndex ���ۺţ�ȡֵ��Χ[1..14]
 * @param pData ��ȡ������
 * @param byteNum ��ȡ���ݵĳ��ȣ���λbyte��ȡֵ��Χ[0..64]
 * @return
*/
GT_API GTN_RN_ReadPNData(short cardIndex, short stationPhyId, short slotIndex, unsigned char* pData, unsigned short byteNum);

#define USER_MAX_STATION_NUM_V1          (256)

typedef struct RingInfVer1
{
    unsigned char m_master_flag;
    unsigned char m_port_link_up_a;
    unsigned char m_port_link_up_b;
    unsigned char m_id_auto_set;

    unsigned char m_sync_status;
    unsigned char m_dc_status;

    unsigned char m_device_num;
    unsigned char m_device_id;

    unsigned short m_sync_cycle;
    unsigned short rsvd0;

    unsigned char m_station_id_list[USER_MAX_STATION_NUM_V1];
    unsigned char m_station_ready[USER_MAX_STATION_NUM_V1];
    //add by luo.mj
    uint32_t m_crc_ok_cnt_a;
    uint32_t m_crc_err_cn_a;
    uint32_t m_crc_ok_cn_b;
    uint32_t m_crc_err_cn_b;
}StRingInfVer1;

/**
 * @brief ��ȡ�����ϴ�վ��Ϣ,֧��256����վ
 * @param cardIndex ����
 * @param stationPhyId ����վ��
 * @param StRingInfVer1 ��վ��Ϣ�ṹ��ָ��
 * @return 0��ʾ�ɹ�����0��ʾʧ��
*/
GT_API GTN_RN_GetRemoteInfVer1(short cardIndex,short stationPhyId,StRingInfVer1* pInf);

#define RN_LWR                         (0x0)
#define RN_AWR                         (0x1)     // ����Ѱַд����
#define RN_LMWR                        (0x2)
#define RN_TCWR                        (0x3)
#define RN_LRD                         (0x4)
#define RN_ARD                         (0x5)     // ����Ѱַ������
#define RN_LMRD                        (0x6)
#define RN_TCRD                        (0x7)

typedef struct
{
    uint16_t fineCnt                   :9;       // ��ǰ���������������ݸ���
    uint16_t fineRdFull                :1;       // ��ǰ�������������Ƿ�����
    uint16_t rvsd                      :3;       // ����
    uint16_t ehmiEnMask                :1;       // 1:��ʾehminEn���޸�
    uint16_t ehmiEn                    :1;       // 1:��ʾ��ǰ�豸Ϊehmi�豸
    uint16_t fineRdErr                 :1;       // fifo�ѿգ��Զ�ȡ���������ݣ�������ȡ���󡣸ñ�־λ�����
    uint16_t roundRdCnt                :10;      // ��ǰ�ֲ��������������ݸ���
    uint16_t roundRdFull               :1;       // ��ǰ�ֲ����������Ƿ�����
    uint16_t roundRemoteRdEnMask       :1;       // ��ǰֵΪʱ��roundRemoteRdEn�Żᱻ�޸�
    uint16_t roundRemoteRdEn           :1;       // 1:�ֲ���Զ�˶�ʹ��
    uint16_t roundWrSrcMask            :1;       // ��ǰֵΪʱ��roundWrSrc�Żᱻ�޸�
    uint16_t roundWrSrc                :1;       // 0:���汾�شֲ������ݣ�:�������������Զ������
    uint16_t roundRdErr                :1;       // fifo�ѿգ��Զ�ȡ�ֲ������ݣ�������ȡ���󡣸ñ�־λ�����
}TKsSampleStatus;

/**
 * @brief ���籨�ķ��ͣ�������ģʽ
 * @param cardIndex ����
 * @param stationPhyId ����վ��
 * @param byteAddr ���͵ĵ�ַ��byte��ַ
 * @param pData ���͵���������ͷָ��
 * @param dataNum ���͵����������С����λ��word
 * @param cmd ָ�����ͣ�
 *            ��1��RN_AWR(0x1)������Ѱַд
 *            ��2��RN_ARD(0x1)������Ѱַ��
 * @param addMode ��ַģʽ��
 *                ��1��0��ÿ�η���ͬһ����ַ
 *                ��2��1��ÿ�η��ʵ�ַ�Զ���1
 * @param fastEn ���ٷ���ʹ��
 *               ��1��0����ͨ����
 *               ��2��1�����ٷ���
 * @return 
*/
GT_API GTN_RN_TxNetPacket(int16_t cardIndex,int16_t stationPhyId,uint16_t byteAddr,uint16_t *pData,uint16_t dataNum,uint8_t cmd,uint8_t addMode,uint8_t fastEn);

/**
 * @brief ���籨�Ľ��գ�������ģʽ
 * @param cardIndex ����
 * @param stationPhyId ����վ��
 * @param byteAddr ���յĵ�ַ��byte��ַ
 * @param pData ���յ���������ͷָ��
 * @param dataNum ���յ����������С����λ��word
 * @param cmd ָ�����ͣ�
 *            ��1��RN_AWR(0x1)������Ѱַд
 *            ��2��RN_ARD(0x1)������Ѱַ��
 * @param addMode ��ַģʽ��
 *                ��1��0��ÿ�η���ͬһ����ַ
 *                ��2��1��ÿ�η��ʵ�ַ�Զ���1
 * @param fastEn ���ٽ���ʹ��
 *               ��1��0����ͨ����
 *               ��2��1�����ٽ���
 * @return 0��ʾִ�гɹ�����0��ʾִ��ʧ��
*/
GT_API GTN_RN_RxNetPacket(int16_t cardIndex,int16_t stationPhyId,uint16_t byteAddr,uint16_t *pData,uint16_t dataNum,uint8_t cmd,uint8_t addMode,uint8_t fastEn);

/**
 * @brief ���ò���״̬
 * @param cardIndex ����
 * @param stationPhyId ����վ��
 * @param pStatus ����״̬�����ֽṹ��ָ�룬���庬��ο�ͷ�ļ��ṹ����ϸ˵��
 * @return 0��ʾִ�гɹ�����0��ʾִ��ʧ��
*/
GT_API GTN_RN_SetKsSampleStatus(int16_t cardIndex,int16_t stationPhyId,TKsSampleStatus *pStatus);

/**
 * @brief ��ȡ����״̬
 * @param cardIndex ����
 * @param stationPhyId ����վ��
 * @param pStatus ����״̬�����ֽṹ��ָ�룬���庬��ο�ͷ�ļ��ṹ����ϸ˵��
 * @return 0��ʾִ�гɹ�����0��ʾִ��ʧ��
*/
GT_API GTN_RN_GetKsSampleStatus(int16_t cardIndex,int16_t stationPhyId,TKsSampleStatus *pStatus);

/**
 * @brief �������״̬
 * @param cardIndex ����
 * @param stationPhyId ����վ��
 * @return 0��ʾִ�гɹ�����0��ʾִ��ʧ��
*/
GT_API GTN_RN_SetKsSampleClear(int16_t cardIndex,int16_t stationPhyId);

/**
 * @brief ���ò�������
 * @param cardIndex ����
 * @param stationPhyId ����վ��
 * @param mask ����
 * @return 0��ʾִ�гɹ�����0��ʾִ��ʧ��
*/
GT_API GTN_RN_SetKsSampleMask(int16_t cardIndex,int16_t stationPhyId,uint32_t mask);

/**
 * @brief ��ȡ��������
 * @param cardIndex ����
 * @param stationPhyId ����վ��
 * @param pMask ��ȡ��������
 * @return 0��ʾִ�гɹ�����0��ʾִ��ʧ��
*/
GT_API GTN_RN_GetKsSampleMask(int16_t cardIndex,int16_t stationPhyId,uint32_t *pMask);

/**
 * @brief ��ȡ�����汾
 * @param cardIndex ����
 * @param stationPhyId ����վ��
 * @param pVersion ��ȡ���Ĳ����汾
 * @return 0��ʾִ�гɹ�����0��ʾִ��ʧ��
*/
GT_API GTN_RN_GetKsSampleVersion(int16_t cardIndex,int16_t stationPhyId,uint32_t *pVersion);

/**
 * @brief ��ȡ����������
 * @param cardIndex ����
 * @param stationPhyId ����վ��
 * @param pData ��ȡ������������ͷָ��
 * @param dWordNums ��Ҫ��ȡ�����ݸ�������λ��dWord��ȡֵ��Χ��[1,508]
 * @return 0��ʾִ�гɹ�����0��ʾִ��ʧ��
*/
GT_API GTN_RN_GetKsSampleFineData(int16_t cardIndex,int16_t stationPhyId,uint32_t *pData,uint16_t dWordNums);

/**
 * @brief ��ȡ�ֲ�������
 * @param cardIndex ����
 * @param stationPhyId ����վ��
 * @param pData ��ȡ������������ͷָ��
 * @param dWordNums ��Ҫ��ȡ�����ݸ�������λ��dWord��ȡֵ��Χ��[1,508]
 * @return 0��ʾִ�гɹ�����0��ʾִ��ʧ��
*/
GT_API GTN_RN_GetKsSampleRoundData(int16_t cardIndex,int16_t stationPhyId,uint32_t *pData,uint16_t dWordNums);
