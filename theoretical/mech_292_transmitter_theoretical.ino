#include <RH_ASK.h>
#include <SPI.h>

#include <Adafruit_LSM6DSOX.h>


Adafruit_LSM6DSOX sox;


#define echoPin1 20
#define trigPin1 21

#define echoPin2 22
#define trigPin2 23

#define echoPin3 24
#define trigPin3 25

#define echoPin4 26
#define trigPin4 27

#define echoPin5 28
#define trigPin5 29

#define echoPin6 30
#define trigPin6 31



// for the RF transmitter
RH_ASK driver;

// for the ultrasound distance sensor
long distance;
int duration;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(21, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(31, OUTPUT);
  
  pinMode(20, INPUT);
  pinMode(22, INPUT);
  pinMode(24, INPUT);
  pinMode(26, INPUT);
  pinMode(28, INPUT);
  pinMode(30, INPUT);

  if (!driver.init()){
    Serial.println("init failed");
  }

  if (!sox.begin_I2C()) {
    while (1) {
      delay(10);
    }
  }

  Serial.print("Accelerometer range set to: ");
  switch (sox.getAccelRange()) {
  case LSM6DS_ACCEL_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case LSM6DS_ACCEL_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case LSM6DS_ACCEL_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case LSM6DS_ACCEL_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }

  // sox.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS );
  Serial.print("Gyro range set to: ");
  switch (sox.getGyroRange()) {
  case LSM6DS_GYRO_RANGE_125_DPS:
    Serial.println("125 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_250_DPS:
    Serial.println("250 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_500_DPS:
    Serial.println("500 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_1000_DPS:
    Serial.println("1000 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_2000_DPS:
    Serial.println("2000 degrees/s");
    break;
  case ISM330DHCX_GYRO_RANGE_4000_DPS:
    break; // unsupported range for the DSOX
  }

  // sox.setAccelDataRate(LSM6DS_RATE_12_5_HZ);
  Serial.print("Accelerometer data rate set to: ");
  switch (sox.getAccelDataRate()) {
  case LSM6DS_RATE_SHUTDOWN:
    Serial.println("0 Hz");
    break;
  case LSM6DS_RATE_12_5_HZ:
    Serial.println("12.5 Hz");
    break;
  case LSM6DS_RATE_26_HZ:
    Serial.println("26 Hz");
    break;
  case LSM6DS_RATE_52_HZ:
    Serial.println("52 Hz");
    break;
  case LSM6DS_RATE_104_HZ:
    Serial.println("104 Hz");
    break;
  case LSM6DS_RATE_208_HZ:
    Serial.println("208 Hz");
    break;
  case LSM6DS_RATE_416_HZ:
    Serial.println("416 Hz");
    break;
  case LSM6DS_RATE_833_HZ:
    Serial.println("833 Hz");
    break;
  case LSM6DS_RATE_1_66K_HZ:
    Serial.println("1.66 KHz");
    break;
  case LSM6DS_RATE_3_33K_HZ:
    Serial.println("3.33 KHz");
    break;
  case LSM6DS_RATE_6_66K_HZ:
    Serial.println("6.66 KHz");
    break;
  }

  // sox.setGyroDataRate(LSM6DS_RATE_12_5_HZ);
  Serial.print("Gyro data rate set to: ");
  switch (sox.getGyroDataRate()) {
  case LSM6DS_RATE_SHUTDOWN:
    Serial.println("0 Hz");
    break;
  case LSM6DS_RATE_12_5_HZ:
    Serial.println("12.5 Hz");
    break;
  case LSM6DS_RATE_26_HZ:
    Serial.println("26 Hz");
    break;
  case LSM6DS_RATE_52_HZ:
    Serial.println("52 Hz");
    break;
  case LSM6DS_RATE_104_HZ:
    Serial.println("104 Hz");
    break;
  case LSM6DS_RATE_208_HZ:
    Serial.println("208 Hz");
    break;
  case LSM6DS_RATE_416_HZ:
    Serial.println("416 Hz");
    break;
  case LSM6DS_RATE_833_HZ:
    Serial.println("833 Hz");
    break;
  case LSM6DS_RATE_1_66K_HZ:
    Serial.println("1.66 KHz");
    break;
  case LSM6DS_RATE_3_33K_HZ:
    Serial.println("3.33 KHz");
    break;
  case LSM6DS_RATE_6_66K_HZ:
    Serial.println("6.66 KHz");
    break;
  }

  Serial.println("transmitter");

}

void loop() {
  // put your main code here, to run repeatedly:

  sensors_event_t accel;
  sox.getEvent(&accel, &gyro, &temp);

  if (accel.acceleration.x>2 || accel.acceleration.y>2 || accel.acceleration.z>2) {
    callEMS();
  }

  dist1 = getDistance(20, 21);
  dist2 = getDistance(22, 23);
  dist3 = getDistance(24, 25);
  dist4 = getDistance(26, 27);
  dist5 = getDistance(28, 29);
  dist6 = getDistance(30, 31);

  int commandInt = getCommand(dist1, dist2, dist3, dist4, dist5, dist6);

  driver.send((uint8_t *) &commandInt, 2);
  driver.waitPacketSent();
  
}

long getDistance(echoPin, trigPin) {
  int duration;
  long distacne;
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2;

  return distance;
  
}

int getCommmand(dist1, dist2, dist3, dist4, dist5, dist6) {
  int command;
  // codeblock for creating an integer that outputs a specific command based on the 6 ultrasonic sensors
  return command;
}

void callEMS() {
  // placeholder block to call EMS,
  // send GPS coordinates of current position
  // notify an emergency personal contact
}

