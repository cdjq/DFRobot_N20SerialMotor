'''!
  @file address_scan.py
  @brief Scan N20 serial motor addresses on Raspberry Pi.
  @copyright Copyright (c) 2026 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license The MIT License (MIT)
  @author JiaLi(zhixin.liu@dfrobot.com)
  @version V1.0.0
  @date 2026-06-18
  @url https://github.com/DFRobot/DFRobot_N20SerialMotor
'''

import os
import serial
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from DFRobot_N20SerialMotor import DFRobot_N20SerialMotor


port = "/dev/ttyAMA0"
MOTOR_BAUD = 9600
SCAN_START_ADDR = DFRobot_N20SerialMotor.ADDR_MIN
SCAN_END_ADDR = DFRobot_N20SerialMotor.ADDR_MAX

ser = serial.Serial(port=port, baudrate=MOTOR_BAUD, bytesize=8, parity='N', stopbits=1)
ser.reset_input_buffer()
ser.reset_output_buffer()
scanner = DFRobot_N20SerialMotor(ser, slave_addr=SCAN_START_ADDR)


def setup():
  print()
  print("========================================")
  print("  DFRobot N20 Serial Motor")
  print("  Address Scan Example")
  print("========================================")
  print("[SCAN] Range: {}~{}".format(SCAN_START_ADDR, SCAN_END_ADDR))
  print("[SCAN] Scanning bus...")
  print("Full range scan may take a while. Please be patient and wait.")

  found_addrs = scanner.scan_address(SCAN_START_ADDR, SCAN_END_ADDR)
  if not found_addrs:
    print("[SCAN] No device found on bus.")
  else:
    print("[SCAN] Found {} device(s), address:".format(len(found_addrs)))
    print(" ".join(str(addr) for addr in found_addrs))

  print("[SCAN] Done.")


if __name__ == "__main__":
  try:
    setup()
  except KeyboardInterrupt:
    pass
  finally:
    scanner.close()
