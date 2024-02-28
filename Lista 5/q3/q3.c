#include <p18f4520.h>
#pragma config OSC=INTIO67	// clock interno (oscilador) e libera pinos RA6 e RA7 como IO

#define tx PORTCbits.RC0
#define rx PORTCbits.RC1
#define z1 PORTBbits.RB7
#define z2 PORTBbits.RB6
#define z3 PORTBbits.RB5
#define z4 PORTBbits.RB4


int seg_u=0, seg_d=0, min_u=0, min_d=0, hor_u=0, hor_d=0;
int aux=0, cont=0, timer = 0;
int val_1=0, val_2=0, val_3=0, val_4=0;
int cont_1=0, cont_2=0, cont_3=0, cont_4=0;
char arr[10] = {'0','1','2','3','4','5','6','7','8','9'};

void relogio(){
	timer++;
	seg_u++;
	if(seg_u>=9){
		seg_u=0;
		seg_d++;
	}	
	if(seg_d>=5){
		seg_d=0;
		min_u++;
	}
	if(min_u>=9){
		min_u=0;
		min_d++;
	}
	if(min_d>=5){
		min_d=0;
		hor_u++;
	}
	if(hor_u>=9){
		hor_u=0;
		hor_d++;
	}
	if(hor_d>=2 && hor_d>=4){
		seg_u=0, seg_d=0, min_u=0, min_d=0, hor_u=0, hor_d=0;
	}
}

void delay_ms(int ms){
	unsigned int i;
	for(;ms>0;ms--){
		for(i=0;i<131;i++){}
	}
}

void delay_s(int s){
	int i;
	for(;s>0;s--){
		delay_ms(1001);
		for(i=0;i<60;i++){}
	}
}

void delay_1200bps (void)
{
	unsigned int i;
	for(i=0;i<108;i++) {}
}

void delay_meiobit (void)
{
	unsigned int i;
	for(i=0;i<53;i++) {}
}


void transmite_serial (char dado)
{
	int mascara = 0x01;
	unsigned int i=0;
	
	tx = 1;
	delay_1200bps ();	//repouso 	
	tx = 0;
	delay_1200bps ();	//start
	
	for (i = 0;i <=7;i++)
	{
		tx = (dado & mascara) ;
		delay_1200bps ();
		dado = dado >>1;
	}
	
	tx = 1;
	delay_1200bps();
}

void Configuracao_do_Pic ()
{

	T0CONbits.T08BIT=0;		//16 bits
	T0CONbits.PSA=0;		//COM PRESCALER
	T0CONbits.T0PS2=1;
	T0CONbits.T0PS1=1;
	T0CONbits.T0PS0=0;		//PRESCALER 1:128
	T0CONbits.T0CS=0;		//OSCILADOR INTERNO
	T0CONbits.TMR0ON=1;		//LIGA TIMER0
	TMR0H=0XC2;
	TMR0L=0XF7;				//65536-15625 = -> 1 seg

//OSC=8MHz -> clock = 2MHz -> 15625Hz (64us) 1s -> 1000000us/64us=15625

	INTCONbits.TMR0IF=0;
	INTCONbits.TMR0IE=1;
	INTCON2bits.TMR0IP=1;	
	INTCONbits.GIE=1;		//HABILITO O SISTEMA DE INTERRUP�AO DE ALTA PRIORIDADE
	

//Configura��o da dire��o dos pinos de I/O

TRISCbits.RC7=0; //lampada como saida
ADCON1 = 0B00001111; //configura todos os pinos das portas como I/O



//TRISC = 0b01111111; // configura LED como saida (RC7=0), INTERRUPTOR como entrada (RC0=1)
}

void tratamento_int_alta (void);

//____________________________________________

#pragma code vetor_alta=0x0008

void int_alta_prioridade (void)

{
	_asm GOTO tratamento_int_alta _endasm		
}

#pragma code

//____________________________________________

#pragma interrupt tratamento_int_alta

void tratamento_int_alta (void)

