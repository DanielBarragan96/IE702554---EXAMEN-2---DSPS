/**
	\file
	\brief
		This is the header file for the UART device driver.
		It contains the macros and function definition.
	\author Daniel Barragán
	\date	2/11/2017
	\todo
		To implement all needed functions
 */
#ifndef TERATERM_H_
#define TERATERM_H_

#include "DataTypeDefinitions.h"

/*! This data type is used to indicate when TeraTerm worked properly*/
typedef enum{
	ERROR,
	GOOD
}TeraTermStatus;


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It sends the MainMenu through the serial port.
 	 \return GOOD if there were no troubles
 */
TeraTermStatus printTTMainMenu();


#endif /* TERATERM_H_ */
