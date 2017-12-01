#include "MK64F12.h"
#include "NVIC.h"
#include "UART.h"
#include "DataTypeDefinitions.h"
#include "FIFO.h"
#include "States.h"

UART_MailBoxType UART0_MailBox = {0,0};
BooleanType enterFlag = FALSE;

void UART0_RX_TX_IRQHandler(void){
	while((UART0->S1 & UART_S1_RDRF_MASK)){
		//Check RIE (Receiver Full Interrupt) end transmission

		UART0_MailBox.mailBox = UART0->D; //set the MailBox value
		UART0_MailBox.flag = 1;//activates the MailBox flag

		if(ENTER ==UART0_MailBox.mailBox)//If the pressed key was ENTER
			enterFlag = TRUE;//This will be handled in the main, for controlling the menus
		else{
			enterFlag = FALSE;
			push(UART0_MailBox.mailBox);//store the new key pressed in the FIFO
		}
		return;
	}
}

void UART_init(UART_ChannelType uartChannel, uint32 systemClk, UART_BaudRateType baudRate){
	switch(uartChannel){
		case UART_0:{
				SIM->SCGC4 |= SIM_SCGC4_UART0_MASK; //Activate UART0 Clock gating
				UART0->C2 &= (~UART_C2_TE_MASK & ~UART_C2_RE_MASK); //Disable transmission and receptor of the UART
				
				uint16 SBR = (systemClk)/(16*baudRate);
				uint8 brfa = 32*((systemClk)/(16*baudRate)-SBR);

				//First we clean the UART high and low baudrate values, then we assign the wanted baudRate value
				UART0->BDH &= ~UART_BDH_SBR_MASK;
				UART0->BDL &= ~UART_BDL_SBR_MASK;
				UART0->BDH =   ((UART_BDH_SBR_MASK & SBR) >> 8);
				UART0->BDL = ((UART_BDL_SBR_MASK &  (uint8)SBR));

				//First we clean the BaudRate fine adjust value
				UART0->C4 &= ~UART_C4_BRFA_MASK;
				UART0->C4 = UART_C4_BRFA(brfa); //Copy brfa to UART0_C4[4:0]

				UART0->C2 |= (UART_C2_TE_MASK |UART_C2_RE_MASK); //Enable transmission and receptor of the UART
			break;
		}
		case UART_1:{
			SIM->SCGC4 |= SIM_SCGC4_UART1_MASK; //Activate UART0 Clock gating
			UART1->C2 &= (~UART_C2_TE_MASK & ~UART_C2_RE_MASK); //Disable transmission and receptor of the UART

			uint16 SBR = (systemClk)/(16*baudRate);
			uint8 brfa = 32*((systemClk)/(16*baudRate)-SBR);

			//First we clean the UART high and low baudrate values, then we assign the wanted baudRate value
			UART1->BDH &= ~UART_BDH_SBR_MASK;
			UART1->BDL &= ~UART_BDL_SBR_MASK;
			UART1->BDH =   ((UART_BDH_SBR_MASK & SBR) >> 8);
			UART1->BDL = (UART_BDL_SBR_MASK & ((uint8) SBR));

			//First we clean the BaudRate fine adjust value
			UART1->C4 &= ~UART_C4_BRFA_MASK;
			UART1->C4 = UART_C4_BRFA(brfa); //Copy brfa to UART0_C4[4:0]

			UART1->C2 |= (UART_C2_TE_MASK |UART_C2_RE_MASK); //Enable transmission and receptor of the UART
		break;
		}
		case UART_2:{
			SIM->SCGC4 |= SIM_SCGC4_UART2_MASK; //Activate UART0 Clock gating
			UART2->C2 &= (~UART_C2_TE_MASK & ~UART_C2_RE_MASK); //Disable transmission and receptor of the UART

			uint16 SBR = (systemClk/2)/(16*baudRate);
			uint8 brfa = 32*((systemClk/2)/(16*baudRate)-SBR);

			//First we clean the UART high and low baudrate values, then we assign the wanted baudRate value
			UART2->BDH &= ~UART_BDH_SBR_MASK;
			UART2->BDL &= ~UART_BDL_SBR_MASK;
			UART2->BDH =   ((UART_BDH_SBR_MASK & SBR) >> 8);
			UART2->BDL = (UART_BDL_SBR_MASK & ((uint8) SBR));

			//First we clean the BaudRate fine adjust value
			UART2->C4 &= ~UART_C4_BRFA_MASK;
			UART2->C4 = UART_C4_BRFA(brfa); //Copy brfa to UART0_C4[4:0]

			UART2->C2 |= (UART_C2_TE_MASK |UART_C2_RE_MASK); //Enable transmission and receptor of the UART
		break;
		}
		case UART_3:{
			SIM->SCGC4 |= SIM_SCGC4_UART3_MASK; //Activate UART0 Clock gating
			UART3->C2 &= (~UART_C2_TE_MASK & ~UART_C2_RE_MASK); //Disable transmission and receptor of the UART

			uint16 SBR = (systemClk/2)/(16*baudRate);
			uint8 brfa = 32*((systemClk/2)/(16*baudRate)-SBR);

			//First we clean the UART high and low baudrate values, then we assign the wanted baudRate value
			UART3->BDH &= ~UART_BDH_SBR_MASK;
			UART3->BDL &= ~UART_BDL_SBR_MASK;
			UART3->BDH =   ((UART_BDH_SBR_MASK & SBR) >> 8);
			UART3->BDL = (UART_BDL_SBR_MASK & ((uint8) SBR));

			//First we clean the BaudRate fine adjust value
			UART3->C4 &= ~UART_C4_BRFA_MASK;
			UART3->C4 = UART_C4_BRFA(brfa); //Copy brfa to UART0_C4[4:0]

			UART3->C2 |= (UART_C2_TE_MASK |UART_C2_RE_MASK); //Enable transmission and receptor of the UART
		break;
		}
		case UART_4:{
			SIM->SCGC1 |= SIM_SCGC1_UART4_MASK; //Activate UART0 Clock gating
			UART4->C2 &= (~UART_C2_TE_MASK & ~UART_C2_RE_MASK); //Disable transmission and receptor of the UART

			uint16 SBR = (systemClk/2)/(16*baudRate);
			uint8 brfa = 32*((systemClk/2)/(16*baudRate)-SBR);

			//First we clean the UART high and low baudrate values, then we assign the wanted baudRate value
			UART4->BDH &= ~UART_BDH_SBR_MASK;
			UART4->BDL &= ~UART_BDL_SBR_MASK;
			UART4->BDH =   ((UART_BDH_SBR_MASK & SBR) >> 8);
			UART4->BDL = (UART_BDL_SBR_MASK & ((uint8) SBR));

			//First we clean the BaudRate fine adjust value
			UART4->C4 &= ~UART_C4_BRFA_MASK;
			UART4->C4 = UART_C4_BRFA(brfa); //Copy brfa to UART0_C4[4:0]

			UART4->C2 |= (UART_C2_TE_MASK |UART_C2_RE_MASK); //Enable transmission and receptor of the UART
		break;
		}
		case UART_5:{
			SIM->SCGC1 |= SIM_SCGC1_UART5_MASK; //Activate UART0 Clock gating
			UART5->C2 &= (~UART_C2_TE_MASK & ~UART_C2_RE_MASK); //Disable transmission and receptor of the UART

			uint16 SBR = (systemClk/2)/(16*baudRate);
			uint8 brfa = 32*((systemClk/2)/(16*baudRate)-SBR);

			//First we clean the UART high and low baudrate values, then we assign the wanted baudRate value
			UART5->BDH &= ~UART_BDH_SBR_MASK;
			UART5->BDL &= ~UART_BDL_SBR_MASK;
			UART5->BDH =   ((UART_BDH_SBR_MASK & SBR) >> 8);
			UART5->BDL = (UART_BDL_SBR_MASK & ((uint8) SBR));

			//First we clean the BaudRate fine adjust value
			UART5->C4 &= ~UART_C4_BRFA_MASK;
			UART5->C4 = UART_C4_BRFA(brfa); //Copy brfa to UART0_C4[4:0]

			UART5->C2 |= (UART_C2_TE_MASK |UART_C2_RE_MASK); //Enable transmission and receptor of the UART
		break;
		}
		default: return;
	}

}

