/*
 * lcd.h
 *
 *  Created on: Mar 3, 2017
 *      Author: otm2
 */

#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>

#define LCDON 0
#define LCDDATA 4
#define LCDDATAPORT DDRD
#define LCDENABLE 3// PD3
#define LCDREAD 2 // PB2
#define LCDRS 2 // PD2

void lcdwrite(uint8_t data, uint8_t send_data);
void lcdinit();
void lcdclear();
void lcdcursor(uint8_t on);
void lcdgotoxy(uint8_t x, uint8_t y);
void lcdline2();
void lcdwritechar(uint8_t data);
void lcdwritestring(const char* string);


void forfun();

#endif /* LCD_H_ */
