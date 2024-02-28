#include <p18f4520.h>

unsigned char uni_seg,dez_seg,uni_min,dez_min,uni_hor,dez_hor;

unsigned char converte_7seg [] =

{
	//hgfedcba
	0b00111111,		//zero
	0b00000110,		//um
	0b01011011,
	0b01001111,
	0b01100110,
	0b01101101,
	0b01111101,
	0b00000111,
	0b01111111,
	0b01101111,		//nove
};

void delay(void)
{
	unsigned long int i;
	for (i=0;i<=80000;i++) {}
}

void configura_sistema (void)
 
{
	TRISD=0B10000000;	//DISPLAY_7SEG COMO SAIDA
	TRISC=0B10000000;	//DISPLAY_7SEG COMO SAIDA
}

void inicializa_relogio ()

{
	dez_hor=0;
	uni_hor=0;
	dez_min=0;
	uni_min=0;
	dez_seg=5;
	uni_seg=0;
}

void mostra_relogio (void)

{
	LATD=converte_7seg[uni_seg];
	LATC=converte_7seg[dez_seg];
}

void atualiza_relogio (void)

{
	uni_seg++;
	if (uni_seg>9)
	{
		uni_seg=0;
		dez_seg++;
		if (dez_seg>5)
		{
			dez_seg=0;
		}
	}
}


main ()

{
	configura_sistema();
	inicializa_relogio();
	
	while (1)
	{
		mostra_relogio ();
		delay();
		atualiza_relogio ();		
	}
}