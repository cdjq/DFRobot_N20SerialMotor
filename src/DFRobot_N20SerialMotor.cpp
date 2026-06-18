/*!
 * @file DFRobot_N20SerialMotor.cpp
 * @brief Implementation for serial N20 motor driver.
 * @copyright Copyright (c) 2026 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author JiaLi(zhixin.liu@dfrobot.com)
 * @version V1.0.0
 * @date 2026-05-09
 * @url https://github.com/DFRobot/DFRobot_N20SerialMotor
 */

#include "DFRobot_N20SerialMotor.h"

DFRobot_N20SerialMotor::DFRobot_N20SerialMotor(uint8_t addr, Stream *s) : DFRobot_RTU(s)
{
  _s = s;
  _addr = addr;
}

int8_t DFRobot_N20SerialMotor::begin(void)
{
  setTimeoutTimeMs(200);
  if (_addr < N20SERIAL_ADDR_MIN || _addr > N20SERIAL_ADDR_MAX) {
    return -1;
  }
  delay(500);
  for (uint8_t i = 0; i < 3; i++) {
    if (detectDeviceAddress(_addr)) {
      return 0;
    }
    delay(100);
  }
  return -1;
}

bool DFRobot_N20SerialMotor::detectDeviceAddress(uint8_t addr)
{
  uint16_t vid = 0;
  if (!readReg16Compat(addr, N20SERIAL_INPUTREG_VID, vid)) {
    return false;
  }
  return (vid == N20SERIAL_DEVICE_VID);
}

int8_t DFRobot_N20SerialMotor::setSpeed(int16_t speed)
{
  if (speed > 255) {
    speed = 255;
  }
  if (speed < -255) {
    speed = -255;
  }

  if (writeHoldingReg16(_addr, N20SERIAL_HOLDINGREG_SPEED, (uint16_t)speed) != 0) {
    delay(50);
    return -1;
  }
  return 0;
}

int8_t DFRobot_N20SerialMotor::setDeviceAddr(uint8_t addr)
{
  if (addr < N20SERIAL_ADDR_MIN || addr > N20SERIAL_ADDR_MAX) {
    return -1;
  }
  if (writeHoldingReg16(_addr, N20SERIAL_HOLDINGREG_ADDR, addr) != 0) {
    return -1;
  }
  delay(50);
  return 0;
}

int8_t DFRobot_N20SerialMotor::setBaudrate(eBaudrate_t baud)
{
  if (writeHoldingReg16(_addr, N20SERIAL_HOLDINGREG_BAUDRATE, (uint16_t)baud) != 0) {
    return -1;
  }
  delay(50);
  return 0;
}

int8_t DFRobot_N20SerialMotor::restoreFactory(void)
{
  if (writeHoldingReg16(_addr, N20SERIAL_HOLDINGREG_RESET, N20SERIAL_FACTORY_RESET_VALUE) != 0) {
    return -1;
  }
  delay(50);
  return 0;
}

sDeviceInfo_t DFRobot_N20SerialMotor::getDeviceInfo(void)
{
  sDeviceInfo_t info;

  info.vid = 0;
  info.pid = 0;
  info.version = 0;

  readReg16Compat(_addr, N20SERIAL_INPUTREG_VID, info.vid);
  readReg16Compat(_addr, N20SERIAL_INPUTREG_PID, info.pid);
  readReg16Compat(_addr, N20SERIAL_INPUTREG_VERSION, info.version);

  return info;
}

uint8_t DFRobot_N20SerialMotor::scanAddress(uint8_t *addrBuf, uint8_t bufLen, uint8_t startAddr, uint8_t endAddr)
{
  uint8_t count = 0;
  uint8_t addr = 0;

  if (addrBuf == NULL || bufLen == 0) {
    return 0;
  }

  if (startAddr < N20SERIAL_ADDR_MIN) {
    startAddr = N20SERIAL_ADDR_MIN;
  }
  if (endAddr > N20SERIAL_ADDR_MAX) {
    endAddr = N20SERIAL_ADDR_MAX;
  }
  if (startAddr > endAddr) {
    return 0;
  }

  for (addr = startAddr; addr <= endAddr; addr++) {
    if (detectDeviceAddress(addr)) {
      addrBuf[count++] = addr;
      if (count >= bufLen) {
        break;
      }
    }
  }

  delay(50);

  return count;
}

bool DFRobot_N20SerialMotor::readReg16Compat(uint8_t devAddr, uint16_t reg, uint16_t &value)
{
  uint8_t recvBuf[2] = { 0 };
  value = 0;

  if (readInputReg(devAddr, reg, recvBuf, 2) == 0) {
    value = ((uint16_t)recvBuf[1] << 8) | recvBuf[0];
    return true;
  }
  return false;
}

uint8_t DFRobot_N20SerialMotor::readInputReg(uint8_t devAddr, uint16_t reg, void *pBuf, uint8_t size)
{
  if (pBuf == NULL) {
    return 0;
  }
  return readInputRegister(devAddr, reg, (uint8_t *)pBuf, size);
}

uint8_t DFRobot_N20SerialMotor::readHoldingReg(uint8_t devAddr, uint16_t reg, void *pBuf, uint8_t size)
{
  if (pBuf == NULL) {
    return 0;
  }
  return readHoldingRegister(devAddr, reg, (uint8_t *)pBuf, size);
}

uint8_t DFRobot_N20SerialMotor::writeHoldingReg16(uint8_t devAddr, uint16_t reg, uint16_t value)
{
  return writeHoldingRegister(devAddr, reg, value);
}
