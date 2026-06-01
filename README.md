# Program-Registor-with-STM32

Program Register-Level Programming with STM32G431CBU6 using SPI, I2C, and UART communication protocols.

---

## 📖Introduction

This project is created for learning and practicing **Embedded Systems** and **Bare-Metal Programming** using the **STM32G431CBU6** microcontroller.

The main purpose of this repository is to understand how STM32 peripherals work internally by configuring registers manually instead of using high-level libraries.

The project includes implementations of:

- SPI Communication
- I2C Communication
- UART Communication

with several external peripherals and sensors.

---

## 🛠️Hardware Used

### Microcontroller
- STM32G431CBU6

### SPI Device
- MAX6675 Thermocouple Temperature Sensor

### I2C Device
- BMP280 Pressure and Temperature Sensor

### UART Communication
- ESP32 for serial communication and data transfer

---

## 💻Development Environment

- IDE: STM32CubeIDE
- Language: C
- Programming Style: Register-Level / Bare Metal
- Debugger: ST-Link

---

# ✨Features

## SPI Communication
Interface STM32 with MAX6675 using direct register programming.

### Functions
- SPI Initialization
- SPI Clock Configuration
- Read Raw Temperature Data
- Convert Temperature Value

---

## I2C Communication
Interface STM32 with BMP280 sensor using direct register access.

### Functions
- I2C Initialization
- Read/Write Registers
- Read Pressure Data
- Read Temperature Data

---

## UART Communication
Transmit data between STM32 and ESP32.

### Functions
- UART Initialization
- Baudrate Configuration
- Send String Data
- Serial Debugging

---

# 🎯Objectives

* Learn STM32 peripheral registers
* Understand low-level embedded programming
* Practice communication protocols
* Improve debugging skills
* Build strong embedded systems fundamentals

---

# 🚀Getting Started

## 📥Clone Repository

```bash
git clone https://github.com/your-username/Program-Registor-with-STM32.git
```

---

## ▶️Open Project

1. Open STM32CubeIDE
2. Import Existing Project
3. Build Project
4. Flash firmware to STM32G431CBU6

---

# 🧪Example Applications

* Read temperature from MAX6675 using SPI
* Read pressure and temperature from BMP280 using I2C
* Send sensor data to ESP32 through UART

---

# 👨‍💻Author

Thanh Sang
Embedded Systems & Bare-Metal STM32 Development

---

# License

This project is developed for educational purposes.
