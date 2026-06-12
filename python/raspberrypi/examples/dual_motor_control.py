'''!
  @file dual_motor_control.py
  @brief Two DFR1277 motors demo on Raspberry Pi.
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
  motor0 = DFRobot_N20SerialMotor(port, slave_addr=1, baudrate=9600)
  motors = [
    motor0,
    DFRobot_N20SerialMotor(port, slave_addr=2, baudrate=9600, bus=motor0)
  ]

  print()
  print("========================================")
  print("  DFRobot N20 Serial Motor")
  print("  Dual Motor Control Example")
  print("========================================")

  for i, motor in enumerate(motors):
    while motor.begin() == -1:
      print("[ERROR] Motor {} init failed, retrying...".format(i + 1))
      time.sleep(1)
    print("[OK] Motor {} initialized (Modbus addr: {})".format(i + 1, i + 1))

  print("All motors ready.")
  print("Starting dual motor control loop...")
  print()

  try:
    while True:
      print("-> M1 speed 180, M2 speed -180")
      motors[0].set_speed(180)
      motors[1].set_speed(-180)
      time.sleep(2)

      print("-> M1 speed -120, M2 speed 120")
      motors[0].set_speed(-120)
      motors[1].set_speed(120)
      time.sleep(2)

      print("-> Both motors stop")
      motors[0].stop()
      motors[1].stop()
      time.sleep(1.5)

      print()
  except KeyboardInterrupt:
    pass
  finally:
    motors[1].close()
    motors[0].close()


if __name__ == "__main__":
  main()
