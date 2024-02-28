#include <p18f4520.h>

#pragma config OSC=INTIO67	// clock interno (oscilador) e libera pinos RA6 e RA7 como IO

#define     ponto   LATCbits.LATC7
#define		c1		LATBbits.LATB0
#define		c2		LATBbits.LATB1
#define		c3		LATBbits.LATB2

#define		l1		PORTBbits.RB3
#define		l2		PORTBbits.RB4
#define		l3		PORTBbits.RB5
#define		l4		PORTBbits.RB6

#define	displays 	LATC

#define d1 LATDbits.LATD0
#define d2 LATDbits.LATD1
#define d3 LATDbits.LATD2
#define d4 LATDbits.LATD3
#define d5 LATDbits.LATD4
#define d6 LATDbits.LATD5


char converte_7seg [] = 
{
//hgfedcba		//mapeamento de segmentos do display 7seg
0b00111111,		//"0"
0b00000110,		//"1"
0b01011011,		//"2"
0b01001111,		//"3"
0b01100110,		//"4"
0b01101101,		//"5"
0b01111101,		//"6"
0b00000111,		//"7"
0b01111111,		//"8"
0b01101111,		//"9"
0b10111111,		//"0."
0b10000110,		//"1."
0b11011011,		//"2."
0b11001111,		//"3."
0b11100110,		//"4."
0b11101101,		//"5."
0b11111101,		//"6."
0b10000111,		//"7."
0b11111111,		//"8."
0b11101111,		//"9."
};

char dh=10,uh=0,dm=0,um=0,ds=0,us=0,ms=0;
char p1=0,p2=0,p3=0,p4=0,p5=0,p6=0;
char cont = 0;
char aux = 0;


void delay_ms(void){
	unsigned int i;
	for(i=0;i<1310;i++){}
}

void varre_display(void)
{
		d1=1;
		d2=1;
		d3=1;
		d4=1;
		d5=1;
		d6=1;
		
				
		displays = converte_7seg[dh];
		d1=0;		
		delay_ms();
		d1=1;					
				
		displays = converte_7seg[uh];	
		d2=0;			
		delay_ms();
		d2=1;			
		
		displays = converte_7seg[dm];
		d3=0;			
		delay_ms();
		d3=1;			
		
		displays = converte_7seg[um];
		d4=0;			
		delay_ms();
		d4=1;			
		
		displays = converte_7seg[ds];
		d5=0;			
		delay_ms();
		d5=1;			
		
		displays = converte_7seg[us];
		d6=0;			
		delay_ms();
		d6=1;			
}


char varre_teclado (void)

{
	c1=0;		
	c2=1;
	c3=1;
	
	if (l1==0)
	{
		while (l1==0) {};		//espera soltar a tecla 1
		return 1;
	}
	
	if (l2==0)
	{
		while (l2==0) {};		//espera soltar a tecla 1
		return 4;
	}

	if (l3==0)
	{
		while (l3==0) {};		//espera soltar a tecla 1
		return 7;
	}
	
	if (l4==0)
	{
		while (l4==0) {};		//espera soltar a tecla 1
		cont++;
		return 0;
	}

	c1=1;
	c2=1;
	c3=1;
	
	return 255;		//teclado vazio
}



char varre_teclado_2 (void)

{
	c1=1;		//seleciona a coluna do teclado
	c2=0;
	c3=1;
	
	if (l1==0)
	{
		while (l1==0) {};		//espera soltar a tecla 1
		return 2;
	}
	
	if (l2==0)
	{
		while (l2==0) {};		//espera soltar a tecla 1
		return 5;
	}

	if (l3==0)
	{
		while (l3==0) {};		//espera soltar a tecla 1
		return 8;
	}
	if (l4==0)
	{
		while (l4==0) {};		//espera soltar a tecla 1
		return 0;
	}

	c1=1;
	c2=1;
	c3=1;
	
	return 255;		//teclado vazio
}



char varre_teclado_3 (void)

