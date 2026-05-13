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

/* ---------------------------------------------------------------------------------------------------------------------
  *    board   |             MCU                | Leonardo/Mega2560/M0 |    UNO    | ESP8266 | ESP32 |  microbit  |   m0  |
  *     VCC    |              5V                |         5V           |     5V    |    5V   |   5V  |     X      |   5V  |
  *     GND    |              GND               |        GND           |    GND    |   GND   |  GND  |     X      |  GND  |
  *     RX     |              TX                |     Serial1 TX1      |     4     |   4/D7  | 25/D2 |     X      |  tx1  |
  *     TX     |              RX                |     Serial1 RX1      |     5     |   5/D6  | 26/D3 |     X      |  rx1  |
  * ----------------------------------------------------------------------------------------------------------------------*/
/* Baud rate can be changed */

#if defined(ESP8266) || defined(ARDUINO_AVR_UNO)
SoftwareSerial n20Serial(4, 5);
DFRobot_N20SerialMotor motor(1, &n20Serial, 9600);
#elif defined(ESP32)
DFRobot_N20SerialMotor motor(1, &Serial1, 9600, /*D2*/ D2, /*D3*/ D3);
#else
DFRobot_N20SerialMotor motor(1, &Serial1, 9600);
#endif

void setup()
{
  Serial.begin(115200);

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
