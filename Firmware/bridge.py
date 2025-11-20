
#THIS IS THE BRIDGE SCRIPTS THAT CONNECT THE PROTEUS VIA VSPD I USED com0com BUT YOU CAN USE ANYONE YOU ARE WANT
#THIS BRIDGE SCRIPTS RECEIVE LIVE DATA AND UNDER MQTT PUBLISH TO environment/data TOPIC
#YOU REQUIRE TO INSTALL PAHO-MQTT AND SERIAL DEPENCE LIBARIES
import serial
import json
import paho.mqtt.client as mqtt


# Define the serial port you used in  Virtual serial port drive and baudRate

serial_port = "COM4"
baud_rate = 9600


# Setup Mqtt broker and topic

mqtt_broker = "localhost"
mqtt_port = 1883
mqtt_topic = "environment/data"

# initialize serial connection & MQTT Client Connection set protocol to MQTTV311 the most common stable and easy to use MQTT Protocol

ser = serial.Serial(serial_port, baud_rate)
mqttc = mqtt.Client(protocol=mqtt.MQTTv311)
mqttc.connect(mqtt_broker, mqtt_port)

print("Bridge now is running: serial --> MQTT")

#Create the loop that will always Publishes data  and handle exception if occurs
while True:
    try:
        line = ser.readline().decode().strip()
        if line:
            data = json.loads(line)
            print("Received:", line)
            print("Sending to Node-red......")
            mqttc.publish(mqtt_topic, json.dumps(data))

    except Exception as e:
        print("Error: ", e)

