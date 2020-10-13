#include <mecanico.h>

//constante da funcao piscaLedStatus()
//1 TEMPOCICLOLEDS == 200mS na configuracao atual
#define TEMPOCICLOLEDS 30

#include <placa_recep_antigo.h>

struct adc {
   unsigned int8 bateria;
   unsigned int8 alimentacao;
};

void leAdc(struct adc *leitura_adc)
{
   struct adc adc_copy;
   adc_copy = *leitura_adc;

   set_adc_channel(2);
   delay_us(20);
   adc_copy.alimentacao = read_adc();

   set_adc_channel(4);
   delay_us(20);
   adc_copy.bateria = read_adc();

   *leitura_adc = adc_copy;
}

void main()
{
   int8 adc1 = 0, adc2 = 0;
   int8 leitura_adc[2] = {0,0};

   setup_adc_ports(sAN2 | sAN4);
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
      if (um_segundo)
      {
         um_segundo = 0;

         leAdc(leitura_adc);

         write_eeprom(0x13,leitura_adc[0]); delay_us(50);
         write_eeprom(0x14,leitura_adc[1]); delay_us(50);

         output_toggle(LED1);
      }
      //TODO: User Code
   }
}
