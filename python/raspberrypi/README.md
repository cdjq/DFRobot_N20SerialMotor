# DFRobot_N20SerialMotor Python

===========================

* [中文版](./README_CN.md)

DFRobot_N20SerialMotor Python is a Raspberry Pi Modbus-RTU driver for DFR1277 serial N20 motor module.

## Product Link ()
    SKU: DFR1277

## Table of Contents

  * [Summary](#summary)
  * [Installation](#installation)
  * [Methods](#methods)
  * [Examples](#examples)
  * [History](#history)
  * [Credits](#credits)

## Summary

* Open serial port and initialize module communication<br/>
* Set speed and stop motor<br/>
* Set/read slave address<br/>
* Configure baudrate/parity/stop bits<br/>
* Read module VID/PID/version and scan addresses

## Installation

Install dependency:

```bash
pip3 install modbus_tk
```

Copy `DFRobot_N20SerialMotor.py` and example folder to your Raspberry Pi project.

## Methods

```python

  def __init__(self, port, slave_addr=1, baudrate=9600, timeout=0.2):
    '''!
      @brief Constructor.
      @param port Serial port name, e.g. "/dev/ttyAMA0".
      @param slave_addr Modbus slave address.
      @param baudrate Host serial baudrate.
      @param timeout Serial timeout in seconds.
    '''

  def begin(self):
    '''!
      @brief Open serial port and check target device.
      @return bool True if device is reachable.
    '''

  def close(self):
    '''!
      @brief Close serial port.
    '''

  def set_speed(self, speed):
    '''!
      @brief Set motor speed.
      @param speed Range: -255~255, sign controls direction.
      @return bool True on success.
    '''

  def stop(self):
    '''!
      @brief Stop motor.
      @return bool True on success.
    '''

  def get_speed(self):
    '''!
      @brief Read speed register.
      @return int Speed value -255~255.
    '''

  def get_motor_state(self):
    '''!
      @brief Read motor state register.
      @return int
      @n     STATE_STOP    0, motor stopped
      @n     STATE_FORWARD 1, motor running forward
      @n     STATE_REVERSE 2, motor running backward
    '''

  def set_device_addr(self, addr):
    '''!
      @brief Set module device address.
      @param addr Range: 1~32.
      @return bool True on success.
    '''

  def set_baudrate(self, baud_code):
    '''!
      @brief Configure baudrate.
      @param baud_code Baudrate code.
      @n     BAUD_2400
      @n     BAUD_4800
      @n     BAUD_9600
      @n     BAUD_14400
      @n     BAUD_19200
      @n     BAUD_38400
      @n     BAUD_57600
      @n     BAUD_115200
      @return bool True on success.
    '''

  def get_device_info(self):
    '''!
      @brief Read VID/PID/version.
      @return tuple (vid, pid, version).
    '''

  def scan(self, start_addr=1, end_addr=32):
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
