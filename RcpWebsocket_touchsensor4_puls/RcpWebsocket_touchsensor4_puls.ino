#include <WiFi.h>

// include RabbitControl protocol
#include <RCP.h>
// Transporter using ESPAsyncWebserver:
// https://github.com/me-no-dev/ESPAsyncWebServer
#include <RcpESP32WebsocketServerTransporter.h>

// wifi setup
const char* ssid = "Puppe";
const char* password = "puppe2010";
//const char* ssid = "pattern";
//const char* password = "pattern2022";
//const char* ssid = "another";
//const char* password = "6214766256629834";
//const char* ssid = "ladenlokal";
//const char* password = "puppe2010";

// create a websocket transporter on port 10000
RcpESP32WebsocketServerTransporter transporter(10000);

// create a rcp server with transporter
RcpServer rcpServer(transporter);

// our exposed variables
RcpInt sensor1;
RcpInt sensor2;
RcpInt sensor3;
RcpInt sensor4;




// other variables
int val[4];
int gPin[] = {25,26,27,14};
int sPin[] = {A0,A3,A6,A7};
int Num_of_Pins = 4;
int cnt;
long lastMillis;


void setup()
{
  for (int i=0; i<Num_of_Pins; i++){
  pinMode(gPin[i], OUTPUT);
  digitalWrite(gPin[i],HIGH);
  }
  
  // Start Serial port
  Serial.begin(115200);

  // Connect to access point
  Serial.println("Connecting");
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }

  // Print our IP address
  Serial.println("Connected!");
  Serial.print("My IP address: ");
  Serial.println(WiFi.localIP());

  transporter.begin();
 
  
  sensor1 = rcpServer.exposeInt("sensor1");
  sensor1.setReadonly(true);
  sensor1.setMinMax(0, 4095);

  sensor2 = rcpServer.exposeInt("sensor2");
  sensor2.setReadonly(true);
  sensor2.setMinMax(0, 4095);

  sensor3 = rcpServer.exposeInt("sensor3");
  sensor3.setReadonly(true);
  sensor3.setMinMax(0, 4095);

  sensor4 = rcpServer.exposeInt("sensor4");
  sensor4.setReadonly(true);
  sensor4.setMinMax(0, 4095);
 
  // update the server
  rcpServer.update();
  lastMillis = millis();
}

void loop()
{
  // read websocket
  transporter.read();  
  // all rcp values are up to date after transporter.read()
  
// reading happens every 100ms
long currentMillis = millis();
if (currentMillis - lastMillis  > 30){
  lastMillis = currentMillis; // mark the current timing as lastMillis
  
  // toggle which sensor to read.
  cnt++;
  cnt = cnt%Num_of_Pins;

  //smooth the reading by taking samplesize
  int sampleSize=5;
  int avg[Num_of_Pins];
  for (int i=0; i<Num_of_Pins; i++){
    avg[i] = val[i];
  }
  
  for (int l=0; l<sampleSize; l++){
  digitalWrite(gPin[cnt],LOW); // connect the matching touch pad to GND
  val[cnt] = analogRead(sPin[cnt]);
  avg[cnt] = (avg[cnt]*(sampleSize-1)+val[cnt])/sampleSize;
  val[cnt]=avg[cnt];  
  }
  digitalWrite(gPin[cnt],HIGH); // set back the matching touch pad to nonGND
  
  sensor1 = val[0];
  sensor2 = val[1];
  sensor3 = val[2];
  sensor4 = val[3];
}
  
  // update server
  rcpServer.update();
delay(10);
}
