/**
	\file
	\brief
		This project controls the UART and I2C protocols.
	\author Daniel Barragán and Alejandro Ávila
	\date	07/11/2017
 */

#include "MK64F12.h"
#include "UART.h"
#include "NVIC.h"
#include "GPIO.h"
#include "init.h"
#include "FIFO.h"
#include "UART.h"
#include "States.h"
#include "MCG.h"
#include "PIT.h"
#include "TeraTerm.h"

int main(void)
{
	initMain();//initialize all configurations for using this practice

	for(;;) {

		if(getEnterFlag())	controlMenu();//When ENTER was pressed handle the input



	}
	return 0;
}
