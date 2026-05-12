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

#define N20SERIAL_BROADCAST_ADDR      0x00
#define N20SERIAL_DEVICE_VID          0x3343
#define N20SERIAL_DEVICE_PID          0x02C1

#define N20SERIAL_INPUTREG_VID        0x0000
#define N20SERIAL_INPUTREG_PID        0x0001
#define N20SERIAL_HOLDINGREG_ADDR     0x0002
#define N20SERIAL_HOLDINGREG_BAUDRATE 0x0003
#define N20SERIAL_HOLDINGREG_VS       0x0004
#define N20SERIAL_INPUTREG_VERSION    0x0005
#define N20SERIAL_INPUTREG_STATE      0x0006
#define N20SERIAL_HOLDINGREG_SPEED    0x0007
#define N20SERIAL_HOLDINGREG_RESET    0x0008

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
 * @enum eParity_t
 * @brief UART parity configuration.
 */
typedef enum {
  eParityNone = 0x00,
  eParityEven = 0x01,
  eParityOdd  = 0x02
} eParity_t;

/**
 * @enum eStopBit_t
 * @brief UART stop bit configuration.
 */
typedef enum {
  eStopBit0_5 = 0x00,
  eStopBit1   = 0x01,
  eStopBit1_5 = 0x02,
  eStopBit2   = 0x03
} eStopBit_t;

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
   * @fn getDeviceAddr
   * @brief Read current module address.
   * @return uint8_t Device address.
   */
  uint8_t getDeviceAddr(void);

  /**
   * @fn setBaudrate
   * @brief Configure baudrate/parity/stop bits.
   * @param baud Baudrate code.
   * @n     eBaud2400
   * @n     eBaud4800
   * @n     eBaud9600
   * @n     eBaud14400
   * @n     eBaud19200
   * @n     eBaud38400
   * @n     eBaud57600
   * @n     eBaud115200
   * @param stopBits Stop bit code.
   * @n     eStopBit0_5
   * @n     eStopBit1
   * @n     eStopBit1_5
   * @n     eStopBit2
   * @param parity Parity code.
   * @n     eParityNone
   * @n     eParityEven
   * @n     eParityOdd
   * @return int8_t
   * @retval 0 success
   * @retval -1 failed
   */
  int8_t setBaudrate(eBaudrate_t baud, eStopBit_t stopBits = eStopBit1, eParity_t parity = eParityNone);

  /**
   * @fn restoreFactory
   * @brief Restore factory configuration by writing RESET register.
   * @return int8_t
   * @retval 0 success
   * @retval -1 failed
   */
  int8_t restoreFactory(void);

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
};

#endif
