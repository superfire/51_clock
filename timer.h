#ifndef __TIMER_H__
#define __TIMER_H__

//Suggested timer base
#define TIMER_BASE_1MS       (1)
#define TIMER_BASE_10MS      (10)
#define TIMER_BASE_100MS     (100)
#define TIMER_BASE_1000MS    (1000)

#define SYS_TIMEOUT_5MS     (5)
#define SYS_TIMEOUT_10MS    (10)
#define SYS_TIMEOUT_50MS    (50)   // TIMER_BASE_1MS * 50
#define SYS_TIMEOUT_100MS   (100)   
#define SYS_TIMEOUT_500MS   (500)
#define SYS_TIMEOUT_1SEC    (1000)  
#define SYS_TIMEOUT_2SEC    (2000)

// Timer0 is a general 16-bit timer.
VOID timer0_config_ms(UINT8 u8_ms);

// Timer1 is a general 8-bit timer.
VOID timer1_config_us(UINT8 u8_us);
VOID mculib_ext_init(VOID);


//
VOID delay_ms(UINT16 u16_ms);


extern UINT16 g_u16_sys_timer;
extern UINT16 g_u16_key_timer;


#define enable_interrupt()   (EA = 1)
#define disable_interrupt()  (EA = 0)


#endif //endif use timer module
