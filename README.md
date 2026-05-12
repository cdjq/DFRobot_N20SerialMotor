# DFRobot_N20SerialMotor

===========================

* [中文版](./README_CN.md)

DFRobot_N20SerialMotor is an Arduino library for DFR1277 Modbus-RTU serial N20 motor driver. It supports speed control, address configuration, UART parameter configuration, and multi-device scan on one bus.

![product image]

## Product Link ()
    SKU: DFR1277

## Table of Contents

  * [Summary](#summary)
  * [Installation](#installation)
  * [Methods](#methods)
  * [Examples](#examples)
  * [Compatibility](#compatibility)
  * [History](#history)
  * [Credits](#credits)

## Summary

* Initialize module and verify communication by Modbus-RTU<br/>
* Set motor speed (`-255~255`) and stop quickly<br/>
* Configure slave address (`1~32`)<br/>
* Configure baudrate/parity/stop bits<br/>
* Read VID/PID/version and scan cascaded devices

## Installation

Download this library and dependency library before use:

* https://github.com/DFRobot/DFRobot_N20SerialMotor.git
* https://github.com/DFRobot/DFRobot_RTU.git

Copy both folders into `Arduino/libraries`, then open examples and run.

## Methods

```C++

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
  uint8_t scan(uint8_t *addrBuf, uint8_t bufLen, uint8_t startAddr = 1, uint8_t endAddr = 32);
```

## Examples

* [singleMotorControl](./examples/singleMotorControl/singleMotorControl.ino)
* [dualMotorControl](./examples/dualMotorControl/dualMotorControl.ino)
* [modify_slave_address](./examples/modify_slave_address/modify_slave_address.ino)

## Compatibility

MCU                | Work Well    |   Work Wrong    | Untested    | Remarks
------------------ | :----------: | :-------------: | :---------: | :----:
Arduino Uno        |      √       |                 |             |
Arduino MEGA2560   |      √       |                 |             |
Arduino Leonardo   |      √       |                 |             |
FireBeetle-ESP8266 |      √       |                 |             |
FireBeetle-ESP32   |      √       |                 |             |
FireBeetle-M0      |      √       |                 |             |
Micro:bit          |              |                 |     √       |

## History

- 2026-05-09 - Version 1.0.0 released.

## Credits

Written by JiaLi(zhixinliu@dfrobot.com), 2026. (Welcome to our [website](https://www.dfrobot.com/))
