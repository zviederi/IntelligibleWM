#include "IntelligibleTabBar.h"

namespace IntelligibleWM
{
    IntelligibleTabBar::IntelligibleTabBar(QWidget *parent) : QTabBar(parent)
    {
        setDrawBase(false);
        setStyleSheet(buildStyleSheet());
    }

    /**
         * @brief Builds stylesheet for Dellper tab bar widget
         */
    QString IntelligibleTabBar::buildStyleSheet()
    {
        QColor background = palette().window().color();
        QColor gradientZero = QColor("#ffffff");      //Qt::white;//.lighter(103);
        QColor gradientOne = background.lighter(104); //Qt::white;//.lighter(103);
        QColor gradientTwo = background.lighter(108); //.lighter(103);

        QString styles = QString(
                            "QTabBar::tab:first {"
                            "margin-left: 4px;"
                            "} "
                            "QTabBar::tab:last {"
                            "margin-right: 1px;"
                            "} "

                            "QTabBar::tab {"
                            "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                            "stop: 0 #F0F0F0, stop: 0.4 #DEDEDE,"
                            "stop: 0.5 #E6E6E6, stop: 1.0 #E1E1E1);"
                            "border: 1px solid #C4C4C3;"
                            "border-bottom-color: #C2C7CB;" // #C2C7CB same as the pane color

                            "max-width: 200px;"
                            "min-width: 100px;"
                            "padding: 5px 0px 5px 4px;"
                            "margin: 0px;"
                            "margin-left: 1px;"
                            "margin-right: 0px;" // it should be -(tab:first:margin-left + tab:last:margin-left) to fix incorrect text elidement
                            "}"

                            "QTabBar::tab:selected, QTabBar::tab:hover {"
                            "background: qlineargradient(x1: 0, y1: 1, x2: 0, y2: 0,"
                            "stop: 0 %1, stop: 0.3 %2,"    //#fafafa, #f4f4f4
                            "stop: 0.6 %3, stop: 1.0 %4);" //#e7e7e7, #fafafa
                            "background-color: white;"
                            "}"

                            "QTabBar::tab:selected {"
                            "border-color: #9B9B9B;"   //
                            "border-bottom-color: %4;" //#fafafa
                            "}"

                            "QTabBar::tab:!selected {"
                            "margin-top: 2px;" // make non-selected tabs look smaller
                            "}  "

                            "QTabBar::tab:only-one { "
                            "margin-top: 2px; "
                            "margin-left:4px; "
                            "}")
                            .arg(gradientZero.name(), gradientOne.name(), gradientTwo.name(), "#ffffff");

        return styles;
    }
} // namespace IntelligibleWM