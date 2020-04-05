#pragma once

#include <QTreeWidget>

#include "core/utils/utils.h"
#include "core/settings/ConnectionSettings.h"
#include "core/settings/SettingsManager.h"

#include "gui/GuiRegistry.h"
#include "gui/dialogs/EditConnectionIntelligibleWM.h"

namespace IWM
{
    class ConnectionListWidgetItem;
    class SettingsManager;

    class ConnectionIntelligibleWM : public QDialog
    {
        Q_OBJECT
    public:
        /**
         * @brief Constructs dialog with specified connection
         */
        ConnectionIntelligibleWM(SettingsManager *manager, QWidget *parent = nullptr);
    /**
         * @brief ConnectionSettings, that was selected after pressing on
         * "Connect" button
         */
        ConnectionSettings *selectedConnection() const { return _selectedConnectionSettings; }

     private:

        /**
         * @brief ConnectionSettings, that was selected after pressing on
         * "Connect" button
         */
        ConnectionSettings *_selectedConnectionSettings;

        /**
         * @brief SettingsManager connection
         */
        SettingsManager *_settingsManager;

        /**
         * @brief Connections list widget
         */
        QTreeWidget *_connectionsWiget;

        /**
         * @brief Hash that helps to connect ConnectionSettings with
         * ConnectionListWidgetItem*
         */
       //ConnectionListItemContainerType _connectionItems;

     private Q_SLOTS:
        /**
          * @brief Initiate 'add' action, usually when user clicked on Add button
          */
         void add();

         /**
          * @brief Add connection to the list widget
          */
         void add(ConnectionSettings *connection);


         /**
          * @brief Initiate 'remove' action, usually when user clicked on Remove
          * button
          */
         void remove();

         /**
          * @brief Initiate 'edit' action, usually when user clicked on Edit
          * button
          */
         void edit();

         /**
          * @brief Accept() save connection settings and connect
          */
         virtual void accept();

         /**
          * @brief Handles ListWidget layoutChanged() signal
          */
         void connectionsWiget_layoutChanged();
        
    };

    class ConnectionsTreeWidget : public QTreeWidget
    {
        Q_OBJECT
    public:
        ConnectionsTreeWidget();


    Q_SIGNALS:
        void layoutChanged();

    protected:
        void dropEvent(QDropEvent *event);
    };

} // namespace IWM