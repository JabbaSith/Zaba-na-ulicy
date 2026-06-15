/**
 * @file main.cpp
 * @brief Punkt wejścia aplikacji.
 */

#include <QApplication>
#include "gamewindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("Frog on the Road");
    app.setApplicationVersion("0.1-alpha");

    GameWindow window;
    window.show();

    return app.exec();
}
