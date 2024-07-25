
#define F_CPU 16000000UL  // Define la frecuencia del reloj del microcontrolador
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "UART.h"

void UART_Init(unsigned long baud_rate) {
	unsigned int ubrr = F_CPU / 16 / baud_rate - 1;
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);  // Habilitar el receptor y el transmisor
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Configurar el formato de datos: 8 bits
}

void UART_Transmit(unsigned char data) {
	while (!(UCSR0A & (1 << UDRE0)));  // Esperar a que el buffer de transmisión esté vacío
	UDR0 = data;  // Enviar el dato
}

unsigned char UART_Receive(void) {
	while (!(UCSR0A & (1 << RXC0)));  // Esperar a que los datos estén disponibles
	return UDR0;  // Leer el dato recibido
}

void UART_TransmitString(const char *str) {
	while (*str) {
		UART_Transmit(*str++);
	}
}
