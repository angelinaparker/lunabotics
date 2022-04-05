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

int pin = 7;          // OUT pin of ACHS-7121 Current Sensor is connected to analog pin 7 of the Arduino. 
int value = 0;
int voltage = 1023;   // default max value that can be read is 4.9mv per unit  

void setup(){
  Serial.begin(9600);
}

void loop(){
  value = analogRead(pin);    // read the input pin
  Serial.println(val);        // output the value for testing purposes
  
  // if statement to stop motor if current sensor reads a certain voltage
  if (value >= voltage) {       
     // stop motor
     break;
  }
}
