//!#IF 5 == 5
//!   #ERROR LCD e LED_D usando a mesma porta!
//!#ENDIF

int1 listen_bus(void);
int8 detecta_freq(void);
void setup_can(void);
void setup_lcd(void);
void setup_iterrupt(void);
void setup_io(void);

#IFDEF LED_B
   #DEFINE LED1  PIN_B0
   #DEFINE LED2  PIN_B1
   #DEFINE LED3  PIN_B2
   #DEFINE LED4  PIN_B3
   #DEFINE LED5  PIN_B4
   #DEFINE LED6  PIN_B5
   #DEFINE LED7  PIN_B6
   #DEFINE LED8  PIN_B7
#ELSE
   #IFDEF LED_D
      #DEFINE LED1 PIN_D0
      #DEFINE LED2 PIN_D1
      #DEFINE LED3 PIN_D2
      #DEFINE LED4 PIN_D3
      #DEFINE LED5 PIN_D4
      #DEFINE LED6 PIN_D5
      #DEFINE LED7 PIN_D6
      #DEFINE LED8 PIN_D7
   #ENDIF
#ENDIF



