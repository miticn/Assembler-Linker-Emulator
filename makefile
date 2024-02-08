

all: flex bison assembler emulator linker

assembler: flex
	gcc -g -o assembler src/assembler.cpp misc/flex.cpp misc/bison.cpp src/literal_pool.cpp -lstdc++

emulator:
	gcc -g -pthread -o emulator src/emulator.cpp src/emulator_memory.cpp src/terminal.cpp -lstdc++

linker: src/linker.cpp src/linker_output.cpp
	gcc -g -o linker src/linker.cpp src/linker_output.cpp -lstdc++

flex: bison
	flex misc/flex.l

bison:
	bison -d misc/bison.y


serialization_test:
	gcc -g src/setialization_test.cpp src/literal_pool.cpp src/section.cpp src/realocation.cpp -o ser_test -lstdc++

clean:
	rm -f misc/flex.yy.c misc/flex misc/flex.cpp misc/flex.hpp
	rm -f misc/bison.tab.c misc/bison.tab.h misc/bison misc/bison.cpp misc/bison.hpp
	rm -f assembler emulator linker
	rm -f ser_test
	rm -f -r tests/nivo-a/*.o
	rm -f -r tests/nivo-b/*.o
	rm -f -r tests/nivo-c/*.o
	rm -f -r tests/nivo-a/*.hex
	rm -f -r tests/nivo-b/*.hex
	rm -f -r tests/nivo-c/*.hex
	
