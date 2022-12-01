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
  // put your main code here, to run repeatedly:

  digitalWrite(vibrationPin, LOW);
  delay(250);
  digitalWrite(vibrationPin, HIGH);
  delay(250);

  uint8_t buf[12];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)) {
    int i;
    Serial.println((char*)buf);
  }

}
