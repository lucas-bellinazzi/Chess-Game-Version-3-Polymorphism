FLAGS = -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused --no-exceptions --no-rtti --no-use-cxa-atexit -std=c++0x -O2 -Wall -Werror -fexceptions -Wsign-conversion

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp,obj/%.o,$(SRCS))

ifeq ($(OS),Windows_NT)
    EXE = .exe
    RM_CHECK := $(shell where.exe rm 2>nul)
    ifeq ($(RM_CHECK),)
        # Windows CMD / PowerShell (no rm available)
        CLEAN_CMD = -del /f /q Chess$(EXE) 2>nul & if exist obj rmdir /s /q obj
        RUN_CMD = .\Chess$(EXE)
        MKDIR_CMD = if not exist obj mkdir obj
    else
        # Windows Unix-like shell (rm is available)
        CLEAN_CMD = rm -rf obj Chess$(EXE)
        RUN_CMD = ./Chess$(EXE)
        MKDIR_CMD = mkdir -p obj
    endif
else
    # Linux / macOS
    EXE =
    CLEAN_CMD = rm -rf obj Chess$(EXE)
    RUN_CMD = ./Chess$(EXE)
    MKDIR_CMD = mkdir -p obj
endif

Chess: $(OBJS)
	g++ $(OBJS) -o Chess$(EXE)

obj/%.o: src/%.cpp | obj
	g++ -c $(FLAGS) -Iinclude $< -o $@

obj:
	$(MKDIR_CMD)

all:
	$(MAKE) Chess

clean:
	$(CLEAN_CMD)

run:
	$(RUN_CMD)

valgrind:
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./Chess$(EXE)

xtermValgrind:
	xterm -e 'valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./Chess$(EXE); read -n 1 -p "Press any key to finish..." "mainmenuinput"'

Debug: clean Chess xtermValgrind
