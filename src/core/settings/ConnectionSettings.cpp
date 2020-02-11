#include "ConnectionSettings.h"

namespace IntelligibleWM {

    ConnectionSettings::ConnectionSettings() : QObject()
    { }

    ConnectionSettings::ConnectionSettings(QVariantMap map): QObject()
      ,_database(map.value("database").toString().toStdString())
      ,_host(map.value("host").toString().toStdString())
      ,_port(map.value("port").toInt())
      ,_userName(map.value("userName").toString().toStdString())
      ,_userPassword(map.value("userPassword").toString().toStdString())
      ,_isDefaultConnection(map.value("isDefaultConnection").toBool())
    {  }

    ConnectionSettings::~ConnectionSettings()
    { }

    void ConnectionSettings::apply(const ConnectionSettings *source)
    {
        setDatabase(source->database());
        setHost(source->host());
        setPort(source->port());
        setDefaultConnection(source->isDefaultConnection());
        setUserName(source->userName());
        setUserPassword(source->userPassword());
    }

    ConnectionSettings *ConnectionSettings::clone() const
    {
        ConnectionSettings *newConnectionSettings = new ConnectionSettings();
        newConnectionSettings->apply(this);
        return newConnectionSettings;
    }

    QVariant ConnectionSettings::toVariant() const
    {
        QVariantMap map;
        map.insert("database", QString::fromStdString(database()));
        map.insert("host", QString::fromStdString(host()));
        map.insert("port", port());
        map.insert("isDefaultConnection", isDefaultConnection());
        map.insert("userName", QString::fromStdString(userName()));
        map.insert("userPassword", QString::fromStdString(userPassword()));
        return map;
    }

    QString ConnectionSettings::fullAddress() const
    {
        QString fullAddress = QString::fromStdString(_host);
        fullAddress.append(":" + QString::number(_port));
        fullAddress.append("/" + QString::fromStdString(_database));
        return fullAddress;
    }

    std::string ConnectionSettings::connectionUri() const
    {
        /**
         * std::string expected_url("mongodb://user:password@localhost:27017/database");
         */
        std::string mongo_url("mongodb://");
        if (!_userName.empty() && !_userPassword.empty()) {
            mongo_url.append(_userName+":");
            mongo_url.append(_userPassword+"@");
        }
        mongo_url.append(_host+":");
        mongo_url.append(std::to_string(_port)+"/");
        mongo_url.append(_database);
        return mongo_url;
    }

} // namespace IntelligibleWM