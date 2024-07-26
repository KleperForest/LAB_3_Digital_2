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


char buffer[64];
uint16_t valorSPI_1 = 0;
uint16_t valorSPI_2 = 0;
int counter = 0;  // Contador inicial

void refreshPORT(uint8_t valor);
void send_data_to_computer(uint16_t adc1, uint16_t adc2, int counter);
void process_command(char command);

int main(void) {
	// Configurar Pines como salida
	DDRD |= (1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7);
	DDRB |= (1<<DDB0)|(1<<DDB1);
	
	PORTD &= ~((1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7));
	PORTB &= ~((1<<DDB0)|(1<<DDB1));
	
	// Iniciar Librerias SPI y UART
	SPI_init(SPI_MASTER_OSC_DV16, SPI_Data_Order_MSB, SPI_Clock_IDLE_LOW, SPI_clock_First_EDGE);
	UART_Init(BAUD);
	
	while (1) {
		PORTB &= ~(1<<PORTB2); // Selecciono SLAVE, QUIERO HABLAR
		
		// Solicitar y recibir el primer valor de ADC (ADC7)
		SPI_send('c');
		valorSPI_1 = SPI_receive();
		
		// Solicitar y recibir el segundo valor de ADC (ADC6)
		SPI_send('d');
		valorSPI_2 = SPI_receive();
		
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

void send_data_to_computer(uint16_t adc1, uint16_t adc2, int counter) {
	snprintf(buffer, sizeof(buffer), "ADC7: %d, ADC6: %d, Counter: %d\r\n", adc1, adc2, counter);
	UART_TransmitString(buffer);
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

