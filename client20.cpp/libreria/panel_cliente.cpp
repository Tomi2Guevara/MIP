//
// Created by tguev on 27/10/2023.
//

#include "panel_cliente.h"
#include <windows.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
#include "XmlRpc.h"
using namespace XmlRpc;

#include "panel_cliente.h"

Panel_cliente::Panel_cliente(){}

Panel_cliente::Panel_cliente(int id, std::string puerto, std::string IP)
{
    this->ID = id;
    this->puerto = puerto;
    this->IP = IP;
}

void Panel_cliente::setID(int id)
{
    this->ID = id;
}
void Panel_cliente::setPuerto(std::string puerto)
{
    this->puerto = puerto;
}
void Panel_cliente::setIP(std::string IP)
{
    this->IP = IP;
}
int Panel_cliente::getID()
{
    return this->ID;
}
std::string Panel_cliente::getPuerto()
{
    return this->puerto;
}
std::string Panel_cliente::getIP()
{
    return this->IP;
}


/**
 * @brief Executes the 'listCom' method of an XmlRpcClient object and prints the result to the console.
 * 
 * @param c The XmlRpcClient object to execute the method on.
 */
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
/**
 * @brief Connects to a remote server using XmlRpcClient and executes the "conectar" method with the ID of the current Panel_cliente object.
 * 
 * @param c The XmlRpcClient object used to connect to the remote server.
 */
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

/**
 * @brief Disconnects the client from the server using XmlRpc protocol.
 * 
 * @param c The XmlRpcClient object used to make the call.
 */
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
/**
 * @brief Executes the "motores" method on the XmlRpcClient with the given mode and ID.
 * 
 * @param c The XmlRpcClient to execute the method on.
 * @param modo The mode to pass as the first argument to the "motores" method.
 */
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
/**
 * @brief Executes a mode change on the server through an XmlRpcClient object.
 * 
 * @param c The XmlRpcClient object used to execute the mode change.
 * @param modo The mode to be executed.
 */
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

/**
 * @brief This function sends a request to the server to get the position of the client panel.
 * 
 * @param c The XmlRpcClient object used to make the request.
 */
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

/**
 * @brief Executes homing function on the remote server for the current Panel_cliente object.
 * 
 * @param c XmlRpcClient object used to execute the homing function remotely.
 */
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

/**
 * @brief Executes a linear movement command on the remote server using the given XmlRpcClient object.
 * 
 * @param c The XmlRpcClient object used to execute the command.
 * @param x The x coordinate of the destination point.
 * @param y The y coordinate of the destination point.
 * @param z The z coordinate of the destination point.
 * @param v The velocity of the movement.
 */
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

/**
 * @brief Moves the client panel in a linear way using the given coordinates.
 * 
 * @param c The XmlRpcClient used to execute the movement.
 * @param x The x coordinate of the movement.
 * @param y The y coordinate of the movement.
 * @param z The z coordinate of the movement.
 */
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
/**
 * @brief Executes the gripper function on the XmlRpcClient with the given mode and ID.
 * 
 * @param c The XmlRpcClient to execute the function on.
 * @param modo The mode to pass as the first argument to the gripper function.
 */
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
/**
 * Executes the 'aprendizaje' method on the given XmlRpcClient with the specified mode and file name.
 * Also includes the ID of the current Panel_cliente object as a parameter.
 * 
 * @param c The XmlRpcClient to execute the method on.
 * @param modo The mode to use for the aprendizaje method.
 * @param fileName The name of the file to use for the aprendizaje method.
 */
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
/**
 * Executes a tray file on the server.
 * @param c The XmlRpcClient object used to make the request.
 * @param fileName The name of the tray file to execute.
 */
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


/**
 * @brief Generates a report using an XmlRpcClient object.
 * 
 * @param c The XmlRpcClient object used to generate the report.
 */
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
/**
 * @brief Lists the tray of the client using an XmlRpcClient object.
 * 
 * @param c The XmlRpcClient object used to execute the 'listTray' method.
 */
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
/**
 * @brief Closes the client connection using the given XmlRpcClient object.
 * 
 * @param c The XmlRpcClient object to use for closing the connection.
 */
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
 