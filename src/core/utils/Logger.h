#pragma once

#include <QObject>
#include <QDir>
#include <QString>
#include <QTextStream>
#include <string>
#include "SingletonPattern.hpp"
// #include <mongocxx/logger.hpp>

namespace IntelligibleWM
{
    class Logger: public QObject, public Patterns::LazySingleton<Logger>
    {
        friend class Patterns::LazySingleton<Logger>;
        Q_OBJECT
    // public:
    //     void print(const char *mess, mongocxx::log_level level, bool notify);
    //     void print(const std::string &mess, mongocxx::log_level level, bool notify);
    //     void print(const QString &mess, mongocxx::log_level level, bool notify);
    // Q_SIGNALS:
    //     void printed(const QString &mess, mongocxx::log_level level);

    private:
        Logger();
        ~Logger();

        QFile *_file;
    };

    // template<typename T>
    // inline void LOG_MSG(const T &mess, mongocxx::log_level level, bool notify = true)
    // {
    //     return Logger::instance().print(mess, level, notify);
    // }
} // namespace IntelligibleWM