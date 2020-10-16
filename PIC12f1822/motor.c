#include <motor.h>
#define TIMER0_F

#include <functions.h>

void fim_curso(){
   unsigned int sec_t = sec, count = 0;

   while(count < 5){
      if(sec != sec_t){
         sec_t = sec;
         count++;
      }
      output_high(PIN_A5);
   }
   output_low(PIN_A5);
}

void main()
{
   int1 status_bloqueio = 0;

   //===========REGISTRADORES===================================
   disable_interrupts(GLOBAL);               // habilitar interr global
   enable_interrupts(INT_RDA);               //UART
   //enable_interrupts(INT_EXT_H2L);         // interrupcao CAN
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8); // setar timer1 para interno
   enable_interrupts(INT_TIMER1);            // habilita Timer1
   set_timer1(0);                            // limpar flag TMR1H & TMR1L
   counter = int_per_sec;
   enable_interrupts(GLOBAL);                // habilitar interr global
   //----------------------------------------------------------

   output_low(PIN_A5);
   output_low(PIN_A4);

   while(TRUE)
   {
      if(!status_bloqueio){
         if(input(PIN_A2) && !input(PIN_A3)){
            output_high(PIN_A4);
            fim_curso(); 
            status_bloqueio = 1;
         }
      }
      if(status_bloqueio){
         if(!input(PIN_A2) && input(PIN_A3)){
            output_low(PIN_A4);
            fim_curso(); 
            status_bloqueio = 0;
         }
      }

      if(um_segundo){
         um_segundo = 0;
         
         output_toggle(PIN_A0);
      }
   }
}
