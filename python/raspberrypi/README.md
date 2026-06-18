# DFRobot_N20SerialMotor Python

===========================

* [中文版](./README_CN.md)

Raspberry Pi Python library for the N20 motor driver module. Based on the Modbus-RTU protocol, it supports motor speed control, address configuration, serial parameter configuration, and multi-device cascade scanning.

## Product Link (https://www.dfrobot.com)
    SKU: DFR1277

## Table of Contents

  * [Summary](#summary)
  * [Installation](#installation)
  * [Methods](#methods)
  * [Examples](#examples)
  * [History](#history)
  * [Credits](#credits)

## Summary

* Use an opened serial port to verify module communication<br/>
* Set motor speed (`-255~255`, 0 stops the motor)<br/>
* Set/read slave address<br/>
* Configure baudrate<br/>
* Restore factory settings (UART and device address); defaults take effect after power-on again<br/>
* Read module VID/PID/version and scan addresses

## Installation

Install dependency:

```bash
pip3 install modbus_tk pyserial
```

Copy `DFRobot_N20SerialMotor.py` and example folder to your Raspberry Pi project.

## Methods

```python

  def __init__(self, ser=None, slave_addr=1, bus=None):
    '''!
      @brief Constructor.
      @param ser Opened serial port object. Required when bus is None.
      @param slave_addr Modbus slave address.
      @param bus Another instance to share the serial bus with.
    '''

  def begin(self):
    '''!
      @brief Verify target device on the opened serial port.
      @return bool True on success, False on failure.
    '''

  def close(self):
    '''!
      @brief Close Modbus master owned by this instance.
    '''

  def set_speed(self, speed):
    '''!
      @brief Set motor speed.
      @param speed Range: -255~255, sign controls direction. 0 stops the motor.
      @return bool True on success, False on failure.
    '''

  def set_device_addr(self, addr):
    '''!
      @brief Set module device address.
      @param addr Range: 1~247.
      @n     The new address takes effect after the module is powered on again.
      @n     This method does not update the internal communication address;
      @n     recreate the object with the new address after the module restarts.
      @return bool True on success, False on failure.
    '''

  def set_baudrate(self, baud_code):
    '''!
      @brief Configure baudrate, Only the baud rate can be modified, and the stop bit and check bit cannot be modified.
      @param baud_code Baudrate code.
      @n     BAUD_2400
      @n     BAUD_4800
      @n     BAUD_9600
      @n     BAUD_14400
      @n     BAUD_19200
      @n     BAUD_38400
      @n     BAUD_57600
      @n     BAUD_115200
      @n     The new baudrate takes effect after the module is powered on again.
      @n     This method does not update the host serial baudrate;
      @n     reopen the serial port with the new baudrate after the module restarts.
      @return bool True on success, False on failure.
    '''

  def restore_factory(self):
    '''!
      @brief Restoring factory Settings mainly involves setting the uart and device addresses back to their default values.
      @n     Factory settings take effect after the module is powered on again.
      @return bool True on success, False on failure.
    '''

  def get_device_info(self):
    '''!
      @brief Read VID/PID/version.
      @return tuple (vid, pid, version).
    '''

  def scan_address(self, start_addr=1, end_addr=247):
    '''!
      @brief Scan bus addresses.
      @param start_addr Start address of scan range.
      @param end_addr End address of scan range.
      @return list Detected address list.
    '''
```
## History

- 2026-05-09 - Version 1.0.0 released.

## Credits

Written by JiaLi(zhixinliu@dfrobot.com), 2026. (Welcome to our [website](https://www.dfrobot.com/))
