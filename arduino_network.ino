#include "arduino_secrets.h"

// Connects to Wifi (fails after ten attempts)
bool wifi() {
  WiFi.begin(SSID, PASS);
  Serial.print("Connecting to WiFi ");
  int cnt = 0;
  while (cnt < 10) {
    if (WiFi.status() == WL_CONNECTED){
      Serial.println("OK");
      return true;
    }
    Serial.print('.');
    cnt++;
    delay(1000);
  }
  Serial.println("ERR");
  return false;
}
// Connect to MQTT (first time).
bool mqtt() {
    mqttClient.setCallback(callback);
    mqttClient.setServer(BROKER,PORT);
    mqttClient.setKeepAlive(60);
    mqttClient.connect(ID,USER,PASSWORD);
    mqttClient.subscribe(TOPIC);
    delay(3000);
    if (mqttClient.connected()){
        Serial.println("MQTT Connected.");
        mqttClient.publish(TOPIC,"alarmUp");
        return true;
    } else {
        Serial.println("Cannot connect to MQTT"+ String(mqttClient.state()));
        return false;
    }
}

// Connect to MQTT (reconnect)
bool reMqtt() {
  mqttClient.connect(ID,USER,PASSWORD);
  if (mqttClient.connected()){
    Serial.println("MQTT connected; resubscribing...");
    mqttClient.subscribe(TOPIC);
    mqttClient.publish(TOPIC,"alarmUp");
    return true;
  }
  Serial.println("MQTT down resetting internet...");
  return false;
}

// Handle MQTT Messages.
void callback(char* topic, byte* payload, unsigned int length) {
  char tmp[60];
  if (length>60) length = 60;
  memcpy(tmp, payload, length);
  String tmpS = tmp;
  
  Serial.println(tmpS);

  if(isDigit(tmpS.charAt(0))) {
    if (status == 2 && tmpS.toInt() == 1) return;
    if (status == 2 && tmpS.toInt() == 0) mqttClient.publish(TOPIC,"lamp_on");;
    status = tmpS.toInt();
  }
  
} 