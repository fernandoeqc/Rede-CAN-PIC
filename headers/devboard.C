
int8 detecta_freq(void)
{
   int8 freq, i;
   for(freq = 0; freq < 6; freq++)
   {
      can_set_mode(CAN_OP_CONFIG);
      set_freq_var(freq);
      can_set_baud();
      can_set_mode(CAN_OP_LISTEN);
      lcd_gotoxy(0,0);
      lcd_putc_hexa(freq);
      
      for(i = 0; i < 8; i++)
      {
         delay_ms(500);
         if(can_kbhit()) return freq;
      }   
      output_toggle(LED2);
   }
   return 0xff;
}

void setup_can(void)
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

   freq = detecta_freq();
   lcd_putc_hexa(0xAA); delay_ms(500);
   
   can_set_mode(CAN_OP_NORMAL);   
   
   //can_set_interr(0x03); //receive data only
}

void setup_lcd(void)
{
   lcd_init();
   lcd_cursor_on(1);
   lcd_putc("\fReady...\n"); delay_ms(500);
   lcd_send_byte(0,0x01);
}

void setup_interrupt(void)
{
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_32);      //1,0 s overflow
   enable_interrupts(INT_EXT);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
}

void setup_io(void)
{
   //VEJA placa_plus.h
   set_tris_a(0b00001100);
   set_tris_b(0b00010001);
   set_tris_c(0b00010000);
   set_tris_d(0b00000000);
   
   output_high(LED1);
   delay_ms(200);
   output_low(LED1);
   delay_ms(200);
   output_high(LED1);
   delay_ms(200);
   output_low(LED1);
   delay_ms(200);
   
   output_low(LED1);
   output_low(LED2);
}

#DEFINE TECLADO_ON
#IFDEF TECLADO_ON
const char map_key[3][5] = {"<741", "0852", ">963"};
char key = 0,
     prev_key = 0;
    

char teclado()
{
   int8 i = 0,
        j = 0,
        portd = 0;
   
   //faz a leitura inicial do teclado
   output_low(pin_b0);
   output_low(pin_b1);
   output_low(pin_b2);
   portd = input_d();
   output_high(pin_b0);
   output_high(pin_b1);
   output_high(pin_b2);
   
   //se alguma tecla for pressionada:
   if(portd != 0x0f)
   {
      for(i = 0; i < 3; i++)
      {
         output_low(pin_b0 + i);
         portd = input_d();
         for(j = 0; j < 4; j++)
         {
            if(!bit_test(portd, j))
            {
               key = map_key[i][j];
               //previne a releiturada tecla repetidamente
               if(key != prev_key)
               {
                  prev_key = key;
                  return key; 
               }
            }
         }
         output_high(pin_b0 + i);
      }   
   }
   else {prev_key = 0;}
   return 0;
}
#ENDIF

void piscaLed(char nPisca, unsigned int16 delay, unsigned int8 led)
{
     char i = 0;
     
     for(i = 0; i < 5; i++){
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