{
	c1=1;		//seleciona a coluna do teclado
	c2=1;
	c3=0;
	
	if (l1==0)
	{
		while (l1==0) {};		//espera soltar a tecla 1
		return 3;
	}
	
	if (l2==0)
	{
		while (l2==0) {};		//espera soltar a tecla 1
		return 5;
	}

	if (l3==0)
	{
		while (l3==0) {};		//espera soltar a tecla 1
		return 9;
	}
	

	c1=1;
	c2=1;
	c3=1;
	
	return 255;		//teclado vazio
}

char varre_teclado_modo (void){
	c1=1;		//seleciona a coluna do teclado
	c2=1;
	c3=0;
	
	
	if (l4==0){
		while (l4==0) {};		//espera soltar a tecla 1
		aux++;
		return;
	}

	c1=1;
	c2=1;
	c3=1;
	
	return 255;		//teclado vazio
}

void atualiza(void){
	ms++;
	if(ms>10){
		ms=0;
		us++;
	}
	if(us>9){
		us=0;
		ds++;
	}
	if(ds>5){
		ds=0;
		um++;
	}
	if(um>9){
		um=0;
		dm++;	
	}
	if(dm>5){
		dm=0;
		uh++;
	}
	if(uh>9){
		uh++;
	}
	if(dh>=2){
		dh=0,uh=0,dm=0,um=0,ds=0,us=0;
	}
	if(dh>=1 && uh>=2){
		dh=0,uh=0,dm=0,um=0,ds=0,us=0;
	}
}

void ajusta() {
	unsigned char tecla, tecla_2, tecla_3;
	tecla=varre_teclado();
	tecla_2=varre_teclado_2();
	tecla_3=varre_teclado_3();

	switch(cont){
		case 0:
			if (tecla<10)
			{
				dh=tecla+10;
			}
			if (tecla_2<10)
			{
				dh=tecla_2+10;
			}
			if (tecla_3<10)
			{
				dh=tecla_3+10;
			}
		break;
		case 1:
			if (dh>=10){dh-=10,uh+=10;}
			if (tecla<10)
			{
				uh=tecla+10;
			}
			if (tecla_2<10)
			{
				uh=tecla_2+10;
			}
			if (tecla_3<10)
			{
				uh=tecla_3+10;
			}
		break;
		case 2:
			if (uh>=10){uh-=10,dm+=10;}
			if (tecla<10)
			{
				dm=tecla+10;
			}
			if (tecla_2<10)
			{
				dm=tecla_2+10;
			}
			if (tecla_3<10)
			{
				dm=tecla_3+10;
			}
		break;
		case 3:
			if (dm>=10){dm-=10,um+=10;}
			if (tecla<10)
			{
				um=tecla+10;
			}
			if (tecla_2<10)
			{
				um=tecla_2+10;
			}
			if (tecla_3<10)
			{
				um=tecla_3+10;
			}
		break;
		case 4:
			if (um>=10){um-=10,dh+=10;}
			cont=0;
		break;							
	}
}

void modo(void){
	if (aux==0){
		varre_teclado_modo();
		ajusta();
	}
	if (aux==1){
		if(dh>=10){dh-=10;}
		if(uh>=10){uh-=10;}
		if(dm>=10){dm-=10;}
		if(um>=10){um-=10;}
		varre_teclado_modo();
		atualiza();
		if (aux>=2){
			aux=0;
			cont=0;
			dh+=10;
		}
	}
}

void main ()

{	
	OSCCON=0b11111111;	//8MHz de clock da CPU
	ADCON1=0B00001111;	//DESABILITAS PINOS ANALÓGICOS
	TRISC=0B00000000;	//BARRAMENTO DOS DISPLAYS
	TRISD=0B11000000;	//CATODOS DOS DISPLAYS (HABILITADORES)
	TRISB=0B11111000;	//LINHAS E COLUNAS DO TECLADO

	while (1)
	{	
		varre_display();
		modo();
	}
}
