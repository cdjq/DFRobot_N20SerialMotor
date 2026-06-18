'''!
  @file DFRobot_N20SerialMotor.py
  @brief Raspberry Pi Modbus-RTU driver for serial N20 motor module.
  @copyright Copyright (c) 2026 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license The MIT License (MIT)
  @author JiaLi(zhixin.liu@dfrobot.com)
  @version V1.0.0
  @date 2026-05-09
  @url https://github.com/DFRobot/DFRobot_N20SerialMotor
'''

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
  ADDR_MAX = 0xF7

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

  def __init__(self, ser=None, slave_addr=1, bus=None):
    '''!
      @brief Constructor.
      @param ser Opened serial port object. Required when bus is None.
      @param slave_addr Modbus slave address.
      @param bus Another DFRobot_N20SerialMotor instance to share the serial bus with.
    '''
    self._slave_addr = slave_addr
    self._owns_master = False
    self._ser = None
    self._debug = False

    if bus is not None:
      self.master = bus.master
      self._ser = bus._ser
    else:
      if ser is None:
        raise ValueError("ser is required when bus is not provided")
      self._ser = ser
      self.master = modbus_rtu.RtuMaster(self._ser)
      self.master.set_timeout(1.0)
      self._owns_master = True

  def begin(self):
    '''!
      @brief Verify device at current address.
      @return bool True on success, False on failure.
    '''
    if self._slave_addr < self.ADDR_MIN or self._slave_addr > self.ADDR_MAX:
      return False

    time.sleep(0.5)

    for _ in range(3):
      if self._detect_device_address(self._slave_addr):
        return True
      time.sleep(0.1)

    return False

  def close(self):
    '''!
      @brief Close Modbus master owned by this instance.
    '''
    if self._owns_master and self.master is not None:
      self.master.close()
      self._ser = None
    self.master = None

  def set_speed(self, speed):
    '''!
      @brief Set motor speed.
      @param speed Range: -255~255. 0 stops the motor.
      @return bool True on success, False on failure.
    '''
    if speed > 255:
      speed = 255
    if speed < -255:
      speed = -255

    if not self._write_reg(self._slave_addr, self.HOLDINGREG_SPEED, speed & 0xFFFF):
      time.sleep(0.05)
      return False
    return True

  def set_device_addr(self, addr):
    '''!
      @brief Set module device address.
      @param addr Address range: 1~247.
      @return bool True on success, False on failure.
    '''
    if addr < self.ADDR_MIN or addr > self.ADDR_MAX:
      return False
    if not self._write_reg(self._slave_addr, self.HOLDINGREG_ADDR, addr):
      return False
    time.sleep(0.05)
    return True

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
    if not self._write_reg(self._slave_addr, self.HOLDINGREG_BAUDRATE, baud_code):
      return False
    time.sleep(0.05)
    return True

  def restore_factory(self):
    '''!
      @brief Restoring factory Settings mainly involves setting the uart and device addresses back to their default values.
      @n     Factory settings take effect after the module is powered on again.
      @return bool True on success, False on failure.
    '''
    if not self._write_reg(self._slave_addr, self.HOLDINGREG_RESET, self.FACTORY_RESET_VALUE):
      return False
    time.sleep(0.05)
    return True

  def get_device_info(self):
    '''!
      @brief Read VID/PID/version.
      @return tuple (vid, pid, version).
    '''
    return (
      self._read_reg16_compat(self._slave_addr, self.INPUTREG_VID),
      self._read_reg16_compat(self._slave_addr, self.INPUTREG_PID),
      self._read_reg16_compat(self._slave_addr, self.INPUTREG_VERSION)
    )

  def scan_address(self, start_addr=ADDR_MIN, end_addr=ADDR_MAX, max_count=None):
    '''!
      @brief Scan slave addresses on current bus.
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
        if max_count is not None and len(found) >= max_count:
          break

    time.sleep(0.05)
    return found

  def set_debug(self, enabled):
    '''!
      @brief Enable or disable debug output.
    '''
    self._debug = bool(enabled)

  def _debug_print(self, msg):
    if self._debug:
      print("[N20 DEBUG] {}".format(msg))

  @staticmethod
  def _fmt_hex(data):
    return ' '.join('{:02X}'.format(b) for b in data)

  @staticmethod
  def _swap_reg16(value):
    return ((value & 0xFF) << 8) | ((value >> 8) & 0xFF)

  @staticmethod
  def _calc_crc(data):
    crc = 0xFFFF
    for byte in data:
      crc ^= byte
      for _ in range(8):
        if crc & 1:
          crc = (crc >> 1) ^ 0xA001
        else:
          crc >>= 1
    return ((crc & 0x00FF) << 8) | ((crc & 0xFF00) >> 8)

  def _verify_crc(self, frame):
    if len(frame) < 3:
      return False
    crc_recv = (frame[-2] << 8) | frame[-1]
    return self._calc_crc(frame[:-2]) == crc_recv

  def _read_byte(self, deadline):
    while time.time() < deadline:
      if self._ser.in_waiting:
        return self._ser.read(1)[0]
      time.sleep(0.001)
    return None

  def _recv_write_package(self, dev_addr, reg, timeout=0.2):
    '''!
      @brief Receive FC 0x06 response, same logic as DFRobot_RTU recvAndParsePackage().
    '''
    deadline = time.time() + timeout
    raw_buf = bytearray()

    while time.time() < deadline:
      head = bytearray()
      while len(head) < 4:
        byte = self._read_byte(deadline)
        if byte is None:
          self._debug_print(
            "write resp timeout waiting header, reg=0x{:04X}, got={}".format(
              reg, self._fmt_hex(raw_buf) if raw_buf else "(none)"))
          return None
        raw_buf.append(byte)
        if len(head) == 0 and byte != dev_addr:
          self._debug_print("skip byte 0x{:02X}, expect addr {}".format(byte, dev_addr))
          continue
        if len(head) == 1 and (byte & 0x7F) != 0x06:
          self._debug_print("skip func 0x{:02X}, expect 0x06".format(byte))
          head = bytearray()
          continue
        head.append(byte)

      resp_reg = (head[2] << 8) | head[3]
      if resp_reg != reg and self._swap_reg16(resp_reg) != reg:
        self._debug_print(
          "write resp reg mismatch: got=0x{:04X} swapped=0x{:04X} expect=0x{:04X}".format(
            resp_reg, self._swap_reg16(resp_reg), reg))
        continue

      frame = bytearray(head)
      while len(frame) < 8:
        byte = self._read_byte(deadline)
        if byte is None:
          self._debug_print(
            "write resp timeout waiting body, partial={}".format(self._fmt_hex(frame)))
          return None
        raw_buf.append(byte)
        frame.append(byte)

      if frame[1] & 0x80:
        exc = frame[2] if len(frame) > 2 else 0xFF
        self._debug_print(
          "write resp exception: func=0x{:02X} code=0x{:02X} frame={}".format(
            frame[1], exc, self._fmt_hex(frame)))
        return None

      if not self._verify_crc(bytes(frame)):
        crc_recv = (frame[-2] << 8) | frame[-1]
        crc_calc = self._calc_crc(bytes(frame[:-2]))
        self._debug_print(
          "write resp CRC error: recv=0x{:04X} calc=0x{:04X} frame={}".format(
            crc_recv, crc_calc, self._fmt_hex(frame)))
        continue

      self._debug_print("write resp OK: {}".format(self._fmt_hex(frame)))
      return bytes(frame)

    self._debug_print(
      "write resp timeout overall, reg=0x{:04X}, raw={}".format(
        reg, self._fmt_hex(raw_buf) if raw_buf else "(none)"))
    return None

  def _read_reg16_compat(self, dev_addr, reg):
    '''!
      @brief Read one input register with the same byte order as Arduino readReg16Compat().
    '''
    try:
      raw = self._read_reg(dev_addr, reg, 1)[0]
    except Exception:
      return 0
    return self._swap_reg16(raw)

  def _detect_device_address(self, addr):
    try:
      raw = self._read_reg(addr, self.INPUTREG_VID, 1)[0]
    except Exception:
      return False

    compat = self._swap_reg16(raw)
    return (raw == self.DEVICE_VID) or (compat == self.DEVICE_VID)

  def _read_reg(self, dev_addr, reg, length):
    return list(self.master.execute(dev_addr, cst.READ_INPUT_REGISTERS, reg, length))

  def _write_reg(self, dev_addr, reg, value):
    '''!
      @brief Write holding register (FC 0x06), same as DFRobot_RTU writeHoldingRegister().
      @return bool True on success, False on failure.
    '''
    value &= 0xFFFF
    self._ser.reset_input_buffer()
    payload = bytes([
      dev_addr, 0x06,
      (reg >> 8) & 0xFF, reg & 0xFF,
      (value >> 8) & 0xFF, value & 0xFF
    ])
    crc = self._calc_crc(payload)
    frame = payload + bytes([(crc >> 8) & 0xFF, crc & 0xFF])
    self._debug_print(
      "write TX: reg=0x{:04X} value=0x{:04X} frame={}".format(reg, value, self._fmt_hex(frame)))
    self._ser.write(frame)
    self._ser.flush()

    ok = self._recv_write_package(dev_addr, reg, timeout=0.2) is not None
    if not ok:
      self._debug_print("write FAILED: reg=0x{:04X} value=0x{:04X}".format(reg, value))
    return ok
