'''!
  @file single_motor_control.py
  @brief Single DFR1277 motor demo on Raspberry Pi.
  @copyright Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license The MIT License (MIT)
  @author JiaLi(zhixin.liu@dfrobot.com)
  @version V1.0.0
  @date 2026-05-09
  @url https://github.com/DFRobot/DFRobot_N20SerialMotor
'''

import os
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from DFRobot_N20SerialMotor import DFRobot_N20SerialMotor


port = "/dev/ttyAMA0"


def main():
  motor = DFRobot_N20SerialMotor(port, slave_addr=1, baudrate=9600)

  print()
  print("========================================")
  print("  DFRobot N20 Serial Motor")
  print("  Single Motor Control Example")
  print("========================================")

  while not motor.begin():
    print("[ERROR] Motor init failed, retrying...")
    motor.close()
    time.sleep(1)

  print("[OK] Motor initialized (Modbus addr: 1)")
  print("Starting speed control loop...")
  print()

  try:
    while True:
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
      motor.stop()
      time.sleep(1.5)

      print()
  except KeyboardInterrupt:
    pass
  finally:
    motor.close()


if __name__ == "__main__":
  main()
