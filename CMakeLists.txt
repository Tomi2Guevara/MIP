cmake_minimum_required(VERSION 3.26)
project(intProyect)

set(CMAKE_CXX_STANDARD 14)

include_directories(robotArm_v0.63)

add_executable(intProyect
        client20.cpp/client_original.cpp
        client20.cpp/hola_server.cpp
        robotArm_v0.63/byj_gripper.cpp
        robotArm_v0.63/byj_gripper.h
        robotArm_v0.63/command.cpp
        robotArm_v0.63/command.h
        robotArm_v0.63/config.h
        robotArm_v0.63/endstop.cpp
        robotArm_v0.63/endstop.h
        robotArm_v0.63/equipment.cpp
        robotArm_v0.63/equipment.h
        robotArm_v0.63/fanControl.cpp
        robotArm_v0.63/fanControl.h
        robotArm_v0.63/interpolation.cpp
        robotArm_v0.63/interpolation.h
        robotArm_v0.63/logger.cpp
        robotArm_v0.63/logger.h
        robotArm_v0.63/pinout.h
        robotArm_v0.63/pinout_uno.h
        robotArm_v0.63/queue.h
        robotArm_v0.63/RampsStepper.cpp
        robotArm_v0.63/RampsStepper.h
        robotArm_v0.63/robotArm_v0.63.ino
        robotArm_v0.63/robotGeometry.cpp
        robotArm_v0.63/robotGeometry.h
        robotArm_v0.63/servo_gripper.cpp
        robotArm_v0.63/servo_gripper.h
        client20.cpp/panel_cliente.h)
