#ifndef Serial_h
	#define Serial_h
	#include <SoftwareSerial.h>
	#include "Arduino.h"

	class Serialmanual{
		public:
		  	static void readserial(char *buf);
		  	static void clearredundant();
	};
#endif