#ifndef SPI_H
#define SPI_H
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdint.h>

// Definiciones de entradas
typedef enum{
	SPI_MASTER_OSC_DV2		= 0b01010000,
	SPI_MASTER_OSC_DV4		= 0b01010001,
	SPI_MASTER_OSC_DV8		= 0b01010010,
	SPI_MASTER_OSC_DV16		= 0b01010011,
	SPI_MASTER_OSC_DV32		= 0b01010100,
	SPI_MASTER_OSC_DV64		= 0b01010101,
	SPI_MASTER_OSC_DV128	= 0b01010110,
	SPI_SLAVE_SS			= 0b01000000
}SPI_TYPE;

typedef enum{
	SPI_Data_Order_MSB = 0b00000000,
	SPI_Data_Order_LSB = 0b00100000
	}SPI_Data_Order;
	
typedef enum{
	SPI_Clock_IDLE_HIGH		= 0b00001000, 
	SPI_Clock_IDLE_LOW		= 0b00000000
	}SPI_Clock_Polarity;
	
typedef enum{
	SPI_clock_First_EDGE	= 0b00000000,
	SPI_clock_Last_EDGE		= 0b00000100
}SPI_Clock_Phase;

// Funciones para inicializar el SPI
void SPI_init(SPI_TYPE, SPI_Data_Order, SPI_Clock_Polarity, SPI_Clock_Phase);
void SPI_send(uint8_t data);
uint8_t SPI_receive(void);

#endif // SPI_H
