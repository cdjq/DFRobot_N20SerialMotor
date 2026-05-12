/*!
 * @file dualMotorControl.ino
 * @brief Two DFR1277 motors control demo.
 * @details Scan bus addresses and control 2 cascaded motors by Modbus-RTU.
 * @copyright Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author JiaLi(zhixin.liu@dfrobot.com)
 * @version V1.0.0
 * @date 2026-05-09
 * @url https://github.com/DFRobot/DFRobot_N20SerialMotor
 */

#include "DFRobot_N20SerialMotor.h"

#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
#include "SoftwareSerial.h"
SoftwareSerial n20Serial(2, 3);  // RX, TX
#define N20_PORT n20Serial
#else
#define N20_PORT Serial1
#endif

DFRobot_N20SerialMotor motors[] = {
  DFRobot_N20SerialMotor(1, &N20_PORT),
  DFRobot_N20SerialMotor(2, &N20_PORT)
};
const uint8_t MOTOR_COUNT = sizeof(motors) / sizeof(motors[0]);

void setup()
{
  uint8_t i = 0;
  uint8_t addrList[8];
  uint8_t count = 0;

  Serial.begin(115200);
  N20_PORT.begin(9600);

  for (i = 0; i < MOTOR_COUNT; i++) {
    while (motors[i].begin() != 0) {
      Serial.print("Motor init failed, index: ");
      Serial.println(i);
      delay(1000);
    }
  }

  count = motors[0].scan(addrList, sizeof(addrList));
  Serial.print("Detected module count: ");
  Serial.println(count);
  for (i = 0; i < count; i++) {
    Serial.print(" - Addr: ");
    Serial.println(addrList[i]);
  }
}

void loop()
{
  motors[0].setSpeed(180);
  motors[1].setSpeed(-180);
  delay(2000);

  motors[0].setSpeed(-120);
  motors[1].setSpeed(120);
  delay(2000);

  motors[0].stop();
  motors[1].stop();
  delay(1500);
}
