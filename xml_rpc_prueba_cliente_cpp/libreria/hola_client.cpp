/* holaClient.cpp : ejemplo sencillo de cliente XMLRPC. 
   Uso: holaCliente Host Port
   Nota: sobre Windows puede faltar ws2_32.lib, para poder crear los sockets
*/
#include <windows.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
#include "XmlRpc.h"
using namespace XmlRpc;

void do_homing(XmlRpcClient c);

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

  //Llamada al metodo connect
  oneArg[0] = "remote";
  if (c.execute("connect", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'connect'\n\n";

  // Llamada al metodo homing
  // oneArg[0] = "remote";
  // if (c.execute("homing", oneArg, result))
  //   std::cout << result << "\n\n";
  // else
  //   std::cout << "Error en la llamada a 'homing'\n\n";
  do_homing(c);

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


