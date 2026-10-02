# Laboratory Activity 5: Structured Workstation Light Controller

An ESP32-based workstation light controller built using C++ and PlatformIO/Arduino. This project applies a **modular architecture** (separating inputs, processing, and outputs) to implement a safety push-button interlock and potentiometer-driven PWM brightness control.

---

##  Project Overview
* **Microcontroller:** DOIT ESP32 DEVKIT V1
* **Framework:** Arduino / PlatformIO
* **Core Features:**
  * **Active-LOW Enable Interlock:** Button press activates status indicator and enables dimming control.
  * **12-bit to 8-bit Scaling:** Custom function maps ADC potentiometer readings ($0 - 4095$) to PWM duty cycle ($0 - 255$).
  * **Structured Architecture:** Strictly enforces separation into `readInputs()`, `processInputs()`, and `updateOutputs()`.

---

## Summary Table

| Parameter / Feature | Configuration / Value | Description / Function |
| :--- | :--- | :--- |
| **Microcontroller Board** | DOIT ESP32 DEVKIT V1 | Main controller running Arduino / PlatformIO framework. |
| **Push Button Input** | `GPIO 4` (`BUTTON_PIN`) | Active-LOW momentary enable switch (`INPUT_PULLUP`). |
| **Potentiometer Input** | `GPIO 34` (`POT_PIN`) | Analog input sampling $0 - 3.3\text{V}$ ($12\text{-bit ADC: } 0 - 4095$). |
| **Status LED Output** | `GPIO 2` (`STATUS_LED_PIN`) | Red LED indicator; turns ON when control is enabled. |
| **Workstation Light Output**| `GPIO 18` (`PWM_LED_PIN`) | Green LED driven by PWM via LEDC Channel 0. |
| **PWM Settings** | $5\text{ kHz}$ @ $8\text{-bit}$ resolution | PWM frequency with duty cycle output range of $0 - 255$. |
| **Scaling Function** | `scaleToDuty(int raw)` | Maps raw ADC values ($0 - 4095$) to PWM duty cycles ($0 - 255$). |
| **Safety Interlock Logic** | `isEnabled == false` | Forces `appliedDuty = 0` and Status LED OFF when button is released. |
| **Code Architecture** | Modular (`read`, `process`, `update`) | Separates input sampling, decision logic, and hardware driving. |

---

## Hardware Connections & Pinout

### Point-to-Point Wiring Map
```text
[ LAPTOP / PC ] ─── (USB Cable) ───► [ ESP32 Micro-USB Port ]

[ ESP32 GPIO 4  ] ─── (Jumper Wire) ───► [ Push Button Leg 1 ]
[ ESP32 GND     ] ─── (Black Wire) ────► [ Push Button Leg 2 & Breadboard GND Rail ]

[ ESP32 GPIO 34 ] ─── (Yellow Wire) ───► [ Potentiometer Wiper (Center) ]
[ ESP32 3.3V    ] ─── (Red Wire) ──────► [ Potentiometer VCC (Pin 1) ]
[ Breadboard GND] ─── (Black Wire) ────► [ Potentiometer GND (Pin 3) ]

[ ESP32 GPIO 2  ] ─── (Jumper Wire) ───► [ 220Ω Resistor ] ───► [ Red Status LED (+) ]
[ ESP32 GPIO 18 ] ─── (Green Wire) ────► [ 220Ω Resistor ] ───► [ Green PWM LED (+) ]
[ Breadboard GND] ───────────────────────────────────────────► [ LED Cathodes (-) ]
```
## Expected vs. Observed Behavior Table

| Test Case / Condition | Button State (`isEnabled`) | Knob Position | Expected Raw ADC (`rawPotValue`) | Expected PWM Duty (`appliedDuty`) | Expected LED Behavior | Observed Hardware Behavior |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **1. Reset with Button Released** | Released (`false`) | Any Position | $0 - 4095$ | `0` | Both LEDs OFF | Red and Green LEDs stay completely OFF. |
| **2. Rotate Knob While Released** | Released (`false`) | Low $\rightarrow$ High | $0 \rightarrow 4095$ | `0` | Both LEDs OFF | Rotating knob has no effect; output stays OFF. |
| **3. Hold Button (Low Position)** | Held (`true`) | Fully Counter-Clockwise | $0 - 100$ | $0 - 6$ | Status LED ON; Dimming LED OFF/Dim | Red LED ON; Green LED OFF or barely visible. |
| **4. Hold Button (Mid Position)** | Held (`true`) | Centered (~50%) | ~$2047$ | ~$127$ | Status LED ON; Dimming LED Medium | Red LED ON; Green LED lit at ~50% brightness. |
| **5. Hold Button (High Position)**| Held (`true`) | Fully Clockwise | $4095$ | $255$ | Status LED ON; Dimming LED Full | Red LED ON; Green LED lit at 100% brightness. |
| **6. Release Button Mid-Operation**| Released (`false`) | Kept at High Position | $4095$ | `0` | Both LEDs turn OFF instantly | Both Red and Green LEDs turn OFF immediately. |

## Demonstration Documentation


https://github.com/user-attachments/assets/e5ec5955-ee45-41bf-81e4-ad48b0a3af9e


## 📝 Conclusion

Laboratory Activity 5 successfully demonstrated a safety-interlocked workstation light controller using modular ESP32 programming. By dividing the code into `readInputs()`, `processInputs()`, and `updateOutputs()`, the system maintains a clean and reliable logic flow. The active-LOW push button acts as an effective safety switch, forcing outputs to `0` when released, while the `scaleToDuty()` function accurately maps the 12-bit ADC potentiometer readings ($0\text{--}4095$) to an 8-bit PWM brightness level ($0\text{--}255$) when held.
