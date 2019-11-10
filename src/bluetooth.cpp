#include "bluetooth.h"



class MyCallbacks: public BLECharacteristicCallbacks {

    void onWrite(BLECharacteristic *pCharacteristic) {
      Serial.println("write");

      std::string value = pCharacteristic->getValue();

      if (value.length() > 0) {

        Serial.println("*********");
        Serial.print("New value: ");

        for (int i = 0; i < value.length(); i++)

          // Serial.print(value[i]);
          Serial.print((int)value[0]);

        Serial.println();

        Serial.println("*********");
        int input = (int)value[0];
        int segmented = input%10;
        int sw = input/10;
        Serial.println(sw);
        Serial.println(segmented);
        struct{
            int sw = 0;
            int seg = 0;
        } se;
        se.sw = sw;
        se.seg = segmented;
        EEPROM.begin(8);
        EEPROM.put(0,se);
        EEPROM.commit();
      }

    }

};

BLECharacteristic* pCharacteristic = NULL;

void setupBluetooth(){

    

    Serial.println("Starting BLE work!");

    BLEDevice::init("Long name works now");

    BLEServer *pServer = BLEDevice::createServer();

    BLEService *pService = pServer->createService(SERVICE_UUID);

    pCharacteristic = pService->createCharacteristic(

                                            CHARACTERISTIC_UUID,

                                            BLECharacteristic::PROPERTY_READ |

                                            BLECharacteristic::PROPERTY_WRITE |

                                            BLECharacteristic::PROPERTY_NOTIFY

                                        );


    pCharacteristic->setCallbacks(new MyCallbacks());

    pCharacteristic->setValue("Test");

    pCharacteristic->setReadProperty(true);

    pService->start();

    // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

    pAdvertising->addServiceUUID(SERVICE_UUID);

    pAdvertising->setScanResponse(true);

    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue

    pAdvertising->setMinPreferred(0x12);

    BLEDevice::startAdvertising();

    Serial.println("Characteristic defined! Now you can read it in your phone!");
};