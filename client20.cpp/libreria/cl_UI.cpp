
#include <iostream>
#include <string>
#include <exception>
#include <sstream>
#include <unistd.h>
#include <limits>
#include <vector>
using namespace std;
#include "cl_UI.h"
#include "panel_cliente.h"


cl_UI::cl_UI() {  
    
}

void cl_UI::setCliente(Panel_cliente* cliente) {
    this->cli = cliente;
}

int cl_UI::inicio(){
    int ID;
    std::cout << "\n==========================================================================\n";
    std::cout << "\nBienvenido al panel de control del robot" << std::endl;
    std::cout << "Ingrese su ID: ";
    std::cin >> ID;
    return ID;    
}

void cl_UI::ListCom() {
    
    stringstream ss;
    ss << "\n\nDocumented commands (type help <topic>):\n";
    ss << "==========================================================================\n";
    ss << "conectar      desconectar         motores on|off          modo auto|manual\n";
    ss << "getPos        homing              movLineal               reporte\n";
    ss << "listCom       gripper on|off      aprendizaje on|off      ejecutarTray\n";
    ss << "salir\n";
    ss << "==========================================================================\n";
    std::cout<<ss.str();
}


void cl_UI::mostrarDatosCliente() {
    stringstream ss;
    ss << "\n-------CONEXION ESTABLECIDA-------\n";
    ss << "ID: " << cli->getID() << "\n";
    ss << "Puerto: " << cli->getPuerto() << "\n";
    ss << "IP: " << cli->getIP() << "\n";
    ss << "----------------------------------\n";
    std::cout<<ss.str();
}

void cl_UI::cambiarDatosCliente() {
    int id, ip;
    std::string nombrePanel, puerto;

    std::cout << "Ingrese el nuevo ID del cliente: ";
    std::cin >> id;
    cli->setID(id);

    std::cout << "Ingrese el nuevo puerto del cliente: ";
    std::cin >> puerto;
    cli->setPuerto(puerto);

    std::cout << "Ingrese la nueva dirección IP del cliente: ";
    std::cin >> ip;
    cli->setID(ip);
}

void cl_UI::msjError(std::string metodo) {
    std::cout << "Error al ejecutar " << metodo << std::endl;
}


int cl_UI::loop(Panel_cliente cli ,XmlRpcClient c) {
    
    string comando;
    int opcion;
    string modo;
    string fileName;
    char cont;
    char flag;

    ListCom();

    do
    {
        // Limpia el búfer de entrada
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        //muestro un promt >> 
        std::cout << ">> ";
        getline(std::cin, comando);//aveces toma caracteres que no tipeo el usuario, porque se ejecuta antes de que termine de llegar la respuesta del servidor
        //si es un solo caracter, lo toma como un enter, entonces lo ignoro
        if(comando.length()==1)
            continue;
        opcion = decode(comando);

        switch (opcion)
        {
        case 1:
            cli.do_conectar(c);
            break;
        case 2:
            cli.do_desconectar(c);
            break;
        case 3:
            modo = "on";
            cli.do_motores(c, modo);
            break;
        case 4:
            modo = "off";
            cli.do_motores(c, modo);
            break;
        case 5:
            modo = "auto";
            cli.do_modo(c, modo);
            break;
        case 6:
            modo = "manual";
            cli.do_modo(c, modo);
            break;
        case 7:
            cli.do_getPos(c);
            break;
        case 8:
            cli.do_homing(c);
            break;
        case 9:
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
                cli.do_movLineal(c, x, y, z);
            }
            else
                cli.do_movLineal(c, x, y, z);
            break;
        case 10:
            cli.do_reporte(c);
            break;
        case 11:
            ListCom();
            break;
        case 12:
            modo = "on";
            cli.do_gripper(c, modo);
            break;
        case 13:
            modo = "off";
            cli.do_gripper(c, modo);
            break;
        case 14:
            std::cout << "Ingrese el nombre del archivo: ";
            std::cin >> fileName;
            cli.do_aprendizaje(c, "on", fileName);
            break;
        case 15:
            cli.do_aprendizaje(c, "off", "");
            break;
        case 16:
            std::cout<<"Las trayectorias disponibles son: \n";
            cli.do_listTray(c);
            std::cout << "Ingrese el nombre del archivo: ";
            std::cin >> fileName;
            cli.do_ejecutarTray(c, fileName);
            break;
        case 17:
            cli.do_desconectar(c);
            cli.do_cerrarCliente(c);
            break;
        case 18:
            comando = comando.substr(5, comando.length());
            std::cout << helpCommand(comando);
            break;
        default:
            std::cout << "Comando no reconocido\n";
            break;
        }
    } while (opcion != 17);
    
    char salida;
    std::cout << "Ingrese cualquier caracter para salir...";
    std::cin >> salida;  
    return 0;
}

