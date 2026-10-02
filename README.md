# Laboratory Activity 5: Structured Workstation Light

An ESP32-based embedded system project using modular software design principles (separate input, processing, and output functions) to implement a safety workstation light with PWM brightness control and button-enable safety interlocks.

---

## Project Overview
* **Microcontroller:** DOIT ESP32 DEVKIT V1
* **Language/Framework:** C++ / Arduino (PlatformIO)
* **Key Features:**
  * Active-LOW push button acts as an enable hold switch.
  * 12-bit ADC reading from potentiometer mapped to 8-bit PWM LED control.
  * Modular architecture enforcing `readInputs()`, `processLogic()`, and `writeOutputs()`.

---

## Hardware Connections & Pinout

| Component | ESP32 Pin | Logic / Function |
| :--- | :--- | :--- |
| **Push Button** | `GPIO 4` | Digital Input (`INPUT_PULLUP`), Active-LOW Enable |
| **Potentiometer** | `GPIO 34` | Analog Input (`ADC1_CH6`), 0 - 3.3V Variable |
| **Workstation LED** | `GPIO 18` | PWM Output (`LEDC`), 5 kHz @ 8-bit resolution |

### Component Interconnection List

* **Push Button (Enable Interlock):**
  * One leg connected to **GPIO 4** (`BUTTON_PIN`) via **White Wire**
  * Opposite leg connected to **GND Rail** via **Black Wire**
* **Potentiometer (Brightness Control):**
  * Center Pin (Wiper) connected to **GPIO 34** (`POT_PIN`) via **Yellow/Green Wire**
  * Outer Pin 1 connected to **3.3V Rail** via **Red Wire**
  * Outer Pin 2 connected to **GND Rail** via **Black Wire**
* **Workstation Light (Green LED Output):**
  * Anode (+) connected to **GPIO 18** (`LED_PIN`) via **Green Wire** through a **220Ω Resistor**
  * Cathode (-) connected directly to **GND Rail**
* **Power & Ground Connections:**
  * **ESP32 Micro-USB Port** connected to **Laptop/PC** via **USB Cable** (Power & Serial)
  * **ESP32 GND Pin** connected to **Breadboard GND Rail** via **Black Wire**

---

### Terminal Connection Block Diagram

```text
[ LAPTOP / PC ] <=== USB Cable ===> [ ESP32 Micro-USB Port ]

[ ESP32 GPIO 4 ]  <=== White Wire =====> [ Push Button Leg 1 ]
[ Breadboard GND ] <=== Black Wire =====> [ Push Button Leg 2 ]

[ ESP32 GPIO 34 ] <=== Yellow Wire ====> [ Potentiometer Center Wiper ]
[ Breadboard 3.3V] <=== Red Wire ======> [ Potentiometer Pin 1 ]
[ Breadboard GND ] <=== Black Wire ====> [ Potentiometer Pin 2 ]

[ ESP32 GPIO 18 ] <=== Green Wire ====> [ 220Ω Resistor ] ===> [ LED Anode (+) ]
[ Breadboard GND ] <======================================== [ LED Cathode (-) ]

---

## System Logic & Flow
```text
  RED WIRE - GPIO 4 (ESP32) - LED (ANODE +) - LED (CATHODE -) - 220Ω RESISTOR - GND RAIL
  BLACK WIRE - GND (ESP32) - GND RAIL
  USB CABLE - ESP32 - PC / LAPTOP (POWER SOURCE)

```

## Documentation / Required Testing


https://github.com/user-attachments/assets/df406601-6fb2-4ef1-a05e-25e464fe2947


## Expected vs. Observed Behavior Table

| Test Case / Condition | Button State (`isEnabled`) | Knob Position | Expected Raw ADC (`rawPotValue`) | Expected Duty (`outputDuty`) | Observed Hardware Behavior |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **1. System Reset / Idle** | Released (`false`) | Any position | Variable ($0 - 4095$) | `0` | LED is completely OFF |
| **2. Released Knob Rotation** | Released (`false`) | Rotated Low → High | Changing ($0 \rightarrow 4095$) | `0` | LED remains OFF despite knob rotation |
| **3. Held - Low Position** | Held (`true`) | Fully Counter-Clockwise | $0 - 100$ | $0 - 6$ | Green LED is OFF / extremely dim |
| **4. Held - Middle Position** | Held (`true`) | Center (~50%) | ~$2047$ | ~$127$ | Green LED illuminates at ~50% medium brightness |
| **5. Held - High Position** | Held (`true`) | Fully Clockwise | ~$4095$ | $255$ | Green LED illuminates at 100% full brightness |
| **6. Released Mid-Operation** | Released (`false`) | Kept at High position | ~$4095$ | `0` | Green LED turns OFF immediately upon button release |

## Conclusion 

The activity successfully demonstrated a modular ESP32 workstation light controller by separating the codebase into distinct readInputs(), processLogic(), and writeOutputs() functions. The active-LOW push button effectively functions as a safety interlock, forcing the PWM output duty cycle to 0 whenever released. When held, the scaleToDuty() function accurately converts the 12-bit ADC potentiometer reading ($0\text{--}4095$) into an 8-bit PWM value ($0\text{--}255$), providing smooth and reliable brightness control. 


