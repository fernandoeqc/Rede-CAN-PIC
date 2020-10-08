#include <mecanico.h>

//constante da funcao piscaLedStatus()
//1 TEMPOCICLOLEDS == 200mS na configuracao atual
#define TEMPOCICLOLEDS 30

#include <placa_recep_antigo.h>

void leAdc(int *leitura_adc_t)
{
   set_adc_channel(0);
   delay_us(20);
   leitura_adc_t[0] = read_adc();

   set_adc_channel(1);
   delay_us(20);
   leitura_adc_t[1] = read_adc();
}

void main()
{
   int8 adc1 = 0, adc2 = 0;
   int8 leitura_adc[2] = {0,0};

   setup_adc_ports(sAN0 | sAN1);
   setup_adc(ADC_CLOCK_DIV_32);

   //===========REGISTRADORES===================================
   disable_interrupts(GLOBAL); // habilitar interr global
   //enable_interrupts(INT_EXT_H2L);           // interrupcao CAN
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8); // setar timer1 para interno
   enable_interrupts(INT_TIMER1);            // habilita Timer1
   set_timer1(0);                            // limpar flag TMR1H & TMR1L
   counter = int_per_sec;
   enable_interrupts(GLOBAL); // habilitar interr global
   //----------------------------------------------------------

   while (TRUE)
   {
      if (um_periodo)
      {
         um_periodo = 0;

         leAdc(leitura_adc);

         output_toggle(LED1);
      }
      //TODO: User Code
   }
}
