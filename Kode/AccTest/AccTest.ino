/*
ADXL335
note:vcc-->5v ,but ADXL335 Vs is 3.3V
The circuit:
      5V: VCC
analog 1: x-axis
analog 2: y-axis
analog 3: z-axis
*/
const int xpin = 0;                  // x-axis of the accelerometer
const int ypin = 1;                  // y-axis
const int zpin = 2;                  // z-axis (only on 3-axis models)
void setup()
{
 // initialize the serial communications:
 Serial.begin(9600);
}
void loop()
{
 int x = analogRead(xpin);  //read from xpin
 
 int y = analogRead(ypin);  //read from ypin
 
 int z = analogRead(zpin);  //read from zpin
 
  float zero_G = 512.0; //ADC is 0~1023  the zero g output equal to Vs/2
                      //ADXL335 power supply by Vs 3.3V
  float scale = 102.3;  //ADXL335330 Sensitivity is 330mv/g
                       //330 * 1024/3.3/1000  
  /*
  Serial.print(x); 
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.print(z);  
  Serial.print("\t");
  Serial.println(constrain(map(x,349,281,0,90),0,90));
  Serial.print("\n");
  */

float x1 = ((float)x - 331.5)/65*9.8;
float y1 = ((float)y - 329.5)/68.5*9.8;
float z1 = ((float)z - 340)/68*9.8;

Serial.print(x1);  //print x value on serial monitor
Serial.print("\t");
Serial.print(y1);  //print y value on serial monitor
Serial.print("\t");
Serial.print(z1);  //print z value on serial monitor
Serial.print("\t");
Serial.print( ((9.82f) - (y1 < 0 ? y1 * -1 : y1)) / 9.82 * 90);  //print z value on serial monitor
Serial.print("\n");

delay(500);
}
