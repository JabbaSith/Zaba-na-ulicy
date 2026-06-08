# Instrukcja konfiguracji projektu w Qt Creator – Etap 1

## 1. Wymagania wstępne

| Narzędzie | Wersja minimalna |
|-----------|-----------------|
| Qt        | 6.4             |
| CMake     | 3.16            |
| Kompilator | GCC 10 / MSVC 2019 / Clang 13 |
| Git       | dowolna (FetchContent pobiera GTest) |

> Qt 5.15 też zadziała – wystarczy w `CMakeLists.txt` zmienić `Qt6` → `Qt5` wszędzie.

---

## 2. Struktura katalogów

Stwórz jeden folder główny projektu (np. `FrogOnTheRoad/`) i ułóż pliki **dokładnie** tak:

```
FrogOnTheRoad/
├── CMakeLists.txt
├── include/
│   ├── gamedefs.h
│   ├── playerskin.h
│   ├── defaultskin.h
│   ├── ninjaskin.h
│   ├── goldenskin.h
│   ├── skinmanager.h
│   ├── player.h
│   ├── car.h
│   ├── smallcar.h
│   ├── truck.h
│   ├── suv.h
│   ├── lane.h
│   ├── collisiondetector.h
│   ├── scoremanager.h
│   ├── audiomanager.h
│   ├── aicontroller.h
│   ├── game.h
│   ├── menuscreen.h
│   └── gamewindow.h
├── src/
│   ├── main.cpp
│   ├── playerskin.cpp
│   ├── defaultskin.cpp
│   ├── ninjaskin.cpp
│   ├── goldenskin.cpp
│   ├── skinmanager.cpp
│   ├── player.cpp
│   ├── car.cpp
│   ├── smallcar.cpp
│   ├── truck.cpp
│   ├── suv.cpp
│   ├── lane.cpp
│   ├── collisiondetector.cpp
│   ├── scoremanager.cpp
│   ├── audiomanager.cpp
│   ├── aicontroller.cpp
│   ├── game.cpp
│   ├── menuscreen.cpp
│   └── gamewindow.cpp
└── tests/
    ├── test_player.cpp
    ├── test_scoremanager.cpp
    ├── test_car.cpp
    ├── test_collisiondetector.cpp
    └── test_lane.cpp
```

---

## 3. Otwieranie projektu w Qt Creator

1. Uruchom **Qt Creator**.
2. Kliknij **File → Open File or Project…**
3. Nawiguj do folderu `FrogOnTheRoad/` i wybierz plik **`CMakeLists.txt`**.
4. Qt Creator zapyta o **kit** (kompilator + Qt) – wybierz np. `Desktop Qt 6.x.x GCC 64bit`.
5. Kliknij **Configure Project**.
6. Qt Creator skonfiguruje CMake i pobierze Google Test z internetu  
   *(FetchContent – wymaga połączenia przy pierwszym buildzie)*.

---

## 4. Budowanie

### Aplikacja główna
- Upewnij się, że w pasku na dole widnieje target **`FrogOnTheRoad`**.
- Kliknij zieloną strzałkę ▶ **Build & Run** (Ctrl+R).

### Testy Google Test
- Zmień aktywny target na **`FrogTests`**  
  *(lewy dolny róg Qt Creator → kliknij nazwę targetu)*.
- Kliknij **Build** (Ctrl+B).
- Wyniki testów pojawią się w zakładce **Test Results** lub uruchom z terminala:
  ```bash
  cd build/
  ctest --output-on-failure
  ```

---

## 5. Jeśli CMake nie znajdzie Qt

Dodaj ścieżkę do Qt w ustawieniach Qt Creator:  
**Edit → Preferences → Kits → Qt Versions → Add…**  
Wskaż np. `~/Qt/6.x.x/gcc_64/bin/qmake`.

Alternatywnie przy wywołaniu cmake z terminala:
```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH=~/Qt/6.x.x/gcc_64
cmake --build build
```

---

## 6. Co już działa w tej wersji (Etap 1)

| Funkcja | Stan |
|---------|------|
| Menu z wyborem trybu | ✅ działa |
| Żaba porusza się klawiszami | ✅ działa |
| Samochody jeżdżą po pasach | ✅ działa |
| Detekcja kolizji | ✅ działa |
| Punkty za dotarcie do góry | ✅ działa |
| Game Over po kolizji | ✅ działa (powrót do menu po 2 sek) |
| Skórki (placeholder grafiki) | ✅ kompiluje się |
| AI Controller | ⚙️ stub – zawsze idzie w górę |
| Dźwięk (AudioManager) | ⚙️ stub – `qDebug()` zamiast dźwięku |
| Zapis rekordu do pliku | ❌ TODO Etap 2 |
| Prawdziwe PNG sprites | ❌ TODO Etap 2 |
| Pełny Q-learning AI | ❌ TODO Etap 2 |

---

## 7. Podział pracy (propozycja)

| Osoba | Odpowiedzialność |
|-------|-----------------|
| **Osoba 1** | `Game`, `Lane`, `Car`/`SmallCar`/`Truck`/`SUV` – logika ruchu i spawnu |
| **Osoba 2** | `GameWindow`, `MenuScreen`, grafika (PNG sprites, tło) |
| **Osoba 3** | `AIController` (Q-learning), `ScoreManager` zapis/odczyt, testy |

---

## 8. Czyszczenie przed zipowaniem (do oddania)

Usuń foldery generowane przez build, żeby zip był lekki:
```bash
rm -rf build/
rm -rf .qtcreator/
```
Lub w Qt Creator: **Build → Clean All**.
