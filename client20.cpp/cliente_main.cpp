#include <iostream>
#include <string>
using namespace std;
#include "libreria/XmlRpc.h"
using namespace XmlRpc;
#include "panel_cliente.h"
#include "cl_UI.h"
#include <vector>



int main(int argc, char* argv[]){
    bool error;
    bool errorCliente;
    std::string modo;
    std::string fileName;
    char cont;
    char flag;
    int opcion;
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
            
        
        
        

       
            
            ui.panelDeControl(&opcion);
            do{                    
                switch (opcion) {
                
                    case 1:
                        cli.do_homing(c);
                        break;
                    case 2:
                        cli.do_conectar(c);
                        break;
                    case 3:
                        cli.do_desconectar(c);
                        break;
                    case 4:
                        ui.case4();
                        modo = "on";
                        cli.do_motores(c, modo);
                        break;
                    case 5:
                        ui.case5(&modo);
                        cli.do_modo(c, modo);
                        break;
                    case 6:
                        float x, y, z, v;
                        ui.case6(&x, &y, &z, &v, &flag);
                        if (flag == 's'){
                            std::cout << "Ingrese v: ";
                            std::cin >> v;
                            cli.do_movLineal(c, x, y, z, v);
                        }
                        else
                            cli.do_movLineal(c, x, y, z);
                        break;
                    case 7:
                        cli.do_getPos(c);
                        break;
                    case 8:
                        cli.do_listCom(c);
                        break;
                    case 9:
                        cli.do_reporte(c);
                        break;
                    case 10:
                        std::cout << "Ingrese el modo on|off: ";
                        std::cin >> modo;
                        cli.do_gripper(c, modo);
                        break;
                    case 11:
                        std::cout << "Ingrese el modo on|off: ";
                        std::cin >> modo;
                        if (modo == "on"){
                            std::cout << "Ingrese el nombre del archivo donde va a guardar la trayectoria: ";
                            std::cin >> fileName;}
                        cli.do_aprendizaje(c, modo, fileName);
                        break;
                    case 12:
                        std::cout<<"las trayectorias disponibles son: \n";
                        cli.do_listTray(c);
                        std::cout << "Ingrese el nombre del archivo: ";
                        std::cin >> fileName;
                        cli.do_ejecutarTray(c, fileName);
                        break;
                    case 13:
                        ui.case13();
                        modo = "off";
                        cli.do_motores(c, modo);
                        break;

                    case 14:
                        cli.do_cerrarCliente(c);
                        std::cout << "Saliendo...\n";
                        break;
                    default:
                        std::cout << "Opcion incorrecta\n";
                        break;
                    }
                ui.acciones(&opcion);                        
                
            } while (opcion != 13);
            
    
            

            char salida;
            cli.do_cerrarCliente(c);
            std::cout << "Ingrese cualquier caracter para salir...";
            std::cin >> salida;  
            return 0;
            
        
        
        } catch(const std::exception& e) {
            error = true;
            std::cerr << "Se ha producido una excepción: " << e.what() << '\n';
        }
    } while (error);
}


