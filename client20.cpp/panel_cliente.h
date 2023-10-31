//
// Created by tguev on 27/10/2023.
//
#include <string>
using namespace std;
#include "libreria/XmlRpc.h"
using namespace XmlRpc;
#ifndef INTPROYECT_PANEL_CLIENTE_H
#define INTPROYECT_PANEL_CLIENTE_H

    class Panel_cliente {
        private:
            int ID;
            std::string puerto;
            std::string IP;


        public:
            Panel_cliente();
            Panel_cliente(int id, std::string puerto, std::string IP);
            void setID(int id);
            void setPuerto(std::string puerto);
            void setIP(std::string IP);
            int getID();
            std::string getPuerto();
            std::string getIP();
            void do_homing(XmlRpcClient c);
            void do_conectar(XmlRpcClient c);
            void do_desconectar(XmlRpcClient c);
            void do_motores(XmlRpcClient c, string modo);
            void do_movLineal(XmlRpcClient c, float x, float y, float z, float v);
            void do_movLineal(XmlRpcClient c, float x, float y, float z);
            void do_getPos(XmlRpcClient c);
            void do_listCom(XmlRpcClient c);
            void do_reporte(XmlRpcClient c);
            void do_modo(XmlRpcClient c, string modo);
            void do_gripper(XmlRpcClient c, string modo);
            void do_aprendizaje(XmlRpcClient c, string modo, string fileName);
            void do_ejecutarTray(XmlRpcClient c, string fileName);
            void do_listTray(XmlRpcClient c);
            void do_cerrarCliente(XmlRpcClient c);


    };



#endif //INTPROYECT_PANEL_CLIENTE_H


