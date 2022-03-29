#include <REG51.h>
#include <stdio.h>

unsigned char NUMB _at_ 0x70;

sbit ADC_WR = P3^6;
sbit ADC_RD = P3^7;

 // 8 leds for outut
sbit led0 = P1^0;
sbit led1 = P1^1;
sbit led2 = P1^2;
sbit led3 = P1^3;
sbit led4 = P1^4;
sbit led5 = P1^5;
sbit led6 = P1^6;
sbit led7 = P1^7;

void int0(void) interrupt 0 using 3
{
	ADC_RD = 0; // ADC read id enabled here
	NUMB = P2; // copying data into RAM address 70H
	ADC_RD = 1; //  ADC read is disabled
	ADC_WR = 0; //  ADC write is enabled
	ADC_WR = 1; //  ADC write is disabled
	
	// The NUMBer in NUMB variable is checked individually with the 8 divided levels (0V to 5V ) and shows the led lvl
	
	if(NUMB < 32){	
		led0 = 0;
		led1 = 1;
		led2 = 1;
		led3 = 1;
		led4 = 1;
		led5 = 1;
		led6 = 1;
		led7 = 1;
	}
	else if(NUMB < 64){
		led0 = 0;
		led1 = 0;
		led2 = 1;
		led3 = 1;
		led4 = 1;
		led5 = 1;
		led6 = 1;
		led7 = 1;
	}
	else if(NUMB < 96){
		led0 = 0;
		led1 = 0;
		led2 = 0;
		led3 = 1;
		led4 = 1;
		led5 = 1;
		led6 = 1;
		led7 = 1;
	}
	else if(NUMB < 128){
		led0 = 0;
		led1 = 0;
		led2 = 0;
		led3 = 0;
		led4 = 1;
		led5 = 1;
		led6 = 1;
		led7 = 1;
	}
	else if(NUMB < 160){
		led0 = 0;
		led1 = 0;
		led2 = 0;
		led3 = 0;
		led4 = 0;
		led5 = 1;
		led6 = 1;
		led7 = 1;
	}
	
	else if(NUMB < 192){
		led0 = 0;
		led1 = 0;
		led2 = 0;
		led3 = 0;
		led4 = 0;
		led5 = 0;
		led6 = 1;
		led7 = 1;
	}
	else if(NUMB < 224){
		led0 = 0;
		led1 = 0;
		led2 = 0;
		led3 = 0;
		led4 = 0;
		led5 = 0;
		led6 = 0;
		led7 = 1;
	}
	else if(NUMB < 256){
		led0 = 0;
		led1 = 0;
		led2 = 0;
		led3 = 0;
		led4 = 0;
		led5 = 0;
		led6 = 0;
		led7 = 0;
	}
	else{
		led0 = 1;
		led1 = 1;
		led2 = 1;
		led3 = 1;
		led4 = 1;
		led5 = 1;
		led6 = 1;
		led7 = 1;
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