#include <ATTCloudClient.h>

// Longest variable is 32 chars
PROGMEM const prog_uchar   M2MIO_USERNAME[]    = "<user>";
PROGMEM const prog_uchar   M2MIO_PASSWORD[]    = "<MD5 sum of password (32 characters)>";
PROGMEM const prog_uchar  M2MIO_DOMAIN[]       = "<domain>";
PROGMEM const prog_uchar  M2MIO_DEVICE_TYPE[]  = "<device types>";
PROGMEM const prog_uchar  M2MIO_DEVICE_ID[]    = "<device ID>";

#define REPORTING_INTERVAL_MS  3000

ATTCloudClient acc;
ATT3GModemClient c;

// LED PIN
int ledPin = 7;

void cmdCallBack(char *topic, uint8_t* payload, unsigned int len);

void setup() {

  while(!Serial);
  delay(1500);

  Serial.begin(9600); // port to communicate to PC
  Serial1.begin(115200); // port that talks to 3G modem

  // set led pin as output
  pinMode(ledPin, OUTPUT);

  Serial.println(F("LED Control"));

  c = ATT3GModemClient();
  acc = ATTCloudClient(cmdCallBack,c);

  if (!acc.connect(M2MIO_DEVICE_ID,M2MIO_USERNAME,M2MIO_PASSWORD) ) {
   Serial.println(F("Unable to connect to network (12)"));
    //return;
  }

  acc.setDomainStuffThing(M2MIO_DOMAIN,M2MIO_DEVICE_TYPE,M2MIO_DEVICE_ID);

  acc.registerForCommands();
}

void loop() {
  delay(200);
  acc.loop();
}

void cmdCallBack(char *topic, uint8_t* payload, unsigned int len) {
  Serial.println(F("Command Recieved"));

  if (acc.commandCompare("{\"light\":\"on\"}", payload, len)) {
    digitalWrite(ledPin, HIGH);
  } else if (acc.commandCompare("{\"light\":\"off\"}", payload, len)) {
    digitalWrite(ledPin, LOW);
  } else {
    Serial.println(F("No match"));
  }
}
