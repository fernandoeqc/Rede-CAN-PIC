#include <placa_testes.h>
#define TIMER0_F

#include <functions.h>


unsigned int data = 'D', last_data = 0;


void tabelaVerdade(void) {
      

}


void enviaUart(int data) {

}


void main()
{
   int8 conta_seg = 0;

   //===========REGISTRADORES===================================
   disable_interrupts(GLOBAL); // habilitar interr global
   enable_interrupts(INT_RDA); //UART
   //enable_interrupts(INT_EXT_H2L);         // interrupcao CAN
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8); // setar timer1 para interno
   enable_interrupts(INT_TIMER1);            // habilita Timer1
   set_timer1(0);                            // limpar flag TMR1H & TMR1L
   counter = int_per_sec;
   enable_interrupts(GLOBAL); // habilitar interr global
   //----------------------------------------------------------
   
   while(TRUE) {
      if (um_segundo) {
         um_segundo = 0;

         enviaUart(data);

         conta_seg++;
         if (conta_seg == 15) {
            conta_seg = 0;

            enviaComando();
         }


      }
   }
}
