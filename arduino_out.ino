// Control which LED turns on, default to none.
void led(int pin = -1) {

  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);

  switch (pin) {
    case red:
      digitalWrite(red, HIGH);
      break;
    case yellow:
      digitalWrite(yellow, HIGH);
      break;
    case green:
      digitalWrite(green, HIGH);
      break;
    case blue:
      digitalWrite(blue, HIGH);
      break;
  }
}

// Play alert noise on buzzer
void alert_buzz() {
    int valley = 1500;
    int peak = 3000;
    for (int i = valley; i < peak; i += 100) {
      tone(buzzer, i);
      delay(10);
    }
    for (int i = peak; i >= valley; i -= 100) {
      tone(buzzer, i);
      delay(10);
    }

  noTone(buzzer);
}


// Checks if motion or not
bool getMotion() {
  return digitalRead(sensor) == HIGH;
}

// Strobe the lamp every 500ms.

void strobe_lamp() {
  if(millis() - last >= 1000) {
    last = millis();
    mqttClient.publish(TOPIC,"lamp");
  }
}