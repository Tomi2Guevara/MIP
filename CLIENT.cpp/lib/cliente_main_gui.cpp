#include <iostream>
#include "XmlRpc.h"
using namespace XmlRpc;
#include "cl_GUI.h"



int main(int argc, char* argv[]){
    signal(SIGPIPE, SIG_IGN);
    bool error;
    bool errorCliente;
    cl_GUI gui = cl_GUI();
    do{
        error = false;

        if (argc != 3) {
            std::cerr << "Uso: hola_Client IP_HOST N_PORT\n"; // se debe indicar la IP y el puerto del servidor
            return -1;
        }
        try{

            int port = atoi(argv[2]);
            //XmlRpc::setVerbosity(5);
            // Una mirada a los métodos soportados por la API
            XmlRpcClient c(argv[1], port); //se crea un cliente XMLRPC para conectarse al servidor indicado en la linea de comandos
            gui.inicio( argv[2], argv[1]);
            gui.mostrarDatosCliente();
            gui.loop2(c);
            return 0;

        } catch(const std::exception& e) {
            error = true;
            gui.msjError("main");
        }
    } while (error);
    return 0;
}

