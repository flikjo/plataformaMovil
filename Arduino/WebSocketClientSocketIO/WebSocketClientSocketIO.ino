#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <WebSocketsClient.h>
#include <SocketIOclient.h>

#include <ArduinoJson.h>

ESP8266WiFiMulti WiFiMulti;
SocketIOclient socketIO;

#define EnableA   15   // Enable motors Right        GPIO15(D8)        
#define EnableB   4    // Enable motors Left         GPIO4 (D2)
#define IN1  13        // L298N in1 motors Right     GPIO13(D7)
#define IN2  12        // L298N in2 motors Right     GPIO12(D6)
#define IN3  14        // L298N in3 motors Left      GPIO14(D5)
#define IN4  0         // L298N in4 motors Left      GPIO0 (D3)      

#define PIN_TRG D1
#define PIN_ECHO D0

long tiempo;
int distancia;
#define USE_SERIAL Serial1

void setup() {

  pinMode(EnableA, OUTPUT);
  pinMode(EnableB, OUTPUT);  
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT); 

  pinMode(PIN_TRG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  
  Serial.begin(115200);

  WiFiMulti.addAP("LUZMARINA", "+6-5LJB%=*M4j4l452. 47");
  //WiFiMulti.addAP("manuel", "3115574493");
  
  while (WiFiMulti.run() != WL_CONNECTED) {

    Serial.println("connecting...");
    delay(1000);
  }
    // server address, port and URL
    // "/socket.io/?EIO=4", compatibilidad con ultima versión de socket.io
  socketIO.begin("35.168.1.210", 3009, "/socket.io/?EIO=4");

    // event handler
  socketIO.onEvent(socketIOEvent);
  
  
}

void loop() {
    socketIO.loop();
    
    digitalWrite(PIN_TRG, LOW);  //para generar un pulso limpio ponemos a LOW 4us
    delayMicroseconds(4);
   
    digitalWrite(PIN_TRG, HIGH);  //generamos Trigger (disparo) de 10us
    delayMicroseconds(10);
    digitalWrite(PIN_TRG, LOW);
   
    tiempo = pulseIn(PIN_ECHO, HIGH);
    distancia = (tiempo/2) /29; // (tiempo * 0.034) / 2;
    delay(10);
    //Serial.println(distancia);
   
    if(distancia >= 10 && distancia <= 15){
        Serial.println(distancia);     
        // creat JSON message for Socket.IO (event)
        DynamicJsonDocument doc(1024);
        JsonArray array = doc.to<JsonArray>();
        
        // add evnet name
        // Hint: socket.on('event_name', ....
        array.add("ArduinoMessage");

        // add payload (parameters) for the event
        JsonObject param1 = array.createNestedObject();
        param1["ip_origin"] = WiFi.localIP().toString();
        param1["command"] = "stop";
        

        // JSON to String (serializion)
        String output;
        serializeJson(doc, output);

        // Send event        
        socketIO.sendEVENT(output);
        
        delay(1000);
        // Print JSON for debugging
        USE_SERIAL.println(output);
    }
    
}


void socketIOEvent(socketIOmessageType_t type, uint8_t * payload, size_t length) {

    //Serial.println("entro a socketIOEvent");
    Serial.printf("\n[IOc] get payload: %s\n", payload);

    String response = (char*)payload;
    
    if (response.indexOf("backward") > 0) {
      Serial.printf("hacia atras\n");
      backwards();
      delay(1000);
      stops();
    }

    if (response.indexOf("forward") > 0) {
      Serial.printf("hacia delante\n");
      forwards();
      delay(1000);
      stops();
    }

    if (response.indexOf("rightward") > 0) {
      Serial.printf("hacia derecha\n");
      rightwards();
      delay(1000);
      stops();
    }

    if (response.indexOf("leftward") > 0) {
      Serial.printf("hacia izquierda\n");
      leftwards();
      delay(1000);
      stops();
    }

    if (response.indexOf("stop") > 0) {
      Serial.printf("Detenido\n");
      stops();

      delay(1000);

      weird_mov();
      
    }

    switch(type) {
        case sIOtype_DISCONNECT:
            USE_SERIAL.printf("[IOc] Disconnected!\n");
            break;
        case sIOtype_CONNECT:
            USE_SERIAL.printf("[IOc] Connected to url: %s\n", payload);

            // join default namespace (no auto join in Socket.IO V3)
            socketIO.send(sIOtype_CONNECT, "/");
            break;
        case sIOtype_EVENT:
            USE_SERIAL.printf("[IOc] get event: %s\n", payload);
            break;
    }
}

void prenda_esa_vaina(){
  digitalWrite(EnableA, HIGH);
  digitalWrite(EnableB, HIGH);
}
void forwards(){
  prenda_esa_vaina();
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backwards(){
  prenda_esa_vaina();
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void rightwards(){
  prenda_esa_vaina();

  /*digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  delay(500);
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);*/

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(500);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

}

void leftwards(){
  prenda_esa_vaina();

  /*digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  delay(500);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);*/
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(500);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
}

void stops(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void weird_mov(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  delay(500);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
