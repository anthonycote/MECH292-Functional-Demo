#include <RH_ASK.h>
#include <SPI.h>

#define vibrationPin1 20
#define vibrationPin2 21
#define vibrationPin3 22
#define vibrationPin4 23
#define vibrationPin5 24
#define vibrationPin6 25
#define vibrationPin7 26
#define vibrationPin8 27
#define vibrationPin9 28
#define vibrationPin10 29


RH_ASK driver;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(vibrationPin1, OUTPUT);
  pinMode(vibrationPin2, OUTPUT);
  pinMode(vibrationPin3, OUTPUT);
  pinMode(vibrationPin4, OUTPUT);
  pinMode(vibrationPin5, OUTPUT);
  pinMode(vibrationPin6, OUTPUT);
  pinMode(vibrationPin7, OUTPUT);
  pinMode(vibrationPin8, OUTPUT);
  pinMode(vibrationPin9, OUTPUT);
  pinMode(vibrationPin10, OUTPUT);


  if (!driver.init()) {
    Serial.println("init failed");
  }

}

void loop() {

  int received_value = -1;
  uint8_t buflen = 2;

  if (driver.recv((uint8_t *) &received_value, &buflen)) {
    runVibration(
      received_value,
      vibrationPin1,
      vibrationPin2,
      vibrationPin3,
      vibrationPin4,
      vibrationPin5,
      vibrationPin6,
      vibrationPin7,
      vibrationPin8,
      vibrationPin9,
      vibrationPin10
    )   
  }

}

void runVibration(commandInt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) {
  // logic statement here to run motor vibrations based on command integer
}
