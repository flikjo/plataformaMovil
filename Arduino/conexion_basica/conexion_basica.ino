#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <WebSocketsClient.h>


ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;

int PIN_TRG = 10;
int PIN_ECHO = 9;

float tiempo;
float distancia;

// SETUP
void setup() {
  
  Serial.begin(115200);

  WiFiMulti.addAP("LUZMARINA", "+6-5LJB%=*M4j4l452. 47");

  while (WiFiMulti.run() != WL_CONNECTED) {

    Serial.println("connecting...");
    delay(1000);
  }

  webSocket.begin("192.168.0.5", 3009, "/socket.io/?transport=websocket");
  //webSocket.begin("192.168.0.5", 3009, "/socket.io/?EIO=4");
  webSocket.onEvent(webSocketEvent);

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);  
  pinMode(5, OUTPUT);  
  pinMode(4, OUTPUT);

  pinMode(PIN_TRG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  /*sensor;*/
}

// LOOP
void loop() {  
  webSocket.loop();
  
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {

  Serial.println("=========================");

  sensor;
  switch(type) {

    case WStype_TEXT: {
        Serial.printf("[WSc] get text: %s\n", payload);
  
  
        String response = (char*)payload;
    
        if (response.indexOf("backward") > 0) {
          Serial.printf("hacia atras");
          digitalWrite(13, HIGH);
          delay(1000);
          digitalWrite(13, LOW);
        }
    
        if (response.indexOf("rightward") > 0) {
          Serial.printf("hacia derecha");
          digitalWrite(5, HIGH);
          delay(1000);
          digitalWrite(5, LOW);
        }
    
        if (response.indexOf("forward") > 0) {
          Serial.printf("hacia delante");
          digitalWrite(12, HIGH);
          delay(1000);
          digitalWrite(12, LOW);
        }
    
        if (response.indexOf("leftward") > 0) {
          Serial.printf("hacia izquierda");
          digitalWrite(4, HIGH);
          delay(1000);
          digitalWrite(4, LOW);
        }
        
      }
      break;
      
    }

}
void sensor(){
  digitalWrite(PIN_TRG, LOW);
  delayMicroseconds(4);

  digitalWrite(PIN_TRG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRG, LOW);

  tiempo = pulseIn(PIN_ECHO, HIGH);
  distancia = tiempo/58.3;

  Serial.println(distancia);

  delay(1000);
}
