from opcua import Client
import time

url = "opc.tcp://192.168.1.153:4840"

client = Client(url)

client.connect()

print ("Client connected")

while True:
	Temp = client.get_node("ns=2;i=2")
	temperature = Temp.get_value()

	Press = client.get_node("ns=2;i=3")
	pressure = Press.get_value()

	TIME = client.get_node("ns=2;i=4")
	Time_val = TIME.get_value()

	print("client: ", temperature, pressure, Time_val)


	time.sleep(2)