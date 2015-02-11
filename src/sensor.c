/**
 *  @file      src
 *  @brief     Paper Feeding Machine Control by PIC18F458 microcontroller and link to a Touch Panel.This project based on Paper Feeding Machine which rolls polythene/ papers to other machines in big industrial machines. The machine where the paper needs to be feed and for that needed control.
               That is the Picture of the paper Feeding machine where paper is mounted on shaft and the paper need to feed in the next machine. In here I had to control the feeding system in such a way to maintain the continuity of the paper in the next system so that paper don't touch the ground as well as paper should not breakup if the next machine is running is taking paper and our feeder is stopped. The machine should start and stops according to the next machine.
 *  @author    Indrajit Paul <indra.p21@gmail.com>
 *  @version   1.00, 
 *             programming language "C",
 *             development tool chain "keil "
 *             and "Microelectronika "
 *             and "Code composer studio"
 *  @date      2015-01-31
 *  @copyright Apache License, Version 2.0
 *
 *  
 *
 *  Copyright 1988-2015 Indrajit Paul
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing,
 *  software distributed under the License is distributed on an
 *  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 *  either express or implied.
 *  See the License for the specific language governing permissions
 *  and limitations under  the License. .....*/
#include "me18.H"
//#include "justmisra.H"
void GLCD_Write_Data(unsigned short ddata);
void main() {
unsigned char x;
#ifndef P18F458
 TRISD=0x00;
 TRISB=0x00;
 TRISA5_bit=1;
 TRISE0_bit=1;
 TRISA0_bit=1;
 TRISA4_bit=1;
 TRISA1_bit=1;
 TRISC4_bit=0;
 TRISC5_bit=0;
 TRISC6_bit=0;
 TRISC7_bit=0;
 TRISC1_bit=0;
 TRISC0_bit=0;
 TRISB6_bit=1;
 GLCD_CS1 = 1; // De-Activate both chips
 GLCD_CS2 = 1;
 GLCD_RST = 1;
 #endif
 GLCD_ON();
 GLCD_Set_Font(Font_Glcd_5x7, 5, 7, 32); // Choose font
 GLCD_Fill(0); // Clear GLCD
 CopyConst2Ram(msg,msg1); // Copy “COUNTER= ” string to RAM
 Glcd_Write_Text(msg,10,0,1);
//Display Buttons on GLCD: //
 GLCD_Rectangle(3,10,50,35,1);
 GLCD_Rectangle(7,16,35,45,1);
 GLCD_Rectangle(68,16,120,48,1);
 GLCD_Box(10,18,58,46,1);
 GLCD_Box(70,14,90,44,1);
 GLCD_Box(50,16,70,48,1);
 CopyConst2Ram(msg,msg2); // Copy “BUTTON1” string to RAM
 GLCD_Write_Text(msg,14,3,0);
 CopyConst2Ram(msg,msg4);
  GLCD_Write_Text(msg,14,4,0);
 CopyConst2Ram(msg,msg3); // Copy “BUTTON2” string to RAM
 GLCD_Write_Text(msg,74,3,0);
 CopyConst2Ram(msg,msg5); // Copy “MOTOR ANTICLOCKWISE” string to RAM
 GLCD_Write_Text(msg,74,5,0);
 CopyConst2Ram(msg,msg9); // Copy “BUTTON3” string to RAM
  GLCD_Write_Text(msg,82,3,0);
 CopyConst2Ram(msg,msg6); // Copy “STOP” string to RAM
 GLCD_Write_Text(msg,82,4,0);
Label:
SWITCH1=0;
switch(SWITCH1)
{
case 0:           ////FOR AUTOMOMATIC////
if (S1==1 && S2==1)
MOTOR_CLOCKWISE();
else if(S1==1 && S2==0)
MOTOR_ANTICLOCKWISE();
else if(S1=0 && S2==0)
MOTOR_STOP();
else
MOTOR_STOP();
break;
case 1:                 //////FOR MANNUAL///
if (TP_Press_Detect())
x_coord = GetX();
y_coord = GetY();
x_coord128 = (x_coord * 128) / 1024;
y_coord64 = 64 -((y_coord *64) / 1024);

//if BUTTON1 is selected
if ((x_coord128 >= 10) && (x_coord128 <= 58) && (y_coord64 >= 18) && (y_coord64 <= 46)) {
 {
 {
MOTOR_CLOCKWISE();
CopyConst2Ram(msg,msg7); // Copy “CLOCKWISE  ON “ string to RAM
Glcd_Write_Text(msg,14,4,0);
}

if ((x_coord128 >= 70) && (x_coord128 <= 90) && (y_coord64 >= 14) && (y_coord64 <= 44)){
MOTOR_ANTICLOCKWISE();
CopyConst2Ram(msg,msg8); // Copy “ANTICLOCKWISE ON “ string to RAM
Glcd_Write_Text(msg,74,4,0);
}
if ((x_coord128 >= 70) && (x_coord128 <= 90) && (y_coord64 >= 14) && (y_coord64 <= 44)) {
MOTOR_STOP();
CopyConst2Ram(msg,msg10); // Copy “STOP “ string to RAM
Glcd_Write_Text(msg,74,4,0);
}
else
MOTOR_STOP();
}
}
break;
T0CON=0x68;
TMR0L=0;
if (S1==1){
do{
T0CON.TMR0ON=1;
x=TMR0L;
}
while(INTCON.TMR0IF==0);
T0CON.TMR0ON=0;
INTCON.TMR0IF==0;

}
CopyConst2Ram(msg,msg1);
GLCD_Write_Data(x);
}
if (x=200)       ////8 bit counter so 25 maxima
MOTOR_STOP();
else
goto Label;
}