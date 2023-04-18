# ⚠️!! READ FIRST !! ⚠️
<hr><br>
## Project: burglaralarmv1
Code and 3D models for the Arduino Burglar Alarm

<hr>

This repo has two branches:

1. main - this code is the simple no-wifi version which simply plays a buzzer alarm when motion is detected.
2. net - this code is the original, more advanced version which connects to MQTT and Phillips Hue to allow remote arming/disarming and lamp strobing on alert.



## Main files
- burglaralarmv1.ino - main code that will run
- arduino_out.ino - code with functions that will control the external components (sensor, LED, buzzer)


## net files

- burglaralarmv1.ino - main code that will run
- arduino_out.ino - code with functions that will control the external components (sensor, LED, buzzer)
- arduino_network.ino - code that connects to WiFi/MQTT
- arduino_secrets.h - a template file for storing credentials required for MQTT and WiFi
- main.py - a code snippet of my server that acts as a middleman between the Arduino and the Phillips Hue light
