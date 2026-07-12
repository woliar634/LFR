<div align="center">

# 🤖 Line Following Robot (LFR)

### Competition-Oriented Arduino Robot for Autonomous Line Tracking, Junction Navigation, Wall Following & Inverse Line Detection

<p>
  <img src="https://img.shields.io/badge/Platform-Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white" alt="Arduino"/>
  <img src="https://img.shields.io/badge/Language-C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++"/>
  <img src="https://img.shields.io/badge/Category-Robotics-red?style=for-the-badge&logo=ros&logoColor=white" alt="Robotics"/>
  <img src="https://img.shields.io/badge/University-JUST-success?style=for-the-badge" alt="JUST"/>
  <img src="https://img.shields.io/badge/Department-EEE-blueviolet?style=for-the-badge" alt="EEE"/>
</p>

<p>
  <img src="https://img.shields.io/github/stars/woliar634/LFR?style=social" alt="GitHub Stars"/>
  <img src="https://img.shields.io/github/forks/woliar634/LFR?style=social" alt="GitHub Forks"/>
  <img src="https://img.shields.io/github/watchers/woliar634/LFR?style=social" alt="GitHub Watchers"/>
</p>

---

### 🚀 Overview

An **advanced Arduino-based Line Following Robot (LFR)** developed for robotics competitions requiring **high-speed, precise, and reliable autonomous navigation** on complex tracks.

The robot combines multiple navigation techniques, including **line following**, **junction recognition**, **automatic U-turn recovery**, **wall following**, **inverse (black/white) line detection**, and **EEPROM-based sensor calibration**. Its modular software architecture makes the project easy to understand, maintain, and extend for future robotics competitions.

---

### ✨ Key Highlights

🚀 High-Speed Navigation • 📍 6-Channel IR Sensor Array • 🔄 Intelligent Junction Detection • ↩️ Automatic U-Turn Recovery • 🧱 Ultrasonic Wall Following • ⚪⚫ Automatic Inverse Line Detection • 💾 EEPROM Calibration • 🏁 Multi-Round Competition Modes • 🎯 Modular Arduino Architecture • ⚡ Optimized Motor Control

</div>

---

# ✨ Features

### 🚀 High-Speed Line Following

Optimized motor speed control and efficient sensor processing enable the robot to follow the line smoothly while maintaining high speed on straight paths.

### 📍 6-Channel IR Sensor Array

Six analog infrared sensors continuously monitor the track, providing accurate line position detection for precise navigation.

### 🔄 Intelligent Junction Detection

Automatically detects left, right, T, and cross junctions, allowing the robot to make correct navigation decisions during complex courses.

### ↩️ Automatic U-Turn Recovery

When the robot loses the line, it intelligently searches for the track and performs a controlled U-turn to recover without manual intervention.

### 🧱 Wall Following

Utilizes two ultrasonic sensors to detect nearby walls and navigate wall-following sections during advanced competition tracks.

### ⚪⚫ Automatic Inverse Line Detection

Supports both **black line on white surface** and **white line on black surface** by automatically switching detection logic when required.

### 💾 EEPROM-Based Sensor Calibration

Calibration values are permanently stored in the Arduino EEPROM, eliminating the need to recalibrate every time the robot is powered on.

### 🏁 Multi-Round Competition Modes

Implements separate navigation algorithms for the **First Round** and **Second Round**, allowing optimized behavior for different competition stages.

### ⚡ Optimized Motor Control

Differential motor control with PWM provides smooth steering, sharp corner handling, and stable high-speed operation.

### 🎯 Modular Software Architecture

The project is divided into multiple Arduino source files, making the code easier to understand, debug, maintain, and extend.

# 🤖 Line Following Robot (LFR)

A competition-oriented **Arduino-based Line Following Robot (LFR)** capable of navigating complex tracks containing sharp turns, junctions, dead ends, wall-following sections, and inverse (white-line) tracks.

The project was developed for robotics competitions where both speed and reliability are essential.

---

# Code Descriptions

---

# Hardware Used

| Component                               | Quantity |
| --------------------------------------- | -------- |
| Arduino Nano / Uno                      | 1        |
| IR Line Sensors                         | 6        |
| DC Geared Motors                        | 2        |
| Motor Driver                            | 1        |
| Ultrasonic Sensors (HC-SR04 compatible) | 2        |
| Robot Chassis                           | 1        |
| Li-ion Battery Pack                     | 1        |
| Wheels                                  | 2        |
| Castor Wheel                            | 1        |

