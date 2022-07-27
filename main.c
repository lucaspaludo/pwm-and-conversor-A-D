#include <avr/io.h>
#include <avr/interrupt.h>

int NUM[7] = {63,6,91,79,102,109,125}; //criação do vetor com números que serão mostrados no display

ISR(ADC_vect){ //interrupção pelo conversor A/D
	
	if(ADCW>=0 && ADCW<102){ //tensão entre 0 e 0,5 -> número 0 no display
		PORTD = NUM[0];
	}
	
	if(ADCW>=102 && ADCW<307){ //tensão entre 0,5 e 1,5 -> número 1 no display
		PORTD = NUM[1];
	}
		
	if(ADCW>=307 && ADCW<512){ //tensão entre 1,5 e 2,5 -> número 2 no display
		PORTD = NUM[2];
	}
	
	if(ADCW>=512 && ADCW<717){ //tensão entre 2,5 e 3,5 -> número 3 no display
		PORTD = NUM[3];
	}
		
	if(ADCW>=717 && ADCW<922){ //tensão entre 3,5 e 4,5 -> número 4 no display
		PORTD = NUM[4];
	}
		
	if(ADCW>=922 && ADCW<=1024){ //tensão entre 4,5 e 5 -> número 5 no display
		PORTD = NUM[5];
	}
	
	ADCSRA|=0b01000000; // inicia nova conversão
	
}


int main(void)
{
	/*----------------SAÍDAS------------------*/
	DDRD = 0b11111111;			 //saída display 7 segmentos
	DDRB |= (1<<PB1);			 //define pino OC1A (PB1) como saída
	/*----------------------------------------*/
	
	/*----------------PWM---------------------*/
	//CONFIGURAÇÃO DOS REGISTRADORES PWM
	TCCR1A = 0b10000010;		 //define modo de operação PWM rápido (WGM11, WGM12, WGM13, COM1A1)				 //define prescaler de 1
	TCCR1B = 0b00011001;		 //topo em ICR1 e atualização do OCR1A na base
	ICR1 = 999;					 //divide o clock por 10000 (ICR1+1) para PWM de 1Khz
	OCR1A = 0;					 //ajusta o PWM inicial para 100% -> tensão média no led equivalente a tensão na saída do potenciômetro
	/*----------------------------------------*/	
	
	/*--------------CONVERSOR A/D-------------*/
	//CONFIGURAÇÃO DOS REGISTRADORES DO CONVERSOR A/D
	ADMUX = 0b01000000;			  //define entrada ADC0 do conversor A/D com referência no pino AVCC
	ADCSRA = 0b11001111;		  //define prescaler de 128, habilita a interrupção pelo conversor A/D, inicia a conversão e habilita o conversor A/D
	/*----------------------------------------*/
	
	sei(); //ativa todas as interrupções
	
	
    while (1) 
    {
		
	}
}

