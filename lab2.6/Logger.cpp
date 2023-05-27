#include "Logger.hpp"

namespace an {

    Logger::Logger(const std::string& logFilePath) {
        m_logFile.open(logFilePath);
        m_logLevel = LogLevel::Info;    // default log level 
    }

    Logger::~Logger() {
        if (m_logFile.is_open()) {
            m_logFile.close();
        }
    }

    void Logger::setLogLevel(LogLevel level) {
        m_logLevel = level;
    }

    std::string Logger::getCurrentDateAndTime() const {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);

        char buffer[20];    // 19 символов + '/0'
        std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %X", std::localtime(&time));
        return buffer;
    }

    // time + log level
    std::string Logger::formatLogMessage(const std::string& message, LogLevel level) const {
        std::string formattedMessage = getCurrentDateAndTime() + " ";

        switch (level) {
        case LogLevel::Info:
            formattedMessage += "[INFO] ";
            break;
        case LogLevel::Debug:
            formattedMessage += "[DEBUG] ";
            break;
        case LogLevel::Error:
            formattedMessage += "[ERROR] ";
            break;
        default:
            break;
        }

        formattedMessage += message;
        return formattedMessage;
    }

    void Logger::logInfo(const std::string& message) {
        if (m_logLevel >= LogLevel::Info) {
            std::string formattedMessage = formatLogMessage(message, LogLevel::Info);
            std::cout << formattedMessage << std::endl;
            if (m_logFile.is_open()) {
                m_logFile << formattedMessage << std::endl;
            }
        }
    }

    void Logger::logDebug(const std::string& message) {
        if (m_logLevel >= LogLevel::Debug) {
            std::string formattedMessage = formatLogMessage(message, LogLevel::Debug);
            std::cout << formattedMessage << std::endl;
            if (m_logFile.is_open()) {
                m_logFile << formattedMessage << std::endl;
            }
        }
    }

    void Logger::logError(const std::string& message) {
        if (m_logLevel >= LogLevel::Error) {
            std::string formattedMessage = formatLogMessage(message, LogLevel::Error);
            std::cerr << formattedMessage << std::endl;
           
            if (m_logFile.is_open()) {
                m_logFile << formattedMessage << std::endl;
            }
        }
    }

}