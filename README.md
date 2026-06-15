# Zaba-na-ulicy

Klasyczna gra zręcznościowa inspirowana kultowym "Froggerem", napisana w języku C++ z wykorzystaniem frameworka Qt. Przeprowadź żabę przez ruchliwą autostradę pełną rozpędzonych samochodów, zdobywaj punkty i odblokowuj nowe wyglądy postaci!

## 🎮 O grze

Celem gry jest dotarcie na drugą stronę wielopasmowej jezdni, unikając zderzenia z pojazdami. Poziom punktacji zależy od postępu na planszy – im bliżej mety, tym wyższy wynik. 

Projekt powstał specjalnie na zajęcia z programowania obiektowego na Politechnice Warszawskiej.

## ✨ Główne funkcjonalności

* **Dwa tryby rozgrywki:**
    * **Gra ręczna (Player):** Tradycyjne sterowanie klawiaturą, walka o jak najwyższy wynik i bicie własnych rekordów.
    * **Tryb AI (Trening):** Zaimplementowany algorytm uczenia ze wzmocnieniem (*Q-learning*). Obserwuj, jak sztuczna inteligencja z każdym epizodem uczy się unikać aut i optymalizuje swoją ścieżkę do mety!
* **Zróżnicowane pojazdy:** Trzy klasy samochodów o różnych gabarytach .
* **Menedżer Audio:** Wbudowana obsługa muzyki i efektów dźwiękowych w menu oraz podczas rozgrywki.

## 🕹️ Sterowanie

* **W** - ruch do przodu
* **S** - ruch do tyłu
* **A/D** - ruch na boki
* **ESC** - natychmiastowy powrót do menu głównego

## 🛠️ Technologie i architektura

* **Język:** C++ (standard C++17/C++20)
* **Framework UI/Grafika:** Qt (QGraphicsScene, QPainter, Qt Widgets)
* **System budowania:** CMake
* **Architektura:** Obiektowa (OOP), z wyraźnym podziałem na logikę gry, interfejs użytkownika oraz niezależne moduły.

## 🚀 Jak uruchomić projekt lokalnie?

1. Upewnij się, że masz zainstalowane środowisko **Qt Creator** oraz system **CMake**.
2. Sklonuj repozytorium na swój komputer:
   ```bash
   git clone [https://github.com/TwojNick/Zaba-na-ulicy.git](https://github.com/TwojNick/Zaba-na-ulicy.git)