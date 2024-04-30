class LED_Status {
  public:
    void static turn_off_all(int LED_YELLOW, int LED_RED, int BUZZER) {
      digitalWrite(LED_YELLOW, LOW);
      digitalWrite(LED_RED, LOW);
    }

    void static turn_on_red_and_buzzer(int LED_YELLOW, int LED_RED, int BUZZER) {
      digitalWrite(LED_YELLOW, LOW);
      digitalWrite(LED_RED, HIGH);
      tone(BUZZER, 100, 1000);
    }

    void static turn_on_yellow(int LED_YELLOW, int LED_RED, int BUZZER) {
      digitalWrite(LED_YELLOW, HIGH);
      digitalWrite(LED_RED, LOW);
    }
};


class Base_Sensor {
  public:
    int LED_WARNING_STATUS;
    int LED_CRITICAL_STATUS;
    int BUZZER_CRITICAL_OVERALL;

    int WARNING_THRESHOLD;
    int CRITICAL_THRESHOLD;

    String SENSOR_NAME;

    Base_Sensor(int led_warning, int led_critical, int buzzer_critical, int warning_treshold, int critical_threshold, String sensor_name) {
      LED_WARNING_STATUS = led_warning;
      LED_CRITICAL_STATUS = led_critical;
      BUZZER_CRITICAL_OVERALL = buzzer_critical;

      WARNING_THRESHOLD = warning_treshold;
      CRITICAL_THRESHOLD = critical_threshold;

      SENSOR_NAME = sensor_name;
    }

    void status(int sensor_value) {
      if(isAboveCriticalTreshold(sensor_value)) {
        LED_Status::turn_on_red_and_buzzer(LED_WARNING_STATUS, LED_CRITICAL_STATUS, BUZZER_CRITICAL_OVERALL);
        Serial.print(SENSOR_NAME);
        Serial.print(": 🔴 ");
      }
      else {
        if (isAboveWarningThreshold(sensor_value)) {
          LED_Status::turn_on_yellow(LED_WARNING_STATUS, LED_CRITICAL_STATUS, BUZZER_CRITICAL_OVERALL);
          Serial.print(SENSOR_NAME);
          Serial.print(": 🟡 ");
        }
        else {
          LED_Status::turn_off_all(LED_WARNING_STATUS, LED_CRITICAL_STATUS, BUZZER_CRITICAL_OVERALL);
          Serial.print(SENSOR_NAME);
          Serial.print(": 🟢 ");
        }
      }

      Serial.print("(");
      Serial.print(sensor_value);
      Serial.println(")");
    }

  private:
    bool isAboveCriticalTreshold(int sensor_value) {
      return sensor_value > CRITICAL_THRESHOLD;
    }

    bool isAboveWarningThreshold(int sensor_value) {
      return sensor_value > WARNING_THRESHOLD;
    }

};