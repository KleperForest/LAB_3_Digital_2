//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Universidad del Valle de Guatemala
// IE3054: ELECTRÓNICA DIGITAL 2
// Autor: Alan Gomez
// Proyecto: LAB_3_SLAVE.c
// Descripción: Laboratorio, librerias LCD, ADC y UART.
// Hardware: ATmega328p
// Created: 7/19/24 8:07 a.m.
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#define F_CPU 16000000UL
#define BAUD 9600
#define MY_UBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "LIB_me/ADC/ADC.h"
#include "LIB_me/UART/UART.h"
#include "LIB_me/SPI/SPI.h"

////////////////////////////////////////////////////
// Variables.
////////////////////////////////////////////////////
char buffer[64];  // Buffer para las cadenas de caracteres a mostrar en el LCD y UART
uint16_t adc_results[2];  // Array para almacenar los resultados del ADC

uint8_t valorSPI = 0;
uint8_t adc_value_1 = 0;


////////////////////////////////////////////////////
// Prototipos de funciones
////////////////////////////////////////////////////
void display_menu(void);
void process_command(char command);

////////////////////////////////////////////////////
// Programa Principal
////////////////////////////////////////////////////

int main(void)
{
	// Configurar Pines como salida
	DDRD |= (1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7);
	DDRB |= (1<<DDB0)|(1<<DDB1);
	
	PORTD &= ~((1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7));
	PORTB &= ~((1<<DDB0)|(1<<DDB1));
	
	SPI_init(SPI_SLAVE_SS,SPI_Data_Order_MSB,SPI_Clock_IDLE_LOW,SPI_clock_First_EDGE);
	ADC_Init();  // Inicializa el ADC
	//uint8_t adc_channels[] = {7, 6};  // Canales ADC a leer (ADC7 y ADC6)
		
	SPCR |= (1<<SPIE); // Activar ISR SPI
	sei();
	
	UART_Init(BAUD);  // Inicializa la UART

	uint8_t adc_channels[] = {1, 0};  // Canales ADC a leer (ADC7 y ADC6)


	// Mostrar el menú inicial en la consola
	display_menu();

	while (1)
	{
		// Leer los valores de los ADC
		ADC_Read_Multiple(adc_channels, adc_results, 2);

		// Leer y procesar los comandos de la UART
		if (UCSR0A & (1 << RXC0)) {  // Verificar si hay datos disponibles en el buffer de recepción
			char received_char = UART_Receive();
			process_command(received_char);
		}

		_delay_ms(50);  // Espera medio segundo antes de la siguiente actualización
	}
}

////////////////////////////////////////////////////
// Funciones auxiliares
////////////////////////////////////////////////////

void display_menu(void) {
	UART_TransmitString("\r\n***** Menu *****\r\n");
	UART_TransmitString("1. Mostrar valores de ADC\r\n");
	UART_TransmitString("*****************\r\n");
	UART_TransmitString("Seleccione una opción: ");
}

void process_command(char command) {
	switch (command) {
		case '1':
		snprintf(buffer, sizeof(buffer), "Valores ADC - ADC6: %u, ADC7: %u\r\n", adc_results[1], adc_results[0]);
		UART_TransmitString(buffer);
		break;
		default:
		UART_TransmitString("Opción inválida. Por favor, seleccione una opción válida.\r\n");
		break;
	}
	display_menu();
}

ISR(SPI_STC_vect) {
		valorSPI = SPDR;
		if (valorSPI == 'c') {
			SPI_Write(adc_results[0]);
			}
}