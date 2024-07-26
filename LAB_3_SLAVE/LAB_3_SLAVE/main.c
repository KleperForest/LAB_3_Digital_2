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
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>
#include "LIB_me/ADC/ADC.h"
#include "LIB_me/SPI/SPI.h"
#include "LIB_me/UART/UART.h"

uint8_t valorSPI = 0;
volatile uint16_t adc_values[2];  // Valores de los ADCs

void refreshPORT(uint8_t valor);
void send_ADC_values_UART(void);

int main(void)
{
	// Configurar Pines como salida
	DDRD |= (1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7);
	DDRB |= (1<<DDB0)|(1<<DDB1);
	
	PORTD &= ~((1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7));
	PORTB &= ~((1<<DDB0)|(1<<DDB1));
	
	SPI_init(SPI_SLAVE_SS, SPI_Data_Order_MSB, SPI_Clock_IDLE_LOW, SPI_clock_First_EDGE);
	UART_Init(9600);  // Inicializar UART con una tasa de baudios de 9600
	ADC_Init();
	SPCR |= (1<<SPIE); // Activar ISR SPI
	sei();
	
	// Iniciar la primera conversión en los canales 6 y 7
	uint8_t channels[] = {6, 7};
	ADC_Read_Multiple(channels, adc_values, 2);
	
	while (1)
	{
		// El resultado de la conversión ADC se actualizará en la ISR del ADC
	}
}

ISR(SPI_STC_vect) {
	valorSPI = SPDR;
	if (valorSPI == 'c') {
		SPI_send(adc_values[1]);  // Enviar el valor del canal 7 (índice 1 en el array)
		send_ADC_values_UART();   // Enviar valores de ADC 6 y 7 por UART
	}
}

ISR(ADC_vect) {
	static uint8_t current_channel = 0;
	adc_values[current_channel] = ADC;
	current_channel++;
	
	if (current_channel < 2) {
		ADC_Start_Conversion(current_channel == 0 ? 6 : 7);  // Iniciar la conversión del próximo canal
		} else {
		current_channel = 0;  // Reiniciar el índice del canal
		ADC_Start_Conversion(6);  // Reiniciar la conversión en el primer canal
	}
}

void send_ADC_values_UART(void) {
	char buffer[20];
	sprintf(buffer, "ADC6: %d\r\n", adc_values[0]);
	UART_TransmitString(buffer);
	sprintf(buffer, "ADC7: %d\r\n", adc_values[1]);
	UART_TransmitString(buffer);
}
