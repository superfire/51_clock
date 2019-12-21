#ifndef __KEY_H__
#define __KEY_H__

typedef enum _sys_press_key_def {
    KEY_HOUR,
	KEY_MIN,
	KEY_SEC,
	KEY_MODE,
	KEY_START_STOP,
	KEY_CLEAR,
	KEY_NONE = 0xFF
}SysPressKeyDef;


SysPressKeyDef key_scan();

#endif //__KEY_H__
