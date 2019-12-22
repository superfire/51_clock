#include "comm.h"

VOID uart_init(UINT16 u16_baud_rate)
{
    TMOD = 0x20; //such as AT89S52
    SCON = 0x50; 
    TH1 = TL1 = -(FOSC/12/32/u16_baud_rate); 
    TR1 = 1; 

    ES = 1;
}

VOID uart_print_char(UINT8 u8_byte)
{
    SBUF = u8_byte;
    while (!TI);
    TI = 0; 
}

VOID _send_ascii(UINT8 u8_byte)
{
    if (u8_byte > 0x09)
    {
        u8_byte = (u8_byte - 10) + 0x41;    // 'A' -> 0x41
    }
    else
    {
        u8_byte = u8_byte + 0x30;           // '0' -> 0x30
    }
    uart_print_char(u8_byte);   
}

VOID uart_print_dec(UINT16 u16_word)
{
    UINT8 u8_buff[5];
    UINT8 u8_i = 0;
    BOOL  b_start = FALSE;

    while(u8_i < 5)
    {
        u8_buff[u8_i] =  u16_word % 10;
        u16_word /= 10;
        u8_i ++;
    }

    while(u8_i)
    {
        if (u8_buff[u8_i - 1] != 0)
        {
            b_start = TRUE;
        }

        if (b_start)
        {
            uart_print_char(u8_buff[u8_i - 1] + 0x30);     
        }
        
        u8_i --;
    }

    if (!b_start)
    {
        uart_print_char(0x30);
    }
}

VOID uart_print_hex(UINT16 u16_word)
{
    UINT8 value;
    UINT8 i;
    
    i = (u16_word > 0xFF) ? 4 : 2;
    // High nibble    
    while (i --)
    {
        value = (u16_word >> (i * 4)) & 0x0F;
        _send_ascii(value);
    }
}

VOID uart_print_string(UINT8 *u8_string)
{
    while (*u8_string)
    {
        uart_print_char(*u8_string++);
    }
}

VOID uart_log(UINT8 *u8_string)
{
    uart_print_string(u8_string);
    uart_print_string("\r\n");
}

VOID uart_log1(UINT8 *u8_string, UINT16 u16_hex)
{
    uart_print_string(u8_string);
    uart_print_string("0x");
    uart_print_hex(u16_hex);
    uart_print_string("\r\n");
}

VOID uart_log2(UINT8 *u8_string, UINT16 u16_dec)
{
    uart_print_string(u8_string);
    uart_print_dec(u16_dec);
    uart_print_string("\r\n");
}

VOID uart_isr(VOID) interrupt 4
{
    UINT8 u8_data;
    
    if (RI)
    {
        u8_data = SBUF;
        uart_print_char(u8_data);
        RI = 0;
    }
}

