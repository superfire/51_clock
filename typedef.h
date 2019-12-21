#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

/*
** Global typedefs.
*/

#ifndef NULL
#define NULL ((void*)0)
#endif

#define __CODE code
#define __XDATA xdata
#define __DATA data
#define __IDATA idata
#define __NEAR
#define __IO volatile

//bool bype
typedef bit BOOL;

//unsigned integer type
typedef unsigned char UINT8;
typedef char          CHAR;
typedef unsigned short UINT16;

//signed integer type
typedef signed char INT8;
typedef signed short INT16;

//32bit type
typedef unsigned long int UINT32;
typedef signed long int INT32;


#define VOID void

#define FALSE 0
#define TRUE  1

#define DISABLE 0
#define ENABLE  1

#define LOW     0
#define HIGH    1

#define OFF     0
#define ON      1


// Helper macros.
#define _UNUSED_(arg)     ((arg) = (arg))

#ifndef _countof
#define _countof(ARRAY) (sizeof(ARRAY) / sizeof(ARRAY[0]))
#endif

#ifndef max
#define max(a, b)   (((a)>(b))?(a):(b)) 
#endif

#ifndef min
#define min(a, b)   (((a)<(b))?(a):(b))
#endif

// sys info
typedef enum _sys_mode_def {
    MODE_DISP_TIME,
	MODE_SET_TIME,
	MODE_STOPWATCH,
	MODE_ALARM
}SysModeDef;


typedef struct _sys_time_def {
    UINT8 hour;
	UINT8 min;
	UINT8 sec;
	UINT16 msec;
}SysTimeDef;

typedef struct _sys_stopwatch_def {
    SysTimeDef time;
	UINT8 is_running;
}SysStopWatchDef;

typedef struct _sys_alarm_def {
    SysTimeDef time;
	UINT8 is_set;    // 是否设置了闹钟
	UINT8 is_arrived; // 闹钟是否到达
}SysAlarmDef;

#endif  // __TYPEDEF_H__