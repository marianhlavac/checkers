cmake_minimum_required(VERSION 3.1)
project(Checkers)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp)
add_executable(PA2_LS2015_Semestralka ${SOURCE_FILES} src/Player.cpp src/Player.h src/Console.cpp src/Console.h src/SingletonInstantiationException.cpp src/SingletonInstantiationException.h src/LocalPlayer.cpp src/LocalPlayer.h src/GameController.cpp src/GameController.h src/UIRenderer.cpp src/UIRenderer.h src/NetworkPlayer.cpp src/NetworkPlayer.h src/AIPlayer.cpp src/AIPlayer.h src/Piece.cpp src/Piece.h src/UIRendererUnicode.cpp src/UIRendererUnicode.h src/MenPiece.cpp src/MenPiece.h src/KingPiece.cpp src/KingPiece.h src/ConsoleParsingErrorException.cpp src/ConsoleParsingErrorException.h)