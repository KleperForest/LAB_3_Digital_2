//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Universidad del Valle de Guatemala
// IE3054: ELECTR�NICA DIGITAL 2
// Autor: Alan Gomez
// Proyecto: LAB_3_SLAVE.c
// Descripci�n: Laboratorio, comunicaci�n SPI_Mode_Master.
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
#include "LIB_me/SPI/SPI.h"

uint8_t valorADC = 0;

void refreshPORT(uint8_t valor);
void initADC(void);

int main(void)
{
	// Configurar Pines como salida
	DDRD |= (1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7);
	DDRB |= (1<<DDB0)|(1<<DDB1);
	
	PORTD &= ~((1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7));
	PORTB &= ~((1<<DDB0)|(1<<DDB1));
	
	SPI_init(SPI_SLAVE_SS, SPI_Data_Order_MSB, SPI_Clock_IDLE_LOW, SPI_clock_First_EDGE);
	initADC();
	SPCR |= (1<<SPIE); // Activar ISR SPI
	sei();
	
	while (1)
	{
		ADCSRA |= (1<<ADSC);
		_delay_ms(100);
	}
}

void initADC(void)
{
	// Seleccionar ADC7
	ADMUX = (1<<REFS0) | (1<<ADLAR) | 7;  // Vref = AVCC, Justificaci�n a la izquierda, Seleccionar ADC7

	// Encender ADC
	ADCSRA = (1<<ADEN) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);  // Habilitar ADC, habilitar interrupci�n, preescalar de 128

	
}

ISR(ADC_vect)
{
	valorADC = ADCH;
	ADCSRA |= (1<<ADIF);
}

ISR(SPI_STC_vect)
{
	uint8_t valorSPI = SPDR;
	if (valorSPI == 'c') {
		SPI_send(valorADC);
	}
}
