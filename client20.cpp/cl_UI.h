#include "cliente.h"
#include <istream>
using namespace std;
#include <string>
#include <vector>

class cl_UI {
private:
    Cliente* cliente;
public:
    cl_UI();
    vector <string> inicio();
    void mostrarMenu();
    void mostrarDatosCliente();
    void cambiarDatosCliente();
    void conectarCliente();
    void desconectarCliente();
    void enviarMensajeCliente();
    void recibirMensajeCliente();
    int panelDeControl();

};