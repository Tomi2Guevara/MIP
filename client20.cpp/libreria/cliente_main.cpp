#include <iostream>
#include <string>
using namespace std;
#include "XmlRpc.h"
using namespace XmlRpc;
#include "panel_cliente.h"
#include "cl_UI.h"
#include <vector>



int main(int argc, char* argv[]){
    bool error;
    bool errorCliente;
    cl_UI ui = cl_UI();
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
            int datos;
            datos = ui.inicio();
            Panel_cliente cli = Panel_cliente(datos, argv[2], argv[1]);
            ui.setCliente(&cli);
            ui.mostrarDatosCliente();
            ui.loop(cli, c);
            return 0;
   
        } catch(const std::exception& e) {
            error = true;
            std::cerr << "Se ha producido una excepción: " << e.what() << '\n';
        }
    } while (error);
    return 0;
}


