#include <ATTCloudClient.h>

// Longest variable is 32 chars
PROGMEM const prog_uchar   M2MIO_USERNAME[]      = "user@email.com";
PROGMEM const prog_uchar   M2MIO_PASSWORD[]      = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";    // MD5 key of password
PROGMEM const prog_uchar  M2MIO_DOMAIN[]      =  "yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy";
PROGMEM const prog_uchar  M2MIO_DEVICE_TYPE[] =	 "things";
PROGMEM const prog_uchar  M2MIO_DEVICE_ID[]   =  "device01";

PROGMEM const prog_uchar M2MIO_CLIENT_ID[] =          "things/device01";

ATTCloudClient acc;
ATT3GModemClient c;

void cmdCallBack(char *topic, uint8_t* payload, unsigned int len);

void setup() {

  while( !Serial) ;
  delay(1500);

  Serial.begin(115200); // port to communicate to PC
  Serial1.begin(115200); // port that talks to 3G modem

  Serial.println(F("M2M Demo Begin (LEO)."));

  c = ATT3GModemClient();
  acc = ATTCloudClient(cmdCallBack,c);

  //acc.test();

  //  Serial.println(F("Debug: 1"));

  if (!acc.connect(M2MIO_CLIENT_ID,M2MIO_USERNAME,M2MIO_PASSWORD) ) {
   Serial.println(F("Unable to connect to network (12)"));
    //return;
  }

  //  acc.publish(M2MIO_DOMAIN,M2MIO_DEVICE_TYPE,M2MIO_DEVICE_ID,"{\"foo\":001}");
  //acc.setDomainStuffThing(M2MIO_DOMAIN,M2MIO_DEVICE_TYPE,M2MIO_DEVICE_ID);
  // acc.sendKV("test1","0001");
  // acc.sendKV("test2",1);
  // acc.sendKV("test3",(boolean)true);

  // acc.startMessage();
  // acc.addKVToMessage("test3",22);
  // acc.endMessage();
  // acc.sendMessage();
   
  //acc.disconnect();

  acc.setDomainStuffThing(M2MIO_DOMAIN,M2MIO_DEVICE_TYPE,M2MIO_DEVICE_ID);
  acc.sendKV("test100",201);
  acc.registerForCommands();

  
}

void cmdCallBack(char *topic, uint8_t* payload, unsigned int len) {
  Serial.println(F("In the cmdCallBack()"));

  Serial.println((char*)payload);
}

void loop() {
  Serial.println("Loop...");
  //acc.publish(M2MIO_DOMAIN,M2MIO_DEVICE_TYPE,M2MIO_DEVICE_ID,"{\"foo\":123}");
  delay(200);
  acc.loop();
}


