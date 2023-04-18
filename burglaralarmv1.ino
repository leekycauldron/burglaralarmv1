#include <PubSubClient.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"


void led(int pin = -1);
void alert_buzz();
bool getMotion();
void strobe_lamp();

const int red = 13;   
const int yellow = 12;
const int green = 11;
const int blue = 10;
int sensor = 9;
int buzzer = 8;

int status = 0; // 0 = disarmed, 1 = armed, 2, alert

         
int state = LOW; // Current sensor state.
int val = 0; // Saved sensor state.
unsigned long last = millis(); // Keeps track of time for strobing lamp during alert.

char ssid[] = SSID;     
char pass[] = PASS;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);


bool net = false;

void setup() {
  Serial.begin(115200);

  // Set pins
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT); 
  pinMode(green, OUTPUT); 
  pinMode(blue, OUTPUT); 

  pinMode(sensor, INPUT);    


  led(blue);

  // Network Setup
  WiFi.disconnect();
  delay(100);
  wifi();
  net = mqtt();
  
  
        
}

void loop(){
  


  switch(status){
    case 0:
      led(green);
      break;
    case 1:
      led(yellow);
      break;
    case 2:
      alert_buzz();
      strobe_lamp();
      led(red);
      break;
  }

  
  if (getMotion() && state == LOW) {           
      mqttClient.publish(TOPIC,"lamp_on");
      if(status == 1) {
        status = 2;
        mqttClient.publish(TOPIC,"2");
      }
      state = HIGH;      
  } else if (!getMotion() && state == HIGH){      
        mqttClient.publish(TOPIC,"lamp_off");
        if (status == 2) status = 1;
        state = LOW;       
  }

  // Network Check.
  net = mqttClient.connected();
  if (!net) {
    led(blue);
    if (!reMqtt()) wifi(); // Attempt MQTT reconnect, if failed attempt Wifi reconnect.
  }
    
  mqttClient.loop();
}