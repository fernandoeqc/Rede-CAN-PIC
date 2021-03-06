#include <18F4520.h>

#device ADC=16


#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)

#use delay(crystal=8MHz)

//#DEFINE TECLADO_ON
//#DEFINE LED1 PIN_B7
//#DEFINE LED2 PIN_B6
//#define SPI1_ON
#define LED_B
//#DEFINE USE_HARDWARE_SPI
//#define BUT1 PIN_B0
//#BYTE LATD 0x0F
//#BIT SSPEN = 0b1

