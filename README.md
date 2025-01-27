# Smart Home Control GUI  

## Overview  
This project is a **Smart Home Control** GUI application built using **PyQt5**. It allows users to monitor and control smart home devices such as **lamps, plugs, and temperature sensors**. The GUI interacts with an **embedded system** via **UART communication** to send and receive data.  

## Features  
- **Lamp & Plug Control:** Toggle the state of connected devices through the GUI.  
- **Temperature Monitoring:** Displays real-time temperature readings and raises warnings if the temperature exceeds a set threshold.  
- **Door Status Logging:** Monitors door status updates and logs timestamped entries in a table.  
- **HMI Interface:** User-friendly graphical controls with interactive buttons and icons.  
- **Serial Communication:** Uses **UART (Serial Communication)** to interface with external hardware.
- Ensure the correct COM port is set in the script before running the application. 

## Technologies Used  
- **Python** (PyQt5 for GUI, PySerial for serial communication, threading for UART handling)  
- **Embedded Systems** (UART communication with external microcontroller)  

## Installation  
### **Prerequisites**  
Ensure you have **Python 3.x** installed. You can install the required dependencies using:  

```bash
pip install pyqt5 pyserial
