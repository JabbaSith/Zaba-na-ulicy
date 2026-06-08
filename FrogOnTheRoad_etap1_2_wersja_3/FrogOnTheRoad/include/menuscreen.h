#pragma once

/**
 * @file menuscreen.h
 * @brief Ekran głównego menu.
 *
 * Klasa zarządza LOGIKĄ menu – nie buduje UI ręcznie.
 * Wygląd pochodzi z pliku ui/menuscreen.ui (Qt Designer).
 *
 * Aby podłączyć UI z Designer:
 *   1. Stwórz ui/menuscreen.ui zgodnie z poradnik_qt_designer.html
 *   2. Odkomentuj linię: #include "ui_menuscreen.h"
 *   3. Odkomentuj: Ui::MenuScreen *ui; w sekcji private
 *   4. W menuscreen.cpp odkomentuj blok "=== DESIGNER ===" i usuń blok "=== TYMCZASOWY ==="
 */

#include <QWidget>
#include "gamedefs.h"
#include "audiomanager.h"

// ════════════════════════════════════════════════════════════════════════════
//  KROK 1 – odkomentuj gdy masz gotowy plik ui/menuscreen.ui
// ════════════════════════════════════════════════════════════════════════════
 #include "ui_menuscreen.h"

// Forward-declare żeby uniknąć błędu gdy nagłówek jeszcze nie istnieje
namespace Ui { class MenuScreen; }

/**
 * @class MenuScreen
 * @brief Ekran menu z wyborem trybu gry.
 *
 * Emituje sygnał modeSelected(GameMode) gdy gracz kliknie przycisk.
 * Wymagane objectName w pliku .ui:
 *   - btnPlayer  (QPushButton) – tryb gracza
 *   - btnAI      (QPushButton) – tryb AI
 *   - titleLabel (QLabel)      – tytuł gry
 */
class MenuScreen : public QWidget {
    Q_OBJECT
public:
    explicit MenuScreen(AudioManager *audio, QWidget *parent = nullptr);
    ~MenuScreen() override;

signals:
    /** @brief Emitowany gdy gracz wybierze tryb. */
    void modeSelected(GameMode mode);

private slots:
    void onPlayerModeClicked();
    void onAIModeClicked();

private:
    // ════════════════════════════════════════════════════════════════════════
    //  KROK 2 – odkomentuj i usuń poniżej sekcję "TYMCZASOWY KOD"
    // ════════════════════════════════════════════════════════════════════════
     Ui::MenuScreen *ui;   ///< Struktura UI wygenerowana z menuscreen.ui

    // ── TYMCZASOWY KOD (usunąć po podłączeniu Designer) ──────────────────────
   ///< Buduje UI kodem gdy brak pliku .ui
    // ─────────────────────────────────────────────────────────────────────────

    AudioManager *m_audio;
};
