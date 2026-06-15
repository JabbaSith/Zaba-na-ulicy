/**
 * @file menuscreen.cpp
 */

#include "menuscreen.h"
#include "ui_menuscreen.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

MenuScreen::MenuScreen(AudioManager *audio, SkinManager *skinManager, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuScreen)
    , m_audio(audio)
    , m_skinManager(skinManager)
{
    ui->setupUi(this);   // ← buduje cały UI z pliku .ui

    // Połączenia – objectName z Designer musi być btnPlayer / btnAI / btnSkin
    connect(ui->btnPlayer, &QPushButton::clicked,
            this,          &MenuScreen::onPlayerModeClicked);
    connect(ui->btnAI,     &QPushButton::clicked,
            this,          &MenuScreen::onAIModeClicked);
    connect(ui->btnSkin,   &QPushButton::clicked,
            this,          &MenuScreen::onSkinClicked);

    refreshSkinButton();

    if (m_audio) m_audio->playMenuMusic();
}

MenuScreen::~MenuScreen() { delete ui; }


void MenuScreen::onPlayerModeClicked() { emit modeSelected(GameMode::PlayerControlled); }
void MenuScreen::onAIModeClicked()     { emit modeSelected(GameMode::AITraining); }

// ── Wybór skórki ──────────────────────────────────────────────────────────────
void MenuScreen::onSkinClicked() {
    if (!m_skinManager) return;

    const auto &skins = m_skinManager->getAllSkins();
    int count = static_cast<int>(skins.size());
    if (count == 0) return;

    // Przejdź do następnej skórki cyklicznie, pomijając zablokowane.
    int idx = m_skinManager->getActiveIndex();
    for (int step = 1; step <= count; ++step) {
        int next = (idx + step) % count;
        if (m_skinManager->isUnlocked(next)) {
            m_skinManager->setActiveSkin(next);
            break;
        }
    }
    refreshSkinButton();
}

void MenuScreen::refreshSkinButton() {
    if (!m_skinManager) return;

    const QString name = m_skinManager->getActiveSkin()->getName();
    const auto &skins = m_skinManager->getAllSkins();
    int unlockedCount = 0;
    for (size_t i = 0; i < skins.size(); ++i)
        if (m_skinManager->isUnlocked(static_cast<int>(i))) ++unlockedCount;

    ui->btnSkin->setText(QString("SKÓRKA: %1").arg(name));
}
