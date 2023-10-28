#include "panel_cliente.h"
#include <string>


class Cliente {
private:
    int ID;
    Panel_cliente panel;
    std::string puerto;
    std::string IP;
public:
    Cliente();
    Cliente(int id, std::string puerto, std::string IP);
    void setID(int id);
    void setPuerto(std::string puerto);
    void setIP(std::string IP);
    int getID();
    void setPanel(Panel_cliente panel);
    Panel_cliente getPanel();
    std::string getPuerto();
    std::string getIP();
    
    

};