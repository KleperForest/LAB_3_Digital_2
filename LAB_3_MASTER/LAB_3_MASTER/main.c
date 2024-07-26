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

////////////////////////////////////////////////////
// Variables.
////////////////////////////////////////////////////
char buffer[64];  // Buffer para las cadenas de caracteres a mostrar en UART
uint16_t valorSPI_1 = 0;// Valor de POT_1
uint16_t valorSPI_2 = 0;// Valor de POT_2

void refreshPORT(uint8_t valor);//Refrescar leds

int counter = 0;  // Contador inicial

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
	
	// Iniciar Librerias SPI y UART
	SPI_init(SPI_MASTER_OSC_DV16, SPI_Data_Order_MSB, SPI_Clock_IDLE_LOW, SPI_clock_First_EDGE);
	UART_Init(BAUD);
	
	display_menu(); // Mostrar el menú al inicio
	
	while (1)
	{
		PORTB &= ~(1<<PORTB2); // Selecciono SLAVE, QUIERO HABLAR
		
		// Solicitar y recibir el primer valor de ADC (ADC7)
		SPI_send('c');
		valorSPI_1 = SPI_receive();
		
		// Solicitar y recibir el segundo valor de ADC (ADC6)
		SPI_send('d');
		valorSPI_2 = SPI_receive();
		
		refreshPORT(counter);
		
		PORTB |= (1<<PORTB2); // Selecciono SLAVE, YA NO QUIERO HABLAR
		
		// Mapeo de ADC a voltaje
		int voltage1 = (int)(((valorSPI_1 * 5.0) / 1023) * 100);
		int voltage2 = (int)(((valorSPI_2 * 5.0) / 1023) * 100);
		
		// Leer y procesar los comandos de la UART
		if (UCSR0A & (1 << RXC0)) {  // Verificar si hay datos disponibles en el buffer de recepción
			char received_char = UART_Receive();
			process_command(received_char, voltage1, voltage2);
		}
		
		_delay_ms(150);
	}
}

////////////////////////////////////////////////////
// Funciones auxiliares
////////////////////////////////////////////////////

void display_menu() {
	UART_TransmitString("\r\n***** Menu *****\r\n");
	UART_TransmitString("1. Mostrar valores de ADC7\r\n"); // Valor en ADC en voltaje voltage1
	UART_TransmitString("2. Mostrar valores de ADC6\r\n"); // Valor en ADC en voltaje voltage2
	UART_TransmitString("+. Incrementar contador (+)\r\n");
	UART_TransmitString("-. Decrementar contador (-)\r\n");
	UART_TransmitString("4. Mostrar valor del contador\r\n");
	UART_TransmitString("*****************\r\n");
	UART_TransmitString("Seleccione una opción: ");
}

void process_command(char command, int voltage1, int voltage2) {
	switch (command) {
		case '1':
		snprintf(buffer, sizeof(buffer), "Valor ADC7: %d.%02d V\r\n", voltage1 / 100, voltage1 % 100);
		UART_TransmitString(buffer);
		break;
		case '2':
		snprintf(buffer, sizeof(buffer), "Valor ADC6: %d.%02d V\r\n", voltage2 / 100, voltage2 % 100);
		UART_TransmitString(buffer);
		break;
		case '+':
		counter++;
		UART_TransmitString("Contador incrementado.\r\n");
		break;
		case '-':
		counter--;
		UART_TransmitString("Contador decrementado.\r\n");
		break;
		case '4':
		snprintf(buffer, sizeof(buffer), "Valor del contador: %d\r\n", counter);
		UART_TransmitString(buffer);
		break;
		default:
		UART_TransmitString("Opción inválida. Por favor, seleccione una opción válida.\r\n");
		break;
	}
	display_menu();
}

void refreshPORT(uint8_t valor) {
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
