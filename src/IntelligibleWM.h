#pragma once

#include <QMainWindow>
#include <QLabel>

#include "gui/IntelligibleTabWidget.h"

namespace IWM
{

    class IntelligibleTabWidget;

    class IntelligibleWM : public QMainWindow
    {
        Q_OBJECT
    public:
        IntelligibleWM(QWidget *parent = nullptr);

    private:
        IntelligibleTabWidget *_intelligibleTabWidget;

    public Q_SLOTS:
        void aboutIntelligibleWM();

    private Q_SLOTS:
        void openConnectionDialog();
    };

} // namespace IWM