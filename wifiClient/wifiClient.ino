#include <SPI.h>
#include <WiFi.h>

// Information to connect to WiFi
char ssid[] = "Feiji";
char pass[] = "36288000";

int status = WL_IDLE_STATUS;
char server[] = "skunkworks.at.utep.edu";
String location = "/skunkdoor/skunk.php HTTP/1.1";
// Incoming serial data
char inString[500];
// String index counter
int stringPos = 0;

byte statusLed = 0;
char c;

int led1 = 3;
int led2 = 4;
WiFiClient client;

unsigned long lastConnectionTime = 0;
boolean lastConnected = false;
const unsigned long postingInterval = 100;

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  // Check the presence of the shield.
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.print("Please connect a WiFi Shield.");
    while(true);
  }
  while(status != WL_CONNECTED) {
    Serial.print("Attempting to connect to the network called: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(1000);
  }
  // If connection was successful.
  Serial.println("Successful connection ot WiFi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  // If connection is successful report it back
  if (client.connect(server, 80)) {
    Serial.println("Successfully connected to the server.");
    // Make a Request
    client.print("GET ");
    client.println(location);
    client.println("Host: skunkworks.at.utep.edu");
    client.println();
  } else {
    Serial.println("Connection failed");
  }
}

void loop() {
  while (client.available()) {
    c = client.read();
    Serial.write(c);
    CheckingStatus();
  }
  if (!client.connected() && lastConnected) {
    Serial.println();
    Serial.println("Disconnecting");
    client.stop();
  }
  if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
    PingRequest();
  }
  lastConnected = client.connected();
}

void PingRequest() {
  if(client.connect(server, 80)) {
    client.print("GET");
    client.println(location);
    client.println("Host: skunkworks.at.utep.edu");
    client.println("Connection Closed");
    client.println();
    lastConnectionTime = millis();
  } else {
    client.stop();
  }
}

void CheckingStatus() {
  inString[stringPos] = c;
  if (c == '*') {
    statusLed = inString[stringPos - 1];
    stringPos = 0;
    delay(500);
    UpdatingStatus();
  }
  stringPos++;
}

void UpdatingStatus() {
  if(statusLed == '1') {
    digitalWrite(led1, HIGH);
  }
  if(statusLed == '2') {
    digitalWrite(led1, LOW);
  }
  if(statusLed == '3') {
    digitalWrite(led2, HIGH);
  }
  if(statusLed == '4') {
    digitalWrite(led2, HIGH);
  }
}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip= WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("Signal Strength: ");
  Serial.print(rssi);
  Serial.println(" dBm");
}
