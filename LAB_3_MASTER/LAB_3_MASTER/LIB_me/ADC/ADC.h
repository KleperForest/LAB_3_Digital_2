#ifndef ADC_H_
#define ADC_H_

#define F_CPU 16000000UL  // Define la frecuencia del reloj del microcontrolador
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>


////////////////////////////////////////////////////
// Prototipos de funciones para el ADC
////////////////////////////////////////////////////
void ADC_Init();
uint16_t ADC_Read(uint8_t channel);
void ADC_Read_Multiple(uint8_t channels[], uint16_t results[], uint8_t num_channels);

#endif /* ADC_H_ */
