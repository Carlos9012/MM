#include <p18f4520.h>
#define _XTAL_FREQ 8000000

#define RS LATCbits.LATC0
#define EN LATCbits.LATC1
#define D4 LATCbits.LATC4
#define D5 LATCbits.LATC5
#define D6 LATCbits.LATC6
#define D7 LATCbits.LATC7

#define RS_ LATBbits.LATB0
#define EN_ LATBbits.LATB1
#define D4_ LATBbits.LATB4
#define D5_ LATBbits.LATB5
#define D6_ LATBbits.LATB6
#define D7_ LATBbits.LATB7

// Fun??es para controle do LCD

void delay_s (void){
	unsigned long int i;
	for(i=0;i<900;i++){}
}

void delay_ms(void){
	unsigned int i;
	for(i=0;i<90;i++){}
}

void Lcd_Command(unsigned char cmd) {
    RS = 0; // Selecionar modo de comando
    EN = 1; // Habilitar o LCD
    
    // Enviar primeiro nibble
    D4 = (cmd >> 4) & 0x01;
    D5 = (cmd >> 5) & 0x01;
    D6 = (cmd >> 6) & 0x01;
    D7 = (cmd >> 7) & 0x01;
    
    EN = 0; // Desabilitar o LCD
    
   	delay_s();
    
    EN = 1; // Habilitar o LCD
    
    // Enviar segundo nibble
    D4 = (cmd >> 0) & 0x01;
    D5 = (cmd >> 1) & 0x01;
    D6 = (cmd >> 2) & 0x01;
    D7 = (cmd >> 3) & 0x01;
    
    EN = 0; // Desabilitar o LCD
    
    delay_ms();
}


void Lcd_Init() {
    // Configurar pinos como sa?da
    
    // Inicializar o LCD em 4 bits
    Lcd_Command(0x02); // Inicializa??o em 4 bits
    Lcd_Command(0x28); // Configurar interface para 2 linhas e 5x7 fonte
    Lcd_Command(0x0C); // Display on, cursor off
    Lcd_Command(0x06); // Incremento autom?tico do cursor
    Lcd_Command(0x01); // Limpar o display
}



void Lcd_Set_Cursor(unsigned char row, unsigned char col) {
    unsigned char address;
    // Calcular endere?o baseado na posi??o da linha e coluna
    if (row == 1) {
        address = 0x80 + col - 1;
    } else if (row == 2) {
        address = 0xC0 + col - 1;
    }
    Lcd_Command(address); // Posicionar o cursor
}

void Lcd_Write_Char(char c) {
    RS = 1; // Selecionar modo de dados
    EN = 1; // Habilitar o LCD
    
    // Enviar primeiro nibble
    D4 = (c >> 4) & 0x01;
    D5 = (c >> 5) & 0x01;
    D6 = (c >> 6) & 0x01;
    D7 = (c >> 7) & 0x01;
    
    EN = 0; // Desabilitar o LCD
    
    delay_ms();
    
    EN = 1; // Habilitar o LCD
    
    // Enviar segundo nibble
    D4 = (c >> 0) & 0x01;
    D5 = (c >> 1) & 0x01;
    D6 = (c >> 2) & 0x01;
    D7 = (c >> 3) & 0x01;
    
    EN = 0; // Desabilitar o LCD
    
   delay_ms();
}

void Lcd_Command_2(unsigned char cmd) {
    RS_ = 0; // Selecionar modo de comando
    EN_ = 1; // Habilitar o LCD
    
    // Enviar primeiro nibble
    D4_ = (cmd >> 4) & 0x01;
    D5_ = (cmd >> 5) & 0x01;
    D6_ = (cmd >> 6) & 0x01;
    D7_ = (cmd >> 7) & 0x01;
    
    EN_ = 0; // Desabilitar o LCD
    
   	delay_s();
    
    EN_ = 1; // Habilitar o LCD
    
    // Enviar segundo nibble
    D4_ = (cmd >> 0) & 0x01;
    D5_ = (cmd >> 1) & 0x01;
    D6_ = (cmd >> 2) & 0x01;
    D7_ = (cmd >> 3) & 0x01;
    
    EN_ = 0; // Desabilitar o LCD
    
    delay_ms();
}


void Lcd_Init_2() {
    Lcd_Command_2(0x02); // Inicializa  o em 4 bits
    Lcd_Command_2(0x28); // Configurar interface para 2 linhas e 5x7 fonte
    Lcd_Command_2(0x0C); // Display on, cursor off
    Lcd_Command_2(0x06); // Incremento autom tico do cursor
    Lcd_Command_2(0x01); // Limpar o display
}



void Lcd_Set_Cursor_2(unsigned char row, unsigned char col) {
    unsigned char address;
    if (row == 1) {
        address = 0x80 + col - 1;
    } else if (row == 2) {
        address = 0xC0 + col - 1;
    }
    Lcd_Command_2(address); 
}

void Lcd_Write_Char_2(char c) {
    RS_ = 1;
    EN_ = 1; 

    D4_ = (c >> 4) & 0x01;
    D5_ = (c >> 5) & 0x01;
    D6_ = (c >> 6) & 0x01;
    D7_ = (c >> 7) & 0x01;

	EN_ = 0;
    
    delay_ms();
    
    EN_ = 1;
    D4_ = (c >> 0) & 0x01;
    D5_ = (c >> 1) & 0x01;
    D6_ = (c >> 2) & 0x01;
    D7_ = (c >> 3) & 0x01;
    
    EN_ = 0;
    
   delay_ms();
}




void main (){
    
    TRISC = 0x00;
	TRISB = 0x00;
    Lcd_Init();
	Lcd_Init_2();
    
    while (1) {
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_Char('N');
        Lcd_Write_Char('i');
        Lcd_Write_Char('g');
        Lcd_Write_Char('t');
        Lcd_Write_Char('h');
        delay_ms();
		Lcd_Set_Cursor_2(1, 1);
        Lcd_Write_Char_2('N');
        Lcd_Write_Char_2('o');
        Lcd_Write_Char_2('i');
        Lcd_Write_Char_2('t');
        Lcd_Write_Char_2('e');
		delay_ms();
    }
    
}
