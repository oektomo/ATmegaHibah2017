/*
 * adc.c
 *
 *  Created on: Mar 4, 2017
 *      Author: otm2
 */
#include <avr/io.h>
#include "adc.h"


void adcinit()
{
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADEN);
}

uint16_t adcread()
{
	while( (ADCSRA & (1 << ADIF)) == 0 );
	ADCSRA |= 1 << ADIF;
	return ADC;
}

void adcstart()
{
	ADCSRA |= 1 << ADSC;
}
