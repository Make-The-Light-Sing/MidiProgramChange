//#define DEBUG

#include <SPI.h>
#include <Usb.h>
#include <usbh_midi.h>

USB Usb;
USBH_MIDI Midi(&Usb);

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

bool received = false;
long time = 0;
long debounce = 1000;

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
       
        if (millis() - time > debounce) {
          if (received) {
            SendMIDI(cmd);
            received = false;
            time = millis();
          } else {
            received = true;
          }
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
