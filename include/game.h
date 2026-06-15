#pragma once

/**
 * @file game.h
 * @brief Klasa Game – główna logika rozgrywki.
 */

#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <vector>
#include <memory>
#include "gamedefs.h"
#include "player.h"
#include "lane.h"
#include "collisiondetector.h"
#include "scoremanager.h"
#include "skinmanager.h"

/**
 * @class Game
 * @brief Pętla gry: timer → update → render.
 */
class Game : public QObject {
    Q_OBJECT
public:
    explicit Game(QGraphicsScene *scene, SkinManager *skinManager,
                  QObject *parent = nullptr);

    void startGame();
    void pauseGame();
    void endGame();
    void handleInput(Direction dir);

    /**
     * @brief Resetuje pozycję/stan żaby (po kolizji w trybie AI),
     *        BEZ zatrzymywania timera, resetowania wyniku ani pasów ruchu.
     */
    void resetPlayer();

    /// Zmienia interwał ticka (np. wolniejszy w trybie AI).
    void setTickInterval(int ms);

    /**
     * @brief Symuluje @p ticks ticków ruchu aut (bez żaby i bez kolizji).
     * Wywołaj po startGame() w trybie AI, żeby mapa była już zapełniona
     * autami zanim AI zacznie podejmować decyzje.
     */
    void warmup(int ticks);

    Player*       getPlayer() const;
    ScoreManager* getScore()  const;
    bool          isRunning() const;

    /// Dostęp do pasów ruchu (potrzebne dla AIController).
    const std::vector<std::unique_ptr<Lane>>& getLanes() const;

signals:
    /// Emitowany gdy gra zostaje zakończona (przegrana w trybie gracza lub META w obu trybach).
    void gameOver();
    void scoreUpdated(int newScore);

    /// Emitowany przy wykryciu kolizji żaby z pojazdem (w KAŻDYM ticku, w którym do niej doszło).
    void playerDied();

    /// Emitowany gdy żaba dotrze do strefy META (góra planszy).
    void goalReached();

    /**
     * @brief Emitowany na początku każdego ticku, przed ruchem samochodów.
     *        Pozwala AIController podjąć decyzję i wykonać ruch żaby
     *        zanim pasy ruchu zostaną zaktualizowane i sprawdzona zostanie kolizja.
     */
    void tickReady();

private slots:
    void tick();
    void renderTick();  ///< Ruch aut + rysowanie (30ms, niezależny od trybu AI).

private:
    void resetGame();
    void renderFrame();
    void drawRoadSection(int topY, int count);

    QGraphicsScene                     *m_scene;
    QTimer m_timer;        ///< Decyzje AI / input gracza (zmienny interwał).
    QTimer m_renderTimer;  ///< Ruch aut + render (zawsze GAME_TICK_MS = 30ms).
    std::unique_ptr<Player>             m_player;
    std::vector<std::unique_ptr<Lane>>  m_lanes;
    std::unique_ptr<CollisionDetector>  m_collision;
    std::unique_ptr<ScoreManager>       m_score;
    SkinManager                        *m_skinManager;
    bool  m_running;
    int   m_tick;
};
