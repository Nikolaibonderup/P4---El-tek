﻿//Først inkluderes ønskede elementer
#include <SoftwareSerial.h>  

//Konstanter initieres
const int buttonPinLeft = 4;     // Knap til venstre
const int buttonPinRight = 5;     // Knap til højre
const int buttonPinUp = 6;     // Knap op
const int buttonPinDown = 7;     // Knap ned
const int buttonPinShoot = 8;     // Knap skyd

// Variabler til registreing af knaptryk
int buttonStateLeft = 0;
int buttonStateRight = 0;
int buttonStateUp = 0;
int buttonStateDown = 0;
int buttonStateShoot = 0;

int bluetoothTx = 2;  // TX-O pin til bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin til bluetooth mate, Arduino D3

Seriel bluetooth opstartes
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);


void setup() {
  // pushbutton's pin sættes til at være input
  pinMode(buttonPinLeft, INPUT);
  pinMode(buttonPinRight, INPUT);
  pinMode(buttonPinUp, INPUT);
  pinMode(buttonPinDown, INPUT);
  pinMode(buttonPinShoot, INPUT);
  //Seriel kommunkation påbegyndes
  Serial.begin(9600);
  bluetooth.begin(115200);  // Bluetooth Silver standard 115200bps
  bluetooth.print("$");  // Print tre gange individuelt for at starte kommando sekvens
  bluetooth.print("$");
  bluetooth.print("$");  //Kommandow sekvens startet
  delay(100);  // Delay for at sikre at den anden Bluesmirf Silver kan nå at svarer med CMD 
  //bluetooth.println("I");
  //bluetooth.println("C,00066686745c");   
  bluetooth.println("U,9600,N");  // baudrate skiftes midlertidigt til 9600, Ingen paritet
  // 115200 baudrate kan være for hurtigt for stabil seriel kommunktion
  bluetooth.begin(9600);  // Start bluetooth seriel at 9600

  Serial.print("Ended Setup");
}

//Værdi til at vurdere om kontrol segmentet har kørt
bool control = 1;

void loop() {
  //Control sekvens og kommunikation påbegyndes 
  if(control){
    bluetooth.print("$$$");delay(1000);
    bluetooth.println("SM,1");delay(1000);
    bluetooth.println("C,00066686745c");delay(15000);
    bluetooth.println("x");delay(15000);

    for(int x = 0; x < 1000; ++x){}; delay(100);
    
    bluetooth.println("---");delay(100);

    control = !control;

    //Serial.print("Ends");
  }
    //Knaptryk registreres
  buttonStateLeft = digitalRead(buttonPinLeft);
  buttonStateRight = digitalRead(buttonPinRight);
  buttonStateUp = digitalRead(buttonPinUp);
  buttonStateDown = digitalRead(buttonPinDown);
  buttonStateShoot = digitalRead(buttonPinShoot);

//Alt efter hvilken knap som er blevet trykket sendes en "kommando karakter" til vores kanontårn
 if (buttonStateLeft == HIGH){
      bluetooth.print((char)'a');
      Serial.println('a');
      delay(1000);
    }
 else if(buttonStateRight == HIGH){
      bluetooth.print((char)'b');
      Serial.println('b');
      delay(1000);
 }
 else if(buttonStateUp == HIGH){
      bluetooth.print((char)'c');
      Serial.println('c');
      delay(1000);
 }
 else if(buttonStateDown == HIGH){
      bluetooth.print((char)'d');
      Serial.println('d');
      delay(1000);
 }
  else if(buttonStateShoot == HIGH){
      bluetooth.print((char)'e');
      Serial.println('e');
      delay(1000);
  }
  if(bluetooth.available())  // Hvis en karakter er blevet sendt med bluetooth udføres følgene:
  {
    // Alle karatere som er blevet sendt gennem bluetooth printes i serial monitor.
    Serial.print((char)bluetooth.read());  
  }
  if(Serial.available())  // Hvis noget er blevet skrevet i serial monitoren:
  {
    // sendes dette til bluetooth elementet og printes.
    
  }
   else {
    // Sker der ikke noget
  }
}
