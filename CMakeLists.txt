cmake_minimum_required(VERSION 3.16)
project(TicTacToe)

#set(CMAKE_AUTOUIC ON) #this is for #include <ui_UINAME.h> and adding a UINAME.ui file
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
set(CMAKE_STANDARD 23)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

#find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)


# This would make a target, named TicTacToe, which is a bunch of resources and libraries
add_executable(${PROJECT_NAME} "main.cpp")
# set_target_properties(TicTacToe PROPERTIES
#     WIN32_EXECUTABLE TRUE
# )
#target_link_libraries(TicTacToe PUBLIC
 #   Qt6::Core
#)