{
	if (INTCONbits.INT0IF)
	{
//		Odometro++;				//registra volta da roda
//		Tempo_roda = Timer0;	//registra tempo da volta da roda
//		Calcula_Velocidade (Tempo_roda);
//		Timer0=0;				//prepara timer0 para a pr�xima volta da roda		
		INTCONbits.INT0IF=0;
	}
	if (INTCONbits.TMR0IF)
	{
		TMR0H=0XC2;
		TMR0L=0XF7;				//65536-15625 -> 1 seg
		//led=~led;
		relogio();
		INTCONbits.TMR0IF=0;
	}
}



void print_zona(){
	transmite_serial('z');
	transmite_serial('o');
	transmite_serial('n');
	transmite_serial('a');
	transmite_serial(':');
}

void print_hora(){
	transmite_serial('(');
	transmite_serial(arr[hor_d]);
	transmite_serial(arr[hor_u]);
	transmite_serial(':');
	transmite_serial(arr[min_d]);
	transmite_serial(arr[min_u]);
	transmite_serial(':');
	transmite_serial(arr[seg_d]);
	transmite_serial(arr[seg_u]);
	transmite_serial(')\n');
}

void validacao(){
	if(cont_1 == 0 && z1 == 1) {
		print_zona();
		transmite_serial('1');
		transmite_serial('_');
		aux = timer + 3;		
		print_hora();
		while(timer <= aux){
			PR2 =100;
			CCPR1L = 100;
		}
		PR2 =0;
		CCPR1L = 0;
		cont_1=1;
		
	}
	if(cont_2 == 0 && z2 == 1) {
		print_zona();
		transmite_serial('2');
		transmite_serial('_');
		aux = timer + 3;		
		print_hora();
		while(timer <= aux){
			PR2 =120;
			CCPR1L = 120;
		}
		PR2 =0;
		CCPR1L = 0;
		cont_2=1;
	}
	if(cont_3 == 0 && z3 == 1) {
		print_zona();
		transmite_serial('3');
		transmite_serial('_');
		aux = timer + 3;		
		print_hora();
		while(timer <= aux){
			PR2 =140;
			CCPR1L = 140;
		}
		PR2 =0;
		CCPR1L = 0;
		cont_3=1;
	}
	if(cont_4 == 0 && z4 == 1) {
		print_zona();
		transmite_serial('4');
		transmite_serial('_');
		aux = timer + 3;		
		print_hora();
		while(timer <= aux){
			PR2 =160;
			CCPR1L = 160;
		}
		PR2 =0;
		CCPR1L = 0;
		cont_4=1;
	}
}

void sensor(){
	if(z1 == 1){
		validacao();
		cont_1=1;
	}
	if(z2 == 1){
		validacao();
		cont_2=1;
	}
	if(z3 == 1){
		validacao();
		cont_3=1;
	}
	if(z4 == 1){
		validacao();
		cont_4=1;
	}
	if(z1==0){
		cont_1=0;
	}
	if(z2==0){
		cont_2=0;
	}
	if(z3==0){
		cont_3=0;
	}
	if(z4==0){
		cont_4=0;
	}
}

main()
{

	TRISCbits.RC2 = 0;

	T2CONbits.T2CKPS1 = 1;
	T2CONbits.T2CKPS0 = 1;
	T2CONbits.TMR2ON = 1;

	PR2 = 0;
	
	CCPR1L = 0;
	CCP1CONbits.DC1B1 = 0;
	CCP1CONbits.DC1B0 = 0;
	
	CCP1CONbits.CCP1M3 = 1;
	CCP1CONbits.CCP1M2 = 1;
	CCP1CONbits.CCP1M1 = 0;
	CCP1CONbits.CCP1M0 = 0;
	
	TRISCbits.RC0 = 0;    //tx -> saida
	TRISCbits.RC1 = 1;    //rx -> entrada
	OSCCON=0b11111111;	//8MHz de clock da CPU
	ADCON1=0B00001111;	//DESABILITAS PINOS ANAL�GICOS
	TRISB=0B11111000;	//LINHAS E COLUNAS DO TECLADO
	TRISB=0B11111111;	//LINHAS E COLUNAS DO TECLADO
	Configuracao_do_Pic();
	//transmite_serial('fco');
	while(1)
	{
		sensor();
	}
}	