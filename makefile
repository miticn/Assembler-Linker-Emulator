

all: flex bison assembler emulator linker

assembler: flex
	g++ -o src/assembler src/assembler.cpp misc/flex.cpp misc/bison.cpp

emulator:
	g++ -o src/emulator src/emulator.cpp src/emulator_memory.cpp

linker:
	g++ -o src/linker src/linker.cpp

flex: bison
	flex misc/flex.l

bison:
	bison -d misc/bison.y

clean:
	rm -f misc/flex.yy.c misc/flex misc/flex.cpp misc/flex.hpp
	rm -f misc/bison.tab.c misc/bison.tab.h misc/bison misc/bison.cpp misc/bison.hpp
	rm -f src/assembler src/emulator src/linker
	
