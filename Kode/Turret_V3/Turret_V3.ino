//Først inkluderes ønskede elementer
#include <SoftwareSerial.h>  

//Værdier til pins oprettes

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
  //Seriel kommunikation påbegyndes:
  Serial.begin(9600);  // Serial monitor påbegyndes ved 9600bps
  bluetooth.begin(115200);  // Bluetooth "Mate" starter som standard to 115200bps
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
     delay(500);
     Serial.println("a");
     delay(1);
     break;
      case 'b'://Hvis Turret har modtaget char: b, drej til højre i 500ms
     digitalWrite(R, HIGH);
     digitalWrite(L, LOW);
     delay(500);
     Serial.println("b");
     delay(1);
     break;
       case 'c'://Hvis Turret har modtaget char: c, panorer op i 500ms
     digitalWrite(U, HIGH);
     digitalWrite(D, LOW);
     delay(500);
     Serial.println("c");
     delay(1);
     break;
       case 'd'://Hvis Turret har modtaget char: d, panorer ned i 500ms
     digitalWrite(U, LOW);
     digitalWrite(D, HIGH);
     delay(500);
     Serial.println("d");
     delay(1);
     break;
       case 'e'://Hvis Turret har modtaget char: e, tænd for relæ til at skyde i 10s
     digitalWrite(S, LOW);
     delay(1000);
     digitalWrite(S, HIGH);
     delay(10000);
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
