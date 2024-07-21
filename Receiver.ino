#include <ESP8266WiFi.h>

#define ssid  ""
#define pwsd  ""

// Create an instance of the server
WiFiServer server(80);

const int buzzer = 14;
const int R_led = 12;
const int G_led = 13;

void setup() {
  Serial.begin(115200);

  // Intializing led and buzzer;
  pinMode(R_led,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(G_led,OUTPUT);

  digitalWrite(R_led,0);
  digitalWrite(buzzer,0);
  digitalWrite(G_led,1);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwsd);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi connected"));

  // Start the server
  server.begin();
  Serial.println(F("Server started"));

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.accept();
  if (!client) { return; }
  Serial.println(F("new client"));

  client.setTimeout(5000);  // default is 1000

  // Read the first line of the request
  String roll = client.readStringUntil('\n');
  Serial.println("Roll Angle: ");
  Serial.println(roll);

  // Alerting condition
  if(abs(roll.toInt())>=30){
    digitalWrite(R_led,1);
    digitalWrite(buzzer,1);
    digitalWrite(G_led,0);
  }else{
    digitalWrite(G_led,1);
    digitalWrite(R_led,0);
    digitalWrite(buzzer,0);
  }
  
  while (client.available()) {
    // byte by byte is not very efficient
    client.read();
  }

  Serial.println(F("Disconnecting from client"));
}
