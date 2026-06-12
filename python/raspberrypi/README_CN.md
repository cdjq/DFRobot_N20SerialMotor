# DFRobot_N20SerialMotor Python

===========================

* [English Version](./README.md)

DFRobot_N20SerialMotor Python 是用于树莓派平台的 DFR1277 串口 N20 电机 Modbus-RTU 驱动库。

## 产品链接 ()
    SKU: DFR1277

## 目录

  * [概述](#概述)
  * [安装](#安装)
  * [方法](#方法)
  * [示例](#示例)
  * [历史](#历史)
  * [创作者](#创作者)

## 概述

* 打开串口并初始化模块通讯<br/>
* 设置速度并停止电机<br/>
* 设置和读取从机地址<br/>
* 配置波特率<br/>
* 恢复出厂设置，默认参数重新上电后生效<br/>
* 读取 VID/PID/版本并扫描设备地址

## 安装

安装依赖：

```bash
pip3 install modbus_tk
```

将 `DFRobot_N20SerialMotor.py` 和示例目录拷贝到树莓派项目中即可使用。

## 方法

```python

  def __init__(self, port, slave_addr=1, baudrate=9600, bus=None):
    '''!
      @brief 构造函数。
      @param port 串口名称，如 "/dev/ttyAMA0"。
      @param slave_addr Modbus 从机地址。
      @param baudrate 主机串口波特率。
      @param bus 共享同一串口总线的另一个实例。
    '''

  def begin(self):
    '''!
      @brief 在已打开的串口上检测目标设备。
      @return int 成功返回 0，失败返回 -1。
    '''

  def close(self):
    '''!
      @brief 关闭串口。
    '''

  def set_speed(self, speed):
    '''!
      @brief 设置电机速度。
      @param speed 范围：-255~255，符号控制方向。
      @return bool 成功返回 True。
    '''

  def stop(self):
    '''!
      @brief 停止电机。
      @return bool 成功返回 True。
    '''

  def set_device_addr(self, addr):
    '''!
      @brief 设置模块设备地址。
      @param addr 范围：1~247。
      @n     新地址在模块重新上电后生效。
      @n     本方法不会更新内部通讯地址；
      @n     模块重启后请使用新地址重新创建对象。
      @return bool 成功返回 True。
    '''

  def set_baudrate(self, baud_code):
    '''!
      @brief 配置波特率。
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
      @n     模块重启后请使用新波特率重新创建对象。
      @return bool 成功返回 True。
    '''

  def restore_factory(self):
    '''!
      @brief 恢复模块出厂设置。
      @return bool 成功返回 True。默认参数在模块重新上电后生效。
    '''

  def get_device_info(self):
    '''!
      @brief 读取 VID/PID/版本。
      @return tuple (vid, pid, version)。
    '''

  def scan(self, start_addr=1, end_addr=247):
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
