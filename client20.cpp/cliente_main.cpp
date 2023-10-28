#include <iostream>
#include <string>
#include "libreria/XmlRpc.h"
using namespace XmlRpc;
#include "panel_cliente.h"
#include "cliente.h"
#include "cl_UI.h"
#include <vector>



int main(int argc, char* argv[]){

    if (argc != 3) {
        std::cerr << "Uso: hola_Client IP_HOST N_PORT\n"; // se debe indicar la IP y el puerto del servidor
        return -1;
    }
    
    int port = atoi(argv[2]);
    //XmlRpc::setVerbosity(5);

    // Una mirada a los métodos soportados por la API
    XmlRpcClient c(argv[1], port); //se crea un cliente XMLRPC para conectarse al servidor indicado en la linea de comandos
    vector <string> datos;
    cl_UI ui = cl_UI();
    datos = ui.inicio();
    Cliente cli = Cliente(stoi(datos[0]), datos[1], datos[2]);


 
    do
    {
        
        int opcion = ui.panelDeControl();

        switch (opcion)
        {
        case 1:
        cli.getPanel().do_homing(c);
        break;
        case 2:
        cli.getPanel().do_conectar(c);
        break;
        case 3:
        cli.getPanel().do_desconectar(c);
        break;
        case 4:
        std::cout << "Ingrese el modo on|off: ";
        std::cin >> modo;
        cli.getPanel().do_motores(c, modo);
        break;
        case 5:
        std::cout << "Ingrese el modo auto|manual: ";
        std::cin >> modo;
        cli.getPanel().do_modo(c, modo);
        break;
        case 6:
        float x, y, z, v;
        std::cout << "Ingrese x: ";
        std::cin >> x;
        std::cout << "Ingrese y: ";
        std::cin >> y;
        std::cout << "Ingrese z: ";
        std::cin >> z;
        std::cout << "Desea especificar la velocidad? (s/n): ";
        std::cin>>flag;
        if (flag == 's'){
            std::cout << "Ingrese v: ";
            std::cin >> v;
            cli.getPanel().do_movLineal(c, x, y, z, v);
        }
        else
            cli.getPanel().do_movLineal(c, x, y, z);
        break;
        case 7:
        cli.getPanel().do_getPos(c);
        break;
        case 8:
        cli.getPanel().do_listCom(c);
        break;
        case 9:
        cli.getPanel().do_reporte(c);
        break;
        case 10:
        std::cout << "Ingrese el modo on|off: ";
        std::cin >> modo;
        cli.getPanel().do_gripper(c, modo);
        break;
        case 11:
        std::cout << "Ingrese el modo on|off: ";
        std::cin >> modo;
        if (modo == "on"){
            std::cout << "Ingrese el nombre del archivo donde va a guardar la trayectoria: ";
            std::cin >> fileName;}
        cli.getPanel().do_aprendizaje(c, modo, fileName);
        break;
        case 12:
        std::cout<<"las trayectorias disponibles son: \n";
        cli.getPanel().do_listTray(c);
        std::cout << "Ingrese el nombre del archivo: ";
        std::cin >> fileName;
        cli.getPanel().do_ejecutarTray(c, fileName);
        break;
        case 13:
        cli.getPanel().do_cerrarCliente(c);
        std::cout << "Saliendo...\n";
        break;
        default:
        std::cout << "Opcion incorrecta\n";
        break;
        }
        std::cout << "Presione cualquier tecla para continuar...";
        std::cin>>cont;
        system("cls");
    } while (opcion != 13);
    
    char salida;
    cli.getPanel().do_cerrarCliente(c);
    std::cout << "Ingrese cualquier caracter para salir...";
    std::cin >> salida;  
    return 0;
}