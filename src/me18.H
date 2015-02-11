#ifndef P18F458_H_
#define P18F458_H_
// Glcd module connections  //
//#include <p18f458.h>
#define GLCD_Dir TRISD
char GLCD_DataPort at PORTD;
sbit GLCD_CS1 at LATB0_bit;
sbit GLCD_CS2 at LATB1_bit;
sbit GLCD_RS  at LATB2_bit;
sbit GLCD_RW  at LATB3_bit;
sbit GLCD_EN  at LATB4_bit;
sbit GLCD_RST at LATB5_bit;
sbit GLCD_CS1_Direction at TRISB0_bit;
sbit GLCD_CS2_Direction at TRISB1_bit;
sbit GLCD_RS_Direction  at TRISB2_bit;
sbit GLCD_RW_Direction  at TRISB3_bit;
sbit GLCD_EN_Direction  at TRISB4_bit;
sbit GLCD_RST_Direction at TRISB5_bit;
// End Glcd module connections  //
// Touch Panel module connections   //
sbit DriveA at RC0_bit;
sbit DriveB at RC1_bit;
sbit DriveA_Direction at TRISC0_bit;
sbit DriveB_Direction at TRISC1_bit;
// End Touch Panel module connections   //
sbit LED1 at RC0_bit;
sbit LED2 at RC1_bit;
sbit LED1_Direction at TRISC0_bit;
sbit LED2_Direction at TRISC1_bit;
sbit SWITCH1 at RB6_bit;            //SWITCH1 CONTROL AUTOMATIC OR MANNUAL MODE //
sbit SWITCH1_Direction at TRISB6_bit; // IF SWITCH1=0 THEN AUTOMATIC MODE AND IF SWITCH1=1 THEN MANNUAL MEANS USER CONTROL THE SYSTEM USING BY TFT TOUCH PANEL//
//SENSOR CONNECTION//
sbit COUNTERSENSOR at RA4_bit;
sbit UPPERENSOR at RA5_bit;
sbit LOWERSENSOR at RE0_bit;
sbit COUNTERSENSOR_Direction at TRISA4_bit;
sbit UPPERSENSOR_Direction at TRISA5_bit;
sbit LOWERSENSOR_Direction at TRISE0_bit;
sbit S1 at RA5_bit;
sbit S2 at RE0_bit;
sbit S3 at RA4_bit;
//END SENSOR CONNECTION//
// H BRIDGE CONNECTION//
sbit INPUTA1 at RC4_bit;
sbit INPUTA2 at RC5_bit;
sbit INPUTB1 at RC6_bit;
sbit INPUTB2 at RC7_bit;
sbit INPUTA1_Direction at TRISC4_bit;
sbit INPUTA2_Direction at TRISC5_bit;
sbit INPUTB1_Direction at TRISC6_bit;
sbit INPUTB2_Driection at TRISC7_bit;
//END OF H BRIDGE CONNECTION//
//ASSIGN ANSEL AND ANSELH REGISTER FOR PIC18F458 //
sfr unsigned short volatile ANSEL           absolute 0x0188;       //DECLERATION OF ANSEL REGISTER//
sfr unsigned short volatile ANSELH          absolute 0x0189;       //DECLERATION OF ANSELH REGISTER//
//MOTOR PROTOTYPE//
void MOTOR_CLOCKWISE();
void MOTOR_ANTICLOCKWISE();
void MOTOR_STOP();
#endif
//MOTOR WORK//
void MOTOR_CLOCKWISE()
{
INPUTA1=1;
INPUTA2=0;
INPUTB1=0;
INPUTB2=1;
}
void MOTOR_ANTICLOCKWISE()
{
INPUTA1=0;
INPUTA2=1;
INPUTB1=1;
INPUTB2=0;
}
void MOTOR_STOP()
{
INPUTA1=0;
INPUTA2=0;
INPUTB1=0;
INPUTB2=0;
}
//END OF MOTOR FUNCTION//
 void Enable_Pulse() {
 GLCD_EN = 1; //EN high
 delay_us(5);
 GLCD_EN = 0; //EN low
 delay_us(5);
 }
 void GLCD_ON() {
 //Activate both chips
 GLCD_CS1 = 0;
 GLCD_CS2 = 0;
 GLCD_RS = 0; //RS low --> command
 GLCD_RW = 0; //RW low --> write
 GLCD_DataPort = 0x3F; //ON command
 Enable_Pulse();
 }
