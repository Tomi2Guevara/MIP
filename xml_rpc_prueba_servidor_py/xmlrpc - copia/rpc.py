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
        self.server.register_function(self.do_homing, 'homing')
        self.server.register_function(self.do_connect, 'connect')
        self.server.register_function(self.do_disconnect, 'disconnect')
        self.server.register_function(self.do_suma, 'suma')

        self.thread = Thread(target = self.run_server)
        self.thread.start()
        print("Servidor RPC iniciado en el puerto [%s]" % str(self.server.server_address))

    def run_server(self):
        self.server.serve_forever()

    def shutdown(self):
        self.server.shutdown()
        self.thread.join()

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

    def do_connect(self, arg1):
        """Funcion definida en otro modulo dentro del servidor 
        en este caso dentro del propio interprete de comandos"""
        return self.consola.do_connect(arg1, "remoto")
    
    def do_disconnect(self, arg1):
        """Funcion definida en otro modulo dentro del servidor 
        en este caso dentro del propio interprete de comandos"""
        return self.consola.do_disconnect(arg1, "remoto")
    
    def do_homing(self, arg1):
        """Funcion definida en otro modulo dentro del servidor 
        en este caso dentro del propio interprete de comandos"""
        return self.consola.do_homing(arg1, "remoto")
    
    def do_suma(self, arg1, arg2=None, arg3=None):
        """Funcion definida en otro modulo dentro del servidor 
        en este caso dentro del propio interprete de comandos"""
        return self.consola.do_suma(arg1, arg2, arg3)