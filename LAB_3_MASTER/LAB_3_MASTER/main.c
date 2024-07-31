//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Universidad del Valle de Guatemala
// IE3054: ELECTR�NICA DIGITAL 2
// Autor: Alan Gomez
// Proyecto: LAB_3_MASTER.c
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
#include "LIB_me/UART_M/UART.h"
#include "LIB_me/SPI_M/SPI.h"
#include "LIB_me/POT_M/POT.h"
/////////////////////////////////////////////
//Variables
/////////////////////////////////////////////
uint8_t datoRecibido1 = 0x00;
uint8_t datoRecibido2 = 0x00;

int active = 0, menu2 = 0, i = 0;
int Change = 0, MAX = 0, MIN  = 0, active3 = 0, desactivedor = 0;
volatile char receivedChar = 0;    //Variable que almacena el valor del UART

int lista1[] = {0,5,5}; //Lista de numeros a mostrar
/////////////////////////////////////////////
//Sub_rutinas
/////////////////////////////////////////////
void setup(void);
void setup(void){
	cli();  //Apagar interrupciones
	DDRD = 0xFF;  //Puerto D como salida
	DDRC = 0x03;  //Puerto C como salida
	
	initUART9600();  //Iniciar UART
	SPI_init();
	

	PORTD = 0x00;
	sei(); //activer interrupciones
}

/////////////////////////////////////////////
//Programa Principal
/////////////////////////////////////////////
int main(void)
{
	setup();
	
	while (1)
	{
		_delay_ms(5);
		if (receivedChar == 'R') //si se desea usar python, bloquear el acceso a UART normal
		{
			active = 1;
		}
		
		if(active == 0 && menu2 == 0){
			writeTextUART("\n\r     **************MENU****************");   //Mostrar inicio
			writeUART(10);
			writeUART(13);
			writeUART(10);
			writeTextUART("          Potenciometro ADC0");   //Mostrar inicio
			writeUART(10);
			writeUART(13);
			writeTextUART("          Potenciometro ADC1\n\r");   //Mostrar inicio
			writeUART(10);
			writeUART(13);
			active = 1;   //Salir del menu
		}
		
		
		
		if (receivedChar !='c' && active3 == 1)
		{
			
			
			switch(receivedChar){
				case '0':
				lista1[i] = 0;
				break;
				case '1':
				lista1[i] = 1;
				break;
				case '2':
				lista1[i] = 2;
				break;
				case '3':
				lista1[i] = 3;
				break;
				case '4':
				lista1[i] = 4;
				break;
				case '5':
				lista1[i] = 5;
				break;
				case '6':
				lista1[i] = 6;
				break;
				case '7':
				lista1[i] = 7;
				break;
				case '8':
				lista1[i] = 8;
				break;
				case '9':
				lista1[i] = 9;
				break;
				
			}
			
			
			if (i >= 2)
			{
				int result = 0;

				for (int P = 0; P < 3; P++) {
					result = result * 10 + lista1[P];  // Construir el n?mero
				}
				
				PORTD = result << 2;  //Mostrar el valor del contador, con corrimiento hacia la derecha, de dos bits, muestra los primeros 6 bits
				PORTC = result >> 6;   //Mostrar el valor del contador, con corrimiento hacia la izquierda, muestra los ultimos 2 bits
				i = 0;
				active3 = 0;
			}
			

			i++;
			receivedChar = 'c';
			
		}
		
		
		if(receivedChar != 0 && active3 == 0){      //Si la variable que hay en USART es diferente de cero
			
			if (receivedChar == 'A') //Si se quiere enviar un valor directo al contador por python
			{
				active3 = 1;
				receivedChar = 'c';
				i = 0;
			}
			
			
			
			if ((receivedChar == '1' && menu2 == 0) || receivedChar == 'Q')   //Si se quiere ver los potenciometros, Q es para usar la interfaz de python
			{
				if (receivedChar == 'Q')
				{
					USANDOPYTHON(1);
				}
				else{
					USANDOPYTHON(0);
				}
				
				SPI_slaveON(2);
				SPI_tx(1);
				datoRecibido1 = SPI_rx();
				SPI_slaveOFF(2);
				
				
				SPI_slaveON(2);
				SPI_tx(2);
				datoRecibido2 = SPI_rx();
				SPI_slaveOFF(2);
				
				POT(datoRecibido1, datoRecibido2);
				
				receivedChar = 0;
			}
			
			
			if (receivedChar == '2' ){   //Si se elige modificar el valor del contador
				menu2 = 1;
				writeTextUART("Presione + para incrementar, - para decrementar, e para menu principal \n\r");
				writeUART(10);
				writeUART(13);
				writeUART(10);
				writeUART(13);
				
				receivedChar = 0;
			}
			
			if (receivedChar == '+' && menu2 == 1){
				Change ++;
				if (Change >= 255)    //si el contador es MAX de 255, dejarlo en 255
				{
					Change = 255;
				}
				CONTA(Change);
				
				
				PORTD = Change << 2;  //Mostrar el valor del contador, con corrimiento hacia la derecha, de dos bits, muestra los primeros 6 bits
				PORTC = Change >>6;   //Mostrar el valor del contador, con corrimiento hacia la izquierda, muestra los ultimos 2 bits
				receivedChar = 0;
				
			}
			
			if (receivedChar == '-' && menu2 == 1){
				Change --;
				
				if (Change <= 0)    //si el contador es MAX de 255, dejarlo en 255
				{
					Change = 0;
				}
				CONTA(Change);
				PORTD = Change << 2;  //Mostrar el valor del contador, con corrimiento hacia la derecha, de dos bits, muestra los primeros 6 bits
				PORTB = Change >>6;   //Mostrar el valor del contador, con corrimiento hacia la izquierda, muestra los ultimos 2 bits
				receivedChar = 0;
				
			}
			
			if (receivedChar == 'e')
			{
				receivedChar = 0;
				menu2 = 0;
				active = 0;
				writeUART(10);  //Enviar un enter
				writeUART(10);  //Enviar un enter
				writeUART(10);  //Enviar un enter
				writeUART(10);  //Enviar un enter
				writeUART(10);  //Enviar un enter
			}
		}
		
	}
}

/////////////////////////////////////////////
//Vector USART
/////////////////////////////////////////////
ISR(USART_RX_vect)
{
	receivedChar = UDR0; // Almacena el car?cter recibido
	
	while(!(UCSR0A & (1<<UDRE0)));    //Mientras haya caracteres
	
}
