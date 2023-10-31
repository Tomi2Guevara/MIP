// Purpose: Header file for cl_UI.cpp
#include <string>
#include "panel_cliente.h"
#include <exception> 

class cl_UI {
private:
    Panel_cliente* cliente;
public:
    cl_UI();
    int inicio();
    void mostrarDatosCliente();
    void cambiarDatosCliente();
    void panelDeControl(int* opcion);
    void acciones(int* opcion);
    void msjError(string metodo);
    void setCliente(Panel_cliente* cliente);
    void case4();
    void case5(string* modo);
    void case6(float* x, float* y, float* z, float* v, char* flag);
    void case10(string* modo);
    void case11(string* modo, string* fileName);
    void case12A();
    void case12B(string* fileName);
    void case13();
    void case14();
    void defaultCase();
};