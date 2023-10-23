/* holaClient.cpp : ejemplo sencillo de cliente XMLRPC. 
*/

// Acuerdense de guardar antes de compilar!!!!


#include <windows.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
#include "XmlRpc.h"
using namespace XmlRpc;

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



int main(int argc, char* argv[])
{
  if (argc != 3) {
    std::cerr << "Uso: hola_Client IP_HOST N_PORT\n"; // se debe indicar la IP y el puerto del servidor
    return -1;
  }
  
  int port = atoi(argv[2]);
  //XmlRpc::setVerbosity(5);

  // Una mirada a los métodos soportados por la API
  XmlRpcClient c(argv[1], port); //se crea un cliente XMLRPC para conectarse al servidor indicado en la linea de comandos
  XmlRpcValue noArgs, result; //se crean dos variables de tipo XmlRpcValue para almacenar los argumentos y el resultado de las llamadas XMLRPC
  

  // Requerimiento a la API para recuperar una ayuda sobre el método Saludo
  XmlRpcValue oneArg;
  oneArg[0] = "remote";
  

  // Llamada al metodo Saludo
  if (c.execute("status", noArgs, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'status'\n\n";

  // Llamada al metodo list
  oneArg[0] = "remote"; 
  if (c.execute("list", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'list'\n\n";

  // Llamada al metodo conectar
  do_listCom(c);
  do_modo(c, "auto");
  do_modo(c, "manual");
  do_conectar(c);
  do_motores(c, "on");
  do_homing(c);
  do_gripper(c, "on");
  do_gripper(c, "off");
  do_movLineal(c, 53.1, 82.1, 54.1, 25);
  do_movLineal(c, 100.1, 56.1, 200.1);
  do_getPos(c);
  do_reporte(c);
  do_motores(c, "off");
  do_desconectar(c);

  // llamada al metodo suma, recibe dos numeros como parametros y devuelve la suma de ellos
  XmlRpcValue twoArgs;
  twoArgs[0] = 1;
  twoArgs[1] = 2;
  twoArgs[2] = 3;
  if (c.execute("suma", twoArgs, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'suma'\n\n";

  char salida;
  cout << "Ingrese cualquier caracter para salir...";
  cin >> salida;  
  return 0;
}



//ESTO HAY QUE HACERLO CON TODOS LOS METODOS
// Llamada al metodo homing implementada en una funcion
void do_homing(XmlRpcClient c)
{
  XmlRpcValue oneArg,result;
  oneArg[0] = "remote";
  if (c.execute("homing", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'homing'\n\n";
}

void do_conectar(XmlRpcClient c)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = "remote";
  if (c.execute("conectar", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'conectar'\n\n";
}

void do_desconectar(XmlRpcClient c)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = "remote";
  if (c.execute("desconectar", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'desconectar'\n\n";
}

void do_motores(XmlRpcClient c, string modo)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = modo;
  if (c.execute("motores", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'motores'\n\n";
  
}

void do_modo(XmlRpcClient c, string modo)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = modo;
  if (c.execute("modo", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'modo'\n\n";
}

void do_movLineal(XmlRpcClient c, float x, float y, float z, float v)
{
  XmlRpcValue fourArgs, result;
  fourArgs[0] = x;
  fourArgs[1] = y;
  fourArgs[2] = z;
  fourArgs[3] = v;
  if (c.execute("movLineal", fourArgs, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'movLineal'\n\n";
}
void do_movLineal(XmlRpcClient c, float x, float y, float z)
{
  XmlRpcValue threeArgs, result;
  threeArgs[0] = x;
  threeArgs[1] = y;
  threeArgs[2] = z;
  if (c.execute("movLineal", threeArgs, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'movLineal'\n\n";
  
}

void do_getPos(XmlRpcClient c)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = "remote";
  if (c.execute("getPos", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'getPos'\n\n";
}

void do_listCom(XmlRpcClient c)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = "remote";
  if (c.execute("listCom", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'listCom'\n\n";
}

void do_reporte(XmlRpcClient c)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = "remote";
  if (c.execute("reporte", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'reporte'\n\n";
}

void do_gripper(XmlRpcClient c, string modo)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = modo;
  if (c.execute("gripper", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'gripper'\n\n";
}