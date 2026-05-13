/*!
 * @file modify_slave_address.ino
 * @brief DFR1277 slave address configuration demo.
 * @details Initialize by current address and only modify slave address.
 * @copyright Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author JiaLi(zhixin.liu@dfrobot.com)
 * @version V1.0.0
 * @date 2026-05-12
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
SoftwareSerial n20Serial(4, 5);  // RX, TX
#endif

// Current module configuration (before running this sketch).
const uint8_t CURRENT_ADDR = 1;
const unsigned long CURRENT_HOST_BAUD = 9600;

// Target module configuration.
const uint8_t TARGET_ADDR = 2;

#if defined(ESP8266) || defined(ARDUINO_AVR_UNO)
DFRobot_N20SerialMotor motorCurrent(CURRENT_ADDR, &n20Serial, CURRENT_HOST_BAUD);
#elif defined(ESP32)
DFRobot_N20SerialMotor motorCurrent(CURRENT_ADDR, &Serial1, CURRENT_HOST_BAUD, /*D2*/ D2, /*D3*/ D3);
#else
DFRobot_N20SerialMotor motorCurrent(CURRENT_ADDR, &Serial1, CURRENT_HOST_BAUD);
#endif

void setup()
{
  Serial.begin(115200);

  Serial.println("Step1: Init with current address...");
  while (motorCurrent.begin() != 0) {
    Serial.println("Init failed. Check CURRENT_ADDR/CURRENT_HOST_BAUD/wiring.");
    delay(1000);
  }
  Serial.println("Init success.");

  if (CURRENT_ADDR != TARGET_ADDR) {
    Serial.print("Step2: Set slave address to ");
    Serial.println(TARGET_ADDR);
    if (motorCurrent.setDeviceAddr(TARGET_ADDR) != 0) {
      Serial.println("Set slave address failed.");
      while (1) {
        delay(1000);
      }
    }
    Serial.println("Set slave address success.");
    delay(100);
  } else {
    Serial.println("Step2: Skip address change (same address).");
  }

  Serial.println("Configuration written.");
  Serial.print("Please communicate with new addr=");
  Serial.print(TARGET_ADDR);
  Serial.print(", baud=");
  Serial.println(CURRENT_HOST_BAUD);
}

void loop()
{
  delay(1000);
}
 
