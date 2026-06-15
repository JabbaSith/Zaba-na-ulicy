/**
 * @file test_main.cpp
 * @brief Własny punkt wejścia testów Google Test.
 *
 * Tworzy QApplication przed uruchomieniem testów – wymagane przez Qt
 * gdy testy tworzą obiekty używające QPainter / QPixmap.
 */

#include <gtest/gtest.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);   // musi istnieć przed jakimkolwiek kodu Qt GUI
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
