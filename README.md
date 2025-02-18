
# IoT-based Active Safety System for Coastal and Harbour Ferries

## Project Overview

This project aims to enhance the safety of coastal and harbour ferries using IoT technology. By leveraging ESP8266 modules for communication and an MPU sensor for roll angle calculations, we provide a real-time safety monitoring system. The system alerts the crew with a buzzer when the ferry's roll angle exceeds a predetermined threshold, ensuring timely responses to potential hazards.

## Key Components

1. **ESP8266 Modules**: For Wi-Fi communication between devices.
2. **MPU Sensor**: Calculates the roll angle of the ferry.
3. **Kalman Filter**: Ensures accurate roll angle calculation through sensor fusion.
4. **Buzzer**: Alerts the crew when the roll angle exceeds the threshold.

## Features

- **Real-time Monitoring**: Continuously monitors the ferry's roll angle.
- **Accurate Calculations**: Utilizes the Kalman filter for precise sensor fusion.
- **Safety Alerts**: Buzzer alerts the crew when the roll angle exceeds the threshold.

### Hardware Requirements

- 2 x ESP8266 Modules
- 1 x MPU Sensor (e.g., MPU-6050)
- 1 x Buzzer
- Breadboard and connecting wires
- 2 x LED (Red And Green)

### Software Requirements

- Arduino IDE
- ESP8266 Library for Arduino
- MPU6050 Library for Arduino
- Kalman Filter Library

## Usage

- **Real-time Monitoring**: Continuously monitor the roll angle of the ferry.
- **Safety Alerts**: Receive immediate alerts if the roll angle exceeds the safe threshold.

## Receiver Circuit Design
- ![Screenshot 2024-07-16 124518](https://github.com/user-attachments/assets/09df9461-70b2-4851-9944-1c8e14397150)

## Transmitter Circuit Design
- ![Screenshot 2024-07-16 123907](https://github.com/user-attachments/assets/72fae526-53b5-4cdc-901d-e05b967c360b)


## Contact

For questions or feedback, please open an issue on GitHub or reach out to us at [swargiarijitraj@gmail.com].

---

**Stay Safe, Sail Smart!**

#IoT #FerrySafety #MaritimeTech #ESP8266 #KalmanFilter #SmartSafety
