/******************************************************************************
  Qwiic Relay Firmware
  Kevin Kuwata @ SparkX
  March 21, 2018
  https://github.com/sparkfunX/Qwiic_Relay
  Arduino 1.8.5

  This is the firmware on the Qwiic Relay. The default I2C Address is
  0x18;

******************************************************************************/
#include <TinyWire.h> //https://github.com/lucullusTheOnly/TinyWire
#include <EEPROM.h>


#define RELAY_PIN   4
 
#define SETTING_LOCATION_ADDRESS	1

volatile byte qwiicRelayAddress  =    0x18; //default

const byte relayAddressPin	=	3;



#define COMMAND_RELAY_OFF 			0x00
#define COMMAND_RELAY_ON 			0x01
#define COMMAND_CHANGE_ADDRESS 		0x03
#define COMMAND_FIRMWARE_VERSION 	0x04
#define COMMAND_STATUS 				0x05
#define COMMAND_HAS_BEEN_CHECKED 	0x99

const byte firmwareVersionMajor = 1;
const byte firmwareVersionMinor = 1;

volatile byte command = COMMAND_HAS_BEEN_CHECKED;
volatile byte address = COMMAND_HAS_BEEN_CHECKED;


void setup() {
	
  pinMode(relayAddressPin, INPUT);
  digitalWrite(relayAddressPin, HIGH); //internal pull up
  
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
	
	if(digitalRead(relayAddressPin) == 0){
		qwiicRelayAddress = 0x19;
	}
	else{
  //Read EEPROM, is it empty (0xFF)? or does it have a value?
  qwiicRelayAddress =  EEPROM.read(SETTING_LOCATION_ADDRESS);
		if (qwiicRelayAddress == 0xFF) {
			//EEPROM has never been written before, use the default address 0x18.
		qwiicRelayAddress = 0x18; //default
		}
	}

  TinyWire.begin(qwiicRelayAddress);
  TinyWire.onReceive(receiveEvent); // register event
  TinyWire.onRequest(onI2CRequest);
}

void loop() {
}

/*========================================================*/
//        ISR
/*========================================================*/

// When the master initiates a command and data to slave
//		ie) the master says 0x01, then sends a 1, means command: 0x01 then the slave listens for the next thing, which is the relay state 1
void receiveEvent(int bytesReceived) {
  byte count = 0;
  while (TinyWire.available() > 0) {
    if (count == 0) {
      command = TinyWire.read();

      if (command == COMMAND_RELAY_ON) {
        digitalWrite(RELAY_PIN, HIGH);
        command = COMMAND_HAS_BEEN_CHECKED;
      }
      else if (command == COMMAND_RELAY_OFF) {
        digitalWrite(RELAY_PIN, LOW);
        command = COMMAND_HAS_BEEN_CHECKED;
      }
    }
    else if (count == 1) {
      if (command == COMMAND_CHANGE_ADDRESS) {
        byte address = TinyWire.read();

        if (address > 0x07 && address < 0x78) {
          //valid address, update and save to EEPROM
          qwiicRelayAddress = address;

          EEPROM.write(SETTING_LOCATION_ADDRESS, qwiicRelayAddress);
          TinyWire.begin(qwiicRelayAddress);
        }
      }
    }
    else {
      TinyWire.read(); //read the data coming in but ignore it.
    }
    count++;
  }
}// end of receive ISR



//When the master requests data from the slave, this
//    ISR is triggered.

void onI2CRequest() {
  //not sure if this will work because the master sends 0x04, then the salve enters the RX event isr
  // then goes to main, sets the flag. then if that happens slower than versionFlag we have a race condition.
  if (command == COMMAND_FIRMWARE_VERSION) {
    //TinyWire.send(firmwareVersion);// tiny wire can't send multiple bytes.
    TinyWire.send(firmwareVersionMajor);
    TinyWire.send(firmwareVersionMinor);

    command = COMMAND_HAS_BEEN_CHECKED;
  }
  else if (command == COMMAND_STATUS) {
    if (digitalRead(RELAY_PIN) == HIGH)
      TinyWire.send(COMMAND_RELAY_ON);
    else
      TinyWire.send(COMMAND_RELAY_OFF);

    command = COMMAND_HAS_BEEN_CHECKED;
  }
}
