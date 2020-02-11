#include "SettingsManager.h"

#include <QDir>
#include <QFile>
#include <QVariantList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTextStream>
#include <QCoreApplication>

#include "core/settings/ConnectionSettings.h"
#include "core/utils/Logger.h"
#include "core/utils/utils.h"

namespace IntelligibleWM {

    /**
     * Creates SettingsManager for config file in default location
     * ~/.config/IntelligibleWM/intelligible.json
     */
    SettingsManager::SettingsManager()
    {
        /**
        * @brief Config file absolute path
        *        (loaction usually ~/.config/IntelligibleWM/intelligible.json)
        */
       _configPath = QString("%1/config/intelligible.json").arg(QCoreApplication::applicationDirPath());

       /**
        * @brief Config file containing directory path (usually: config/)
        */
       _configDir = QString("%1/config").arg(QCoreApplication::applicationDirPath());

       load();
       //LOG_MSG("SettingsManager initialized in " + _configPath, mongocxx::log_level::k_info, false);
    }

    SettingsManager::~SettingsManager()
    {
         std::for_each(_connections.begin(),_connections.end(),stdutils::default_delete<ConnectionSettings *>());
    }

    /**
     * Load settings from config file.
     * @return true if success, false otherwise
     */
    void SettingsManager::load()
    {
        // if (!QFile::exists(_configPath))
        //     LOG_MSG("ERROR: Could not found settings file with path: " + _configDir, mongocxx::log_level::k_error);

        QFile f(_configPath);
        // if (!f.open(QIODevice::ReadOnly))
        //     LOG_MSG("ERROR: Settings file: " + _configDir + " is not read only", mongocxx::log_level::k_error);

        QString jsonString = f.readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
        QJsonObject jsonObject = jsonDocument.object();
        QVariantMap map = jsonObject.toVariantMap();
        loadFromMap(map);        
    }

    /**
     * Saves all settings to config file.
     * @return true if success, false otherwise
     */
    void SettingsManager::save()
    {
        QVariantMap map = convertToMap();

        // if (!QDir().mkpath(_configDir)) {
        //     LOG_MSG("ERROR: Could not create settings path: " + _configDir, mongocxx::log_level::k_error);
        // }

        QFile f(_configPath);
        // if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        //     LOG_MSG("ERROR: Could not write settings to: " + _configPath,  mongocxx::log_level::k_error);
        // }

        QJsonObject jsonObject = QJsonObject::fromVariantMap(map);
        QJsonDocument jsonDocument;
        jsonDocument.setObject(jsonObject);
        f.write(jsonDocument.toJson());

        // LOG_MSG("Settings saved to: " + _configPath,  mongocxx::log_level::k_info);
    }

    bool SettingsManager::isDefaultConnection()
    {
        return _isDefaultConnection;
    }

    ConnectionSettings *SettingsManager::defaultConnection()
    {
        for(ConnectionSettingsContainerType::const_iterator it = _connections.begin(); it != _connections.end(); ++it) {
            ConnectionSettings * connectionSettings = qobject_cast<ConnectionSettings *>(* it);
            if (connectionSettings->isDefaultConnection()) {
               return connectionSettings;
            }
        }
    }

    void SettingsManager::addConnection(ConnectionSettings *connection)
    {
        _connections.push_back(connection);
    }

    void SettingsManager::removeConnection(ConnectionSettings *connection)
    {
        ConnectionSettingsContainerType::iterator it = std::find(_connections.begin(), _connections.end(), connection);
        if (it!=_connections.end()) {
            _connections.erase(it);
            delete connection;
        }
    }

    ConnectionSettings *SettingsManager::connection(ConnectionSettings *connection)
    {
        for(ConnectionSettingsContainerType::const_iterator it = _connections.begin(); it != _connections.end(); ++it) {
            ConnectionSettings * connectionSettings = qobject_cast<ConnectionSettings *>(* it);
            if (connectionSettings->database().compare(connection->database()) == 0) {
                connection = connectionSettings;
                break;
            }

        }
        return connection;
    }

    void SettingsManager::reorderConnections(const SettingsManager::ConnectionSettingsContainerType &connections)
    {
        _connections = connections;
    }

    void SettingsManager::setWidgetSettings(QString widget, bool visible)
    {
        _widgets[widget] = visible;
    }

    bool SettingsManager::isWidgetVisible(QString widget)
    {
        return _widgets[widget].toBool();
    }

    void SettingsManager::setFontFamily(const QString &fontFamily)
    {
         _font["fontFamily"] = fontFamily;
    }

    void SettingsManager::setFontSize(const int fontSize)
    {
         _font["fontSize"] = fontSize;
    }

    /**
     * Load settings from the map. Existings settings will be overwritten.
     * TODO should recheck execution events.
     */
    void SettingsManager::loadFromMap(QVariantMap &map)
    {
        _useCompleter = map.value("useCompleter").toBool();

        _theme = map.value("theme").toString();
        // if (_theme.isEmpty()) {
        //     _theme = DellperStyles::StyleName;
        // }

        _widgets = map.value("widgets").toMap();
        WidgetsSettingsContainerType::const_iterator widgets_it = _widgets.find("collectionList");
        if (_widgets.end() == widgets_it)
            _widgets["collectionList"] = true;

        widgets_it = _widgets.find("toolBar");
        if (_widgets.end() == widgets_it)
            _widgets["toolBar"] = true;

        // widgets_it = _widgets.find("partsView");
        // if (_widgets.end() == widgets_it)
        //     _widgets["partsView"] = true;

        // widgets_it = _widgets.find("stockObjectView");
        // if (_widgets.end() == widgets_it)
        //     _widgets["stockObjectView"] = true;

        _font = map.value("font").toMap();

        int isDefault = 0;
        QVariantList list = map.value("connections").toList();
        for (QVariantList::iterator it = list.begin(); it != list.end(); ++it) {
            ConnectionSettings *record = new ConnectionSettings((*it).toMap());
             if (record->isDefaultConnection())
                 isDefault++;
            _connections.push_back(record);
        }
        if (isDefault > 0 )
            _isDefaultConnection = true;

    }

    /**
     * Convert all settings to map.
     */
    QVariantMap SettingsManager::convertToMap() const
    {
        QVariantMap map;
        map.insert("useCompleter", _useCompleter);
        map.insert("theme", _theme);
        map.insert("widgets", _widgets);
        map.insert("font", _font);

        QVariantList list;
        for (ConnectionSettingsContainerType::const_iterator it = _connections.begin(); it!=_connections.end(); ++it) {
            QVariantMap rm = (*it)->toVariant().toMap();            
            list.append(rm);
        }
        map.insert("connections", list);
        return map;
    }

} // namespace IntelligibleWM