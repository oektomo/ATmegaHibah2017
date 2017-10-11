/*
 * tools.h
 *
 *  Created on: Mar 4, 2017
 *      Author: otm2
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include <stdint.h>

#define RING_BUFFER_SIZE 100
#define WRITE_BUFF (1 << 2)
#define NEW_RX	(1 << 1)
#define PHERIPHERAL_OFF 0
#define PHERIPHERAL_ON 1
#define PHERIPHERAL_AMOUNT 15

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

#endif /* TOOLS_H_ */
