#include "Logger.h"

#include <QTime>
#include <QMetaType>
#include <iostream>

namespace
{
    std::string getLoggerPath()
    {
        static std::string path = QString(QString("%1/IntelligibleWM.log").arg(QDir::tempPath())).toStdString();

        return path;
    }
}

namespace IntelligibleWM
{
    Logger::Logger()
    {
        std::string path = getLoggerPath();
        _file = new QFile(QString::fromStdString(path));
        /**
         * delete file if it size more than 1mb
         */
        if (_file->exists() && _file->size() > 1024 * 1024) {
            _file->copy(QString::fromStdString(path).append("-"+QDate::currentDate().toString("yyyy-MM-dd")));
        }
    }

    Logger::~Logger()
    {
    }

    // void Logger::print(const char *mess, mongocxx::log_level level, bool notify)
    // {
    //     print(std::string(mess), level, notify);
    // }

    // void Logger::print(const std::string &mess, mongocxx::log_level level, bool notify)
    // {
    //     print(QString::fromStdString(mess), level, notify);
    // }

    // void Logger::print(const QString &mess, mongocxx::log_level level, bool notify)
    // {
    //     QString textLog;
    //     QString mongoLevel;
    //     QString newLine = "\n";

    //     switch (level) {
    //         case mongocxx::log_level::k_critical:
    //             mongoLevel = "CRITICAL";
    //             break;
    //         case mongocxx::log_level::k_debug:
    //             mongoLevel = "DEBUG";
    //             break;
    //         case mongocxx::log_level::k_error:
    //             mongoLevel = "ERROR";
    //             break;
    //         case mongocxx::log_level::k_info:
    //             mongoLevel = "INFO";
    //             break;
    //         case mongocxx::log_level::k_message:
    //             mongoLevel = "MESSAGE";
    //             break;
    //         case mongocxx::log_level::k_trace:
    //             mongoLevel = "TRACE";
    //             break;
    //         case mongocxx::log_level::k_warning:
    //             mongoLevel = "WARNING";
    //             break;
    //         default:
    //             mongoLevel = "DEBUG";
    //             break;
    //       }

    //     QTime time = QTime::currentTime();
    //     QDate date = QDate::currentDate();

    //     _file->open( QIODevice::Append | QIODevice::Text );
    //     QTextStream stream(_file);

    //     textLog.append(date.toString("yyyy-MM-dd ") + time.toString("hh:mm:ss ") + mongoLevel + " " + mess + newLine);
    //     stream << textLog;
    //     _file->close();

    //     if (notify)
    //           emit printed(mess, level);
    // }

} // namespace IntelligibleWM