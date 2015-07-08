#define KNOB1 0
#define KNOB2 1

#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 4

#define STAT1 13
#define STAT2 6

#define OFF 1
#define ON 2
#define WAIT 3

#include <LiquidCrystal.h>
//#include <Usb.h>
//#include <usbhub.h>
//#include <usbh_midi.h>

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

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
    pinMode(STAT1, OUTPUT);
    pinMode(STAT2, OUTPUT);
    pinMode(BUTTON1, INPUT);
    pinMode(BUTTON2, INPUT);
    pinMode(BUTTON3, INPUT);
    
    digitalWrite(BUTTON1, HIGH);
    digitalWrite(BUTTON2, HIGH);
    digitalWrite(BUTTON3, HIGH);
    
    for (int i = 0; i < 10; i++) {
        digitalWrite(STAT1, HIGH);
        digitalWrite(STAT2, LOW);
        delay(30);
        digitalWrite(STAT1, LOW);
        digitalWrite(STAT2, HIGH);
        delay(30);
    }
    digitalWrite(STAT1, HIGH);
    digitalWrite(STAT2, HIGH);

    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("hello, world!");
    
    Serial.begin(31250);
}

void loop() {
  // put your main code here, to run repeatedly:
    if (Serial.available() > 0) 
    {
        cmd = Serial.read();
        data1 = Serial.read();
        data2 = Serial.read();
        lcd.setCursor(0, 1);
        lcd.print(cmd);
        lcd.print('.');
        lcd.print(data1);
        lcd.print('.');
        lcd.print(data2);
        lcd.print("       ");
    }
}


// Send "Program Change" MIDI Message

/*void SendMIDI(byte number)
{
  Usb.Task();
  if( Usb.getUsbTaskState() == USB_STATE_RUNNING )
  {
    byte Message[2];                 // Construct the midi message (2 bytes)
    Message[0]=0xC0;                 // 0xC0 is for Program Change 
    Message[1]=number;               // Number is the program/patch 
    Midi.SendData(Message);          // Send the message
    delay(10);
  }
  else
  {
      lcd.setCursor(0, 0);
      lcd.print("Error");
    digitalWrite(outPinErr, HIGH);
    delay (500);
    digitalWrite(outPinErr, LOW);
    delay (500);
    digitalWrite(outPinErr, HIGH);
    delay (500);
    digitalWrite(outPinErr, LOW);
    delay (500);
    digitalWrite(outPinErr, HIGH);
    delay (500);
    digitalWrite(outPinErr, LOW);
  }
}*/
