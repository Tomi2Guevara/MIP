
#la idea es registrar cada peticion que se hace al servior
#y luego poder hacer un reporte de las peticiones realizadas
#Armar un log con las peticiones realizadas
#y la cantidad que han sido realizadas
class Orden:
    def __init__(self, nombre, hora, resultado, especificaciones = None):
        self.nombre = nombre
        self.hora = hora
        self.especificaciones = especificaciones
        self.resultado = resultado

    def getNombre(self):
        return self.nombre
    def getHora(self):
        return self.hora
    def getEspecificaciones(self):
        return self.especificaciones
    def getResultado(self):
        return self.resultado
        
    