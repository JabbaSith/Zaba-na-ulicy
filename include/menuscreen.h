#pragma once

/**
 * @file menuscreen.h
 * @brief Ekran głównego menu.
 *
 * Klasa zarządza LOGIKĄ menu – nie buduje UI ręcznie.
 * Wygląd pochodzi z pliku ui/menuscreen.ui (Qt Designer).
 */

#include <QWidget>
#include "gamedefs.h"
#include "audiomanager.h"
#include "skinmanager.h"

 #include "ui_menuscreen.h"

namespace Ui { class MenuScreen; }

/**
 * @class MenuScreen
 * @brief Ekran menu z wyborem trybu gry.
 *
 * Emituje sygnał modeSelected(GameMode) gdy gracz kliknie przycisk.
 * Wymagane objectName w pliku .ui:
 *   - btnPlayer  (QPushButton) – tryb gracza
 *   - btnAI      (QPushButton) – tryb AI
 *   - btnSkin    (QPushButton) – wybór skórki żaby (cyklicznie, tylko odblokowane)
 *   - titleLabel (QLabel)      – tytuł gry
 */
class MenuScreen : public QWidget {
    Q_OBJECT
public:
    explicit MenuScreen(AudioManager *audio, SkinManager *skinManager, QWidget *parent = nullptr);
    ~MenuScreen() override;

    /// Odświeża tekst przycisku skórki (np. po powrocie z gry, gdy odblokowano nową skórkę).
    void refreshSkinButton();

signals:
    /** @brief Emitowany gdy gracz wybierze tryb. */
    void modeSelected(GameMode mode);

private slots:
    void onPlayerModeClicked();
    void onAIModeClicked();
    void onSkinClicked();

private:
     Ui::MenuScreen *ui;   ///< Struktura UI wygenerowana z menuscreen.ui

    AudioManager *m_audio;
    SkinManager  *m_skinManager;
};
