#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <WebSocketsClient.h>
#include <SocketIOclient.h>

#include <ArduinoJson.h>

ESP8266WiFiMulti WiFiMulti;
SocketIOclient socketIO;

#define PIN_TRG D4
#define PIN_ECHO D5

float tiempo;
float distancia;
#define USE_SERIAL Serial1

void setup() {
  Serial.begin(115200);

  WiFiMulti.addAP("LUZMARINA", "+6-5LJB%=*M4j4l452. 47");
  //WiFiMulti.addAP("manuel", "3115574493");
  
  while (WiFiMulti.run() != WL_CONNECTED) {

    Serial.println("connecting...");
    delay(1000);
  }
    // server address, port and URL
  socketIO.begin("192.168.0.5", 3009, "/socket.io/?EIO=4");

    // event handler
  socketIO.onEvent(socketIOEvent);
  
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);  
  pinMode(5, OUTPUT);  
  pinMode(4, OUTPUT);

  pinMode(PIN_TRG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}

void loop() {
    socketIO.loop();
    
    digitalWrite(PIN_TRG, LOW);  //para generar un pulso limpio ponemos a LOW 4us
    delayMicroseconds(500);
   
    digitalWrite(PIN_TRG, HIGH);  //generamos Trigger (disparo) de 10us
    delayMicroseconds(150000);
    digitalWrite(PIN_TRG, LOW);
   
    tiempo = pulseIn(PIN_ECHO, HIGH);
    distancia = tiempo/58.3;

    //Serial.println(distancia);

    if(distancia < 15) {

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

        // Print JSON for debugging
        USE_SERIAL.println(output);
    }
}


void socketIOEvent(socketIOmessageType_t type, uint8_t * payload, size_t length) {

    Serial.println("entro a socketIOEvent");
    Serial.printf("[IOc] get payload: %s\n", payload);

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
