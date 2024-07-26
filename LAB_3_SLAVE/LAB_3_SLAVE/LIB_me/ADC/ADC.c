#include "ADC.h"

#define MAX_ADC_CHANNELS 8

volatile uint16_t adc_results[MAX_ADC_CHANNELS];  // Array para almacenar los resultados de la conversión ADC
volatile uint8_t current_channel = 0;
volatile uint8_t total_channels = 0;
volatile uint8_t *channels_to_read;

void ADC_Init() {
	// Configura el ADC con una referencia de voltaje de AVcc y un preescalador de 128
	ADMUX = (1<<REFS0);  // Referencia de voltaje en AVcc
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) | (1<<ADIE);  // Habilitar ADC, interrupción y configurar preescalador a 128
	sei();  // Habilitar interrupciones globales
}

void ADC_Start_Conversion(uint8_t channel) {
	// Selecciona el canal de ADC
	ADMUX = (ADMUX & 0xF8) | (channel & 0x07);
	// Inicia la conversión
	ADCSRA |= (1<<ADSC);
}

uint16_t ADC_Get_Result(uint8_t channel) {
	return adc_results[channel];
}

void ADC_Read_Multiple(uint8_t channels[], uint16_t results[], uint8_t num_channels) {
	channels_to_read = channels;
	total_channels = num_channels;
	current_channel = 0;
	ADC_Start_Conversion(channels_to_read[current_channel]);
	// Esperar hasta que se lean todos los canales
	while (current_channel < total_channels);
	// Copiar los resultados a la matriz de resultados proporcionada
	for (uint8_t i = 0; i < num_channels; i++) {
		results[i] = ADC_Get_Result(channels[i]);
	}
}

// Definir la ISR del ADC en la implementación de la librería
ISR(ADC_vect) {
	// Guardar el resultado de la conversión en el array correspondiente
	adc_results[channels_to_read[current_channel]] = ADC;
	// Incrementar el índice del canal actual
	current_channel++;
	// Iniciar la conversión del siguiente canal si hay más canales
	if (current_channel < total_channels) {
		ADC_Start_Conversion(channels_to_read[current_channel]);
	}
}
