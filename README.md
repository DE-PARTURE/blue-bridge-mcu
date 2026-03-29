# BlueBridgeMCU

蓝桥杯单片机方向综合工程，围绕矩阵键盘进行功能切换，整合了温度、超声波、光敏、红外和实时时钟等模块，适合做功能联调和课程设计参考。

## 功能概览

- 矩阵键盘控制不同功能模块的切换
- `S7`：温度相关功能
- `S11`：超声波相关功能
- `S15`：光敏相关功能
- `S19`：红外相关功能
- `S6`：实时时钟功能

## 使用说明

- 启用某个功能后，需要先关闭该功能，再切换到下一个功能。
- 使用红外功能时，需要短接 `P11` 和 `P33`。

## 项目结构

- `V1.3_Temperature_Photoresistor_Infrared_Ultrasnoic_Thir_Clock`
  - `User`：应用入口与主流程
  - `Basic`：基础配置与系统初始化
  - `Hardware`：温度、超声波、红外、数码管、时钟等外设驱动
  - `example.uvproj`：Keil 工程文件

## 开发环境

- 平台：蓝桥杯单片机开发板
- IDE：Keil MDK
- 语言：C

## 编译方式

1. 使用 Keil 打开 `V1.3_Temperature_Photoresistor_Infrared_Ultrasnoic_Thir_Clock/example.uvproj`。
2. 根据实际硬件检查管脚连接与外设初始化。
3. 编译并下载到开发板运行。

## License

本仓库采用 [BSD 3-Clause License](LICENSE)。
