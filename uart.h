#ifndef __UART_H__
#define __UART_H__


VOID uart_init(UINT16 u16_baud_rate);

VOID uart_print_char(UINT8 u8_byte);
VOID uart_print_dec(UINT16 u16_word);
VOID uart_print_hex(UINT16 u16_word);
VOID uart_print_string(UINT8 *u8_string);

//application interface
VOID uart_log(UINT8 *u8_string);
VOID uart_log1(UINT8 *u8_string, UINT16 u16_hex);
VOID uart_log2(UINT8 *u8_string, UINT16 u16_dec);


#ifdef USE_DEBUGGING_LOG
#define LOG(X)      uart_log((UINT8*)X)

#define LOG1(X, Y)  uart_log1((UINT8*)X, Y)

#define LOG2(X, Y)  uart_log2((UINT8*)X, Y)
    
#else
#define LOG(X)
#define LOG1(X, Y)
#define LOG2(X, Y)
#endif



#endif //__UART_H__
