# 🎮 ESP32 Bluetooth Color Guessing Game  
A fun, interactive, sensor-based mini-project using **ESP32 + TCS3200 Color Sensor + Bluetooth**.  
No actuators. Just smart sensing, Bluetooth communication, and real-time game logic.

---

## 🚀 Overview  
This project turns an ESP32 into a **Bluetooth-driven color guessing game**.  
The user connects via Bluetooth (phone/laptop), sends guessing inputs (`1`, `2`, `3`), and the ESP32 checks whether the guess matches the detected color under the TCS3200 sensor.

The game is played for **10 rounds** or until the score becomes **≤ 0** after having been positive.

---

## 🎯 Features  
✔ Start game **automatically** when a valid color (Red/Green/Blue) is detected  
✔ Bluetooth-based interaction (HC-05 or ESP32 internal BT)  
✔ TCS3200 color detection using frequency comparison  
✔ Game scoring system  
   - Correct guess → **+5 points**  
   - Wrong guess → **–2 points**  
✔ Smooth input filtering (no invalid characters)  
✔ Skips Unknown/No Object readings  
✔ Game restarts automatically  
✔ No actuators = quick to build  
✔ Perfect for mini-projects, labs, and portfolio demos  

---

## 📡 How the Game Works

### 1) Device Boots  
- Bluetooth name: **ESP32_COLOR_GAME**  
- When phone connects → sends welcome instructions  
- Game waits until any of: **Red / Green / Blue** is detected  

### 2) User Sends Guess Over Bluetooth  
```

1 → Red
2 → Green
3 → Blue

```

### 3) ESP32 Responds  
- Reads actual color  
- Compares with guess  
- Updates score  
- Prints result  

### 4) Game Ends When  
- 10 rounds completed  
**OR**  
- Score ≤ 0 (after first positive score)

### 5) Automatically waits for a new color to start again.

---

## 🧠 Hardware Required  
| Component | Quantity |
|----------|----------|
| ESP32 Dev Kit V1 | 1 |
| TCS3200 Color Sensor | 1 |
| Jumper Wires | As needed |
| Power Source (5V USB) | 1 |

(Optional: Cardboard tube or cover to block ambient light)

---

## 🔌 Wiring Diagram (Text Version)

| TCS3200 Pin | ESP32 Pin |
|-------------|-----------|
| S0 | 23 |
| S1 | 22 |
| S2 | 19 |
| S3 | 18 |
| OUT | 5 |
| VCC | 3.3V |
| GND | GND |

---

## 📱 Bluetooth Terminal Setup  
Use any Bluetooth terminal app (Android/iOS):

- Serial Bluetooth Terminal  
- Bluetooth Electronics  
- Arduino Bluetooth Controller  
- iOS Bluefruit, etc.

Pair with:
```

ESP32_COLOR_GAME

```

Then send:
```

1 → Red
2 → Green
3 → Blue

```

---

## 🧩 Game Logic Flowchart

```

Bluetooth Connected
↓
Show Welcome Message
↓
Check Sensor
↓  ↓  ↓
Red / Green / Blue?  → YES → Start Game
↓ NO
Wait for valid color

```

During game:
```

Receive guess → Validate → Detect Color
↓
Match? +5 : -2
↓
Update Score
↓
Game Over?

```

---

## 🛠 Source Code  
The full working code is available in:

```

/src/esp32_color_game.ino

```

Contains:
- Bluetooth initialization  
- Frequency-based color detection  
- Robust guessing engine  
- Scoring system  
- Game restarts  
- Unknown color filtering  

---

## 🔧 Core Functions

### `readRGB()`  
Reads averaged frequency values for Red, Green, Blue filters.

### `getColor()`  
Returns:
```

"Red", "Green", "Blue", "No Object", "Unknown"

````

### Game Variables  
```cpp
int rounds = 0;
int score = 0;
bool hasPositiveScore = false;
bool gameStarted = false;
````

---

## 🎥 Demo



---

## 📝 Future Enhancements

* Add OLED display scoreboard
* Add “HEX code” output for color analysis
* Create Android app UI (buttons + scoreboard)
* Add sound feedback with buzzer
* Store scores in EEPROM
* Multi-color learning mode

---

## 📄 License

MIT License is recommended for student projects.

---

## ✨ Author

**Daniel Raj C**
ESP32 / IoT / Embedded Systems Projects

```
github.com/DanielRajChristeen
```

---

## ⭐ If you like this project…

Consider giving the repository a **star** to support future work!
