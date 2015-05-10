cmake_minimum_required(VERSION 3.1)
project(PA2_LS2015_Semestralka)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(PA2_LS2015_Semestralka ${SOURCE_FILES} Player.cpp Player.h Console.cpp Console.h SingletonInstantiationException.cpp SingletonInstantiationException.h LocalPlayer.cpp LocalPlayer.h GameController.cpp GameController.h UIRenderer.cpp UIRenderer.h NetworkPlayer.cpp NetworkPlayer.h AIPlayer.cpp AIPlayer.h Piece.cpp Piece.h)