#include <Servo.h>
#include <SoftwareSerial.h>

//Set up the Servo motor
Servo doorServo;
int incomingByte = 0;   // for incoming serial data

void setup() {
  Serial.begin(9600);
  //  Attach the servo motor to its pin
  doorServo.attach(9);
}

//Initial position setting
int pos = 0;

// Function to open the door
void openDoor() {
  Serial.println("Door is opening now");
  //  Move the servo 90 degrees
  for (pos = 0; pos < 90; pos += 1) {
    doorServo.write(pos);
    Serial.println(pos);
  }
}

// Function to close the door.
void closeDoor() {
  Serial.println("Door is closing now!");
  //  Return to the zero position
  for (pos = 90; pos > 0; pos -= 1) {
    doorServo.write(pos);
    Serial.println(pos);
  }
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    // Display the incoming byte.
    Serial.println(incomingByte, DEC);
    //  In the serial 1 = 49 0 = 48
    if (incomingByte == 48) {
      openDoor();
      delay(1000);
      closeDoor();
    } else if (incomingByte == 49) {
      closeDoor();
      delay(5000);
      openDoor();
    }
    //Otherwise do nothing
  }
}
