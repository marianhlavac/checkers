NAME        = checkers
CC          = g++
CCFLAGS     = -std=c++0x -Wall -pedantic -Wno-long-long -O0 -ggdb
SOURCES     = AIPlayer.cpp Console.cpp exceptions.cpp GameController.cpp KingPiece.cpp LocalPlayer.cpp MenPiece.cpp NetworkConnection.cpp NetworkPlayer.cpp Piece.cpp Player.cpp Savefile.cpp UIRenderer.cpp UIRendererCompatible.cpp UIRendererUnicode.cpp
OBJECTS     = $(SOURCES:.cpp=.o)

all: compile doc

compile: copysplash $(NAME)
	@echo Built. Compiled sucessfully!
	@echo "  - Run the game with './checkers' command"

$(NAME): $(OBJECTS)
	@echo Linking and compiling executable...
	@$(CC) $(CCFLAGS) $^ src/main.cpp -o $@

%.o: src/%.cpp
	@echo "Building object $< ..."
	@$(CC) $(CCFLAGS) -c $<

copysplash:
	@cp src/checkers-splash.txt ./checkers-splash.txt
	@echo "Splash file copied into build directory..."

run:
	@echo "This program requires parameters to start with options. See the documentation or readme."
	@echo "The program will start with default options..."
	@sleep 4
	@./$(NAME)

clean:
	@rm -f $(OBJECTS) $(NAME) checkers-splash.txt
	@echo Directory cleaned.

doc:
	@echo Generating documentation to directory doc/ , give me a second...
	@doxygen Doxyfile
	@echo Done
