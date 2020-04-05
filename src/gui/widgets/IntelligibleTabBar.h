#pragma once

#include <QTabBar>

namespace IWM
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

} // namespace IWM
