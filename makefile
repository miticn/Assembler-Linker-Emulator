

all: flex bison assembler emulator linker

assembler:
	g++ -o src/assembler src/assembler.cpp

emulator:
	g++ -o src/emulator src/emulator.cpp src/emulator_memory.cpp

linker:
	g++ -o src/linker src/linker.cpp

flex:
	flex -o misc/flex.yy.c misc/flex.l
	gcc -o misc/flex misc/flex.yy.c

bison:
	bison -d misc/bison.y
	gcc -o misc/bison misc/bison.tab.c

clean:
	rm -f misc/flex.yy.c misc/flex
	rm -f misc/bison.tab.c misc/bison.tab.h misc/bison
	rm -f src/assembler src/emulator src/linker
	
