# DFRobot_N20SerialMotor

===========================

* [English Version](./README.md)

N20 电机驱动模块的 Arduino 库，基于 Modbus-RTU 协议，可实现电机速度控制、地址配置、串口参数配置和多设备级联扫描。

![产品图片]

## 产品链接 (https://www.dfrobot.com)
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

* 校验模块 Modbus-RTU 通讯<br/>
* 设置电机速度（`-255~255`，0 停止电机）<br/>
* 配置从机地址（`1~247`），重新上电后生效<br/>
* 配置波特率，重新上电后生效<br/>
* 恢复出厂设置（UART 参数和设备地址），默认参数重新上电后生效<br/>
* 读取 VID/PID/版本并扫描总线设备

## 库安装

使用前请先下载本库和依赖库：
* https://github.com/DFRobot/DFRobot_RTU.git
将两个库复制到 `Arduino/libraries` 目录，然后打开示例运行。

## 方法

```C++

  /**
   * @fn DFRobot_N20SerialMotor
   * @brief 构造函数。
   * @param addr Modbus 从机地址，范围：1~247。
   * @param s Modbus-RTU 通讯串口对象指针。
   */
  DFRobot_N20SerialMotor(uint8_t addr, Stream *s);

  /**
   * @fn begin
   * @brief 校验当前地址设备。
   * @n     调用本函数前，请先在用户程序中初始化串口。
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
   * @fn setDeviceAddr
   * @brief 设置模块设备地址。
   * @param addr 地址范围：1~247。
   * @n     新地址在模块重新上电后生效。
   * @n     本函数不会更新内部通讯地址；
   * @n     模块重启后请使用新地址重新创建对象。
   * @return int8_t
   * @retval 0 成功
   * @retval -1 失败
   */
  int8_t setDeviceAddr(uint8_t addr);

  /**
   * @fn setBaudrate
   * @brief 配置波特率，仅可修改波特率，不可修改停止位和校验位。
   * @param baud 波特率代码。
   * @n     eBaud2400
   * @n     eBaud4800
   * @n     eBaud9600
   * @n     eBaud14400
   * @n     eBaud19200
   * @n     eBaud38400
   * @n     eBaud57600
   * @n     eBaud115200
   * @n     新波特率在模块重新上电后生效。
   * @n     本函数不会更新主机串口波特率；
   * @n     模块重启后请使用新波特率重新初始化串口。
   * @return int8_t
   * @retval 0 成功
   * @retval -1 失败
   */
  int8_t setBaudrate(eBaudrate_t baud);

  /**
   * @fn restoreFactory
   * @brief 恢复出厂设置，主要将 UART 参数和设备地址恢复为默认值。
   * @n     默认参数在模块重新上电后生效。
   * @return int8_t
   * @retval 0 成功
   * @retval -1 失败
   */
  int8_t restoreFactory(void);

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
   * @fn scanAddress
   * @brief 扫描总线上在线设备地址。
   * @param addrBuf 输出地址数组。
   * @param bufLen addrBuf 最大可存储数量。
   * @param startAddr 扫描起始地址。
   * @param endAddr 扫描结束地址。
   * @return uint8_t 发现的设备数量。
   */
  uint8_t scanAddress(uint8_t *addrBuf, uint8_t bufLen, uint8_t startAddr = 1, uint8_t endAddr = 247);
```

## 示例

* `singleMotorControl`：初始化单个电机并进行正反转速度控制。
* `dualMotorControl`：初始化两个级联电机，并在同一总线上控制。
* `addressScan`：扫描 Modbus-RTU 总线并打印发现的电机地址。

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
