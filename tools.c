/*
 * tools.c
 *
 *  Created on: Mar 4, 2017
 *      Author: otm2
 */

// C program for implementation of ftoa()
#include <math.h>
#include <stdlib.h>
#include "tools.h"
#include "uart.h"
#ifdef USE_LCD
#include "lcd.h"
#endif

// reverses a string 'str' of length 'len'
void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

// ring buffer tools
void write_buffer(uint8_t data, buffer_typedef* Buffer)
{
	(Buffer->n)++;
	if (Buffer->n < RING_BUFFER_SIZE) {
		Buffer->buff[Buffer->pin] = data;
		(Buffer->pin)++;
		Buffer->pin = Buffer->pin % RING_BUFFER_SIZE;
	} else {
		(Buffer->n)--;
	}
}

uint8_t read_buffer(buffer_typedef* Buffer)
{
	(Buffer->n)--;
	uint8_t temp = 0;
	if (Buffer->n >= 0) {
		temp = Buffer->buff[Buffer->pout];
		(Buffer->pout)++;
		Buffer->pout = Buffer->pout % RING_BUFFER_SIZE;
	} else {
		(Buffer->n)++;
	}
	return temp;
}

uint8_t check_buffer(buffer_typedef* Buffer)
{
		uint8_t temp = 0;
		if (Buffer->n > 0) {
			temp = Buffer->buff[Buffer->pout];
		}
		return temp;
}

void init_buffer(buffer_typedef* Buffer)
{
	Buffer->n = 0;
	Buffer->pin = 0;
	Buffer->pout = 0;
}

int match(buffer_typedef* Buffer, pheripheral_typedef* Pheripheral)
{
/*#ifdef UART_DEBUG
	//UART_Tx(" ");
	UARTWriteInt(Buffer->n);
	UARTWriteString("\n\r");
#endif*/
	int retVal = -1;
	// read if received data already hit one frame
	// package example Sxxx&xxxE
	if(Buffer->n > 8) {
		if(check_buffer(Buffer) != 'S') {
#ifdef USE_LCD
			lcdwritechar( read_buffer(Buffer) );	// waste if we don't get Header
#else
			read_buffer(Buffer);
#endif
		} else {
			char idNumChar[4], idStateChar[4];
			read_buffer(Buffer);	// ditch "S" header
			for (int i = 0; i < 3; i++) {
				idNumChar[i] = read_buffer(Buffer); // copy value id consist 3 char
			}
			idNumChar[3] = '\0';
			int idNumInt = atoi(idNumChar);
			read_buffer(Buffer);	// ditch "&" separator
			for (int i = 0; i < 3; i++) {
				idStateChar[i] = read_buffer(Buffer); // copy state consist 3 char
			}
			idStateChar[3] = '\0';
			int idStateInt = atoi(idStateChar);
			read_buffer(Buffer);	// ditch "E" tail

			if( (idNumInt > 0) && (idNumInt <= PHERIPHERAL_AMOUNT) ) {
				Pheripheral[idNumInt].id = idNumInt;
				Pheripheral[idNumInt].state = idStateInt;
			}
			retVal = idNumInt;
		}

	}
	return retVal;
}

void pheripheralInit(pheripheral_typedef* Pheripheral)
{
	for(int i = 0; i < PHERIPHERAL_AMOUNT; i++) {
		Pheripheral[i].id = i;
		Pheripheral[i].state = PHERIPHERAL_OFF;
	}
}

void printPheripheralState(pheripheral_typedef* Pheripheral)
{
	char charBuff[8];
	for (int i = 0; i<PHERIPHERAL_AMOUNT; i++) {
		UARTWriteString("\n\r");
		itoa(Pheripheral[i].id, charBuff, 10);
		UARTWriteString(charBuff);
		UARTWriteString(" ");

		itoa(Pheripheral[i].state, charBuff, 10);
		UARTWriteString(charBuff);
	}
	UARTWriteString("\n\r");
}

void pheripheralSwitch(pheripheral_typedef* Pheripheral, int PheripID)
{
	if( (PheripID >= 0) && (PheripID < PHERIPHERAL_AMOUNT) ) {
		if (Pheripheral[PheripID].state == 1) {
			switch (PheripID) {
			case 1:
				PORT_PH1 |= PIN_PH1;
				break;
			case 2:
				PORT_PH2 |= PIN_PH2;
				break;
			case 3:
				PORT_PH3 |= PIN_PH3;
				break;
			case 4:
				PORT_PH4 |= PIN_PH4;
				break;
			case 5:
				PORT_PH5 |= PIN_PH5;
				break;
			case 6:
				PORT_PH6 |= PIN_PH6;
				break;
			case 7:
				PORT_PH7 |= PIN_PH7;
				break;
			case 8:
				PORT_PH8 |= PIN_PH8;
				break;
			case 9:
				PORT_PH9 |= PIN_PH9;
				break;
			case 10:
				PORT_PH10 |= PIN_PH10;
				break;
			}
		} else {
			switch (PheripID) {
			case 1:
				PORT_PH1 &= ~PIN_PH1;
				break;
			case 2:
				PORT_PH2 &= ~PIN_PH2;
				break;
			case 3:
				PORT_PH3 &= ~PIN_PH3;
				break;
			case 4:
				PORT_PH4 &= ~PIN_PH4;
				break;
			case 5:
				PORT_PH5 &= ~PIN_PH5;
				break;
			case 6:
				PORT_PH6 &= ~PIN_PH6;
				break;
			case 7:
				PORT_PH7 &= ~PIN_PH7;
				break;
			case 8:
				PORT_PH8 &= ~PIN_PH8;
				break;
			case 9:
				PORT_PH9 &= ~PIN_PH9;
				break;
			case 10:
				PORT_PH10 &= ~PIN_PH10;
				break;
			}
		}
#ifdef UART_DEBUG
		printPheripheralState(Pheripheral);
#endif
	}

}
