#include "ConnectionIntelligibleWM.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QTableView>
#include <QHeaderView>
#include <QLabel>

namespace IntelligibleWM
{
    /**
     * @brief Simple ListWidgetItem that has several convenience methods.
     */
    class ConnectionListWidgetItem : public QTreeWidgetItem
    {
        public:
        /**
         * @brief Creates ConnectionListWidgetItem with specified ConnectionSettings
         */
        ConnectionListWidgetItem(ConnectionSettings *connection) { setConnection(connection); }

        /**
         * @brief Returns attached ConnectionSettings.
         */
        ConnectionSettings *connection() { return _connection; }

        /**
         * @brief Attach ConnectionSettings to this item
         */
        void setConnection(ConnectionSettings *connection)
        {
            setText(0, QString::fromStdString(connection->database()));
            setText(1, QString::fromStdString(connection->userName()));
            setText(2, QString::fromStdString(connection->host())+":"+QString::number(connection->port()));
            setCheckState(3, connection->isDefaultConnection() ? Qt::Checked : Qt::Unchecked);
            setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

            _connection = connection;
            setIcon(0, GuiRegistry::instance().newConnection());
        }

    private:
        ConnectionSettings *_connection;
    };

    ConnectionIntelligibleWM::ConnectionIntelligibleWM(SettingsManager *settingsManager, QWidget *parent): QDialog(parent),
        _settingsManager(settingsManager)
    {
        setWindowTitle("Connection Settings");
        setWindowIcon(GuiRegistry::instance().databaseIcon());
        setMinimumWidth(525);

        _connectionsWiget = new ConnectionsTreeWidget();
        QStringList headerColums;
        headerColums << "Database" << "User" << "Address" << "Default";
        _connectionsWiget->setHeaderLabels(headerColums);
        _connectionsWiget->header()->resizeSection(0,140);
        _connectionsWiget->header()->resizeSection(1,60);
        _connectionsWiget->header()->resizeSection(2,160);
        _connectionsWiget->header()->resizeSection(3,30);
        VERIFY(connect(_connectionsWiget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(accept()))); //edit();
        VERIFY(connect(_connectionsWiget, SIGNAL(layoutChanged()), this, SLOT(connectionsWiget_layoutChanged())));

        QDialogButtonBox *buttonBox = new QDialogButtonBox(this);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Save);
        buttonBox->button(QDialogButtonBox::Save)->setText("C&onnect");

