#include <p18f4520.h>
#define _XTAL_FREQ 8000000

#define RS LATCbits.LATC0
#define EN LATCbits.LATC1
#define D4 LATCbits.LATC4
#define D5 LATCbits.LATC5
#define D6 LATCbits.LATC6
#define D7 LATCbits.LATC7

// Funções para controle do LCD

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
    // Configurar pinos como saída
    
    // Inicializar o LCD em 4 bits
    Lcd_Command(0x02); // Inicialização em 4 bits
    Lcd_Command(0x28); // Configurar interface para 2 linhas e 5x7 fonte
    Lcd_Command(0x0C); // Display on, cursor off
    Lcd_Command(0x06); // Incremento automático do cursor
    Lcd_Command(0x01); // Limpar o display
}



void Lcd_Set_Cursor(unsigned char row, unsigned char col) {
    unsigned char address;
    // Calcular endereço baseado na posição da linha e coluna
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

void Lcd_Write_String(const char* str) {
    while (*str) {
        Lcd_Write_Char(*str++);
    }
}

void Lcd_Shift_Esquerda() {
    Lcd_Command(0x18); // Deslocar o display para a esquerda
}

void Lcd_Shift_Direita() {
    Lcd_Command(0x1C); // Deslocar o display para a direita
}


void Lcd_Clear() {
    Lcd_Command(0x01); // Limpar o display
}

void main (){
    unsigned char a;
    
    TRISC = 0x00;
    Lcd_Init();
    
    while (1) {
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_Char('C');
        Lcd_Write_Char('a');
        Lcd_Write_Char('r');
        Lcd_Write_Char('l');
        Lcd_Write_Char('o');
        Lcd_Write_Char('s');
        delay_ms();
    }
    
}
