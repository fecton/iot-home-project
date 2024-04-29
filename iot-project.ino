#include "tests.h"

// Overall status
#define LED_DISABLE_CRITICAL_OVERALL    2
#define BUTTON_DISABLE_CRITICAL_OVERALL 3
#define BUZZER_CRITICAL_OVERALL         4

// Microphone
#define MICRO_INPUT               0
#define LED_MICRO_CRITICAL_STATUS 5
#define LED_MICRO_WARNING_STATUS  6

// Temperature
#define TEMP_INPUT               0
#define LED_TEMP_CRITICAL_STATUS 7
#define LED_TEMP_WARNING_STATUS  8

// Gas
#define GAS_INPUT               0
#define LED_GAS_CRITICAL_STATUS 9
#define LED_GAS_WARNING_STATUS  10

// Serial bindings: use for sensors' output
// Available to bind: 300, 600, 750, 1200, 4800, 9600, 19200
#define SERIAL_MICRO 300
#define SERIAL_TEMP  600
#define SERIAL_GAS   750

void testComponents() {
  // LED
  testLED(LED_DISABLE_CRITICAL_OVERALL);
  testLED(LED_MICRO_CRITICAL_STATUS);
  testLED(LED_MICRO_WARNING_STATUS);
  testLED(LED_TEMP_CRITICAL_STATUS);
  testLED(LED_TEMP_WARNING_STATUS);
  testLED(LED_GAS_CRITICAL_STATUS);
  testLED(LED_GAS_WARNING_STATUS);

  // BUZZER
  // testBuzzer(BUZZER_CRITICAL_OVERALL);
}

void setup() {
  // Serial.begin(300);
  // Serial.begin(600);
  // Serial.begin(750);
  // Serial.begin(1200);
  // Serial.begin(4800);
  Serial.begin(9600);
  // Serial.begin(19200);

  testComponents();
}

void loop() {


  delay(1000);
}

