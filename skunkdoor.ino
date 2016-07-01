#include <SPI.h>
#include <WiFi.h>

char ssid[] = "yourSSID";      //  your network SSID (name)
char pass[] = "yourSSIDPassword";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;
// Initialize the Wifi client library
WiFiClient client;

// Store the strings
String currentLine;
String currentStatus = "";
boolean statusNumbers = false;
int outStatus = 0;

// server address:
char server[] = "skunkworks.at.utep.edu";
//IPAddress server(64,131,82,241);

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // LED or Servo Setting
  pinMode(9, OUTPUT);

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  // you're connected now, so print out the status:
   printWifiStatus();
}

void loop() {
  while (client.available()) {
    char inChar = client.read();
    // Convert into a string
    currentLine += inChar;

    if (inChar == '\n') {
      currentLine = "";
    }

    //Serial.println(currentLine.endsWith("<status>"));
    if (currentLine.endsWith("<status>")) {
      statusNumbers = true;
    } else if (statusNumbers) {
      if (!currentLine.endsWith("</status>")) {
        currentStatus += inChar;
      }
      else {
        statusNumbers = false;
        String justStatus = currentStatus.substring(0, currentStatus.length()-8);
        outStatus = justStatus.toInt();
        //Serial.println(justStatus);
      }
    }
  }
  currentStatus = "";

  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
  }

  //Actions to turn LED
  if (outStatus == 1) {
    digitalWrite(9, HIGH);
  }
  else if (outStatus == 0) {
    digitalWrite(9, LOW);
  }
}



// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80)) {
    // send the HTTP PUT request:
    client.println("GET /skunk/doors/1/status.html HTTP/1.1");
    client.println("Host: skunkworks.at.utep.edu");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
