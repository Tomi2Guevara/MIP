#!/usr/bin/env python
# -*- coding: utf-8 -*-
from cmd import Cmd 

from rpc import XRServer

from controlador import Controlador

from orden import Orden

from report import Report

from dataLogger import dataLogger

import time

import os   

class ConsolaCLI(Cmd):
    elements = ['1', 2, 'TRES', 'Y EL RESTO']
    listaComandos = ["conectar","desconectar","motores on/off","modo auto/manual","homing","getPos","movLineal x y z vel","list","suma","exit","rpc true/false"]
    ErrorValidacion="ERROR: El robot esta siendo usado por otro cliente, debe esperar..."
    ErrorControl="ERROR: El servidor ha bloqueado el control del robot, comuniquese para mas informacion..."

    def __init__(self):
        Cmd.__init__(self)
        self.rpc_server = None
        self.controlador = Controlador()
        self.ordenes = []
        self.learnFile = None
        self.log = dataLogger("./log/log.txt")
        self.idAct="0000"
        self.idAdmin="0000"
        

    #debemos identificar cada usuario que se conecta al servidor
    #Cuando se conecta un usuario al servidor se le asigna un id

    
    def postcmd(self, stop, line):
        '''This method is called just after a command has been executed.'''
        print("")
        return stop

    def default(self, line):
        print("ERROR: comando no reconocido")    
            
    def do_exit(self, args):
        """"Desconecta de un dispositivo interno y sale del programa."""
        if self.controlador.estadoConexion==True: self.controlador.desconectar()
        self.do_rpc(False)
        raise SystemExit

    def do_rpc(self, value):
        """"Inicia/Para el servidor rpc según el valor dado (true/false)."""
        if value:
            if self.rpc_server is None:
                self.rpc_server = XRServer(self)  #este objeto inicia el servidor y se da a conocer 
                self.log.add(Orden("INICIO SERVIDOR RPC",time.strftime("%H:%M:%S"),"Servidor RPC iniciado en el puerto: "+str(self.rpc_server.server.server_address)))
        else:
            if self.rpc_server is not None:
                self.rpc_server.shutdown()
                self.rpc_server = None
                self.log.add(Orden("PARADA SERVIDOR RPC",time.strftime("%H:%M:%S"),"Servidor RPC detenido"))
        
    def do_listCom(self, arg1, arg2=None):
        """Muestra la lista de comandos disponibles."""
        respuesta = "\n\nDocumented commands (type help <topic>):\n==========================================================================\n"
        respuesta += "conectar      desconectar         motores on|off          modo auto|manual\n"
        respuesta += "getPos        homing              movLineal x y z vel     reporte\n"
        respuesta += "exit          rpc true|false      gripper on|off          aprendizaje on|off\n"
        respuesta += "ejecutarTray\n"          
        respuesta += "==========================================================================\n"
        if arg2 is not None:
            return (respuesta)
        else:
            print(respuesta)

    def do_conectar(self, arg1, ID=None):
        """Conecta el robot al puerto serie."""
        if ID is not None:
            if self.idAct=="0000":
                respuesta = self.controlador.conectar()
                self.log.add(Orden("CONECTAR ROBOT-ID "+str(ID),time.strftime("%H:%M:%S"),respuesta,"Puerto: COM6\nBaudrate: 115200"))
                if not("ERROR" in respuesta):
                    self.idAct=ID
            else: 
                respuesta = self.ErrorValidacion

            self.log.add(Orden("CONECTAR ROBOT-ID "+str(ID),time.strftime("%H:%M:%S"),respuesta,"Puerto: COM6\nBaudrate: 115200"))
            return (respuesta)
            
        else:
            respuesta = self.controlador.conectar()
            self.log.add(Orden("CONECTAR ROBOT-ID admin",time.strftime("%H:%M:%S"),respuesta,"Puerto: COM6\nBaudrate: 115200"))
            print(respuesta)

########################################################################            
    def do_getId(self,args):
        """Obtiene el id del cliente que esta usando el robot."""
        print(self.idAct)
    
    def getOrdenes(self):
        return self.ordenes
