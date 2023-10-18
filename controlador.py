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
    def conect(self, puerto, velocidad = 115200):
        try:
            self.SerialPort = SerialPort(puerto, velocidad)
        except:
            return ("Error al conectar")
        else:
            self.estConect = True
            return ("Conectado")
    def disconnect(self):
        try:
            self.SerialPort.close()
        except:
            return ("Error al desconectar")
        else:
            self.estConect = False
            return ("Desconectado")    
    # no hay analisis cinemático
    def movimientoLineal(self,vel,posFinal):
        try:            
            self.posActuador= posFinal
            return ("Movimiento Exitoso")
        except:
            return ("Error en el movimiento")
        

    

   

    


    



    



    

    