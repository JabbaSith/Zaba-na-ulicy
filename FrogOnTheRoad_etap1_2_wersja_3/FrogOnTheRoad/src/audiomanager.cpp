/**
 * @file audiomanager.cpp
 * @brief Stub – etap 1. Metody nie odtwarzają jeszcze dźwięku.
 */

#include "audiomanager.h"
#include <QDebug>

AudioManager::AudioManager(QObject *parent)
    : QObject(parent), m_volume(0.8f), m_muted(false)
{}

void  AudioManager::playMenuMusic() { qDebug() << "[Audio] playMenuMusic (stub)"; }
void  AudioManager::playGameMusic() { qDebug() << "[Audio] playGameMusic (stub)"; }
void  AudioManager::stopMusic()     { qDebug() << "[Audio] stopMusic (stub)"; }
void  AudioManager::setVolume(float v) { m_volume = qBound(0.0f, v, 1.0f); }
void  AudioManager::toggleMute()    { m_muted = !m_muted; }
bool  AudioManager::isMuted()  const { return m_muted; }
float AudioManager::getVolume() const { return m_volume; }