---

# Project Structure

```
Line following bot/
│
├── wolier.ino              // Main program
├── 1st_round.ino           // First round algorithm
├── 2nd_round.ino           // Second round algorithm
├── Motor.ino               // Motor control
├── Reading_info.ino        // Sensor reading
├── calibration.ino         // Sensor calibration
├── Sonar_sensor.ino        // Wall following
├── brake.ino               // Braking routine
```

---

# Pin Configuration

## Motor Driver

| Arduino Pin | Function            |
| ----------- | ------------------- |
| D3          | Left Motor PWM      |
| D4          | Left Motor Reverse  |
| D5          | Left Motor Forward  |
| D6          | Right Motor Forward |
| D7          | Right Motor Reverse |
| D9          | Right Motor PWM     |

---

## Ultrasonic Sensors

| Sensor      | Pin |
| ----------- | --- |
| Right Sonar | D12 |
| Left Sonar  | D10 |

---

## IR Sensors

Six analog IR sensors are connected to:

```
A0
A1
A2
A3
A4
A5
```

---

# Software Libraries

* EEPROM
* NewPing

Install **NewPing** from the Arduino Library Manager before compiling.

---

# Working Principle

## 1. Sensor Reading

Each IR sensor is read as an analog value.

Values greater than the threshold are converted into digital values.

```
Black Line  → 1
White Floor → 0
```

The robot then creates a binary pattern representing the detected line position.

Example:

```
001100
```

This pattern determines the steering action.

---

## 2. Straight Line Following

When the center sensors detect the line, both motors run at equal speed.

```
Left Motor  = Full Speed
Right Motor = Full Speed
```

---

## 3. Steering

Different sensor combinations produce different steering commands.

Examples:

```
001100 → Straight

000110 → Slight Right

000010 → Medium Right

000001 → Sharp Right

011000 → Slight Left

010000 → Medium Left

100000 → Sharp Left
```

Motor speed is adjusted by changing the PWM values instead of stopping a motor completely, resulting in smoother motion.

---

## 4. Junction Detection

When multiple sensors become active, the robot identifies:

* Left junction
* Right junction
* Cross junction

The turning direction is selected using internal state variables.

---

## 5. U-turn Recovery

If all sensors lose the line for a predefined time:

* Robot brakes
* Rotates in the desired direction
* Searches until the center sensors detect the line again

This allows recovery after missing a turn.

---

## 6. Wall Following

During the second round, ultrasonic sensors monitor nearby walls.

If a wall is detected, the robot temporarily switches from line following to wall following until the line is found again.

Distance measurements are handled using the **NewPing** library.

---

## 7. Inverse Line Detection

When both outer sensors remain active for a specified duration, the robot automatically toggles between:

* Black line on white surface
* White line on black surface

No manual switching is required.

---

## 8. Sensor Calibration

The robot rotates in place while recording the minimum and maximum values of every sensor.

The calculated calibration values are stored in EEPROM, eliminating the need for recalibration every time the robot is powered on.

---

# Algorithms

## First Round

* Normal line following
* Junction detection
* Sharp turn handling
* U-turn recovery
* Endpoint detection

---

## Second Round

Includes every feature from the first round plus:

* Wall following
* Inverse line detection
* Improved navigation for complex competition tracks

---

# Motor Control

The project uses differential drive.

```
Forward
L = +
R = +

Left Turn
L = Slow
R = Fast

Right Turn
L = Fast
R = Slow

Brake
Both motors reverse briefly
then stop
```

---

# How to Run

1. Open the project in Arduino IDE.
2. Install the **NewPing** library.
3. Connect the robot hardware.
4. Calibrate the sensors if required.
5. Select the desired operating mode:

```cpp
one_round_line_follow();
```

or

```cpp
two_round_line_follow();
```

6. Upload the code.
7. Place the robot on the track and start.

---

# Future Improvements

* PID-based control
* Adaptive speed control
* Maze solving
* Path memory optimization
* OLED display interface
* Bluetooth configuration
* Wi-Fi telemetry
* ESP32 version

---

# Author

**Woliar Rahman**

Department of Electrical and Electronic Engineering (EEE)

Jashore University of Science and Technology (JUST)

Bangladesh

---

## License

This project is intended for educational purposes and robotics competitions. Feel free to use and modify it with appropriate attribution.
