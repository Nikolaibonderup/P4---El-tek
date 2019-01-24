#include <SoftwareSerial.h>  
#include <Stepper.h>

  //http://www.arduino.cc/en/Tutorial/Button
  // constants won't change. They're used here to set pin numbers:
const int buttonPin = 4;     // the number of the pushbutton pin
const int ledPin = 13;

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

//stepper setup
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// Rotationer etableres med pins 8 til 11:
Stepper StepFor(stepsPerRevolution, 8, 9, 10, 11);
Stepper StepBac(stepsPerRevolution, 11, 10, 9, 8);
// Rotationer etableres med pins 8 til 11:
Stepper StepUp(stepsPerRevolution, 4, 5, 6, 7);
Stepper StepDown(stepsPerRevolution, 7, 6, 5, 4);

int stepCount = 0;         // number of steps the motor has taken

// Montering: grøn cennector på h bro: grøn til null på den tre-sets gule connector med den sorte sprit streg
// og gul til gul ledning på samme
// Blå connector: gul til null og grøn til gul

//Montering stor: Sort til OUT4, Grøn til OUT3, Blå til OUT2, Rød til OUT1

//Montering af L298N: PIN 8 til input 1, PIN 9 til input 2, PIN 10 til input 3, PIN 11 til input 4.


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

}

void loop()
{
  if(bluetooth.available())
    switch ((char)bluetooth.read()){
      case 'a':
     for (stepCount == 0;stepCount<200; 1){
     // step one step:
     StepBac.step(1);
     Serial.print("steps:");
     Serial.println(stepCount);
     stepCount++;
     delay(1);
     }
     Serial.println("done");
      stepCount = 0;
     break;
      case 'b':
      for (stepCount == 0;stepCount<200; 1){
     // step one step:
     StepFor.step(1);
     Serial.print("steps:");
     Serial.println(stepCount);
     stepCount++;
     delay(1);
    }
    Serial.println("done");
    stepCount = 0;
    break;
    case 'c':
      for (stepCount == 0;stepCount<200; 1){
     // step one step:
     StepUp.step(1);
     Serial.print("steps:");
     Serial.println(stepCount);
     stepCount++;
     delay(1);
    }
    Serial.println("done");
    stepCount = 0;
    break;
  case 'd':
      for (stepCount == 0;stepCount<200; 1){
     // step one step:
     StepDown.step(1);
     Serial.print("steps:");
     Serial.println(stepCount);
     stepCount++;
     delay(1);
    }
    Serial.println("done");
    stepCount = 0;
    break;
    case 'e':
     //skal skyde på en eller anden måde
     delay(1);
    }
    Serial.println("done");
    stepCount = 0;
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
