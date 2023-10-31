/* holaServer.cpp : ejemplo sencillo de servidor XMLRPC. 
   Uso: holaServer Port
*/
#include <windows.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
#include "libreria/XmlRpc.h"
using namespace XmlRpc;

// S es el servidor
XmlRpcServer S; // Se crea un servidor XMLRPC sobre el puerto indicado en la linea de comandos (por defecto 8080) y se pone a la escucha de requerimientos XMLRPC en un bucle infinito. 

// Sin argumentos, el resultado es "Hola".
class Saludo : public XmlRpcServerMethod // Se crea una clase derivada de XmlRpcServerMethod que implementa el método Saludo del servidor XMLRPC. 
{
public:
  Saludo(XmlRpcServer* S) : XmlRpcServerMethod("Saludo", S) {} // Se crea un método XMLRPC con nombre "Saludo" y se registra en el servidor S. 

  void execute(XmlRpcValue& params, XmlRpcValue& result) // Se implementa el método execute que es llamado por el servidor cuando se recibe una llamada XMLRPC al método "Saludo".
  {
    result = "Hola";
  }

  std::string help() { return std::string("Diga Hola"); } // Se implementa el método help que es llamado por el servidor cuando se recibe una llamada XMLRPC al método "system.methodHelp".

} saludo(&S);    // Este constructor registra el método en el servidor


// Con un argumento, el resultado es "Hola, " + argumento
class SaludoNombre : public XmlRpcServerMethod
{
public:
  SaludoNombre(XmlRpcServer* S) : XmlRpcServerMethod("SaludoNombre", S) {}

  void execute(XmlRpcValue& params, XmlRpcValue& result)
  {
    std::string resultString = "Hola, ";
    resultString += std::string(params[0]);
    result = resultString;
  }
} saludoNombre(&S);


// Con un numero variable de argumento, todos dobles, el resultado es la suma
class Sumar : public XmlRpcServerMethod
{
public:
  Sumar(XmlRpcServer* S) : XmlRpcServerMethod("Sumar", S) {}

  void execute(XmlRpcValue& params, XmlRpcValue& result)
  {
    int nArgs = params.size(); // Se obtiene el numero de argumentos
    double sum = 0.0;
    for (int i=0; i<nArgs; ++i)
      sum += double(params[i]); // Se suman los argumentos
    result = sum;
  }
} sumar(&S);



int main(int argc, char* argv[])
{
  if (argc != 2) { //para iniciar el servidor se debe indicar el puerto: hola_server.exe 8080, con esto argc = 2 y argv[1] = 8080
    std::cerr << "Uso: hola_server N_Port\n"; // Se comprueba que se ha indicado el puerto en la linea de comandos y se muestra un mensaje de error si no es así. 
    return -1;
  }
  int port = atoi(argv[1]);

  XmlRpc::setVerbosity(5); // Se establece el nivel de verbosidad del servidor XMLRPC (0 es el mínimo y 5 el máximo)
  //el nivel de verbosidad es el nivel de detalle de los mensajes que se muestran en la consola del servidor cuando se recibe una llamada XMLRPC.
  //Nivel 0: no se muestra nada
  //Nivel 1: se muestra el nombre del método XMLRPC que se ha llamado
  //Nivel 2: se muestra el nombre del método XMLRPC que se ha llamado y los argumentos que se han pasado
  //Nivel 3: se muestra el nombre del método XMLRPC que se ha llamado, los argumentos que se han pasado y el resultado que se devuelve
  //Nivel 4: se muestra el nombre del método XMLRPC que se ha llamado, los argumentos que se han pasado, el resultado que se devuelve y el tiempo que ha tardado en ejecutarse el método
  //Nivel 5: se muestra el nombre del método XMLRPC que se ha llamado, los argumentos que se han pasado, el resultado que se devuelve, el tiempo que ha tardado en ejecutarse el método y el número de llamadas que se han recibido al método


  // Se crea un socket de servidor sobre el puerto indicado
  S.bindAndListen(port);
  //un socket es un punto extremo de un enlace de comunicación bidireccional entre dos programas que se ejecutan en la red.
  //bindAndListen() crea un socket de servidor y lo pone a la escucha de requerimientos XMLRPC en el puerto indicado.
  //El servidor se queda bloqueado en esta llamada hasta que recibe un requerimiento XMLRPC.


  // Enable introspection
  S.enableIntrospection(true); // Se habilita la introspección. La introspección es un mecanismo que permite obtener información sobre los métodos XMLRPC que se han registrado en el servidor.
  //Cuando se habilita la introspección, el servidor XMLRPC crea un método XMLRPC llamado "system.listMethods" que devuelve una lista con los nombres de todos los métodos XMLRPC que se han registrado en el servidor.
  //También crea un método XMLRPC llamado "system.methodHelp" que devuelve una cadena de texto con la descripción del método XMLRPC que se ha pasado como argumento.


  // A la escucha de requerimientos
  S.work(-1.0);// Se pone a la escucha de requerimientos XMLRPC en un bucle infinito.

  return 0;
}
 
