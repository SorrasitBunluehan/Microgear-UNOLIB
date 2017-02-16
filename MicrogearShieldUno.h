#ifndef MicrogearShieldUno_h
	#define MicrogearShieldUno_h
	#include "WiFiclass.h"
	#include "RingBuf.h"
	#include "Arduino.h"	
	#include "Print.h"
	#include "Client.h"
	#include "IPAddress.h"
	#include "Wificlient.h"
	#include "Serial.h"
	
	using namespace std;
	
	extern WiFiClass WiFi;
	


class Microgear{

public:
   Microgear();

   void init(char *appid, char *key, char *secret ,char *alias);
   void tokensetup(char *token, char *tokensecret);
   bool connect();
   bool disconnect();
   void setalias(char *alias);
   void publish(char *topic,char *data);
   void chat(char *appid,char *data);
   void subscribe(char *topic);
   void unsubscribe(char *topic);
   void loop();

private:
	  struct RingBuf* microgear_buf;
	  static int countindex;
	  int index;
	  char myserialdata[30];
	  char ip[16];
	  char state;
	  unsigned long time;
	  uint8_t getFirstSocket();
};





#endif