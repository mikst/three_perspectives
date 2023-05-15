/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/
int avg1;
int avg2;
int avg3;

int samplesize=10;

int sensorValue1;
int sensorValue2;
int sensorValue3;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  sensorValue1 = analogRead(A5);
  sensorValue2 = analogRead(A4);
  sensorValue3 = analogRead(A3);

  avg1 = (avg1 * (samplesize-1) + sensorValue1)/samplesize;
  avg2 = (avg2 * (samplesize-1) + sensorValue2)/samplesize;
  avg3 = (avg3 * (samplesize-1) + sensorValue3)/samplesize;

  
  // print out the value you read:
  Serial.print(avg1);
  Serial.print(" ");
  Serial.print(avg2);
  Serial.print(" ");
  Serial.print(avg3);
  Serial.print(" ");
  Serial.println();
  delay(10);        // delay in between reads for stability
}
