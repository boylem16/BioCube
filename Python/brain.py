import serial
import time

ser = 0;
ser1 = 0;
time.sleep(10)

def debugSerial():
	global ser
	global ser1;
	try:
		ser = serial.Serial("/dev/ttyACM0", 9600)
		#print("ser = 0")
	except:
		try:
			ser = serial.Serial("/dev/ttyACM1", 9600)
			#print("ser = 1")
		except:
			ser = serial.Serial("/dev/ttyACM2",9600)
			#print("ser = 2")

	try:
		ser1 = serial.Serial("/dev/ttyACM3", 9600)
		#print("ser2 = 3")
	except:
		try:
			ser1 = serial.Serial("/dev/ttyACM2", 9600)
			#print("ser2 = 2")
		except:
			ser1 = serial.Serial("/dev/ttyACM1",9600)
			#print("ser2 = 1")
debugSerial()
		
    #From serial library - serial.Serial(Port, frequency/baud)

class Sensor:
    def __init__ (self, name):
        self.name = name;
        self.value = 0;
        self.array = [0] * 5;
        self.averageVal = 0;
    def addValue(self, number):
        self.value = number
        self.arrayValue()
        
    def arrayValue(self):
        self.array.pop(0)
        self.array.append(self.value)

    def average(self):
        total = 0;
        for x in self.array:
            total += x;
        self.averageVal = total / len(self.array);
        self.averageVal = float(self.averageVal)
        return float("%.3f" % self.averageVal)

    def stats(self):
        return  self.name+":"+" "+str(self.value)

    

 # Use numbers, ascii does not transfer properly, untegers work, hex would be needed for ascii

 # Temperature - tell arduino to get temperature info
def getData(command):

    #command = convertToHex(command)
    #print(command)
    
    ser.write(command)
    temp = ser.readline()
    #print(temp)

     # (convert to ((float ( convert from hex to int )) / 10)  temperature in celcius
    #temp = float(int(temp,16))/10 
    return float(temp)

def convertToHex(string):
    converted = ''
    for c in string:
        converted += hex(ord(c))
    return converted

def invert(num, minRange, maxRange):
    return -(num + minRange - maxRange)

 # Sensor Objects
temperature = Sensor("Temperature");
moisture = Sensor("Moisture");

pressure = Sensor("Pressure");

#time.sleep(20)
#serial.write("Startup")

 # Read from pi input buffer - Get temperature value in hex, number is multiplied by 10 to keep accuracy
while(1):
    #ser2.write("temperature")

    try:
        temp = float(getData('temperature'))/10
        temperature.addValue((temp* 9 / 5) + 32)
    except ValueError as err:
        print(err)

    #print temperature.stats()
    #ser2.write(str(temperature.value))
    #time.sleep(1)
    #ser2.write("pressure")

    try:
        pressure.addValue(getData('pressure'))
    except ValueError as err:
        print(err)

    #print pressure.stats()
    #ser2.write(str(pressure.averageVal))
    #time.sleep(1)
    #ser2.write("moisture")
    
    try:
	
        moisture.addValue( invert (getData('moisture')/10.0,0,100) )
    except ValueError as err:
        print(err)
 
   #print moisture.stats()
    #ser2.write(str(moisture.averageVal))
    #time.sleep(1)
# (convert to ((float ( convert from hex to int )) / 10)  temperature in celcius
#temp = float(int(temp,16))/10



#Display temperature
