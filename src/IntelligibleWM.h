#pragma once

#include <QMainWindow>
#include <QLabel>

#include "gui/IntelligibleTabWidget.h"

namespace IntelligibleWM
{

    class IntelligibleTabWidget;

    class IntelligibleWM : public QMainWindow
    {
        Q_OBJECT
    public:
        IntelligibleWM(QWidget *parent = nullptr);

    private:
        IntelligibleTabWidget *_intelligibleTabWidget;    
    };

} // namespace IntelligibleWM