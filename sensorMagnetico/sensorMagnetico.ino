#include <ArduinoBLE.h>

BLEService MagneticSensorService("00002a24-1234-1000-8000-00805f9b34fb"); // BLE Sensor Service
BLEService LEDService("00002a24-4321-1000-8000-00805f9b34fb"); // BLE LED Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central

BLEByteCharacteristic MagneticSensorCharacteristic("00002a24-1234-1000-8000-00805f9b34fb",  BLERead | BLENotify | BLEWrite);
BLEByteCharacteristic LEDCharacteristic("00002a24-4321-1000-8000-00805f9b34fb", BLERead | BLENotify | BLEWrite);

void setup() {

  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

  // begin initialization

  if (!BLE.begin()) {

    Serial.println("starting Bluetooth® Low Energy failed!");

  }

  // set advertised local name and service UUID:

  BLE.setLocalName("Magnetic Sensor Device");

  BLE.setAdvertisedService(MagneticSensorService);
  BLE.setAdvertisedService(LEDService);

  // add the characteristic to the service

  MagneticSensorService.addCharacteristic(MagneticSensorCharacteristic);
  LEDService.addCharacteristic(LEDCharacteristic);

  // add service

  BLE.addService(MagneticSensorService);
  BLE.addService(LEDService);

  // start advertising

  BLE.advertise();

  Serial.println("BLE Magnetic Sensor, waiting for connections....");

}

void loop() {

  // listen for BLE peripherals to connect:

  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:

  if (central) {

    Serial.print("Connected to central: ");

    // print the central's MAC address:

    Serial.println(central.address());

    // while the central is still connected to peripheral:
    char i = 0;
    while (central.connected()) {
      delay(1000);
      MagneticSensorCharacteristic.writeValue(i);
      i++;
      /*
      if (LEDCharacteristic.valueUpdated()) {
        byte value = 0;
        LEDCharacteristic.readValue(value);
        Serial.println(value);
        if( value != 0x00){      
          Serial.println(value);
        }
        if(value & 0x01){
          digitalWrite(LED_BUILTIN,HIGH); 
        } else if(value & 0x02){
          digitalWrite(LED_BUILTIN,LOW); 
        }
      }*/
    }
    Serial.print(F("Disconnected from central: "));

    Serial.println(central.address());
  }

}