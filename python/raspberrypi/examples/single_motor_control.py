'''!
  @file single_motor_control.py
  @brief Single motor demo on Raspberry Pi.
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
MOTOR_ADDR = 1
MOTOR_BAUD = 9600

ser = serial.Serial(port=port, baudrate=MOTOR_BAUD, bytesize=8, parity='N', stopbits=1)
ser.reset_input_buffer()
ser.reset_output_buffer()
motor = DFRobot_N20SerialMotor(ser, slave_addr=MOTOR_ADDR)

def setup():
  print()
  print("========================================")
  print("  DFRobot N20 Serial Motor")
  print("  Single Motor Control Example")
  print("========================================")

  while not motor.begin():
    print("[ERROR] Motor init failed, retrying...")
    time.sleep(1)

  print("[OK] Motor initialized (Modbus addr: {})".format(MOTOR_ADDR))
  print("Starting speed control loop...")
  print()

def loop():
  print("-> Speed 200")
  motor.set_speed(200)
  time.sleep(2)

  print("-> Speed 80")
  motor.set_speed(80)
  time.sleep(1.2)

  print("-> Speed -200")
  motor.set_speed(-200)
  time.sleep(2)

  print("-> Stop")
  motor.set_speed(0)
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
    motor.close()
