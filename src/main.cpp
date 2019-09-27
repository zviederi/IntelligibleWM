#include "IntelligibleWM.h"

#include <iostream>
#include <QApplication>
#include <QDesktopWidget>
#include <QFile>

QByteArray readTextFile(const QString &file_path) {
  QFile input_file(file_path);
  QByteArray input_data;

  if (input_file.open(QIODevice::Text | QIODevice::Unbuffered | QIODevice::ReadOnly)) {
    input_data = input_file.readAll();
    input_file.close();
    return input_data;
  }
  else {
    return QByteArray();
  }
}

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // Initialize Qt application
    QApplication a(argc, argv);

    IntelligibleWM::IntelligibleWM intelligibleWM;

    QString customStylesheet = readTextFile(":/intelligibleWM/stylesheets/custom.qss");
    a.setStyleSheet(customStylesheet);

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