#ifndef STROOP_LOGGING_H
#define STROOP_LOGGING_H

#include <iostream>

enum wafelLogLevel : int {
    INFO = 0,
    WARNING,
    ERROR,
    SUCCESS
};

enum wafelSource : int {
    LEVELEDITOR = 0,
    IMPORT,
    EXPORT,
    SAVING,
    CONFIG,
    MAIN
};

inline void wafelLog(wafelLogLevel level, wafelSource source, const char *message) {
    switch (level) {
        case INFO:        std::cout << "\033[35m" << "[INFO] "  << "\033[0m"; break;
        case WARNING:     std::cout << "\033[33m" << "[WARNING] "  << "\033[0m"; break;
        case ERROR:       std::cout << "\033[31m" << "[ERROR] "  << "\033[0m"; break;
        case SUCCESS:     std::cout << "\033[92m" << "[SUCCESS] "  << "\033[0m"; break;
    }

    switch (source) {
        case LEVELEDITOR:      std::cout << "{LEVELEDITOR}: "; break;
        case IMPORT:           std::cout << "{IMPORT}: "; break;
        case EXPORT:           std::cout << "{EXPORT}: "; break;
        case SAVING:           std::cout << "{SAVING}: "; break;   
        case CONFIG:           std::cout << "{CONFIG}: "; break;  
        case MAIN:             std::cout << "{MAIN}: "; break;  
    }

    std::cout << message << std::endl;
};

#endif
