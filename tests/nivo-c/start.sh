ASSEMBLER=../../assembler
LINKER=../../linker
EMULATOR=../../emulator

${ASSEMBLER} -o main.o main.s
${ASSEMBLER} -o handler.o handler.s
${ASSEMBLER} -o isr_terminal.o isr_terminal.s
${ASSEMBLER} -o isr_timer.o isr_timer.s
${LINKER} -hex \
  -place=code@0x40000000 \
  -o program.hex \
  isr_timer.o isr_terminal.o main.o handler.o  
${EMULATOR} program.hex