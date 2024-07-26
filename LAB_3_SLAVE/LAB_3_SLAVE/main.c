//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Universidad del Valle de Guatemala
// IE3054: ELECTRÓNICA DIGITAL 2
// Autor: Alan Gomez
// Proyecto: LAB_3_SLAVE.c
// Descripción: Laboratorio, comunicación SPI_Mode_Master.
// Hardware: ATmega328p
// Created: 7/25/2024 10:56:31 AM
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>
#include "LIB_me/ADC/ADC.h"
#include "LIB_me/SPI/SPI.h"

uint8_t valorSPI = 0;
uint8_t adc_value_1 = 0;
uint8_t adc_value_2 = 0;
uint16_t adc_results[2];  // Array para almacenar los resultados del ADC

void refreshPORT(uint8_t valor);

int main(void)
{
	// Configurar Pines como salida
	DDRD |= (1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7);
	DDRB |= (1<<DDB0)|(1<<DDB1);
	
	PORTD &= ~((1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7));
	PORTB &= ~((1<<DDB0)|(1<<DDB1));
	
	SPI_init(SPI_SLAVE_SS,SPI_Data_Order_MSB,SPI_Clock_IDLE_LOW,SPI_clock_First_EDGE);
	ADC_Init();
	uint8_t adc_channels[] = {7, 6};  // Canales ADC a leer (ADC7 y ADC6)
	SPCR |= (1<<SPIE); // Activar ISR SPI
	sei();
	
	while (1)
	{
		ADC_Read_Multiple(adc_channels, adc_results, 2);
		adc_value_1 = adc_results[0];
		adc_value_2 = adc_results[1];
		
	}
}

ISR(SPI_STC_vect) {
	valorSPI = SPDR;
	if (valorSPI == 'c') {
		SPI_send(adc_value_1);
		} else if (valorSPI == 'd') {
		SPI_send(adc_value_2);
	}
}