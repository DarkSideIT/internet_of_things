import paho.mqtt.client as mqtt
import time
import serial

mqtt_broker_host = "broker.emqx.io"
mqtt_broker_port = 1883
mqtt_topic = "mytopic"

ser = serial.Serial("COM4", baudrate=9600, timeout=1)

def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    client.subscribe(mqtt_topic)

def on_message(client, userdata, msg):
    message = msg.payload.decode()
    print(f"Received message: {message}")
    ser.write(message.encode())

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(mqtt_broker_host, mqtt_broker_port, 60)

while True:
    client.loop_start()
    time.sleep(1)
