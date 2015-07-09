//#define DEBUG

#include <SPI.h>
#include <Usb.h>
#include <usbh_midi.h>

USB Usb;
USBH_MIDI Midi(&Usb);

byte PatchA1 = 0x31;
byte PatchA2 = 0x2F;
byte PatchB1 = 0x30;
byte PatchB2 = 0x2B;
byte PatchC1 = 0x2D;
byte PatchC2 = 0x2A;
byte PatchD1 = 0x2C;
byte PatchD2 = 0x29;
byte PatchOff = 0x2E;

byte cmd;
byte data1;
byte data2;

#ifdef DEBUG
  #define ledpin A1
  #define transpin A2
#endif

void setup() {
  #ifdef DEBUG
    pinMode(ledpin, OUTPUT);
    pinMode(transpin, OUTPUT);
    digitalWrite(transpin, HIGH);
  #endif
  
  Usb.Init();
  SendMIDI(0);
  
  #ifdef DEBUG
    digitalWrite(transpin, LOW);
  #endif
  
  Serial.begin(31250);
  
  #ifdef DEBUG
  for (int i = 0; i < 4; i++) {    // flash led for indicating arduino start
    digitalWrite(ledpin, HIGH);
    delay(300);
    digitalWrite(ledpin, LOW);
    delay(200);
  }
  #endif
}

void loop() {
  // put your main code here, to run repeatedly:
    if (Serial.available() > 0) 
    {
        #ifdef DEBUG
          digitalWrite(ledpin, HIGH);
        #endif
        cmd = Serial.read();
        data1 = Serial.read();
        data2 = Serial.read();

        switch(cmd) {
          case 0 : SendMIDI(PatchA1);
            break;
          case 1 : SendMIDI(PatchA2);
            break;
          case 2 : SendMIDI(PatchB1);
            break;
          case 3 : SendMIDI(PatchB2);
            break;
          case 4 : SendMIDI(PatchC1);
            break;
          case 5 : SendMIDI(PatchC2);
            break;
          case 6 : SendMIDI(PatchD1);
            break;
          case 7 : SendMIDI(PatchD2);
            break;
        }
        #ifdef DEBUG
          digitalWrite(ledpin, LOW);
        #endif
    }
}


// Send "Program Change" MIDI Message

void SendMIDI(byte number)
{
  Usb.Task();
  if( Usb.getUsbTaskState() == USB_STATE_RUNNING )
  {
    #ifdef DEBUG
      digitalWrite(transpin, HIGH);
    #endif
    
    byte Message[2];                 // Construct the midi message (2 bytes)
    Message[0]=0xC0;                 // 0xC0 is for Program Change 
    Message[1]=number;               // Number is the program/patch 

    Midi.SendData(Message);          // Send the message
    delay(10);
    
    #ifdef DEBUG
      digitalWrite(transpin, LOW);
    #endif
  }
  else
  {
    #ifdef DEBUG
      digitalWrite(transpin, HIGH);
      delay (500);
      digitalWrite(transpin, LOW);
      delay (500);
      digitalWrite(transpin, HIGH);
      delay (500);
      digitalWrite(transpin, LOW);
      delay (500);
      digitalWrite(transpin, HIGH);
      delay (500);
      digitalWrite(transpin, LOW);
    #endif
  }
}
