#include <receptor.h>
#include <can-mcp2515.c>
#include <placa_recep.h>

#define MASTER 200
#define RECEPTOR1 303

void trata_dado()
{
   struct rx_stat rxstat;
   int32 tx_id;
   int8 rx_len;   
   int32 rx_id;
   int8 dadosEnv[8] = {0xAA,0xBB},
        dadosRec[8] = {0xAA,0xBB};
        
   flag_receb = 0b0;  
   if(can_getd (rx_id, dadosRec, rx_len, rxstat))
   {
      if(dadosRec[0] == 0xAA)
      {
         output_high(LED2);
         output_low(SAIDA1);
      }
      else if(dadosRec[0] == 0xBB)
      {
         output_low(LED2);
         output_high(SAIDA1);
      }
   }
}

//interrupcoes
unsigned int8 trata_interr()
{
   unsigned int8 int_id,i,int_unitario = 0x00; 
   piscaLed(1,100,LED1); 
   int_id = mcp2510_read(CANINTF);
   //int_unitario retorna o bit mais significativ de i
   if(int_id)
   {
      for (i = 1; i != 0; i<<=1)
      {
         if ((int_id & i) != 0) {int_unitario = i;}
      }
   }

   //int_unitario ee a interrupcao mais importante
   enum {CAN_RX0_INT=1,CAN_RX1_INT=2,CAN_TX0_INT=4,CAN_TX1_INT=8,CAN_TX2_INT=16,CAN_ERROR_INT=32,CAN_WAKE_INT=64,CAN_MESERR_INT=128};

   if(CAN_RX0_INT & int_id)
   {
      flag_receb = 0b1;
   }
   
   if(CAN_RX1_INT & int_id)
   {
      flag_receb = 0b1;
   }
   
   //REFATOR: Verificar individualmente cada interrupcao, ao inves de limpar todas de uma vez
   mcp2510_bitmodify(CANINTF,int_id,0x00);
   int_id = 0;
   return int_id;
}


void main()
{  
   //VEJA placa_plus.h
   set_tris_a(0b00001100);
   set_tris_c(0b00000010);
   output_low(LED1);
   output_low(LED2);
   
   output_high(LED1);
   delay_ms(200);

   can_init();

   output_low(LED1);
   delay_ms(200);
   
   can_set_mode(CAN_OP_CONFIG);
   can_set_id(RX0MASK,0x71F,CAN_USE_EXTENDED_ID);
   can_set_id(RX0FILTER0,0x71F,CAN_USE_EXTENDED_ID);
   can_set_id(RX0FILTER1,0x71F,CAN_USE_EXTENDED_ID);
   can_set_id(RX1MASK,0x71F,CAN_USE_EXTENDED_ID);
   can_set_id(RX1FILTER2,0x71F,CAN_USE_EXTENDED_ID);
   can_set_id(RX1FILTER3,0x71F,CAN_USE_EXTENDED_ID);
   can_set_id(RX1FILTER4,0x71F,CAN_USE_EXTENDED_ID);
   can_set_id(RX1FILTER5,0x71F,CAN_USE_EXTENDED_ID);
   can_set_interr(0x03);
   can_set_mode(CAN_OP_NORMAL);

   output_high(LED1);
   delay_ms(200);
   
//===========REGISTRADORES===================================
   disable_interrupts(GLOBAL);                 // habilitar interr global
   enable_interrupts(INT_EXT_H2L);             // interrupcao CAN
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);   // setar timer1 para interno
   enable_interrupts(INT_TIMER1);              // habilita Timer1 
   set_timer1(0);                              // limpar flag TMR1H & TMR1L 
   counter=int_per_sec;
   enable_interrupts(GLOBAL);                  // habilitar interr global
//----------------------------------------------------------

   output_low(LED1);
   delay_ms(200);

   while(TRUE)
   {
      if(flag_interr)
      {    
         flag_interr = 0b0;
         trata_interr();        
      }
      
      if(flag_receb)
      {
         trata_dado();
         //piscaLed(1,1,LED2);
      }


      if(um_segundo)
      {      
         um_segundo = 0b0;

      }
   }
}
