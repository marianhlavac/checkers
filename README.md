# Checkers

Seminar project for PA2 subject on FIT CTU written in C++. Basic checkers game with single player vs AI, local and network multiplayer modes.

## Screenshot

[![Screenshot of Checkers](http://goo.gl/HJJztm)](http://goo.gl/HJJztm)

## Requirements

 - g++ min. 4.6
 - sys/socket.h lib
 - netdb.h (definitions for network database operations ) lib
 - doxygen (optional)

## How to install

Compile the project using **make** tool.

    $ make

## How to run

If you want to play 1 vs 1 on local machine, it's the default mode, you can just

    $ ./checkers

For singleplayer game with AI, type

    $ ./checkers --versus-ai

For multiplayer game over network, hosting player will use

    $ ./checkers --versus-network --host --port [port]

and client will connect with

    $ ./checkers --versus-network --ip [ipaddress] --port [port]

Other options can be found in documentation. For example you can run the game with unicode renderer

    $ ./checkers --versus-ai --unicode

## Documentation

Generate documentation with command

    $ make doc

The documentation then can be find in doc/ directory.
