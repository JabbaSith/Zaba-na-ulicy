/**
 * @file test_audiomanager.cpp
 * @brief Testy jednostkowe AudioManager.
 *
 * Uwaga: testy nie weryfikują faktycznego odtwarzania dźwięku (wymagałoby
 * to działającego backendu audio w środowisku CI), a jedynie poprawność
 * zarządzania stanem (głośność, mute).
 */

#include <gtest/gtest.h>
#include "audiomanager.h"

TEST(AudioManagerTest, DefaultStateNotMuted) {
    AudioManager am;
    EXPECT_FALSE(am.isMuted());
}

TEST(AudioManagerTest, VolumeIsClamped) {
    AudioManager am;

    am.setVolume(0.5f);
    EXPECT_FLOAT_EQ(am.getVolume(), 0.5f);

    am.setVolume(2.0f); // ponad zakres -> 1.0
    EXPECT_FLOAT_EQ(am.getVolume(), 1.0f);

    am.setVolume(-1.0f); // poniżej zakresu -> 0.0
    EXPECT_FLOAT_EQ(am.getVolume(), 0.0f);
}

TEST(AudioManagerTest, ToggleMuteFlipsState) {
    AudioManager am;
    bool initial = am.isMuted();
    am.toggleMute();
    EXPECT_NE(am.isMuted(), initial);
    am.toggleMute();
    EXPECT_EQ(am.isMuted(), initial);
}

TEST(AudioManagerTest, PlayCallsDoNotCrashWithoutAudioDevice) {
    AudioManager am;
    // W środowisku bez urządzenia audio (np. CI) odtwarzanie po prostu
    // nic nie robi, ale wywołania nie powinny zgłaszać wyjątków/crashować.
    EXPECT_NO_THROW(am.playMenuMusic());
    EXPECT_NO_THROW(am.playGameMusic());
    EXPECT_NO_THROW(am.stopMusic());
}