        VERIFY(connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept())));
        VERIFY(connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject())));

        QDialogButtonBox *addRemoveBox = new QDialogButtonBox(this);
        addRemoveBox->setOrientation(Qt::Vertical);
        addRemoveBox->setStandardButtons(QDialogButtonBox::Yes | QDialogButtonBox::No | QDialogButtonBox::Help);
        addRemoveBox->button(QDialogButtonBox::Yes)->setText("&Add");
        addRemoveBox->button(QDialogButtonBox::Yes)->setIcon(GuiRegistry::instance().add());
        addRemoveBox->button(QDialogButtonBox::No)->setText("&Remove");
        addRemoveBox->button(QDialogButtonBox::No)->setIcon(GuiRegistry::instance().cross());
        addRemoveBox->button(QDialogButtonBox::Help)->setText("&Edit");
        VERIFY(connect(addRemoveBox, SIGNAL(accepted()), this, SLOT(add())));
        VERIFY(connect(addRemoveBox, SIGNAL(rejected()), this, SLOT(remove())));
        VERIFY(connect(addRemoveBox, SIGNAL(helpRequested()), this, SLOT(edit())));

        QSpacerItem *spacer = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);

        QHBoxLayout *topLayout = new QHBoxLayout;
        topLayout->addWidget(_connectionsWiget);
        topLayout->addWidget(addRemoveBox);

        QHBoxLayout *bottomLayout = new QHBoxLayout;
        bottomLayout->addSpacerItem(spacer);
        bottomLayout->addWidget(buttonBox);

        QLabel *intro = new QLabel("Add, edit, remove or reorder IntelligibleWM connections via drag'n'drop.");

        QVBoxLayout *firstColumnLayout = new QVBoxLayout;
        firstColumnLayout->addWidget(intro);
        firstColumnLayout->addLayout(topLayout);
        firstColumnLayout->addLayout(bottomLayout);

        QHBoxLayout *mainLayout = new QHBoxLayout(this);
        mainLayout->addLayout(firstColumnLayout, 0);

        /**
         * @brief Populate list connections
         */
        SettingsManager::ConnectionSettingsContainerType connections = _settingsManager->connections();
        for (SettingsManager::ConnectionSettingsContainerType::const_iterator it = connections.begin(); it != connections.end(); ++it) {
            ConnectionSettings *connectionModel = *it;
            add(connectionModel);
        }

        _connectionsWiget->setFocus();
    }

    void ConnectionIntelligibleWM::add()
    {
        ConnectionSettings *newConnectionSettings = new ConnectionSettings();
        ConnectionListWidgetItem *item = new ConnectionListWidgetItem(newConnectionSettings);
        _connectionsWiget->addTopLevelItem(item);
        _connectionsWiget->setFocus();
        _settingsManager->addConnection(newConnectionSettings);
    }

    void ConnectionIntelligibleWM::add(ConnectionSettings *connection)
    {
        ConnectionListWidgetItem *item = new ConnectionListWidgetItem(connection);
        _connectionsWiget->addTopLevelItem(item);
    }

    void ConnectionIntelligibleWM::remove()
    {
        ConnectionListWidgetItem *currentItem = reinterpret_cast<ConnectionListWidgetItem *>(_connectionsWiget->currentItem());

        /**
         * Do nothing if no item selected
         */
        if (!currentItem)
            return;

        ConnectionSettings *connectionSettings = currentItem->connection();

        int answer = QMessageBox::question(this, "Delete Connections",
            QString("Are you sure to delete \"%1\" database connection?").arg(connectionSettings->databaseName()),
            QMessageBox::Yes, QMessageBox::No, QMessageBox::NoButton);

        if (answer != QMessageBox::Yes)
            return;

        _settingsManager->removeConnection(connectionSettings);
        delete currentItem;
        _settingsManager->save();
    }

    void ConnectionIntelligibleWM::edit()
    {
        ConnectionListWidgetItem *currentItem = reinterpret_cast<ConnectionListWidgetItem *> (_connectionsWiget->currentItem());

        /**
         * Do nothing if no item selected
         */
        if (currentItem == nullptr)
            return;

        int count = _connectionsWiget->topLevelItemCount();
        ConnectionSettings *connection = currentItem->connection();
        EditConnectionIntelligibleWM editConnection(connection, this);
        if (editConnection.exec() != QDialog::Accepted) {
            activateWindow();
            return;
        }
       activateWindow();
       SettingsManager::ConnectionSettingsContainerType connections = _settingsManager->connections();
       for (SettingsManager::ConnectionSettingsContainerType::const_iterator conn = connections.begin(); conn != connections.end(); ++conn) {
           ConnectionSettings *connectionModel = *conn;
            if (connectionModel == connection)  {
                currentItem->setConnection(connection);
            } else {
                if (connection->isDefaultConnection()) {
                    for(int i = 0; i < count; i++)
                    {
                        ConnectionListWidgetItem * item = reinterpret_cast<ConnectionListWidgetItem *> (_connectionsWiget->topLevelItem(i));
                        if (connectionModel == item->connection()) {
                            connectionModel->setDefaultConnection(false);
                            item->setConnection(connectionModel);
                        }

                    }
                }
            }
       }
    }

    void ConnectionIntelligibleWM::accept()
    {       
        _settingsManager->save();

        ConnectionListWidgetItem *currentItem = reinterpret_cast<ConnectionListWidgetItem *> (_connectionsWiget->currentItem());

        /**
        * Do nothing if no item selected
        */
        if (!currentItem)
            return;

        _selectedConnectionSettings = currentItem->connection();

        QDialog::accept();
    }

    void ConnectionIntelligibleWM::connectionsWiget_layoutChanged()
    {
        int count = _connectionsWiget->topLevelItemCount();

        /**
         * Make childrens toplevel again. This is a bad, but quickiest item reordering
         * implementation.
         */
        for(int i = 0; i < count; i++)
        {
            ConnectionListWidgetItem * item = reinterpret_cast<ConnectionListWidgetItem *> (_connectionsWiget->topLevelItem(i));
            if (item->childCount() > 0) {
                ConnectionListWidgetItem *childItem = reinterpret_cast<ConnectionListWidgetItem *> (item->child(0));
                item->removeChild(childItem);
                _connectionsWiget->insertTopLevelItem(++i, childItem);
                _connectionsWiget->setCurrentItem(childItem);
                break;
            }
        }

        count = _connectionsWiget->topLevelItemCount();
        SettingsManager::ConnectionSettingsContainerType items;
        for(int i = 0; i < count; i++)
        {
            ConnectionListWidgetItem * item = reinterpret_cast<ConnectionListWidgetItem *> (_connectionsWiget->topLevelItem(i));
            items.push_back(item->connection());
        }

        _settingsManager->reorderConnections(items);

    }

    ConnectionsTreeWidget::ConnectionsTreeWidget()
    {
        setDragDropMode(QAbstractItemView::InternalMove);
        setSelectionMode(QAbstractItemView::SingleSelection);
        setDragEnabled(true);
        setAcceptDrops(true);
    }

    void ConnectionsTreeWidget::dropEvent(QDropEvent *event)
    {        
        QTreeWidget::dropEvent(event);
        emit layoutChanged();
    }
} // namespace IntelligibleWM