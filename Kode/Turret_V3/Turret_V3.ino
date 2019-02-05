#include <SoftwareSerial.h>  
#include <Stepper.h>

  //http://www.arduino.cc/en/Tutorial/Button
  // constants won't change. They're used here to set pin numbers:
const int buttonPin = 4;     // the number of the pushbutton pin
const int ledPin = 13;

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3
const int R = 8;   //Drej til venstre
const int L = 9;   //Drej til højre
const int U = 10;   //Op
const int D = 11;   //Ned
const int S = 12;   //Skyd

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  Serial.begin(9600);  // Begin the serial monitor at 9600bps

  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$");  // Print three times individually
  bluetooth.print("$");
  bluetooth.print("$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  bluetooth.println("SM,0");
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
  pinMode(R, OUTPUT);
  pinMode(L, OUTPUT);
  pinMode(U, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(S, OUTPUT);
}

void loop()
{
    digitalWrite(R, LOW);
    digitalWrite(L, LOW);
    digitalWrite(U, LOW);
    digitalWrite(D, LOW);
    digitalWrite(S, LOW);
  if(bluetooth.available())
    switch ((char)bluetooth.read()){
      case 'a':
     digitalWrite(R, LOW);
     digitalWrite(L, HIGH);
     delay(500);
     Serial.println("a");
     delay(1);
     break;
      case 'b':
     digitalWrite(R, HIGH);
     digitalWrite(L, LOW);
     delay(500);
     Serial.println("b");
     delay(1);
     break;
       case 'c':
     digitalWrite(U, HIGH);
     digitalWrite(D, LOW);
     delay(500);
     Serial.println("c");
     delay(1);
     break;
       case 'd':
     digitalWrite(U, LOW);
     digitalWrite(D, HIGH);
     delay(500);
     Serial.println("d");
     delay(1);
     break;
       case 'e':
     digitalWrite(S, LOW);
     delay(1000);
     digitalWrite(S, HIGH);
     delay(10000);
     digitalWrite(S, LOW);
     Serial.println("e");
     delay(1);
     break;
   }
  
  /*if(bluetooth.available())  // If the bluetooth sent any characters
  {
    // Send any characters the bluetooth prints to the serial monitor
    Serial.print((char)bluetooth.read());  
  }*/
  
  if(Serial.available())  // If stuff was typed in the serial monitor
  {
    // Send any characters the Serial monitor prints to the bluetooth
    bluetooth.print((char)Serial.read());
  }
  // and loop forever and ever!
}
