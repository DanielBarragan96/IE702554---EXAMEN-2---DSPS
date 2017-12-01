
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
		{'B',{LINE,DOT,DOT,DOT}},
		{'C',{LINE,DOT,LINE,DOT,END}},
		{'D',{LINE,DOT,DOT,END}},
		{'E',{DOT,END}},
		{'F',{DOT,DOT,LINE,DOT,END}},
		{'G',{LINE,LINE,DOT,END}},
		{'H',{DOT,DOT,DOT,DOT,END}},
		{'I',{DOT,DOT,END}},
		{'J',{DOT,LINE,LINE,LINE,END}},
		{'K',{DOT,LINE,DOT,END}},
		{'L',{DOT,LINE,DOT,DOT,END}},
		{'M',{LINE,LINE,END}},
		{'N',{LINE,DOT,END}},
		{'O',{LINE,LINE,LINE,END}},
		{'P',{DOT,LINE,LINE,DOT,END}},
		{'Q',{LINE,LINE,DOT,LINE,END}},
		{'R',{DOT,LINE,DOT,END}},
		{'S',{DOT,DOT,DOT,END}},
		{'T',{LINE,END}},
		{'U',{DOT,DOT,LINE,END}},
		{'V',{DOT,DOT,DOT,LINE,END}},
		{'W',{DOT,LINE,LINE,END}},
		{'X',{LINE,DOT,DOT,LINE,END}},
		{'Y',{LINE,DOT,LINE,LINE,END}},
		{'Z',{LINE,LINE,DOT,DOT,END}},
		{'1',{DOT,LINE,LINE,LINE,LINE,END}},
		{'2',{DOT,DOT,LINE,LINE,LINE,END}},
		{'3',{DOT,DOT,DOT,LINE,LINE,END}},
		{'4',{DOT,DOT,DOT,DOT,LINE,END}},
		{'5',{DOT,DOT,DOT,DOT,DOT,END}},
		{'6',{LINE,DOT,DOT,DOT,DOT,END}},
		{'7',{LINE,LINE,DOT,DOT,DOT,END}},
		{'8',{LINE,LINE,LINE,DOT,DOT,END}},
		{'9',{LINE,LINE,LINE,LINE,DOT,END}},
		{'0',{LINE,LINE,LINE,LINE,LINE,END}}
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
