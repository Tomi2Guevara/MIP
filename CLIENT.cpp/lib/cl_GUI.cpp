#include <iostream>
#include <string>
#include <sstream>
#include <fcntl.h>
#include <unistd.h>
#include <vector>

#include "cl_GUI.h"
#include "panel_cliente.h"

using namespace std;

// Trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// Trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// Trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

cl_GUI::cl_GUI() {

}

void cl_GUI::inicio(string puerto, string IP) {
    int ID;
    std::cout << "\n==========================================================================\n";
    std::cout << "\nBienvenido al panel de control del robot" << std::endl;
    std::cout << "Ingrese su ID: ";
    std::cin >> ID;
    Panel_cliente* cli = new Panel_cliente(ID, puerto, IP);
    this->cli = cli;
}

void cl_GUI::mostrarDatosCliente() {
    stringstream ss;
    ss << "\n-------CONEXION ESTABLECIDA-------\n";
    ss << "ID: " << cli->getID() << "\n";
    ss << "Puerto: " << cli->getPuerto() << "\n";
    ss << "IP: " << cli->getIP() << "\n";
    ss << "----------------------------------\n";
    std::cout<<ss.str();
}

void cl_GUI::msjError(string metodo) {
    std::cout << "Error al ejecutar " << metodo << std::endl;
}

void cl_GUI::setCliente(Panel_cliente* cliente) {
    this->cli = cliente;
}

void cl_GUI::loop2(XmlRpcClient c) {

    string command;
    string modo;
    string secondCommand;
    string fileCommand;
    vector<int> coordinates;

    string pipePath = "/Users/martinarobyculasso/Desktop/pipe/my_pipe";

    int fd = open(pipePath.c_str(), O_RDONLY);
    if (fd == -1) {
        cerr << "Error opening pipe." << endl;
    }

    while (true) {
        char buffer[256];
        ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            command = string(buffer);
            trim(command);  // Trim the command
            cout << "Received command: " << command << endl;

            // If the command is "movLineal", read a second command from the pipe
            if (command == "movLineal") {
                sleep(1);
                bytesRead = read(fd, buffer, sizeof(buffer) - 1);
                if (bytesRead > 0) {
                    buffer[bytesRead] = '\0';
                    secondCommand = string(buffer);
                    cout << "Received second command: " << secondCommand << endl;
                }
                } else if (command == "aprendizaje on" || command == "ejecutarTray") {
                sleep(1);
                bytesRead = read(fd, buffer, sizeof(buffer) - 1);
                if (bytesRead > 0) {
                    buffer[bytesRead] = '\0';
                    fileCommand = string(buffer);
                    trim(fileCommand);
                    cout << "Received second command: " << fileCommand << endl;
                }
            }

            if (command == "conectar") {
                cli->do_conectar(c);
            } else if (command == "desconectar") {
                cli->do_desconectar(c);
            } else if (command == "motores on") {
                modo = "on";
                cli->do_motores(c, modo);
            } else if (command == "motores off") {
                modo = "off";
                cli->do_motores(c, modo);
            } else if (command == "modo auto") {
                modo = "auto";
                cli->do_modo(c, modo);
            } else if (command == "modo manual") {
                modo = "manual";
                cli->do_modo(c, modo);
            } else if (command == "getPos") {
                cli->do_getPos(c);
            } else if (command == "homing") {
                cli->do_homing(c);
            } else if (command == "movLineal") {
                if (!secondCommand.empty()) {
                    coordinates.clear();
                    istringstream iss(secondCommand);
                    float coordinate;
                    while (iss >> coordinate) {
                        coordinates.push_back(coordinate);
                    }
                    if (coordinates.size() == 4) {
                        int x = coordinates[0], y = coordinates[1], z = coordinates[2], v = coordinates[3];
                        cli->do_movLineal(c, x, y, z, v);
                    } else {
                        cout << "Invalid number of coordinates." << endl;
                    }
                    secondCommand.clear(); // Clear the second command after using it
                } else {
                    cout << "No second command received." << endl;
                }
            } else if (command == "reporte") {
                cli->do_reporte(c);
            } else if (command == "gripper on") {
                modo = "on";
                cli->do_gripper(c, modo);
            } else if (command == "gripper off") {
                modo = "off";
                cli->do_gripper(c, modo);
            } else if (command == "aprendizaje on") {
//                std::cout << "Ingrese el nombre del archivo: ";
                cli->do_aprendizaje(c, "on", fileCommand);
            } else if (command == "aprendizaje off") {
                cli->do_aprendizaje(c, "off", "");
            } else if (command == "ejecutarTray") {
                std::cout << "Las trayectorias disponibles son: \n";
                cli->do_listTray(c);
//                std::cout << "Ingrese el nombre del archivo: ";
//                if (!fileCommand.empty()) {
//                    this->fileName = fileCommand;
//                    fileCommand.clear(); // Clear the second command after using it
//                } else {
//                    cout << "No second command received." << endl;
//                }
                cli->do_ejecutarTray(c, fileCommand);
            } else if (command == "salir") {
                cli->do_desconectar(c);
                cli->do_cerrarCliente(c);
                break;
            } else {
                std::cout << "Comando no reconocido\n";
            }
        }
    }
    close(fd);
}



