#include "comm.h"

// modify by user
SysTimeDef  g_sys_time = {0,0,0,0};
SysAlarmDef  g_sys_alarm = { {0,0,0,0}, {FALSE}, {FALSE}};
SysStopWatchDef  g_sys_stopwatch = { {0,0,0,0}, {FALSE} };

//timer0 count reload val
static UINT8 g_u8_TL0;
static UINT8 g_u8_TH0;

sbit PIN_BEEP = P1^7;
static UINT16 g_u16_pwm_time = 0;
static UINT16 g_u16_beep_time = 0;
static UINT8  g_u8_beep_on = FALSE;

static void update_sys_time()
{
	g_sys_time.sec ++;
	
	if( g_sys_time.sec > 59 )
	{
	    g_sys_time.sec = 0;
		
		g_sys_time.min += 1;
		if( g_sys_time.min > 59 )
		{
		    g_sys_time.min = 0;
			g_sys_time.hour += 1;
			if( g_sys_time.hour > 23 )
			{
			    g_sys_time.hour = 0;
			}
		}
	}
}

static void update_stopwatch_time()
{
	g_sys_stopwatch.time.sec ++;
	
	if( g_sys_stopwatch.time.sec > 59 )
	{
	    g_sys_stopwatch.time.sec = 0;
		
		g_sys_stopwatch.time.min += 1;
		if( g_sys_stopwatch.time.min > 59 )
		{
		    g_sys_stopwatch.time.min = 0;
			g_sys_stopwatch.time.hour += 1;
			if( g_sys_stopwatch.time.hour > 9 )
			{
			    g_sys_stopwatch.time.hour = 0;
			}
		}
	}
}

static void chk_alarm()
{
    SysTimeDef time;
    
	if( g_sys_alarm.is_set != TRUE )
		return;
	
	if( g_sys_alarm.is_arrived == TRUE )
	{
		g_u16_beep_time ++;
		if( g_u16_beep_time >= SYS_TIMEOUT_1SEC )
		{
			g_u16_beep_time = 0;
			
			if( g_u8_beep_on != TRUE )
				g_u8_beep_on = TRUE;
			else
				g_u8_beep_on = FALSE;
		}
		
		if( g_u8_beep_on == TRUE )
		{
			g_u16_pwm_time ++;
			if( g_u16_pwm_time <= 1 )
			{
				PIN_BEEP = 1;
			}
			else if( g_u16_pwm_time <= 2 )
			{
				PIN_BEEP = 0;
			}
			else
				g_u16_pwm_time = 0;
		}
		
		return;
	}
	
	time = g_sys_time;
	if( ( g_sys_alarm.time.sec == g_sys_time.sec ) &&\
        ( g_sys_alarm.time.min == g_sys_time.min ) &&\
	    ( g_sys_alarm.time.hour == g_sys_time.hour ) )
	{
	    LOG("\r\nalarm arrived, cur time:\r\n");
		LOG2("hour:", g_sys_time.hour);
		LOG2("min:", g_sys_time.min);
		LOG2("sec:", g_sys_time.sec);
		g_sys_alarm.is_arrived = TRUE;
	}
}

VOID timer0_config_ms(UINT8 u8_ms)
{
    //waring, u8_ms * FOSC can not large than UINT32
    UINT16 u16_thl = 65536 - u8_ms * FOSC / 12 / 1000; 
    g_u8_TL0 = (UINT8)u16_thl;
    g_u8_TH0 = (UINT8)(u16_thl >> 8);
    
    TMOD &= 0xf0; 
    TMOD |= 0x01;   //timer0 is 16 bit manual reload

    TL0 = g_u8_TL0;
    TH0 = g_u8_TH0;

    TR0 = 1;
    ET0 = 1;
}

VOID timer0_isr(VOID) interrupt 1
{
    TL0 = g_u8_TL0;
    TH0 = g_u8_TH0;
    
	g_sys_time.msec ++;
	
	if( g_sys_time.msec >= SYS_TIMEOUT_1SEC )
	{
		g_sys_time.msec = 0;
	    update_sys_time();
	}

	chk_alarm();
	
	if( g_sys_stopwatch.is_running == TRUE )
	{
	    g_sys_stopwatch.time.msec ++;
		if( g_sys_stopwatch.time.msec >= 1000 )
		{
			g_sys_stopwatch.time.msec = 0;
		    update_stopwatch_time();
		}
	}
}

VOID delay_ms(UINT16 u16_ms)
{
    UINT8 i;
    
    while (u16_ms--)
    {
        for (i = 0; i < 110; i++)
        {

        }
    }
}

VOID delay_us( UINT16 u16_us )
{
    while (u16_us--)
		_nop_();
}

#if 0
VOID mculib_timer1_config_us(UINT8 u8_us)
{
    //waring, u8_us * FOSC can not large than UINT32
    UINT8 u8_th = 65536 - u8_us * FOSC / 12 / 1000000UL;
    
    TMOD &= 0xf0; 
    TMOD |= 0x20;  //timer1 is 8 bit auto reload
    PT1 = 1;       //Improve the priority if you need
    
    TL1 = u8_th;
    TH1 = u8_th;

    TR1 = 1;
    ET1 = 1;
}

VOID mculib_ext_init(VOID)
{
    //ext1
    PX1 = 1; //Improve the priority
    IT1 = 1; //Falling edge trigger
    EX1 = 1;

    //ext0
    PX0 = 1;
    IT0 = 1;
    EX0 = 1;
}

VOID ext0_isr(VOID) interrupt 0
{
    //do thing
}

VOID ext1_isr(VOID) interrupt 2
{
    //do thing
}

VOID timer1_isr(VOID) interrupt 3
{    
    //do thing
}
#endif
