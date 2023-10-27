cmake_minimum_required(VERSION 3.26)
project(intProyect)

set(CMAKE_CXX_STANDARD 14)

include_directories(client20.cpp/libreria)

add_executable(intProyect
        client20.cpp/libreria/base64.h
        client20.cpp/libreria/hola_client.cpp
        client20.cpp/libreria/XmlRpc.h
        client20.cpp/libreria/XmlRpcClient.cpp
        client20.cpp/libreria/XmlRpcClient.h
        client20.cpp/libreria/XmlRpcDispatch.cpp
        client20.cpp/libreria/XmlRpcDispatch.h
        client20.cpp/libreria/XmlRpcException.h
        client20.cpp/libreria/XmlRpcServer.cpp
        client20.cpp/libreria/XmlRpcServer.h
        client20.cpp/libreria/XmlRpcServerConnection.cpp
        client20.cpp/libreria/XmlRpcServerConnection.h
        client20.cpp/libreria/XmlRpcServerMethod.cpp
        client20.cpp/libreria/XmlRpcServerMethod.h
        client20.cpp/libreria/XmlRpcSocket.cpp
        client20.cpp/libreria/XmlRpcSocket.h
        client20.cpp/libreria/XmlRpcSource.cpp
        client20.cpp/libreria/XmlRpcSource.h
        client20.cpp/libreria/XmlRpcUtil.cpp
        client20.cpp/libreria/XmlRpcUtil.h
        client20.cpp/libreria/XmlRpcValue.cpp
        client20.cpp/libreria/XmlRpcValue.h
        client20.cpp/client_original.cpp
        client20.cpp/hola_server.cpp
        client20.cpp/xml_rpc_test_01.zpr)