//int cl_GUI::loop(XmlRpcClient c) {
//    string pipePath = "/Users/martinarobyculasso/Desktop/pipe/my_pipe";
//
//    int fd = open(pipePath.c_str(), O_RDONLY);
//    if (fd == -1) {
//        cerr << "Error opening pipe." << endl;
//        return 1;
//    }
//
//    string command;
//    string secondCommand;
//    while (true) {
//        char buffer[256];
//        ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
//        if (bytesRead > 0) {
//            buffer[bytesRead] = '\0';
//            command = string(buffer);
//            trim(command);  // Trim the command
//            cout << "Received command: " << command << endl;
//
//            // If the command is "movLineal", read a second command from the pipe
//            if (command == "movLineal") {
//                bytesRead = read(fd, buffer, sizeof(buffer) - 1);
//                if (bytesRead > 0) {
//                    buffer[bytesRead] = '\0';
//                    secondCommand = string(buffer);
//                    trim(secondCommand);  // Trim the command
//                    cout << "Received second command: " << secondCommand << endl;
//                } else if (command.substr(0, 9) == "fileName:") {
//                    // Extract the file name from the command
//                    this->fileName = command.substr(9);}
//
//                int opcion = 0;
//                string modo;
//                char cont;
//                char flag;
//                int e;
//                vector<float> coordinates;
//
//                try {
//                    while (opcion != 17) {
//                        trim(command);
//                        opcion = decode(command);
//
//                        switch (opcion) {
//                            case 1:
//                                cli->do_conectar(c);
//                                break;
//                            case 2:
//                                cli->do_desconectar(c);
//                                break;
//                            case 3:
//                                modo = "on";
//                                cli->do_motores(c, modo);
//                                break;
//                            case 4:
//                                modo = "off";
//                                cli->do_motores(c, modo);
//                                break;
//                            case 5:
//                                modo = "auto";
//                                cli->do_modo(c, modo);
//                                break;
//                            case 6:
//                                modo = "manual";
//                                cli->do_modo(c, modo);
//                                break;
//                            case 7:
//                                cli->do_getPos(c);
//                                break;
//                            case 8:
//                                cli->do_homing(c);
//                                break;
//                            case 9:
//                                if (!secondCommand.empty()) {
//                                    coordinates.clear();
//                                    istringstream iss(secondCommand);
//                                    float coordinate;
//                                    while (iss >> coordinate) {
//                                        coordinates.push_back(coordinate);
//                                    }
//                                    if (coordinates.size() == 4) {
//                                        float x = coordinates[0], y = coordinates[1], z = coordinates[2], v = coordinates[3];
//                                        cli->do_movLineal(c, x, y, z, v);
//                                    } else {
//                                        cout << "Invalid number of coordinates." << endl;
//                                    }
//                                    secondCommand.clear(); // Clear the second command after using it
//                                } else {
//                                    cout << "No second command received." << endl;
//                                }
//                                break;
//                            case 10:
//                                cli->do_reporte(c);
//                                break;
//                            case 11:
//                                //
//                                break;
//                            case 12:
//                                modo = "on";
//                                cli->do_gripper(c, modo);
//                                break;
//                            case 13:
//                                modo = "off";
//                                cli->do_gripper(c, modo);
//                                break;
//                            case 14:
//                                std::cout << "Ingrese el nombre del archivo: ";
//                                cli->do_aprendizaje(c, "on", this->fileName);
//                                break;
//                            case 15:
//                                cli->do_aprendizaje(c, "off", "");
//                                break;
//                            case 16:
//                                std::cout << "Las trayectorias disponibles son: \n";
//                                cli->do_listTray(c);
//                                std::cout << "Ingrese el nombre del archivo: ";
//                                cli->do_ejecutarTray(c, this->fileName);
//                                break;
//                            case 17:
//                                cli->do_desconectar(c);
//                                cli->do_cerrarCliente(c);
//                                break;
//
//                            default:
//                                std::cout << "Comando no reconocido\n";
//                                break;
//                        }
//                    }
//                } catch (const std::exception &e) {
//                    cout << "Error en la llamada a 'loop': " << e.what() << "\n\n";
//                    msjError("loop");
//                }
//            } else {
//                usleep(10000); // Sleep for 10 milliseconds
//            }
//        }
//
//        //close(fd);
//        return 0;
//    }
//}
//
//
//int cl_GUI::decode(string s) {
//    if (s == "conectar")
//        return 1;
//    if (s == "desconectar")
//        return 2;
//    if (s == "motores on")
//        return 3;
//    if (s == "motores off")
//        return 4;
//    if (s == "modo auto")
//        return 5;
//    if (s == "modo manual")
//        return 6;
//    if (s == "getPos")
//        return 7;
//    if (s == "homing")
//        return 8;
//    if (s == "movLineal")
//        return 9;
//    if (s == "reporte")
//        return 10;
//    if (s == "listCom")
//        return 11;
//    if (s == "gripper on")
//        return 12;
//    if (s == "gripper off")
//        return 13;
//    if (s == "aprendizaje on")
//        return 14;
//    if (s == "aprendizaje off")
//        return 15;
//    if (s == "ejecutarTray")
//        return 16;
//    if (s == "salir")
//        return 17;
//    if (s.substr(0, 9) == "fileName:") {
//        // Extract the file name from the command
//        fileName = s.substr(9);
//        return 19; // Return a custom code for file name received
//    }
//}





