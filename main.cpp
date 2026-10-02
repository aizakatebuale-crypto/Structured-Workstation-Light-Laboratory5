#include <Arduino.h>

const int BUTTON_PIN = 4;  
const int POT_PIN    = 34;  
const int LED_PIN    = 18;  


const int PWM_FREQ       = 5000; 
const int PWM_RESOLUTION = 8;    


bool isEnabled   = false;
int rawPotValue  = 0;
int outputDuty   = 0;


int scaleToDuty(int raw) {
  int clamped = constrain(raw, 0, 4095);
  return map(clamped, 0, 4095, 0, 255);
}

void readInputs() {
 
  isEnabled   = (digitalRead(BUTTON_PIN) == LOW);
  rawPotValue = analogRead(POT_PIN);
}


void processLogic() {
  if (isEnabled) {
    outputDuty = scaleToDuty(rawPotValue);
  } else {
    
    outputDuty = 0;
  }
}


void writeOutputs() {
  #if defined(ESP_ARDUINO_VERSION_MAJOR) && (ESP_ARDUINO_VERSION_MAJOR >= 3)
    ledcWrite(LED_PIN, outputDuty);
  #else
    ledcWrite(0, outputDuty); 
  #endif
}

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);


  #if defined(ESP_ARDUINO_VERSION_MAJOR) && (ESP_ARDUINO_VERSION_MAJOR >= 3)
    ledcAttach(LED_PIN, PWM_FREQ, PWM_RESOLUTION);
  #else
    ledcSetup(0, PWM_FREQ, PWM_RESOLUTION); 
    ledcAttachPin(LED_PIN, 0);
  #endif

  writeOutputs();
}

void loop() {
  readInputs();
  processLogic();
  writeOutputs();


  Serial.print("Enabled: ");
  Serial.print(isEnabled ? "YES" : "NO");
  Serial.print(" | Raw ADC: ");
  Serial.print(rawPotValue);
  Serial.print(" | Output Duty: ");
  Serial.println(outputDuty);

  delay(20);
}
