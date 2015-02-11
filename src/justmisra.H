/*
 * justmisra.h
 *
 *  Created on: Oct 28, 2014
 *      Author: Indrajit Paul, Bachelor of Electronics & Instrumentation Engineer.
 */
#ifndef MSP430_H_
#define MSP430_H_
#include <msp430f5527.h>
#define M1_A  BIT4
#define M1_B  BIT5
#define M2_A  BIT6
#define M2_B  BIT7
#define S1    BIT0
#define S2    BIT1
#define tft_cs1 BIT2
#define tft_cs2 BIT3
#define tft_RST BIT4
#define tft_RW  BIT5
#define tft_RS  BIT6
#define tft_EN  BIT7
#define tft_data P4DIR
#define tft_driveA  BIT2
#define tft_driveB  BIT3
#define switch1  BIT4
void motor_Init(void);
void Delay(unsigned int tic);
void Glcd_Init(void);
void tft_Set_ADC_Threshold(unsigned int threshold);
void DCM_Forward(void);
void DCM_Back(void);
void DCM_Left(void);
void DCM_Right(void);
void DCM_Stop(void);
void ADC12_Init1(void);
void GLCD_COL(unsigned int x);
void GLCD_ROW(unsigned int y);
void GLCD_ON(void);
void Enable_Pulse(void);
void GLCD_Write(unsigned char* b);
void GLCD_Read(unsigned short column);
void GLCD_XY(unsigned int x,unsigned int y);
void Set_Start_Line(unsigned short line);
void tft_Init(unsigned int display_width, unsigned int display_height);
void Glcd_Set_Side(unsigned short x_pos);
void GLCD_Rectangle(unsigned int a1, unsigned int b1, unsigned int c1 ,unsigned int d1);
void GLCD_Box(unsigned int a1, unsigned int b1, unsigned int c1 ,unsigned int d1);
#endif
void motor_Init(void)
{
	P1DIR |= M1_A;
	    P1OUT = 0x10;
	    P1DIR |= M1_B;
	    P1OUT = 0x20;
	    P1DIR |= M2_A;
	    P1OUT = 0x40;
	    P1DIR |= M2_B;
	    P1OUT = 0x80;
	    P2DIR &= S1;
	        P2IN = 0xFE;
	        P2DIR &= S2;
	        P2IN =0xFD;
}
void Glcd_Init(void)
{
	    P3DIR |= tft_cs1;
	    P3OUT = 0x00;
	    P3DIR |= tft_cs2;
	    P3OUT = 0x00;
	    P3DIR |= tft_RST;
	    P3OUT = 0x00;
	    P3DIR |= tft_RW;
	    P3OUT = 0x00;
	    P3DIR |= tft_RS;
	    P3OUT = 0x00;
	    P3DIR |= tft_EN;
	    P3OUT = 0x00;
	    P4DIR = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7 ;
	    P4OUT= 0x00;
	    P2DIR |= tft_driveA;
	    P2OUT = 0x00;
	    P2DIR |= tft_driveB;
	    P2OUT = 0x00;
}
void Enable_Pulse() {
P3DIR |= BIT7;
P3OUT = 0x80;
Delay(1000);
P3DIR |= BIT7;
P3OUT = 0;
Delay(1000);
}
void GLCD_ON(void) {
	P3DIR |= BIT2;
P3OUT = 0;
P3DIR |= BIT3;
P3OUT = 0;
P3DIR |= BIT6;
P3OUT = 0;
P3DIR |= BIT5;
P3OUT = 0;
P4DIR = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7 ;
P4OUT = 0x3F;
Enable_Pulse();
}
void Set_Start_Line(unsigned short line)
{
	P3DIR |= BIT6;
P3OUT = 0;
P3DIR |= BIT5;
P3OUT = 0;
P3DIR |= BIT2;
P3OUT = 0;
P3DIR |= BIT3;
P3OUT = 0;
P4DIR = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7 ;
P4OUT = (0xC0 | line);
Enable_Pulse();
}
void GLCD_Write(unsigned char* b)
{
	P3DIR |= BIT6;
P3OUT = 0x40;
P3DIR |= BIT5;
P3OUT = 0x00;
P4DIR = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7 ;
P4OUT = 0xb0;
Delay(1000);
Enable_Pulse();
}
void GLCD_Read(unsigned short column)
{
unsigned short read_data = 0;
P4DIR = BIT0 & BIT1 & BIT2 & BIT3 & BIT4 & BIT5 & BIT6 & BIT7 ;
P4IN = 0x00;
P3DIR |= BIT5;
P3OUT= 0x20;
P3DIR |= BIT6;
P3OUT= 0x40;
P3DIR |= BIT2;
P3OUT= (column>63);
P3DIR= BIT3;
P3OUT = !(column>63);
Delay(1000);
P3DIR |= BIT7;
P3OUT = 0x80;
Delay(1000);
P3DIR |= BIT7;
P3OUT= 0x00;
Delay(1000);
P3DIR |= BIT7;
P3OUT = 0x80;
Delay(1000);
read_data = P4IN;
P3DIR |= BIT7;
P3OUT = 0;
Delay(1000);
P4DIR = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7 ;
P4OUT = read_data;
}
void GLCD_COL(unsigned int x)
{
unsigned short Col_Data;
P3DIR |= BIT6;
P3OUT = 0;
P3DIR |= BIT6;
P3OUT = 0;
if(x<64)
{
P3DIR |= BIT2;
P3OUT = 0x00;
P3DIR |= BIT3;
P3OUT= 0x08;
Col_Data = x;
}
else
{
	P3DIR |= BIT3;
P3OUT = 0;
P3DIR |= BIT2;
P3OUT = 0x04;
Col_Data = x-64;
}
Col_Data = ((Col_Data || 0x40 ) && 0x7F);
P4OUT = Col_Data;
Enable_Pulse();
}
void GLCD_ROW(unsigned int y)
{
unsigned short Col_Data;
P3DIR |= BIT6;
P3OUT = 0;
P3DIR |= BIT5;
P3OUT= 0;
Col_Data = ((y || 0xB8 ) && 0xBF);
P4DIR = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7 ;
P4OUT = Col_Data;
Enable_Pulse();
}
void GLCD_XY(unsigned int x,unsigned int y)
{
GLCD_COL(x);
GLCD_ROW(y);
}
char * CopyConst2Ram(char * dest, const char * src){
for(;*dest++ = *src++;)
;
return dest;
}
void GLCD_Rectangle(unsigned int a1, unsigned int b1, unsigned int c1 ,unsigned int d1){

	 GLCD_COL(a1);
	 GLCD_ROW(b1);
	 GLCD_COL(c1);
	 GLCD_ROW(d1);
}
void GLCD_Box(unsigned int a1, unsigned int b1, unsigned int c1 ,unsigned int d1){
	 GLCD_COL(a1);
	 GLCD_ROW(b1);
	 GLCD_COL(c1);
	 GLCD_ROW(d1);
}
int GetX()
{
	P2DIR |= tft_driveA;
		    P2OUT = 0x02;
		    P2DIR |= tft_driveB;
		    P2OUT = 0x00;

		    Delay(1000);
		ADC12_Init1();
return(0);
}
int GetY()
{
	P2DIR |= tft_driveA;
			    P2OUT = 0x00;
			    P2DIR |= tft_driveB;
			    P2OUT = 0x04;

Delay(1000);
ADC12_Init1();
return(0);
}

