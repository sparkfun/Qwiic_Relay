/******************************************************************************
  Qwiic Relay Example 2 - Change I2C Address
  Kevin Kuwata @ SparkX
  March 21, 2018
  https://github.com/sparkfunX/Qwiic_Relay
  Arduino 1.8.5

  This sketch demonstrates how to change the I2C Address
  of the Qwiic Relay. The new address will be saved to the
  Relay's EEPROM.

  The factory default slave address is 0x18.

  Note: If the Qwiic Relay is connected but unresponsive, try Example 3 - I2C_Scanner
  to find the current address of the Relay.

  Only valid address can be saved to the Relay's EEPROM. If an invalid address is
  sent, the Relay will ignore the address change without notifying the user.

******************************************************************************/
#include <Wire.h>
#define COMMAND_RELAY_OFF 				  0x00
#define COMMAND_RELAY_ON 				    0x01
#define COMMAND_CHANGE_ADDRESS 			0x03



volatile byte qwiicRelayAddress = 0x18;     //Default Address


void setup() {
  Serial.begin(9600);
  Serial.println("Qwiic Relay Master Awake");
  Wire.begin(); // join the I2C Bus


  Wire.beginTransmission(qwiicRelayAddress); // transmit to device
  //check here for an ACK from the slave
  if (Wire.endTransmission() != 0 ) {
    Serial.println("Check Connections. Slave not found.");
  }
  else {
    Serial.println("Qwiic Relay found!");
  }
  
  boolean error = changeAddress(0x19); // Change the Relay's address to 0x19
  
  if (error != true) {
    Serial.println("!!!!! invalid address" );
  }
  else {
    Serial.println("success");
  }
}

void loop() { //Toggle the Relay on the new address
  relayOn();
  delay(2000);
  relayOff();
  delay(2000);
}


// changeAddress() takes a 7 bit I2C Address
// and writes it to the Relay. This function
// checks to see if the address is between
// 0x07 and 0x78. If valid, the new address is
// saved to the Relay's EEPROM. If not valid
// address is not changed and is ignored.
// This function returns true if successful and
// false if unsuccessful.
boolean changeAddress(byte address) {
  //check if valid address.
  if (address < 0x07 || address > 0x78) {
    Serial.println("Invalid I2C address");
    return (false);
  }
  //valid address
  Wire.beginTransmission(qwiicRelayAddress);
  Wire.write(COMMAND_CHANGE_ADDRESS);
  qwiicRelayAddress = address;
  Wire.write(qwiicRelayAddress);
  if (Wire.endTransmission() != 0)
  {
    return false;
  }
  return true;//success
}




// RelayOn() turns on the relay at the SLAVE_ADDRESS
// Checks to see if a slave is connected and prints a
// message to the Serial Monitor if no slave found.
void relayOn() {
  Wire.beginTransmission(qwiicRelayAddress);
  Wire.write(COMMAND_RELAY_ON);
  if (Wire.endTransmission() != 0) {
    Serial.println("Check Connections. No slave attached");
  }
}


// RelayOff() turns off the relay at the qwiicRelayAddress
// Checks to see if a slave is connected and prints a
// message to the Serial Monitor if no slave found.
void relayOff() {
  Wire.beginTransmission(qwiicRelayAddress);
  Wire.write(COMMAND_RELAY_OFF);
  if (Wire.endTransmission() != 0) {
    Serial.println("Check Connections. No slave attached");
  }
}
