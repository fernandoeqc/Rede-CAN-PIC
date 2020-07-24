#include <LCD2.h>

#include <LCDedit.c>


void main()
{
   char k;
   
   output_b(0x00);
   output_d(0x00);
   
   output_toggle(pin_b0); delay_ms(150);
   output_toggle(pin_b0); delay_ms(150);
   output_toggle(pin_b0); delay_ms(150);
   output_toggle(pin_b0); delay_ms(150);
   
   
   
   lcd_init();

   lcd_putc("\fReady...\n"); delay_ms(500);
   lcd_gotoxy(3,2);
   k = "A";
   lcd_putc(k); delay_ms(500);
   
   
   
   while(TRUE)
   {
       //lcd_putc("\f");
       lcd_putc(k);
       K++;
       
       output_b(k);
       delay_ms(1000);

      //TODO: User Code
   }

}
