#include <16F1823.h>
#device ADC=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(internal=4000000)

#define LED1  PIN_C5
#define LED2  PIN_A4
#define AVISO PIN_A1

#define BLOQ  PIN_A0
