#include <teste1823.h>

#define int_per_sec 10

unsigned int8 counter = 0,
              sec = 0,
              min = 0;

int1 um_segundo = 0b0,
     um_minuto = 0b0;

/*
  T * Fosc
-------------- = valor do timer
4 * prescaler


0,1 * 4000000
--------------
   4 * 8
*/


#INT_TIMER1
void timer1_isr(){  // interrupt routine    
   set_timer1(53036);
   counter--;  // decrements counter which is set to it_per_sec 
   
   output_toggle(LED1);
   
   //SEGUNDOS
   if(counter==0){         
      
      
      sec++;
      counter=int_per_sec; //resets counter
      //contador_seg++;
      um_segundo = 0b01;
   }  

   //MINUTOS
   if(sec==60){ 
      sec=0;       
      min++;
      um_minuto = 0b1;
   }
    
   //HORAS
   if(min==60) { 
      min=0;
      //atualizar dados da eeprom aqui
   }
}


void main()
{
//===========REGISTRADORES===================================
   disable_interrupts(GLOBAL);                 // habilitar interr global
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);   // setar timer1 para interno
   enable_interrupts(INT_TIMER1);              // habilita Timer1 
   set_timer1(0);                              // limpar flag TMR1H & TMR1L 
   counter=int_per_sec;
   enable_interrupts(GLOBAL);                  // habilitar interr global
//----------------------------------------------------------


   while(TRUE)
   {
      
      //TODO: User Code
   }
   
}
