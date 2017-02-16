#ifndef WiFiClient_h
	#define WiFiClient_h
	#include "Wificlass.h"
	//#include "RingBuf.h"
	#include "Arduino.h"	
	#include "Client.h"
	#include "IPAddress.h"
	#include "SoftwareSerial.h"
	#include "Serial.h"

	#define buffersize 50
	extern SoftwareSerial mySerial;
	extern WiFiClass WiFi;

	class WiFiClient: public Client {
		public:
		  WiFiClient();
		  // struct RingBuf* client1;
		  // struct RingBuf* client2;
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
#endif