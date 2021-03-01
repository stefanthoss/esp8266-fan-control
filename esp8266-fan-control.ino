#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define FAN_PIN 12
#define SIGNAL_PIN 13

Adafruit_BME280 bme; // I2C

const int delayTime = 1000; // time between measurements [ms]
const int minFanSpeedPercent = 24; // minimum fan speed [%]
const int minTemp = 25; // turn fan off below [deg C]
const int maxTemp = 40; // turn fan to full speed above [deg C]

void setup() {
  Serial.begin(9600);

  pinMode(FAN_PIN, OUTPUT);
  pinMode(SIGNAL_PIN, INPUT);

  bool status = bme.begin(0x76);

  if (!status) {
    Serial.println("Could not find a valid BME280 sensor.");
    while (1);
  }
}

int getFanSpeedRpm() {
  int highTime = pulseIn(SIGNAL_PIN, HIGH);
  int lowTime = pulseIn(SIGNAL_PIN, LOW);
  int period = highTime + lowTime;
  if (period == 0) {
    return 0;
  }
  float freq = 1000000.0 / (float)period;
  return (freq * 60.0) / 2.0; // two cycles per revolution
}

void setFanSpeedPercent(int p) {
  int value = (p / 100.0) * 1024;
  analogWrite(FAN_PIN, value);
}

void loop() {
  float temp = bme.readTemperature();
  Serial.print("Temperature is ");
  Serial.print(temp);
  Serial.println(" deg C");

  int fanSpeedPercent, actualFanSpeedRpm;

  if (temp < minTemp) {
    fanSpeedPercent = 0;
  } else if (temp > maxTemp) {
    fanSpeedPercent = 100;
  } else {
    fanSpeedPercent = (100 - minFanSpeedPercent) * (temp - minTemp) / (maxTemp - minTemp) + minFanSpeedPercent;
  }

  Serial.print("Setting fan speed to ");
  Serial.print(fanSpeedPercent);
  Serial.println(" %");
  setFanSpeedPercent(fanSpeedPercent);

  actualFanSpeedRpm = getFanSpeedRpm();
  Serial.print("Fan speed is ");
  Serial.print(actualFanSpeedRpm);
  Serial.println(" RPM");

  Serial.println();
  delay(delayTime);
}
