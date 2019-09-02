#pragma once

#include <QTabBar>

namespace IntelligibleWM
{
    class IntelligibleTabBar : public QTabBar
    {
        Q_OBJECT

    public:
        /**
             * @brief Creates IntelligibleTabBar without parent widget.
             */
        explicit IntelligibleTabBar(QWidget *parent = nullptr);

    private:
        /**
             * @brief Builds stylesheet for this DellperTabBar widget.
             */
        QString buildStyleSheet();
    };

} // namespace IntelligibleWM
