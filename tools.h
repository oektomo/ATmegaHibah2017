/*
 * tools.h
 *
 *  Created on: Mar 4, 2017
 *      Author: otm2
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include <stdint.h>
#include <avr/io.h>

#define RING_BUFFER_SIZE 100
#define WRITE_BUFF (1 << 2)
#define NEW_RX	(1 << 1)
#define PHERIPHERAL_OFF 0
#define PHERIPHERAL_ON 1
#define PHERIPHERAL_AMOUNT 15

#define PORT_PH1 PORTC
#define PIN_PH1 (1 << PIN5)
#define PORT_PH2 PORTC
#define PIN_PH2 (1 << PIN4)
#define PORT_PH3 PORTC
#define PIN_PH3 (1 << PIN2)
#define PORT_PH4 PORTC
#define PIN_PH4 (1 << PIN1)
#define PORT_PH5 PORTC
#define PIN_PH5 (1 << PIN0)
#define PORT_PH6 PORTB
#define PIN_PH6 (1 << PIN5)
#define PORT_PH7 PORTB
#define PIN_PH7 (1 << PIN4)
#define PORT_PH8 PORTB
#define PIN_PH8 (1 << PIN3)
#define PORT_PH9 PORTB
#define PIN_PH9 (1 << PIN2)
#define PORT_PH10 PORTB
#define PIN_PH10 (1 << PIN1)

void ftoa(float n, char *res, int afterpoint);

// ring buffer
typedef struct {
	uint8_t pin; // pointer in (write)
	uint8_t pout; // pointer out (read)
	int8_t n;	// amount of data inside the buffer
	uint8_t buff[RING_BUFFER_SIZE];
} buffer_typedef;

typedef struct {
	int id;
	int state;
} pheripheral_typedef;

void write_buffer(uint8_t data, buffer_typedef* Buffer);
uint8_t read_buffer(buffer_typedef* Buffer);
uint8_t check_buffer(buffer_typedef* Buffer);
void init_buffer(buffer_typedef* Buffer);
int match(buffer_typedef* Buffer, pheripheral_typedef* Pheripheral);
void pheripheralInit(pheripheral_typedef* Pheripheral);
void pheripheralSwitch(pheripheral_typedef* Pheripheral, int PheripID);
#endif /* TOOLS_H_ */
