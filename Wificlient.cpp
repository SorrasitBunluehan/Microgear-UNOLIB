#include "Wificlient.h"

WiFiClient::WiFiClient(){
		time = millis();
		// mySerial.begin(115200);
		if(countindex <4){
			index = countindex++;	
		}
		// client1 = RingBuf_new(1, buffersize);
		// client2 = RingBuf_new(1, buffersize);
		time = millis();
}	

int WiFiClient::connect(IPAddress ip, uint16_t port){}
int WiFiClient::connect(const char *host, uint16_t port){
  	mySerial.print("AT+CCS");
  	mySerial.print(index);
  	mySerial.print(" \"");
  	mySerial.print(host);
  	mySerial.print("\",");
  	mySerial.println(port);

    Serial.print("AT+CCS");
    Serial.print(index);
    Serial.print(" \"");
    Serial.print(host);
    Serial.print("\",");
    Serial.println(port);

  	Serialmanual::readserial(myserialdata);
  	if(strncmp(myserialdata,"CONNECTED\r\n",11) == 0)return 1;
  	return 0;
}

size_t WiFiClient::write(uint8_t b){
	  return write(&b, 1);
}

size_t WiFiClient::write(const uint8_t *buf, size_t size){
  	mySerial.print("AT+CP");
  	mySerial.print(index);
  	mySerial.print(" \"");
    for(int count =0; count < size ;count++){
      mySerial.print((char)*(buf+count));
    }
    mySerial.println("\"");
    Serialmanual::readserial(myserialdata);
    if(strncmp(myserialdata,"SUCCESS\r\n",9) == 0)return size;
    return 0;
}

//Called when available function is invoked use to REQUEST and STORE DATA FROM CLIENT1,2(In ESP8266) to Arduino UNO 
void WiFiClient::transmission(){
  	if((millis() - time) > 1000){
    		time = millis();
        getdatafrommyserial();
    		sendrequest();	
    		
  	} 
}

//Called after transmission is invoked 
void WiFiClient::sendrequest(){
    for(int count =1; count < 3; count ++){
        if((count == 1) && (WiFiClass::get_element(1) < (buffersize-10))){
          //Serial.println("Sending request data to client1");
            mySerial.print("AT+CRTA");
            mySerial.print(count);
            mySerial.print(" ");
            mySerial.println(buffersize - WiFiClass::get_element(1));
            delay(1000); 
        }
        else if((count == 2) && (WiFiClass::get_element(2)< (buffersize-10))){
          //Serial.println("Sending request data to client2");
            mySerial.print("AT+CRTA");
            mySerial.print(count);
            mySerial.print(" ");
            mySerial.println(buffersize - WiFiClass::get_element(2));

            // Serial.print("AT+CRTA");
            // Serial.print(count);
            // Serial.print(" ");
            // Serial.println(buffersize - client2->elements);
            delay(1000);
        }
    }
}

//Called after transmission is invoked 
void WiFiClient::getdatafrommyserial(){
    
// for(int i = 0; i <3 ; i++){
//    unsigned long timeout = millis();

//     while(true){
//       if(mySerial.available()){
//         break;
//       }else if(millis() - timeout > 2500){
//         //Serial.println("Interupt routien Time out!!");
//         break;
//       }
//     }

    while(mySerial.available()){
        byte header = mySerial.read();
        int client_num = (header & B11100000);
        int payload_size = (header & B00011111);

        Serial.print("Received data client num: ");
        Serial.println(client_num);

        if(client_num == 32){
          // Serial.print("Payload size: ");
          // Serial.println(payload_size);
          Serial.print("Data to client1: ");
          //   for(int count =0; count<payload_size; count++){
          //       char a = mySerial.read();
          //       Serial.print(a);
          //       client1->add(client1,&a);
          //   }
          Serial.print("Inside loop client1");
            for(int count =0; count<payload_size; count++){
                char a = mySerial.read();
                //client1->add(client1,&a);
               WiFiClass::add_element(1, &a);
                
                delay(100);
            }
            Serial.print("Clinet1 buffer: ");
            Serial.println(WiFiClass::get_element(1));
        }else if(client_num == 64){      
            // for(int count = 0;count < payload_size;count++){
            //     char b = mySerial.read();           
            //     client2->add(client2,&b);
            // }
           Serial.print("Inside loop client2");     
            for(int count = 0;count < payload_size;count++){
                char b = mySerial.read(); 
                WiFiClass::add_element(2, &b); 
                // client2->add(client2,&b);   
                 delay(100);     
            }
            Serial.print("Clinet2 buffer: ");
          Serial.println(WiFiClass::get_element(2));
        }
    }
    // Serial.print("Clinet1 buffer after loop: ");
    // Serial.println(WiFiClass::get_element(1));
    // Serial.print("Clinet2 buffer after loop: ");
    // Serial.println(WiFiClass::get_element(2));
}
   
// }
  
  //Return Number of available data in buffer 
int WiFiClient::available(){
  	if(index == 1){
      Serial.print("Clinet1 buffer: ");
      Serial.println(WiFiClass::get_element(1));
  	   	return (WiFiClass::get_element(1));
  	}
  	if(index == 2){
      Serial.print("Clinet2 buffer: ");
      Serial.println(WiFiClass::get_element(2));
  		  return (WiFiClass::get_element(2));
  	}
}

int WiFiClient::read(){
  	int c;
  	if(index == 1){
  		  WiFiClass::pull_element(1, &c);
        //client1->pull(client1,&c);
  	}
  	if(index == 2){
      WiFiClass::pull_element(2, &c);
  		  //client2->pull(client2,&c);
  	}
  	delay(10);
  	return c;
}


int WiFiClient::read(uint8_t *buf, size_t size){
    int count,buf1,buf2;
  	for(count = 0 ; count<size ; count++){
  		if(index == 1){
         WiFiClass::pull_element(1, &buf1);
    			//client1->pull(client1,&buf1);
          buf[count] = buf1;
  		}
  		if(index == 2){
        WiFiClass::pull_element(2, &buf2);
         // client2->pull(client2,&buf2);
          buf[count] = buf2;
  		}	
  	}
  	delay(10);
  	return count;
}

int WiFiClient::peek(){
  	int c;
  	if(index == 1){
      WiFiClass::peek_element(1, c);
  		  //client1->peek(client1,c);
  	}
  	if(index == 2){
        WiFiClass::peek_element(2, c);
  		  //client2->peek(client2,c);
  	}
  	delay(10);
  	return c;
}

void WiFiClient::flush(){}
void WiFiClient::stop(){
  	mySerial.print("AT+CD");
  	mySerial.println(index);
}
  
uint8_t WiFiClient::connected(){
  	mySerial.print("AT+CCS");
  	mySerial.print(index);
    mySerial.println("?");
  	Serialmanual::readserial(myserialdata);
  	if(strcmp(myserialdata,"CONNECTED\r\n") == 0)return 1;
  	return 0;
}

WiFiClient::operator bool(){}
int WiFiClient::countindex = 0;