void DCM_Forward(void)
{
	P3DIR |=BIT4;
	P3OUT=0x10;
	P3DIR |=BIT5;
	P3OUT=0;
	P3DIR |=BIT6;
	P3OUT=0;
	P3DIR |=BIT7;
	P3OUT=0x80;
}
void DCM_Back(void)
{
	P3DIR |=BIT4;
	P3OUT=0;
	P3DIR |=BIT5;
	P3OUT=0x20;
	P3DIR |=BIT6;
	P3OUT=0x40;
	P3DIR |=BIT7;
	P3OUT=0;
}
void DCM_Left(void)
{
	P3DIR |=BIT4;
	P3OUT=0x10;
	P3DIR |=BIT5;
	P3OUT=0;
	P3DIR |=BIT6;
	P3OUT=0x40;
	P3DIR |=BIT7;
	P3OUT=0;
}
void DCM_Right(void)
{

	P3DIR |=BIT4;
	P3OUT=0;
	P3DIR |=BIT5;
	P3OUT=0x20;
	P3DIR |=BIT6;
	P3OUT=0;
	P3DIR |=BIT7;
	P3OUT=0x80;
}
void DCM_Stop(void)
{

	P3DIR |=BIT4;
	P3OUT=0;
	P3DIR |=BIT5;
	P3OUT=0;
	P3DIR |=BIT6;
	P3OUT=0;
	P3DIR |=BIT7;
	P3OUT=0;
}

void ADC12_Init1(void)
{
	ADC12CTL1=ADC12INCH_1+ADC12INCH_2+ ADC12DIV_7;
	    ADC12CTL0=ADC12REF2_5V+ADC12REFON+ADC12SHT03+ADC12ON+ADC12IE;
	    _BIS_SR(GIE);
	    while(1)
	        {
	        ADC12CTL1 |= ADC12ENC+ ADC12SC;
	         Delay(1000);
	        }
}
unsigned char interrupt_triggered = 0;
int* a;
int* b;
void ADC12_ServiceFunction(ADC12_param);
#pragma vector=ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
        interrupt_triggered = 1;
         _BIC_SR_IRQ(LPM3_bits);
         if (tft_driveA==1){
        	 a= ADC12MEM;
         }
         else{
        	 b= ADC12MEM;
         }
}
volatile unsigned char i;
void Delay(unsigned int tic)
{
        while(tic!=0)
        {
                i=140;
                while(i!=0)
                {
                i--;
                }
                tic--;
        }
}
