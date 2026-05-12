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

#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
#include "SoftwareSerial.h"
SoftwareSerial n20Serial(2, 3);  // RX, TX
#define N20_PORT n20Serial
#else
#define N20_PORT Serial1
#endif

// Current module configuration (before running this sketch).
const uint8_t CURRENT_ADDR = 1;
const unsigned long CURRENT_HOST_BAUD = 9600;

// Target module configuration.
const uint8_t TARGET_ADDR = 2;

DFRobot_N20SerialMotor motorCurrent(CURRENT_ADDR, &N20_PORT);

void setup()
{
  Serial.begin(115200);
  N20_PORT.begin(CURRENT_HOST_BAUD);

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
 
