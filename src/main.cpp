#include "IntelligibleWM.h"

#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // Initialize Qt application
    QApplication a(argc, argv);

    IntelligibleWM::IntelligibleWM intelligibleWM;

    /**
     * @brief screenGeometry - resize main window.
     */
    QRect screenGeometry = QApplication::desktop()->availableGeometry();
    int horizontalMargin = static_cast<int>(screenGeometry.width() * 0.1);
    int verticalMargin = static_cast<int>(screenGeometry.height() * 0.1);
    int width = screenGeometry.width() - horizontalMargin;
    int height = screenGeometry.height() - verticalMargin;
    intelligibleWM.resize(QSize(width, height));

    /**
     * @brief move to center main window.
     */
    int x = (screenGeometry.width() - intelligibleWM.width()) / 2;
    int y = (screenGeometry.height() - intelligibleWM.height()) / 2;
    intelligibleWM.move(x, y);

    /**
     * @brief show IntelligibleWM.
     */
    intelligibleWM.show();

    return a.exec();
}