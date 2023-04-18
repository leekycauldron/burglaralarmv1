import paho.mqtt.client as mqtt
from phue import Bridge

# Connect to Bridge here
b = Bridge('192.168.1.191')
b.connect()

# Also add regular MQTT code, code available at https://www.cloudmqtt.com/docs/python.html/

# Code that listens to lamp and alarm messages
def on_message(client, obj, msg):
  ...
  elif temp == "lamp":
      if b.get_light(5,'on'):
          b.set_light(5,'on',False)
          mqttc.publish("cc","lampOff")
      else:
          b.set_light(5,'on',True)
          mqttc.publish("cc","lampOn")
  elif temp == "lamp_on":
      b.set_light(5,'on',True)
      mqttc.publish("cc","lampOn")
  elif temp == "lamp_off":
      b.set_light(5,'on',False)
      mqttc.publish("cc","lampOff")
  elif temp == "2":
      webhook = DiscordWebhook(url=HOOK_URL,content="<@424297184822034444> Library Intruder!")
      webhook.execute()
