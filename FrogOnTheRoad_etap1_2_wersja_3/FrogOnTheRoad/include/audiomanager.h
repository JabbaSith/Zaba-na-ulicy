#pragma once

/**
 * @file audiomanager.h
 * @brief Zarządza muzyką w menu i podczas gry.
 *
 * TODO (Etap 2): podpiąć QMediaPlayer i pliki audio.
 * Na Etap 1 metody są stubami (nic nie grają).
 */

#include <QObject>

/**
 * @class AudioManager
 * @brief Stub zarządzania dźwiękiem.
 */
class AudioManager : public QObject {
    Q_OBJECT
public:
    explicit AudioManager(QObject *parent = nullptr);

    void playMenuMusic();
    void playGameMusic();
    void stopMusic();
    void setVolume(float value);   ///< 0.0 – 1.0
    void toggleMute();

    bool isMuted()   const;
    float getVolume() const;

private:
    float m_volume;
    bool  m_muted;
    // TODO: QMediaPlayer *m_player;
};
