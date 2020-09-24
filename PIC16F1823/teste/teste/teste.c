#include <teste.h>
#define TEMPOCICLOLEDS 30

#include <placa_recep_antigo.h>
#include <can-mcp2515.c>

struct tempo{
   unsigned int seg;
   unsigned int contaSeg;
   unsigned int1 flag:1;
   unsigned int1 ativo:1;
};

/* volatile unsigned int8 contaPeriodo = TEMPOCICLOLEDS;
void piscaLedStatus(struct latx *lat){
	struct latx latCopy;
	latCopy = *lat;

	//responsavel por desligar o led no segundo periodo
	//se led esta ligado, desliga
	if(bit_test(*latCopy.porta,latCopy.pino))
	{
		bit_clear(*latCopy.porta,latCopy.pino);
		return;
	}



	*lat = latCopy;
} */


void gerenciaTempo(struct tempo *tmp)
{
	int a = 0;
	struct tempo b_tmp;
	b_tmp = *tmp;

	b_tmp.contaSeg ++;
	a = b_tmp.contaSeg;
	
	if(a == b_tmp.seg)
	{
		b_tmp.contaSeg = 0;
		b_tmp.flag = 1;
		a = 0;
	}

	*tmp = b_tmp;
}


void main()
{
	output_a(0b00000000);
	output_c(0b00000000);

	//controle pino LED1 (RA4)
	struct latx LATA4;
	LATA4.status = 0x05;
	LATA4.statusBuf = 0x00;
	LATA4.pausa = 0x0A;
	LATA4.pausaBuf = 0x00;
	LATA4.porta = 0x10C;
	LATA4.pino = 0x04;

	struct tempo contaBloq;
	contaBloq.seg = 0x05;
	contaBloq.contaSeg = 0x00;
	contaBloq.ativo = 0x01;
	contaBloq.flag = 0;

	disable_interrupts(GLOBAL);                 // habilitar interr global
	//enable_interrupts(INT_EXT_H2L);             // interrupcao CAN
	setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);   // setar timer1 para interno
	enable_interrupts(INT_TIMER1);              // habilita Timer1 
	set_timer1(0);                              // limpar flag TMR1H & TMR1L 
	counter=int_per_sec;
	enable_interrupts(GLOBAL);                  // habilitar interr global

	//LATA.statusBuf = 4;
	output_low(LED1);
	
	while(TRUE)
	{		
		if(flag_interr)
		{          
			flag_interr = 0b0;
		}

		if(contaBloq.flag)
		{


		}

		if(um_periodo)
		{
			um_periodo = 0;

			//passagem LATA.4 como parametro
			//piscaLedStatus(&LATA4);
			
			contaPeriodo--;
			if(contaPeriodo == 0)
			{
				contaPeriodo = TEMPOCICLOLEDS;
			}
		}	

      if(um_segundo)
      {
        um_segundo = 0b0;

		gerenciaTempo(&contaBloq);


         //piscaLed(1,50,LED2);
         
         //can_putd(0x71F,dadosEnv,2,0,0,0);

      }
	}
}
