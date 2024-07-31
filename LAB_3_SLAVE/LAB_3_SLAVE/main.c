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

/////////////////////////////////////////////
//Librerias Primarias
/////////////////////////////////////////////
#define F_CPU 16000000
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

/////////////////////////////////////////////
//Librerias Secundarias
/////////////////////////////////////////////
#include "LIB_me/ADC/ADC.h"   //Incluir libreria de ADC
#include "LIB_me/SPI/SPI.h"   //Incluir libreria SPI

/////////////////////////////////////////////
// Variables
/////////////////////////////////////////////
uint8_t value_1 = 0, value_2 = 0, case_spi = 0;    //Variables de procesamiento

/////////////////////////////////////////////
//Función de configuración (setup)
/////////////////////////////////////////////
void setup(void);
void setup(void){
	cli();  //Apagar interrupciones
	DDRC =0;  //Puerto C como entrada
	
	SPI_init();
	SPCR |= (1<<SPIE); //Activar interrupcion SPI
	
	initADC(); //Iniciar ADC
	
	sei(); //Activar interrupciones
}

/////////////////////////////////////////////
//Función principal (main)
/////////////////////////////////////////////

int main(void)
{
	setup();
	
	while (1)
	{
		
		ADCSRA |=(1<<ADSC);  //Leer ADC
		_delay_ms(20);   //Retardo para evitar malos procesamientos del Atmega328P
		
		
	}
}

/////////////////////////////////////////////
//Interrupción del ADC (ISR(ADC_vect))
/////////////////////////////////////////////

ISR(ADC_vect){
	
	switch (case_spi){
		case 0:
		ADMUX &= ~((1<<MUX2)|(1<<MUX1)|(1<<MUX0)); //Borrar configuracion actual y poner ADC0
		value_1 = ADCH;
		case_spi = 1;
		break;
		
		case 1:
		ADMUX &= ~((1<<MUX2)|(1<<MUX1)|(1<<MUX0));   //Borrar configuracion actual y poner ADC1
		ADMUX |= (1<<MUX0);
		value_2 = ADCH;
		case_spi = 0;
		break;
	}
	
	ADCSRA |= (1<<ADIF); //Se borra la bandera de interrupción

}

/*ISR(ADC_vect){
	switch (case_spi){
		case 0:
		ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0)); // Borrar la configuración actual
		ADMUX |= (1<<MUX2) | (1<<MUX1); // Configurar para leer ADC6
		value_1 = ADCH;  // Leer valor de ADC6
		case_spi = 1;  // Cambiar al siguiente caso
		break;
		
		case 1:
		ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0)); // Borrar la configuración actual
		ADMUX |= (1<<MUX2) | (1<<MUX1) | (1<<MUX0); // Configurar para leer ADC7
		value_2 = ADCH;  // Leer valor de ADC7
		case_spi = 0;  // Cambiar al siguiente caso
		break;
	}
	
	ADCSRA |= (1<<ADIF); // Limpiar la bandera de interrupción del ADC
}*/


/////////////////////////////////////////////
//Interrupción SPI (ISR(SPI_STC_vect))
/////////////////////////////////////////////

ISR(SPI_STC_vect){
	uint8_t SPIVALOR = SPDR;

	
	if (SPIVALOR == 1)  //Si el maestro quiere ver el valor de los potenciometros
	{
		SPDR = value_2;
	}
	
	if (SPIVALOR == 2)  //Si el maestro quiere ver el valor de los potenciometros
	{
		SPDR = value_1;
	}

}