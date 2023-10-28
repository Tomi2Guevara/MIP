#include "cl_UI.h"
#include <iostream>
#include <string>
#include <vector>

cl_UI::cl_UI() {  
    
}

vector <string> inicio(){
    string ID;
    string puerto;
    string IP;
    vector <string> datos;
    std::cout << "Bienvenido al panel de control del robot" << std::endl;
    std::cout << "Ingrese su ID: "<< std::endl;
    std::cin >> ID;
    std::cout << "Ingrese el puerto de comunicación: "<< std::endl;
    std::cin >> puerto;
    std::cout << "Ingrese la IP del servidor: "<< std::endl;
    std::cin >> IP;
    datos.push_back(ID);
    datos.push_back(puerto);
    datos.push_back(IP);
    return datos;    
}

int cl_UI::panelDeControl() {
    int opcion;
    std::cout << "Ingrese el numero del metodo que desea ejecutar:\n";
    std::cout << "1. homing\n";
    std::cout << "2. conectar\n";
    std::cout << "3. desconectar\n";
    std::cout << "4. motores\n";
    std::cout << "5. modo\n";
    std::cout << "6. movLineal\n";
    std::cout << "7. getPos\n";
    std::cout << "8. listCom\n";
    std::cout << "9. reporte\n";
    std::cout << "10. gripper\n";
    std::cout << "11. aprendizaje\n";
    std::cout << "12. ejecutarTrayectoria\n";
    std::cout << "13. salir\n";
    std::cout << "Opcion: ";
    std::cin >> opcion;

    //limpio la pantalla
    system("cls");

    return opcion;
}

void cl_UI::mostrarMenu() {
    std::cout << "Menú de opciones:" << std::endl;
    std::cout << "1. Mostrar datos del cliente" << std::endl;
    std::cout << "2. Cambiar datos del cliente" << std::endl;
    std::cout << "3. Conectar cliente" << std::endl;
    std::cout << "4. Desconectar cliente" << std::endl;
    std::cout << "5. Enviar mensaje al cliente" << std::endl;
    std::cout << "6. Recibir mensaje del cliente" << std::endl;
    std::cout << "7. Salir" << std::endl;
}

void cl_UI::mostrarDatosCliente() {
    std::cout << "Datos del cliente:" << std::endl;
    std::cout << "ID: " << cliente->getID() << std::endl;
    std::cout << "Puerto: " << *cliente->getPuerto() << std::endl;
    std::cout << "IP: " << *cliente->getIP() << std::endl;
}

void cl_UI::cambiarDatosCliente() {
    int id;
    std::string nombrePanel, puerto, ip;

    std::cout << "Ingrese el nuevo ID del cliente: ";
    std::cin >> id;
    cliente->setID(id);

    std::cout << "Ingrese el nuevo nombre del panel del cliente: ";
    std::cin >> nombrePanel;
    cliente->getPanel()->setNombre(nombrePanel);

    std::cout << "Ingrese el nuevo puerto del cliente: ";
    std::cin >> puerto;
    *cliente->getPuerto() = puerto;

    std::cout << "Ingrese la nueva dirección IP del cliente: ";
    std::cin >> ip;
    *cliente->getIP() = ip;
}

void cl_UI::conectarCliente() {
    ;
    std::cout << "Cliente conectado." << std::endl;
}

void cl_UI::desconectarCliente() {
    cliente->desconectar();
    std::cout << "Cliente desconectado." << std::endl;
}

void cl_UI::enviarMensajeCliente() {
    std::string mensaje;
    std::cout << "Ingrese el mensaje a enviar: ";
    std::cin >> mensaje;
    cliente->enviarMensaje(mensaje);
    std::cout << "Mensaje enviado." << std::endl;
}

void cl_UI::recibirMensajeCliente() {
    std::string mensaje = cliente->recibirMensaje();
    std::cout << "Mensaje recibido: " << mensaje << std::endl;
}

