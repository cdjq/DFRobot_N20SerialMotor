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

import time
from DFRobot_N20SerialMotor import DFRobot_N20SerialMotor


PORT = "/dev/ttyUSB0"


def main():
  motors = [
    DFRobot_N20SerialMotor(PORT, slave_addr=1, baudrate=9600),
    DFRobot_N20SerialMotor(PORT, slave_addr=2, baudrate=9600)
  ]

  for i, motor in enumerate(motors):
    if not motor.begin():
      print("Motor init failed, index:", i)
      for opened in motors[:i]:
        opened.close()
      return

  print("Scan result:", motors[0].scan())

  try:
    while True:
      motors[0].set_speed(180)
      motors[1].set_speed(-180)
      time.sleep(2)

      motors[0].set_speed(-120)
      motors[1].set_speed(120)
      time.sleep(2)

      motors[0].stop()
      motors[1].stop()
      time.sleep(1)
  except KeyboardInterrupt:
    pass
  finally:
    for motor in motors:
      motor.close()


if __name__ == "__main__":
  main()
