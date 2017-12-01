
#ifndef MORSE_H_
#define MORSE_H_

#include "DataTypeDefinitions.h"

#define MAX_SIMBOL_SIZE 6
#define WORDS_SIZE 36

typedef enum{
	DOT,
	LINE,
	END
}Simbol;

typedef struct{
	sint8 word;
	Simbol simbol[MAX_SIMBOL_SIZE];
}MorseWord;

BooleanType startDecodeMorse();

BooleanType showMorseWord(uint8 index);

BooleanType printDot();

BooleanType printLine();

#endif
