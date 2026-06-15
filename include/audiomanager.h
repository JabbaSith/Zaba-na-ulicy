#pragma once

/**
 * @file audiomanager.h
 * @brief Zarządza muzyką w menu i podczas gry.
 *
 * Używa jednego pliku audio (assets/music.mp3) odtwarzanego w pętli,
 * zarówno w menu jak i podczas gry — przełączanie trybu nie zmienia
 * utworu, tylko ewentualnie wznawia/zatrzymuje odtwarzanie.
 */

#include <QObject>
#include <QString>

class QMediaPlayer;
class QAudioOutput;

/**
 * @class AudioManager
 * @brief Odtwarza muzykę w tle (jeden plik mp3, loop) z kontrolą głośności/mute.
 */
class AudioManager : public QObject {
    Q_OBJECT
public:
    explicit AudioManager(QObject *parent = nullptr);
    ~AudioManager() override;

    void playMenuMusic();
    void playGameMusic();
    void stopMusic();
    void setVolume(float value);   ///< 0.0 – 1.0
    void toggleMute();

    bool  isMuted()   const;
    float getVolume() const;

private:
    void play();

    QMediaPlayer *m_player;
    QAudioOutput *m_output;

    float m_volume;
    bool  m_muted;

    static const QString kMusicPath;
};
