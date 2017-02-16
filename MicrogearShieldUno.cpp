#include "MicrogearShieldUno.h"

WiFiClient mg_shield_client;
/*************************************** NET PIE GEAR *************************************/

//Constructor of Netpie microgear
Microgear::Microgear(){

}

void Microgear::init(char *appid, char *key, char *secret ,char *alias){

      /* |< Use after debugging mode is ok >| */
      // mySerial.print("AT+MGIN \"");
      // mySerial.print(appip);
      // mySerial.print("\",\"");
      // mySerial.print(key);
      // mySerial.print("\",\"");
      // mySerial.print(secret);
      // mySerial.print("\",\"");
      // mySerial.print(alias);
      // mySerial.println("\"");

      Serial.print("AT+MGIN \"");
      Serial.print(appid);
      Serial.print("\",\"");
      Serial.print(key);
      Serial.print("\",\"");
      Serial.print(secret);
      Serial.print("\",\"");
      Serial.print(alias);
      Serial.println("\"");
} 

  void Microgear::tokensetup(char *token, char *tokensecret){
    /* |< Use after debugging mode is ok >| */
      // mySerial.print("AT+MGST \"");
      // mySerial.print(token);
      // mySerial.print("\",\"");
      // mySerial.print(tokensecret);
      // mySerial.println("\"");

      Serial.print("AT+MGST \"");
      Serial.print(token);
      Serial.print("\",\"");
      Serial.print(tokensecret);
      Serial.println("\"");
  }

  bool Microgear::connect(){
    /* |< Use after debugging mode is ok >| */
      // mySerial.println("AT+MGCN");

      Serial.println("AT+MGCN");

  }

  bool Microgear::disconnect(){
    /* |< Use after debugging mode is ok >| */
      // mySerial.println("AT+MGDC");

      Serial.println("AT+MGDC");
  }

  void Microgear::setalias(char *alias){
    /* |< Use after debugging mode is ok >| */
      // mySerial.print("AT+MGSA \"");
      // mySerial.print(alias);
      // mySerial.println("\"");

      Serial.print("AT+MGSA \"");
      Serial.print(alias);
      Serial.println("\"");
  }

  void Microgear::publish(char *topic,char *data){
    /* |< Use after debugging mode is ok >| */
      // mySerial.print("AT+MGP \"");
      // mySerial.print(topic);
      // mySerial.print("\",\"");
      // mySerial.print(data);
      // mySerial.println("\"");

      Serial.print("AT+MGP \"");
      Serial.print(topic);
      Serial.print("\",\"");
      Serial.print(data);
      Serial.println("\"");
  }

  void Microgear::chat(char *appid,char *data){
    /* |< Use after debugging mode is ok >| */
      // mySerial.print("AT+MGC \"");
      // mySerial.print(appid);
      // mySerial.print("\",\"");
      // mySerial.print(data);
      // mySerial.println("\"");

      Serial.print("AT+MGC \"");
      Serial.print(appid);
      Serial.print("\",\"");
      Serial.print(data);
      Serial.println("\"");
  }

  void Microgear::subscribe(char *topic){
    /* |< Use after debugging mode is ok >| */
      // mySerial.print("AT+MGS \"");
      // mySerial.print(topic);
      // mySerial.println("\"");

      Serial.print("AT+MGS \"");
      Serial.print(topic);
      Serial.println("\"");

  }

  void Microgear::unsubscribe(char *topic){
    /* |< Use after debugging mode is ok >| */
      // mySerial.print("AT+MGUS \"");
      // mySerial.print(topic);
      // mySerial.println("\"");

      Serial.print("AT+MGUS \"");
      Serial.print(topic);
      Serial.println("\"");
  }

  void Microgear::loop(){
    mg_shield_client.transmission();
    
  }


int Microgear::countindex = 0;