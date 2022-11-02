cmake_minimum_required(VERSION 3.23)
project(tarea2multi)

set(CMAKE_CXX_STANDARD 14)

include_directories(control/src)
include_directories(control/src/control_autogen)
include_directories(control/src/control_autogen/include)

add_executable(tarea2multi
        control/src/control_autogen/EWIEGA46WW/moc_genericmonitor.cpp
        control/src/control_autogen/EWIEGA46WW/moc_genericworker.cpp
        control/src/control_autogen/EWIEGA46WW/moc_specificmonitor.cpp
        control/src/control_autogen/EWIEGA46WW/moc_specificworker.cpp
        control/src/control_autogen/include/moc_sigwatch.cpp
        control/src/control_autogen/moc_predefs.h
        control/src/control_autogen/mocs_compilation.cpp
        control/src/CommonBehavior.cpp
        control/src/CommonBehavior.h
        control/src/commonbehaviorI.cpp
        control/src/commonbehaviorI.h
        control/src/config.h
        control/src/DifferentialRobot.cpp
        control/src/DifferentialRobot.h
        control/src/DifferentialRobotMulti.cpp
        control/src/DifferentialRobotMulti.h
        control/src/GenericBase.cpp
        control/src/GenericBase.h
        control/src/genericmonitor.cpp
        control/src/genericmonitor.h
        control/src/genericworker.cpp
        control/src/genericworker.h
        control/src/Laser.cpp
        control/src/Laser.h
        control/src/LaserMulti.cpp
        control/src/LaserMulti.h
        control/src/main.cpp
        control/src/specificmonitor.cpp
        control/src/specificmonitor.h
        control/src/specificworker.cpp
        control/src/specificworker.h
        control/src/ui_mainUI.h)
