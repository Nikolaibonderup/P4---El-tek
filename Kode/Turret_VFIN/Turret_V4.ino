//Først inkluderes ønskede elementer
#include <SoftwareSerial.h>  

//Værdier til pins oprettes
const int interruptPin = 2; //Interrupt sættes til INT0
int bluetoothTx = 3;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 4;  // RX-I pin of bluetooth mate, Arduino D3
const int R = 8;   //Drej til venstre
const int L = 9;   //Drej til højre
const int U = 10;   //Op
const int D = 11;   //Ned
const int S = 12;   //Skyd
const int LedPin = 13; //Standard ombordværende LEDPIN

volatile int state = LOW;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  //Seriel kommunikation påbegyndes:
  Serial.begin(9600);  // Serial monitor påbegyndes ved 9600bps
  bluetooth.begin(115200);  // Bluetooth "Mate" starter som standard to 115200bps
  bluetooth.print("$");  // Print et dollartegn tre gange individuelt for at starte kommandosekvensen
  bluetooth.print("$");
  bluetooth.print("$");  // Kommando sekvens påbegyndt
  delay(100);  // En kort pause, for at sikre at mate sender CMD
  bluetooth.println("U,9600,N");  // Baudrate sættes midlertidigt til 9600
  bluetooth.println("SM,0");
  // 115200 kan være for hurtigt til pålidelig kommunikation
  bluetooth.begin(9600);  // Start bluetooth serial ved 9600
  pinMode(R, OUTPUT); //Pinmodes bestemmes
  pinMode(L, OUTPUT);
  pinMode(U, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(S, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin),blink,CHANGE); // interrupt opsættes
  pinMode(LedPin,OUTPUT);
  pinMode(interruptPin,INPUT_PULLUP); //7Standard interrupt pin bruges (INT 0, Pin 2)
}

void blink(){//LED på boardet baseret på interrupt
  state = !state;
}


void loop()
{
    //Alle H-bro pins sættes til at være LOW for at undgå problemer med flere HIGH's ad gangen
    digitalWrite(R, LOW);
    digitalWrite(L, LOW);
    digitalWrite(U, LOW);
    digitalWrite(D, LOW);
    digitalWrite(S, LOW);
  if(bluetooth.available())//Hvis der er kommunikation med bluetooth, start switch
    switch ((char)bluetooth.read()){
      case 'a'://Hvis Turret har modtaget char: a, drej til venstre i 500ms
     digitalWrite(R, LOW);
     digitalWrite(L, HIGH);
     digitalWrite(LedPin, state); //Hvis der drejes med venstre tændes LED
     delay(250);
     Serial.println("a");
     delay(1);
     break;
      case 'b'://Hvis Turret har modtaget char: b, drej til højre i 500ms
     digitalWrite(R, HIGH);
     digitalWrite(L, LOW);
     delay(250);
     Serial.println("b");
     delay(1);
     break;
       case 'c'://Hvis Turret har modtaget char: c, panorer op i 500ms
     digitalWrite(U, HIGH);
     digitalWrite(D, LOW);
     delay(1000);
     Serial.println("c");
     delay(1);
     break;
       case 'd'://Hvis Turret har modtaget char: d, panorer ned i 500ms
     digitalWrite(U, LOW);
     digitalWrite(D, HIGH);
     delay(1000);
     Serial.println("d");
     delay(1);
     break;
       case 'e'://Hvis Turret har modtaget char: e, tænd for relæ til at skyde i 10s
     digitalWrite(S, LOW);
     delay(1000);
     digitalWrite(S, HIGH);
     delay(1000);
     digitalWrite(S, LOW);
     Serial.println("e");
     delay(1);
     break;
   }
  
  if(Serial.available())  // Hvis der er skrevet noget i serial monitor:
  {
    // Printes dette til bluetooth serial.
    bluetooth.print((char)Serial.read());
  }
}
