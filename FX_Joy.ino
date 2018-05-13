/*
Uses an analog micro joystick to trigger an Adafruit FX sound board.
I use the the 2Meg or 16Meg with the built in amplifier 
The computer will not recognize the FX sound board if the serial pins 
are connected to the arduino; you must disconnect to transfer files. 
Joystick must be calibrated, see section of code 
*/

#include <SoftwareSerial.h>
#include "Adafruit_Soundboard.h"

#define SFX_TX 5 // TX Pin of FX
#define SFX_RX 6 // RX Pin of FX
#define SFX_RST 7  // RST of FX
SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);
//SoftwareSerial mySerial(2,6); // RX/TX pin 2 = TX, pin 6 = RX (unused)
Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);


int potpinS1 = 0;  //analog input pin A0 switch these around to reverse joystick axis 
int potpinS2 = 1;  //analog input pin A1

int newvalS1;
int newvalS2;
int YN = 0;
int D1 = 90;
int D2 = 90;
int H1 = 3;
int H2 = 3;
int MC =1;
int Pin3 = digitalRead(3); // button pin

void setup() 
{

  pinMode(3, INPUT);           // set button pin to input
digitalWrite(3, HIGH);       

  Serial.begin(9600);  
  ss.begin(9600);  //FX sound
 Serial.println("Joystick AD output");   
 //view output using the serial monitor
}

   
void loop() 
{ 
  newvalS1 = analogRead(potpinS1);           
  newvalS1 = map(newvalS1, 0, 1023, 0, 181); // adjust here or there for pot adjustment
delay (100);
newvalS2 = analogRead(potpinS2);
newvalS2 = map(newvalS2, 0, 1023, 0, 176);  // adjust here or there for pot adjustment

  Serial.print("MC= ");
  Serial.println(MC);
  Pin3 = digitalRead(3); 
 
 if ((newvalS2)>(D2 -H2) && (newvalS2) < (D2 +H2) && (newvalS1) > (D1 -H1) &&(newvalS1) < (D1 +H1)) 
 {
 MC =1; // no movement

 }

if  ((newvalS1) > (D1 +H1)  && (newvalS2)>(D2 -H2) && (newvalS2) < (D2 +H2))
{ 
   MC = 8; // Forward
}

if  ((newvalS1) < (D1 -H1)  && (newvalS2)>(D2 -H2) && (newvalS2) < (D2 +H2)) // right spin

{ 
   MC = 5; //rev
}

if  ((newvalS2) > (D2 +H2) && (newvalS1) > (D1 -H1) &&(newvalS1) < (D1 +H1)) // left
{ 
   MC = 2;  // left
}
  
if ((newvalS2) < (D2 - H2) && (newvalS1) > (D1 -H1) &&(newvalS1) < (D1 +H1))
{ 
   MC = 3; // right
}


if ((newvalS1) < (D1 -H1)&& (newvalS2)>(D2 + H2))
 {
    MC =4;     // slight left reverse
 }
  

if ((newvalS2) < (D2 - H2) && (newvalS1) < (D1 - H1))
{ 
   MC = 6; //silght right reverse
}


  if ((newvalS2) > (D2 +H2)  && (newvalS1) > (D1 +H1)) 

{ 
   MC = 7; //silght left  forward
}


if ((newvalS2)< (D2 - H2) && (newvalS1) > (D1 +H1))
{ 
   MC = 9; //silght right  forward
}

if (Pin3 == 0) // Button press
{
  MC = 10;
}

switch (MC) {
     case 1: //all off

Serial.print("ALL STOP");
  Serial.println("   ");
 Serial.print("1- ");
 Serial.println(newvalS1);
 Serial.print("2- ");    
 Serial.println(newvalS2);
 Serial.print("PIN 3 ");    
 Serial.println(Pin3);
   
       break;     

case 2: // left

 sfx.playTrack (4); 
 Serial.print("LEFT ");
   Serial.println("   ");

 Serial.print("1- ");
 Serial.println(newvalS1);
 Serial.print("2- ");    
 Serial.println(newvalS2);
       break;

 case 9://Right & Forward 

  sfx.playTrack(5); 
   Serial.print("Right & Forward");
 Serial.println("   ");
 Serial.print("1- ");
 Serial.println(newvalS1);
 Serial.print("2- ");    
 Serial.println(newvalS2);    
       break;
       
  case 3:// right

 sfx.playTrack(3); 

  Serial.print("Right ");
 Serial.println("   ");
 Serial.print("1- ");
 Serial.println(newvalS1);
 Serial.print("2- ");    
 Serial.println(newvalS2);
         break;
    
case 8:// Forward 
  
  YN = 1;
    sfx.playTrack(YN); 
 Serial.print(" Forward");
 Serial.println("     ");
Serial.print("1- ");
 Serial.println(newvalS1);
 Serial.print("2- ");    
 Serial.println(newvalS2);

       break;
       
  case 7://left forward 
sfx.playTrack(6); 

 delay (20);
 
  Serial.print(" Left & Forward");
  Serial.println("   ");
 
 Serial.print("1- ");
 Serial.println(newvalS1);
 Serial.print("2- ");    
 Serial.println(newvalS2);   
       break;
 
case 6://Right reverse slight

sfx.playTrack(7); 

 Serial.print("Right reverse slight");
 Serial.println("   ");
Serial.print("1- ");
 Serial.println(newvalS1);
 Serial.print("2- ");    
 Serial.println(newvalS2);
      
       break;

 case 5: //Rev
 sfx.playTrack(2); 

Serial.print("Reverse ");
Serial.println("   ");
 
Serial.print("1- ");
 Serial.println(newvalS1);
 Serial.print("2- ");    
 Serial.println(newvalS2);

 
       break;

case 4://Reverse Left 

sfx.playTrack(8); 

Serial.print("Reverse and Left slight");
Serial.println("   ");
Serial.print("1- ");
 Serial.println(newvalS1);
 Serial.print("2- ");    
 Serial.println(newvalS2);
  
       break;
case 10: //Button pressed
  sfx.playTrack(9);    

Serial.print("BUTTON Pressed");
Serial.println("   ");
   break;
     default: 
       // if nothing else matches, do the default
       // default is optional
     break;
   }

delay (200);
  
  }




