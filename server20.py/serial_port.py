#creamos una clase para manejar el puerto serie
try:
    import serial
except ImportError:
    raise "El módulo serial no está instalado. Por favor, instale el módulo para continuar."
    
import time

class SerialPort:

    def __init__(self, port, baudrate):
        """
        Initializes the SerialPort object and opens the serial connection.

        Args:
        port (str): The name of the serial port to connect to.
        baudrate (int): The baud rate of the serial connection.
        """
            
        # Configura el puerto serie
        self.ser = serial.Serial(port, baudrate)  #se crea el objeto serie de pyserial 
        self.ser.flushInput() #borra el buffer de entrada
        self.ser.flushOutput() #borra el buffer de salida

        
    def read(self, lineas=0):
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
                        #si lineas==0 guarda hasta que no haya mas datos en el data
                        #si lineas==n guarda n lineas en data
                        if lineas!=0:
                            if data.count("\n")<lineas:
                                data += self.ser.readline().decode('utf-8')
                                # si hay dos \n\n elimina el ultimo
                                if data.count("\n")>lineas:
                                    data=data[:data.rfind("\n")]
                            else:
                                self.ser.flushInput() #borra el buffer de entrada
                                break
                        else:
                             data += self.ser.readline().decode('utf-8')
                    else:
                        break
                return data
            except Exception as e:
                return"ERROR: no se pudo leer el puerto serie:" + str(e)
                
            

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
                return "ERROR: no se pudo escribir en el puerto serie:" + str(e)
        
    def close(self):
            """
            Closes the serial port connection.

            Raises:
                Exception: If there is an error while closing the serial port.
            """
            try:
                self.ser.close()
            except Exception as e:
                return "ERROR: al cerrar el puerto serie:" + str(e)
    
'''   def initialize(self):
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
'''               
