#include <12F1822.h>

#pragma device ADC=16

#pragma FUSES NOWDT                 	//No Watch Dog Timer

#pragma FUSES NOMCLR                	//Master Clear pin used for I/O

#pragma FUSES NOBROWNOUT            	//No brownout reset

#pragma FUSES NOLVP                 	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#pragma use delay(internal=4000000)

#pragma use rs232(baud=9600,parity=N,xmit=PIN_A0,rcv=PIN_A1,bits=8,stream=PORT1)

#define LED PIN_A4
#define DELAY 1000


