#include <SPI.h>
#include <ATTCloudClient.h>
#include <Ethernet.h>
#include "Timer.h"

#define  M2MIO_USERNAME  "<att username>"
#define  M2MIO_PASSWORD  "<att password (MD5 hash of password)>"
#define  MY_DOMAIN       "<att domain>"
#define  MY_STUFF        "<stuff>"
#define  MY_DEVICE_ID    "arduino1"
#define REPORTING_INTERVAL_MS  3000

Timer t;

byte MAC_ADDRESS[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
EthernetClient ethernetClient;
ATTCloudClient myClient(MQTT_SERVER, 1883, sensorCallback, ethernetClient);

int sensorPin = A0;   // Sensing voltage on analog pin 0
int sensorValue = 0;  // sensor reading

void setup()
{
  // init serial link for debugging
  Serial.begin(9600);

  // connect to cloud server
  Serial.print("ATT Client Connecting...");
  myClient.connect(MY_DEVICE_ID, M2MIO_USERNAME, M2MIO_PASSWORD);
  myClient.setDomainStuffThing(MY_DOMAIN, MY_STUFF, MY_DEVICE_ID);
  Serial.print("connected.");
  Serial.println();

  // setup timer to publish every 1 second
  int sensorEvent = t.every(REPORTING_INTERVAL_MS, getSensorValue);
}

void loop()
{
  t.update();  
  myClient.loop();
}

void getSensorValue() {
  Serial.println("sensor read");

  // read value from sensor
  sensorValue = analogRead(sensorPin);    
  
  // send key-value pair to server  (sensor_val:<value>)
  myClient.sendKV("sensor_val", sensorValue);
}

// handles command arriving (not used in this example)
void cmdRcvdCallback(char* topic, byte* cmd, unsigned int length) { }
