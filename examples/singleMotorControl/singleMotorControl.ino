/*!
 * @file singleMotorControl.ino
 * @brief Single DFR1277 motor control demo.
 * @details Demo for initializing one serial motor module and driving forward/backward.
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

DFRobot_N20SerialMotor motor(1, &N20_PORT);

void setup()
{
  Serial.begin(115200);
  N20_PORT.begin(9600);

  while (motor.begin() != 0) {
    Serial.println("N20 serial motor init failed.");
    delay(1000);
  }

  Serial.println("N20 serial motor init success.");
}

void loop()
{
  motor.setSpeed(200);
  delay(2000);

  motor.setSpeed(80);
  delay(1200);

  motor.setSpeed(-200);
  delay(2000);

  motor.stop();
  delay(1500);
}
