
#include "MK64F12.h"
#include "NVIC.h"
#include "UART.h"
#include "DataTypeDefinitions.h"
#include "FIFO.h"
#include "States.h"
#include "TeraTerm.h"
#include "GPIO.h"

static BooleanType startTransmition = FALSE;

//This structure is used for controlling the menus shown in the serial port
//Each menu has up to 3 sub stages which are changed whenever controlSystem is used
const StateType FSM_Moore[] =
	{
			{&printTTMainMenu,&TTstartTransmission,&noFunction},
			{&noFunction,&noFunction,&noFunction},
			{&noFunction,&noFunction,&noFunction},
			{&noFunction,&noFunction,&noFunction}
	};
//This structure handles the current system status
SystemControl currentSystem = {PRINCIPAL,0};

BooleanType noFunction(){
	//as we put an index in the limit, control Menu will restart the serial port
	currentSystem.stateIndex = STATE_MACHINE_SIZE;
	controlMenu();
	return FALSE;
}

BooleanType controlSystem(){//control system alternates the sub functions inside an state of the FSM_Moore
	uint8 index = (currentSystem.currentStatus - 48);//because currentStatus is in ASCII value, we have to decrease 48
	//according to the index value we control the sub functions of the current FSM_Moore state
	if(CERO == currentSystem.stateIndex) FSM_Moore[index].fptrFirst();
	else if(ONE== currentSystem.stateIndex) FSM_Moore[index].fptrSecond();
	else if(TWO == currentSystem.stateIndex) FSM_Moore[index].fptrThird();

	return TRUE;
}

BooleanType controlMenu(){
	if(STATE_MACHINE_SIZE <= currentSystem.stateIndex){//if we overpassed the state machine size
			currentSystem.stateIndex = 0;//restore the initial configuration of the screen
			currentSystem.currentStatus = PRINCIPAL;
			startTransmition = FALSE;
	}
	else
		currentSystem.stateIndex++;//update the sub function index for the next lap

	controlSystem();//update the serial port screen
	clearEnter();//clear enter flag, which is enabled in the UART interruption
	clearFIFO();//reset the stored FIFO
	return TRUE;
}

SystemControl* getSystem(){ return &currentSystem; }//return currentSstem direction

BooleanType getStartTransmition(){ return startTransmition;	}

BooleanType setStartTransmition(BooleanType start){
	startTransmition = start;
	return TRUE;
}

BooleanType delayLEDs(uint16 delay)
{
	volatile uint16 counter;

	for(counter=delay; counter > 0; counter--)
	{
	}
	return TRUE;
}

BooleanType turnLEDsOff(){
			GPIOB->PDOR |= 0x00200000;/**Blue led off*/
			return TRUE;
}

BooleanType blueLEDOn(){
		turnLEDsOff();
	GPIOB->PDOR &= ~(0x00200000);/**Blue led on*/
	return TRUE;
}
