
#include <WiFi.h>
#include <WebServer.h>
#include <PubSubClient.h>

// Change the credentials below, so your ESP8266 connects to your router
const char* ssid = "Home@Ranchi";
const char* password = "manju@1234";

// Change the variable to your Raspberry Pi IP address, so it connects to your MQTT broker
const char* mqtt_server = "192.168.29.87";

WiFiClient espClient_door;
PubSubClient client(espClient_door);

//room1 light sensor
const int ledPin =4;
const int pirPin = 5;

// Don't change the function below. This functions connects your ESP8266 to your router
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

// This functions reconnects your ESP8266 to your MQTT broker
// Change the function below if you want to subscribe to more topics with your ESP8266 
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    if (client.connect("espClient_door")) {
      Serial.println("connected");  
      // Subscribe or resubscribe to a topic
      // You can subscribe to more topics (to control more LEDs in this example)
      client.subscribe("door/lamp");
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// This functions is executed when some device publishes a message to a topic that your ESP8266 is subscribed to
// Change the function below to add logic to your program, so when a device publishes a message to a topic that 
// your ESP8266 is subscribed you can actually do something
void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // If a message is received on the topic room/lamp, you check if the message is either on or off. Turns the lamp GPIO according to the message
  if(topic=="door/lamp"){
      Serial.print("Changing Room lamp to ");
      if(messageTemp == "1"){
        digitalWrite(ledPin, HIGH);
        Serial.print("On");
      }
      else if(messageTemp == "0"){
        digitalWrite(ledPin, LOW);
        Serial.print("Off");
      }
  }
  Serial.println();
}
void setup(){
  
  Serial.begin(9600);                 // Start the serial terminal
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback); 

  //room1
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  Serial.begin(115200);
  digitalWrite(ledPin, LOW);  
}

void loop(){  
  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
  {
    client.connect("espClient_door");
  }

  //door
  int pirStatus = digitalRead(pirPin);
  Serial.print("light value : ");
  Serial.println(pirStatus);
  
  if (pirStatus == 1)
  {
    client.publish("door/pir", "1");
    //digitalWrite(ledPin, HIGH);
    Serial.print("Motion Detected. Status: ");
    Serial.println(pirStatus);
  }
  else
  {
    client.publish("door/pir", "0");
    //digitalWrite(ledPin, LOW);
    Serial.print("No Motion detected, Status: ");
    Serial.println(pirStatus);
  }
  Serial.println("waiting for 5 seconds");
  delay(5000);
}
