#include "IntelligibleTabBar.h"

namespace IntelligibleWM
{
    IntelligibleTabBar::IntelligibleTabBar(QWidget *parent) : QTabBar(parent)
    {
        setDrawBase(false);
    }
} // namespace IntelligibleWM