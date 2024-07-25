#include "ADC.h"

#define F_CPU 16000000UL  // Define la frecuencia del reloj del microcontrolador
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

void ADC_Init() {
	// Configura el ADC con una referencia de voltaje de AVcc y un preescalador de 128
	ADMUX = (1<<REFS0);  // Referencia de voltaje en AVcc
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);  // Habilitar ADC y configurar preescalador a 128
}

uint16_t ADC_Read(uint8_t channel) {
	// Selecciona el canal de ADC
	ADMUX = (ADMUX & 0xF8) | (channel & 0x07);
	// Inicia la conversión
	ADCSRA |= (1<<ADSC);
	// Espera a que la conversión termine
	while(ADCSRA & (1<<ADSC));
	// Devuelve el resultado de la conversión
	return ADC;
}

void ADC_Read_Multiple(uint8_t channels[], uint16_t results[], uint8_t num_channels) {
	for (uint8_t i = 0; i < num_channels; i++) {
		results[i] = ADC_Read(channels[i]);
	}
}
