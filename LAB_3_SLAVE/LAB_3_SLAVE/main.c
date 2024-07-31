//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Universidad del Valle de Guatemala
// IE3054: ELECTR�NICA DIGITAL 2
// Autor: Alan Gomez
// Proyecto: LAB_3_SLAVE.c
// Descripci�n: Laboratorio, comunicaci�n SPI_Mode_Master.
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
uint8_t value_1 = 0, value_2 = 0, cse_spi = 0;    //Variables de procesamiento

/////////////////////////////////////////////
//Funci�n de configuraci�n (setup)
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
//Funci�n principal (main)
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
//Interrupci�n del ADC (ISR(ADC_vect))
/////////////////////////////////////////////

ISR(ADC_vect){
	
	switch (cse_spi){
		case 0:
		ADMUX &= ~((1<<MUX2)|(1<<MUX1)|(1<<MUX0)); //Borrar configuracion ADC0
		value_1 = ADCH;
		cse_spi = 1;
		break;
		
		case 1:
		ADMUX &= ~((1<<MUX2)|(1<<MUX1)|(1<<MUX0));   //Borrar configuracion ADC1
		ADMUX |= (1<<MUX0);
		value_2 = ADCH;
		cse_spi = 0;
		break;
	}
	
	ADCSRA |= (1<<ADIF); //Se borra la bandera de interrupci�n

}


/////////////////////////////////////////////
//Interrupci�n SPI (ISR(SPI_STC_vect))
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