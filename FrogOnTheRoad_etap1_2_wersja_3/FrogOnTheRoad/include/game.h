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
 * @brief Orkiestruje pętlę gry: timer → update → render.
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

    Player*       getPlayer() const;
    ScoreManager* getScore()  const;
    bool          isRunning() const;

signals:
    void gameOver();
    void scoreUpdated(int newScore);

private slots:
    void tick();

private:
    void resetGame();
    void renderFrame();
    void drawRoadSection(int topY, int count);

    QGraphicsScene                     *m_scene;
    QTimer                              m_timer;
    std::unique_ptr<Player>             m_player;
    std::vector<std::unique_ptr<Lane>>  m_lanes;
    std::unique_ptr<CollisionDetector>  m_collision;
    std::unique_ptr<ScoreManager>       m_score;
    SkinManager                        *m_skinManager;
    bool  m_running;
    int   m_tick;
};
