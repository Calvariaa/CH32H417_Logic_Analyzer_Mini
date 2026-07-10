# 16通道200MHz逻辑分析仪 (CH32H417WEU6移植版)

![逻辑分析仪效果图](https://i.imgur.com/bj86NZk.png)

本工程是基于[立创开源平台原项目](https://oshwhub.com/q2h2/project_bszkxrnf)的移植版本。核心变动为：**将主控芯片从CH32H417QEU6 (QFN-128) 更换为CH32H417WEU6 (QFN-68)**，并据此修改了原理图、重绘了PCB，调整了部分引脚分配。

感谢xlj佬帮忙测试程序和捉虫（）
经测试USB3.0正常，200MHz采样正常，ADC采样正常。

## 项目概述

*   **核心芯片**: CH32H417WEU6 (QFN-68封装)
*   **主要功能**:
    *   **16通道数字逻辑分析仪**: 最高200MHz采样率 (需USB3.0连接)。
    *   **2通道模拟信号采样**: 最高20Msps采样率 (功能需验证，且受WEU6封装限制)。
*   **通信接口**: Type-C (支持USB3.0 5Gbps，兼容USB2.0)。
*   **PC端软件**: 兼容开源软件PulseView (配合专用上位机U3LogicAnalyzer)。
*   **原工程**: [https://oshwhub.com/q2h2/project_bszkxrnf](https://oshwhub.com/q2h2/project_bszkxrnf)

## 移植修改详情

### 1. 关键引脚变更

| 功能 | 原方案 (QEU6) 引脚 | **本移植方案 (WEU6) 引脚** | 备注 |
| :--- | :--- | :--- | :--- |
| **VIO18调压 (DAC)** | PA4 (DAC1) | **PA5 (DAC2)** | 用于控制DCDC输出电压，调节IO电平阈值 |
| **模拟采样通道 (HSADC)** | PF8, PF9 | **PC2, PC3** | 原PF8/PF9在WEU6封装中未引出，需修改固件ADC通道 |
| **UART调试打印** | PA9 (TX) | **PD1 (TX)** | 用于输出调试信息，波特率921600 |
| **LED指示灯** | PB3, PB4 | **PB0, PB1** | 例如：PB0-绿灯(USB连接)，PB1-蓝灯(固件运行) |

### 2. 原理图变更

1.  **主控芯片**: 替换U1为`CH32H417WEU6`，封装改为QFN-68。
2.  **电源网络调整**: VIO18供电将DAC控制脚改为PA5。
3.  **ADC通道重映射**:
    *   原模拟采样通道 (PF8/PF9) 在WEU6上未引出，改为PC2/PC3。
    *   修改MCU固件中的ADC初始化代码，更换采样通道。

## 固件与软件说明

### 固件修改点
1.  **ADC通道**: 修改`HSADC`初始化代码，将采样通道从PF8/PF9改为PC2/PC3。
2.  **DAC调压**: 如保留VIO18调压功能，需将DAC输出脚从PA4改为PA5，并修改相应控制逻辑。
3.  **LED控制**: 修改GPIO初始化代码，将LED控制引脚从PB3/PB4改为PB0/PB1。
4.  **UART调试**: 修改串口初始化代码，将UART TX引脚从PA9改为PD1。

> **注意**：本硬件修改不改变PC端软件 (U3LogicAnalyzer/PulseView) 的使用方式。

### 固件烧录流程 (重要)
1.  使用WCH-Link，通过SWD接口烧录**IAP固件** (V3F内核)。
2.  将逻辑分析仪通过USB连接至PC。
3.  打开PC端软件`U3LogicAnalyzer`，使用“帮助-固件升级”功能，烧录**APP固件** (V5F内核的.bin文件)。
> **提示**：烧录IAP后SWD接口可能被禁用，如需再次烧录，可能需要执行“全片擦除”操作。

## 参考资料

*   **原工程**: [https://oshwhub.com/q2h2/project_bszkxrnf](https://oshwhub.com/q2h2/project_bszkxrnf)
*   **类似移植参考**: 评论区@pandy_f的2.54mm排针版本 [https://oshwhub.com/motozilog/project_ttbtynyk](https://oshwhub.com/motozilog/project_ttbtynyk)
*   **芯片手册**: CH32H417DS0.PDF, CH32H417评估板说明书.pdf (可从沁恒官网下载)

---
**声明**：本工程为开源硬件项目的修改版本，遵循原项目GPL 3.0开源协议。复刻者需自行验证电路可行性并承担相关责任。
