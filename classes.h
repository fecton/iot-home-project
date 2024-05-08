#include "DHT.h"

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

    int SENSOR_INPUT;

    explicit Base_Sensor(
      int led_warning, int led_critical, int buzzer_critical,
      int warning_treshold, int critical_threshold, String sensor_name
    ) 
    {
      LED_WARNING_STATUS = led_warning;
      LED_CRITICAL_STATUS = led_critical;
      BUZZER_CRITICAL_OVERALL = buzzer_critical;

      WARNING_THRESHOLD = warning_treshold;
      CRITICAL_THRESHOLD = critical_threshold;

      SENSOR_NAME = sensor_name;
    }

    void status(int sensor_value) {
      Serial.print(SENSOR_NAME);
      if(isAboveCriticalTreshold(sensor_value)) {
        LED_Status::turn_on_red_and_buzzer(LED_WARNING_STATUS, LED_CRITICAL_STATUS, BUZZER_CRITICAL_OVERALL);
        Serial.print(": 🔴 ");
      }
      else {
        if (isAboveWarningThreshold(sensor_value)) {
          LED_Status::turn_on_yellow(LED_WARNING_STATUS, LED_CRITICAL_STATUS, BUZZER_CRITICAL_OVERALL);
          Serial.print(": 🟡 ");
        }
        else {
          LED_Status::turn_off_all(LED_WARNING_STATUS, LED_CRITICAL_STATUS, BUZZER_CRITICAL_OVERALL);
          Serial.print(": 🟢 ");
        }
      }

      Serial.print("(");
      Serial.print(sensor_value);
      Serial.println(")");
    }

  private:
    bool isAboveCriticalTreshold(int sensor_value) {
      return sensor_value >= CRITICAL_THRESHOLD;
    }

    bool isAboveWarningThreshold(int sensor_value) {
      return sensor_value >= WARNING_THRESHOLD;
    }
};

class Temp_Sensor {
  public:
    float static readTemperature(int sensor_input) {
      DHT dht22(sensor_input, DHT22);
      dht22.begin();
      return dht22.readTemperature();
    }

    float static readHumidity(int sensor_input) {
      DHT dht22(sensor_input, DHT22);
      dht22.begin();
      return dht22.readHumidity();
    }

};

class Distance_Sensor {
  public:
    int static readDistance(int trig_input, int echo_input) {
      int distance, duration;

      digitalWrite(trig_input, LOW); 
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trig_input, HIGH); 
      delayMicroseconds(10);
      digitalWrite(trig_input, LOW);
      duration = pulseIn(echo_input, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
      distance= duration*0.034/2;

      return distance;
    }
};
