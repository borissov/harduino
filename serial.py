import serial #pyserial
import sys
import pprint



class ArduinoSerial:
    def send(self,write):
        ser = serial.Serial("COM12", 115200, timeout=0.2)
        ser.flush()
        ping = 'ping'
        ser.write(ping.encode())
        read = ser.read(1000).decode()
        read = read.replace("\r\n","")
        if read == 'ready':
            ser.write(write.encode())
            read = ser.read(1000).decode()
            read = read.replace("\r\n","")
        ser.close()
        return read







if __name__ == '__main__':
    arduino = ArduinoSerial()
    write = sys.argv[1]
    print(arduino.send(write)) 

