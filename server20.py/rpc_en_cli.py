#!/usr/bin/env python
# -*- coding: utf-8 -*-
from cmd import Cmd 

from rpc import XRServer

from controlador import Controlador

from orden import Orden

from report import Report

import time

import os   

class ConsolaCLI(Cmd):
    elements = ['1', 2, 'TRES', 'Y EL RESTO']
    listaComandos = ["conectar","desconectar","motores on/off","modo auto/manual","homing","getPos","movLineal vel x y z","list","suma","exit","rpc true/false"]
    
    def __init__(self):
        Cmd.__init__(self)
        self.rpc_server = None
        self.controlador = Controlador()
        self.ordenes = []
        self.learnFile = None

    def getOrdenes(self):
        return self.ordenes
    
    def postcmd(self, stop, line):
        '''This method is called just after a command has been executed.'''
        print("")
        return stop

    def default(self, line):
        print("ERROR: comando no reconocido")    

    def do_listCom(self, arg1, arg2=None):
        """Muestra la lista de comandos disponibles."""
        respuesta = "\n\nDocumented commands (type help <topic>):\n==========================================================================\n"
        respuesta += "conectar      desconectar         motores on|off          modo auto|manual\n"
        respuesta += "homing        getPos              movLineal vel x y z     reporte\n"
        respuesta += "exit          rpc true|false      gripper on|off\n"          
        respuesta += "==========================================================================\n"
        if arg2 is not None:
            return (respuesta)
        else:
            print(respuesta)
            
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
        else:
            if self.rpc_server is not None:
                self.rpc_server.shutdown()
                self.rpc_server = None
    
        
    def do_reporte(self, arg1, arg2=None):
        """Genera un reporte del estado actual del robot y las ordenes realizadas por el cliente."""
        reporte = Report()
        if arg2 is not None:
            return (reporte.crearReporte(self.controlador,self.ordenes))
        else:
            print(reporte.crearReporte(self.controlador,self.ordenes))  

    def do_conectar(self, arg1, arg2=None):
        """Conecta el robot al puerto serie."""
        if arg2 is not None:
            respuesta = self.controlador.conectar()
            self.ordenes.append(Orden("CONECTAR",time.strftime("%H:%M:%S"),respuesta,"Puerto: COM6\nBaudrate: 115200"))
            return (respuesta)
        else:
            print(self.controlador.conectar())
    

    def do_desconectar(self, arg1, arg2=None):
        """Desconecta el robot del puerto serie."""
        if arg2 is not None:
            respuesta = self.controlador.desconectar()
            self.ordenes.append(Orden("DESCONECTAR",time.strftime("%H:%M:%S"),respuesta))
            return (respuesta)
        else:
            print(self.controlador.desconectar())
    
    def do_motores(self, modo, arg2=None):
        """Activa/Desactiva los motores del robot. Se usa motores on|off"""
        if arg2 is not None:
            if modo == "on":
                respuesta = self.controlador.activarMotores()
                self.ordenes.append(Orden("MOTORES",time.strftime("%H:%M:%S"),respuesta,"Modo: "+modo))
                return (respuesta)
            elif modo == "off":
                respuesta = self.controlador.desactivarMotores()
                self.ordenes.append(Orden("MOTORES",time.strftime("%H:%M:%S"),respuesta,"Modo: "+modo))
                return (respuesta)           
        else:
            if modo == "on":
                print(self.controlador.activarMotores())
            elif modo == "off":
                print(self.controlador.desactivarMotores())
            else:
                print("ERROR: argumentos incorrectos")
            

    def do_modo(self, modo, arg2=None):
        """Cambia el modo de funcionamiento del robot. Se usa modo manual|auto"""
        if arg2 is not None:
            respuesta = self.controlador.cambiarModo(modo)
            self.ordenes.append(Orden("CAMBIAR MODO",time.strftime("%H:%M:%S"),respuesta,"Modo: "+modo))
            return (respuesta)
        else:
            print(self.controlador.cambiarModo(modo))
   
    def do_homing(self, arg1, arg2=None):
        """Realiza el homing y el robot vuelve a su posición de referencia."""
        if arg2 is not None:
            respuesta = self.controlador.homing()
            self.ordenes.append(Orden("HOMING",time.strftime("%H:%M:%S"),respuesta))
            return (respuesta)
        else:
            print(self.controlador.homing())

    def do_getPos(self, arg1, arg2=None):
        """Obtiene la posicion actual del del efector final."""
        #agregando orden cuando es llamado desde el cliente
        if arg2 is not None:
            respuesta = self.controlador.getCurrentPosition()
            self.ordenes.append(Orden("GET POSITION",time.strftime("%H:%M:%S"),respuesta))
            return (respuesta)
        else:
            print(self.controlador.getCurrentPosition())
    
    def do_movLineal(self, arg1, y=None, z=None, vel=None ):
        """Realiza un movimiento lineal en el dispositivo. Se usa movLineal x y z vel"""
        if y is not None:
            if vel is not None:
                posFinal = [float(arg1),float(y),float(z)]
                vel=float(vel)
                respuesta = self.controlador.movimientoLineal(posFinal,vel)
                self.ordenes.append(Orden("MOVIMIENTO LINEAL",time.strftime("%H:%M:%S"),respuesta,"Velocidad: "+str(vel)+" mm/s\nPosicion requerida: "+str(posFinal)))
            else:
                posFinal = [float(arg1),float(y),float(z)]
                respuesta = self.controlador.movimientoLineal(posFinal)
                self.ordenes.append(Orden("MOVIMIENTO LINEAL",time.strftime("%H:%M:%S"),respuesta,"Posicion requerida: "+str(posFinal)))
            return (respuesta)
        else:
            #separo el argumento por espacios y los convierto a float
            lista = arg1.split()
            lista = [float(i) for i in lista]
            if len(lista) == 3:
                posFinal = lista 
                print(self.controlador.movimientoLineal(posFinal))
            elif len(lista) == 4:
                vel = lista[3]
                posFinal = lista[0:3] #desde el segundo elemento hasta el final
                print(self.controlador.movimientoLineal(posFinal,vel))
            else:
                print("ERROR: argumentos incorrectos")

    #quiero que pueda pasar movLineal 100 10 20 30 o movLineal 100 10 20 30 40
    #en repo tengo hecha la funcion pero el problema se da en controlador.py

    def do_gripper(self, modo, arg2=None):
        """Activa o desactiva el efector final. Se usa gripper on|off"""
        if arg2 is not None:
            if modo == "on":
                respuesta = self.controlador.activarEfector()
                self.ordenes.append(Orden("GRIPPER",time.strftime("%H:%M:%S"),respuesta,"Modo: "+modo))
                return (respuesta)
            elif modo == "off":
                respuesta = self.controlador.desactivarEfector()
                self.ordenes.append(Orden("GRIPPER",time.strftime("%H:%M:%S"),respuesta,"Modo: "+modo))
                return (respuesta)
        else:
            if modo == "on":
                print(self.controlador.activarEfector())
            elif modo == "off":
                print(self.controlador.desactivarEfector())
            else:
                print("ERROR: comando no reconocido")
    
    def do_aprendizaje(self, modo, arg2=None):
        """Activa o desactiva el modo aprendizaje. Se usa aprendizaje on|off"""
        if arg2 is not None:
            if modo == "on":
                respuesta = self.controlador.aprenderTrayectoria(True, str(arg2))
                self.ordenes.append(Orden("APRENDIZAJE",time.strftime("%H:%M:%S"),respuesta,"Modo: "+modo+"\nNombre del archivo: "+str(arg2)))
                return respuesta
            elif modo == "off":
                respuesta = self.controlador.aprenderTrayectoria(False, str(arg2))
                self.ordenes.append(Orden("APRENDIZAJE",time.strftime("%H:%M:%S"),respuesta,"Modo: "+modo))
                return respuesta
        else:
            if modo == "on":
                print("Ingrese el nombre del archivo donde quiere guardar la trayectoria")
                self.learnFile = input()
                print(self.controlador.aprenderTrayectoria(True, self.learnFile))               
            elif modo == "off":
                print(self.controlador.aprenderTrayectoria(False, self.learnFile))              
            else:
                print("ERROR: comando no reconocido")

    def do_ejecutarTray(self, arg1, arg2=None):
        """Ejecuta una trayectoria aprendida."""
        
        if arg2 is not None:
            respuesta = self.controlador.ejecutarTrayectoria(str(arg1))
            self.ordenes.append(Orden("EJECUTAR TRAYECTORIA",time.strftime("%H:%M:%S"),respuesta,"Nombre del archivo: "+str(arg1)))
            return respuesta
        else:
            if self.controlador.getModo() == "Manual":
                print("ERROR: el robot debe estar en modo automatico")
            else:
                print("Tryectorias disponibles:")
                #listo los archivos en el directorio trayectorias
                
                for file in os.listdir("trayectorias"):
                    print(file)
                print("Ingrese el nombre del archivo que desea ejecutar")
                file = input()
                file = "./trayectorias/"+file
                print(self.controlador.ejecutarTrayectoria(file))
        

##############################################################
############# FUNCIONES del ejemplo original #################
##############################################################

    def do_list(self, arg1, arg2=None):
        """Lista elementos."""
        if arg2 is not None:
            return (self.elements)
        #al enviar el objeto va a ser recibido {1,2,TRES,Y EL RESTO}
        else:   
            print(self.elements)

    def do_suma(self, arg1, arg2=None, arg3=None):
        """Suma dos numeros."""
        #separo los argumentos por espacios
        if arg2 is not None:
            #retorno un string con los argumentos separados por espacios
            return (str(arg1) + " " + str(arg2)+ " " + str(arg3))
        else:
            print(str(arg1))

    
    #al llamar a esta funcion se debe hacer de esta manera: suma 1 2 pero no suma(1,2) ni suma(1,2,3)
    #porque el interprete de comandos no lo va a reconocer

    # def do_connect(self):

    # def help_connect(self):

    # def do_disconnect(self):

    # def help_disconnect(self):

