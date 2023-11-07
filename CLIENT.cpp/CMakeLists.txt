cmake_minimum_required(VERSION 3.26)
project(client20_cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(lib)

add_executable(client20_cpp
        lib/base64.h
        lib/cl_GUI.cpp
        lib/cl_GUI.h
        lib/cliente_main_gui.cpp
        lib/panel_cliente.cpp
        lib/panel_cliente.h
        lib/XmlRpc.h
        lib/XmlRpcClient.cpp
        lib/XmlRpcClient.h
        lib/XmlRpcDispatch.cpp
        lib/XmlRpcDispatch.h
        lib/XmlRpcException.h
        lib/XmlRpcServer.cpp
        lib/XmlRpcServer.h
        lib/XmlRpcServerConnection.cpp
        lib/XmlRpcServerConnection.h
        lib/XmlRpcServerMethod.cpp
        lib/XmlRpcServerMethod.h
        lib/XmlRpcSocket.cpp
        lib/XmlRpcSocket.h
        lib/XmlRpcSource.cpp
        lib/XmlRpcSource.h
        lib/XmlRpcUtil.cpp
        lib/XmlRpcUtil.h
        lib/XmlRpcValue.cpp
        lib/XmlRpcValue.h)
