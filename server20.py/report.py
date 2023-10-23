
class Report:

    def __init__(self):
        pass
    
    def crearReporte(self, controlador, listaOrdenes):
        reporte = "Reporte de estado del robot:\n"
        reporte += "Estado de la conexión: " + controlador.getEstadoConexion() + "\n"
        reporte += "Estado de los motores: " + controlador.getEstadoMotores() + "\n"
        reporte += "Posicion del efector final: " + controlador.getPosEfector() + "\n"
        reporte += "Fecha de conexion: " + str(controlador.getFechaConexion()) + "\n"
        reporte += "Hora de conexion: " + str(controlador.getHoraConexion()) + "\n\n"
        
        for orden in listaOrdenes:
            reporte += "------------"+orden.getNombre()+"-----------------\n"
            reporte += "Hora de ejecucion: "+str(orden.getHora())+"\n"
            if orden.getEspecificaciones() is not None:
                reporte += "Especificaciones: "+orden.getEspecificaciones()+"\n"
            reporte += "Resultado: "+str(orden.getResultado())+"\n"
            reporte += "------------------------------------------------\n\n"
 
        return reporte
      
        #------------Nombre de la orden-----------------
        # Hora de ejecucion: 12:00:00
        # especificaciones: especificaciones
        # Resultado: INFO: Conexion exitosa
        # Info: Robot conectado en el puerto COM6
        #------------------------------------------------

