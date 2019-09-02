#include "IntelligibleWM.h"
#include "gui/GuiRegistry.h"

#include <QApplication>
#include <QWidgetAction>

namespace IntelligibleWM {

    IntelligibleWM::IntelligibleWM(QWidget *parent) : QMainWindow(parent) {
        setWindowTitle(PROJECT_NAME_VERSION); 
        setWindowIcon(GuiRegistry::instance().intelligibleWMIcon());
    }

}