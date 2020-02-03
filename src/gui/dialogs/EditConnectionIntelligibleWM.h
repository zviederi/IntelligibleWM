#pragma once

#include <QDialog>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QLabel;
class QPushButton;
class QSpinBox;
class QCheckBox;
QT_END_NAMESPACE

namespace IntelligibleWM {

    class ConnectionSettings;

    class EditConnectionIntelligibleWM : public QDialog
    {
        Q_OBJECT
    public:
        EditConnectionIntelligibleWM(ConnectionSettings *connection, QWidget *parent = nullptr);

    private:
        /**
         * @brief Edited connection
         */
        ConnectionSettings *const _connectionSettings;

        QLabel    *_hostLabel;
        QLineEdit *_host;

        QLabel    *_portLabel;
        QSpinBox  *_port;

        QLabel    *_databaseNameLabel;
        QLineEdit *_databaseName;

        QLabel    *_userNameLabel;
        QLineEdit *_userName;

        QLabel    *_userPasswordLabel;
        QLineEdit *_userPassword;

        QPushButton *_echoModeButton;

        QLabel    *_setAsDefaultLabel;
        QCheckBox *_setAsDefault;

    public Q_SLOTS:
        /**
         * @brief Accept() is called when user agree with entered data.
         */
        virtual void accept();

        void saveConnectionSettings();

    private Q_SLOTS:
        /**
         * @brief Test current connection
         */
        void testConnection();

        /**
         * Hide or show password
         * @brief toggleEchoMode
         */
        void toggleEchoMode();
    };
}