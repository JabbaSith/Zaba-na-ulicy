/**
 * @file menuscreen.cpp
 *
 * ┌─────────────────────────────────────────────────────────────────────────┐
 * │  JAK PODŁĄCZYĆ QT DESIGNER – instrukcja w 3 krokach                    │
 * │                                                                         │
 * │  1. Stwórz ui/menuscreen.ui wg poradnik_qt_designer.html               │
 * │     (objectNames: btnPlayer, btnAI, titleLabel)                        │
 * │                                                                         │
 * │  2. W menuscreen.h:                                                     │
 * │     - odkomentuj: #include "ui_menuscreen.h"                           │
 * │     - odkomentuj: Ui::MenuScreen *ui;                                  │
 * │     - usuń:       void buildFallbackUI();                              │
 * │                                                                         │
 * │  3. W tym pliku (menuscreen.cpp):                                       │
 * │     - usuń blok oznaczony "=== TYMCZASOWY KOD ==="                     │
 * │     - odkomentuj blok oznaczony "=== DESIGNER ==="                     │
 * └─────────────────────────────────────────────────────────────────────────┘
 */

#include "menuscreen.h"
#include "ui_menuscreen.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

// ════════════════════════════════════════════════════════════════════════════
//  === DESIGNER === odkomentuj ten blok po stworzeniu ui/menuscreen.ui
// ════════════════════════════════════════════════════════════════════════════

MenuScreen::MenuScreen(AudioManager *audio, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuScreen)
    , m_audio(audio)
{
    ui->setupUi(this);   // ← buduje cały UI z pliku .ui

    // Połączenia – objectName z Designer musi być btnPlayer / btnAI
    connect(ui->btnPlayer, &QPushButton::clicked,
            this,          &MenuScreen::onPlayerModeClicked);
    connect(ui->btnAI,     &QPushButton::clicked,
            this,          &MenuScreen::onAIModeClicked);

    if (m_audio) m_audio->playMenuMusic();
}

MenuScreen::~MenuScreen() { delete ui; }

// ════════════════════════════════════════════════════════════════════════════


// ════════════════════════════════════════════════════════════════════════════
//  === TYMCZASOWY KOD === usuń ten blok po podłączeniu Designer
// ════════════════════════════════════════════════════════════════════════════


// ════════════════════════════════════════════════════════════════════════════

void MenuScreen::onPlayerModeClicked() { emit modeSelected(GameMode::PlayerControlled); }
void MenuScreen::onAIModeClicked()     { emit modeSelected(GameMode::AITraining); }
