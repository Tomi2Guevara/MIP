//
// Created by tguev on 27/10/2023.
//

#ifndef INTPROYECT_PANEL_CLIENTE_H
#define INTPROYECT_PANEL_CLIENTE_H

    class Panel_cliente {
        private:

        public:
            Panel_cliente();
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


