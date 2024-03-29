#include <p18f4520.h>

#pragma config OSC = INTIO67 // clock interno (oscilador) e libera pinos RA6 e RA7 como IO
#define displays LATC

#define	RS			LATCbits.LATC0
#define	RW			LATCbits.LATC1
#define	EN			LATCbits.LATC2
#define	porta_lcd	LATD


int timer = 0;
int odometro = 0;
int rotacao = 0;
int uni=0,dez=0,cen=0,mil=0,dez_m=0,cen_m=0;
int rpm_u=0, rpm_d=0, rpm_c=0, rpm_m=0;
int vel_u=0, vel_d=0, vel_c=0;
int long rpm =0,vel = 0;
char arr[10] = {'0','1','2','3','4','5','6','7','8','9'};


void delay_s(void) {
    unsigned long int i;
    for (i = 0; i < 90; i++) {}
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
}


void calcula_rpm() {
    rpm = rotacao * 60 / timer;
	rotacao = 0;
	timer = 0;
}

void calcular_velocidade() {
    float velocidade_m_s = (0.35 * 2 * 3.14 * rotacao ) / (timer); // Calcula a velocidade em metros por segundo (m/s)
	vel = velocidade_m_s * 3.6; // Converte a velocidade de m/s para km/h	
}



void print_display(){
	envia_comando_lcd(0x87);
    envia_dado_lcd('M');
	envia_comando_lcd(0x86);
    envia_dado_lcd('K');
	envia_comando_lcd(0x85);
    envia_dado_lcd(arr[uni]); 
	envia_comando_lcd(0x84);
    envia_dado_lcd(arr[dez]); 
	envia_comando_lcd(0x83);
    envia_dado_lcd(arr[cen]);
	envia_comando_lcd(0x82);
    envia_dado_lcd(arr[mil]); 
	envia_comando_lcd(0x81);
    envia_dado_lcd(arr[dez_m]); 
	envia_comando_lcd(0x80);
    envia_dado_lcd(arr[cen_m]);
	envia_comando_lcd(0xc0);
    envia_dado_lcd(arr[rpm_m]);	
	envia_dado_lcd(arr[rpm_c]);	
	envia_dado_lcd(arr[rpm_d]);	
	envia_dado_lcd(arr[rpm_u]);
    envia_dado_lcd('R');
    envia_dado_lcd('P');
    envia_dado_lcd('M');
	envia_dado_lcd('-');
	envia_dado_lcd(arr[vel_c]);	
	envia_dado_lcd(arr[vel_d]);	
	envia_dado_lcd(arr[vel_u]);
    envia_dado_lcd('K');
    envia_dado_lcd('M');
    envia_dado_lcd('/');
    envia_dado_lcd('H');	

}

void odometro_display(){
	unsigned int long cont;
	cont = odometro;
	cen_m = cont/100000;
	dez_m = cont/10000 - cen_m*10;
	mil = cont/1000 - dez_m*10 - cen_m*100;
	cen = cont/100 - mil*10 - dez_m*100 - cen_m*1000;
	dez = cont/10 - cen*10 - mil*100 - dez_m*1000 - cen_m*10000;
	uni = cont%10;
}

void rpm_display(){
	unsigned int long aux;
	aux = rpm;
	rpm_m = aux/1000;
	rpm_c = aux/100 - rpm_m*10;
	rpm_d = aux/10 - rpm_c*10 - rpm_m*100;
	rpm_u = aux%10;
}

void vel_display(){
	unsigned int long aux;
	aux = vel;
	vel_c = aux/100;
	vel_d = aux/10 - vel_c *10;
	vel_u = aux%10;
}

void Configuracao_do_Pic() {
    T0CONbits.T08BIT = 0;    //16 bits
    T0CONbits.PSA = 0;       //COM PRESCALER
    T0CONbits.T0PS2 = 1;
    T0CONbits.T0PS1 = 1;
    T0CONbits.T0PS0 = 0;    //PRESCALER 1:128
    T0CONbits.T0CS = 0;     //OSCILADOR INTERNO
    T0CONbits.TMR0ON = 1;    //LIGA TIMER0
    TMR0H = 0XC2;
    TMR0L = 0XF7;           //65536-15625 = -> 1 seg

    //OSC=8MHz -> clock = 2MHz -> 15625Hz (64us) 1s -> 1000000us/64us=15625
    INTCONbits.INT0IE = 1;  // Habilita a interrupção externa INT0
    INTCON2bits.INTEDG0 = 1; // Configura a borda de detecção como borda de subida
    INTCON3bits.INT1E = 1;   // Habilita a interrupção externa INT1
    INTCON2bits.INTEDG1 = 1; // Configura a borda de detecção como borda de subida
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    INTCON2bits.TMR0IP = 1;
    INTCONbits.GIE = 1;     //HABILITO O SISTEMA DE INTERRUPÇAO DE ALTA PRIORIDADE

    //Configuração da direção dos pinos de I/O
    TRISCbits.RC7 = 0; //lampada como saida
    ADCON1 = 0B00001111; //configura todos os pinos das portas como I/O

    TRISBbits.RB0 = 1; // Configura o pino RB0 como entrada para a interrupção externa INT0
    TRISBbits.RB1 = 1; // Configura o pino RB1 como entrada para a interrupção externa INT1
}

void tratamento_int_alta(void);

//____________________________________________

#pragma code vetor_alta = 0x0008

void int_alta_prioridade(void) {
    _asm GOTO tratamento_int_alta _endasm
}

#pragma code

//____________________________________________

#pragma interrupt tratamento_int_alta

void tratamento_int_alta(void) {
    if (INTCONbits.INT0IF) {
        odometro++;             //registra volta da roda
        INTCONbits.INT0IF = 0;  // Rearma a flag de interrupção externa INT0
    }
    if (INTCON3bits.INT1IF) {
        rotacao++;
        //registra volta da roda
        INTCON3bits.INT1IF = 0;  // Rearma a flag de interrupção externa INT1
    }
    if (INTCONbits.TMR0IF) {
        TMR0H = 0XC2;
        TMR0L = 0XF7;           //65536-15625 -> 1 seg
        timer++;
		calcular_velocidade();
		odometro_display();
		calcula_rpm();
        INTCONbits.TMR0IF = 0;
    }
}

void main() {
    OSCCON = 0b11111111;    //8MHz de clock da CPU
    ADCON1 = 0B00001111;    //DESABILITA PINOS ANALÓGICOS
    TRISC = 0B00000000;     //BARRAMENTO DOS DISPLAYS
    TRISD = 0B00000000;     //CATODOS DOS DISPLAYS (HABILITADORES)
    TRISB = 0B11111111;     //LINHAS E COLUNAS DO TECLADO
    Configuracao_do_Pic();
	inicializa_lcd();
    while (1) {
		print_display();
		vel_display();
		rpm_display();
    }
}
