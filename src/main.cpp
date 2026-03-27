#include "runner.h"
#include <exception>
#include <iostream>

int main(int argc, char** argv) {
    try {
        run(argc, argv);
        return 0;
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
