#include <teste_can_rec.h>
#include <can-mcp2515.c>
#include <placa_plus.h>


#define MASTER 200
#define RECEPTOR1 303

unsigned int8 status = 0x08;

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
   
   int_id = mcp2510_read(CANINTF);
   //int_unitario retorna o bit mais significativ de i

   //int_unitario ee a interrupcao mais importante

   if (int_id & CAN_RX0_INT) {
      flag_receb = 0b1;
      status = 1;
   }
   
   if (int_id & CAN_RX1_INT) {
      flag_receb = 0b1;
      status = 1;
   }
   
   if (int_id & CAN_TX0_INT) {
      //flag_receb = 0b1;
      status = 2;
   }

   if (int_id & CAN_TX1_INT) {
      //flag_receb = 0b1;
      status = 4;
   }

   if (int_id & CAN_TX2_INT) {
      //flag_receb = 0b1;
      status = 5;
   }

   if (int_id & CAN_ERROR_INT) {
      //flag_receb = 0b1;
      status = 6;
   }

   if (int_id & CAN_WAKE_INT) {
      //flag_receb = 0b1;
      status = 7;
   }

   if (int_id & CAN_MESERR_INT) {
      //flag_receb = 0b1;
      status = 8;
   }
   
   mcp2510_bitmodify(CANINTF,int_unitario,0x00);
   int_id &= ~int_unitario;
   return int_id;
}

void main()
{  
   unsigned int8 conta_seg = 0;

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
         piscaLed(status,100,LED2);
         conta_seg = 0;
      }
      
      if(um_segundo)
      {      
         conta_seg++;
         if(conta_seg == 6) {
            conta_seg = 0;
            piscaLed(status,100,LED1);
         }
      }
   }
}


