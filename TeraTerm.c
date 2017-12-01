#include "MK64F12.h"
#include "NVIC.h"
#include "UART.h"
#include "DataTypeDefinitions.h"
#include "TeraTerm.h"
#include "FIFO.h"
#include "States.h"
#include "PIT.h"
#include "States.h"
#include "Morse.h"

TeraTermStatus printTTMainMenu(){

	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in green and background in black*/
	UART_putString(UART_0,"\033[0;32;10m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");

	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[4;10H");
	UART_putString(UART_0, "Ingrese mensaje a traducir. \r");

	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[6;10H");

	return GOOD;
}

TeraTermStatus TTstartTransmission(){
	/* VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[8;10H");
	UART_putString(UART_0, "Su mensaje está siendo procesado. \r");

	BooleanType error = FALSE;

	while(!isFIFOEmpty()){
		error = (startDecodeMorse());
		if(error){
			UART_putString(UART_0, "Error en mensaje ingresado. \r");
			return FALSE;
		}
	}

	return GOOD;
}
