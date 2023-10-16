class Controlador:
    def __init__(self):
        self.tipo = None # no se para que es esto
        self.efector_final = None # no se para que es esto
        self.dimensiones = None
        self.velMax = None
        self.velAngularMax = None
        self.posMax = []
        self.posAngularMax = []
        self.encendido = False
        self.auto = None #true si es automatico, false si es manual
        self.posArticular = []
        self.posActuador = []
        self.SerialPort = None
    def setDimensiones(self, anchura, altura, profundidad):
        self.dimensiones = [anchura, altura, profundidad]
    def setVelMax(self, velMax):
        self.velMax = velMax
    def setVelAngularMax(self, velAngularMax):
        self.velAngularMax = velAngularMax
    def setPosMax(self, x, y, z):
        self.posMax = [x, y, z]
    def setPosAngularMax(self, wx, wy, wz):
        self.posAngularMax = [wx, wy, wz]
    def setEncendido(self, encendido):
        self.encendido = encendido
    def setModo(self, auto):
        self.auto = auto
    def setPosArticular(self, x, y, z, wx, wy, wz ):
        self.posArticular = [x, y, z, wx, wy, wz]
    def setPosActuador(self, x, y, z, wx, wy, wz ):
        self.posActuador = [x, y, z, wx, wy, wz]
    def setSerialPort(self, SerialPort):
        self.SerialPort = SerialPort
    def getDimensiones(self):
        return self.dimensiones
    def getVelMax(self):
        return self.velMax
    def getVelAngularMax(self):
        return self.velAngularMax
    def getPosMax(self):
        return self.posMax
    def getPosAngularMax(self):
        return self.posAngularMax
    def getEncendido(self):
        return self.encendido
    def getModo(self):
        return self.auto
    def getPosArticular(self):
        return self.posArticular
    def getPosActuador(self):
        return self.posActuador
    def getSerialPort(self):
        return self.SerialPort


    




    