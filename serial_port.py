#creamos una clase para manejar el puerto serie
try:
    import serial
except ImportError:
    raise "El módulo serial no está instalado. Por favor, instale el módulo para continuar."
    
import time

class SerialPort:

    class SerialPort:
       

        def __init__(self, port, baudrate):
            """
            Initializes the SerialPort object and opens the serial connection.

            Args:
            port (str): The name of the serial port to connect to.
            baudrate (int): The baud rate of the serial connection.
            """
            self.port = port
            self.baudrate = baudrate
            try:
                # Configura el puerto serie
                self.ser = serial.Serial(port, baudrate)  # Cambia 'COM3' al puerto correcto
                self.ser.flushInput() #borra el buffer de entrada
                self.ser.flushOutput() #borra el buffer de salida
            except Exception as e:
                return"Error al abrir el puerto serie:" + str(e)
                exit() #sale del programa (opcional)
            else:
                return"Puerto serie abierto correctamente"
    
    def initialize(self):
            """
            Initializes the robot by sending a G28 command to configure it in its initial position.

            Raises:
                Exception: An error occurred while initializing the robot.
            """
            try:
                gcode = 'G28'
                self.ser.write(gcode.encode())
            except Exception as e:
                return "Error al inicializar el robot:" + str(e)
                
        
        
        
    def read(self):
            """
            Reads data from the serial port and returns it as a string.

            Returns:
            data (str): The data read from the serial port.
            
            Raises:
            Exception: If there was an error while reading from the serial port.
            """
            try:
                data=""
                while True:
                    if self.ser.in_waiting > 0:
                        data += self.ser.readline().decode('utf-8')
                    else:
                        break
                return data
            except Exception as e:
                return"Error al leer el puerto serie:" + str(e)
                
            

    def write(self, mensaje):
            """
            Writes a message to the serial port.

            Args:
                mensaje (str): The message to be written to the serial port.

            Returns:
                None
            """
            try:
                self.ser.write(str(mensaje + '\r\n').encode('utf-8'))
                time.sleep(0.1)
            except Exception as e:
                return "Error al escribir en el puerto serie:" + str(e)
        
    def close(self):
            """
            Closes the serial port connection.

            Raises:
                Exception: If there is an error while closing the serial port.
            """
            try:
                self.ser.close()
            except Exception as e:
                return "Error al cerrar el puerto serie:" + str(e)

