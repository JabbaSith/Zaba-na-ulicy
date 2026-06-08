#pragma once

/**
 * @file gamewindow.h
 * @brief Główne okno aplikacji – przełącza między menu a grą.
 *
 * Klasa zarządza LOGIKĄ okna – nie buduje UI ręcznie.
 * Wygląd pochodzi z pliku ui/gamewindow.ui (Qt Designer).
 *
 * Aby podłączyć UI z Designer:
 *   1. Stwórz ui/gamewindow.ui zgodnie z poradnik_qt_designer.html
 *   2. Odkomentuj: #include "ui_gamewindow.h"
 *   3. Odkomentuj: Ui::GameWindow *ui; w sekcji private
 *   4. W gamewindow.cpp odkomentuj blok "=== DESIGNER ===" i usuń "=== TYMCZASOWY ==="
 *
 * Wymagane objectName w pliku ui/gamewindow.ui:
 *   - scoreLabel    (QLabel)         – pasek wyników u góry
 *   - stackedWidget (QStackedWidget) – kontener menu/gra
 *   - gameView      (QGraphicsView)  – widok sceny gry (strona 1 stacka)
 */

#include <QMainWindow>
#include <QStackedWidget>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <memory>
#include "gamedefs.h"
#include "game.h"
#include "menuscreen.h"
#include "audiomanager.h"
#include "skinmanager.h"
#include "aicontroller.h"

// ════════════════════════════════════════════════════════════════════════════
//  KROK 1 – odkomentuj gdy masz gotowy plik ui/gamewindow.ui
// ════════════════════════════════════════════════════════════════════════════
#include "ui/ui/ui_gamewindow.h"

namespace Ui { class GameWindow; }

/**
 * @class GameWindow
 * @brief MainWindow aplikacji – korzeń drzewa widgetów.
 *
 * Indeksy QStackedWidget:
 *   0 – MenuScreen
 *   1 – widok gry (QGraphicsView)
 */
class GameWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow() override;

    void showMenu();
    void showGame();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onModeSelected(GameMode mode);
    void onGameOver();
    void onScoreUpdated(int score);

private:
    void initLogic();          ///< Tworzy managery (audio, skin) – wspólne dla obu trybów UI
    void connectMenuSignals(); ///< Łączy sygnały MenuScreen → GameWindow

    // ════════════════════════════════════════════════════════════════════════
    //  KROK 2 – odkomentuj i usuń sekcję "TYMCZASOWE WSKAŹNIKI" poniżej
    // ════════════════════════════════════════════════════════════════════════
    Ui::GameWindow *ui;   ///< Struktura UI z gamewindow.ui


    // ─────────────────────────────────────────────────────────────────────────

    // ── Zawsze obecne (logika, niezależna od UI) ──────────────────────────────
    MenuScreen     *m_menu;
    QGraphicsScene *m_scene;

    std::unique_ptr<Game>         m_game;
    std::unique_ptr<AIController> m_aiController;
    std::unique_ptr<AudioManager> m_audio;
    std::unique_ptr<SkinManager>  m_skinManager;

    GameMode m_gameMode;
};
