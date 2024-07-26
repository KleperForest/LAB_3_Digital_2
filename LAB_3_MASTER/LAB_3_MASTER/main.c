//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Universidad del Valle de Guatemala
// IE3054: ELECTRÓNICA DIGITAL 2
// Autor: Alan Gomez
// Proyecto: LAB_3_MASTER.c
// Descripción: Laboratorio, comunicación SPI_Mode_Master.
// Hardware: ATmega328p
// Created: 7/25/2024 10:56:31 AM
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#define F_CPU 16000000UL
#define BAUD 9600
#define MY_UBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "LIB_me/UART/UART.h"
#include "LIB_me/SPI/SPI.h"

uint16_t valorSPI_1 = 0;
void refreshPORT(uint16_t valor);

int main(void)
{
	// Configurar Pines como salida
	DDRD |= (1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7);
	DDRB |= (1<<DDB0)|(1<<DDB1);
	
	PORTD &= ~((1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7));
	PORTB &= ~((1<<DDB0)|(1<<DDB1));
	
	SPI_init(SPI_MASTER_OSC_DV16,SPI_Data_Order_MSB,SPI_Clock_IDLE_LOW,SPI_clock_First_EDGE);
	
	while (1)
	{
					PORTB &= ~(1<<PORTB2); // Selecciono SLAVE, QUIERO HABLAR
					
					// Solicitar y recibir el primer valor de ADC (ADC7)
					SPI_send('c');
					valorSPI_1 = SPI_receive();
					
					
					refreshPORT(valorSPI_1);
					
					PORTB |= (1<<PORTB2); // Selecciono SLAVE, YA NO QUIERO HABLAR
					
					_delay_ms(250);
	}
}

void refreshPORT(uint16_t valor)
{
	
		if (valor & 0b10000000) {
			PORTB |= (1<<PORTB1);
			} else {
			PORTB &= ~(1<<PORTB1);
		}
		if (valor & 0b01000000) {
			PORTB |= (1<<PORTB0);
			} else {
			PORTB &= ~(1<<PORTB0);
		}
		if (valor & 0b00100000) {
			PORTD |= (1<<PORTD7);
			} else {
			PORTD &= ~(1<<PORTD7);
		}
		if (valor & 0b00010000) {
			PORTD |= (1<<PORTD6);
			} else {
			PORTD &= ~(1<<PORTD6);
		}
		if (valor & 0b00001000) {
			PORTD |= (1<<PORTD5);
			} else {
			PORTD &= ~(1<<PORTD5);
		}
		if (valor & 0b00000100) {
			PORTD |= (1<<PORTD4);
			} else {
			PORTD &= ~(1<<PORTD4);
		}
		if (valor & 0b00000010) {
			PORTD |= (1<<PORTD3);
			} else {
			PORTD &= ~(1<<PORTD3);
		}
		if (valor & 0b00000001) {
			PORTD |= (1<<PORTD2);
			} else {
			PORTD &= ~(1<<PORTD2);
		}
	
}
