
#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <stdint.h>

void initUART9600();
void writeUART(char Caracter);
void writeTextUART(char * Texto);



#endif