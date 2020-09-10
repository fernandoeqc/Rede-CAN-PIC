#include <transmissor.h>

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

#define MASTER 200
#define RECEPTOR1 303

//interrupcoes
unsigned int trata_interr()
{
   unsigned int int_id,i,int_unitario = 0x00; 
   enum {CAN_RX0_INT=1,CAN_RX1_INT=2,CAN_TX0_INT=4,CAN_TX1_INT=8,CAN_TX2_INT=16,CAN_ERROR_INT=32,CAN_WAKE_INT=64,CAN_MESERR_INT=128};

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
   int dadosEnv[8] = {0xAA,0xBB};
   int contaSeg = 0;
   int retorno = 0;

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
      /* 
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
      
      if(!input(BOTAO)) {dadosEnv[0] = 0xBB;}    
      else {dadosEnv[0] = 0xAA;} */
   
   
      if(um_periodo)
      {
         um_periodo = 0b0;
         
         piscaLedStatus(&LATA4); 

         contaPeriodo--;
			if(contaPeriodo == 0)
			{
            contaPeriodo = TEMPOCICLOLEDS;
			}
      }

      if(um_segundo)
      {
         um_segundo = 0b0;

         piscaLed(1,50,LED2);
         
         can_putd(0x71F,dadosEnv,2,0,0,0);
         //delay_ms(10);
         //retorno = mcp2510_read(TXB0CTRL);
         //write_eeprom(0x08,retorno);
         
         contaSeg++;
         if(contaSeg > 5)
         {
            contaSeg = 0;
         }
      }
   }
   //#error ********* continuar trabalho.txt *********
}



