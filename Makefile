NAME        = checkers
CC          = g++-4.6
CCFLAGS     = -std=c++0x -Wall -pedantic -Wno-long-long
SOURCES     = AIPlayer.cpp Console.cpp exceptions.cpp GameController.cpp KingPiece.cpp LocalPlayer.cpp MenPiece.cpp NetworkConnection.cpp NetworkPlayer.cpp Piece.cpp Player.cpp Savefile.cpp UIRenderer.cpp UIRendererCompatible.cpp UIRendererUnicode.cpp
OBJECTS     = $(SOURCES:.cpp=.o)

all: compile

compile: $(NAME)
	@echo Compiled sucessfully!

$(NAME): $(OBJECTS)
	@echo Linking and compiling main file...
	@$(CC) $(CCFLAGS) $^ src/main.cpp -o $@

%.o: src/%.cpp
	@echo "Compiling $< ..."
	@$(CC) $(CCFLAGS) -c $<

run:
	./$(NAME)

clean:
	rm -f $(OBJECTS) $(NAME)
	echo Directory cleaned.
