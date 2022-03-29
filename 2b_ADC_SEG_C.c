#include <REG51.h>
#include <stdio.h>

unsigned char NUMB _at_ 0x70;

code unsigned char table[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92};

sbit ADC_WR = P3^6;
sbit ADC_RD = P3^7;
sbit dac_write = P0^7;

// ROM - Stored in table
// 11000000B	: 0
// 11111001B	: 1
// 10100100B	: 2
// 10110000B	: 3
// 10011001B	: 4



void int0(void) interrupt 0 using 3
{
	ADC_RD = 0; // enable ADC read
	NUMB = P2; // read data from ADC and write into RAM address 70H
	ADC_RD = 1; // disable ADC read
	ADC_WR = 0; // enable ADC write
	ADC_WR = 1; // disable ADC write
	
	// Variable val is compared with the voltage levels,
	// 0V - 0.99V ===> 0 in 7 segment LEDs
	// 1V - 1.99V  ===> 1 in 7 segment LEDs
	// 2V - 2.99V ===> 2 in 7 segment LEDs
	// 3V - 3.99V ===> 3 in 7 segment LEDs
	// 4V - 4.99V ===> 4 in 7 segment LEDs
	// greater than 4.99 ===> 5 in 7 segment LEDs
	
	
	if(NUMB >= 0 && NUMB <= 51){
		P1 = table[0];
	}
	else if(NUMB >= 52 && NUMB <= 102){
		P1 = table[1];
	}
	if(NUMB >= 103 && NUMB <= 153){
		P1 = table[2];
	}
	else if(NUMB >= 154 && NUMB <= 204) {
		P1 = table[3];
	}
	else if(NUMB >= 205 && NUMB <= 254){
		P1 = table[4];
	}
	else if(NUMB > 254){
		P1 = table[5];
	}
	
}
void main(void)
{
	TCON = 1; //  entering INT0 edge mode
	IE = 0x81; // INT0 is enabled
	ADC_WR = 0; //  ADC write is enabled
	ADC_WR = 1; //  ADC write is disabled
	while (1);
}