#include "comm.h"

extern UINT32 g_u32_seg_val;
extern SysTimeDef g_sys_time;
extern SysStopWatchDef  g_sys_stopwatch;

static UINT8 code SEG7CODE[] = 
{
/*   0      1     2    3     4     5     6     7     8     9     -     .    È«Ãð */
	0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xbf, 0x7f, 0xff
};

static VOID seg_display(UINT8 u8_val)
{
    P0 = SEG7CODE[u8_val % _countof(SEG7CODE)];
}

static VOID seg_display_with_dot( UINT8 u8_val, UINT8 isDispDot )
{
    UINT8 val;
	
	val = SEG7CODE[u8_val % _countof(SEG7CODE)];
	
	P0 = ( isDispDot ? (val&0x7f) : val );
}

void disp_time( SysTimeDef time )
{
	UINT8 i, val;
    UINT8 k = 0x01;
    
    for (i = 0; i < 8; i++)
    {
		k =_cror_(k, 1);
		P2 = 0;
		switch( i )
		{
		    case 0:
				val = time.sec % 10;
				break;
			case 1:
				val = time.sec / 10;
				break;
			case 2:
				val = 10;
				break;
			case 3:
				val = time.min % 10;
				break;
			case 4:
				val = time.min / 10;
				break;
			case 5:
				val = 10;
				break;
			case 6:
				val = time.hour % 10;
				break;
			case 7:
				val = time.hour / 10;
				break;
			default:
				continue;
				break;
		}
		P2 = k;
        seg_display(val);
		delay_ms(5);
    }
}

void disp_stopwatch()
{
	SysTimeDef time;
	UINT8 i, val;
	UINT8 isDispDot = FALSE;
    UINT8 k = 0x01;

	time = g_sys_stopwatch.time;
    for (i = 0; i < 8; i++)
    {
		k =_cror_(k, 1);
		P2 = 0;
		switch( i )
		{
		    case 0:
				val = (time.msec / 1) % 10;
				isDispDot = FALSE;
				break;
			case 1:
				val = (time.msec / 10) % 10;
			    isDispDot = FALSE;
				break;
			case 2:
				val = (time.msec / 100) % 10;
			    isDispDot = FALSE;
				break;
			case 3:
				val = (time.sec / 1) % 10;
			    isDispDot = TRUE;
				break;
			case 4:
				val = (time.sec / 10) % 10;
			    isDispDot = FALSE;
				break;
			case 5:
				val = (time.min / 1) % 10;
			    isDispDot = TRUE;
				break;
			case 6:
				val = (time.min / 10) % 10;
			    isDispDot = FALSE;
				break;
			case 7:
				val = (time.hour / 1) % 10;
			    isDispDot = TRUE;
				break;
			default:
				continue;
				break;
		}
		P2 = k;
        seg_display_with_dot(val, isDispDot );
		delay_ms(5);
    }
}

//void disp_digit( UINT32 digit )
//{
//    UINT8 i;
//    UINT8 k = 0x01;
//    UINT32 u32_val = digit;
//    
//    for (i = 0; i < 8; i++)
//    {
//        k =_cror_(k, 1);
//        P2 = 0;
//        seg_display(u32_val % 10);
//        P2 = k;
//        u32_val /= 10;
//    }
//}
