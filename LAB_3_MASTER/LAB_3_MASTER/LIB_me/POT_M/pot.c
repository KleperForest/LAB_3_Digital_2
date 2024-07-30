#include "POT.h"


int millares = 0;
int centenas = 0;
int decenas = 0;
int unidades = 0;
int python = 0, cambios = 0, enclava = 0; 


char lista[10] = {'0','1','2','3','4','5','6','7','8','9'}; //Lista de numeros a mostrar
	
	
void USANDOPYTHON(uint8_t activar){    //Si se requiere ver los potenciómeros usando la interfaz gráfica de python
	if (activar == 1)
	{
		python = 1;    //Activar que se pueda ver en la interfaz gráfica
		
	}  
	
	else{
		python = 0;   //Desactivar que se pueda ver en la interfaz gráfica
	}
	
	}

void POT(uint8_t VA1, uint8_t VA2){
	
	if (python == 1 && enclava == 0)
	{
		cambios = 2;
		enclava = 1;
	}
	
	if (python == 1 && cambios == 2)
	{
		cambios = 1;
	}
	
	else if (python == 1 && cambios == 1)
	{
		cambios = 2;
	}
	
	
	millares = VA2/1000;
	centenas = (VA2-(millares*1000))/100;
	decenas = (VA2- (millares*1000 + centenas*100))/10;
	unidades = VA2-(millares*1000 + centenas*100 + decenas*10);
	writeUART(10);  //Enviar un enter
	if (python == 0)
	{
		writeUART(10);  //Enviar un enter
		writeUART(10);  //Enviar un enter
		writeUART(10);  //Enviar un enter
		writeUART(10);  //Enviar un enter
		writeTextUART("Valor potenciometro 1: ");
		cambios = 1;
		enclava = 0;
		
	}
	
	if (cambios == 1)
	{
		
	
	
	switch(centenas){   //Mostrar centenas
		case 0:
		writeUART(lista[0]);
		break;
		
		
		case 1:
		writeUART(lista[1]);
		break;
		
		case 2:
		writeUART(lista[2]);
		break;
		
		
		case 3:
		writeUART(lista[3]);
		break;
		
		case 4:
		writeUART(lista[4]);
		break;
		
		
		case 5:
		writeUART(lista[5]);
		break;
		
		
		case 6:
		writeUART(lista[6]);
		break;
		
		
		case 7:
		writeUART(lista[7]);
		break;
		
		case 8:
		writeUART(lista[8]);
		break;
		
		
		case 9:
		writeUART(lista[9]);
		break;
		
	}
	
	
	switch(decenas){   //Mostrar decenas
		case 0:
		writeUART(lista[0]);
		break;
		
		
		case 1:
		writeUART(lista[1]);
		break;
		
		case 2:
		writeUART(lista[2]);
		break;
		
		
		case 3:
		writeUART(lista[3]);
		break;
		
		case 4:
		writeUART(lista[4]);
		break;
		
		
		case 5:
		writeUART(lista[5]);
		break;
		
		
		case 6:
		writeUART(lista[6]);
		break;
		
		
		case 7:
		writeUART(lista[7]);
		break;
		
		case 8:
		writeUART(lista[8]);
		break;
		
		
		case 9:
		writeUART(lista[9]);
		break;
		
	}
	
	switch(unidades){   //Mostrar unidades
		case 0:
		writeUART(lista[0]);
		break;
		
		
		case 1:
		writeUART(lista[1]);
		break;
		
		case 2:
		writeUART(lista[2]);
		break;
		
		
		case 3:
		writeUART(lista[3]);
		break;
		
		case 4:
		writeUART(lista[4]);
		break;
		
		
		case 5:
		writeUART(lista[5]);
		break;
		
		
		case 6:
		writeUART(lista[6]);
		break;
		
		
		case 7:
		writeUART(lista[7]);
		break;
		
		case 8:
		writeUART(lista[8]);
		break;
		
		
		case 9:
		writeUART(lista[9]);
		break;
		
	}
	}
	
	
	//Obtener el dato del potenciometro descompuesto
	millares = VA1/1000;
	centenas = (VA1-(millares*1000))/100;
	decenas = (VA1- (millares*1000 + centenas*100))/10;
	unidades = VA1-(millares*1000 + centenas*100 + decenas*10);
	
	if (python == 0)
	{
		writeUART(10);  //Enviar un enter
		writeTextUART("Valor potenciometro 2: ");
	}
	
	if (cambios == 2 || python == 0)
	{
		
	
	
	switch(centenas){   //Mostrar centenas
		case 0:
		writeUART(lista[0]);
		break;
		
		
		case 1:
		writeUART(lista[1]);
		break;
		
		case 2:
		writeUART(lista[2]);
		break;
		
		
		case 3:
		writeUART(lista[3]);
		break;
		
		case 4:
		writeUART(lista[4]);
		break;
		
		
		case 5:
		writeUART(lista[5]);
		break;
		
		
		case 6:
		writeUART(lista[6]);
		break;
		
		
		case 7:
		writeUART(lista[7]);
		break;
		
		case 8:
		writeUART(lista[8]);
		break;
		
		
		case 9:
		writeUART(lista[9]);
		break;
		
	}
	
	
	switch(decenas){   //Mostrar decenas
		case 0:
		writeUART(lista[0]);
		break;
		
		
		case 1:
		writeUART(lista[1]);
		break;
		
		case 2:
		writeUART(lista[2]);
		break;
		
		
		case 3:
		writeUART(lista[3]);
		break;
		
		case 4:
		writeUART(lista[4]);
		break;
		
		
		case 5:
		writeUART(lista[5]);
		break;
		
		
		case 6:
		writeUART(lista[6]);
		break;
		
		
		case 7:
		writeUART(lista[7]);
		break;
		
		case 8:
		writeUART(lista[8]);
		break;
		
		
		case 9:
		writeUART(lista[9]);
		break;
		
	}
	
	switch(unidades){   //Mostrar unidades
		case 0:
		writeUART(lista[0]);
		break;
		
		
		case 1:
		writeUART(lista[1]);
		break;
		
		case 2:
		writeUART(lista[2]);
		break;
		
		
		case 3:
		writeUART(lista[3]);
		break;
		
		case 4:
		writeUART(lista[4]);
		break;
		
		
		case 5:
		writeUART(lista[5]);
		break;
		
		
		case 6:
		writeUART(lista[6]);
		break;
		
		
		case 7:
		writeUART(lista[7]);
		break;
		
		case 8:
		writeUART(lista[8]);
		break;
		
		
		case 9:
		writeUART(lista[9]);
		break;
		
	}
	
	
}
}

