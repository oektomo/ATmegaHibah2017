/*
 * uart.c
 *
 *  Created on: Oct 11, 2017
 *      Author: otm2
 */
#include "uart.h"
#include <avr/io.h>

void UART_Init(void)
{
	UCSRA |= (1 << U2X);
	UCSRB = (1 << RXEN)|(1 << TXEN);
	UBRRL = 51;	// 9600
	UBRRL = 8;	// 115200
}

void UART_IT_Init(void)
{
	UCSRB |= (1 << RXCIE);
}

void UART_Tx(uint8_t data)
{
	while( !(UCSRA & (1 << UDRE)) );
	UDR = data;
}

void UARTWriteString(const char* string)
{
	uint8_t i = 0;
	while(string[i] != 0x00)
	{
		UART_Tx(string[i]);
		i++;
	}
}
