#include <p18f4520.h>

#define	RS			LATCbits.LATC0
#define	RW			LATCbits.LATC1
#define	EN			LATCbits.LATC2
#define	porta_lcd	LATD

void delay_s(void) {
    unsigned long int i;
    for (i = 0; i < 9000; i++) {}
}

void delay_ms(void) {
    unsigned int i;
    for (i = 0; i < 900; i++) {}
}

void envia_comando_lcd(unsigned char comando) {
    RS = 0;
    RW = 0;
    EN = 0;
    EN = 1;
    porta_lcd = comando;
    EN = 0;
    delay_ms();
}

void envia_dado_lcd(unsigned char dado) {
    RS = 1;
    RW = 0;
    EN = 0;
    porta_lcd = dado;
    EN = 1;
    EN = 0;
    delay_ms();
}

void inicializa_lcd(void) {
    delay_s();
    envia_comando_lcd(0b00111000);
    envia_comando_lcd(0b00001110);
    envia_comando_lcd(0b00000001);
}

void define_caracteres_personalizados(void) {
    envia_comando_lcd(0x40);

    envia_dado_lcd(0b01110);
    envia_dado_lcd(0b10001);
    envia_dado_lcd(0b10001);
    envia_dado_lcd(0b10001);
    envia_dado_lcd(0b10001);
    envia_dado_lcd(0b10001);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);
    
    envia_dado_lcd(0b01110);
    envia_dado_lcd(0b10001);
    envia_dado_lcd(0b10001);
    envia_dado_lcd(0b10001);
    envia_dado_lcd(0b10001);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);
    
    envia_dado_lcd(0b01110);
    envia_dado_lcd(0b10001);
    envia_dado_lcd(0b10001);
    envia_dado_lcd(0b10001);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);

	envia_dado_lcd(0b01110);
    envia_dado_lcd(0b10001);
    envia_dado_lcd(0b10001);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);

	envia_dado_lcd(0b01110);
    envia_dado_lcd(0b10001);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);

	envia_dado_lcd(0b01110);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);
    envia_dado_lcd(0b11111);
}

void main() {
    TRISD = 0b00000000;
    TRISC = 0b00000000;
    inicializa_lcd();
    define_caracteres_personalizados();
    
    while (1) {
        envia_comando_lcd(0x80);
        envia_dado_lcd(0x00);  
		delay_s();
        envia_comando_lcd(0x80);
        envia_dado_lcd(0x01); 
		delay_s();
        envia_comando_lcd(0x80);
        envia_dado_lcd(0x02); 
		delay_s();
		envia_comando_lcd(0x80);
        envia_dado_lcd(0x03);
		delay_s();
		envia_comando_lcd(0x80);
        envia_dado_lcd(0x04);
		delay_s();
		envia_comando_lcd(0x80);
        envia_dado_lcd(0x05);
 		delay_s();
		envia_comando_lcd(0x80);
        envia_dado_lcd(0x06);
 		delay_s();
    }
}