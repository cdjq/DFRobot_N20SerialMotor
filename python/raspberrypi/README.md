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
pip3 install pyserial
```

Copy `DFRobot_N20SerialMotor.py` and example folder to your Raspberry Pi project.

## Methods

```python

  def __init__(self, port, slave_addr=1, baudrate=9600, timeout=0.2):
    '''!
      @brief Constructor.
      @param port Serial port name, e.g. "/dev/ttyUSB0".
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

  def set_baudrate(self, baud_code, stop_bit=STOP_BIT_1, parity=PARITY_NONE):
    '''!
      @brief Configure baudrate and UART format.
      @param baud_code Baudrate code.
      @n     BAUD_2400
      @n     BAUD_4800
      @n     BAUD_9600
      @n     BAUD_14400
      @n     BAUD_19200
      @n     BAUD_38400
      @n     BAUD_57600
      @n     BAUD_115200
      @param stop_bit Stop bit code.
      @n     STOP_BIT_0_5
      @n     STOP_BIT_1
      @n     STOP_BIT_1_5
      @n     STOP_BIT_2
      @param parity Parity code.
      @n     PARITY_NONE
      @n     PARITY_EVEN
      @n     PARITY_ODD
      @return bool True on success.
    '''

  def restore_factory(self):
    '''!
      @brief Restore factory settings.
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

## Examples

* [single_motor_control](./examples/single_motor_control/single_motor_control.py)
* [dual_motor_control](./examples/dual_motor_control/dual_motor_control.py)
* [modify_slave_address](./examples/modify_slave_address/modify_slave_address.py)

## History

- 2026-05-09 - Version 1.0.0 released.

## Credits

Written by JiaLi(zhixinliu@dfrobot.com), 2026. (Welcome to our [website](https://www.dfrobot.com/))
