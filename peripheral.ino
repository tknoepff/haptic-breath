
#include <ArduinoBLE.h>
#include <Wire.h>
#include "Adafruit_SGP30.h"

Adafruit_SGP30 breath_sensor;

int breathe_val = 0;
int initial_value = 0;
int calibrator_counter = 0;

BLEService hapticService("19B10000-E8F2-537E-4F6C-D104768A1214");
BLEByteCharacteristic hapticCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

int hapticPin = D2;


void setup() {
  pinMode(hapticPin, OUTPUT);
  
  breath_sensor.begin();

  BLE.begin();
  BLE.setAdvertisedService(hapticService);
  hapticService.addCharacteristic(hapticCharacteristic);
  BLE.addService(hapticService);
  hapticCharacteristic.writeValue(0);
  BLE.advertise();
}


void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    central.discoverAttributes();
    
    BLECharacteristic hapticTalkCharacteristic = central.characteristic("19b10001-e8f2-537e-4f6c-d104768a1214");

    while (central.connected()) {

      if (hapticTalkCharacteristic.written()) {
        if (hapticTalkCharacteristic.value()) {
          digitalWrite(hapticPin, HIGH);
        } else {
          digitalWrite(hapticPin, LOW);
        }
      }

    breath_sensor.IAQmeasureRaw();
    breathe_val = breath_sensor.rawH2;

    if(calibrator_counter > 100){
      initial_value = breathe_val;
      calibrator_counter = 0;
    }

    calibrator_counter = calibrator_counter + 1;

      if (breathe_val < initial_value - 100) {
        hapticCharacteristic.writeValue((byte)0x01);
        
      } else {
        hapticCharacteristic.writeValue((byte)0x00);
      }
    }
  }
}
