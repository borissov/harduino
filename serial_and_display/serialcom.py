import serial #pyserial
import sys
import pprint
import subprocess  



class ArduinoSerial:
    def send(self,write):
        ser = serial.Serial("/dev/ttyACM0", 115200, timeout=0.2)
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
    write = sys.argv[1][:32]
    arduino.send(write)
    #info=subprocess.check_output(["cat /proc/cpuinfo"])  
    #print(info.split('@')[1].split(' ')[1])

