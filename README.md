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

## Demonstration Documentation


https://github.com/user-attachments/assets/e5ec5955-ee45-41bf-81e4-ad48b0a3af9e

## Expected vs. Observed Behavior Table

## 📊 Expected vs. Observed Behavior Table (Based on Video Demo)

| Test Case / Step | Physical Action in Video | Expected System Logic | Expected LED Status | Actual Observed Behavior in Video |
| :--- | :--- | :--- | :--- | :--- |
| **1. Idle / Released State** | Button is NOT pressed; Potentiometer knob untouched[cite: 4]. | `isEnabled = false`<br>`appliedDuty = 0` | Status LED: **OFF**<br>PWM LED: **OFF** | Both Red Status LED and Green PWM LED stay completely **OFF**[cite: 4]. |
| **2. Holding Button (Initial Angle)** | Pressing and holding down the push button at top right[cite: 4]. | `isEnabled = true`<br>`appliedDuty = scaleToDuty(raw)` | Status LED: **ON**<br>PWM LED: **ON** | Red Status LED turns **ON** instantly; Green PWM LED lights up based on current knob position[cite: 4]. |
| **3. Adjusting Brightness (Rotating Knob)** | Rotating the potentiometer knob while continuously holding the button[cite: 4]. | `isEnabled = true`<br>Duty cycle dynamically scales ($0 - 255$) | Status LED: **ON**<br>PWM LED: **Varies** | Red LED remains steadily **ON**; Green PWM LED smoothly changes brightness as knob turns[cite: 4]. |
| **4. Safety Release (Interlock)** | Releasing the push button while leaving the knob in position[cite: 4]. | `isEnabled = false`<br>Forces `appliedDuty = 0` | Status LED: **OFF**<br>PWM LED: **OFF** | Both Red Status LED and Green PWM LED turn **OFF** immediately upon releasing the button[cite: 4]. |


## 📝 Conclusion

Laboratory Activity 5 successfully demonstrated a safety-interlocked workstation light controller using modular ESP32 programming. By dividing the code into `readInputs()`, `processInputs()`, and `updateOutputs()`, the system maintains a clean and reliable logic flow. The active-LOW push button acts as an effective safety switch, forcing outputs to `0` when released, while the `scaleToDuty()` function accurately maps the 12-bit ADC potentiometer readings ($0\text{--}4095$) to an 8-bit PWM brightness level ($0\text{--}255$) when held.
