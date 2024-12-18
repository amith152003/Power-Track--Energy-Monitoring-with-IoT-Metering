# PowerTrack - An IoT Based Energy Meter

## Overview

PowerTrack is a smart energy monitoring IoT-based metering device designed to track and manage electricity consumption. It accurately measures various electrical parameters such as **Voltage**, **Current**, **Power**, and **Energy** over time. This device allows users to analyze their energy consumption patterns, calculate electricity bills based on real-time data, and manage energy usage more efficiently.

The project is powered by an **ATmega328P** microcontroller with an **ESP32** module for Wi-Fi connectivity, enabling data transmission to a **Firebase Database**. Additionally, data visualization is done using **Google Sheets**, making it easy for users to monitor their energy consumption remotely.

---

## Features

- **Real-time Energy Monitoring**: Measure voltage, current, power, and energy consumption.
- **Bill Calculation**: Calculate electricity bills based on time-of-day usage and different pricing rates.
- **Data Logging**: Store consumption data on Firebase for future reference.
- **Mobile App Integration**: View data and real-time status through a custom mobile app.
- **Multiple Display Screens**: Display live readings, units consumed, and billing information on a 20x4 LCD.
- **User Alerts**: Real-time notifications for abnormal voltage or current.
- **Time-based Pricing**: Energy pricing adjusts based on the time of day (Day, Evening, Night).
- **Relay Control**: Control a relay to manage electrical appliances based on specific conditions.

---
## Components Used

### Hardware

| **Component**        | **Description**                                                                 |
|----------------------|---------------------------------------------------------------------------------|
| **ATmega328P**        | Main microcontroller that handles the sensor readings and processes data.      |
| **ESP32**             | Wi-Fi module for communication with Firebase and Google Sheets.                |
| **ZMPT101B**          | Voltage sensor for measuring AC voltage.                                       |
| **ACS758**            | Current sensor for measuring AC current.                                       |
| **ADS1115**           | ADC used for precise analog-to-digital conversion (for current sensing).       |
| **RTC DS3231**        | Real-time clock module for accurate timekeeping.                               |
| **20x4 LCD Display**  | Used to display real-time data (voltage, current, power, etc.).                |
| **Cooling Fan**       | Optional component used for cooling the system (if necessary).                 |
| **EEPROM**            | Memory module for storing past consumption data.                              |

### Libraries

| **Library**               | **Purpose**                                                                         |
|---------------------------|-------------------------------------------------------------------------------------|
| **LiquidCrystal_I2C**      | Library for controlling the 20x4 LCD display.                                       |
| **ADS1X15**                | Library to interface with the ADS1115 ADC for current sensing.                      |
| **Wire**                   | Library for I2C communication between microcontroller and sensors/display.          |
| **SoftwareSerial**         | Provides software-based serial communication on digital pins.                       |
| **ZMPT101B**               | Library for interfacing with the ZMPT101B voltage sensor.                           |
| **RTClib**                 | Library for interfacing with the DS3231 real-time clock.                           |
| **EEPROM**                 | Library to read/write data from the EEPROM memory.                                 |
| **WiFi**                   | Library for ESP32 Wi-Fi connection to the internet and Firebase.                   |
| **ESP32Firebase**          | Library to send and receive data from Firebase on ESP32.                           |
| **WiFiClientSecure**       | Library to create secure connections with Firebase and Google Sheets API.          |
| **TRIGGER_WIFI**           | Custom library for managing Wi-Fi connections and retries.                         |
| **TRIGGER_GOOGLESHEETS**   | Custom library for sending data to Google Sheets API.                              |

---

## Installation

### Prerequisites

- **Arduino IDE**: Install [Arduino IDE](https://www.arduino.cc/en/software) for programming the ATmega328P and ESP32.
- **Firebase Account**: Set up a Firebase project to store consumption data. Add the Firebase credentials to your ESP32 code.
- **Google Sheets API**: Set up a Google Sheets API and integrate it with the ESP32 to log data.

### Setup

1. Clone this repository or download the files.
2. Install the necessary libraries in the Arduino IDE:
   - `LiquidCrystal_I2C`
   - `ADS1X15`
   - `Wire`
   - `SoftwareSerial`
   - `ZMPT101B`
   - `RTClib`
   - `EEPROM`
   - `WiFi`
   - `ESP32Firebase`
   - `WiFiClientSecure`
   - `TRIGGER_WIFI`
   - `TRIGGER_GOOGLESHEETS`
3. Connect the components as per the circuit diagram provided in the repository (if available).
4. Configure the **SSID** and **PASSWORD** in the ESP32 code to connect to your Wi-Fi network.
5. Upload the code to the ATmega328P and ESP32 using the Arduino IDE.

---

## Code Description

### ATmega328P Code

The ATmega328P microcontroller collects data from various sensors, including voltage and current, and calculates real-time values for power and energy consumption. The readings are displayed on a 20x4 LCD and stored in the EEPROM for later retrieval. The bill is calculated based on time-of-day pricing, and the data is sent to the ESP32 for further processing and transmission to Firebase.

Key functions:
- `Get_Voltage()`: Measures the voltage using the ZMPT101B sensor.
- `getRmsCurrent()`: Measures the current using the ACS758 sensor.
- `getPower()`: Calculates real power based on voltage and current readings.
- `getEnergy()`: Computes energy consumption based on the power readings.
- `Price_Calculation()`: Computes the electricity bill based on time-of-day prices.
- `SendReceiveData()`: Sends the measured data to the ESP32 for further processing.

### ESP32 Code

The ESP32 acts as the communication bridge between the ATmega328P and Firebase. It receives the data from the ATmega328P over serial communication, processes it, and sends it to Firebase for real-time monitoring. It also retrieves pricing data from Firebase for bill calculation.

Key functions:
- `Google_Sheets_Init()`: Initializes the Google Sheets API for data logging.
- `Firebase.setFloat()`: Sends energy-related data to Firebase.
- `Relay Control`: Manages the relay based on the received data, such as voltage and current limits.

---

## Firebase Setup

1. Create a Firebase project and configure the real-time database.
2. Add the Firebase credentials (API key, database URL, etc.) to the ESP32 code.
3. Structure the database to include fields for **Meter/Voltage**, **Meter/Current**, **Meter/Power**, **Meter/Units**, and **Meter/Total_Rate**.
4. Integrate Firebase rules to control access and ensure data security.

---

## Google Sheets Setup

1. Set up a Google Sheet for data visualization.
2. Use Google Apps Script to configure API calls and link the sheet with your ESP32.
3. Share the Google Sheet with the necessary permissions for data access.

---

## Usage

- Power on the system and ensure all components are connected.
- The device will start measuring voltage, current, power, and energy consumption.
- The LCD will display real-time data on multiple pages (Voltage, Current, Power, Units, and Bill).
- Access the Firebase database to monitor the data remotely or use the Google Sheets integration for graphs and trends.
- The relay will automatically switch based on voltage and current limits set in the Firebase database.

---

## Troubleshooting

- **Wi-Fi Connection Issues**: Make sure the SSID and password are correctly set in the ESP32 code.
- **Sensor Readings Not Correct**: Verify the sensor connections and calibration.
- **Relay Not Switching**: Check the relay control logic and ensure that Firebase contains the correct settings.

---
## Team Member

- **Amith Mathew Titus**
- **Anugraha M.**
- **Chaithanya C.**

---

## License

This project is licensed under the MIT License.

