#include <mecanico.h>

#define COMANDO_BLOQUEIO 'B'
#define COMANDO_DESBLOQUEIO 'D'

//constante da funcao piscaLedStatus()
//1 TEMPOCICLOLEDS == 200mS na configuracao atual
#define TEMPOCICLOLEDS 30
#include <placa_recep_antigo.h>

//SELETOR DE FREQUENCIA - byte 0A
#pragma ROM 0xF013 = {0x00}
#define EP_CONTROL_FLAGS 0x0B,0x01

//SELETOR DE FREQUENCIA - byte 0A
#pragma ROM 0xF014 = {0x00}
#define EP_ID 0x0C,0x01

//SELETOR DE FREQUENCIA - byte 0A
#pragma ROM 0xF015 = {0x00}
#define EP_ID 0x0D,0x01


int8 data = 0, last_data = 0;

//precisa iniciar com valores diferentes 
unsigned int8 control_flags = 0b111, 
              last_control_flags = 0b000; 

#pragma INT_RDA
void RDA_isr(void) {  
   data = getc();
}

struct adc {
   unsigned int8 bateria;
   unsigned int8 alimentacao;
};

void leAdc(struct adc *leitura_adc) {
   struct adc adc_copy;
   adc_copy = *leitura_adc;

   set_adc_channel(2);
   delay_us(20);
   adc_copy.alimentacao = read_adc();

   set_adc_channel(4);
   delay_us(20);
   adc_copy.bateria = read_adc();

   *leitura_adc = adc_copy;
}

unsigned int8 trataAdc(struct adc dados) {
  unsigned int8 control = 0b0000, limiteBateria = 150, limiteAlim = 100;

  if (dados.bateria >= limiteBateria && dados.alimentacao >= limiteAlim) {
    control = 0b0011;
  } if (dados.bateria >= limiteBateria && dados.alimentacao < limiteAlim) {
    control = 0b0010;
  } if (dados.bateria < limiteBateria && dados.alimentacao >= limiteAlim) {
    control = 0b0001;
  } if (dados.bateria < limiteBateria && dados.alimentacao < limiteAlim) {
    control = 0b0000;
  }

  return control;
}

unsigned char trataUart(){

   if(data != last_data){
      last_data = data;

      if(data == COMANDO_BLOQUEIO){
         output_high(LED2);
         return 0;
      }
      else if(data == COMANDO_DESBLOQUEIO){
         output_low(LED2);
         return 0b100;
      }
      data = 0;
      output_toggle(LED1);
      
   }
   return;
}

void checkState(unsigned int8 c_adc, unsigned int8 c_uart, unsigned int8 c_fim_curso){
   
   control_flags = c_adc + c_uart;

   if(control_flags != last_control_flags){
      last_control_flags = control_flags;

      if(control_flags == 4) eeprom_grava(EP_CONTROL_FLAGS,1,control_flags); // DEBUG EEPROM

      if(control_flags == 0b111) {
         blockMotor(FALSE);
         turnBattery(FALSE);
      }
      else if(control_flags == 0b110) {
         blockMotor(FALSE);
         turnBattery(TRUE);
      }
      else{
         blockMotor(TRUE);
         turnBattery(TRUE);
      }
   }
}

void main()
{
   unsigned int8 adc1 = 0,           //batteria
                 adc2 = 0,           //alimentacao
                 ctrl_adc = 0,
                 ctrl_uart = 0,      //bits de controle de dados
                 ctrl_fim_curso = 0; 
                 
   unsigned char command = 0;                   //dados de comando pelo UART
  
   //flags de controle de fim de curso, dados, tensao veiculo, tensao bateria
      

   setup_adc_ports(sAN2 | sAN4);
   setup_adc(ADC_CLOCK_DIV_32);

   //===========REGISTRADORES===================================
   disable_interrupts(GLOBAL);               // habilitar interr global
   enable_interrupts(INT_RDA);               //UART
   //enable_interrupts(INT_EXT_H2L);         // interrupcao CAN
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8); // setar timer1 para interno
   enable_interrupts(INT_TIMER1);            // habilita Timer1
   set_timer1(0);                            // limpar flag TMR1H & TMR1L
   counter = int_per_sec;
   enable_interrupts(GLOBAL);                // habilitar interr global
   //----------------------------------------------------------

   struct adc leitura_adc;
   leitura_adc.alimentacao = 200;
   leitura_adc.bateria = 180;

 
   while (TRUE)
   {
      if (um_segundo)
      {
         um_segundo = 0;

         /* leAdc(leitura_adc);

         result_adc = trataAdc(leitura_adc); */
         ctrl_uart = trataUart();
         ctrl_adc = trataAdc(leitura_adc);
         ctrl_fim_curso = trataFimCurso();
         
         check_state(ctrl_uart,ctrl_adc,ctrl_fim_curso);

      }
      //TODO: User Code
      //control_flags;
   }
}