void Set_Start_Line(unsigned short line)
{
GLCD_RS = 0; //RS low --> command
GLCD_RW = 0; //RW low --> write //Activate both chips
GLCD_CS1 = 0;
GLCD_CS2 = 0;
GLCD_DataPort = 0xC0 | line; //Set Start Line command
Enable_Pulse();
}
void GLCD_Write(unsigned short b)
{
GLCD_RS = 1; //RS high --> data
GLCD_RW = 0; //RW low --> write
GLCD_DataPort = b; //put data on data port
delay_us(1);
Enable_Pulse();
}
unsigned short GLCD_Read(unsigned short column)
{
unsigned short read_data = 0; //Read data here
GLCD_Dir = 0xFF; //PORTD as Input
GLCD_RW = 1; //Read
GLCD_RS = 1; //Data
GLCD_CS1 = (column>63);
GLCD_CS2 = !GLCD_CS1; //Disable/Enable CS2
delay_us(1); //tasu
GLCD_EN = 1; //Latch RAM data into ouput register
delay_us(1); //twl + tf
//Dummy read
GLCD_EN = 0; //Low Enable
delay_us(5);
GLCD_EN = 1; //latch data from output register to data bus d
Delay_us(1); //tr + td(twh)
read_data = GLCD_DataPort; //Input data
GLCD_EN = 0; //Low Enable to remove data from the bus
delay_us(1); //tdhr
GLCD_Dir = 0x00; //Output again return read_data;
}
void GOTO_COL(unsigned int x)
{
unsigned short Col_Data;
GLCD_RS = 0; //RS low --> command
GLCD_RW = 0; //RW low --> write
if(x<64) //left section
{
GLCD_CS1 = 0; //select chip 1
GLCD_CS2 = 1; //deselect chip 2
Col_Data = x; //put column address on data port
}
else     //right section
{
GLCD_CS2 = 0;
GLCD_CS1 = 1;
Col_Data = x-64; //put column address on data port
}
Col_Data = (Col_Data | 0x40 ) & 0x7F; //Command format
GLCD_DataPort = Col_Data;
Enable_Pulse();
}
void GOTO_ROW(unsigned int y)
{
unsigned short Col_Data;
GLCD_RS = 0; //RS low --> command
GLCD_RW = 0; //RW low --> write
Col_Data = (y | 0xB8 ) & 0xBF; //put row address on data port set command
GLCD_DataPort = Col_Data;
Enable_Pulse();
}
void GOTO_XY(unsigned int x,unsigned int y)
{
GOTO_COL(x);
GOTO_ROW(y);
}
//STARTING TFT //
const char msg1[] = "COUNTER= ";
const char msg2[] = "BUTTON1";
const char msg3[] = "BUTTON2";
const char msg9[] = "BUTTON3";
const char msg4[] = "MOTOR CLOCKWISE";
const char msg5[] = "MOTOR ANTICLOCKWISE";
const char msg7[] = "CLOCKWISE";
const char msg8[] = "ANTICLOCKWISE";
const char msg6[] = "SYSTEM STOP";
const char msg10[] = "STOP";
long x_coord, y_coord, x_coord128, y_coord64; // scaled x-y position
char msg[16];
void Initialize() {
  DriveA_Direction = 0;                                    // Set DriveA pin as output
  DriveB_Direction = 0;                                    // Set DriveB pin as output
  ANSEL=3;
  ANSELH=0;                                           // and other AN pins as digital I/O
  TRISA  = 0X03;
  //C1ON_bit = 0;                                            // Disable comparators
  //C2ON_bit = 0;
  Glcd_Init();                                             // Initialize GLCD
  Glcd_Fill(0);                                            // Clear GLCD
  ADC_Init();                                              // Initialize ADC
  TP_Init(128, 64, 0, 1);                                  // Initialize touch panel, dimensions 128x64 AND READX_CH NO=0 , READY_CH NO=1;
  TP_Set_ADC_Threshold(900);                               // Set touch panel ADC threshold
}
char * CopyConst2Ram(char * dest, const char * src){
for(;*dest++ = *src++;)
;
return dest;
}
unsigned int GetX() {
//reading X
LED1 = 1; // DRIVEA = 1 (LEFT drive on, RIGHT drive on, TOP drive off )
LED2 = 0; // DRIVEB = 0 (BOTTOM drive off )
Delay_ms(5);
return ADC_read(0); // reading X value from RA0 (BOTTOM)
}
unsigned int GetY() {
//reading Y
LED1 = 0; // DRIVEA = 0 (LEFT drive off , RIGHT drive off , TOP drive on)
LED2= 1; // DRIVEB = 1 (BOTTOM drive on)
Delay_ms(5);
return ADC_read(1); // reading Y value from RA1 (from LEFT)
}