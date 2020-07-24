#include <display1.h>
#include <devboard.h>
#include <LCDedit.c>
#include <can-mcp2515.c>
#include <devboard.c>

#define MASTER 200
#define RECEPTOR1 303

//interrupções
//enum {CAN_RX0_INT=1,CAN_RX1_INT=2,CAN_TX0_INT=4,CAN_TX1_INT=8,CAN_TX2_INT=16,CAN_ERROR_INT=32,CAN_WAKE_INT=64,CAN_MESERR_INT=128};
int1 interr = 0b0;

#INT_EXT
void external_can_interrupt (){
   int int_id;
   int_id=mcp2510_read(CANINTF);

   output_toggle(LED1);
   
   switch(int_id) {
   case CAN_RX0_INT:
      interr = 1;//interr = int_id;lcd_putc("ENCONTRADO");// add receive code here
      break;
      
   case CAN_RX1_INT:
      interr = 1;//lcd_putc("ENCONTRADO");// add receive code here
      break;
      
   case CAN_ERROR_INT:
      
      // add error code here
      break;
   case CAN_MESERR_INT:
       
      // add message error code here
      break;
   case CAN_TX0_INT:
      output_high(LED2);
      break;
   case CAN_TX1_INT:

      break;
   case CAN_TX2_INT:
     
      break;
   }
}

#INT_TIMER0
void  TIMER0_isr(void) 
{
   //output_toggle(LED1);
}

int8 dados_env_buf[8];
int1 verif_novo_dado(*dadosEnv, tam_dado)
{
   int8 i;
   int1 diferente = 0b0;
   
   for(i = 0; i < tam_dado; i++)
   {
      if(dadosEnv[i] != dados_env_buf[i])
      {
         dados_env_buf[i] = dadosEnv[i];
         diferente = 0b1;
         write_eeprom(i,dados_env_buf[i]);
      }
   }
   return diferente;
}



void main()
{  
   //int1 inc_flag = 0b0;
   struct rx_stat rxstat;
   int32 rx_id;
   //int32 tx_id;
   int8 rx_len, i;   
   
   int8 dadosEnv[8] = {0xAA,0x40},
        dadosRec[8],
        k = 0x00;
        
   //int8 teste[10] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
   //int8 num[10] = {0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x3f};
   //int1 proximo = 0;
   //char k;

//!   setup_io();
//!   setup_lcd();
//!   setup_can();
//!   setup_interrupt();

   while(TRUE)
   {
      delay_ms(500);
      output_toggle(LED1);
//!      if(can_kbhit())
//!      {
//!         if (can_getd (rx_id, dadosRec, rx_len, rxstat))
//!         {
//!            //output_toggle(LED1);
//!            
//!            //lcd_putc_hexa(interr);
//!            
//!            if(dadosRec[0] == 0xAA) output_high(LED2);
//!            else if(dadosRec[0] == 0xBB)output_low(LED2);
//!            
//!            lcd_gotoxy(0,0);
//!            lcd_putc_hexa(rx_id);
//!            
//!            lcd_gotoxy(0,1);
//!            for(i = 0; i < rx_len; i++)
//!            {
//!               lcd_putc_hexa(dadosRec[i]);
//!            }
//!         }   
//!      }
   }
}

