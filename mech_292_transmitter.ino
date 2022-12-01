#include <RH_ASK.h>
#include <SPI.h>

#define echoPin 2
#define trigPin 3


// for the RF transmitter
RH_ASK driver;

// for the ultrasound distance sensor
long distance;
int duration;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  if (!driver.init()){
    Serial.println("init failed");
  }

}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(100);

  if (distance > 10) {
    const char *msg = "clear";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
  }

  else {
    const char *msg = "obstacle";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
  }

  Serial.println("msg sent!");
  delay(1000);

}
