cmake_minimum_required(VERSION 3.16)
project(FrogOnTheRoad VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)   # generuje moc_*.cpp dla klas z Q_OBJECT
set(CMAKE_AUTOUIC ON)   # generuje ui_*.h z plików .ui (Qt Designer)
set(CMAKE_AUTORCC ON)   # obsługa plików .qrc (zasoby)

# Gdzie szukać plików .ui – folder ui/ obok src/ i include/
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

# ── Qt ────────────────────────────────────────────────────────────────────────
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia)

# ── Google Test ───────────────────────────────────────────────────────────────
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

# ── Nagłówki z Q_OBJECT (muszą być jawnie w targecie – wymóg qt_add_executable) ──
set(MOC_HEADERS
    include/player.h
    include/car.h
    include/smallcar.h
    include/truck.h
    include/suv.h
    include/lane.h
    include/collisiondetector.h
    include/scoremanager.h
    include/audiomanager.h
    include/aicontroller.h
    include/skinmanager.h
    include/game.h
include/menuscreen.h
    include/gamewindow.h
)

# Nagłówki bez Q_OBJECT
set(PLAIN_HEADERS
    include/gamedefs.h
    include/playerskin.h
    include/defaultskin.h
    include/ninjaskin.h
    include/goldenskin.h
)

# ── Pliki .ui (Qt Designer) ───────────────────────────────────────────────────
# Gdy plik .ui istnieje → AUTOUIC wygeneruje ui_gamewindow.h / ui_menuscreen.h
# Gdy pliku jeszcze nie ma → zostaw tę listę pustą lub zakomentuj
set(UI_FILES
    ui/gamewindow.ui    # ← odkomentuj gdy masz gotowy plik z Designer
    ui/menuscreen.ui    # ← odkomentuj gdy masz gotowy plik z Designer
)

# ── Pliki źródłowe aplikacji ──────────────────────────────────────────────────
set(APP_SOURCES
    src/main.cpp
    src/player.cpp
    src/car.cpp
    src/smallcar.cpp
    src/truck.cpp
    src/suv.cpp
    src/lane.cpp
    src/collisiondetector.cpp
    src/scoremanager.cpp
    src/audiomanager.cpp
    src/aicontroller.cpp
    src/playerskin.cpp
    src/defaultskin.cpp
    src/ninjaskin.cpp
    src/goldenskin.cpp
    src/skinmanager.cpp
    src/game.cpp
    src/menuscreen.cpp
    src/gamewindow.cpp
)

# ── Główny executable ─────────────────────────────────────────────────────────
# qt_add_executable zapewnia poprawne działanie MOC i AUTOUIC
qt_add_executable(FrogOnTheRoad
    ${APP_SOURCES}
    ${UI_FILES}        # pliki .ui – generują ui_*.h
    ${MOC_HEADERS}     # nagłówki z Q_OBJECT – muszą być tu dla MOC
    ${PLAIN_HEADERS}
    #ui/ui/menuscreen.ui
    #ui/ui/gamewindow.ui
    #include/menuscreen.h include/menuscreen.cpp
)
target_include_directories(FrogOnTheRoad PRIVATE include)
target_link_libraries(FrogOnTheRoad PRIVATE Qt6::Core Qt6::Widgets Qt6::Multimedia)

# Kopiuj folder assets/ (muzyka) do katalogu z plikiem wykonywalnym
add_custom_command(TARGET FrogOnTheRoad POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:FrogOnTheRoad>/assets
)

# ── Pliki źródłowe dla testów (bez main.cpp i plików UI) ─────────────────────
set(LIB_SOURCES
    src/player.cpp
    src/car.cpp
    src/smallcar.cpp
    src/truck.cpp
    src/suv.cpp
    src/lane.cpp
    src/collisiondetector.cpp
    src/scoremanager.cpp
    src/audiomanager.cpp
    src/aicontroller.cpp
    src/playerskin.cpp
    src/defaultskin.cpp
    src/ninjaskin.cpp
    src/goldenskin.cpp
    src/skinmanager.cpp
)

set(LIB_MOC_HEADERS
    include/player.h
    include/car.h
    include/smallcar.h
    include/truck.h
    include/suv.h
    include/lane.h
    include/collisiondetector.h
    include/scoremanager.h
    include/audiomanager.h
    include/aicontroller.h
    include/skinmanager.h
)

# ── Executable testów ─────────────────────────────────────────────────────────
# tests/test_main.cpp dostarcza własny main() z QApplication
qt_add_executable(FrogTests
    tests/test_main.cpp
    tests/test_player.cpp
    tests/test_scoremanager.cpp
    tests/test_car.cpp
    tests/test_collisiondetector.cpp
    tests/test_lane.cpp
    tests/test_skinmanager.cpp
    tests/test_aicontroller.cpp
    tests/test_audiomanager.cpp
    ${LIB_SOURCES}
    ${LIB_MOC_HEADERS}
    ${PLAIN_HEADERS}
)
target_include_directories(FrogTests PRIVATE include)
target_link_libraries(FrogTests
    PRIVATE
    GTest::gtest       # bez _main – własny main w tests/test_main.cpp
    Qt6::Core
    Qt6::Widgets
    Qt6::Multimedia
)

include(GoogleTest)
add_test(NAME FrogTests COMMAND FrogTests)