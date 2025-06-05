# 🌱 Smart Greenhouse System – ESP32-Based IoT Project

This project implements an **IoT-based Smart Greenhouse System** using an **ESP32 microcontroller**, **temperature/humidity and light sensors**, and a **Firebase-powered Android mobile app** for real-time monitoring and control. The system offers a modern solution for optimizing plant growth conditions through smart automation.

---

## 📷 Project Overview

The Smart Greenhouse monitors:

- 🌡️ Temperature (via DHT11)
- 💧 Humidity (via DHT11)
- 💡 Light intensity (via LDR)

The system:

- Sends real-time data to Firebase
- Provides both **automatic** and **manual** control over fans, lights, and water pumps
- Uses an **Android application** (built with MIT App Inventor) for monitoring and control

---

## 🚀 Features

### 🔄 Real-Time Monitoring
- Temperature and humidity updates every few seconds.
- Light intensity captured using an LDR.

### ☁️ Firebase Integration
- ESP32 sends data to **Firebase Realtime Database**.
- Android app fetches and displays sensor data instantly.

### 🎛️ Dual Control Modes
- **Automatic**: Actions triggered based on sensor values.
- **Manual (Otonom)**: User can manually control hardware components via the app.

### ♻️ Energy & Resource Optimization
- Automated irrigation and ventilation reduce water and energy waste.
- Helps achieve sustainable agriculture practices.

---

## 🧰 Components Used

| Component | Description |
|----------|-------------|
| **ESP32** | Wi-Fi enabled microcontroller for IoT integration |
| **DHT11** | Temperature and humidity sensor |
| **LDR** | Light dependent resistor for light intensity |
| **Fan, Water Pump, LEDs** | Actuators controlled based on environment |
| **Firebase** | Realtime cloud database for data logging |
| **Android App** | Developed via MIT App Inventor for remote access |
| **Miscellaneous** | Breadboard, jumpers, resistors, power supply |

---

## 🔌 Circuit Diagram

![Circuit Diagram](https://your-image-url.com) *(Add circuit diagram screenshot here if available)*

---

## 📱 Android App

Developed using [MIT App Inventor](https://appinventor.mit.edu)

### Features:
- Firebase login (`user:123`)
- Live display of environmental data
- Control toggles for fan, water pump, and lights
- Auto/manual mode switch
---

## 🧾 main.ino (ESP32 Code Overview)

The `main.ino` script does the following:

1. Connects ESP32 to Wi-Fi
2. Reads data from DHT11 and LDR
3. Sends data to Firebase
4. Listens to Firebase for commands
5. Controls actuators based on real-time commands or thresholds

#### 📌 Sample Code Snippet:
```cpp
float humidity = dht.readHumidity();
float temperature = dht.readTemperature();
int lightValue = analogRead(ldrPin);

// Upload to Firebase
Firebase.setFloat(firebaseData, "/sensor/temperature", temperature);
Firebase.setFloat(firebaseData, "/sensor/humidity", humidity);
Firebase.setInt(firebaseData, "/sensor/light", lightValue);
```

---

## 🧮 Calculations

- **Humidity**: `float humidity = data[0] + data[1] / 10.0`
- **Temperature**: `float temperature = data[2] + data[3] / 10.0`
- **Light %**: `(ADC_VALUE * 100) / 4095`

---

## 📊 Performance Evaluation

| Aspect | Summary |
|--------|---------|
| **Sensor Reliability** | Stable under test conditions with filtering |
| **Firebase Speed** | Occasional delay due to U.S.-based server |
| **App Responsiveness** | Real-time updates, low latency observed |
| **User Experience** | Simple and intuitive interface |

---

## 🔮 Future Improvements

- Implement **machine learning** to predict optimal climate conditions.
- Switch to **local or Europe-based servers** for lower latency.
- Add **CO₂ sensors** and **soil moisture** support.
- Expand to multi-greenhouse control with dashboards.
---

## 📜 License

This project is released under the [MIT License](LICENSE).