#######################################################################

    def do_desconectar(self, arg1, ID=None):
        """Desconecta el robot del puerto serie."""
        if ID is not None:
            if ID==self.idAct or self.idAct=="0000":
                respuesta = self.controlador.desconectar()
                self.log.add(Orden("DESCONECTAR ROBOT-ID "+str(ID),time.strftime("%H:%M:%S"),respuesta))
                if "ERROR" in respuesta:
                    return (respuesta)
                else:
                    self.idAct="0000"
                    return (respuesta)
            else: 
                respuesta = self.ErrorValidacion
                self.log.add(Orden("DESCONECTAR ROBOT-ID "+str(ID),time.strftime("%H:%M:%S"),respuesta))
                return (respuesta)
        else:
            respuesta = self.controlador.desconectar()
            self.log.add(Orden("DESCONECTAR ROBOT-ID admin",time.strftime("%H:%M:%S"),respuesta))
            print(respuesta)
    
    def do_motores(self, modo, ID=None):
        """Activa/Desactiva los motores del robot. Se usa motores on|off"""
        if ID is not None:
            if ID==self.idAct or self.idAct=="0000":
                if modo == "on":
                    respuesta = self.controlador.activarMotores()
                elif modo == "off":
                    respuesta = self.controlador.desactivarMotores()       
            else: 
                respuesta = self.ErrorValidacion

            self.log.add(Orden("MOTORES-ID "+str(ID),time.strftime("%H:%M:%S"),respuesta,"Modo: "+modo))
            return (respuesta)    
        else:
            if modo == "on" or modo == "off":
                if modo == "on":
                    respuesta = self.controlador.activarMotores()
                    
                elif modo == "off":
                    respuesta = self.controlador.desactivarMotores()
            
                self.log.add(Orden("MOTORES-ID admin",time.strftime("%H:%M:%S"),respuesta,"Modo: "+modo))
                print(respuesta)   
            else:
                print("ERROR: argumentos incorrectos")           

    def do_modo(self, modo, ID=None):
        """Cambia el modo de funcionamiento del robot. Se usa modo manual|auto"""
        if ID is not None:
            if ID==self.idAct or self.idAct=="0000":
                respuesta = self.controlador.cambiarModo(modo)
            else:
                respuesta = self.ErrorValidacion
            
            self.log.add(Orden("CAMBIAR MODO-ID "+str(ID),time.strftime("%H:%M:%S"),respuesta,"Modo: "+modo))
            return (respuesta)
       
        else:
            if modo == "manual" or modo == "auto":
                respuesta = self.controlador.cambiarModo(modo)
                self.log.add(Orden("CAMBIAR MODO-ID admin",time.strftime("%H:%M:%S"),respuesta,"Modo: "+modo))
                print(respuesta)
            else:
                print("ERROR: argumentos incorrectos")

    def do_getPos(self, arg1, ID=None):
        """Obtiene la posicion actual del del efector final."""
        if ID is not None:
            if ID==self.idAct or self.idAct=="0000":
                respuesta = self.controlador.getCurrentPosition()
            else:
                respuesta = self.ErrorValidacion 

            self.log.add(Orden("GET POSITION-ID "+str(ID),time.strftime("%H:%M:%S"),respuesta))
            return (respuesta)
        
        else:
            respuesta = self.controlador.getCurrentPosition()
            self.log.add(Orden("GET POSITION-ID admin",time.strftime("%H:%M:%S"),respuesta))
            print(respuesta)
        
   
    def do_homing(self, arg1, ID=None):
        """Realiza el homing y el robot vuelve a su posición de referencia."""
        if ID is not None:
            if ID==self.idAct or self.idAct=="0000":
                respuesta = self.controlador.homing()   
            else:
                respuesta = self.ErrorValidacion

            self.log.add(Orden("HOMING-ID "+str(ID),time.strftime("%H:%M:%S"),respuesta))
            return (respuesta)
        else:
            respuesta = self.controlador.homing()
            self.log.add(Orden("HOMING-ID admin",time.strftime("%H:%M:%S"),respuesta))
            print(respuesta)


    
    def do_movLineal(self, arg1, ID=None, x=None, y=None, z=None, vel=None ):
        """Realiza un movimiento lineal en el dispositivo. Se usa movLineal x y z vel"""
        
        if ID is not None:
            if ID==self.idAct or self.idAct=="0000":
                if vel is not None:
                    posFinal = [float(x),float(y),float(z)]
                    vel=float(vel)
                    respuesta = self.controlador.movimientoLineal(posFinal,vel)
                    self.log.add(Orden("MOVIMIENTO LINEAL-ID"+str(ID),time.strftime("%H:%M:%S"),respuesta,"Velocidad: "+str(vel)+" mm/s\nPosicion requerida: "+str(posFinal)))
                else:
                    posFinal = [float(x),float(y),float(z)]
                    respuesta = self.controlador.movimientoLineal(posFinal)
                    self.log.add(Orden("MOVIMIENTO LINEAL-ID"+str(ID),time.strftime("%H:%M:%S"),respuesta,"Posicion requerida: "+str(posFinal)))
                return (respuesta)
            else: 
                respuesta = self.ErrorValidacion
                self.log.add(Orden("MOVIMIENTO LINEAL-ID "+str(ID),time.strftime("%H:%M:%S"),respuesta))
                return (respuesta)
        else:
            #separo el argumento por espacios y los convierto a float
            lista = arg1.split()
            lista = [float(i) for i in lista]
            if len(lista) == 3:
                posFinal = lista 
                respuesta=self.controlador.movimientoLineal(posFinal)
                self.log.add(Orden("MOVIMIENTO LINEAL-ID admin",time.strftime("%H:%M:%S"),respuesta,"Posicion requerida: "+str(posFinal)))
                print(respuesta)
            elif len(lista) == 4:
                vel = lista[3]
                posFinal = lista[0:3] #desde el segundo elemento hasta el final
                respuesta=self.controlador.movimientoLineal(posFinal,vel)
                self.log.add(Orden("MOVIMIENTO LINEAL-ID admin",time.strftime("%H:%M:%S"),respuesta,"Velocidad: "+str(vel)+" mm/s\nPosicion requerida: "+str(posFinal)))
                print(respuesta)
            else:
                print("ERROR: argumentos incorrectos")

    #quiero que pueda pasar movLineal 100 10 20 30 o movLineal 100 10 20 30 40
    #en repo tengo hecha la funcion pero el problema se da en controlador.py

    def do_gripper(self, modo, ID=None):
        """Activa o desactiva el efector final. Se usa gripper on|off"""
        if ID is not None:
            if ID==self.idAct or self.idAct=="0000":
                if modo == "on":
                    respuesta = self.controlador.activarEfector()
                elif modo == "off":
                    respuesta = self.controlador.desactivarEfector()
            else:
                respuesta = self.ErrorValidacion 
            self.log.add(Orden("GRIPPER-ID"+str(ID),time.strftime("%H:%M:%S"),respuesta,"Modo: "+modo))
            return (respuesta)
        else:
            if modo == "on" or modo == "off":
                if modo == "on":
                    respuesta = self.controlador.activarEfector()              
                elif modo == "off":
                    respuesta = self.controlador.desactivarEfector()
                self.log.add(Orden("GRIPPER-ID admin",time.strftime("%H:%M:%S"),respuesta,"Modo: "+modo))
                print(respuesta)
            else:
                print("ERROR: argumentos incorrectos")

    
    def do_aprendizaje(self, modo, fileName=None, ID=None):
        """Activa o desactiva el modo aprendizaje. Se usa aprendizaje on|off"""
        if ID is not None:
            if ID==self.idAct or self.idAct=="0000":
                if modo == "on":
                    self.learnFile = fileName
                    respuesta = self.controlador.aprenderTrayectoria(True, str(self.learnFile))   
                elif modo == "off":
                    respuesta = self.controlador.aprenderTrayectoria(False, str(self.learnFile))    
            elif self.idAct=="admin":
                respuesta = self.ErrorControl         
            else:
                respuesta = self.ErrorValidacion
            self.log.add(Orden("APRENDIZAJE-ID"+str(ID),time.strftime("%H:%M:%S"),respuesta,"Modo: "+modo+"\nNombre del archivo: "+str(fileName)))
            return respuesta   
        else:
            if modo == "on" or modo == "off":
                if modo == "on":
                    print("Ingrese el nombre del archivo donde quiere guardar la trayectoria")
                    self.learnFile = input()
                    respuesta= (self.controlador.aprenderTrayectoria(True, self.learnFile))               
                elif modo == "off":
                    respuesta= (self.controlador.aprenderTrayectoria(False, self.learnFile)) 

                self.log.add(Orden("APRENDIZAJE-ID admin",time.strftime("%H:%M:%S"),respuesta,"Modo: "+modo+"\nNombre del archivo: "+str(fileName)))          
                print(respuesta)      
            else:
                print("ERROR: Argumentos incorrectos")

   
    def do_ejecutarTray(self, tray, ID=None):
        """Ejecuta una trayectoria aprendida."""
        
        if ID is not None:
            if ID==self.idAct or self.idAct=="0000":
                print(tray)
                tray="./trayectorias/"+tray
                respuesta = self.controlador.ejecutarTrayectoria(str(tray))
            else:
                respuesta = self.ErrorValidacion
            self.log.add(Orden("EJECUTAR TRAYECTORIA-ID"+str(ID),time.strftime("%H:%M:%S"),respuesta,"Nombre del archivo: "+str(tray)))
            return respuesta

        else:
            if self.controlador.getModo() == "Manual":
                respuesta="ERROR: el robot debe estar en modo automatico"
                self.log.add(Orden("EJECUTAR TRAYECTORIA-ID admin",time.strftime("%H:%M:%S"),respuesta,"Nombre del archivo: "+str(tray)))
                print(respuesta)
            else:
                print("Tryectorias disponibles:")
                for file in os.listdir("trayectorias"):
                    print(file)
                #pedimos el nombre del archivo y controlamos que exista
                print("Ingrese el nombre del archivo que desea ejecutar")
                file = input()
                file="./trayectorias/"+file
                if os.path.isfile(file):
                    respuesta = self.controlador.ejecutarTrayectoria(str(file))
                    self.log.add(Orden("EJECUTAR TRAYECTORIA-ID admin",time.strftime("%H:%M:%S"),respuesta,"Nombre del archivo: "+str(file)))
                    print(respuesta)
                else:
                    respuesta="ERROR: el archivo no existe"
                self.log.add(Orden("EJECUTAR TRAYECTORIA-ID admin",time.strftime("%H:%M:%S"),respuesta,"Nombre del archivo: "+str(file)))
                print(respuesta)  

    def do_reporte(self, arg1, arg2=None):
        """Genera un reporte del estado actual del robot y las ordenes realizadas por el cliente."""
        reporte = Report()
        if arg2 is not None:
            return (reporte.crearReporte(self.controlador))
        else:
            print(reporte.crearReporte(self.controlador))  

    def do_listTray(self, arg1, ID=None):
        """Lista las trayectorias disponibles en directroio trayectorias."""
        if ID is not None:
            respuesta="Trayectorias disponibles:\n"
            for file in os.listdir("trayectorias"):
                respuesta += file+"\n"
            print(respuesta)
            return respuesta     

    def do_cerrarCliente(self, arg1, ID=None):
        """Libera el control del robot para otro cliente."""
        if ID is not None:
            if ID==self.idAct or self.idAct=="0000":
                self.idAct="0000"
                respuesta="INFO: Control liberado"
            else:
                respuesta = self.ErrorValidacion
            self.log.add(Orden("DESCONEXION CLIENTE-ID"+str(ID),time.strftime("%H:%M:%S"),respuesta))
            return respuesta
        else:
            #reseteo el ID
            self.idAct="0000"
            respuesta="INFO: Control liberado"
            self.log.add(Orden("DESCONEXION CLIENTE-ID admin",time.strftime("%H:%M:%S"),respuesta))
            print(respuesta)
    
    def do_freeControl(self, args):
        """Libera el control del robot para otro cliente."""
        self.idAct="0000"
        respuesta="INFO: Control liberado"
        self.log.add(Orden("DESCONEXION CLIENTE-ID admin",time.strftime("%H:%M:%S"),respuesta))
        print(respuesta)

    def do_block(self, args):
        """Bloquea el robot para otros clientes."""
        self.idAct="admin"
        respuesta="INFO: Control bloqueado"
        self.log.add(Orden("BLOQUEO ROBOT-ID admin",time.strftime("%H:%M:%S"),respuesta))
        print(respuesta)
            

    
    #al llamar a esta funcion se debe hacer de esta manera: suma 1 2 pero no suma(1,2) ni suma(1,2,3)
    #porque el interprete de comandos no lo va a reconocer

    # def do_connect(self):

    # def help_connect(self):

    # def do_disconnect(self):

    # def help_disconnect(self):

