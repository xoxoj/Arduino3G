#include <ATTCloudClient.h>

// Longest variable is 32 chars
PROGMEM const prog_uchar   M2MIO_USERNAME[]      = "mikesutton@gmail.com";
PROGMEM const prog_uchar   M2MIO_PASSWORD[]      = "1eef665a480de5611d24d69bbbf3f4a2";    // MD5 key of password
PROGMEM const prog_uchar  M2MIO_DOMAIN[]      =  "c7a7258f3eaf0df06f3feb8da7948b7b";
PROGMEM const prog_uchar  M2MIO_DEVICE_TYPE[] =	 "things";
PROGMEM const prog_uchar  M2MIO_DEVICE_ID[]   =  "device02";

PROGMEM const prog_uchar M2MIO_CLIENT_ID[] =          "things/device02";



ATTCloudClient acc;
ATT3GModemClient c;


//#define AT_RESPONSE_LEN 130
//char response[AT_RESPONSE_LEN];

void cmdCallBack(char *topic, uint8_t* payload, unsigned int len);

void setup() {
  //char tmpBuf[50];
  
  Serial.begin(115200);
  // Serial.print("size of acc: ");
  // Serial.println(sizeof(acc));
  // Serial.print("size of c: ");
  // Serial.println(sizeof(c));
  Serial.println(F("M2M Demo Begin."));
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
  //Serial.println(F("In the cmdCallBack()"));
  //char tmp[5];
  //sprintf(tmp,"l:%d",len);
  //Serial.println(tmp);
  //Serial.println((char*)payload);  // this gets sent to modem and can
				   // fill buffer and generally
				   // confuse matters

  sendATcommand("AT","OK",2000);
  delay(500);
  //while (Serial.available() > 0) Serial.read();

}

void loop() {
  //Serial.println("Loop...");
  //acc.publish(M2MIO_DOMAIN,M2MIO_DEVICE_TYPE,M2MIO_DEVICE_ID,"{\"foo\":123}");
  delay(200);
  acc.loop();
}


