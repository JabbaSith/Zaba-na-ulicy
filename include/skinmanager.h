#pragma once

/**
 * @file skinmanager.h
 * @brief Zarządza kolekcją skórek gracza.
 */

#include <QObject>
#include <vector>
#include <memory>
#include "playerskin.h"

/**
 * @class SkinManager
 * @brief Przechowuje wszystkie skórki i obsługuje ich odblokowywanie.
 */
class SkinManager : public QObject {
    Q_OBJECT
public:
    explicit SkinManager(QObject *parent = nullptr);

    /** @brief Odblokowuje skórki kosztujące <= pointsTotal. */
    void tryUnlock(int pointsTotal);

    /** @brief Ustawia aktywną skórkę (tylko odblokowana). */
    void setActiveSkin(int index);

    /** @brief Zwraca aktualnie aktywną skórkę. Nigdy nullptr. */
    PlayerSkin* getActiveSkin() const;

    /** @brief Indeks aktualnie aktywnej skórki. */
    int getActiveIndex() const;

    /** @brief Czy skórka o danym indeksie jest odblokowana. */
    bool isUnlocked(int index) const;

    /** @brief Wszystkie skórki (do wyświetlenia w sklepie). */
    const std::vector<std::unique_ptr<PlayerSkin>>& getAllSkins() const;

private:
    std::vector<std::unique_ptr<PlayerSkin>> m_skins;
    int m_activeIndex;
};
