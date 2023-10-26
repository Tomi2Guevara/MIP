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
void do_aprendizaje(XmlRpcClient c, string modo, string fileName);
void do_ejecutarTray(XmlRpcClient c, string fileName);
void do_listTray(XmlRpcClient c);
void do_cerrarCliente(XmlRpcClient c);


//defino una constante para el ID
int ID;

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
  

  std::cout << "Ingrese el ID del cliente: ";
  std::cin >> ID;
  //creo un menu de usuario para que elija que metodo quiere ejecutar
  int opcion;
  string modo;
  string fileName;
  char cont;
  char flag;
  do
  {
    std::cout << "Ingrese el numero del metodo que desea ejecutar:\n";
    std::cout << "1. homing\n";
    std::cout << "2. conectar\n";
    std::cout << "3. desconectar\n";
    std::cout << "4. motores\n";
    std::cout << "5. modo\n";
    std::cout << "6. movLineal\n";
    std::cout << "7. getPos\n";
    std::cout << "8. listCom\n";
    std::cout << "9. reporte\n";
    std::cout << "10. gripper\n";
    std::cout << "11. aprendizaje\n";
    std::cout << "12. ejecutarTrayectoria\n";
    std::cout << "13. salir\n";
    std::cout << "Opcion: ";
    std::cin >> opcion;

    //limpio la pantalla
    system("cls");

    switch (opcion)
    {
    case 1:
      do_homing(c);
      break;
    case 2:
      do_conectar(c);
      break;
    case 3:
      do_desconectar(c);
      break;
    case 4:
      std::cout << "Ingrese el modo on|off: ";
      std::cin >> modo;
      do_motores(c, modo);
      break;
    case 5:
      std::cout << "Ingrese el modo auto|manual: ";
      std::cin >> modo;
      do_modo(c, modo);
      break;
    case 6:
      float x, y, z, v;
      std::cout << "Ingrese x: ";
      std::cin >> x;
      std::cout << "Ingrese y: ";
      std::cin >> y;
      std::cout << "Ingrese z: ";
      std::cin >> z;
      std::cout << "Desea especificar la velocidad? (s/n): ";
      std::cin>>flag;
      if (flag == 's'){
        std::cout << "Ingrese v: ";
        std::cin >> v;
        do_movLineal(c, x, y, z, v);
      }
      else
        do_movLineal(c, x, y, z);
      break;
    case 7:
      do_getPos(c);
      break;
    case 8:
      do_listCom(c);
      break;
    case 9:
      do_reporte(c);
      break;
    case 10:
      std::cout << "Ingrese el modo on|off: ";
      std::cin >> modo;
      do_gripper(c, modo);
      break;
    case 11:
      std::cout << "Ingrese el modo on|off: ";
      std::cin >> modo;
      if (modo == "on"){
        std::cout << "Ingrese el nombre del archivo donde va a guardar la trayectoria: ";
        std::cin >> fileName;}
      do_aprendizaje(c, modo, fileName);
      break;
    case 12:
      std::cout<<"las trayectorias disponibles son: \n";
      do_listTray(c);
      std::cout << "Ingrese el nombre del archivo: ";
      std::cin >> fileName;
      do_ejecutarTray(c, fileName);
      break;
    case 13:
      do_cerrarCliente(c);
      std::cout << "Saliendo...\n";
      break;
    default:
      std::cout << "Opcion incorrecta\n";
      break;
    }
    std::cout << "Presione cualquier tecla para continuar...";
    std::cin>>cont;
    system("cls");
  } while (opcion != 13);
 
  char salida;
  do_cerrarCliente(c);
  std::cout << "Ingrese cualquier caracter para salir...";
  std::cin >> salida;  
  return 0;
}

//---------------------------------------------------------------//
//--------FUNCIONES QUE LLAMAN A LOS METODOS DEL SERVIDOR--------//
//---------------------------------------------------------------//

void do_listCom(XmlRpcClient c)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = "remote";
  if (c.execute("listCom", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'listCom'\n\n";
}

//El ID (xxxx) lo defini como variable global para este codigo, pero se puede pasar como argumento a cada funcion
void do_conectar(XmlRpcClient c)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = "remote";
  oneArg[1] = ID;
  if (c.execute("conectar", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'conectar'\n\n";
}

void do_desconectar(XmlRpcClient c)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = "remote";
  oneArg[1] = ID;
  if (c.execute("desconectar", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'desconectar'\n\n";
}

//recibe modo on/off
void do_motores(XmlRpcClient c, string modo)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = modo;
  oneArg[1] = ID;
  if (c.execute("motores", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'motores'\n\n";
  
}

//recibe modo manual/auto
void do_modo(XmlRpcClient c, string modo)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = modo;
  oneArg[1] = ID; //se agrega el parametro "remote" para que el servidor sepa que el cliente es remoto
  if (c.execute("modo", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'modo'\n\n";
}

void do_getPos(XmlRpcClient c)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = "remote";
  oneArg[1] = ID;
  if (c.execute("getPos", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'getPos'\n\n";
}

void do_homing(XmlRpcClient c)
{
  XmlRpcValue oneArg,result;
  oneArg[0] = "remote";
  oneArg[1] = ID; 
  if (c.execute("homing", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'homing'\n\n";
}

void do_movLineal(XmlRpcClient c, float x, float y, float z, float v)
{
  XmlRpcValue fourArgs, result;
  fourArgs[0] = "remote";
  fourArgs[1] = ID;
  fourArgs[2] = x;
  fourArgs[3] = y;
  fourArgs[4] = z;
  fourArgs[5] = v;
  if (c.execute("movLineal", fourArgs, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'movLineal'\n\n";
}

void do_movLineal(XmlRpcClient c, float x, float y, float z)
{
  XmlRpcValue threeArgs, result;
  threeArgs[0] = "remote";
  threeArgs[1] = ID;
  threeArgs[2] = x;
  threeArgs[3] = y;
  threeArgs[4] = z;
  if (c.execute("movLineal", threeArgs, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'movLineal'\n\n";
  
}

//recibe modo on/off
void do_gripper(XmlRpcClient c, string modo)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = modo;
  oneArg[1] = ID;
  if (c.execute("gripper", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'gripper'\n\n";
}

//recibe modo on/off y nombre del archivo donde se guardara la trayectoria
void do_aprendizaje(XmlRpcClient c, string modo, string fileName)
{
  XmlRpcValue twoArgs, result;
  twoArgs[0] = modo;
  twoArgs[1] = fileName;
  twoArgs[2] = ID;
  if (c.execute("aprendizaje", twoArgs, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'aprendizaje'\n\n";
}

//recibe nombre del archivo a ejecutar en modo automatico
void do_ejecutarTray(XmlRpcClient c, string fileName)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = fileName;
  oneArg[1] = ID;
  if (c.execute("ejecutarTray", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'ejecutarTray'\n\n";
}


void do_reporte(XmlRpcClient c)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = "remoto";
  oneArg[1] = ID;
  if (c.execute("reporte", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'reporte'\n\n";
}

//lista las trayectorias disponibles para ejecutar
void do_listTray(XmlRpcClient c)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = "remoto";
  oneArg[1] = ID;
  if (c.execute("listTray", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'listTray'\n\n";
}

//libera la conexion del cliente
void do_cerrarCliente(XmlRpcClient c)
{
  XmlRpcValue oneArg, result;
  oneArg[0] = "remoto";
  oneArg[1] = ID;
  if (c.execute("cerrarCliente", oneArg, result))
    std::cout << result << "\n\n";
  else
    std::cout << "Error en la llamada a 'cerrarCliente'\n\n";
}