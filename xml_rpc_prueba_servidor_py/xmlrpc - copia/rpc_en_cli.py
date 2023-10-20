#!/usr/bin/env python
# -*- coding: utf-8 -*-
from cmd import Cmd 

from rpc import XRServer

from controlador import Controlador

from execpciones import ModoInvalido

class XRConsola(Cmd):
    elements = ['1', 2, 'TRES', 'Y EL RESTO']

    def __init__(self):
        Cmd.__init__(self)
        self.rpc_server = None
        self.controlador = Controlador()
        #creo una lista self.elements que va a ser enviada al servidor
       
        
            
    def do_exit(self, args):
        """"Desconecta de un dispositivo interno y sale del programa."""
        if self.controlador.estado=="conectado": self.controlador.disconnect()
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
    

    def do_setModo(self, modo):
        """Cambia el modo de funcionamiento del dispositivo. Se usa setModo Manual|Automatico"""
        while True:
            if modo in ["Manual", "Automatico"]:
                break
            else:
                modo = input("Modo invalido, ingrese nuevamente: ")
        self.controlador.setModo(modo)
        print("Modo cambiado a: ", self.controlador.modo)

    '''def do_setAuto(self, modo, arg2=None):
        """recibe como modo de funcionamiento "on" u "off""""
        while True:
            if modo in ["on", "off"]:
                break
            else:
                modo = input("Modo invalido, ingrese nuevamente: ")
        if arg2 is not None:
            return (self.controlador.setAuto(modo))
        else:
            print(self.controlador.setAuto(modo))'''
    

   
    def do_homing(self, arg1, arg2=None):
        """Realiza el homing del dispositivo."""
        if arg2 is not None:
            return (self.controlador.homing())
        else:
            print(self.controlador.homing())
    

    def do_connect(self, arg1, arg2=None):
        """Conecta con el robot con el puerto serie."""
        if arg2 is not None:
            return (self.controlador.connect())
        else:
            print(self.controlador.connect())

    def do_disconnect(self, arg1, arg2=None):
        """Desconecta el robot del puerto serie."""
        if arg2 is not None:
            return (self.controlador.disconnect())
        else:
            print(self.controlador.disconnect())

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
