/* holaClient.cpp : ejemplo sencillo de cliente XMLRPC. 
   Uso: holaCliente Host Port
   Nota: sobre Windows puede faltar ws2_32.lib, para poder crear los sockets
*/
#include <windows.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
#include "libreria/XmlRpc.h"
using namespace XmlRpc;

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
  if (c.execute("system.listMethods", noArgs, result))//si se ejecuta correctamente el metodo "system.listMethods" se muestra el resultado
    std::cout << "\nMetodos:\n " << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'listMethods'\n\n";

  // Requerimiento a la API para recuperar una ayuda sobre el método Saludo
  XmlRpcValue oneArg;
  oneArg[0] = "Saludo";
  if (c.execute("system.methodHelp", oneArg, result)) //si se ejecuta correctamente el metodo "system.methodHelp" se muestra el resultado
    std::cout << "Ayuda para el metodo 'Saludo': " << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'methodHelp'\n\n";

  // Llamada al metodo Saludo
  if (c.execute("Saludo", noArgs, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'Saludo'\n\n";

  // Llamada al metodo SaludoNombre
  oneArg[0] = "Programador";
  if (c.execute("SaludoNombre", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'SaludoNombre'\n\n";

  // Llamada con un array de numeros
  XmlRpcValue numbers;
  numbers[0] = 33.33;
  numbers[1] = 112.57;
  numbers[2] = 76.1;
  std::cout << "numbers.size() is " << numbers.size() << std::endl;
  if (c.execute("Sumar", numbers, result))
    std::cout << "Suma = " << double(result) << "\n\n";
  else
    std::cout << "Error en la llamada a 'Sumar'\n\n";

  // Prueba de fallo por llamada a metodo inexistente
  if (c.execute("OtroMetodo", numbers, result))
    std::cout << "Llamada a OtroMetodo: fallo: " << c.isFault() << ", resultado = " << result << std::endl;
  else
    std::cout << "Error en la llamada a 'Sumar'\n";
    //esto es lo que se muestra en la consola si se ejecuta el metodo "OtroMetodo", el cual no existe en el servidor XMLRPC, 

  // Prueba de llamada a metodos multiples. 
  // En este caso se trata de argumento unico, un array de estructuras
  XmlRpcValue multicall;//se crea una variable de tipo XmlRpcValue para almacenar los argumentos de la llamada multicall
  multicall[0][0]["methodName"] = "Sumar";//esta linea indica que se va a llamar al metodo "Sumar", el cual recibe dos argumentos,[0][0] indica que es el primer argumento y [0][1] el segundo argumento
  multicall[0][0]["params"][0] = 5.0;
  multicall[0][0]["params"][1] = 9.0;

  multicall[0][1]["methodName"] = "SaludoNombre";//esta linea indica que se va a llamar al metodo "SaludoNombre", el cual recibe un argumento
  multicall[0][1]["params"][0] = "Juan";
    
  multicall[0][2]["methodName"] = "Sumar";//esta linea indica que se va a llamar al metodo "Sumar", el cual recibe dos argumentos
  multicall[0][2]["params"][0] = 10.5;
  multicall[0][2]["params"][1] = 12.5;


  if (c.execute("system.multicall", multicall, result)) //si se ejecuta correctamente el metodo "system.multicall" se muestra el resultado
    std::cout << "\nResultado multicall = " << result << std::endl;
  else
    std::cout << "\nError en la llamada a 'system.multicall'\n";

  char salida;
  cout << "Ingrese cualquier caracter para salir...";
  cin >> salida;  
  return 0;
}
