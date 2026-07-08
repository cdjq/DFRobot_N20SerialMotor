# DFRobot_N20SerialMotor Python

===========================

* [English Version](./README.md)

N20 电机驱动模块的树莓派 Python 库，基于 Modbus-RTU 协议，可实现电机速度控制、地址配置、串口参数配置和多设备级联扫描。

## 产品链接 (https://www.dfrobot.com)
    SKU: DFR1277

## 目录

  * [概述](#概述)
  * [安装](#安装)
  * [方法](#方法)
  * [示例](#示例)
  * [历史](#历史)
  * [创作者](#创作者)

## 概述

* 使用已打开的串口校验模块通讯<br/>
* 设置电机速度（`-255~255`，0 停止电机）<br/>
* 设置和读取从机地址<br/>
* 配置波特率<br/>
* 恢复出厂设置（UART 参数和设备地址），默认参数重新上电后生效<br/>
* 读取 VID/PID/版本并扫描设备地址

## 安装

安装依赖：

```bash
pip3 install modbus_tk pyserial
```

将 `DFRobot_N20SerialMotor.py` 和示例目录拷贝到树莓派项目中即可使用。

## 方法

```python

  def __init__(self, ser=None, slave_addr=1, bus=None):
    '''!
      @brief 构造函数。
      @param ser 已打开的串口对象。未指定 bus 时必须提供。
      @param slave_addr Modbus 从机地址，范围：1~247。
      @param bus 共享同一串口总线的另一个实例。
    '''

  def begin(self):
    '''!
      @brief 在已打开的串口上检测目标设备。
      @return bool 成功返回 True，失败返回 False。
    '''

  def close(self):
    '''!
      @brief 关闭本实例拥有的 Modbus master。
    '''

  def set_speed(self, speed):
    '''!
      @brief 设置电机速度。
      @param speed 范围：-255~255，符号控制方向。0 停止电机。
      @return bool 成功返回 True，失败返回 False。
    '''

  def set_device_addr(self, addr):
    '''!
      @brief 设置模块设备地址。
      @param addr 范围：1~247。
      @n     新地址在模块重新上电后生效。
      @n     本方法不会更新内部通讯地址；
      @n     模块重启后请使用新地址重新创建对象。
      @return bool 成功返回 True，失败返回 False。
    '''

  def set_baudrate(self, baud_code):
    '''!
      @brief 配置波特率，仅可修改波特率，不可修改停止位和校验位。
      @param baud_code 波特率代码。
      @n     BAUD_2400
      @n     BAUD_4800
      @n     BAUD_9600
      @n     BAUD_14400
      @n     BAUD_19200
      @n     BAUD_38400
      @n     BAUD_57600
      @n     BAUD_115200
      @n     新波特率在模块重新上电后生效。
      @n     本方法不会更新主机串口波特率；
      @n     模块重启后请使用新波特率重新打开串口。
      @return bool 成功返回 True，失败返回 False。
    '''

  def restore_factory(self):
    '''!
      @brief 恢复出厂设置，主要将 UART 参数和设备地址恢复为默认值。
      @n     默认参数在模块重新上电后生效。
      @return bool 成功返回 True，失败返回 False。
    '''

  def get_device_info(self):
    '''!
      @brief 读取 VID/PID/版本。
      @return tuple (vid, pid, version)。
    '''

  def scan_address(self, start_addr=1, end_addr=247):
    '''!
      @brief 扫描总线地址。
      @param start_addr 扫描起始地址。
      @param end_addr 扫描结束地址。
      @return list 检测到的地址列表。
    '''
```

## 历史

- 2026-05-09 - 发布 1.0.0 版本。

## 创作者

Written by JiaLi(zhixinliu@dfrobot.com), 2026. (Welcome to our [website](https://www.dfrobot.com/))
