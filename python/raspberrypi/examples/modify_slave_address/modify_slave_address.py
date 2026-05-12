'''!
  @file modify_slave_address.py
  @brief Configure DFR1277 slave address on Raspberry Pi.
  @details Initialize by current communication parameters, then only modify slave address.
  @copyright Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license The MIT License (MIT)
  @author JiaLi(zhixin.liu@dfrobot.com)
  @version V1.0.0
  @date 2026-05-12
  @url https://github.com/DFRobot/DFRobot_N20SerialMotor
'''

from DFRobot_N20SerialMotor import DFRobot_N20SerialMotor


PORT = "/dev/ttyUSB0"

# Current module communication parameters.
CURRENT_ADDR = 1
CURRENT_BAUD = 9600

# Target module parameters.
TARGET_ADDR = 2


def main():
  motor = DFRobot_N20SerialMotor(PORT, slave_addr=CURRENT_ADDR, baudrate=CURRENT_BAUD)

  if not motor.begin():
    print("Init failed, check CURRENT_ADDR/CURRENT_BAUD/wiring.")
    return

  if CURRENT_ADDR != TARGET_ADDR:
    if not motor.set_device_addr(TARGET_ADDR):
      print("Set slave address failed.")
      motor.close()
      return
    print("Set slave address success.")
  else:
    print("Skip address change (same address).")

  print("Configuration written.")
  print("Please communicate with new addr=%d, baud=%d" % (TARGET_ADDR, CURRENT_BAUD))
  motor.close()


if __name__ == "__main__":
  main()
