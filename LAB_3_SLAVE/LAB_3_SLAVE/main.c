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
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "LIB_me/ADC/ADC.h"
#include "LIB_me/UART/UART.h"

////////////////////////////////////////////////////
// Variables.
////////////////////////////////////////////////////
char buffer[64];  // Buffer para las cadenas de caracteres a mostrar en el LCD y UART
uint16_t adc_results[2];  // Array para almacenar los resultados del ADC

int voltage1, voltage2; //Mapeo de ADC

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
	
	ADC_Init();  // Inicializa el ADC
	UART_Init(BAUD);  // Inicializa la UART

	uint8_t adc_channels[] = {7, 6};  // Canales ADC a leer (ADC7 y ADC6)


	// Mostrar el menú inicial en la consola
	display_menu();

	while (1)
	{
		// Leer los valores de los ADC
		ADC_Read_Multiple(adc_channels, adc_results, 2);
		
		// Convertir los valores ADC a voltaje
		voltage1 = (int)(((adc_results[0] * 5.0) / 896));
		voltage2 = (int)(((adc_results[1] * 5.0) / 896)*);


		// Leer y procesar los comandos de la UART
		if (UCSR0A & (1 << RXC0)) {  // Verificar si hay datos disponibles en el buffer de recepción
			char received_char = UART_Receive();
			process_command(received_char);
		}

		_delay_ms(500);  // Espera medio segundo antes de la siguiente actualización
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
		snprintf(buffer, sizeof(buffer), "Valores ADC - ADC6: %u, ADC7: %u\r\n", voltage1, voltage2);
		UART_TransmitString(buffer);
		break;
		default:
		UART_TransmitString("Opción inválida. Por favor, seleccione una opción válida.\r\n");
		break;
	}
	display_menu();
}