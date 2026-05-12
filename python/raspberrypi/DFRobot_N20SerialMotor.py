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
import struct
import time


class DFRobot_N20SerialMotor:
  '''!
    @brief DFR1277 serial motor module driver.
  '''

  REG_VID = 0x0000
  REG_PID = 0x0001
  REG_ADDR = 0x0002
  REG_BAUD = 0x0003
  REG_VERSION = 0x0005
  REG_STATE = 0x0006
  REG_SPEED = 0x0007

  VID = 0x3343
  PID = 0x02C1

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

  def __init__(self, port, slave_addr=1, baudrate=9600, timeout=0.2):
    '''!
      @brief Constructor.
      @param port Serial port name, e.g. "/dev/ttyUSB0".
      @param slave_addr Modbus slave address.
      @param baudrate Host serial baudrate.
      @param timeout Serial timeout in seconds.
    '''
    self._port = port
    self._slave_addr = slave_addr
    self._baudrate = baudrate
    self._timeout = timeout
    self._ser = None

  def begin(self):
    '''!
      @brief Open serial port and check target device.
      @return bool True if device is reachable.
    '''
    self._ser = serial.Serial(self._port, self._baudrate, timeout=self._timeout)
    try:
      return self._is_supported_vid(self._read_reg(self._slave_addr, self.REG_VID))
    except Exception:
      return False

  def close(self):
    '''!
      @brief Close serial port.
    '''
    if self._ser is not None and self._ser.is_open:
      self._ser.close()

  def set_speed(self, speed):
    '''!
      @brief Set motor speed.
      @param speed -255~255, sign controls direction.
      @return bool True on success.
    '''
    if speed > 255:
      speed = 255
    if speed < -255:
      speed = -255
    value = speed & 0xFFFF
    return self._write_reg(self._slave_addr, self.REG_SPEED, value)

  def stop(self):
    '''!
      @brief Stop motor.
      @return bool True on success.
    '''
    return self.set_speed(0)

  def get_speed(self):
    '''!
      @brief Read speed register.
      @return int Speed value.
    '''
    value = self._read_reg(self._slave_addr, self.REG_SPEED)
    if value & 0x8000:
      return value - 0x10000
    return value

  def get_motor_state(self):
    '''!
      @brief Read motor state register.
      @return int STATE_STOP/STATE_FORWARD/STATE_REVERSE.
    '''
    return self._read_reg(self._slave_addr, self.REG_STATE)

  def set_device_addr(self, addr):
    '''!
      @brief Set module address.
      @param addr 1~32.
      @return bool True on success.
    '''
    if addr < 1 or addr > 32:
      return False
    ok = self._write_reg(self._slave_addr, self.REG_ADDR, addr)
    if ok:
      self._slave_addr = addr
      time.sleep(0.05)
    return ok

  def set_baudrate(self, baud_code):
    '''!
      @brief Configure baudrate.
      @return bool True on success.
    '''
    ok = self._write_reg(self._slave_addr, self.REG_BAUD, baud_code)
    if ok:
      time.sleep(0.1)
    return ok

  def get_device_info(self):
    '''!
      @brief Read VID/PID/version.
      @return tuple (vid, pid, version).
    '''
    vid = self._read_reg(self._slave_addr, self.REG_VID)
    pid = self._read_reg(self._slave_addr, self.REG_PID)
    version = self._read_reg(self._slave_addr, self.REG_VERSION)
    return (vid, pid, version)

  def scan(self, start_addr=1, end_addr=32):
    '''!
      @brief Scan bus addresses.
      @return list Detected address list.
    '''
    if start_addr < 1:
      start_addr = 1
    if end_addr > 32:
      end_addr = 32

    found = []
    for addr in range(start_addr, end_addr + 1):
      try:
        if self._is_supported_vid(self._read_reg(addr, self.REG_VID)):
          found.append(addr)
      except Exception:
        pass
    return found

  def _is_supported_vid(self, vid):
    return vid == self.VID or vid == 0x4333

  def _read_reg(self, addr, reg):
    frame = struct.pack(">BBHH", addr, 0x03, reg, 0x0001)
    frame += self._crc16(frame)
    self._ser.reset_input_buffer()
    self._ser.write(frame)
    resp = self._ser.read(7)

    if len(resp) != 7:
      raise RuntimeError("Read timeout")
    if resp[0] != addr or resp[1] != 0x03 or resp[2] != 0x02:
      raise RuntimeError("Invalid response")
    if self._crc16(resp[:-2]) != resp[-2:]:
      raise RuntimeError("CRC error")

    return (resp[3] << 8) | resp[4]

  def _write_reg(self, addr, reg, value):
    frame = struct.pack(">BBHH", addr, 0x06, reg, value & 0xFFFF)
    frame += self._crc16(frame)
    self._ser.reset_input_buffer()
    self._ser.write(frame)
    resp = self._ser.read(8)

    if len(resp) != 8:
      return False
    if self._crc16(resp[:-2]) != resp[-2:]:
      return False

    return resp[:6] == frame[:6]

  @staticmethod
  def _crc16(data):
    crc = 0xFFFF
    for byte in data:
      crc ^= byte
      for _ in range(8):
        if crc & 0x0001:
          crc = (crc >> 1) ^ 0xA001
        else:
          crc >>= 1
    return struct.pack("<H", crc)
