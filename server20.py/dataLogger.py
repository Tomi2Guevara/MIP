from orden import Orden
class dataLogger:

    def __init__(self, filename):
        self.filename = filename
        self.file = None
        self.file = open(self.filename, "w")
        self.file.write("")

        

    def add(self, orden):
        reporte = "----------------"+orden.getNombre()+"-----------------\n"
        reporte += "Hora de ejecucion: "+str(orden.getHora())+"\n"
        if orden.getEspecificaciones() is not None:                
            reporte += "Especificaciones: "+orden.getEspecificaciones()+"\n"
        #reporte += "Resultado: "+str(orden.getResultado())+"\n"
        #en resultado tengo que poner el resultado a veces hay espacios en blanco innecesarios
        #puedo eliminar cuando hayan dos \n seguidos
        resulado = orden.getResultado()
        resulado = resulado.split("\n")
        for i in range(len(resulado)):
            if resulado[i] == "":
                resulado.pop(i)
        for i in range(len(resulado)):
            reporte += resulado[i]+"\n"
         #elimino los \r 
        reporte = reporte.replace("\r","")

        reporte += "---------------------------------------------------------------\n\n"   
        self.file = open(self.filename, "a")
        self.file.write(reporte)
        self.file.close()

    def close(self):
        self.file.close()

'''------------CONECTAR ROBOT-----------------
Hora de ejecucion: 19:23:53
Especificaciones: Puerto: COM6
Baudrate: 115200
Resultado: INFO: ROBOT ONLINE
INFO: conexion exitosa
INFO: Robot conectado en el puerto COM6
------------------------------------------------'''

'''------------MOVIMIENTO LINEAL-ID admin-----------------
Hora de ejecucion: 15:59:36
Especificaciones: Posicion requerida: [80.0, 170.0, 120.0]
Resultado: INFO: LINEAR MOVE: [X:80.00 Y:170.00 Z:120.00 E:0.00] t=0.25s


------------------------------------------------'''
#quiero que se almacene asi:
'''------------MOVIMIENTO LINEAL-ID admin-----------------
Hora de ejecucion: 15:59:36
Especificaciones: Posicion requerida: [80.0, 170.0, 120.0]
Resultado: INFO: LINEAR MOVE: [X:80.00 Y:170.00 Z:120.00 E:0.00] t=0.25s
------------------------------------------------'''
#para esto tengo que modificar el metodo de log de la clase controlador
#los caracteres que se interpretan como saltos de linea son \n\r