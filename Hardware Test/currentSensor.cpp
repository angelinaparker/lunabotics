/*
analogRead()
Reads the value from the specified analog pin. The Arduino board contains a 6 channel (8 channels on the Mini and Nano, 16 on the Mega), 
10-bit analog to digital converter. This means that it will map input voltages between 0 and 5 volts into integer values between 0 and 1023. 
This yields a resolution between readings of: 5 volts / 1024 units or, .0049 volts (4.9 mV) per unit. The input range and resolution can be 
changed using analogReference().
It takes about 100 microseconds (0.0001 s) to read an analog input, so the maximum reading rate is about 10,000 times a second.

Syntax
analogRead(pin)

Parameters
pin: the number of the analog input pin to read from (0 to 5 on most boards, 0 to 7 on the Mini and Nano, 0 to 15 on the Mega)

Returns
int (0 to 1023)
*/

#include <Servo.h>

int pin = 6;          // OUT pin of ACHS-7121 Current Sensor is connected to analog pin 7 of the Arduino. 
int value = 0;
int voltage = 1023;   // default max value that can be read is 4.9mv per unit 
byte servoPin = 7;
Servo servo; 

void setup(){
  Serial.begin(9600);
  servo.attach(servoPin);
  servo.writeMicroseconds(1500); // send "stop" signal to ESC.
  delay(7000); // delay to allow the ESC to recognize the stopped signal
}

void loop(){
  int signal=1500; // Set signal value, which should be between 1100 and 1900
  int value = analogRead(pin);
  float voltage = (value*5)/1023.0;
  //float current = (voltage - 2.5) / 0.185;
  servo.writeMicroseconds(signal); // Send signal to ESC.
  Serial.println(voltage);
  delay(200); 
  if(voltage >=1.68)
  {
    signal == 1500;
  }
}