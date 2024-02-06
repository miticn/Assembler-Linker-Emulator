#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>

#include "../inc/emulator_memory.hpp"

class Terminal{
public:
    static pthread_t inputThread;
    static volatile bool running;
    static volatile bool inputReady;
    static EmulatorMemory *em;
    // Function to enable raw mode for terminal
    static void enableRawMode() {
        struct termios raw;
        tcgetattr(STDIN_FILENO, &raw);
        raw.c_lflag &= ~(ECHO | ICANON); // Turn off echo and canonical mode
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    }

    // Function to disable raw mode and restore the terminal to normal mode
    static void disableRawMode() {
        struct termios original;
        tcgetattr(STDIN_FILENO, &original);
        original.c_lflag |= (ECHO | ICANON);
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
    }

    static void *readInput(void *arg) {
        char c;
        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK); // Set non-blocking mode

        while (running) {
            ssize_t bytes_read = read(STDIN_FILENO, &c, 1);
            if (bytes_read > 0) {
                if (em != nullptr) {
                    em->term_in_reg = c;
                    inputReady = true;
                } else {
                    printf("Terminal: Emulator Memory pointer not set.\n");
                }
            }
        }
        pthread_exit(NULL);
    }

    static void createThreadAndRun() {
        Terminal::enableRawMode();
        if (pthread_create(&inputThread, NULL, Terminal::readInput, NULL) != 0) {
            perror("pthread_create");
            exit(1);
        }
        running = true;
    }

    static void stopThread() {
        running = false;
        pthread_join(inputThread, NULL);
        Terminal::disableRawMode();
    }

};