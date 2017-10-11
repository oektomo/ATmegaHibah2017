/*
 * main.c
 *
 *  Created on: Mar 3, 2017
 *      Author: otm2
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd.h"
#include "adc.h"
#include "uart.h"
#include "tools.h"

volatile uint8_t bufferRx;

ISR(USART_RXC_vect)
{
	bufferRx = UDR;
	UART_Tx(bufferRx);
}

int main()
{
	buffer_typedef ringBuff1;
	pheripheral_typedef Pheripheral1[PHERIPHERAL_AMOUNT];
	char buffer[8];
	uint16_t adcBuff = 12;
	DDRB = 0xFF;
	DDRD = 0xFF;

	PORTC = 0xFF;
	lcdinit();

	lcdwritestring("Good Job Today");
	lcdgotoxy(2, 2);
	lcdwritestring("Hungry");

	UART_Init();
	init_buffer(&ringBuff1);
	pheripheralInit(Pheripheral1);

	_delay_ms(1000);
	UARTWriteString("seems good, done eating\n\r");
	UART_IT_Init();
	sei();

	uint8_t status = 0, oldBuffer = 0;
	int tempInt;
	while(1) {

		// put Received buffer into ring Buffer
		cli();
		if(oldBuffer != bufferRx) {
			oldBuffer = bufferRx;
			status |= NEW_RX;
		}
		sei();

		if ( status & NEW_RX ) {
			status &= ~NEW_RX;
			//status |= WRITE_BUFF;

			write_buffer(oldBuffer, &ringBuff1);
			lcdgotoxy(2, 2);
			itoa(ringBuff1.n, buffer, 10);
			lcdwritestring(buffer);
		}
		tempInt = match(&ringBuff1, Pheripheral1);

		if( (tempInt > 0) && (tempInt <= PHERIPHERAL_AMOUNT) ) {
			itoa(tempInt, buffer, 10);
			lcdgotoxy(2, 1);
			lcdwritestring("Pherip no: ");
			lcdwritestring(buffer);

			for (int i = 0; i<PHERIPHERAL_AMOUNT; i++) {
				itoa(Pheripheral1[i].id, buffer, 10);
				UARTWriteString(buffer);
				UARTWriteString(" ");

				itoa(Pheripheral1[i].state, buffer, 10);
				UARTWriteString(buffer);
				UARTWriteString("\n\r");
			}
		}


	}
	lcdclear();

	itoa(adcBuff, buffer, 10);
	lcdwritestring(buffer);
	//adcinit();
	//adcstart();

	lcdgotoxy(1, 2);
	lcdwritestring("adc: ");

	while(1)
	{
		PORTD = 0xFF;
		_delay_us(3);
		PORTD = 0x00;
		_delay_us(2);
		/*
		adcBuff = adcread();
		adcstart();

		float adcVolt = (float)adcBuff;
		adcVolt = 5 * adcVolt / 1024;
		ftoa (adcVolt, buffer, 3);
		lcdgotoxy(1,1);
		lcdwritechar(' ');
		lcdwritestring(buffer);
		lcdwritechar(' ');
		lcdwritestring("Volt");

		itoa(adcBuff, buffer, 10);
		lcdgotoxy(6, 2);
		lcdwritestring("    ");
		lcdgotoxy(6, 2);
		lcdwritestring(buffer);
		_delay_ms(100);*/

	}
	return 0;
}

