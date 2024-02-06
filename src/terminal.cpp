#include "../inc/terminal.hpp"
volatile bool Terminal::running = false;
pthread_t Terminal::inputThread = 0;
volatile bool Terminal::inputReady = false;
EmulatorMemory *Terminal::em = nullptr;