int cl_UI::decode(string s)
{
  if (s == "conectar")
    return 1;
  if (s == "desconectar")
    return 2;
  if (s == "motores on")
    return 3;
  if (s == "motores off")
    return 4;
  if (s == "modo auto")
    return 5;
  if (s == "modo manual")
    return 6;
  if (s == "getPos")
    return 7;
  if (s == "homing")
    return 8;
  if (s == "movLineal")
    return 9;
  if (s == "reporte")
    return 10;
  if (s == "listCom")
    return 11;
  if(s=="gripper on")
    return 12;
  if(s=="gripper off")
    return 13;
  if(s=="aprendizaje on")
    return 14;
  if(s=="aprendizaje off")
    return 15;
  if(s=="ejecutarTray")
    return 16;
  if(s=="salir")
    return 17;
  //si las primeras letras son help entonces 18
  if(s[0]=='h' && s[1]=='e' && s[2]=='l' && s[3]=='p')
    return 18;
  return 20;
}

 string cl_UI::helpCommand(string comando){
  stringstream ss;
  if(comando=="conectar"){
    ss << "conectar: conecta el cliente al servidor\n";
    ss << "Uso: conectar\n";
    return ss.str();
  }
  if(comando=="desconectar"){
    ss << "desconectar: desconecta el cliente del servidor\n";
    ss << "Uso: desconectar\n";
    return ss.str();
  }
  if(comando=="motores" || comando=="motores on" || comando=="motores off"){
    ss << "motores: enciende o apaga los motores\n";
    ss << "Uso: motores on|off\n";
    return ss.str();
  }
  if(comando=="modo" || comando=="modo auto" || comando=="modo manual"){
    ss << "modo: cambia el modo de operacion del robot\n";
    ss << "Uso: modo auto|manual\n";
    return ss.str();
  }
  if(comando=="getPos"){
    ss << "getPos: devuelve la posicion actual del robot\n";
    ss << "Uso: getPos\n";
    return ss.str();
  }
  if(comando=="homing"){
    ss << "homing: realiza el homing del robot\n";
    ss << "Uso: homing\n";
    return ss.str();
  }
  if(comando=="movLineal"){
    ss << "movLineal: mueve el robot a una posicion especifica\n";
    ss << "Uso: movLineal (vel<50 mm/s)\n";
    return ss.str();
  }
  if(comando=="reporte"){
    ss << "reporte: devuelve el reporte de errores del robot\n";
    ss << "Uso: reporte\n";
    return ss.str();
  }
  if(comando=="listCom"){
    ss << "listCom: devuelve la lista de comandos disponibles\n";
    ss << "Uso: listCom\n";
    return ss.str();
  }
  if(comando=="gripper" || comando=="gripper on" || comando=="gripper off"){
    ss << "gripper: abre o cierra el gripper\n";
    ss << "Uso: gripper on|off\n";
    return ss.str();
  }
  if(comando=="aprendizaje" || comando=="aprendizaje on" || comando=="aprendizaje off"){
    ss << "aprendizaje: activa o desactiva el modo aprendizaje\n";
    ss << "Uso: aprendizaje on|off\n";
    return ss.str();
  }
  if(comando=="ejecutarTray"){
    ss << "ejecutarTray: ejecuta una trayectoria guardada\n";
    ss << "Uso: ejecutarTray\n";
    return ss.str();
  }
  if(comando=="salir"){
    ss << "salir: cierra el cliente\n";
    ss << "Uso: salir\n";
    return ss.str();
  }
  return "Comando no reconocido\n";
}


