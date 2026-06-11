'''!
  @file DFRobot_N20SerialMotor.py
  @brief Raspberry Pi Modbus-RTU driver for DFR1277 serial N20 motor module.
  @copyright Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license The MIT License (MIT)
  @author JiaLi(zhixin.liu@dfrobot.com)
  @version V1.0.0
  @date 2026-05-09
  @url https://github.com/DFRobot/DFRobot_N20SerialMotor
'''

import serial
import time

import modbus_tk.defines as cst
from modbus_tk import modbus_rtu


class DFRobot_N20SerialMotor:
  '''!
    @brief DFR1277 serial motor module driver.
  '''

  BROADCAST_ADDR = 0x00
  DEVICE_VID = 0x3343
  DEVICE_PID = 0x04FD

  INPUTREG_VID = 0x0000
  INPUTREG_PID = 0x0001
  HOLDINGREG_ADDR = 0x0002
  HOLDINGREG_BAUDRATE = 0x0003
  INPUTREG_VERSION = 0x0005
  INPUTREG_STATE = 0x0006
  HOLDINGREG_SPEED = 0x0007
  HOLDINGREG_RESET = 0x0008
  FACTORY_RESET_VALUE = 0x0001

  ADDR_MIN = 0x01
  ADDR_MAX = 0x20

  BAUD_2400 = 0x0001
  BAUD_4800 = 0x0002
  BAUD_9600 = 0x0003
  BAUD_14400 = 0x0004
  BAUD_19200 = 0x0005
  BAUD_38400 = 0x0006
  BAUD_57600 = 0x0007
  BAUD_115200 = 0x0008

  STATE_STOP = 0
  STATE_FORWARD = 1
  STATE_REVERSE = 2
  STATE_UNKNOWN = 0xFFFF

  # Legacy aliases
  REG_VID = INPUTREG_VID
  REG_PID = INPUTREG_PID
  REG_ADDR = HOLDINGREG_ADDR
  REG_BAUD = HOLDINGREG_BAUDRATE
  REG_VERSION = INPUTREG_VERSION
  REG_STATE = INPUTREG_STATE
  REG_SPEED = HOLDINGREG_SPEED
  REG_RESET = HOLDINGREG_RESET
  VID = DEVICE_VID
  PID = DEVICE_PID

  def __init__(self, port, slave_addr=1, baudrate=9600, timeout=0.1):
    '''!
      @brief Constructor.
      @param port Serial port name, e.g. "/dev/ttyAMA0".
      @param slave_addr Modbus slave address.
      @param baudrate Host serial baudrate.
      @param timeout Serial timeout in seconds.
    '''
    self._port = port
    self._slave_addr = slave_addr
    self._baudrate = baudrate
    self._timeout = timeout
    self._ser = None
    self.master = None

  def begin(self):
    '''!
      @brief Open serial port and verify device at current address.
      @return bool True on success.
    '''
    if self._slave_addr < self.ADDR_MIN or self._slave_addr > self.ADDR_MAX:
      return False

    if self._ser is not None and self._ser.is_open:
      self.close()

    self._ser = serial.Serial(port=self._port, baudrate=self._baudrate, bytesize=8, parity='N', stopbits=1)
    self.master = modbus_rtu.RtuMaster(self._ser)
    self.master.set_timeout(self._timeout)
    time.sleep(0.5)

    for _ in range(3):
      if self._detect_device_address(self._slave_addr):
        return True
      time.sleep(0.1)

    return False

  def close(self):
    '''!
      @brief Close serial port.
    '''
    if self.master is not None:
      self.master.close()
      self.master = None
    if self._ser is not None and self._ser.is_open:
      self._ser.close()
      self._ser = None

  def set_speed(self, speed):
    '''!
      @brief Set motor speed.
      @param speed Range: -255~255. 0 stops the motor.
      @return bool True on success.
    '''
    if speed > 255:
      speed = 255
    if speed < -255:
      speed = -255

    if not self._write_holding_reg16(self._slave_addr, self.HOLDINGREG_SPEED, speed & 0xFFFF):
      time.sleep(0.05)
      return False
    return True

  def stop(self):
    '''!
      @brief Stop motor (equivalent to set_speed(0)).
      @return bool True on success.
    '''
    return self.set_speed(0)

  def set_device_addr(self, addr):
    '''!
      @brief Set module device address.
      @param addr Address range: 1~32.
      @return bool True on success.
    '''
    if addr < self.ADDR_MIN or addr > self.ADDR_MAX:
      return False
    if not self._write_holding_reg16(self._slave_addr, self.HOLDINGREG_ADDR, addr):
      return False
    self._slave_addr = addr
    time.sleep(0.05)
    return True

  def set_baudrate(self, baud_code):
    '''!
      @brief Configure baudrate.
      @return bool True on success.
    '''
    if not self._write_holding_reg16(self._slave_addr, self.HOLDINGREG_BAUDRATE, baud_code):
      return False
    time.sleep(0.05)
    return True

  def restoreFactory(self):
    '''!
      @brief Restore factory settings stored in the module.
      @return bool True on success. Factory settings take effect after power-on again.
    '''
    if not self._write_holding_reg16(self._slave_addr, self.HOLDINGREG_RESET, self.FACTORY_RESET_VALUE):
      return False
    time.sleep(0.05)
    return True

  def get_device_info(self):
    '''!
      @brief Read VID/PID/version.
      @return tuple (vid, pid, version).
    '''
    vid = self._read_input_reg16(self._slave_addr, self.INPUTREG_VID)
    pid = self._read_input_reg16(self._slave_addr, self.INPUTREG_PID)
    version = self._read_input_reg16(self._slave_addr, self.INPUTREG_VERSION)
    return (
      vid if vid is not None else 0,
      pid if pid is not None else 0,
      version if version is not None else 0
    )

  def scan(self, start_addr=ADDR_MIN, end_addr=ADDR_MAX):
    '''!
      @brief Scan slave addresses on current bus.
      @param start_addr Start address of scan range.
      @param end_addr End address of scan range.
      @return list Detected address list.
    '''
    if start_addr < self.ADDR_MIN:
      start_addr = self.ADDR_MIN
    if end_addr > self.ADDR_MAX:
      end_addr = self.ADDR_MAX
    if start_addr > end_addr:
      return []

    found = []
    for addr in range(start_addr, end_addr + 1):
      if self._detect_device_address(addr):
        found.append(addr)

    time.sleep(0.05)
    return found

  def _detect_device_address(self, addr):
    vid = self._read_input_reg16(addr, self.INPUTREG_VID)
    if vid is None:
      return False
    return vid == self.DEVICE_VID or vid == 0x4333

  def _read_input_reg16(self, dev_addr, reg):
    try:
      return list(self.master.execute(dev_addr, cst.READ_INPUT_REGISTERS, reg, 1))[0]
    except Exception:
      return None

  def _write_holding_reg16(self, dev_addr, reg, value):
    try:
      self.master.execute(dev_addr, cst.WRITE_SINGLE_REGISTER, reg, output_value=value & 0xFFFF)
      return True
    except Exception:
      return False

  # Legacy helpers
  def _is_supported_vid(self, vid):
    return vid == self.DEVICE_VID or vid == 0x4333

  def _read_reg(self, addr, reg):
    return self._read_input_reg16(addr, reg)

  def _write_reg(self, addr, reg, value):
    return self._write_holding_reg16(addr, reg, value)
