#include "cl_UI.h"
#include <iostream>
#include <string>
using namespace std;
#include "panel_cliente.h"
#include <exception>

cl_UI::cl_UI() {  
    
}

void cl_UI::setCliente(Panel_cliente* cliente) {
    this->cliente = cliente;
}

int inicio(){
    int ID;
    std::cout << "Bienvenido al panel de control del robot" << std::endl;
    std::cout << "Ingrese su ID: "<< std::endl;
    std::cin >> ID;
    return ID;    
}

void cl_UI::panelDeControl(int* opcion) {
    
    std::cout << "==========================================================================\n";
  std::cout << "conectar      desconectar         motores on|off          modo auto|manual\n";
  std::cout << "getPos        homing              movLineal x y z vel     reporte\n";
  std::cout << "listCom       gripper on|off      aprendizaje on|off      ejecutarTray\n";
  std::cout << "salir\n";
  std::cout << "==========================================================================\n";

    //limpio la pantalla
    system("cls");
}

void cl_UI::acciones(int* opcion) {
    std::string comando;
    //muestro un promt >> para que el usuario sepa que tiene que ingresar
    std::cout << ">> ";
    //leo la opcion que ingresa el usuario
    //std::cin >> comando;
    //cuando ingreso comando on o off para los motores o el gripper, el cin no toma el espacio, por lo que uso getline
    getline(std::cin, comando);

    *opcion = 20; // Valor por defecto
    if (comando == "conectar")
        *opcion = 2;
    else if (comando == "desconectar")
        *opcion = 3;
    else if (comando == "motores on")
        *opcion = 4;
    else if (comando == "motores off")
        *opcion = 13;
    else if (comando == "modo auto")
        *opcion = 5;
    else if (comando == "modo manual")
        *opcion = 5;
    else if (comando == "getPos")
        *opcion = 7;
    else if (comando == "homing")
        *opcion = 1;
    else if (comando == "movLineal")
        *opcion = 9;
    else if (comando == "reporte")
        *opcion = 10;
    else if (comando == "listCom")
        *opcion = 11;
    else if(comando=="gripper on")
        *opcion = 10;
    else if(comando=="gripper off")
        *opcion = 10;
    else if(comando=="aprendizaje on")
        *opcion = 11;
    else if(comando=="aprendizaje off")
        *opcion = 11;
    else if(comando=="ejecutarTray")
        *opcion = 12;
    else if(comando=="salir")
        *opcion = 14;
}



void cl_UI::mostrarDatosCliente() {
    std::cout << "Datos del cliente:" << std::endl;
    std::cout << "ID: " << cliente->getID() << std::endl;
    std::cout << "Puerto: " << cliente->getPuerto() << std::endl;
    std::cout << "IP: " << cliente->getIP() << std::endl;
}

void cl_UI::cambiarDatosCliente() {
    int id, ip;
    std::string nombrePanel, puerto;

    std::cout << "Ingrese el nuevo ID del cliente: ";
    std::cin >> id;
    cliente->setID(id);

    std::cout << "Ingrese el nuevo puerto del cliente: ";
    std::cin >> puerto;
    cliente->setPuerto(puerto);

    std::cout << "Ingrese la nueva dirección IP del cliente: ";
    std::cin >> ip;
    cliente->setID(ip);
}

void cl_UI::msjError(std::string metodo) {
    std::cout << "Error al ejecutar " << metodo << std::endl;
}
void cl_UI::case4() {
    std::cout << "motores activados...";    
}
void cl_UI::case5(std::string* modo) {
    std::cout << "Ingrese el modo auto|manual: ";
    std::cin >> *modo;
}
void cl_UI::case6(float* x, float* y, float* z, float* v, char* flag) {
    std::cout << "Ingrese x: ";
    std::cin >> *x;
    std::cout << "Ingrese y: ";
    std::cin >> *y;
    std::cout << "Ingrese z: ";
    std::cin >> *z;
    std::cout << "Desea especificar la velocidad? (s/n): ";
    std::cin>>flag;
}
void cl_UI::case10(string* modo) {
    std::cout << "Ingrese el modo on|off: ";
    std::cin >> *modo;
}
void cl_UI::case11(string* modo, string* fileName) {
    std::cout << "Ingrese el modo on|off: ";
    std::cin >> *modo;
    std::cout << "Ingrese el nombre del archivo: ";
    std::cin >> *fileName;
}
void cl_UI::case12A() {
    std::cout<<"las trayectorias disponibles son: \n";
}

void cl_UI::case12B(string* fileName) {
    std::cout << "Ingrese el nombre del archivo: ";
    std::cin >> *fileName;    
}

void cl_UI::case14() {
    std::cout << "Saliendo del programa..." << std::endl;
}
void defelctCase() {
    std::cout << "Opcion incorrecta, ingrese un numero del 1 al 14" << std::endl;
}


