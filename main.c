#include "comm.h"


SysModeDef  g_sys_mode = MODE_DISP_TIME;
extern SysTimeDef  g_sys_time;
extern SysAlarmDef  g_sys_alarm;
extern SysStopWatchDef  g_sys_stopwatch;

//
void enter_disp_time();
void enter_set_time();
void enter_stopwatch();
void enter_alarm();

//
void stopwatch_start();
void stopwatch_stop();
void stopwatch_clear();

VOID system_init(VOID)
{
	timer0_config_ms( TIMER_BASE_1MS );
    enable_interrupt();
}

void main(void)
{
    system_init();
	
    while(1)
	{
		switch( g_sys_mode )
		{
			case MODE_DISP_TIME:
				enter_disp_time();
				break;
			case MODE_SET_TIME:
				enter_set_time();
				break;
			case MODE_STOPWATCH:
                enter_stopwatch();
				break;
			case MODE_ALARM:
                enter_alarm();
				break;
		    default:
				break;
		}
	}
}

void enter_disp_time()
{
	SysPressKeyDef cur_key;
	
	while(1)
	{
		
		disp_time( g_sys_time );
		
		cur_key = key_scan();
		/*
		 * 正常显示时间模式，按下模式键，进入调整系统时间状态
		 */
		if( cur_key == KEY_MODE )
		{
			g_sys_mode = MODE_SET_TIME;
			return;
		}
    }
}

void enter_set_time()
{
	SysTimeDef tmp_time_setting;
	SysPressKeyDef cur_key;
		
	tmp_time_setting = g_sys_time;
	while(1)
	{
		cur_key = key_scan();

		if( cur_key == KEY_HOUR )
		{
			tmp_time_setting.hour += 1;
			if( tmp_time_setting.hour > 23 )
			{
				tmp_time_setting.hour = 0;
			}
		}
		else if( cur_key == KEY_MIN )
		{
			tmp_time_setting.min += 1;

            /* 这里仅仅溢出清零，不做进位处理 */
			if( tmp_time_setting.min > 59 )  
			{
				tmp_time_setting.min = 0;
			}
		}
		else if( cur_key == KEY_SEC )
		{
			tmp_time_setting.sec += 1;
			if( tmp_time_setting.sec > 59 )
			{
				tmp_time_setting.sec = 0;
			}
		}
	    /*
	     * 在调整系统时间状态，按下模式键，执行如下操作：
		 * 1. 保存时间
		 * 2. 然后进入秒表状态，跳出该函数
	     */
		else if( cur_key == KEY_MODE )
		{
			g_sys_time = tmp_time_setting;
			
			g_sys_mode = MODE_STOPWATCH;
			return;
		}
        disp_time( tmp_time_setting );
	}
}

void enter_stopwatch()
{
	SysPressKeyDef cur_key;

	while( 1 )
	{
		cur_key = key_scan();

		if( cur_key == KEY_START_STOP )
		{
			stopwatch_clear();
			stopwatch_start();
			
			while(1)
			{
		        cur_key = key_scan();
		        if( cur_key == KEY_START_STOP )
				{
				    stopwatch_stop();
					break;
				}
				else if( cur_key == KEY_CLEAR)
				{
					stopwatch_clear();
				}
		        /* 如果按下模式键，进入设定闹钟模式 */
		        else if( cur_key == KEY_MODE )
		        {
					stopwatch_stop();
					stopwatch_clear();
					
		        	g_sys_mode = MODE_ALARM;
		        	return;
		        }
				
				disp_stopwatch();
			}
		}
		/* 如果按下模式键，进入设定闹钟模式 */
		else if( cur_key == KEY_MODE )
		{
			stopwatch_clear();
			
			g_sys_mode = MODE_ALARM;
			return;
		}
		
		disp_stopwatch();
	}
}

void enter_alarm()
{
	SysPressKeyDef cur_key;
	SysTimeDef tmp_time_setting = {0,0,0,0};

	while(1)
	{
		cur_key = key_scan();

		if( cur_key == KEY_HOUR )
		{
			tmp_time_setting.hour += 1;
			if( tmp_time_setting.hour > 23 )
			{
				tmp_time_setting.hour = 0;
			}
		}
		else if( cur_key == KEY_MIN )
		{
			tmp_time_setting.min += 1;
			if( tmp_time_setting.min > 59 )  // 这里仅仅溢出清零，不做进位处理
			{
				tmp_time_setting.min = 0;
			}
		}
		else if( cur_key == KEY_SEC )
		{
			tmp_time_setting.sec += 1;
			if( tmp_time_setting.sec > 59 )
			{
				tmp_time_setting.sec = 0;
			}
		}
	    /*
	     * 在调整系统时间状态，按下模式键，执行如下操作：
		 * 1. 保存时间
		 * 2. 然后进入显示时间状态，跳出该函数
	     */
		else if( cur_key == KEY_MODE )
		{
			g_sys_alarm.time = tmp_time_setting;
			g_sys_alarm.is_set = TRUE;
			g_sys_alarm.is_arrived = FALSE; // 重新设置后，清除达到标志
			
			g_sys_mode = MODE_DISP_TIME;
			return;
		}

        disp_time( tmp_time_setting );
	}
}

void stopwatch_clear()
{
	memset( &g_sys_stopwatch.time, 0, sizeof( SysTimeDef ) );
}

void stopwatch_start()
{
    g_sys_stopwatch.is_running = TRUE;
}

void stopwatch_stop()
{
    g_sys_stopwatch.is_running = FALSE;
}










