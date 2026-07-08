/*!
 * @file addressScan.ino
 * @brief Scan N20 serial motor addresses on the Modbus-RTU bus.
 * @details Scan the configured address range and print the discovered module addresses.
 * @copyright Copyright (c) 2026 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author JiaLi(zhixin.liu@dfrobot.com)
 * @version V1.0.0
 * @date 2026-06-18
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
/* Baud rate and scan range can be changed */

#define MOTOR_BAUD 9600
#define SCAN_START_ADDR 1
#define SCAN_END_ADDR 32
#define SCAN_BUF_LEN 32

#if defined(ESP8266) || defined(ARDUINO_AVR_UNO)
SoftwareSerial n20Serial(4, 5);
DFRobot_N20SerialMotor scanner(SCAN_START_ADDR, &n20Serial);
#elif defined(ESP32)
DFRobot_N20SerialMotor scanner(SCAN_START_ADDR, &Serial1);
#else
DFRobot_N20SerialMotor scanner(SCAN_START_ADDR, &Serial1);
#endif

void setup()
{
  uint8_t scanBuf[SCAN_BUF_LEN] = { 0 };
  uint8_t foundCount = 0;
  uint8_t j = 0;

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
  Serial.println(F("  Address Scan Example"));
  Serial.println(F("========================================"));
  Serial.print(F("[SCAN] Range: "));
  Serial.print(SCAN_START_ADDR);
  Serial.print(F("~"));
  Serial.println(SCAN_END_ADDR);
  Serial.println(F("[SCAN] Scanning bus..."));
  Serial.println("Please be patient and wait.");

  foundCount = scanner.scanAddress(scanBuf, sizeof(scanBuf), SCAN_START_ADDR, SCAN_END_ADDR);

  if (foundCount == 0) {
    Serial.println(F("[SCAN] No device found on bus."));
  } else {
    Serial.print(F("[SCAN] Found "));
    Serial.print(foundCount);
    Serial.println(F(" device(s), address:"));
    for (j = 0; j < foundCount; j++) {
      Serial.print(scanBuf[j]);
      Serial.print(F(" "));
    }
    Serial.println();
  }

  Serial.println(F("[SCAN] Done."));
}

void loop()
{
}
