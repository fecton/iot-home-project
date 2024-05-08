// Internal libs
#include "tests.h"
#include "classes.h"

// External libs
#include "DHT.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Overall status
#define BUZZER_CRITICAL_OVERALL 9

// Temperature
#define TEMP_INPUT               A3
#define LED_TEMP_CRITICAL_STATUS 10
#define LED_TEMP_WARNING_STATUS  11

// Gas
#define GAS_INPUT               A2
#define LED_GAS_CRITICAL_STATUS 12
#define LED_GAS_WARNING_STATUS  13

// Distance
#define DISTANCE_ECHO_INPUT 8
#define DISTANCE_TRIG_INPUT 7
#define LED_DISTANCE_CRITICAL_STATUS 4
#define LED_DISTANCE_WARNING_STATUS 3

// Disabling
#define BUTTON_DISABLE_STATUS 5
#define LED_DISABLE_STATUS 6

// LED display
#define DISPLAY_SDA A4
#define DISPLAY_SDA A5

// RGB led
#define LED_RED_INPUT 2
#define LED_GREEN_INPUT 3
#define LED_BLUE_INPUT A1


void testComponents() {
  // LED
  testLED(LED_DISABLE_STATUS);
  testLED(LED_TEMP_CRITICAL_STATUS);
  testLED(LED_TEMP_WARNING_STATUS);
  testLED(LED_GAS_CRITICAL_STATUS);
  testLED(LED_GAS_WARNING_STATUS);

  // BUZZER
  testBuzzer(BUZZER_CRITICAL_OVERALL);
}

void setup() {
  // Pin buttons
  pinMode(BUTTON_DISABLE_STATUS, INPUT);

  // Pin LEDs
  pinMode(LED_DISABLE_STATUS, OUTPUT);

  pinMode(LED_TEMP_CRITICAL_STATUS,     OUTPUT);
  pinMode(LED_TEMP_WARNING_STATUS,      OUTPUT);

  pinMode(LED_GAS_CRITICAL_STATUS,      OUTPUT);
  pinMode(LED_GAS_WARNING_STATUS,       OUTPUT);

  pinMode(LED_DISTANCE_CRITICAL_STATUS, OUTPUT);
  pinMode(LED_DISTANCE_WARNING_STATUS,  OUTPUT);

  // Pin RGB
  pinMode(LED_RED_INPUT, OUTPUT);
  pinMode(LED_GREEN_INPUT, OUTPUT);
  pinMode(LED_BLUE_INPUT, OUTPUT);

  // Pin Buzzers
  pinMode(BUZZER_CRITICAL_OVERALL, OUTPUT);

  // Pin Sensors
  pinMode(TEMP_INPUT,  INPUT);
  pinMode(GAS_INPUT,   INPUT);

  // Overall status
  Serial.begin(9600);

  // Distance Sensor
  pinMode(DISTANCE_ECHO_INPUT, INPUT);
  pinMode(DISTANCE_TRIG_INPUT, OUTPUT);

  // LCD display

  // Uncomment to validate circuit components
  // testComponents();

  lcd.init();
  lcd.backlight();
}

bool status_state = true;
bool RGB[7][3] = {
  {0,0,1},
  {0,1,0},
  {0,1,1},
  {1,0,0},
  {1,0,1},
  {1,1,0},
  {1,1,1}
};

int rgb_index = 0;


void loop() {
  lcd.clear();

  digitalWrite(LED_RED_INPUT,   RGB[rgb_index][0]);
  digitalWrite(LED_GREEN_INPUT, RGB[rgb_index][1]);
  digitalWrite(LED_BLUE_INPUT,  RGB[rgb_index][2]);

  if(rgb_index == 7) { rgb_index = 0; }
  else               { rgb_index++;   }


  if(digitalRead(BUTTON_DISABLE_STATUS)) {
    status_state = !status_state;
  }

  // Gas
  Base_Sensor gas_sensor = Base_Sensor(
    LED_GAS_WARNING_STATUS,
    LED_GAS_CRITICAL_STATUS,
    BUZZER_CRITICAL_OVERALL,
    400, 800, "Gas"
  );
  int GAS_LEVEL = analogRead(GAS_INPUT);

  // Temp
  Base_Sensor temp_sensor = Base_Sensor(
    LED_TEMP_WARNING_STATUS,
    LED_TEMP_CRITICAL_STATUS,
    BUZZER_CRITICAL_OVERALL,
    25, 30, "Temp"
  );
  int TEMP_LEVEL = Temp_Sensor::readTemperature(TEMP_INPUT);

  // Distance
  Base_Sensor distance_sensor = Base_Sensor(
    LED_DISTANCE_WARNING_STATUS,
    LED_DISTANCE_CRITICAL_STATUS,
    BUZZER_CRITICAL_OVERALL,
    800, 900, "Distance"
  );
  int DISTANCE_LEVEL = 1000 - Distance_Sensor::readDistance(DISTANCE_TRIG_INPUT, DISTANCE_ECHO_INPUT);


  if(status_state) {
    digitalWrite(LED_DISABLE_STATUS, LOW);
    
    gas_sensor.status(GAS_LEVEL);

    lcd.setCursor(0,0);
    lcd.print("Gas: ");
    lcd.print(GAS_LEVEL);

    temp_sensor.status(TEMP_LEVEL);
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(TEMP_LEVEL);
    lcd.print("C");
    distance_sensor.status(DISTANCE_LEVEL);
  }
  else {
    digitalWrite(LED_DISABLE_STATUS, HIGH);

    digitalWrite(LED_TEMP_CRITICAL_STATUS,     LOW);
    digitalWrite(LED_TEMP_WARNING_STATUS,      LOW);
    digitalWrite(LED_GAS_CRITICAL_STATUS,      LOW);
    digitalWrite(LED_GAS_WARNING_STATUS,       LOW);
    digitalWrite(LED_DISTANCE_CRITICAL_STATUS, LOW);
    digitalWrite(LED_DISTANCE_WARNING_STATUS,  LOW);
  
    lcd.print("I am sleeping...");
    lcd.setCursor(0,1);
    lcd.print("__(^_^)__");

    Serial.println("I am sleeping... ^_^");
  }

  delay(250);
}


