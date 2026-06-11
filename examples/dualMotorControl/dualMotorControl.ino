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

/* ---------------------------------------------------------------------------------------------------------------------
  *    board   |             MCU                | Leonardo/Mega2560/M0 |    UNO    | ESP8266 | ESP32 |  microbit  |   m0  |
  *     VCC    |              5V                |         5V           |     5V    |    5V   |   5V  |     X      |   5V  |
  *     GND    |              GND               |        GND           |    GND    |   GND   |  GND  |     X      |  GND  |
  *     RX     |              TX                |     Serial1 TX1      |     5     |   5/D6  | 25/D2 |     X      |  tx1  |
  *     TX     |              RX                |     Serial1 RX1      |     4     |   4/D7  | 26/D3 |     X      |  rx1  |
  * ----------------------------------------------------------------------------------------------------------------------*/
/* Baud rate can be changed */

#if defined(ESP8266) || defined(ARDUINO_AVR_UNO)
SoftwareSerial n20Serial(4, 5);
DFRobot_N20SerialMotor motors[] = {
  DFRobot_N20SerialMotor(1, &n20Serial, 9600),
  DFRobot_N20SerialMotor(2, &n20Serial, 9600)
};
#elif defined(ESP32)
DFRobot_N20SerialMotor motors[] = {
  DFRobot_N20SerialMotor(1, &Serial1, 9600, /*D2*/ D2, /*D3*/ D3),
  DFRobot_N20SerialMotor(2, &Serial1, 9600, /*D2*/ D2, /*D3*/ D3)
};
#else
DFRobot_N20SerialMotor motors[] = {
  DFRobot_N20SerialMotor(1, &Serial1, 9600),
  DFRobot_N20SerialMotor(2, &Serial1, 9600)
};
#endif
const uint8_t motorCount = sizeof(motors) / sizeof(motors[0]);

void setup()
{
  uint8_t i = 0;

  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println(F("========================================"));
  Serial.println(F("  DFRobot N20 Serial Motor"));
  Serial.println(F("  Dual Motor Control Example"));
  Serial.println(F("========================================"));

  for (i = 0; i < motorCount; i++) {
    while (motors[i].begin() != 0) {
      Serial.print(F("[ERROR] Motor "));
      Serial.print(i + 1);
      Serial.println(F(" init failed, retrying..."));
      delay(1000);
    }
    Serial.print(F("[OK] Motor "));
    Serial.print(i + 1);
    Serial.print(F(" initialized (Modbus addr: "));
    Serial.print(i + 1);
    Serial.println(F(")"));
  }

  Serial.println(F("All motors ready."));
  Serial.println(F("Starting dual motor control loop..."));
  Serial.println();
}

void loop()
{
  Serial.println(F("-> M1 speed 180, M2 speed -180"));
  motors[0].setSpeed(180);
  motors[1].setSpeed(-180);
  delay(2000);

  Serial.println(F("-> M1 speed -120, M2 speed 120"));
  motors[0].setSpeed(-120);
  motors[1].setSpeed(120);
  delay(2000);

  Serial.println(F("-> Both motors stop"));
  motors[0].stop();
  motors[1].stop();
  delay(1500);

  Serial.println();
}
