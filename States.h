/**
	\file States.h
	\brief
		This is the header file for controlling the system status
	\author Daniel Barragán
	\date	05/11/2017
 */

#ifndef STATES_H_
#define STATES_H_

#include "DataTypeDefinitions.h"

#define STATE_MACHINE_SIZE 3 // size of the State Machine
#define READ_NUMBER_ERRO 100 // represents error reading number for date

/*! This data type represents all the limits and differentials to cast a ASCII to an HEX*/
typedef enum{
	NUMBER_LOW=48,
	NUMBER_HIGH=57,
	MINLETTER_LOW=97,
	MINLETTER_HIGH = 102,
	MINLETTER_DIF=87,
	UPLETTER_LOW=65,
	UPLETTER_HIGH=70,
	UPLETTER_DIF=55,
	ERROR_ADSRESS=1111
}ASCIIDecode;
/*! This data type represents the screen status*/
typedef enum{//each value is set in ASCII value
	PRINCIPAL= '0',
	PLAY,
	DIFFICULTY,
	RECORDS
}ProgramStatus;
/*! This data type is used to control the sub functions of the State Machine*/
typedef enum{
	CERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	TEN=10
}Index;
/*! This data type is used to control the serial port screen*/
typedef struct
{
	uint8(*fptrFirst)();
	uint8(*fptrSecond)();
	uint8(*fptrThird)();
}StateType;
/*! This data type is used to control the system status*/
typedef struct{
	ProgramStatus currentStatus;
	uint8	stateIndex;
}SystemControl;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It is used when the current state has finished, and we need to reset the serial port.
 	 \return TRUE if there were no troubles
 */
BooleanType noFunction();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function updates the serial port according to the current sub function index.
 	 \return TRUE if there were no troubles
 */
BooleanType controlSystem();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function handles the ENTER pressed, or when the sub function index
 	 its out of limits.
 	 \return TRUE if there were no troubles
 */
BooleanType controlMenu();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function returns the direction of the currentSystem variable.
 	 \return currentSystem direction
 */
SystemControl* getSystem();

#endif /*STATES_H_*/
