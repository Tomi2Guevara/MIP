#creamos una clase para manejar el puerto serie
import serial
import time

class SerialPort:

    def __init__(self, port, baudrate):
        # Configura el puerto serie
        self.ser = serial.Serial(port, baudrate)  # Cambia 'COM3' al puerto correcto
        self.ser.flushInput() #borra el buffer de entrada
        self.ser.flushOutput() #borra el buffer de salida

        
    def read(self):
        data=""
        while True:
            if self.ser.in_waiting > 0:
                data += self.ser.readline().decode('utf-8')
            else:
                break
        return data

    def write(self, mensaje):
        self.ser.write(str(mensaje + '\r\n').encode('utf-8'))
        time.sleep(0.1)
        
    def close(self):
        self.ser.close()
