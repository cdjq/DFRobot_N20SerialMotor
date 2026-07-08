/*!
 * @file singleMotorControl.ino
 * @brief Single motor control demo.
 * @details Demo for initializing one serial motor module and driving forward/backward.
 * @copyright Copyright (c) 2026 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author JiaLi(zhixin.liu@dfrobot.com)
 * @version V1.0.0
 * @date 2026-05-09
 * @url https://github.com/DFRobot/DFRobot_N20SerialMotor
 */

#include "DFRobot_N20SerialMotor.h"

#if defined(ESP8266) || defined(ARDUINO_AVR_UNO)
#include <SoftwareSerial.h>
#endif

/* -----------------------------------------------------------------------------------------------------------------------
  *    board   |             MCU                | Leonardo/Mega2560/M0 |    UNO    | ESP8266 | ESP32 |  microbit  |   m0  |
  *     VCC    |              5V                |         5V           |     5V    |    5V   |   5V  |     X      |   5V  |
  *     GND    |              GND               |        GND           |    GND    |   GND   |  GND  |     X      |  GND  |
  *     RX     |              TX                |     Serial1 TX1      |     5     |   5/D6  | 25/D2 |     X      |  tx1  |
  *     TX     |              RX                |     Serial1 RX1      |     4     |   4/D7  | 26/D3 |     X      |  rx1  |
  * ----------------------------------------------------------------------------------------------------------------------*/
/* Baud rate can be changed */

#define MOTOR_ADDR 1
#define MOTOR_BAUD 9600

#if defined(ESP8266) || defined(ARDUINO_AVR_UNO)
SoftwareSerial n20Serial(4, 5);
DFRobot_N20SerialMotor motor(MOTOR_ADDR, &n20Serial);
#elif defined(ESP32)
DFRobot_N20SerialMotor motor(MOTOR_ADDR, &Serial1);
#else
DFRobot_N20SerialMotor motor(MOTOR_ADDR, &Serial1);
#endif

void setup()
{
  Serial.begin(115200);

#if defined(ESP8266) || defined(ARDUINO_AVR_UNO)
  n20Serial.begin(MOTOR_BAUD);
#elif defined(ESP32)
  Serial1.begin(MOTOR_BAUD, SERIAL_8N1, /*D2*/ D2, /*D3*/ D3);
#else
  Serial1.begin(MOTOR_BAUD);
#endif

  delay(1000);

  Serial.println();
  Serial.println(F("========================================"));
  Serial.println(F("  DFRobot N20 Serial Motor"));
  Serial.println(F("  Single Motor Control Example"));
  Serial.println(F("========================================"));

  while (motor.begin() != 0) {
    Serial.println(F("[ERROR] Motor init failed, retrying..."));
    delay(1000);
  }

  Serial.println(F("[OK] Motor initialized (Modbus addr: 1)"));
  Serial.println(F("Starting speed control loop..."));
  Serial.println();
}

void loop()
{
  Serial.println(F("-> Speed 200"));
  motor.setSpeed(200);
  delay(2000);

  Serial.println(F("-> Speed 80"));
  motor.setSpeed(80);
  delay(1200);

  Serial.println(F("-> Speed -200"));
  motor.setSpeed(-200);
  delay(2000);

  Serial.println(F("-> Stop"));
  motor.setSpeed(0);
  delay(1500);

  Serial.println();
}
