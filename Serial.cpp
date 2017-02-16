#include "Serial.h"

SoftwareSerial mySerial(3, 2);

void Serialmanual::readserial(char *buf){
	unsigned long timeout = millis();
	while(true){
		if(mySerial.available()){
			break;
		}else if(millis() - timeout > 5000){
			Serial.println("Received data Time out!!");
			break;
		}
	}
	int count =0;
	while(mySerial.available()){
		char d = mySerial.read();
		*(buf+count) = d;
		count++;
		delay(10);
	}

}

void Serialmanual::clearredundant(){
	unsigned long timeout = millis();
	while(true){
		if(mySerial.available()){
			break;
		}else if(millis() - timeout > 5000){
			Serial.println("Clear Redundant Time out!!");
			break;
		}
	}

	if(mySerial.available()){
		while(mySerial.available()){
			mySerial.read();
			delay(10);	
		}
		Serial.println("Successfull clear redundant data");
	}
}





