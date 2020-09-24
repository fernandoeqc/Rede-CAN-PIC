#include <loopback_teste.h>

#include <LCDedit.c>
#include <devboard.c>
#include <can-mcp2515.c>

#define MASTER 200
#define RECEPTOR1 303

#pragma INT_TIMER0
void TIMER0_isr(void)
{
   //output_toggle(LED2);
}

void can_loop(int8 *dadosEnv_p)
{
   struct rx_stat rxstat;
   int32 rx_id;
   int32 tx_id;
   int8 rx_len,
       dadosRec[8];

   can_putd(200, dadosEnv_p, 2, 0, 0, 0);
   delay_ms(10);

   if (can_kbhit())
   {
      if (can_getd(rx_id, dadosRec, rx_len, rxstat))
      {
         if (rx_id == 200)
         {
            lcd_putc_hexa(dadosRec[0]);

            //!               if(dadosRec[0] == 0xAA){
            //!                  output_high(LED2);
            //!               }
            //!               else if(dadosRec[0] == 0xBB){
            //!                  output_low(LED2);
            //!               }
         }
      }
   }
}

void main()
{
   int1 inc_flag = 0b0;
   struct rx_stat rxstat;
   int32 rx_id;
   int32 tx_id;
   int8 rx_len;

   int8 dadosEnv[8] = {0xAA, 0x40},
        dadosRec[8];
   int8 teste[10] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

   int8 num[10] = {0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x3f};

   int1 proximo = 0;
   char k;

   //VEJA placa_plus.h
   set_tris_a(0b00001100);
   set_tris_b(0b00010000);
   set_tris_c(0b00010000);
   set_tris_d(0b00000000);

   output_a(0b00000000);
   output_b(0b00000000);
   output_c(0b00000000);
   output_d(0b00000000);
   output_e(0b00000000);

   output_low(LED1);
   output_low(LED2);

   output_high(LED1);
   delay_ms(200);
   output_low(LED1);
   delay_ms(200);

   //usando hardware
   //!   setup_spi(SPI_MASTER|SPI_L_TO_H|SPI_XMIT_L_TO_H
   //!  |SPI_CLK_DIV_4|SPI_SAMPLE_AT_END);
   //!

   lcd_init(); 
   can_init();

   output_high(LED1);
   delay_ms(200);
   output_low(LED1);
   delay_ms(200);
   //can_set_mode(CAN_OP_CONFIG);

   //!
   //!   can_set_id(RX0MASK,303,CAN_USE_EXTENDED_ID);
   //!   can_set_id(RX0FILTER0,307,CAN_USE_EXTENDED_ID);
   //!   can_set_id(RX0FILTER1,0,CAN_USE_EXTENDED_ID);
   //!   can_set_id(RX1MASK,305,CAN_USE_EXTENDED_ID);
   //!   can_set_id(RX1FILTER2,309,CAN_USE_EXTENDED_ID);
   //!   can_set_id(RX1FILTER3,0,CAN_USE_EXTENDED_ID);
   //!   can_set_id(RX1FILTER4,0,CAN_USE_EXTENDED_ID);
   //!   can_set_id(RX1FILTER5,0,CAN_USE_EXTENDED_ID);
   //!




   can_set_mode(CAN_OP_LOOPBACK);
      
   //INT_EN();

   lcd_putc("\fReady...\n"); delay_ms(500);

   k = 9;

   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_32);      //1,0 s overflow

   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);

   //output_high(PIN_A2);
   
   
   
   while(TRUE)
   {
//!      output_low(CS);
//!      spi_xfer(MCP2510,0xab);
//!      output_high(CS);
//!      output_toggle(LED1);
      
      
      //can_loop(dadosEnv);
      delay_ms(1000);
      output_toggle(LED3);
      //lcd_putc_hexa(dadosEnv[0]);
//!      ///////modo teste
//!      //mcp2510_write(CANINTE,0X22);
//!      //delay_ms(10);
//!      //test = mcp2510_read(CANINTE);
//!      //////////
      
      
//!      if(input(BUT1)){
//!         inc_flag = 0b1;
//!         dadosEnv[0] = 0xAA;
//!      }
//!      else{
//!         dadosEnv[0] = 0xBB;
//!         if(inc_flag){
//!            dadosEnv[1]++;
//!            inc_flag = 0b0;
//!         }     
//!      }


      dadosEnv[1]++;
      
      
      can_putd(200,dadosEnv,2,0,0,0);
      delay_ms(100);
      
      if(can_kbhit()){
         if (can_getd (rx_id, dadosRec, rx_len, rxstat)){
            if (rx_id == MASTER){ // MASCARA VIRTUAL
               if(dadosRec[0] == 0xAA){                
                  output_high(LED2);
               }
               else if(dadosRec[0] == 0xBB){
                  output_low(LED2);
               }
               //lcd_putc_hexa(dadosRec[0]);
               lcd_putc_hexa(dadosRec[1]);
            }
         }   
      }
   }
}
