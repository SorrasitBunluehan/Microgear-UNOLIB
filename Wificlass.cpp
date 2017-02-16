#include "Wificlass.h"
WiFiClass WiFi;

WiFiClass::WiFiClass(){
    microgear_buf = RingBuf_new(1,buffersize);
    client1_buf = RingBuf_new(1, buffersize);
    client2_buf = RingBuf_new(1, buffersize);

}


void WiFiClass::begin(const char *ssid, const char *password){
  mySerial.begin(9600);
  mySerial.print("AT+CW \"");
	mySerial.print(ssid);
	mySerial.print("\",\"");
	mySerial.print(password);
  mySerial.println("\"");
  Serialmanual::clearredundant();
}

bool WiFiClass::status(){
  mySerial.println("AT+CW?");
  Serialmanual::readserial(buffer);
	sscanf(buffer,"%s %s",state,ip);
  Serialmanual::clearredundant();
  if(strcmp(state,"CONNECTED") == 0)return true;
	return false;
}

char* WiFiClass::getip(){
  Serial.println(a);
	return ip;
}

int WiFiClass::get_element(int buf_no){
  switch (buf_no){
    case 0: return microgear_buf->elements;
    case 1: return client1_buf->elements;
    case 2: return client2_buf->elements;
  }
}

void WiFiClass::add_element(int buf_no, char *data){
  switch (buf_no){
    case 0: microgear_buf->add(microgear_buf,&data); break; 
    case 1: client1_buf->add(client1_buf,&data); break; 
    case 2: client2_buf->add(client2_buf,&data); break; 
  }
}

void WiFiClass::pull_element(int buf_no, int c){
   switch (buf_no){
    case 0:  microgear_buf->pull(microgear_buf,c); break;
    case 1:  client1_buf->pull(client1_buf,c); break;
    case 2:  client2_buf->pull(client2_buf,c); break;
  }
}

void WiFiClass::peek_element(int buf_no, char *c){
  switch (buf_no){
    case 0: microgear_buf->peek(microgear_buf,c); break;
    case 1: client1_buf->peek(client1_buf,c); break;
    case 2: client2_buf->peek(client2_buf,c); break;
  }
}





