'''!
  @file dual_motor_control.py
  @brief Two motors demo on Raspberry Pi.
  @copyright Copyright (c) 2026 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license The MIT License (MIT)
  @author JiaLi(zhixin.liu@dfrobot.com)
  @version V1.0.0
  @date 2026-05-09
  @url https://github.com/DFRobot/DFRobot_N20SerialMotor
'''

import os
import serial
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from DFRobot_N20SerialMotor import DFRobot_N20SerialMotor


port = "/dev/ttyAMA0"
MOTOR_BAUD = 9600
SCAN_START_ADDR = 1
SCAN_END_ADDR = 32

ser = serial.Serial(port=port, baudrate=MOTOR_BAUD, bytesize=8, parity='N', stopbits=1)
ser.reset_input_buffer()
ser.reset_output_buffer()
motor0 = DFRobot_N20SerialMotor(ser, slave_addr=1)
motor1 = DFRobot_N20SerialMotor(slave_addr=2, bus=motor0)
motors = [motor0, motor1]

'''
  note : The correspondence between motor addresses
  1. Motor1: Address 1
  2. Motor2: Address 2
        ...:...
  n. Motorn: Address n

  usge:
  1. motors[0] is Motor1
  2. motors[1] is Motor2
        ...:...
  n. motors[n-1] is Motorn
'''

def setup():
  print()
  print("========================================")
  print("  DFRobot N20 Serial Motor")
  print("  Dual Motor Control Example")
  print("========================================")

  for i, motor in enumerate(motors):
    if motor.begin():
      print("[OK] Motor {} initialized (Modbus addr: {})".format(i + 1, i + 1))
    else:
      print("[ERROR] Motor {} init failed, scanning bus...".format(i + 1))
      print("This might take about 30 seconds. Please be patient and wait.")

      found_addrs = motors[0].scan_address(SCAN_START_ADDR, SCAN_END_ADDR)
      if not found_addrs:
        print("[SCAN] No device found on bus.")
      else:
        print("[SCAN] Found {} device(s), address:".format(len(found_addrs)))
        print(" ".join(str(addr) for addr in found_addrs))

      print("[ERROR] Motor init failed. Please check whether the device address is correct.")
      while True:
        time.sleep(1)

  print("All motors ready.")
  print("Starting dual motor control loop...")
  print()


def loop():
  print("-> M1 speed 180, M2 speed -180")
  motors[0].set_speed(180)
  motors[1].set_speed(-180)
  time.sleep(2)

  print("-> M1 speed -120, M2 speed 120")
  motors[0].set_speed(-120)
  motors[1].set_speed(120)
  time.sleep(2)

  print("-> Both motors stop")
  motors[0].set_speed(0)
  motors[1].set_speed(0)
  time.sleep(1.5)

  print()


if __name__ == "__main__":
  try:
    setup()
    while True:
      loop()
  except KeyboardInterrupt:
    pass
  finally:
    motors[1].close()
    motors[0].close()
