FLAGS = -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused --no-exceptions --no-rtti --no-use-cxa-atexit -std=c++0x -O2 -Wall -Werror -fexceptions -Wsign-conversion

ifeq ($(OS),Windows_NT)
    EXE = .exe
    RM_CHECK := $(shell where.exe rm 2>nul)
    ifeq ($(RM_CHECK),)
        # Windows CMD / PowerShell (no rm available)
        CLEAN_CMD = -del /f /q *.o Chess$(EXE) 2>nul
        RUN_CMD = .\Chess$(EXE)
    else
        # Windows Unix-like shell (rm is available)
        CLEAN_CMD = rm -f *.o Chess$(EXE)
        RUN_CMD = ./Chess$(EXE)
    endif
else
    # Linux / macOS
    EXE =
    CLEAN_CMD = rm -f *.o Chess
    RUN_CMD = ./Chess
endif

Chess:
	g++ -c $(FLAGS) -Iinclude src/*.cpp
	g++ *.o -o Chess$(EXE)

all:
	$(MAKE) Chess

clean:
	$(CLEAN_CMD)

run:
	$(RUN_CMD)

valgrind:
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./Chess

xtermValgrind:
	xterm -e 'valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./Chess; read -n 1 -p "Press any key to finish..." "mainmenuinput"'

Debug: clean Chess xtermValgrind
