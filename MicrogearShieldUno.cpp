#include "RingBuf.h"
#include "Arduino.h"	
#include "Print.h"
#include "Client.h"
#include "IPAddress.h"
#include <SoftwareSerial.h>
#include "MicrogearShieldUno.h"

#define buffersize 50

WiFiClass WiFi;

SoftwareSerial mySerial(3, 2);

	WiFiClient::WiFiClient(){
		time = millis();
		mySerial.begin(57600);
		if(countindex <3){
			index = ++countindex;	
		}
		client1 = RingBuf_new(1, buffersize);
		client2 = RingBuf_new(1, buffersize);
		time = millis();
	}	

  int WiFiClient::connect(IPAddress ip, uint16_t port){}
  int WiFiClient::connect(const char *host, uint16_t port){
  	//MGS+CONNECTCLIENT1	
  	mySerial.print("MGS+CONNECTCLIENT");
  	mySerial.print(index);
  	mySerial.print(" ");
  	mySerial.print(host);
  	mySerial.print(",");
  	mySerial.println(port);

  	Serialmanual::readserial(myserialdata);
  	if(strcmp(myserialdata,"CONNECTED\r\n") == 0)return 1;
  	return 0;
  }

  size_t WiFiClient::write(uint8_t b){
  	  return write(&b, 1);
  }
  size_t WiFiClient::write(const uint8_t *buf, size_t size){
  	//MGS+PRINT1 GET /search?q=arduino HTTP/1.0

  	mySerial.print("MGS+PRINT");
  	mySerial.print(index);
  	mySerial.print(" ");
  	mySerial.println((char*)buf);
  	delay(1000);
  	return size;
  }

//Called when available function is invoked use to REQUEST and STORE DATA FROM CLIENT1,2(In ESP8266) to Arduino UNO 
 void WiFiClient::transmission(){
 	if((millis() - time) > 200){
 		time = millis();
 		sendrequest();	
 		getdatafrommyserial();
 	} 	
 }

//Called after transmission is invoked 
 void WiFiClient::sendrequest(){
 	mySerial.print("MGS+READ");
	mySerial.print(index);
	mySerial.print(" ");
	if((index == 1) && (client1->elements < (buffersize-10))){
		mySerial.println(buffersize - client1->elements);
		delay(100);	
	}
	else if((index == 2) && (client2->elements < (buffersize-10))){
		mySerial.println(buffersize - client2->elements);
		delay(100);
	}
 }

//Called after transmission is invoked 
 void WiFiClient::getdatafrommyserial(){
 	if(mySerial.available()){
 		byte header = mySerial.read();
 		int client_num = (header & B11000000);
 		int payload_size = (header & B00111111);
 		if(client_num == 64){
 			for(int count =0; count<payload_size; count++){
 				char a = mySerial.read();
 				client1->add(client1,&a);
 			}
 		}else if(client_num == 128){ 			
 			for(int count = 0;count < payload_size;count++){
 				char b = mySerial.read();
 				
 				client2->add(client2,&b);
 			}
 		}
 	}
 }
  
  //Return Number of available data in buffer 
  int WiFiClient::available(){
  	transmission();
  	if(index == 1){
  		return client1->elements;
  	}
  	if(index == 2){
  		return client2->elements;
  	}
  }

  int WiFiClient::read(){
  	int c;
  	if(index == 1){
  		client1->pull(client1,&c);
  	}
  	if(index == 2){
  		client2->pull(client2,&c);
  	}
  	delay(10);
  	return c;
  }


  int WiFiClient::read(uint8_t *buf, size_t size){
  	for(int count = 0 ; count<size ; count++){
  		if(index == 1){
  			client1->pull(client1,buf[count]);
  		}
  		if(index == 2){
  			client2->pull(client2,buf[count]);
  		}	
  	}
  	delay(10);
  	return count;
  }

  int WiFiClient::peek(){
  	int c;
  	if(index == 1){
  		client1->peek(client1,&c);
  	}
  	if(index == 2){
  		client2->peek(client2,&c);
  	}
  	delay(10);
  	return c;

  }

  void WiFiClient::flush(){}
  void WiFiClient::stop(){
  	//MGS+STOP2
  	mySerial.print("MGS+DISCONN");
  	mySerial.println(index);
  }
  
  uint8_t WiFiClient::connected(){
  	//MGS+CONNSTAT1
  	mySerial.print("MGS+CONNSTAT");
  	mySerial.print(index);
  	Serialmanual::readserial(myserialdata);
  	if(strcmp(myserialdata,"CONNECTED\r\n") == 0)return 1;
  	return 0;
  }	
	WiFiClient::operator bool(){}



void Serialmanual::readserial(char *buf){
	delay(500);
	if(mySerial.available()){
		int count =0;
		while(mySerial.available()){
			char d = mySerial.read();
			*(buf+count) = d;
			count++;
			delay(1);
		}
	}
}

void WiFiClass::begin(const char *ssid, const char *password){
	//MGS+SETUPWIFI AP0001,Password@9
	mySerial.print("MGS+SETUPWIFI ");
	mySerial.print(ssid);
	mySerial.print(",");
	mySerial.println(password);
	delay(500);
}

bool WiFiClass::status(){
//MGS+CHECKSTATUS
	mySerial.println("MGS+CHECKSTATUS");
	Serialmanual::readserial(buffer);
	sscanf(buffer,"%s %s",state,ip);
	if(strcmp(state,"CONNECTED") == 0)return true;
	return false;
}

char* WiFiClass::getip(){
	return ip;
}



//Constructor of Netpie microgear
Netpie_microgear::Netpie_microgear(){
		time = millis();
		mySerial.begin(57600);
		if(countindex <2){
			index = ++countindex;	
		}
		client1 = RingBuf_new(1, buffersize);
		client2 = RingBuf_new(1, buffersize);
		time = millis();
}	






















// char Wifi::stat = NULL;
int WiFiClient::countindex = 0;
int Netpie_microgear::countindex = 0;