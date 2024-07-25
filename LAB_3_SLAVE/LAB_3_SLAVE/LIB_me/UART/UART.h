#ifndef UART_H_
#define UART_H_

#define F_CPU 16000000UL  // Define la frecuencia del reloj del microcontrolador
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>

////////////////////////////////////////////////////
// Prototipos de funciones para la UART
////////////////////////////////////////////////////
void UART_Init(unsigned long baud_rate);
void UART_Transmit(unsigned char data);
unsigned char UART_Receive(void);
void UART_TransmitString(const char *str);

#endif /* UART_H_ */
