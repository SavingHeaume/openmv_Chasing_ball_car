#ifndef __MY_UART_H__
#define __MY_UART_H__

#include "usart.h"

//extern uint16_t uart_2_rx[3];
extern uint16_t rx_uint16;
extern uint16_t flag;
extern uint16_t count;

extern uint16_t CX, CY, CZ;

void UART1_Send(uint8_t* data, uint16_t len);
void UART1_Receive(uint16_t len);

void UART2_Send(uint8_t* data, uint16_t len);
void UART2_Receive();

void Openmv_Receive(uint16_t data);

#endif
