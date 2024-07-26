#define F_CPU 16000000UL
#include "SPI.h"

void SPI_init(SPI_TYPE sType, SPI_Data_Order sDataOrder, SPI_Clock_Polarity sClockPolarity, SPI_Clock_Phase sClockPhase) {
	//PB2 -> SS
	//PB3 -> SS
	//PB4 -> SS
	//PB5 -> SS
	
	if (sType & (1<<MSTR)) { //Verificar si se configura como maestro..
		// Configurar como maestro
		DDRB |= (1 << DDB3) | (1 << DDB5) | (1 << DDB2); // MOSI, SCK, SS como salidas
		DDRB &= ~(1 << DDB4); // MISO como entrada
		SPCR |= (1 << MSTR); // Habilitar modo maestro
		
		uint8_t temp = sType & 0b00000111;
		switch(temp){
			case 0: //DIV2
				SPCR &= ~((1<<SPR1)|(1<<SPR0));
				SPSR |= (1<<SPI2X);
			break;
			case 1: //DIV4
				SPCR &= ~((1<<SPR1)|(1<<SPR0));
				SPSR &= ~(1<<SPI2X);
			break;
			case 2: //DIV8
				SPCR |= (1<<SPR0);
				SPCR &= ~(1<<SPR1);
				SPSR |= (1<<SPI2X);
			break;
			case 3: //DIV16
				SPCR |= (1<<SPR0);
				SPCR &= ~(1<<SPR1);
				SPSR &= ~(1<<SPI2X);
			break;
			case 4: //DIV32
				SPCR &= ~(1<<SPR0);
				SPCR |= (1<<SPR1);
				SPSR |= (1<<SPI2X);
			break;
			case 5: //DIV64
				SPCR &= ~(1<<SPR0);
				SPCR |= (1<<SPR1);
				SPSR &= ~(1<<SPI2X);
			break;
			case 6: //DIV128
				SPCR |= (1<<SPR0)|(1<<SPR1);
				SPSR &= ~(1<<SPI2X);
			break;
		}
		
		} else {
		// Configurar como esclavo
		DDRB |= (1 << DDB4); // MISO como salida
		DDRB &= ~((1 << DDB3) | (1 << DDB5) | (1 << DDB2)); // MOSI, SCK, SS como entradas
		
		SPCR &= ~(1 << MSTR); // Habilitar SPI, modo esclavo
	}
	// Habilitar Data Order, Clock Polarity, Clock Phase
	SPCR |= (1<<SPE)|sDataOrder|sClockPolarity|sClockPhase;
}

void SPI_Write(uint8_t data) {
	SPDR = data;
}

uint8_t SPI_Read(void) {
	while(!(SPSR & (1<<SPIF)));
	return(SPDR);
}

unsigned SpiDataReady(){
	if(SPSR & (1<<SPIF))
	return 1;
	else
	return 0;
}

static void spiReceivewait(){
	while (!(SPSR & (1<<SPIF)));
}

