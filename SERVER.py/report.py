
class Report:

    def __init__(self):
        pass
    
    def crearReporte(self, controlador):
        reporte = "--------------------------------------------------\n"
        reporte += "----------ESTADO ACTUAL DE LA ACTIVIDAD------------\n"
        reporte += "--------------------------------------------------\n\n"
        reporte += "Estado de la conexión: " + controlador.getEstadoConexion() + "\n"
        reporte += "Estado de los motores: " + controlador.getEstadoMotores() + "\n"
        reporte += "Posicion del efector final: " + controlador.getPosEfector() + "\n"
        reporte += "Fecha de conexion: " + str(controlador.getFechaConexion()) + "\n"
        reporte += "Hora de conexion: " + str(controlador.getHoraConexion()) + "\n\n"
        reporte += "--------------------------------------------------------------\n\n"
        
        reporte += "--------------------------------------------------\n"
        reporte += "-----------LISTA DE ORDENES EJECUTADAS------------\n"
        reporte += "--------------------------------------------------\n\n"
        #cargo lo que esta en el archivo de log.txt
        with open("./log/log.txt", "r") as archivo:
            for linea in archivo:
                reporte += linea
        return reporte
      
        #------------Nombre de la orden-----------------
        # Hora de ejecucion: 12:00:00
        # especificaciones: especificaciones
        # Resultado: INFO: Conexion exitosa
        # Info: Robot conectado en el puerto COM6
        #------------------------------------------------
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
# para esto tengo que modificar el metodo de log de la clase controlador