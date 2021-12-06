import serial

PORT = "/dev/ttyACM1"

dev = serial.Serial(PORT, 9600)

dev.write(b"?")
result = dev.readline()

print(result)