void CONTA(uint8_t cambi){
	
	 millares = cambi/1000;
	 centenas = (cambi-(millares*1000))/100;
	 decenas = (cambi- (millares*1000 + centenas*100))/10;
	unidades = cambi-(millares*1000 + centenas*100 + decenas*10);
	
	writeUART(10);  //Enviar un enter
	writeTextUART("Valor Del contador: ");
	switch(centenas){   //Mostrar centenas
		case 0:
		writeUART(lista[0]);
		break;
		
		
		case 1:
		writeUART(lista[1]);
		break;
		
		case 2:
		writeUART(lista[2]);
		break;
		
		
		case 3:
		writeUART(lista[3]);
		break;
		
		case 4:
		writeUART(lista[4]);
		break;
		
		
		case 5:
		writeUART(lista[5]);
		break;
		
		
		case 6:
		writeUART(lista[6]);
		break;
		
		
		case 7:
		writeUART(lista[7]);
		break;
		
		case 8:
		writeUART(lista[8]);
		break;
		
		
		case 9:
		writeUART(lista[9]);
		break;
		
	}
	
	
	switch(decenas){   //Mostrar decenas
		case 0:
		writeUART(lista[0]);
		break;
		
		
		case 1:
		writeUART(lista[1]);
		break;
		
		case 2:
		writeUART(lista[2]);
		break;
		
		
		case 3:
		writeUART(lista[3]);
		break;
		
		case 4:
		writeUART(lista[4]);
		break;
		
		
		case 5:
		writeUART(lista[5]);
		break;
		
		
		case 6:
		writeUART(lista[6]);
		break;
		
		
		case 7:
		writeUART(lista[7]);
		break;
		
		case 8:
		writeUART(lista[8]);
		break;
		
		
		case 9:
		writeUART(lista[9]);
		break;
		
	}
	
	switch(unidades){   //Mostrar unidades
		case 0:
		writeUART(lista[0]);
		break;
		
		
		case 1:
		writeUART(lista[1]);
		break;
		
		case 2:
		writeUART(lista[2]);
		break;
		
		
		case 3:
		writeUART(lista[3]);
		break;
		
		case 4:
		writeUART(lista[4]);
		break;
		
		
		case 5:
		writeUART(lista[5]);
		break;
		
		
		case 6:
		writeUART(lista[6]);
		break;
		
		
		case 7:
		writeUART(lista[7]);
		break;
		
		case 8:
		writeUART(lista[8]);
		break;
		
		
		case 9:
		writeUART(lista[9]);
		break;
		
	}
}

