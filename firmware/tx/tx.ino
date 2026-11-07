//kindle page turner - tx (remote)
//xiao esp32-c3, button on D2 to GND

#include <BLEDevice.h>
#include "esp_sleep.h"
#include "driver/gpio.h"

//has to match rx
#define SERVICE_UUID "a3c8b2e0-1d34-4b8a-9f2a-6e2d7c9a1000"
#define CHAR_UUID    "a3c8b2e0-1d34-4b8a-9f2a-6e2d7c9a1001"

const int BUTTON = D2;                     //gpio4, has to be gpio0-5 to wake from deep sleep
const unsigned long CONNECT_TIMEOUT = 10000;
const unsigned long STAY_AWAKE = 60000;    //sleep after 1 min of no presses

BLEClient* client = nullptr;
BLERemoteCharacteristic* tapChar = nullptr;
BLEAdvertisedDevice* receiver = nullptr;
bool found = false;
unsigned long lastPress = 0;

//look for the rx while scanning
class ScanCallback : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice dev) override {
    if (dev.haveServiceUUID() && dev.isAdvertisingService(BLEUUID(SERVICE_UUID))) {
      BLEDevice::getScan()->stop();
      if (receiver != nullptr) delete receiver;
      receiver = new BLEAdvertisedDevice(dev);
      found = true;
    }
  }
};

//bluetooth connection
bool connectToReceiver() {
  found = false;
  BLEScan* scan = BLEDevice::getScan();
  unsigned long start = millis();

  while (!found && millis() - start < CONNECT_TIMEOUT) {
    scan->start(2, false);   //stops early if the rx is found
    scan->clearResults();
  }
  if (!found) return false;

  if (!client->connect(receiver)) return false;

  BLERemoteService* service = client->getService(SERVICE_UUID);
  if (service == nullptr) {
    client->disconnect();
    return false;
  }

  tapChar = service->getCharacteristic(CHAR_UUID);
  if (tapChar == nullptr) {
    client->disconnect();
    return false;
  }

  Serial.println("connected to rx");
  return true;
}

bool sendTap() {
  //reconnect if we lost it
  if (!client->isConnected()) {
    if (!connectToReceiver()) return false;
  }

  uint8_t cmd = '1';
  tapChar->writeValue(&cmd, 1, false);
  Serial.println("tap sent");
  return true;
}

void goToSleep() {
  //wait for button release
  while (digitalRead(BUTTON) == LOW) delay(10);
  delay(20);

  Serial.println("going to sleep");
  Serial.flush();

  if (client != nullptr && client->isConnected()) client->disconnect();

  //wake up when button pulls D2 low
  gpio_pullup_en((gpio_num_t)BUTTON);
  gpio_pulldown_dis((gpio_num_t)BUTTON);
  esp_deep_sleep_enable_gpio_wakeup(1ULL << BUTTON, ESP_GPIO_WAKEUP_GPIO_LOW);
  esp_deep_sleep_start();
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON, INPUT_PULLUP);

  //first power on, give time to upload code then sleep
  if (esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_GPIO) {
    delay(3000);
    goToSleep();
  }

  //wake up
  Serial.println("woke up from button");

  BLEDevice::init("PageTurner-TX");
  client = BLEDevice::createClient();

  BLEScan* scan = BLEDevice::getScan();
  scan->setAdvertisedDeviceCallbacks(new ScanCallback());
  scan->setActiveScan(true);
  scan->setInterval(100);
  scan->setWindow(99);

  if (!sendTap()) {
    Serial.println("couldn't find rx");
    goToSleep();
  }

  lastPress = millis();
  while (digitalRead(BUTTON) == LOW) delay(10);
}

void loop() {
  //button press
  if (digitalRead(BUTTON) == LOW) {
    delay(20);   //debounce
    if (digitalRead(BUTTON) == LOW) {
      sendTap();
      lastPress = millis();
      while (digitalRead(BUTTON) == LOW) delay(10);
      delay(20);
    }
  }

  //no presses for a while
  if (millis() - lastPress > STAY_AWAKE) goToSleep();

  delay(5);
}
