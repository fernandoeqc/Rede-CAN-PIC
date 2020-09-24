#include <timer.h>
#include <LCDedit.c>
#include <devboard.c>

struct latx{
   unsigned int8 status;
   unsigned int8 statusBuf;
   unsigned int8 pausa;
   unsigned int8 pausaBuf;
   unsigned int16 porta;
   unsigned int8 pino;

};
////////////////////////////////////////////////////////////////////////
//
// piscaLedStatus()
// 
// Recebe: status_led = qte de piscadas
//         porta = registrador responsavel pelo led (recomendado LATx)   
////////////////////////////////////////////////////////////////////////

void piscaLedStatus(struct latx *lat){
   struct latx latCopy;
   latCopy = *lat;

   //responsavel por desligar o led no segundo periodo
   //se led esta ligado, desliga
   if(bit_test(latCopy.porta,latCopy.pino))
   {
      bit_clear(latCopy.porta,latCopy.pino);
      return;
   }

   *lat = latCopy;
}

unsigned int16 ajusteTimer = 12; 

volatile unsigned int  counter = 10,
                       per = 9,
                       sec = 0,
                       min = 0,
                       hora = 0;

volatile unsigned int1 um_periodo = 0b0,
                       um_segundo = 0b0, 
                       um_minuto = 0b0,
                       uma_hora = 0b0;

#pragma INT_TIMER0
void TIMER0_isr(void)
{
   //entra a cada 1mS
   set_timer0(ajusteTimer);

   //PERIODO
   //entra a cada 100mS
   if(++counter==100){         
      per++;                
      counter=0; //resets counter
      um_periodo = 0b01;
   }

   //SEGUNDO
   if(per==10){
      //output_toggle(LED6);
      per = 0;
      sec++;
      um_segundo = 0b1;
   }

   //MINUTO
   if(sec==60){ 
      sec=0;       
      min++;
      um_minuto = 0b1;
   }

   //HORA
   if(min==60) { 
      min=0;
      hora++;
      //atualizar dados da eeprom aqui
   }
}

#pragma INT_EXT
void external_interrupt0(void)
{
   output_toggle(LED3);
   ajusteTimer++; 
}

#pragma INT_EXT1
void external_interrupt1(void)
{
   output_toggle(LED4); 
   ajusteTimer--; 
}

#pragma INT_EXT2
void external_interrupt2(void)
{
   output_toggle(LED5); 
   hora = 0;
   min = 0;
   sec = 0;
   per = 0;
}

void mostra_hora(void)
{
   lcd_putc_deca(hora);
   lcd_putc(":");
   lcd_putc_deca(min);
   lcd_putc(":");
   lcd_putc_deca(sec);
   lcd_putc(":");
   lcd_putc_deca(per);
}


void main()
{
   char k;

   //controle pino LED1 (RA4)
   struct latx LATA4;
   LATA4.status = 0x02;
   LATA4.statusBuf = 0x00;
   LATA4.pausa = 0x0A;
   LATA4.pausaBuf = 0x00;
   LATA4.porta = 0x10C;
   LATA4.pino = 0x04;

   disable_interrupts(GLOBAL);
   //enable_interrupts(INT_EXT);
   //enable_interrupts(INT_EXT1);
   enable_interrupts(INT_EXT2);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_8|RTCC_8_BIT); //Timer0_freq = MCU_freq / {4 * Prescaler * (256 – TMR0)}
   enable_interrupts(INT_TIMER0);
   set_timer0(ajusteTimer);
   enable_interrupts(GLOBAL);

/* 
   output_toggle(pin_b0); delay_ms(150);
   output_toggle(pin_b0); delay_ms(150);
   output_toggle(pin_b0); delay_ms(150);
   output_toggle(pin_b0); delay_ms(150);
*/
   
   lcd_init();

   lcd_putc("\fReady...\n"); 
   delay_ms(500);
   lcd_putc("            ");
   k = 0;

   while(TRUE)
   {
      if(um_periodo)
      {
         um_periodo = 0;

         lcd_gotoxy(0,0);
         mostra_hora();

         lcd_gotoxy(0,0);

      }
   }
}
