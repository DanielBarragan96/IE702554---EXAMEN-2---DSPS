
#include "MK64F12.h"
#include "NVIC.h"
#include "UART.h"
#include "DataTypeDefinitions.h"
#include "FIFO.h"
#include "States.h"
#include "TeraTerm.h"
#include "GPIO.h"
#include "Morse.h"
#include "PIT.h"

MorseWord morse[WORDS_SIZE] = {
		{'A',{DOT,LINE,END}},
		{'B',{DOT,LINE,END}},
		{'C',{DOT,LINE,END}},
		{'D',{DOT,LINE,END}},
		{'E',{DOT,LINE,END}},
		{'F',{DOT,LINE,END}},
		{'G',{DOT,LINE,END}},
		{'H',{DOT,LINE,END}},
		{'I',{DOT,LINE,END}},
		{'J',{DOT,LINE,END}},
		{'K',{DOT,LINE,END}},
		{'L',{DOT,LINE,END}},
		{'M',{DOT,LINE,END}},
		{'N',{DOT,LINE,END}},
		{'O',{DOT,LINE,END}},
		{'P',{DOT,LINE,END}},
		{'Q',{DOT,LINE,END}},
		{'R',{DOT,LINE,END}},
		{'S',{DOT,LINE,END}},
		{'T',{DOT,LINE,END}},
		{'U',{DOT,LINE,END}},
		{'V',{DOT,LINE,END}},
		{'W',{DOT,LINE,END}},
		{'X',{DOT,LINE,END}},
		{'Y',{DOT,LINE,END}},
		{'Z',{DOT,LINE,END}},
		{'1',{DOT,LINE,END}},
		{'2',{DOT,LINE,END}},
		{'3',{DOT,LINE,END}},
		{'4',{DOT,LINE,END}},
		{'5',{DOT,LINE,END}},
		{'6',{DOT,LINE,END}},
		{'7',{DOT,LINE,END}},
		{'8',{DOT,LINE,END}},
		{'9',{DOT,LINE,END}},
		{'0',{DOT,LINE,END}}
};

BooleanType startDecodeMorse(){
	if(!isFIFOEmpty()){
		uint8 index = 0;
		sint8 word = pop();//read first value in the FIFO
		while(WORDS_SIZE > index){
			if(morse[index].word == word){
				showMorseWord(index);
				return FALSE;
			}

		}
	}
	return TRUE;//the char readed is not stored in the Morse table
}

BooleanType showMorseWord(uint8 index){
	MorseWord printMorse = morse[index];
	uint8 morseIndex = 0;
	while(END != printMorse.simbol[morseIndex]){
		if(DOT == printMorse.simbol[morseIndex])
			printDot();
		else if(LINE == printMorse.simbol[morseIndex])
			printLine();
		morseIndex++;
	}
	return TRUE;
}

BooleanType printDot(){
	PIT_clear(PIT_0);
	blueLEDOn();
	PIT_delay(PIT_0, SYSTEM_CLOCK, 1.0F);
	while(!PIT_getIntrStutus(PIT_0));
	turnLEDsOff();
	morseDelay();
	return TRUE;
}

BooleanType printLine(){
	PIT_clear(PIT_0);
	blueLEDOn();
	PIT_delay(PIT_0, SYSTEM_CLOCK, 2.0F);
	while(!PIT_getIntrStutus(PIT_0));
	turnLEDsOff();
	morseDelay();
	return TRUE;
}

BooleanType morseDelay(){
	PIT_clear(PIT_0);
	PIT_delay(PIT_0, SYSTEM_CLOCK, 1.0F);
	while(!PIT_getIntrStutus(PIT_0));
	return TRUE;
}
