# 🤖 Multi-Axis Robotic Arm Control (v1.0)

## 📌 Project Overview
This project focuses on the development of a lightweight robotic arm controlled by an **STM32L476RG (Cortex-M4)** microcontroller. The architecture is designed to transition from direct hardware PWM control to an I2C-based expansion system, ultimately integrating with **ROS 2** for advanced motion planning (and manipulation).

---

## 🛠 Progress & Milestones

### 🟢 Phase 1: Core Hardware Abstraction (Completed)
* **C++ Hardware Wrapper:** Successfully encapsulated STM32 HAL (C-based) libraries into a modular, object-oriented `Servo` class.
* **Direct Timer Control:** Implementation of PWM generation via Timer 2 (TIM2) using multiple channels on pins `PA0` and `PA1`.
* **Synchronized Motion Profiling:** Developed non-blocking `update()` methods to allow smooth, simultaneous movement of multiple joints without CPU "stalling."

### 🟡 Phase 2: Expansion & I2C Integration (In Progress)
* **PCA9685 Driver Implementation:** Developing a custom C++ driver to offload PWM generation for up to 16 servos via the **I2C protocol** ($SDA$/$SCL$).
* **Bus Management:** Shifting from local MCU timers to an external 12-bit PWM controller to reduce interrupt overhead and simplify cable management.
* **Power Distribution:** Using a dedicated AC-DC power converter (output 6V/5A) to handle the high inrush current of multiple simultaneous servo movements, protecting the nucleo logic board.

### ⚪ Phase 3: Mechanical Design & Simulation
* **Structural Engineering:** 3D modeling a lightweight, high-rigidity chassis optimized for low-torque **MG90S** servos.
* **Kinematics Optimization:** Calculating center of mass and leverage points to maximize effective payload capacity.

### ⚪ Phase 4: ROS 2 & High-Level Control
* **micro-ROS Integration:** Bridging the STM32 with a ROS 2 workspace via Serial/USB transport.
* **Joint State Broadcasting:** Exporting commanded joint trajectories to RViz2 for real-time kinematic digital-twin synchronization.
* **Inverse Kinematics (IK):** Implementing coordinate-based movement to allow the end-effector to reach specific $X, Y, Z$ targets.

---

## 📐 System Architecture

### Component Selection
| Component | Specification | Role |
| :--- | :--- | :--- |
| **MCU** | STM32L476RG (80MHz) | Main Logic & Real-time Processing |
| **PWM Driver** | PCA9685 (I2C) | 16-Channel 12-bit PWM Expansion |
| **High-Torque Actuator** | MG996R (Standard Size) | Primary Shoulder Rotation |
| **Precision Actuators** | MG90S (Metal Gear) | Primary base Articulation |
| **Lightweight Actuators**| SG90 (Plastic Gear) | Other joints / Gripper Mechanism |
| **Interface** | UART / micro-ROS | External Command & Telemetry |

### Logic Flow
1.  **Command:** User or ROS 2 node sends target joint angles.
2.  **Processing:** STM32 calculates the duty cycle scaling for the 12-bit PCA9685 registers.
3.  **Transmission:** I2C Bus transmits data packets to the **0x40** address.
4.  **Actuation:** PCA9685 provides stable, independent 50Hz PWM signals to all connected servos.

---

## 🔌 Schematic & Wiring
*(Section to be updated with circuit diagrams)*

Current Pinout (Phase 1):
* **PA0:** Elbow Servo (TIM2_CH1)
* **PA1:** Wrist Servo (TIM2_CH2)
* **VCC:** 5V From USB Port
* **GND:** Common Ground
