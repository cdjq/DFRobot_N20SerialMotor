# DFRobot_N20SerialMotor

===========================

* [中文版](./README_CN.md)

Arduino library for the N20 motor driver module. Based on the Modbus-RTU protocol, it supports motor speed control, address configuration, serial parameter configuration, and multi-device cascade scanning.

![product image]

## Product Link (https://www.dfrobot.com)
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

* Verify module communication by Modbus-RTU<br/>
* Set motor speed (`-255~255`, 0 stops the motor)<br/>
* Configure slave address (`1~247`); takes effect after power-on again<br/>
* Configure baudrate; takes effect after power-on again<br/>
* Restore factory settings (UART and device address); defaults take effect after power-on again<br/>
* Read VID/PID/version and scan cascaded devices

## Installation

Download this library and dependency library before use:
* https://github.com/DFRobot/DFRobot_RTU.git
Copy both folders into `Arduino/libraries`, then open examples and run.

## Methods

```C++

  /**
   * @fn DFRobot_N20SerialMotor
   * @brief Constructor.
   * @param addr Modbus slave address, range: 1~247.
   * @param s Stream pointer used for Modbus-RTU communication.
   */
  DFRobot_N20SerialMotor(uint8_t addr, Stream *s);

  /**
   * @fn begin
   * @brief Verify device at current address.
   * @n     Initialize the serial port in user sketch before calling this function.
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
   * @fn setDeviceAddr
   * @brief Set module device address.
   * @param addr Address range: 1~247.
   * @n     The new address takes effect after the module is powered on again.
   * @n     This function does not update the internal communication address;
   * @n     recreate the object with the new address after the module restarts.
   * @return int8_t
   * @retval 0 success
   * @retval -1 failed
   */
  int8_t setDeviceAddr(uint8_t addr);

  /**
   * @fn setBaudrate
   * @brief Configure baudrate, Only the baud rate can be modified, and the stop bit and check bit cannot be modified.
   * @param baud Baudrate code.
   * @n     eBaud2400
   * @n     eBaud4800
   * @n     eBaud9600
   * @n     eBaud14400
   * @n     eBaud19200
   * @n     eBaud38400
   * @n     eBaud57600
   * @n     eBaud115200
   * @n     The new baudrate takes effect after the module is powered on again.
   * @n     This function does not update the host serial baudrate;
   * @n     reinitialize the serial port with the new baudrate after the module restarts.
   * @return int8_t
   * @retval 0 success
   * @retval -1 failed
   */
  int8_t setBaudrate(eBaudrate_t baud);

  /**
   * @fn restoreFactory
   * @brief Restoring factory Settings mainly involves setting the uart and device addresses back to their default values
   * @n     Factory settings take effect after the module is powered on again.
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
   * @fn scanAddress
   * @brief Scan slave addresses on current bus.
   * @param addrBuf Output address array.
   * @param bufLen Max items that can be stored in addrBuf.
   * @param startAddr Start address of scan range.
   * @param endAddr End address of scan range.
   * @return uint8_t Number of discovered devices.
   */
  uint8_t scanAddress(uint8_t *addrBuf, uint8_t bufLen, uint8_t startAddr = 1, uint8_t endAddr = 247);
```

## Examples

* `singleMotorControl`: Initialize one motor and run forward/reverse speed control.
* `dualMotorControl`: Initialize two cascaded motors and control them on the same bus.
* `addressScan`: Scan the Modbus-RTU bus and print discovered motor addresses.

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
