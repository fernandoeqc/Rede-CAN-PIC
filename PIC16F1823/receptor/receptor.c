#include <receptor.h>

//constante da funcao piscaLedStatus()
//1 TEMPOCICLOLEDS == 200mS na configuracao atual
#define TEMPOCICLOLEDS 30

//CASO USE O PLUS ATUAL, COMENTE A LINHA ABAIXO
#define PLACA_PLUS_ANTIGO TRUE

#if PLACA_PLUS_ANTIGO
   #include <placa_recep_antigo.h>
   
#else
   #include <placa_recep.h>
#endif

#include <can-mcp2515.c>

//ID rede can
#define MASTER 200
#define RECEPTOR1 303

int trata_dado()
{
   struct rx_stat rxstat;
   int32 tx_id;
   int rx_len;   
   int32 rx_id;
   int dadosEnv[8] = {0xAA,0xBB},
       dadosRec[8] = {0xAA,0xBB};
          
   if(can_getd (rx_id, dadosRec, rx_len, rxstat))
   {
      if(dadosRec[0] == 0xAA)
      {
         //output_high(LED2);
         output_low(SAIDA1);
         return 1;
      }
      else if(dadosRec[0] == 0xBB)
      {
         //output_low(LED2);
         output_high(SAIDA1);
         return 1;
      }
   }
   return 0;
}

//interrupcoes
unsigned int trata_interr()
{
   unsigned int int_id,i,int_unitario = 0x00; 
   
   int_id = mcp2510_read(CANINTF);

   //int_unitario ee a interrupcao mais importante
   enum {CAN_RX0_INT=1,CAN_RX1_INT=2,CAN_TX0_INT=4,CAN_TX1_INT=8,CAN_TX2_INT=16,CAN_ERROR_INT=32,CAN_WAKE_INT=64,CAN_MESERR_INT=128};

   if(int_id == 0x00)
   {
      //nao occoreu nenhuma interrupcao! erro!
      return 4;
   }

   //ex.:  
   //    1000 0001 : int_id
   // &  1000 0000 : CAN_MESERR_INT
   // ------------
   //    1000 0000 = TRUE
   if((CAN_RX0_INT & int_id) || (CAN_RX1_INT & int_id))
   {
      flag_receb = 0b1;
      return 1;
   }
   
   if(CAN_ERROR_INT & int_id)
   {
      return 5;
   }

   if(CAN_MESERR_INT & int_id)
   {
      return 6;
   }
   
   //REFATOR: Verificar individualmente cada interrupcao, ao inves de limpar todas de uma vez
   mcp2510_bitmodify(CANINTF,int_id,0x00);
   int_id = 0;
   
   //ERRO: ADICIONAR OUTRAS INTERRUPÇÕES
   return 3;
}


void main()
{  
   //VEJA placa_plus.h
   set_tris_a(0b00001100);
   set_tris_c(0b00000010);
  
   output_a(0b00000000);
	output_c(0b00000000);

	//controle pino LED1 (RA4)
	struct latx LATA4;
	LATA4.status = 0x02;
	LATA4.statusBuf = 0x00;
	LATA4.pausa = 0x0A;
	LATA4.pausaBuf = 0x00;
	LATA4.porta = 0x10C;
	LATA4.pino = 0x04;

	//controle pino LED2 (RC5)
	struct latx LATC5;
	LATC5.status = 0x02;
	LATC5.statusBuf = 0x00;
	LATC5.pausa = 0x0A;
	LATC5.pausaBuf = 0x00;
	LATC5.porta = 0x10E;
	LATC5.pino = 0x05;

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
   //status = 4; //**************************************************************
   delay_ms(200);

   flag_interr = 0;

   while(TRUE)
   {
      if(flag_interr)
      {    
         flag_interr = 0b0;
         LATA4.status = trata_interr();        
      }
      
      if(flag_receb)
      {
         piscaLed(1,50,LED2);
         trata_dado();
         flag_receb = 0b0;
      }

      if(um_periodo)
      {      
         um_periodo = 0;

			//LED1
			piscaLedStatus(&LATA4);

			contaPeriodo--;
			if(contaPeriodo == 0)
			{
            contaPeriodo = TEMPOCICLOLEDS;
			}
      }

      if(um_segundo)
      {
         //piscaLed(1,1,LED2);
      }
   }
}
