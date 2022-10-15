
from opcua import Server
from random import randint
import datetime
import time

server = Server()

url = "opc.tcp://192.168.1.153:4840"
server.set_endpoint(url)

name = "OPCUA_SIMULATION_SERVER"
addspace = server.register_namespace(name)

node = server.get_objects_node()

param = node.add_object(addspace, "Parameters")

temp = param.add_variable(addspace, "Temperature", 0)
press = param.add_variable(addspace, "Rpessure", 0)
Time = param.add_variable(addspace, "Time", 0)

temp.set_writable()
press.set_writable()
Time.set_writable()

server.start()
print("server started at {}".format(url))

while True:
	temperature = randint(10, 50)
	pressure = randint(200, 999)
	TIME = datetime.datetime.now()

	print(temperature, pressure, TIME)

	temp.set_value(temperature)
	press.set_value(pressure)
	Time.set_value(TIME)

	time.sleep(2)
