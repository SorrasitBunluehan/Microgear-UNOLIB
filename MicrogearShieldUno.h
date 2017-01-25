
#define MicrogearShieldUno_h
#include "RingBuf.h"
#include "Arduino.h"	
#include "Print.h"
#include "Client.h"
#include "IPAddress.h"
#include <SoftwareSerial.h>
using namespace std;


class WiFiClient: public Client {
	public:
	  WiFiClient();
	  struct RingBuf* client1;
	  struct RingBuf* client2;
	  uint8_t status();
	  virtual int connect(IPAddress ip, uint16_t port);
	  virtual int connect(const char *host, uint16_t port);
	  virtual size_t write(uint8_t b);
	  virtual size_t write(const uint8_t *buf, size_t size);
	  void transmission ();
	  void sendrequest();
	  void getdatafrommyserial();
	  virtual int available();
	  virtual int read();
	  virtual int read(uint8_t *buf, size_t size);
	  virtual int peek();
	  virtual void flush();
	  virtual void stop();
	  virtual uint8_t connected();
	  virtual operator bool(); 
	  
	private:
	  static int countindex;
	  int index;
	  char myserialdata[30];
	  char ip[16];
	  char state;
	  unsigned long time;
	  uint8_t getFirstSocket();
};

class Serialmanual{
	public:
	  static void readserial(char *buf) ;
};


class WiFiClass{
	public:
	   void begin(const char *ssid, const char *password);
	   bool status();
	   char* getip();
	private:
	   char buffer[30];
	   char state[5];
	   char ip[20];
};

/*
MGS+NPCONNECT
MGS+NPDISCONNECT
MGS+TOKENSETUP RKJy30tYkUKoXa7G oWfxRNqRaXdwffVdFvuU27qJqr1KNpIy
MGS+INIT HelloNetpie1 YhtHPvlmMxL5yJB YphWgyUI31q8sEMu6qtNrIPn1 ESP_microgear1
MGS+SETALIAS 
MGS+PUBLISH 
MGS+SUBSCRIBE 
MGS+UNSUBSCRIBE 
MGS+CHAT 
*/

class Netpie_microgear{

public:
   Netpie_microgear();
   void init(char *appid, char *key, char *secret ,char *alias) ;
   void tokensetup(char *token, char *toketsecret);
   bool connect();
   bool disconnect();
   void setalias(char *alias);
   void publish(char *topic,char *data);
   void chat(char *appid,char *data);
   void subscribe(char *topic);
   void unsubscribe(char *topic);

private:
  static int countindex;



};








extern WiFiClass WiFi;


