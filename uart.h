/*
 * uart.h
 *
 *  Created on: Oct 11, 2017
 *      Author: otm2
 */

#ifndef UART_H_
#define UART_H_

#define UART_DEBUG

#include <stdint.h>

void UART_Init(void);
void UART_IT_Init(void);
void UART_Tx(uint8_t data);
void UARTWriteString(const char* string);
void UARTWriteInt(int8_t int8bit);

#endif /* UART_H_ */
