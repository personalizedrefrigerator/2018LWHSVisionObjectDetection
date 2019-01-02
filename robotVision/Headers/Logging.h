#pragma once

// Handles errors.
// This is used instead of std::cerr << "Error message" << error;
//to facilitate debugging.

// Methods are named after JavaScript console.*
//methods.

//FOR AN ERROR
// Method "error".
// This logger should output (and possibly later store)
//information regarding each error including:
// * The area in which the error occured.
// * A short description of the error.
// * Errno and its meaning (even if 0 -- a success).

//FOR A WARNING
// Method "warn".
// Output the message, check and output errno.

//FOR A MESSAGE
// Method "log".
// Output the message to standard out.

// Standard library headers.
#include <string>
#include <iostream>
#include <sstream>

// C Libraries.
#include <errno.h> // Variable errno.
#include <cstring> // std::strerror

// Note:
// These headers are linux/unix-specific.
//This will cause failure on non-linux/unix
//systems.
// * Possibly errno.h.

namespace Logging
{
    enum class TerminalStyle { BOLD, UNDERLINE, END_BOLD, END_UNDERLINE,
        FG_RED, FG_YELLOW, FG_GREEN, NORMAL }; // FG stands for foreground.

    std::string getFormattedErrnoInfo(int errnoToCheck);
    std::string getFormattedErrnoInfo();
    std::string getSetStyleCode(const TerminalStyle& color);

    class Logger : public std::ostream
    {
        protected:
        bool multiLine;
        bool isInStream;

        public:
        Logger() : multiLine(true), isInStream(false) {};
        Logger(bool newMultiLine) : multiLine(newMultiLine), isInStream(false) { };

        virtual void log(const std::string&) = 0;

        template <typename T>
        inline void operator()(const T& arg);

        void setMultiLine(bool newMultiLine) { multiLine = newMultiLine; };
        bool getMultiLine() { return multiLine; };

        void setInStream(bool nowInStream) { isInStream = nowInStream; };
    };

    template <typename T>
    Logger& operator<<(Logger& logger, const T& other)
    {
        bool oldMultiLine = logger.getMultiLine();
        logger.setMultiLine(false);
        logger.setInStream(true);

        logger.operator()(other);

        logger.setInStream(false);
        logger.setMultiLine(oldMultiLine);

        return logger;
    }

    class ErrorLogger : public Logger
    {
        public:
        virtual void log(const std::string&) override;
        void log(const std::string& location, const std::string& description, const std::string& potentialIssues);
        void operator()(const std::string& location, const std::string& description, const std::string& potentialIssues);
    };

    class WarningLogger : public Logger
    {
        public:
        void log(const std::string&) override;
    };

    class NoticeLogger : public Logger
    {
        public:
        void log(const std::string&) override;
    };

    template <typename T>
    void Logger::operator()(const T& arg)
    {
        std::stringstream conversionStream;
        conversionStream << arg;

        log(conversionStream.str());
    }

    // Static is not used here. In C++, static means
    //only to be refrenced in this file. Extern means
    //the variable is defined elsewhere, but declared
    //here.
    //https://stackoverflow.com/questions/11478152/how-to-work-with-variable-in-namespace
    extern ErrorLogger error;
    extern WarningLogger warn;
    extern NoticeLogger log;

    extern std::string endl;
}