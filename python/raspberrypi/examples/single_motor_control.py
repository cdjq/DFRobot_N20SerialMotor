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


PORT = "/dev/ttyAMA0"


def main():
  motor = DFRobot_N20SerialMotor(PORT, slave_addr=1, baudrate=9600)

  if not motor.begin():
    print("Init failed, check wiring/address/baudrate.")
    return

  try:
    while True:
      motor.set_speed(200)
      time.sleep(2)
      motor.set_speed(-200)
      time.sleep(2)
      motor.stop()
      time.sleep(1)
  except KeyboardInterrupt:
    pass
  finally:
    motor.close()


if __name__ == "__main__":
  main()
