#include <SPI.h>
#include <ATTCloudClient.h>
#include <Ethernet.h>
#include "Timer.h"

#define  M2MIO_USERNAME  "<att username>"
#define  M2MIO_PASSWORD  "<att password (MD5 hash of password)>"
#define  MY_DOMAIN       "<att domain>"
#define  MY_STUFF        "<stuff>"
#define  MY_DEVICE_ID    "arduino1"


byte MAC_ADDRESS[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x31, 0xB8 };
EthernetClient ethernetClient;
ATTCloudClient myClient(MQTT_SERVER, 1883, sensorCallback, ethernetClient);

// define the button input pin
const int buttonPin = 2;

int buttonState = 0;
int prevButtonState = 0;

void setup()
{
  // init serial link for debugging
  Serial.begin(9600);

  // setup button pin as input
  pinMode(buttonPin, INPUT);

  // connect to cloud
  Serial.print("ATTClient Connecting...");
  myClient.connect(MY_DEVICE_ID, M2MIO_USERNAME, M2MIO_PASSWORD);
  myClient.setDomainStuffThing(MY_DOMAIN, MY_STUFF, MY_DEVICE_ID);
  Serial.println("connected.");

}

void loop()
{
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // if button state changes, send "button pressed" event to cloud
  if (buttonState == HIGH && prevButtonState == LOW) {
    Serial.println("button");
    myClient.sendKV("button_pressed", (boolean)true);
  }

  prevButtonState = buttonState;
  
  myClient.loop();
}

// handles command arriving (not used in this example)
void cmdRcvdCallback(char* topic, byte* cmd, unsigned int length) { }
