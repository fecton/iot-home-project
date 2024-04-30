#include "tests.h"
#include "gas_sensor.h"
#include "temp_sensor.h"
#include "micro_sensor.h"
#include "lcd_sensor.h"

#include "classes.h"


// Overall status
#define LED_DISABLE_CRITICAL_OVERALL    2
#define BUTTON_DISABLE_CRITICAL_OVERALL 3
#define BUZZER_CRITICAL_OVERALL         4

// Microphone
#define MICRO_INPUT               A4
#define LED_MICRO_CRITICAL_STATUS 5
#define LED_MICRO_WARNING_STATUS  6

// Temperature
#define TEMP_INPUT               A2
#define LED_TEMP_CRITICAL_STATUS 7
#define LED_TEMP_WARNING_STATUS  8

// Gas
#define GAS_INPUT               A3
#define LED_GAS_CRITICAL_STATUS 9
#define LED_GAS_WARNING_STATUS  10

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
  testBuzzer(BUZZER_CRITICAL_OVERALL);
}

void setup() {
  // Pin LEDs
  pinMode(LED_DISABLE_CRITICAL_OVERALL, OUTPUT);
  pinMode(LED_MICRO_CRITICAL_STATUS,    OUTPUT);
  pinMode(LED_MICRO_WARNING_STATUS,     OUTPUT);
  pinMode(LED_TEMP_CRITICAL_STATUS,     OUTPUT);
  pinMode(LED_TEMP_WARNING_STATUS,      OUTPUT);
  pinMode(LED_GAS_CRITICAL_STATUS,      OUTPUT);
  pinMode(LED_GAS_WARNING_STATUS,       OUTPUT);

  // Pin Buzzers
  pinMode(BUZZER_CRITICAL_OVERALL, OUTPUT);

  // Pin Sensors
  pinMode(MICRO_INPUT, INPUT);
  pinMode(TEMP_INPUT,  INPUT);
  pinMode(GAS_INPUT,   INPUT);

  // Overall status
  Serial.begin(9600);

  // Uncomment to validate circuit components
  // testComponents();
}

void loop() {
  Base_Sensor gas_sensor = Base_Sensor(LED_GAS_WARNING_STATUS, LED_GAS_CRITICAL_STATUS, BUZZER_CRITICAL_OVERALL, 400, 800, "Gas");
  
  // TODO: make temp and micro sensors work
  Base_Sensor temp_sensor = Base_Sensor(LED_TEMP_WARNING_STATUS, LED_TEMP_CRITICAL_STATUS, BUZZER_CRITICAL_OVERALL, 25, 30, "Temp");
  Base_Sensor micro_sensor = Base_Sensor(LED_MICRO_WARNING_STATUS, LED_MICRO_CRITICAL_STATUS, BUZZER_CRITICAL_OVERALL, 1500, 2000, "Micro");


  gas_sensor.status(analogRead(GAS_INPUT));
  micro_sensor.status(analogRead(MICRO_INPUT));

  Serial.println();

  delay(100);

}

