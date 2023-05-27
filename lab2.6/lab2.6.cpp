#include "Logger.hpp"

int main() {
    //std::cerr.rdbuf(std::cout.rdbuf());
    an::Logger logger("log.txt");
    logger.setLogLevel(an::LogLevel::Error);

    logger.logInfo("This is an info message");
    logger.logDebug("This is a debug message");
    logger.logError("This is an error message");

    return 0;
}