#pragma once

#include <QTableWidget>
#include <QTabWidget>
#include <QTabBar>

namespace IntelligibleWM
{

    class IntelligibleTabWidget : public QTabWidget
    {
        Q_OBJECT

    public:
        explicit IntelligibleTabWidget(QWidget *parent = nullptr);

        void closeTab(int index);

    private:
        QWidget *_intelligibleWidget;    

    protected:
        /**
         * @brief Overrides QTabWidget::keyPressEvent()
         * tab close key shortcuts Ctrl+W)
         */
        virtual void keyPressEvent(QKeyEvent *event);
    };

} // namespace IntelligibleWM