#include "EditConnectionIntelligibleWM.h"

#include <QPushButton>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>

#include "core/settings/connectionsettings.h"
#include "core/utils/utils.h"

#include "gui/guiregistry.h"

namespace IWM {

    EditConnectionIntelligibleWM::EditConnectionIntelligibleWM(ConnectionSettings *connectionSettings, QWidget *parent) : QDialog(parent),
        _connectionSettings(connectionSettings)
    {
        setWindowTitle("Edit Connection");
        setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
        setMinimumWidth(450);

        _hostLabel = new QLabel("Host:");
        _host = new QLineEdit();
        _host->setText(QString::fromStdString(_connectionSettings->host()));

        _portLabel = new QLabel("Port:");
        _port = new QSpinBox();
        _port->setRange(0,65535);
        _port->setValue(_connectionSettings->port());

        _databaseNameLabel = new QLabel("Database:");
        _databaseName = new QLineEdit();
        _databaseName->setText(QString::fromStdString(_connectionSettings->database()));

        _userNameLabel = new QLabel("User name:");
        _userName = new QLineEdit();             
        _userName->setText(QString::fromStdString(_connectionSettings->userName()));

        _userPasswordLabel = new QLabel("User password:");
        _userPassword = new QLineEdit();
        _userPassword->setText(QString::fromStdString(_connectionSettings->userPassword()));
        _userPassword->setEchoMode(QLineEdit::Password);

        _echoModeButton = new QPushButton("Show");
        VERIFY(connect(_echoModeButton, SIGNAL(clicked()), this, SLOT(toggleEchoMode())));

        _setAsDefaultLabel = new QLabel("Set as default");
        _setAsDefault = new QCheckBox();
        _setAsDefault->setChecked(_connectionSettings->isDefaultConnection());

        QPushButton *testButton = new QPushButton("&Test", this);
        testButton->setIcon(GuiRegistry::instance().info());
        VERIFY(connect(testButton, SIGNAL(clicked()), this, SLOT(testConnection())));

        QDialogButtonBox *buttonBox = new QDialogButtonBox(this);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Save);
        buttonBox->button(QDialogButtonBox::Save);
        VERIFY(connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept())));
        VERIFY(connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject())));

        QSpacerItem *spacer = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);

        QGridLayout *gridLayout = new QGridLayout;
        gridLayout->addWidget(_hostLabel,0,0,1,1);
        gridLayout->addWidget(_host,1,0);
        gridLayout->addWidget(_portLabel,0,1,1,2);
        gridLayout->addWidget(_port,1,1);
        gridLayout->addWidget(_setAsDefaultLabel,2,1,1,2);
        gridLayout->addWidget(_setAsDefault, 3, 1);
        gridLayout->addWidget(_databaseNameLabel,2,0,1,3);
        gridLayout->addWidget(_databaseName,3,0);
        gridLayout->addWidget(_userNameLabel,4,0,1,3);
        gridLayout->addWidget(_userName,5,0);
        gridLayout->addWidget(_userPasswordLabel,6,0,1,3);
        gridLayout->addWidget(_userPassword,7,0);
        gridLayout->addWidget(_echoModeButton,7,1);


        QHBoxLayout *bottomLayout = new QHBoxLayout;
        bottomLayout->addWidget(testButton);
        bottomLayout->addSpacerItem(spacer);
        bottomLayout->addWidget(buttonBox);

        QVBoxLayout *firstColumnLayout = new QVBoxLayout;
        firstColumnLayout->addLayout(gridLayout);
        firstColumnLayout->addLayout(bottomLayout);

        QHBoxLayout *mainLayout = new QHBoxLayout(this);
        mainLayout->addLayout(firstColumnLayout, 0);

    }

    void EditConnectionIntelligibleWM::accept()
    {
        saveConnectionSettings();
        QDialog::accept();
    }

    void EditConnectionIntelligibleWM::saveConnectionSettings()
    {
        _connectionSettings->setHost(_host->text().toStdString());
        _connectionSettings->setPort(_port->value());
        _connectionSettings->setDatabase(_databaseName->text().toStdString());
        _connectionSettings->setUserName(_userName->text().toStdString());
        _connectionSettings->setUserPassword(_userPassword->text().toStdString());
        _connectionSettings->setDefaultConnection(_setAsDefault->isChecked());
    }

    void EditConnectionIntelligibleWM::testConnection()
    {
        emit saveConnectionSettings();
        // ConnectionTestDialog diag(_connectionSettings, this);
        // diag.exec();
    }

    void EditConnectionIntelligibleWM::toggleEchoMode()
    {
        bool isPassword = _userPassword->echoMode() == QLineEdit::Password;
        _userPassword->setEchoMode(isPassword ? QLineEdit::Normal: QLineEdit::Password);
        _echoModeButton->setText(isPassword ? "Hide": "Show");
    }
} // namespace IWM