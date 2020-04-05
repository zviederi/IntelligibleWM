#pragma once

#include <QString>
#include <QVariantMap>
#include <vector>

namespace IWM {

    class ConnectionSettings;

    class SettingsManager 
    {
    public:
        typedef std::vector<ConnectionSettings *> ConnectionSettingsContainerType;
        typedef QMap<QString, QVariant> WidgetsSettingsContainerType;
        typedef QMap<QString, QVariant> FontSettingsContainerType;

        /**
         * @brief Creates SettingsManager for config file in default location
         *        (loaction usually ~/.config/IntelligibleWM/intelligible.json)
         */
        SettingsManager();

        /**
         * @brief Cleanup owned objects
         */
        ~SettingsManager();

        /**
         * @brief Load settings from config file.
         * @return true if success, false otherwise
         */
        void load();

        /**
         * @brief Saves all settings to config file.
         * @return true if success, false otherwise
         */
        void save();

        /**
         * @brief Is default connection exists.
         * @return bool
         */
        bool isDefaultConnection();

        /**
         * @brief Return default connection.
         * @return defaultConnection
         */
        ConnectionSettings *defaultConnection();

        /**
         * @brief Adds connection to the end of list.
         * Connection now will be owned by SettingsManager.
         */
        void addConnection(ConnectionSettings *connection);

        /**
         * @brief Removes connection by index
         */
        void removeConnection(ConnectionSettings *connection);

        /**
         * @brief connection
         * @param connection
         * @return
         */
        ConnectionSettings *connection(ConnectionSettings *connection);

        /**
         * @brief Returns list of connections
         */
        ConnectionSettingsContainerType connections() const { return _connections; }

        /**
         * @brief Reorder Connections
         * @param connections
         */
        void reorderConnections(const ConnectionSettingsContainerType &connections);

        /**
         * @brief list of wigets/toolbars
         * @return
         */
        WidgetsSettingsContainerType widgets() const { return _widgets; }

        /**
         * @brief setWidgetSettings set widget/toolbar visible
         * @param widget
         * @param visible
         */
        void setWidgetSettings(QString widget, bool visible);
        bool isWidgetVisible(QString widget);

        /**
         * @brief useCompleter use completer in search
         * @return
         */
        bool useCompleter() const { return _useCompleter; }
        void setUseCompleter(const bool useCompleter) { _useCompleter = useCompleter; }


        /**
         * @brief set/get dellper theme
         * @return
         */
        QString theme() const { return _theme; }
        void setTheme(const QString &theme) { _theme = theme; }


        /**
         * @brief list of wigets/toolbars
         * @return
         */
        FontSettingsContainerType font() const { return _font; }

        /**
         * @brief set/get dellper font family
         * @return
         */
        QString fontFamily() const { return _font["fontFamily"].toString(); }
        void setFontFamily(const QString &fontFamily);


        /**
         * @brief set/get dellper font family
         * @return
         */
        int fontSize() const { return _font["fontSize"].toInt(); }
        void setFontSize(const int fontSize);

    private:

        /**
         * @brief Load settings from the map. Existings settings will be overwritten.
         */
        void loadFromMap(QVariantMap &map);

        /**
         * @brief Save all settings to map.
         */
        QVariantMap convertToMap() const;

        /**
         * @brief List of connections
         */
        ConnectionSettingsContainerType _connections;        
        WidgetsSettingsContainerType _widgets;
        FontSettingsContainerType _font;

        QString _configPath;
        QString _configDir;

        bool _useCompleter;
        QString _theme;
        bool _isDefaultConnection = false;

    };

} // namespace IWM