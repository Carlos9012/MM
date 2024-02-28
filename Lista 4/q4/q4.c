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
#define		led		PORTCbits.RC7

#define	RS			LATCbits.LATC0
#define	RW			LATCbits.LATC1
#define	EN			LATCbits.LATC2
#define	porta_lcd	LATD

#define d1 LATDbits.LATD0
#define d2 LATDbits.LATD1
#define d3 LATDbits.LATD2
#define d4 LATDbits.LATD3
#define d5 LATDbits.LATD4
#define d6 LATDbits.LATD5



char cont = 0;
char cont_2 = 0;
char aux = -1;
char numero = 0;
int val = 0, x;
char arr[10] = {'_','_','_','_','_','_','_','_','_','_'};
char arr_2[10] = {'4','0','0','2','8','9','2','2','_','_'};

void delay_s (void){
	unsigned long int i;
	for(i=0;i<900;i++){}
}

void delay_ms(void){
	unsigned int i;
	for(i=0;i<90;i++){}
}

void envia_comando_lcd (unsigned char comando){
	RS=0;
	RW=0;
	EN=0;
	EN=1;
	porta_lcd = comando;
	EN=0;
	delay_ms();
}

void envia_dado_lcd (unsigned char dado){
	RS=1;
	RW=0;
	EN=0;
	porta_lcd = dado;
	EN=1;
	EN=0;
	delay_ms();
}

void inicializa_lcd (void){
	delay_s();
	envia_comando_lcd (0b00111000);
	envia_comando_lcd (0b00001110);
	envia_comando_lcd (0b00000001);
}

void delay_us(void){
	unsigned int i;
	for(i=0;i<900;i++){}
}

void varre_display(void)
{
		delay_us();
}

void validacao(){
	int x;
	val = 0;
	for(x=0;x<=10;x++){
		if(arr[x] == arr_2[x]){
			val++;
		}
	}
	if(val == 10){
		led = 1;
	}
	else{
		led=0;
	}
}

void apagar(){
	envia_comando_lcd(0b00000001);
	cont=0;
	cont_2=-1;
	aux = -1;
}

/*void delet(){
cont = 0;
cont_2 = 0;
aux = -1;
numero = 0;

}*/

char varre_teclado (void)

{
	c1=0;		
	c2=1;
	c3=1;
	
	if (l1==0)
	{
		while (l1==0) {};		//espera soltar a tecla 1
		numero = '1';
		aux++;
		cont_2++;
		return;

	}
	
	if (l2==0)
	{
		while (l2==0) {};		//espera soltar a tecla 1
		numero = '4';
		aux++;
		cont_2++;
		return;
	}

	if (l3==0)
	{
		while (l3==0) {};		//espera soltar a tecla 1
		numero = '7';
		aux++;
		cont_2++;
		return;
	}
	
	if (l4==0)
	{
		while (l4==0) {};		//espera soltar a tecla 1
		apagar();
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
		numero = '2';
		aux++;
		cont_2++;
		return;
	}
	
	if (l2==0)
	{
		while (l2==0) {};		//espera soltar a tecla 1
		numero = '5';
		aux++;
		cont_2++;
		return;
	}

	if (l3==0)
	{
		while (l3==0) {};		//espera soltar a tecla 1
		numero = '8';
		aux++;
		cont_2++;
		return;
	}
	if (l4==0)
	{
		while (l4==0) {};		//espera soltar a tecla 1
		numero = '0';
		aux++;
		cont_2++;
		return;
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
		numero = '3';
		aux++;
		cont_2++;
		return;
	}
	
	if (l2==0)
	{
		while (l2==0) {};		//espera soltar a tecla 1
		numero = '5';
		aux++;
		cont_2++;
		return;
	}

	if (l3==0)
	{
		while (l3==0) {};		//espera soltar a tecla 1
		numero = '9';
		aux++;
		cont_2++;
		return;
	}
	if (l4==0)
	{
		while (l4==0) {};		//espera soltar a tecla 1
		validacao();
		return;
	}
	

	c1=1;
	c2=1;
	c3=1;
	
	return 255;		//teclado vazio
}




void ajusta() {
	unsigned char tecla, tecla_2, tecla_3;
	tecla=varre_teclado();
	tecla_2=varre_teclado_2();
	tecla_3=varre_teclado_3();

	if (tecla<10)
	{
		numero=tecla;
	}
	if (tecla_2<10)
	{
		numero=tecla_2;
	}
	if (tecla_3<10)
	{
		numero=tecla_3;
	}
	arr[aux] = numero;

}

void print_display(){
	if(cont_2 == cont && cont_2 <= 24){
		envia_dado_lcd('*');
		cont+=2;
		cont_2++;
	}
}



void main ()

{	
	OSCCON=0b11111111;	//8MHz de clock da CPU
	ADCON1=0B00001111;	//DESABILITAS PINOS ANALÓGICOS
	TRISB=0B11111000;	//LINHAS E COLUNAS DO TECLADO
	TRISD = 0b00000000;
	TRISC = 0b00000000;
	led=0;
	cont_2-=1;
	inicializa_lcd();
	while (1)
	{	
		varre_display();
		ajusta();
		print_display();
	}
}