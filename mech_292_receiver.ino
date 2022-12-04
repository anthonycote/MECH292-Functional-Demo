#include <RH_ASK.h>
#include <SPI.h>

#define vibrationPin 7

RH_ASK driver;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(vibrationPin, OUTPUT);

  if (!driver.init()) {
    Serial.println("init failed");
  }

}

void loop() {

  int received_value = -1;
  uint8_t buflen = 2;

  if (driver.recv((uint8_t *) &received_value, &buflen)) {
    Serial.println(received_value);
    Serial.println("!!!");

    if (received_value == 1) {
      digitalWrite(vibrationPin, LOW);
    }

    else {
      digitalWrite(vibrationPin, HIGH);
    }
    
  }

}
