#include <p18f4520.h>

#define E LATCbits.LATC2
#define RW LATCbits.LATC1
#define lcd LATD
#define RS LATCbits.LATC0

void delay_s (void){
	unsigned long int i;
	for(i=0;i<9000;i++){}
}

void delay_ms(void){
	unsigned int i;
	for(i=0;i<90;i++){}
}


void envia_dado_lcd(unsigned char dado) {
	RS = 1; 
	E = 1;
	RW = 0;
	lcd = dado;
	E = 0;
	delay_ms();
}

void envia_comando_lcd (unsigned char comando) {
	RS = 0; 
	E = 1;
	RW = 0;
	lcd = comando;
	RW = 0;
	E = 0;
	delay_ms();
}

void inicializa_lcd(void){
	envia_comando_lcd (0b00111000); 
	envia_comando_lcd (0b00001100); 
	envia_comando_lcd (0b00000001);	
}


void pic(void) {
	ADCON0bits.ADON=1;  
	ADCON1bits.PCFG3=1;
	ADCON1bits.PCFG2=1;
	ADCON1bits.PCFG1=0;
	ADCON1bits.PCFG0=1; 
	ADCON1bits.VCFG1=0; 
	ADCON1bits.VCFG0=0; 
	ADCON2=0b10111100; 			
	TRISC = 0x00;
	delay_s(); 
	inicializa_lcd();

}

char sinal1[12] = {'S', 'i', 'n', 'a', 'l','_', '1', ':', '0',',','0','0'};
char sinal2[12] = {'S', 'i', 'n', 'a', 'l','_', '2', ':', '0', ',', '0', '0'};
int i = 0;
int b = 0;
void enviar_lcd(void) {
	delay_s(); 
	envia_comando_lcd (0x80);
	for(i = 0; i < 12; i++){
		envia_dado_lcd(sinal1[i]);
	}
	envia_comando_lcd (0xC0);
	
	for(b = 0; b < 13; b++){
		envia_dado_lcd(sinal2[b]);
	}

}

int p1, p2, p3, p4 = -2;
int ddp;
void medir(void) {
	float taxa = 0.0048828125;
	float resultado = ddp*taxa;
	int partes = resultado * 100;
	p1=resultado; partes %= 100;
	p2=partes/10; partes %= 10;
	p3=partes;	
	if(ADCON0bits.CHS0){ 
		envia_comando_lcd (0x88);
	}else{
		envia_comando_lcd (0xC8);
	}

	envia_dado_lcd(p1+48); 
	envia_dado_lcd(','); 
	envia_dado_lcd(p2+48); 
	envia_dado_lcd(p3+48);
}

void main() {
	TRISD = 0x00;	
	pic(); 
	enviar_lcd();
	while(1){  
		ADCON0bits.CHS3=0;
		ADCON0bits.CHS2=0;
		ADCON0bits.CHS1=0;
		ADCON0bits.CHS0=0; 		
		ADCON0bits.GO=1;
		while(ADCON0bits.GO==1){}; 	
		ddp = (ADRESH*256)+ADRESL;
		medir();
		ADCON0bits.CHS3=0;
		ADCON0bits.CHS2=0;
		ADCON0bits.CHS1=0;
		ADCON0bits.CHS0=1; 
		ADCON0bits.GO=1; 	
		while(ADCON0bits.GO==1){}; 	
		ddp = (ADRESH*256)+ADRESL;
		medir();
	}
}