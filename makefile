

all: flex bison assembler emulator linker

assembler: flex
	gcc -g -o src/assembler src/assembler.cpp misc/flex.cpp misc/bison.cpp src/literal_pool.cpp -lstdc++

emulator:
	gcc -g -o src/emulator src/emulator.cpp src/emulator_memory.cpp -lstdc++

linker:
	gcc -g -o src/linker src/linker.cpp src/linker_output.cpp -lstdc++

flex: bison
	flex misc/flex.l

bison:
	bison -d misc/bison.y


serialization_test:
	gcc -g src/setialization_test.cpp src/literal_pool.cpp src/section.cpp src/realocation.cpp -o ser_test -lstdc++

clean:
	rm -f misc/flex.yy.c misc/flex misc/flex.cpp misc/flex.hpp
	rm -f misc/bison.tab.c misc/bison.tab.h misc/bison misc/bison.cpp misc/bison.hpp
	rm -f src/assembler src/emulator src/linker
	rm -f ser_test
	
