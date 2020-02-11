#pragma once

#include <QString>
#include <QVariant>
#include <QVariantMap>

#include <iostream>
#include <string>

namespace IntelligibleWM {

    class ConnectionSettings : public QObject
    {
        Q_OBJECT
    public:
        explicit ConnectionSettings();

        explicit ConnectionSettings(QVariantMap map);

        ~ConnectionSettings();

        /**
         * @brief Discards current state and applies state from 'source' ConnectionSettings.
         */
        void apply(const ConnectionSettings *source);

        /**
         * @brief Creates completely new ConnectionSettings by cloning this record.
         */
        ConnectionSettings *clone() const;

        /**
         * @brief Converts to QVariantMap
         */
        QVariant toVariant() const;

        /**
         * @brief Name of database
         */
        std::string database() const { return _database; }
        QString databaseName() const { return QString::fromStdString(_database); }
        void setDatabase(const std::string &database) { _database = database; }

        /**
         * @brief Connection host
         */
        std::string host() const { return _host; }
        void setHost(const std::string &host) { _host = host; }

        /**
         * @brief Connection port
         */
        int port() const { return _port; }
        void setPort(const int port) { _port = port; }

        /**
         * @brief User name
         */
       std::string userName() const { return _userName; }
       void setUserName(const std::string &userName) { _userName = userName; }

       /**
        * @brief Password - return a user password
        */
       std::string userPassword() const { return _userPassword; }
       void setUserPassword(const std::string &userPassword) { _userPassword = userPassword; }

       /**
        * @brief isDefaultConnection, return a default connection of connections list
        * @return
        */
       bool isDefaultConnection() const { return _isDefaultConnection; }

       /**
        * @brief setDefaulConnection - set as default current connection
        * @param isDefaultConnection
        */
       void setDefaultConnection(const bool isDefaultConnection) { _isDefaultConnection = isDefaultConnection; }

        /**
        * @brief Returns connection full address (i.e. locahost:8090)
        */
       QString fullAddress() const;

       /**
        * @brief connectionUrl Return connection url for mongo db in String URI Format
        * @return std string
        */
       std::string connectionUri() const;

    private:       
        std::string _database;
        std::string _host;
        int _port;
        std::string _userName;
        std::string _userPassword;
        bool _isDefaultConnection;
    };

} // namespace IntelligibleWM