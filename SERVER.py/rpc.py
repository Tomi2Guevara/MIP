from xmlrpc.server import SimpleXMLRPCServer
from threading import Thread
import socket
import logging

RPC_PORT = 8891

class XRServer(object): 

    server = None

    def __init__(self, consola, port = RPC_PORT): 
        self.consola = consola
        used_port = port
        while True:
            try:
                self.server = SimpleXMLRPCServer(("localhost", used_port),
                                                 allow_none = True,
                                                 logRequests = None) 
                #remplazar localhost por la ip del servidor
                if used_port != port:
                    logging.warning(("RPC server bound on non-default port %d") % used_port)
                break
            except socket.error as e:
                if e.errno == 98:
                    used_port += 1
                    continue
                else:
                    raise
        self.server.register_function(self.get_status, 'status') 
        self.server.register_function(self.do_list, 'list')
        self.server.register_function(self.do_listCom, 'listCom')
        self.server.register_function(self.do_reporte, 'reporte')
        self.server.register_function(self.do_homing, 'homing')
        self.server.register_function(self.do_suma, 'suma')
        self.server.register_function(self.do_conectar, 'conectar')
        self.server.register_function(self.do_desconectar, 'desconectar')
        self.server.register_function(self.do_motores, 'motores')
        self.server.register_function(self.do_modo, 'modo')
        self.server.register_function(self.do_movLineal, 'movLineal')
        self.server.register_function(self.do_getPos, 'getPos')
        self.server.register_function(self.do_gripper, 'gripper')
        self.server.register_function(self.do_aprendizaje, 'aprendizaje')
        self.server.register_function(self.do_ejecutarTray, 'ejecutarTray')
        self.server.register_function(self.do_listTray, 'listTray')
        self.server.register_function(self.do_cerrarCliente, 'cerrarCliente')


        self.thread = Thread(target = self.run_server)
        self.thread.start()
        print("Servidor RPC iniciado en el puerto [%s]" % str(self.server.server_address))

    def run_server(self):
        self.server.serve_forever()

    def shutdown(self):
        self.server.shutdown()
        self.thread.join()



    def do_listCom(self, arg1):
        """Funcion definida en otro modulo dentro del servidor 
        en este caso dentro del propio interprete de comandos"""
        return self.consola.do_listCom(arg1, "remoto")
    
    def do_reporte(self, arg1, ID):
        """Funcion definida en otro modulo dentro del servidor 
        en este caso dentro del propio interprete de comandos"""
        return self.consola.do_reporte(arg1, ID)

    def do_conectar(self, arg1, ID):
        """Funcion definida en otro modulo dentro del servidor 
        en este caso dentro del propio interprete de comandos"""
        return self.consola.do_conectar(arg1, ID)
    
    def do_desconectar(self, arg1, ID):
        """Funcion definida en otro modulo dentro del servidor 
        en este caso dentro del propio interprete de comandos"""
        return self.consola.do_desconectar(arg1, ID)

    def do_motores(self, modo, ID):
        """Funcion definida en otro modulo dentro del servidor 
        en este caso dentro del propio interprete de comandos"""
        return self.consola.do_motores(modo, ID)
    
    def do_modo(self, modo, ID):
        """Funcion definida en otro modulo dentro del servidor 
        en este caso dentro del propio interprete de comandos"""
        return self.consola.do_modo(modo, ID)

    def do_homing(self, arg1, ID):
        """Funcion definida en otro modulo dentro del servidor 
        en este caso dentro del propio interprete de comandos"""
        return self.consola.do_homing(arg1, ID)
    
    def do_movLineal(self, arg1, ID=None, x=None, y=None, z=None, vel=None):
        """Funcion definida en otro modulo dentro del servidor 
        en este caso dentro del propio interprete de comandos"""
        return self.consola.do_movLineal(arg1, ID, x, y, z, vel)
    
    def do_getPos(self, arg1, ID):
        """Funcion definida en otro modulo dentro del servidor 
        en este caso dentro del propio interprete de comandos"""
        return self.consola.do_getPos(arg1, ID)
    
    def do_gripper(self, modo, ID):
        """Funcion definida en otro modulo dentro del servidor 
        en este caso dentro del propio interprete de comandos"""
        return self.consola.do_gripper(modo, ID)
    
    def do_aprendizaje(self, modo, fileName, ID):
        """Funcion definida en otro modulo dentro del servidor 
        en este caso dentro del propio interprete de comandos"""
        return self.consola.do_aprendizaje(modo, fileName, ID)
    #el fileName lo debo pedir antes en el cliente
    
    def do_ejecutarTray(self, tray, ID):
        """Funcion definida en otro modulo dentro del servidor 
        en este caso dentro del propio interprete de comandos"""
        return self.consola.do_ejecutarTray(tray, ID)
    #la tray la debo pedir antes en el cliente

    def do_listTray(self, arg1, ID):
        """Funcion definida en otro modulo dentro del servidor 
        en este caso dentro del propio interprete de comandos"""
        #La uso para leer los archivos en el directorio trayectorias
        return self.consola.do_listTray(arg1, ID)

    def do_cerrarCliente(self, arg1, ID):
        """Funcion definida en otro modulo dentro del servidor
        en este caso dentro del propio interprete de comandos"""
        return self.consola.do_cerrarCliente(arg1, ID)
    

    
    
    
 ###########################################################
 # Funciones de ejemplo para el servidor RPC##############
 ###########################################################   
    def do_suma(self, arg1, arg2=None, arg3=None):
        """Funcion definida en otro modulo dentro del servidor 
        en este caso dentro del propio interprete de comandos"""
        return self.consola.do_suma(arg1, arg2, arg3)
    
    def get_status(self):
        """Funcion definida en el propio servidor"""
        return {"param_1": "11",
                "param_2": "22",
                "param_N": "NN",
                }

    def do_list(self, arg1):
        """Funcion definida en otro modulo dentro del servidor 
        en este caso dentro del propio interprete de comandos"""
        return self.consola.do_list(arg1, "remoto")