# QT_Stm32f4discovery

**This project is still very experimental, proceed at your own risk.**  

This project shows how to handle the LEDs on the stm32f4discovery board by using a Qt Application

## 1. Build and Test Environment
Os : Mac os x Sierra / Xubuntu 16.04  
IDE : System Workbench for STM32 / Qtcreator  
The stm32f4discovery board.
An USB to Uart_3v3 cable, and 3 wires to connect the bord to the USB/UART converter.  
A USB cable to power and load a program to the stm32.

## 2. File organization
Qt_app : contains the application that handles the LEDs  
stm32f4 : the directory contains 2 other directories :
- src : the sources or the stm32f4 project.
- inc : the headers or the project.

## 3. Setup the environment
The Qt application has been written on Qt Creator 4.4.1 with Qt version : 5.7.1-0  
For the stm32f4discovery application, I have used the free integrated development environment for STM32 developped by Ac6 Tool : System Workbench for STM32

For the Qt project, You need to :
- Install the latest Qt Creator version with Qt 5.7 or higher.  
- Open the project by double clicking on stm32_app.pro.
- Run qmake
- Then build and finally run your program.  

For the stm32f4discovery :
- Install System Workbench for STM32.
- Create a new C project.
- Select the right board (STM32F4/STM32F4DISCOVERY)
- On the next step : Project Firmware configuration, you need to click on (Hardware Abstraction Layer - Cube HAL)
- Then click on : Finish

The firmware used in this project is STM32Cube_FW_F4_V1.16.0.

- Copy and past the 2 directories ('src' and 'inc') in the new project directory.
- Build and Run the program on your target.

## 4. Hardware setup
In this project, I have used the pins PA2/PA3 for the UART transmission.  
You can use your 3 wires to connect the board to the converter.

| Computer | USB-To-UART converter| STM32F4DISCOVERY  |
| :------- |:-------------:| -----------------:|
|          | GND | GND               |
| USB      | Rx      | PA2 (Tx)               |
|          | Tx      | PA3 (Rx)               |
