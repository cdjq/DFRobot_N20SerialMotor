# DFRobot_N20SerialMotor

===========================

* [English Version](./README.md)

DFRobot_N20SerialMotor 是 DFR1277 串口 N20 电机驱动模块的 Arduino 库，基于 Modbus-RTU 协议，可实现电机速度控制、地址配置、串口参数配置和多设备级联扫描。

![产品图片]

## 产品链接 ()
    SKU: DFR1277

## 目录

  * [概述](#概述)
  * [库安装](#库安装)
  * [方法](#方法)
  * [示例](#示例)
  * [兼容性](#兼容性)
  * [历史](#历史)
  * [创作者](#创作者)

## 概述

* 初始化模块并校验 Modbus-RTU 通讯<br/>
* 设置电机速度（`-255~255`）并支持快速停止<br/>
* 配置从机地址（`1~32`）<br/>
* 配置波特率、校验位和停止位<br/>
* 读取 VID/PID/版本并扫描总线设备

## 库安装

使用前请先下载本库和依赖库：

* https://github.com/DFRobot/DFRobot_N20SerialMotor.git
* https://github.com/DFRobot/DFRobot_RTU.git

将两个库复制到 `Arduino/libraries` 目录，然后打开示例运行。

## 方法

```C++

  /**
   * @fn DFRobot_N20SerialMotor
   * @brief 构造函数。
   * @param addr Modbus 从机地址。
   * @param s Modbus-RTU 通讯串口对象指针。
   */
  DFRobot_N20SerialMotor(uint8_t addr, Stream *s);

  /**
   * @fn begin
   * @brief 初始化串口电机对象并校验当前地址设备。
   * @return int8_t
   * @retval 0 成功
   * @retval -1 失败
   */
  int8_t begin(void);

  /**
   * @fn setSpeed
   * @brief 设置电机速度。
   * @param speed 速度范围：-255~255。0 停止电机。
   * @return int8_t
   * @retval 0 成功
   * @retval -1 失败
   */
  int8_t setSpeed(int16_t speed);

  /**
   * @fn stop
   * @brief 停止电机（等效于 setSpeed(0)）。
   * @return int8_t
   * @retval 0 成功
   * @retval -1 失败
   */
  int8_t stop(void);

  /**
   * @fn getSpeed
   * @brief 读取电机速度寄存器。
   * @return int16_t 当前速度，读取失败返回 0。
   */
  int16_t getSpeed(void);

  /**
   * @fn getMotorState
   * @brief 读取电机状态寄存器。
   * @return eMotorState_t
   * @n     eMotorStop    电机停止
   * @n     eMotorForward 电机正转
   * @n     eMotorReverse 电机反转
   * @n     eMotorUnknown 读取失败
   */
  eMotorState_t getMotorState(void);

  /**
   * @fn setDeviceAddr
   * @brief 设置模块设备地址。
   * @param addr 地址范围：1~32。
   * @return int8_t
   * @retval 0 成功
   * @retval -1 失败
   */
  int8_t setDeviceAddr(uint8_t addr);

  /**
   * @fn setBaudrate
   * @brief 配置波特率。
   * @param baud 波特率代码。
   * @n     eBaud2400
   * @n     eBaud4800
   * @n     eBaud9600
   * @n     eBaud14400
   * @n     eBaud19200
   * @n     eBaud38400
   * @n     eBaud57600
   * @n     eBaud115200
   * @return int8_t
   * @retval 0 成功
   * @retval -1 失败
   */
  int8_t setBaudrate(eBaudrate_t baud);

  /**
   * @fn getDeviceInfo
   * @brief 读取 VID/PID/版本信息。
   * @return sDeviceInfo_t
   * @n       VID           产品 VID。
   * @n       PID           产品 PID。
   * @n       version       产品版本。
   */
  sDeviceInfo_t getDeviceInfo(void);

  /**
   * @fn scan
   * @brief 扫描总线上在线设备地址。
   * @param addrBuf 输出地址数组。
   * @param bufLen addrBuf 最大可存储数量。
   * @param startAddr 扫描起始地址。
   * @param endAddr 扫描结束地址。
   * @return uint8_t 发现的设备数量。
   */
  uint8_t scan(uint8_t *addrBuf, uint8_t bufLen, uint8_t startAddr = 1, uint8_t endAddr = 32);
```

## 兼容性

MCU                | Work Well    |   Work Wrong    | Untested    | Remarks
------------------ | :----------: | :-------------: | :---------: | :----:
Arduino Uno        |      √       |                 |             |
Arduino MEGA2560   |      √       |                 |             |
Arduino Leonardo   |      √       |                 |             |
FireBeetle-ESP8266 |      √       |                 |             |
FireBeetle-ESP32   |      √       |                 |             |
FireBeetle-M0      |      √       |                 |             |
Micro:bit          |              |                 |     √       |

## 历史

- 2026-05-09 - 发布 1.0.0 版本。

## 创作者

Written by JiaLi(zhixinliu@dfrobot.com), 2026. (Welcome to our [website](https://www.dfrobot.com/))
