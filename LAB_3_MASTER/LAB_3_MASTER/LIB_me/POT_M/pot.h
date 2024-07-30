
#include <avr/io.h>
#include <stdint.h>
#define F_CPU 16000000
#include <util/delay.h>

#ifndef POT_H_
#define POT_H_

void POT(uint8_t VA1, uint8_t VA2);
void CONTA(uint8_t cambi);
void USANDOPYTHON(uint8_t activar);

#endif