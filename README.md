# Embedded System & Microcontroller Projects : 03 Project  – Paper Feeding Machine Control by PIC18F458 microcontroller and link to a Touch Panel.
## 03.1 Project Description:
- Project Name : Motor control using by PIC18F458 microcontroller and Touch panel.
- Skill : Sensor used proximity sensor and counter sensor,  programming used Embedded C, Hardware design Multisim, PCB design in Ultiboard, Microcontroller used PIC18F458.
- Application : In Industry, Biomedical, Automation industry, Aerospace etc. 
- Result : Completed.
- This project based on Paper Feeding Machine which rolls polythene/ papers to other machines in big industrial machines. The machine where the paper needs to be feed and for that needed control.That is the Picture of the paper Feeding machine where paper is mounted on shaft and the paper need to feed in the next machine. In here I had to control the feeding system in such a way to maintain the continuity of the paper in the next system so that paper don't touch the ground as well as paper should not breakup if the next machine is running is taking paper and our feeder is stopped. The machine should start and stops according to the next machine.
Here two types control are used 
        1. Automatic.
        2. Manual.
        3. Motor control speed.
        4 Start/Stop the whole system.

- I need to control a DC motor 24 volts with brush with the microcontroller PIC18F458 with the signal input from the two proximity sensors. The complete system needs to work in two mods. Automatic mode and manual mode. In automatic mode the motor will automatically starts and stops with the sensor signal input from the either sensors. In manual mode the motor would be operated by the operator bye a push button called Jog mode. When the push button is pressed the motor will start and when the push button released the motor will stops.
Here two proximity sensors are used for automatic motor(24VDC) control. Here two sensors are described as upper sensor and lower sensor.
  ## Working Principle of sensors:                                                    
         Upper sensor                      Lower Sensor                  Result

          covered                           covered                   Motor start

          uncovered                         covered                   No result

          covered                           uncovered                 Motor start

          uncovered                         uncovered                 Motor stop
- Upper sensor is used to stop the machine then uncovered and lower sensor is used to start the machine then covered.  Another sensor counter sensor is used for paper count. In every paper have a hole or black spot. When the paper hole or black spot is detect by the counter sensor then counter sensor gives a value 0 or 1 and microcontroller count the value and display the value in TFT screen. Every 500 times the count the paper hole the machine should be stopped.
For manual control in here TFT screen is used. In here two button is created one is start button and another is stop button.

## 03.2 Pin Connection: 

              PIN1                          RESTART OF MICROCONTROLLER
              PIN2                          READ X(TFT) A/D
              PIN3                          READ Y(TFT) A/D
              PIN4                          ANALOG CONVERSION(VREF(-)USED AS GND)
              PIN5                          ANALOG CONVERSION(VREF(+))
              PIN6                          COUNTER SENSOR(S3)
              PIN7                          UPPER SENSOR(S1)
              PIN8                          LOWER SENSOR(S2)
              PIN9
              PIN10
              PIN11                         VCC(+5V)
              PIN12                         GND
              PIN13                         XT USED 8 MHz
              PIN14                         XT USED 8 MHz
              PIN15                         RC0 USED FOR DRIVE A OF TFT
              PIN16                         RC1 USED FOR DRIVE B OF TFT
              PIN17
              PIN18                         USB VOLTAGE(3.3V) NC
              PIN19                         D0 (DATA PORT FOR TFT)
              PIN20                         D1 (DATA PORT FOR TFT)
              PIN21                         D2 (DATA PORT FOR TFT)
              PIN22                         D3 (DATA PORT FOR TFT)
              PIN23                         INPUT1 FOR H BRIDGE1
              PIN24                         INPUT2 FOR H BRIDGE1
              PIN25                         INPUT1 FOR H BRIDGE2
              PIN26                         INPUT2 FOR H BRIDGE2
              PIN27                         D4 (DATA PORT FOR TFT)
              PIN28                         D5 (DATA PORT FOR TFT)
              PIN29                         D6 (DATA PORT FOR TFT)
              PIN30                         D7 (DATA PORT FOR TFT)
              PIN31                         GND (0V)
              PIN32                         VDD(+5V)
              PIN33                         CS1 OF TFT
              PIN34                         CS2 OF TFT
              PIN35                         RS OF TFT
              PIN36                         R/W OF TFT
              PIN37                         ENABLE OF TFT
              PIN38                         RST OF TFT
              PIN39
              PIN40

## 03.3 General Description of TFT Screen:

             PIN1                    CS1 CONNECTED WITH RB0
             PIN2                    CS2 CONNECTED WITH RB1
             PIN3                    GND
             PIN4                    VCC
             PIN5                    VO
             PIN6                    RS(REGISTER SELECTION) CONNECTED WITH RB2
             PIN7                    R/W(READ OR WRITE) CONNECTED WITH RB3
             PIN8                    ENABLE CONNECTED WITH RB4
             PIN9                    D0 CONNECTED WITH RD0
             PIN10                   D1 CONNECTED WITH RD1
             PIN11                   D2 CONNECTED WITH RD2
             PIN12                   D3 CONNECTED WITH RD3
             PIN13                   D4 CONNECTED WITH RD4
             PIN14                   D5 CONNECTED WITH RD5
             PIN15                   D6 CONNECTED WITH RD6
             PIN16                   D7 CONNECTED WITH RD7
             PIN17                   RST(RESTART) CONNECTED WITH RB5
             PIN18                   VEE 
             PIN19                   LED(+) VCC
             PIN20                   LED(+) VCC
                                                              }
## 03.4 Running Code Window:
![WP3](https://github.com/indra1234/images/blob/0add27cd1cef5a49ec4cf5a98a40ad73050e9567/electronics/12.JPG?raw=true)
![wp3](https://github.com/indra1234/images/blob/0add27cd1cef5a49ec4cf5a98a40ad73050e9567/electronics/11.JPG?raw=true)

## 03.5 Photos of the Machine and the Project Workplace
![WP3](https://github.com/indra1234/images/blob/0add27cd1cef5a49ec4cf5a98a40ad73050e9567/electronics/15.JPG?raw=true)
![WP3](https://github.com/indra1234/images/blob/0add27cd1cef5a49ec4cf5a98a40ad73050e9567/electronics/14.JPG?raw=true)
![WP3](https://github.com/indra1234/images/blob/0add27cd1cef5a49ec4cf5a98a40ad73050e9567/electronics/13.JPG?raw=true)



