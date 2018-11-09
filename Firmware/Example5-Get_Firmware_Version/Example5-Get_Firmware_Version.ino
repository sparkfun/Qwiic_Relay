/******************************************************************************
  Qwiic Relay Example 5 - Get Firmware Version
  Kevin Kuwata @ SparkX
  April 3, 2018
  https://github.com/sparkfunX/Qwiic_Relay
  Arduino 1.8.5


  This sketch demonstrates how to get the firmware version of the Qwiic Relay.
  If using version prior to (excluding) 1.0 the version number will be 25.5 or 26.5.
  Qwiic Relay starting at version 1.0, the relay  will respond with the correct firmware version.


  Default Qwiic relay address is 0x18.

******************************************************************************/
#include <Wire.h>

#define COMMAND_FIRMWARE_VERSION 0x04

const byte qwiicRelayAddress = 0x18;     //Default Address

void setup() {
  Serial.begin(9600);
  Serial.println("Qwiic Relay Master Awake");

  Wire.begin(); 
  testForConnectivity();
  Serial.print("Version Number: ");
  Serial.println(getFirmwareVersion(), 1);
}

void loop() {
}

//getFirmwareVersion() returns the firmware version as a float.
float getFirmwareVersion() {
  Wire.beginTransmission(qwiicRelayAddress);
  Wire.write(COMMAND_FIRMWARE_VERSION);
  Wire.endTransmission();

  Wire.requestFrom(qwiicRelayAddress, 2); //2 BYTES for the Version Number

  if (Wire.available() == 0) return 0;
  float versionNumber = Wire.read();
  versionNumber += (float)Wire.read() / 10.0;

  return (versionNumber);
}

// testForConnectivity() checks for an ACK from an Relay. If no ACK
// program freezes and notifies user.
void testForConnectivity() {
  Wire.beginTransmission(qwiicRelayAddress);
  //check here for an ACK from the slave, if no ACK don't allow change?
  if (Wire.endTransmission() != 0) {
    Serial.println("Check connections. No slave attached.");
    while (1);
  }
}