void UART0_interruptEnable(UART_ChannelType uartChannel){
	switch(uartChannel){
		case UART_0:{
			UART0->C2 |= (UART_C2_RIE_MASK);
			while ((UART0->S1 & UART_S1_RDRF_MASK));
			break;
		}
		case UART_1:{
			UART1->C2 |= (UART_C2_RIE_MASK);
			while ((UART0->S1 & UART_S1_RDRF_MASK));
			break;
		}
		case UART_2:{
			UART2->C2 |= (UART_C2_RIE_MASK);
			while ((UART0->S1 & UART_S1_RDRF_MASK));
			break;
		}
		case UART_3:{
			UART3->C2 |= (UART_C2_RIE_MASK);
			while ((UART0->S1 & UART_S1_RDRF_MASK));
			break;
		}
		case UART_4:{
			UART4->C2 |= (UART_C2_RIE_MASK);
			while ((UART0->S1 & UART_S1_RDRF_MASK));
			break;
		}
		case UART_5:{
			UART5->C2 |= (UART_C2_RIE_MASK);
			while ((UART0->S1 & UART_S1_RDRF_MASK));
			break;
		}
		default: return;
	}
	EnableInterrupts;
}

//checks if you already transmited before you transmit something else
void UART_putChar (UART_ChannelType uartChannel, uint8 character)
{
	switch(uartChannel)
	{
	case UART_0:
		while(!(UART0->S1 & UART_S1_TDRE_MASK)); //checks the Receive data register full flag bit on the UART Status register 1
				UART0->D = character; //writes the character on the Data register of the UART
		break;
	case UART_1:
		while(!(UART1->S1 & UART_S1_RDRF_MASK))
				UART1->D = character;
		break;
	case UART_2:
		while(!(UART2->S1 & UART_S1_RDRF_MASK))
				UART2->D = character;
		break;
	case UART_3:
		while(!(UART3->S1 & UART_S1_RDRF_MASK))
				UART3->D = character;
		break;
	case UART_4:
		while(!(UART4->S1 & UART_S1_RDRF_MASK))
				UART4->D = character;
		break;
	case UART_5:
		while(!(UART5->S1 & UART_S1_RDRF_MASK))
				UART5->D = character;
		break;
	default:
		return;
	}
}

//writes a string by writing character by character until the string ends
void UART_putString(UART_ChannelType uartChannel, sint8* string)
{
	switch(uartChannel)
	{
	case UART_0:
		while(*string)  //checks while the string hasn't finished
			UART_putChar(UART_0, *string++);    //calls putChar to write the whole string while it moves character by character
		break;
	case UART_1:
		while(*string)
			UART_putChar(UART_1, *string++);
		break;
	case UART_2:
		while(*string)
			UART_putChar(UART_2, *string++);
		break;
	case UART_3:
		while(*string)
			UART_putChar(UART_3, *string++);
		break;
	case UART_4:
		while(*string)
			UART_putChar(UART_4, *string++);
		break;
	case UART_5:
		while(*string)
			UART_putChar(UART_5, *string++);
		break;
	default:
		return;
	}
}

BooleanType getEnterFlag() { return enterFlag;}

BooleanType clearEnter() {
	enterFlag = FALSE;
	return TRUE;
}
