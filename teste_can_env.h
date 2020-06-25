#include <16F1823.h>
#device ADC=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(internal=4000000)

#define LED1  pin_c5
#define LED2  pin_a4
#define AVISO pin_a1

#define BLOQ  pin_a0

// PORTA
#define   IRQ         PIN_A2
#define   CE          PIN_A1
#define   MCLR        PIN_A3
// PORTC
#define   SCK         PIN_C0
#define   SDI         PIN_C1
#define   SDO         PIN_C2
#define   CS          PIN_C3
                      
//TRISA
#define   CE_TRIS     TRISA,1 //O
#define   IRQ_TRIS    TRISA,2 //I

//TRISC
#define   SCK_TRIS    TRISC,0 //O
#define   SDI_TRIS    TRISC,1 //I
#define   SDO_TRIS    TRISC,2 //O
#define   CS_TRIS     TRISC,3 //O

//*****************
//*   VARIABLES   *
//*****************
#BYTE TRISA     =  0x0C //00000110
//#BYTE TRISB     =  0x86
#BYTE TRISC     =  0x02 //00000010
#BYTE INTCON    =  0x00


