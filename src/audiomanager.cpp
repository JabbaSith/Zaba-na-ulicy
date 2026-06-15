/**
 * @file audiomanager.cpp
 * @brief Implementacja odtwarzania muzyki w tle (jeden plik mp3, loop).
 */

#include "audiomanager.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QFile>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

// Plik audio kopiowany jest przy budowaniu do katalogu z plikiem wykonywalnym
const QString AudioManager::kMusicPath = "assets/music.mp3";

AudioManager::AudioManager(QObject *parent)
    : QObject(parent)
    , m_player(new QMediaPlayer(this))
    , m_output(new QAudioOutput(this))
    , m_volume(0.8f)
    , m_muted(false)
{
    m_player->setAudioOutput(m_output);
    m_player->setLoops(QMediaPlayer::Infinite);
    m_output->setVolume(m_volume);

    QString path = QCoreApplication::applicationDirPath() + "/" + kMusicPath;
    if (!QFile::exists(path))
        path = kMusicPath;

    if (QFile::exists(path)) {
        m_player->setSource(QUrl::fromLocalFile(path));
    } else {
        qDebug() << "[AudioManager] Nie znaleziono pliku audio:" << path
                 << "- muzyka nie będzie odtwarzana.";
    }
}

AudioManager::~AudioManager() = default;

void AudioManager::play() {
    if (m_muted) return;
    if (m_player->source().isEmpty()) return;
    if (m_player->playbackState() != QMediaPlayer::PlayingState)
        m_player->play();
}

void AudioManager::playMenuMusic() { play(); }
void AudioManager::playGameMusic() { play(); }

void AudioManager::stopMusic() { m_player->stop(); }

void AudioManager::setVolume(float value) {
    m_volume = qBound(0.0f, value, 1.0f);
    m_output->setVolume(m_volume);
}

void AudioManager::toggleMute() {
    m_muted = !m_muted;
    if (m_muted) {
        m_player->pause();
    } else if (!m_player->source().isEmpty()) {
        m_player->play();
    }
}

bool  AudioManager::isMuted()   const { return m_muted; }
float AudioManager::getVolume() const { return m_volume; }
