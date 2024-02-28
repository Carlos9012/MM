#include <p18f4520.h>
#define BOTAO1 PORTAbits.RA0
#define BOTAO2 PORTAbits.RA1
#define BOTAO3 PORTAbits.RA2
#define BUZZER LATEbits.LATE2

unsigned char seg,min,hor, aux_seg, aux_min, aux_hor, help_seg;

unsigned char converte_bcd[] =

{
	//hgfedcba
	0b00000000,		//zero
	0b00000001,		//um
	0b00000010,
	0b00000011,
	0b00000100,
	0b00000101,
	0b00000110,
	0b00000111,
	0b00001000,
	0b00001001,		//nove
	0b00010000,		//10
	0b00010001,		//11
	0b00010010,
	0b00010011,
	0b00010100,
	0b00010101,
	0b00010110,
	0b00010111,
	0b00011000,
	0b00011001,		//19
	0b00100000,		//20
	0b00100001,		//21
	0b00100010,
	0b00100011,
	0b00100100,
	0b00100101,
	0b00100110,
	0b00100111,
	0b00101000,
	0b00101001,		//29
	0b00110000,		//30
	0b00110001,		//31
	0b00110010,
	0b00110011,
	0b00110100,
	0b00110101,
	0b00110110,
	0b00110111,
	0b00111000,
	0b00111001,		//39
	0b01000000,		//40
	0b01000001,		//41
	0b01000010,
	0b01000011,
	0b01000100,
	0b01000101,
	0b01000110,
	0b01000111,
	0b01001000,
	0b01001001,		//49
	0b01010000,		//50
	0b01010001,		//51
	0b01010010,
	0b01010011,
	0b01010100,
	0b01010101,
	0b01010110,
	0b01010111,
	0b01011000,
	0b01011001,		//59
	0b01100000,		//60

	
};

void delay(void)
{	
	
	unsigned long int i;
	for (i=0;i<=80000;i++) {}
}

void configura_sistema (void)
 
{
	TRISE=0B00000000;
	TRISD=0B00000000;	//DISPLAY_7SEG COMO SAIDA
	TRISC=0B00000000;	//DISPLAY_7SEG COMO SAIDA
	TRISB=0B00000000;
	ADCON1=0B00001111;
}

void inicializa_relogio ()

{
	hor=11;
	min=58;
	seg=50;
	aux_hor=10;
	aux_min=59;
	aux_seg=0;
	help_seg = seg + 2;
}

void mostra_relogio (void)

{
	LATC=converte_bcd[min];
	LATD=converte_bcd[seg];
	LATB=converte_bcd[hor];
}

void atualiza_relogio (void)

{
	seg++;
	if(seg>=60){
		min++;
		seg=0;
			if(min>=60){
				hor++;
				min=0;
				seg=0;
					if(hor>=12){
						hor=0;
						min=0;
						seg=0;
			}
		}
	}
	if(min>=60){
		hor++;
		min=0;
	}
	if(hor>=12){
		hor=-1;
	}
}
void ajusta_min(void){
	if(BOTAO1==1){min++;}
}

void ajusta_hor(void){
	if(BOTAO2==1){hor++;}
}

void config_alarm(void){

	LATC=converte_bcd[aux_min];
	LATD=converte_bcd[0];
	LATB=converte_bcd[aux_hor];
	
	if(BOTAO1==1){
		aux_min++;
		if(aux_min>=60){
			aux_hor++;
			aux_min=0;
		}
	}
	if(BOTAO2==1){
		aux_hor++;
		if(aux_hor>=12){
			aux_hor=0;
		}
	}
}

void alarm(void){
	
	if(aux_min == min && aux_hor==hor){BUZZER = 1;}
	else{BUZZER = 0;}
}


main ()

{
	configura_sistema();
	inicializa_relogio();
	TRISAbits.RA0 = 1;
	TRISAbits.RA1 = 1;
	TRISAbits.RA2 = 1;
	TRISEbits.RE1 = 0;
	
	while(1){
		alarm();
		if(BOTAO3 == 0){
			mostra_relogio();
			delay();
			atualiza_relogio();
			ajusta_hor();
			ajusta_min();
		
		}
		if(BOTAO3 == 1){
			delay();
			config_alarm();	
			atualiza_relogio();
			atualiza_relogio();
			delay();
		}
	}	
}