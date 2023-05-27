#include "Logger.hpp"

int main() {
    an::Logger logger("log.txt");
    logger.setLogLevel(an::LogLevel::Error);

    logger.logInfo("This is an info message");
    logger.logDebug("This is a debug message");
    logger.logError("This is an error message");

    return 0;
}
