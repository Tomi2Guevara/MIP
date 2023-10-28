//
// Created by tguev on 27/10/2023.
//

#include "panel_cliente.h"
#include <windows.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
#include "libreria/XmlRpc.h"
using namespace XmlRpc;

#include "panel_cliente.h"

Panel_cliente::Panel_cliente(){}

Panel_cliente::Panel_cliente(int* id, std::string* puerto, std::string* IP)
{
    this->ID = id;
    this->puerto = puerto;
    this->IP = IP;
}

void Panel_cliente::do_listCom(XmlRpcClient c)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = "remote";
  if (c.execute("listCom", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'listCom'\n\n";
}

//El ID (xxxx) lo defini como variable global para este codigo, pero se puede pasar como argumento a cada funcion
void Panel_cliente::do_conectar(XmlRpcClient c)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = "remote";
  oneArg[1] = this->ID;
  if (c.execute("conectar", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'conectar'\n\n";
}

void Panel_cliente::do_desconectar(XmlRpcClient c)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = "remote";
  oneArg[1] = this->ID;
  if (c.execute("desconectar", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'desconectar'\n\n";
}

//recibe modo on/off
void Panel_cliente::do_motores(XmlRpcClient c, string modo)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = modo;
  oneArg[1] = this->ID;
  if (c.execute("motores", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'motores'\n\n";
  
}

//recibe modo manual/auto
void Panel_cliente::do_modo(XmlRpcClient c, string modo)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = modo;
  oneArg[1] = this->ID; //se agrega el parametro "remote" para que el servidor sepa que el cliente es remoto
  if (c.execute("modo", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'modo'\n\n";
}

void Panel_cliente::do_getPos(XmlRpcClient c)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = "remote";
  oneArg[1] = this->ID;
  if (c.execute("getPos", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'getPos'\n\n";
}

void Panel_cliente::do_homing(XmlRpcClient c)
{
  XmlRpcValue oneArg,result;
  oneArg[0] = "remote";
  oneArg[1] = this->ID; 
  if (c.execute("homing", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'homing'\n\n";
}

void Panel_cliente::do_movLineal(XmlRpcClient c, float x, float y, float z, float v)
{
  XmlRpcValue fourArgs, result;
  fourArgs[0] = "remote";
  fourArgs[1] = this->ID;
  fourArgs[2] = x;
  fourArgs[3] = y;
  fourArgs[4] = z;
  fourArgs[5] = v;
  if (c.execute("movLineal", fourArgs, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'movLineal'\n\n";
}

void Panel_cliente::do_movLineal(XmlRpcClient c, float x, float y, float z)
{
  XmlRpcValue threeArgs, result;
  threeArgs[0] = "remote";
  threeArgs[1] = this->ID;
  threeArgs[2] = x;
  threeArgs[3] = y;
  threeArgs[4] = z;
  if (c.execute("movLineal", threeArgs, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'movLineal'\n\n";
  
}

//recibe modo on/off
void Panel_cliente::do_gripper(XmlRpcClient c, string modo)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = modo;
  oneArg[1] = this->ID;
  if (c.execute("gripper", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'gripper'\n\n";
}

//recibe modo on/off y nombre del archivo donde se guardara la trayectoria
void Panel_cliente::do_aprendizaje(XmlRpcClient c, string modo, string fileName)
{
  XmlRpcValue twoArgs, result;
  twoArgs[0] = modo;
  twoArgs[1] = fileName;
  twoArgs[2] = this->ID;
  if (c.execute("aprendizaje", twoArgs, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'aprendizaje'\n\n";
}

//recibe nombre del archivo a ejecutar en modo automatico
void Panel_cliente::do_ejecutarTray(XmlRpcClient c, string fileName)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = fileName;
  oneArg[1] = this->ID;
  if (c.execute("ejecutarTray", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'ejecutarTray'\n\n";
}


void Panel_cliente::do_reporte(XmlRpcClient c)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = "remoto";
  oneArg[1] = this->ID;
  if (c.execute("reporte", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'reporte'\n\n";
}

//lista las trayectorias disponibles para ejecutar
void Panel_cliente::do_listTray(XmlRpcClient c)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = "remoto";
  oneArg[1] = this->ID;
  if (c.execute("listTray", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'listTray'\n\n";
}

//libera la conexion del cliente
void Panel_cliente::do_cerrarCliente(XmlRpcClient c)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = "remoto";
  oneArg[1] = this->ID;
  if (c.execute("cerrarCliente", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'cerrarCliente'\n\n";
}
 