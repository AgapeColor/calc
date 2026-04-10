#include "runner.h"
#include "logger.h"

#include <exception>
#include <iostream>

int main(int argc, char** argv) {
    try {
        Runner appRunner;
        appRunner.run(argc, argv);
        return 0;
    }
    catch (const std::exception& e) {
        Logger::instance().error(std::string("Fatal error: ") + e.what());
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
