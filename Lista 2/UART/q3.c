#include <p18f4520.h>

#define tx PORTCbits.RC0 // seto a porta RC0 como tx
#define rx PORTCbits.RC1 // seto a porta RC1 como rx

void delay_833_us(){ // delay do tempo de 1 bit
	int i = 0;
	for(i; i<82; i++){
		char j = 0;	
	}
}

void delay_meiobit(){ // delay do tempo de meio bit
	int i = 0;
	for(i; i<40; i++){
		char j = 0;	
	}
}

void transmissor_receptor_serial(){
	int i = 0;
	tx = 1;          // repouso
	delay_833_us();
	while(rx){}      // espera start do rx
	delay_meiobit();
	tx = 0;          // start
	delay_833_us();

	// valor transmitido pelo terminal vai sendo enviado para o rx do terminal
	tx =rx;
	delay_833_us();
	tx =rx;
	delay_833_us();
	tx =rx;
	delay_833_us();
	tx =rx;
	delay_833_us();
	tx =rx;
	delay_833_us();
	tx =rx;
	delay_833_us();
	tx =rx;
	delay_833_us();
	tx =rx;
	delay_833_us();

	tx = 1; // stop bit
	delay_833_us();
}


main(){
	TRISCbits.RC0 = 0; // tx -> saida
	TRISCbits.RC1 = 1; // rx -> entrada

	while(1){
		transmissor_receptor_serial(); // chamada a fun??o que transmite dados do terminal para ele mesmo
	}
}