//kindle page turner - rx (servo side)
//xiao esp32-c3, servo signal on D2, miniboost enable on D3
//needs ESP32Servo library

#include <BLEDevice.h>
#include <BLEServer.h>
#include <ESP32Servo.h>

//has to match tx
#define SERVICE_UUID "a3c8b2e0-1d34-4b8a-9f2a-6e2d7c9a1000"
#define CHAR_UUID    "a3c8b2e0-1d34-4b8a-9f2a-6e2d7c9a1001"

const int SERVO_PIN = D2;
const int BOOST_EN = D3;      //turns on the 5v boost for the servo

//servo angles, the arm is set on the horn so TAP_ANGLE touches the screen
const int REST_ANGLE = 0;
const int TAP_ANGLE = 50;
const int MOVE_TIME = 300;    //time for the servo to get there
const int HOLD_TIME = 150;    //time touching the screen

Servo servo;
volatile bool tapRequested = false;

class ServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* server) override {
    Serial.println("tx connected");
  }
  void onDisconnect(BLEServer* server) override {
    Serial.println("tx disconnected");
    BLEDevice::startAdvertising();   //let the tx find us again
  }
};

//tx sends '1' for a tap
class TapCallback : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* c) override {
    String value = c->getValue();
    if (value.length() > 0 && value[0] == '1') tapRequested = true;
  }
};

void tap() {
  servo.attach(SERVO_PIN, 500, 2400);
  servo.write(TAP_ANGLE);
  delay(MOVE_TIME + HOLD_TIME);
  servo.write(REST_ANGLE);
  delay(MOVE_TIME);
  servo.detach();   //stops buzzing and saves battery
}

void setup() {
  Serial.begin(115200);

  //turn on the boost
  pinMode(BOOST_EN, OUTPUT);
  digitalWrite(BOOST_EN, HIGH);

  //servo to rest position
  ESP32PWM::allocateTimer(0);
  servo.setPeriodHertz(50);
  servo.attach(SERVO_PIN, 500, 2400);
  servo.write(REST_ANGLE);
  delay(MOVE_TIME);
  servo.detach();

  //bluetooth connection
  BLEDevice::init("PageTurner-RX");
  BLEServer* server = BLEDevice::createServer();
  server->setCallbacks(new ServerCallbacks());

  BLEService* service = server->createService(SERVICE_UUID);
  BLECharacteristic* tapChar = service->createCharacteristic(
      CHAR_UUID,
      BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_WRITE_NR);
  tapChar->setCallbacks(new TapCallback());
  service->start();

  BLEAdvertising* adv = BLEDevice::getAdvertising();
  adv->addServiceUUID(SERVICE_UUID);
  adv->setScanResponse(true);
  BLEDevice::startAdvertising();

  Serial.println("rx ready");
}

void loop() {
  if (tapRequested) {
    tapRequested = false;
    Serial.println("tap");
    tap();
  }
}
