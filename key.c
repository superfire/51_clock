#include "comm.h"


sbit PIN_KEY_1 = P1^0;
sbit PIN_KEY_2 = P1^1;
sbit PIN_KEY_3 = P1^2;
sbit PIN_KEY_4 = P1^3;
sbit PIN_KEY_5 = P1^4;
sbit PIN_KEY_6 = P1^5;


UINT8 _do_key_scan(VOID)
{
    if (!PIN_KEY_1)
    {
        return KEY_HOUR;
    }
    else if (!PIN_KEY_2)
    {
        return KEY_MIN;
    }
    else if (!PIN_KEY_3)
    {
        return KEY_SEC;
    }
	else if (!PIN_KEY_4)
    {
        return KEY_MODE;
    }
	else if (!PIN_KEY_5)
    {
        return KEY_START_STOP;
    }
	else if (!PIN_KEY_6)
    {
        return KEY_CLEAR;
    }

    return KEY_NONE;
}

UINT8 key_scan(VOID)
{
    static UINT8 s_u8_key_status = KEY_NONE;
    UINT8 u8_key_val;

    u8_key_val = _do_key_scan();

    if (s_u8_key_status != u8_key_val)
    {
        s_u8_key_status = u8_key_val;
        delay_ms(10);
        return _do_key_scan();
    }

    return KEY_NONE;
}
