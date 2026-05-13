/*!
 * @file DFRobot_N20SerialMotor.h
 * @brief Arduino library for DFR1277 serial N20 motor driver.
 * @copyright Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author JiaLi(zhixin.liu@dfrobot.com)
 * @version V1.0.0
 * @date 2026-05-09
 * @url https://github.com/DFRobot/DFRobot_N20SerialMotor
 */

#ifndef DFROBOT_N20SERIALMOTOR_H
#define DFROBOT_N20SERIALMOTOR_H

#include "Arduino.h"
#include "DFRobot_RTU.h"

#if defined(ESP8266) || defined(ARDUINO_AVR_UNO)
#include <SoftwareSerial.h>
#else
#include <HardwareSerial.h>
#endif

#define N20SERIAL_BROADCAST_ADDR      0x00
#define N20SERIAL_DEVICE_VID          0x3343
#define N20SERIAL_DEVICE_PID          0x02C1

#define N20SERIAL_INPUTREG_VID        0x0000
#define N20SERIAL_INPUTREG_PID        0x0001
#define N20SERIAL_HOLDINGREG_ADDR     0x0002
#define N20SERIAL_HOLDINGREG_BAUDRATE 0x0003
#define N20SERIAL_INPUTREG_VERSION    0x0005
#define N20SERIAL_INPUTREG_STATE      0x0006
#define N20SERIAL_HOLDINGREG_SPEED    0x0007

#define N20SERIAL_ADDR_MIN            0x01
#define N20SERIAL_ADDR_MAX            0x20

/**
 * @enum eBaudrate_t
 * @brief Baudrate code defined by firmware.
 */
typedef enum {
  eBaud2400   = 0x0001,
  eBaud4800   = 0x0002,
  eBaud9600   = 0x0003,
  eBaud14400  = 0x0004,
  eBaud19200  = 0x0005,
  eBaud38400  = 0x0006,
  eBaud57600  = 0x0007,
  eBaud115200 = 0x0008
} eBaudrate_t;

/**
 * @enum eMotorState_t
 * @brief Motor running state.
 */
typedef enum {
  eMotorStop    = 0,
  eMotorForward = 1,
  eMotorReverse = 2,
  eMotorUnknown = 0xFFFF
} eMotorState_t;

/**
 * @struct sDeviceInfo_t
 * @brief Module information read from input registers.
 */
typedef struct {
  uint16_t vid;
  uint16_t pid;
  uint16_t version;
} sDeviceInfo_t;

class DFRobot_N20SerialMotor : public DFRobot_RTU {
public:
  /**
   * @fn DFRobot_N20SerialMotor
   * @brief Constructor.
   * @param addr Modbus slave address.
   * @param s Stream pointer used for Modbus-RTU communication.
   */
  DFRobot_N20SerialMotor(uint8_t addr, Stream *s);

#if defined(ESP8266) || defined(ARDUINO_AVR_UNO)
  /**
   * @fn DFRobot_N20SerialMotor
   * @brief Constructor.
   * @param addr Modbus slave address.
   * @param sSerial Software serial port used for Modbus-RTU communication.
   * @param baud Serial communication baudrate.
   */
  DFRobot_N20SerialMotor(uint8_t addr, SoftwareSerial *sSerial, uint32_t baud);
#else
  /**
   * @fn DFRobot_N20SerialMotor
   * @brief Constructor.
   * @param addr Modbus slave address.
   * @param hSerial Hardware serial port used for Modbus-RTU communication.
   * @param baud Serial communication baudrate.
   * @param rxpin RX pin, used by ESP32.
   * @param txpin TX pin, used by ESP32.
   */
  DFRobot_N20SerialMotor(uint8_t addr, HardwareSerial *hSerial, uint32_t baud, uint8_t rxpin = 0, uint8_t txpin = 0);
#endif

  /**
   * @fn begin
   * @brief Initialize serial motor object and verify device at current address.
   * @return int8_t
   * @retval 0 success
   * @retval -1 failed
   */
  int8_t begin(void);

  /**
   * @fn setSpeed
   * @brief Set motor speed.
   * @param speed Range: -255~255. 0 stops the motor.
   * @return int8_t
   * @retval 0 success
   * @retval -1 failed
   */
  int8_t setSpeed(int16_t speed);

  /**
   * @fn stop
   * @brief Stop motor (equivalent to setSpeed(0)).
   * @return int8_t
   * @retval 0 success
   * @retval -1 failed
   */
  int8_t stop(void);

  /**
   * @fn getSpeed
   * @brief Read motor speed register.
   * @return int16_t Current speed, returns 0 if read failed.
   */
  int16_t getSpeed(void);

  /**
   * @fn getMotorState
   * @brief Read motor state register.
   * @return eMotorState_t
   * @n     eMotorStop    Motor stopped
   * @n     eMotorForward Motor running forward
   * @n     eMotorReverse Motor running backward
   * @n     eMotorUnknown Read failed
   */
  eMotorState_t getMotorState(void);

  /**
   * @fn setDeviceAddr
   * @brief Set module device address.
   * @param addr Address range: 1~32.
   * @return int8_t
   * @retval 0 success
   * @retval -1 failed
   */
  int8_t setDeviceAddr(uint8_t addr);

  /**
   * @fn setBaudrate
   * @brief Configure baudrate.
   * @param baud Baudrate code.
   * @n     eBaud2400
   * @n     eBaud4800
   * @n     eBaud9600
   * @n     eBaud14400
   * @n     eBaud19200
   * @n     eBaud38400
   * @n     eBaud57600
   * @n     eBaud115200
   * @return int8_t
   * @retval 0 success
   * @retval -1 failed
   */
  int8_t setBaudrate(eBaudrate_t baud);

  /**
   * @fn getDeviceInfo
   * @brief Read VID/PID/version.
   * @return sDeviceInfo_t
   * @n       VID           The vendor ID of the device.
   * @n       PID           The product ID of the device.
   * @n       version       The version of the device.
   */
  sDeviceInfo_t getDeviceInfo(void);

  /**
   * @fn scan
   * @brief Scan slave addresses on current bus.
   * @param addrBuf Output address array.
   * @param bufLen Max items that can be stored in addrBuf.
   * @param startAddr Start address of scan range.
   * @param endAddr End address of scan range.
   * @return uint8_t Number of discovered devices.
   */
  uint8_t scan(uint8_t *addrBuf, uint8_t bufLen, uint8_t startAddr = N20SERIAL_ADDR_MIN, uint8_t endAddr = N20SERIAL_ADDR_MAX);

protected:
  bool detectDeviceAddress(uint8_t addr);
  bool readReg16Compat(uint8_t devAddr, uint16_t reg, uint16_t &value);
  uint8_t readInputReg(uint8_t devAddr, uint16_t reg, void *pBuf, uint8_t size);
  uint8_t readHoldingReg(uint8_t devAddr, uint16_t reg, void *pBuf, uint8_t size);
  uint8_t writeHoldingReg16(uint8_t devAddr, uint16_t reg, uint16_t value);

  Stream *_s;
  uint8_t _addr;
  uint32_t _baud;
  bool _autoBegin;
#if defined(ESP8266) || defined(ARDUINO_AVR_UNO)
  SoftwareSerial *_serial;
#else
  HardwareSerial *_serial;
  uint8_t _rxpin;
  uint8_t _txpin;
#endif
};

#endif
