#include "cliente.h"
#include "panel_cliente.h"

// Constructor con parámetros
Cliente::Cliente(int id, std::string pt, std::string ip) {
    this->ID = id;    
    this->puerto = pt;
    this->IP = ip;
    this->panel = Panel_cliente(&this->ID, &this->puerto, &this->IP);
}

// Métodos de acceso
int Cliente::getID() {
    return ID;
}

Panel_cliente Cliente::getPanel()  {
    return this->panel;
}

std::string Cliente::getPuerto()  {
    return puerto;
}

std::string Cliente::getIP()  {
    return IP;
}

void Cliente::setID(int id) {
    ID = id;
}

void Cliente::setPuerto(std::string pt) {
    puerto = pt;
}

void Cliente::setIP(std::string ip) {
    IP = ip;
}

void Cliente::setPanel(Panel_cliente panel) {
    this->panel = panel;
}
