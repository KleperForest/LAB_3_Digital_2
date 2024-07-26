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
		
		// Solicitar y recibir valores de ADC
		SPI_send('c');
		valorSPI_1 = SPI_receive();
		
		SPI_send('d');
		valorSPI_2 = SPI_receive();
		
		PORTB |= (1<<PORTB2); // Selecciono SLAVE, YA NO QUIERO HABLAR
		
		// Enviar datos al computador
		send_data_to_computer(valorSPI_1, valorSPI_2, counter);
		
		// Leer y procesar comandos de la UART
		if (UCSR0A & (1 << RXC0)) {  // Verificar si hay datos disponibles
			char received_char = UART_Receive();
			process_command(received_char);
		}
		
		_delay_ms(150);
	}
}

void send_data_to_computer(uint16_t adc1, uint16_t adc2, int counter) {
	snprintf(buffer, sizeof(buffer), "ADC7: %d, ADC6: %d, Counter: %d\r\n", adc1, adc2, counter);
	UART_TransmitString(buffer);
}

void process_command(char command) {
	switch (command) {
		case '+':
		counter++;
		UART_TransmitString("Contador incrementado.\r\n");
		break;
		case '-':
		counter--;
		UART_TransmitString("Contador decrementado.\r\n");
		break;
		default:
		UART_TransmitString("Comando inválido.\r\n");
		break;
	}
}
