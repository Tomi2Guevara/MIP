// Purpose: Header file for cl_UI.cpp
#include <string>
#include "panel_cliente.h"
#include <exception> 

class cl_UI {
private:
    Panel_cliente* cli;
public:
    cl_UI();
    void inicio(string puerto, string IP);
    void mostrarDatosCliente();
    void cambiarDatosCliente();
    void ListCom();
    void msjError(string metodo);
    void setCliente(Panel_cliente* cliente);
    int loop(XmlRpcClient c);
    int decode(string s);
    string helpCommand(string comando);
};