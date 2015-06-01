NAME        = checkers
CC          = g++
CCFLAGS     = -std=c++0x -Wall -pedantic -Wno-long-long
SOURCES     = src/AIPlayer.cpp src/Console.cpp src/exceptions.cpp src/GameController.cpp src/KingPiece.cpp src/LocalPlayer.cpp src/MenPiece.cpp src/NetworkConnection.cpp src/NetworkPlayer.cpp src/Piece.cpp src/Player.cpp src/Savefile.cpp src/UIRenderer.cpp src/UIRendererCompatible.cpp src/UIRendererUnicode.cpp
OBJECTS     = $(SOURCES:.cpp=.o)

compile: $(NAME)
	@echo Compiled sucessfully!

$(NAME): $(OBJECTS)
	@echo Linking...
	$(CC) $(CCFLAGS) $^ -o $@

%.o: %.cpp
	@echo "Compiling $< ..."
	$(CC) $(CCFLAGS) -c $<

clean:
	rm -f $(OBJS) $(NAME)
	echo Directory cleaned.