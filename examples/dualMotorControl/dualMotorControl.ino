/*!
 * @file dualMotorControl.ino
 * @brief Two motors control demo.
 * @details Scan bus addresses and control 2 cascaded motors by Modbus-RTU.
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

#define MOTOR1_ADDR 1
#define MOTOR2_ADDR 2
#define MOTOR_BAUD 9600

const uint8_t motorCount = 2;

#if defined(ESP8266) || defined(ARDUINO_AVR_UNO)
SoftwareSerial n20Serial(4, 5);
DFRobot_N20SerialMotor motors[] = {
  DFRobot_N20SerialMotor(MOTOR1_ADDR, &n20Serial),
  DFRobot_N20SerialMotor(MOTOR2_ADDR, &n20Serial)
};
#elif defined(ESP32)
DFRobot_N20SerialMotor motors[] = {
  DFRobot_N20SerialMotor(MOTOR1_ADDR, &Serial1),
  DFRobot_N20SerialMotor(MOTOR2_ADDR, &Serial1)
};
#else
DFRobot_N20SerialMotor motors[] = {
  DFRobot_N20SerialMotor(MOTOR1_ADDR, &Serial1),
  DFRobot_N20SerialMotor(MOTOR2_ADDR, &Serial1)
};
#endif
/**
 * note : The correspondence between motor addresses
  * 1. Motor1: Address 1
  * 2. Motor2: Address 2
  *       ...:...
  * n. Motorn: Address n
  *
  * usge:
  * 1. Motors[0] is Motor1
  * 2. Motors[1] is Motor2
  *       ...:...
  * n. Motors[n-1] is Motorn
  */

void setup()
{
  uint8_t i = 0;

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
  Serial.println(F("  Dual Motor Control Example"));
  Serial.println(F("========================================"));

  uint8_t scanBuf[32] = { 0 };
  uint8_t foundCount = 0;
  uint8_t j = 0;
  const uint8_t motorAddrs[] = { MOTOR1_ADDR, MOTOR2_ADDR };

  for (i = 0; i < motorCount; i++) {
    if (motors[i].begin() == 0) {
      Serial.print(F("[OK] Motor "));
      Serial.print(i + 1);
      Serial.print(F(" initialized (Modbus addr: "));
      Serial.print(motorAddrs[i]);
      Serial.println(F(")"));
    } 
    else {
      Serial.print(F("[ERROR] Motor "));
      Serial.print(i + 1);
      Serial.println(F(" init failed, You can check whether the address is correct through the address scan."));
    }
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
  motors[0].setSpeed(0);
  motors[1].setSpeed(0);
  delay(1500);

  Serial.println();
}
