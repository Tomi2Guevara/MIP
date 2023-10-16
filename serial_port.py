#creamos una clase para manejar el puerto serie
try:
    import serial
except ImportError:
    print("El módulo serial no está instalado. Por favor, instale el módulo para continuar.")
    exit()
import time

class SerialPort:

    def __init__(self, port, baudrate):
        try:
            # Configura el puerto serie
            self.ser = serial.Serial(port, baudrate)  # Cambia 'COM3' al puerto correcto
            self.ser.flushInput() #borra el buffer de entrada
            self.ser.flushOutput() #borra el buffer de salida
        except Exception as e:
            print("Error al abrir el puerto serie:", e)
            exit() #sale del programa (opcional)
        else:
            print("Puerto serie abierto correctamente")
    
    def initialize(self):
        try:
            gcode = 'G28'#para configurar el robot en su posicion inicial
            self.ser.write(gcode.encode())
        except Exception as e:
            print("Error al inicializar el robot:", e)
            exit() #sale del programa (opcional)
        
        
        
    def read(self):
        try:
            data=""
            while True:
                if self.ser.in_waiting > 0:
                    data += self.ser.readline().decode('utf-8')
                else:
                    break
            return data
        except Exception as e:
            print("Error al leer el puerto serie:", e)
            

    def write(self, mensaje):
        try:
            self.ser.write(str(mensaje + '\r\n').encode('utf-8'))
            time.sleep(0.1)
        except Exception as e:
            print("Error al escribir en el puerto serie:", e)
        
    def close(self):
        try:
            self.ser.close()
        except Exception as e:
            print("Error al cerrar el puerto serie:", e)

