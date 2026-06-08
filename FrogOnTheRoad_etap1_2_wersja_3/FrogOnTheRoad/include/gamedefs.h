#pragma once

/**
 * @file gamedefs.h
 * @brief Wspólne stałe, enumeracje i typy używane w całym projekcie.
 *
 * Układ sceny (Y od góry):
 *   0..39          – strefa META (trawa)
 *   40..279        – 3 górne pasy ruchu (po LANE_HEIGHT=80 px każdy)
 *   280..359       – pas zieleni (MEDIAN_HEIGHT=80 px)
 *   360..599       – 3 dolne pasy ruchu (po LANE_HEIGHT=80 px)
 *   560..599       – strefa START (trawa, gracz startuje tu)
 *
 *  LANE_Y[0..2]  = górna trójka,  LANE_Y[3..5] = dolna trójka
 */

// ── Rozmiary sceny ────────────────────────────────────────────────────────────
constexpr int SCENE_WIDTH  = 800;
constexpr int SCENE_HEIGHT = 640;   ///< 40 meta + 3*80 + 80 median + 3*80 + 40 start

// ── Gracz ─────────────────────────────────────────────────────────────────────
constexpr int PLAYER_SIZE = 36;
constexpr int PLAYER_STEP = 40;     ///< Krok = szerokość pasa

// ── Pasy ruchu ────────────────────────────────────────────────────────────────
constexpr int LANE_COUNT       = 6;   ///< 3 górne + 3 dolne
constexpr int LANE_HEIGHT      = 80;
constexpr int MEDIAN_HEIGHT    = 80;  ///< Pas zieleni w środku

constexpr int ROAD_TOP_Y       = 40;                              ///< Y górnego pasa ruchu
constexpr int MEDIAN_Y         = ROAD_TOP_Y + 3 * LANE_HEIGHT;   ///< Y = 280
constexpr int ROAD_BOTTOM_Y    = MEDIAN_Y + MEDIAN_HEIGHT;        ///< Y = 360
constexpr int GOAL_Y           = 0;                               ///< Cel: żaba dotrze do Y=0
constexpr int START_Y          = SCENE_HEIGHT - PLAYER_SIZE - 4; ///< Pozycja startowa żaby

/**
 * @brief Zwraca Y górnej krawędzi pasa o danym indeksie (0-5).
 *        Pasy 0-2: górna część drogi. Pasy 3-5: dolna część drogi.
 */
inline int laneTopY(int laneIndex) {
    if (laneIndex < 3)
        return ROAD_TOP_Y  + laneIndex * LANE_HEIGHT;
    else
        return ROAD_BOTTOM_Y + (laneIndex - 3) * LANE_HEIGHT;
}

// ── Prędkości samochodów (px/tick przy 30ms/tick ≈ 33fps) ────────────────────
constexpr float SPEED_SMALL = 3.5f;
constexpr float SPEED_TRUCK = 1.8f;
constexpr float SPEED_SUV   = 2.6f;

// ── Minimalna odległość między autami na pasie (px) ───────────────────────────
/// Gwarantuje lukę >= szerokość gracza * 3  =>  zawsze jest przejście
constexpr int MIN_GAP = PLAYER_SIZE * 4;   ///< 144 px

// ── Timer gry ─────────────────────────────────────────────────────────────────
constexpr int GAME_TICK_MS = 30;

// ── Enumeracje ────────────────────────────────────────────────────────────────
enum class GameMode {
    PlayerControlled,
    AITraining
};

enum class Direction {
    Up, Down, Left, Right, None
};
