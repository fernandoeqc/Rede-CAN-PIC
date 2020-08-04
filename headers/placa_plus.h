//********************************
//*   EEPROM                     *
//********************************
//DEFINE EEPROM_NOME PRIMEIRO ENDERECO,TAMANHO BYTES

//conta transmiss�es perdidas na CAN - bytes 0 a 3
#ROM 0xF000 = {0x00,0x00,0x00,0x00}
#define EP_NAO_TRANS 0x00,0x04

//conta quantas horas ligado desde o ultimo reset - bytes 4 a 5
#ROM 0xF004 = {0x00,0x00}
#define EP_HORA_LIGADO 0x04,0x02

//conta erros de comunica��o com MCP - bytes 6 a 9
#ROM 0xF006 = {0x00,0x00,0x00,0x00}
#define EP_MCP 0x06,0x04

//SELETOR DE FREQUENCIA - byte 0A
#ROM 0xF006 = {0x00}
#define EP_ID 0x0A,0x01

#define int_per_sec 10

//********************************

volatile unsigned int32 erro_nao_trans = 0,
                        erro_mcp = 0;

volatile unsigned int16 horas_ligado = 0;

volatile unsigned int8 counter = 0,
                       sec = 0,
                       min = 0;
                                              
volatile unsigned int1 um_segundo = 0b0, 
                       um_minuto = 0b0,
                       uma_hora = 0b0,
                       flag_interr = 0b0,
                       flag_envio = 0b0,
                       flag_receb = 0b0,
                       erro_nao_trans_flag = 0,
                       erro_mcp_flag = 0;
  
void external_can_interrupt ();
int8 detecta_freq(void);
void setup_can(void);
void piscaLed(char nPisca, int16 delay, int8 led);
void eeprom_grava(unsigned int8 address, unsigned int8 tamanho, unsigned int32 hexa);
unsigned int32 eeprom_le(unsigned int8 address, unsigned int8 tamanho);


#INT_TIMER1
void timer1_isr(){  // interrupt routine    
   set_timer1(53036);
   counter--;  // decrements counter which is set to it_per_sec 

   //SEGUNDOS
   if(counter==0){         
      sec++;                
      counter=int_per_sec; //resets counter
      //contador_seg++;
      um_segundo = 0b01;
   }

   //MINUTOS
   if(sec==60){ 
      sec=0;       
      min++;
      um_minuto = 0b1;
   }

   //HORAS
   if(min==60) { 
      min=0;
      //atualizar dados da eeprom aqui
   }
}

#int_ext
void external_can_interrupt ()
{
   flag_interr = 0b1;
}

int8 detecta_freq(void)
{
   int8 freq, i;
   for(freq = 0; freq < 6; freq++)
   {
      can_set_mode(CAN_OP_CONFIG);
      set_freq_var(freq);
      can_set_baud();
      can_set_mode(CAN_OP_LISTEN);
      
      for(i = 0; i < 8; i++)
      {
         delay_ms(500);
         if(can_kbhit()) return freq;
      }   
      piscaLed(1,1,LED2);
   }
   return 0xff;
}

void setup_can(int1 frequencia_eeprom, unsigned int8 interr, unsigned int8 can_mode)
{
   int8 freq = 0;
   can_init();
   
//!   can_set_mode(CAN_OP_CONFIG);
//!   can_set_id(RX0MASK,0x7E0,CAN_USE_EXTENDED_ID);
//!   can_set_id(RX0FILTER0,0x7E0,CAN_USE_EXTENDED_ID);
//!   can_set_id(RX0FILTER1,0x7E0,CAN_USE_EXTENDED_ID);
//!   can_set_id(RX1MASK,0x223,CAN_USE_EXTENDED_ID);
//!   can_set_id(RX1FILTER2,0x223,CAN_USE_EXTENDED_ID);
//!   can_set_id(RX1FILTER3,0x223,CAN_USE_EXTENDED_ID);
//!   can_set_id(RX1FILTER4,0x223,CAN_USE_EXTENDED_ID);
//!   can_set_id(RX1FILTER5,0x223,CAN_USE_EXTENDED_ID);

   frequencia_eeprom ? (freq = eeprom_le(EP_ID)) : (freq = detecta_freq());
  
   set_freq_var(freq);
   can_set_interr(interr);
   can_set_mode(can_mode); 
}

void piscaLed(char nPisca, unsigned int16 delay, unsigned int8 led)
{
     char i = 0;
     
     for(i = 0; i < nPisca; i++){
         output_high(led);
         delay_ms(20);
         output_low(led);
         delay_ms(delay);
     }
}

void eeprom_grava(unsigned int8 address, unsigned int8 tamanho, unsigned int32 hexa)
{
   unsigned int8 i = 0, bytes[4];               
   
   //separa bytes
   for (i = 0; i < tamanho; i++)
   {
     bytes[i] = hexa;
     hexa >>= 8;
   }
     
   //imprime na ordem inversa
   while(tamanho) 
   {
      write_eeprom(address++,bytes[--tamanho]);
      delay_ms(1);
   }
}

unsigned int32 eeprom_le(unsigned int8 address, unsigned int8 tamanho)
{
   unsigned int8 i = 0;
   unsigned int32 bytes = 0;
   
   for(i = tamanho; i > 0; i--)
   {
      bytes <<= 8;
      bytes |= read_eeprom(address++); 
      delay_ms(1);
   }
   return bytes;
}
