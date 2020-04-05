#include "IntelligibleTabBar.h"

namespace IWM
{
    IntelligibleTabBar::IntelligibleTabBar(QWidget *parent) : QTabBar(parent)
    {
        setDrawBase(false);
    }
} // namespace IWM