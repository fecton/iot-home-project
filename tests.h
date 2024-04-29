void testLED(const int LED) {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);

  Serial.write("LED is passed! ✅");
}

void testBuzzer(const int BUZZER) {
  pinMode(BUZZER, OUTPUT);
  tone(BUZZER, 100, 1000);

  Serial.write(BUZZER + " is passed! ✅");
}