#include <transmissor.h>
#include <can-mcp2515.c>
#include <placa_recep.h>


#define MASTER 200
#define RECEPTOR1 303

//interrupcoes
unsigned int8 trata_interr()
{
   unsigned int8 int_id,i,int_unitario = 0x00; 
   
   int_id = mcp2510_read(CANINTF);
   if(int_id)
   {
      for (i = 1; i != 0; i<<=1)
      {
         if ((int_id & i) != 0) {int_unitario = i;}
      }   
   }

   switch (int_unitario)
   {
      case CAN_RX0_INT:
         break;     
      case CAN_RX1_INT:
         break;      
      case CAN_TX0_INT:
         break;     
      case CAN_TX1_INT:
         break;  
      case CAN_TX2_INT:
         break;      
      case CAN_ERROR_INT:
         break;
      case CAN_WAKE_INT:
         break;      
      case CAN_MESERR_INT:
         mcp2510_bitmodify(CANINTF,int_unitario,0x00);
         break;      
      default: 
         break; //erro!
   }
   
   
   int_id &= ~int_unitario;
   return int_id;
}

void main()
{             
   int8 dadosEnv[8] = {0xCC,0xDD};

   //VEJA placa_plus.h
   set_tris_a(0b00001100);
   set_tris_c(0b00000010);
   output_low(LED1);
   output_low(LED2);
   
   output_high(LED1);
   delay_ms(200);
   output_low(LED1);
   delay_ms(200);
   output_high(LED1);
   delay_ms(200);
   output_low(LED1);
   delay_ms(200);
 
   can_init();
   can_set_mode(CAN_OP_CONFIG);
   can_set_interr(0x80);//tx0 e mserr
   can_set_mode(CAN_OP_NORMAL);
   
//===========REGISTRADORES===================================
   disable_interrupts(GLOBAL);                 // habilitar interr global
   enable_interrupts(INT_EXT_H2L);             // interrupcao CAN
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);   // setar timer1 para interno
   enable_interrupts(INT_TIMER1);              // habilita Timer1 
   set_timer1(0);                              // limpar flag TMR1H & TMR1L 
   counter=int_per_sec;
   enable_interrupts(GLOBAL);                  // habilitar interr global
//----------------------------------------------------------

   while(TRUE)
   {   
      
      if(flag_interr)
      {
         flag_interr = 0b0;
         trata_interr();
         output_low(AVISO);
         piscaLed(2,50,LED1);
      }
      else
      {
         output_high(AVISO);
      }
      
      if(!input(BLOQ)) {dadosEnv[0] = 0xBB;}    
      else {dadosEnv[0] = 0xAA;}
   
   
      if(um_segundo)
      {
         um_segundo = 0b0;
         can_putd(0x71F,dadosEnv,2,0,0,0);
         delay_ms(10);
         piscaLed(1,1,LED1);
      }
   }
}



