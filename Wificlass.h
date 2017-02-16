#ifndef WiFiClass_h
	#define WiFiClass_h

	#include "RingBuf.h"
	#include "Arduino.h"
	#include "Serial.h"
	#include "SoftwareSerial.h"
	#include "Serial.h"
	
	#define buffersize 50
	extern SoftwareSerial mySerial;
	static struct RingBuf* microgear_buf;
    static struct RingBuf* client1_buf;
    static struct RingBuf* client2_buf;

	class WiFiClass{
		public:
		   int a;
		   WiFiClass();
		   void begin(const char *ssid, const char *password);
		   bool status();
		   char* getip();
		   static int get_element(int buf_no);
		   static void add_element(int buf_no, char *data);
		   static void pull_element(int buf_no , int c);
		   static void peek_element(int  buf_no, char *c);
		private:
		   char buffer[150];
		   char state[20];
		   char ip[20];
	};
	extern WiFiClass WiFi;
#endif