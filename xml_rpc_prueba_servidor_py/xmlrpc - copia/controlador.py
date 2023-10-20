from execpciones import ModoInvalido
from serial_port import SerialPort
import time

class Controlador:
    
    def __init__(self):
        self.modo = "Manual"
        self.auto = False
        self.estado = ""
        self.serial = None
         
    def connect(self):
        self.serial = SerialPort("COM6", 115200)
        time.sleep(2)
        data=self.serial.read()
        data+="INFO: Succesful conection\n"
        self.estado="conectado"
        return data

    def disconnect(self):
        self.serial.close()
        return ("INFO: conection finished")

    def setModo(self, modo):
        #cambia el modo de funcionamiento
        self.modo = modo
    
    def homing(self):
        self.serial.write("G28")
        respuesta=self.serial.read()
        return respuesta
   
        
    def setAuto(self,modo):
        if modo=="on":
            self.auto=True
            return ("Modo automatico activado")
        elif modo=="off":
            self.auto=False
            return ("Modo automatico desactivado")
        
        
            

