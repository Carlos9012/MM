#include <p18f4520.h>

void delay_varredura(void)
{
	unsigned int i;
	for(i = 0; i < 830; i++);
}

	
unsigned int *ponteiro,*ponteiro2;
unsigned int mensagem_painel[] = {
0b11111111, //<-ponteiro
0b11111111,	
0b11111111,	
0b11111111,	
0b11111111,	
0b11111111,	
0b11111111,	
0b11111111,	
0b11111111,	//<-ponteiro2
0b11111111,	
0b11111111,	
0b11111111,
0b11111111,	
0b11111111,	
0b11111111,	
0b11111111,	

0b00000001,//C
0b01111101,
0b01111101,
0b01111101,
0b01111101,
0b11111111,//espa?o
0b00000011,//A
0b11101101,
0b11101101,
0b00000001,
0b11111111,//espa?o
0b11111111,//espa?o
0b00000001,//R
0b11101101,
0b11001101,
0b10100001,
0b01111111,
0b11111111,//espa?o
0b00000001,//L
0b01111111,
0b01111111,
0b01111111,
0b11111111,//espa?o
0b11111111,//espa?o
0b00000001,//O
0b01111101,
0b01111101,
0b00000001,
0b11111111,//espa?o
0b11111111,//espa?o
0b01110011,//S
0b01101101,
0b01101101,
0b10011101,
0b11111111,//espa?o
0b11111111,//espa?o


0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,




};

void mostra_nome(void){
		unsigned int aux=1;
		unsigned char varer;
		PORTB = 0b11111111;
		PORTC = 0b11111111;
		ponteiro= &mensagem_painel[0];
		ponteiro2= &mensagem_painel[8];
		while(ponteiro2<&mensagem_painel[67]){
			if(aux==9){
        		ponteiro2=ponteiro2-7;
        		ponteiro=ponteiro-7;
        		aux=1;
    		} 
    		PORTC = *ponteiro;
    		PORTB = *ponteiro2;
    		ponteiro2=ponteiro2+1;
			ponteiro=ponteiro+1;	
			delay_varredura();
			
			if(PORTD == 0b00000000){
				varer=0b00000001;
				PORTD=varer;
			}
			else {
				varer=varer<<1;
				PORTD=varer;
				aux++;
			}
		}
}
void main(void)
{
	TRISB = 0; 		
	TRISD = 0; 
	TRISC = 0;
	ADCON1 = 0b00001111;
	while(1)
	{
		mostra_nome();
	}	
}