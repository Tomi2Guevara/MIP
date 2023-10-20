from serial_port import SerialPort
import nunpy as np  
import time

class Controlador:
    def __init__(self):
        self.dimensiones = None
        self.velMax = []
        self.velAngularMax = []
        self.posMax = []
        self.posAngularMax = []
        self.estConect = False
        self.auto = None #true si es automatico, false si es manual
        self.posArticular = [0.0,0.0,0.0]
        self.posActuador = [0.0, 0.0, 0.0]
        self.SerialPort = None

        """SET methods"""
    
    def setEncendido(self, encendido):
        self.encendido = encendido
    def setModo(self, auto):
        self.auto = auto
    def setPosArticular(self, x, y, z, wx, wy, wz ):
        self.posArticular = [x, y, z, wx, wy, wz]
    def setPosActuador(self, x, y, z, wx, wy, wz ):
        self.posActuador = [x, y, z, wx, wy, wz]

        
    def conect(self, puerto, velocidad=115200):
        """
        Connects to a serial port with the specified port and baud rate.

        Args:
            puerto (str): The name of the serial port to connect to.
            velocidad (int, optional): The baud rate to use for the connection. Defaults to 115200.

        Returns:
            str: A message indicating whether the connection was successful or not.
        """
        try:
            self.SerialPort = SerialPort(puerto, velocidad)
        except:
            return ("Error al conectar")
        else:
            self.estConect = True
            return ("Conectado")
        
        
        
    def disconnect(self):
            """
            Disconnects the serial port and sets the estConect attribute to False.

            Returns:
            str: "Desconectado" if the disconnection was successful, "Error al desconectar" otherwise.
            """
            try:
                self.SerialPort.close()
            except:
                return ("Error al desconectar")
            else:
                self.estConect = False
                return ("Desconectado")
            

         
    # no hay analisis cinemático
    def movimientoLineal(self,vel,posFinal):
            """
            Moves the actuator linearly to a specified position.

            Args:
            vel (float): The velocity of the actuator.
            posFinal (float): The final position of the actuator.

            Returns:
            str: A message indicating whether the movement was successful or not.
            """
            try:            
                self.posActuador= posFinal
                return ("Movimiento Exitoso")
            except:
                return ("Error en el movimiento")
        

    

   

    


    



    



    

    