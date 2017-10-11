/*
 * lcd.c
 *
 *  Created on: Mar 3, 2017
 *      Author: otm2
 */
#include "lcd.h"

void lcdwrite(uint8_t data, uint8_t send_data)
{
	PORTB &= ~(1 << LCDREAD);
	PORTD &= ~(1 << LCDRS);
	PORTD |= send_data << LCDRS;
	PORTD |= 1 << LCDENABLE;
	PORTD &= 0xF;
	PORTD |= data << 4;
	_delay_ms(2);
	PORTD &= ~(1 << LCDENABLE);
}

void lcdinit()
{
	PORTB &= ~(1 << LCDON);
	_delay_ms(18);
	lcdwrite(0x3, 0);
	_delay_ms(5);
	lcdwrite(0x3, 0);
	_delay_ms(1);
	lcdwrite(0x3, 0);
	// set 4 bit bus
	lcdwrite(0x2, 0);

	// set dual line and font size can't set
	lcdwrite(0x2, 0);
	lcdwrite(0x8, 0);

	lcdwrite(0x0, 0);
	lcdwrite(0xF, 0);

	// clear lcd
	lcdwrite(0x0, 0);
	lcdwrite(0x1, 0);

	lcdwrite(0x0, 0);
	lcdwrite(0x6, 0);
}

void lcdclear()
{
	lcdwrite(0x0, 0);
	lcdwrite(0x1, 0);
}

void lcdcursor(uint8_t on)
{
}

void lcdgotoxy(uint8_t x, uint8_t line)
{
	lcdwrite(0x8 + (line-1)*4, 0);
	lcdwrite(x-1, 0);
}

void lcdline2()
{
	_delay_ms(10);
	lcdwrite(0xC, 0);
	lcdwrite(0x0, 0);
	_delay_ms(10);
}
void lcdwritechar(uint8_t data)
{
	lcdwrite(data >> 4, 1);
	lcdwrite(data, 1);
}

void lcdwritestring(const char* string)
{
	uint8_t i = 0;
	while(string[i] != 0x00)
	{
		lcdwritechar(string[i]);
		i++;
	}
}



void forfun()
{
	lcdclear();
	lcdwritestring("laper");
	lcdgotoxy(1, 2);
	lcdwritestring("bobo yuk");
	_delay_ms(1000);
	lcdclear();
	lcdwritestring("mari-mari");
	lcdgotoxy(1, 2);
	lcdwritestring("kita bobo");
	_delay_ms(1000);
}
