#include <iostream>
#include <string>

#include "panel_cliente.h"

using namespace std;

class cl_GUI {
private:
    Panel_cliente* cli;
    string fileName;
public:
    cl_GUI();
    void inicio(string puerto, string IP);
    void mostrarDatosCliente();
    void msjError(string metodo);
    void setCliente(Panel_cliente* cliente);
    int loop(XmlRpcClient c);
    void loop2(XmlRpcClient c);
    int decode(string s);
};



