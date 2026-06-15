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
// ═══ WSZYSTKIE AUTA MAJĄ TĘ SAMĄ PRĘDKOŚĆ – BEZ PRZENIKANIA ═══
constexpr float CAR_SPEED = 2.8f;   ///< Uniwersalna prędkość dla wszystkich typów

// ── Minimalna odległość między autami na pasie (px) ───────────────────────────
/// Gwarantuje lukę >= szerokość gracza * 3  =>  zawsze jest przejście
constexpr int MIN_GAP = PLAYER_SIZE * 4;   ///< 144 px

// ── Timer gry ─────────────────────────────────────────────────────────────────
constexpr int GAME_TICK_MS    = 30;   ///< Tryb gracza – płynna animacja.
constexpr int AI_TICK_MS      = 400;  ///< Tryb AI – wolno, żeby dało się obserwować decyzje między autami.

/// Liczba ticków "rozgrzewki" (ruch aut bez żaby) przed pierwszym ruchem AI.
/// Przy 30ms/tick: 120 ticków = ~3.6s jazdy aut zanim AI zacznie.
constexpr int AI_WARMUP_TICKS = 120;

/// Epsilon eksploracji AI na starcie (wysoka losowość = bardziej "ludzkie" błędy i widoczna nauka).
constexpr float AI_EPSILON_INITIAL = 0.45f;

// ── Kolizje ───────────────────────────────────────────────────────────────────
/// Margines "wycięty" z każdej strony hitboxa (żaby i auta) przed sprawdzeniem
/// kolizji – sprawia, że gra jest mniej restrykcyjna (sprite'y muszą się
/// realnie nakładać, a nie tylko "dotknąć" przezroczystymi krawędziami).
constexpr int COLLISION_MARGIN = 6;

// ── Enumeracje ────────────────────────────────────────────────────────────────
enum class GameMode {
    PlayerControlled,
    AITraining
};

enum class Direction {
    Up, Down, Left, Right, None
};