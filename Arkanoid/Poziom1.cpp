﻿/** \file Poziom1.h
* Odpowiada za pierwszy poziom
*/
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "MainMenu.h"
#include "Poziom1.h"
#include <windows.h>
#include <cstdlib>
#include <SFML/Audio.hpp>
#include "Buff.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;

/// Szablon klasy
/** 
* Funkcja z 2 argumentami szablonowymi, uniwersalna funckja, pozwoli nam sprawdzać kolizje miedzy roznymi obiektami
* Zwraca dana krawedz obiektu w pixelach
*/
template <class T1, class T2> bool isIntersecting1(T1& A, T2& B)
{
    return A.right() >= B.left() && A.left() <= B.right() && A.bottom() >= B.top() && A.top() <= B.bottom();
}
/// collisionTest1
/**
* Funckja z dwoma parametrami sprawdzajaca kolizje paletki i pileczki
* Sprawdza czy oba obiekty na siebie nachodza
* Zabawa grawitacja, losujemy w jaki sposob ma sie odbic pileczka od paletki
*/
bool collisionTest1(Paddle& paddle, Ball& ball)
{
    if (!isIntersecting1(paddle, ball))
        return false;

    srand(time(NULL));
    int liczba = (rand() % 3) + 1;
    switch (liczba)
    {
    case 1:
        ball.moveUp();
        break;
    case 2:
        ball.moveUp();
        break;
    case 3:
        ball.moveUp();
        break;
    }
    
}
/// collisionTest1
/**
* Funckja z dwoma parametrami sprawdzajaca kolizje bloku i pileczki
* Sprawdza czy oba obiekty na siebie nachodza
* Przy odpowiednim warunku zniszcz blok
* Zmienne float z dwoma metodami klasy
* Instrukcja warunkowa, sprawdza w jaki sposob powinna odbic sie pilka
*/
bool collisionTest1(Block& block, Ball& ball)
{
    if (!isIntersecting1(block, ball))
        return false;

    block.destroy();

    float overlapLeft{ ball.right() - block.left() };
    float overlapRight{ block.right() - ball.left() };

    float overlapTop{ ball.bottom() - block.top() };
    float overlapBottom{ block.bottom() - ball.top() };

    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

    float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
    float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

    if (abs(minOverlapX) < abs(minOverlapY))
    {
        ballFromLeft ? ball.moveLeft() : ball.moveRight();
    }
    else
    {
        ballFromTop ? ball.moveUp() : ball.moveDown();
    }
}
/// isGameOver1
/**
* Instrukcja warunkowa, sprawdza czy pilka spadla na dol planszy
*/
bool isGameOver1(Ball& ball)
{
    if (ball.bottom() >= 600)
    {
        return true;
    }
    else
    {
        return false;
    }
}


/// Start
/**
* Obiekt klasy o dwoch parametrach
* Obiekt klasy o dwoch parametrach
* Stworzenie okna window
* Ustalenie limitu klatek na sekunde
* Stworzenie eventu
* Stworzenie zawartosci bloczkow, okreslaja ich liczbe i wielkosc
* Stworzenie wektora obiektu klasy 
* Implementacja liczby blokow
* Petla for rysujaca blocki na ekranie
* Stworzenie tekstur i dodanie kilku tekstur tla
* Stworzenie obiektu klasy do rysowania obrazu na ekranie
* Ustawienie rozmiaru tla
* Buforowanie dzwieku oraz jego implementacja
* Wlaczenie muzyki
* Petla while, ktora dziala tylko przy wlaczonym oknie menu
* Wyczyszczenie okna, narysowanie obrazu na ekranie, dodanie opcji odpowiadajacej za funkcjonalnosc okna
* Warunek sprawdzajacy czy okno zostalo zamkniete
* Wywolanie funkcji update oraz collisionTest dla pilki i paletki\
* Warunek, ktory sprawdza czy gra zostala przegrana
* Zatrzymanie muzyki, wylaczenie okna
* Stworzenie nowego okna
* Buforowanie nowych dzwiekow i ich implementacja
* Dodanie opoznienia dzwieku i wlaczenie go
* Petla while sprawdza czy nowe okno jest otwarte
* Stworzenie eventu
* Petla while sprawdza czy nowy event jest wlaczony - jesli nie to wylacza okno, jesli jest to czekaj na przycisk i wylacz okno
* Wyczysc ekran, narysuj tlo i wyswietl
* Zwroc wartosc -1
* Petla for, dla ktorej argumentow automatycznie jest przypisany typ
* Warunek, ktory sprawdza kolizje bloku i pileczki, jesli nastapi zmniejsza liczbe blokow
* Automatyczny iterator, usuwa blok w przypadku spelnienia warunku
* Warunek sprawdza czy liczba blokow jest rowna zero
* Otworz nowe okno z tlem i komunikatem
* Zwroc wartosc 2
* Narysuj na ekranie pilke, paletke i bloki
* 
* 
*/

void Poziom1::applyBuff(const Buff& buff, Paddle& paddle, Ball& ball)
{
    switch (buff.getType())
    {
    case Buff::WiderPaddle:
        paddle.setWidth(paddle.getWidth() * 1.5f); // Example of widening the paddle
        break;
    case Buff::MultipleBalls:
        // Logic to add multiple balls
        break;
        // Handle other buffs
    default:
        break;
    }
}


int Poziom1::Start()
{
    Ball ball(300, 200);
    Paddle paddle(400, 550);
    RenderWindow window(VideoMode(800, 600), "Arcanoid - Poziom 1");
    
    window.setFramerateLimit(60);
    Event event;
    unsigned blocksX{ 8 }, blocksY{ 4 }, blockWidth{ 65 }, blockHeight{ 20 };
    vector<Block> blocks;
    vector<Buff> buffs; // Vector to store buffs
    int numberOfBlocks = blocksX * blocksY;

    for (int i = 0; i < blocksY; i++)
    {
        for (int j = 0; j < blocksX; j++)
        {
            blocks.emplace_back((j + 1) * (blockWidth + 20), (i + 2) * (blockHeight + 10), blockWidth, blockHeight);
        }
    }

    Texture Poziom1;
    Poziom1.loadFromFile("Textury/level1.png");

    Sprite sprite1;
    sprite1.setTexture(Poziom1);

    RectangleShape tloPrzegrana;
    tloPrzegrana.setSize(Vector2f(800, 600));
    Texture mainPrzegrana;
    mainPrzegrana.loadFromFile("Textury/przegrana.png");
    tloPrzegrana.setTexture(&mainPrzegrana);

    RectangleShape tloWygrana;
    tloWygrana.setSize(Vector2f(800, 600));
    Texture mainWygrana;
    mainWygrana.loadFromFile("Textury/wygrana.png");
    tloWygrana.setTexture(&mainWygrana);

    Sprite sprite11;
    Sprite sprite111;
    SoundBuffer buffer;
    buffer.loadFromFile("Audio/level1Audio.wav");
    Sound sound;
    sound.setBuffer(buffer);
    sound.play();
    
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        ball.update();
        paddle.update();

        // Update buffs positions
        for (auto& buff : buffs)
        {
            buff.update();
        }

        // Check for collisions between the paddle and buffs
        for (auto& buff : buffs)
        {
            if (paddle.getBounds().intersects(buff.getBounds()))
            {
                applyBuff(buff, paddle, ball);
                // Remove the buff from the game
                buffs.erase(std::remove(buffs.begin(), buffs.end(), buff), buffs.end());
                break;
            }
        }

        // Check for collisions between the ball and blocks
        for (auto& block : blocks)
        {
            if (collisionTest1(block, ball))
            {
                numberOfBlocks--;
                // Check if a buff should be generated
                if (std::rand() % 100 < 30)
                {
                    Buff::Type buffType = static_cast<Buff::Type>(std::rand() % 5); // Updated to include new buffs
                    buffs.emplace_back(buffType, block.getPosition().x, block.getPosition().y);
                }
                break;
            }
        }

        auto iterator = remove_if(begin(blocks), end(blocks), [](Block& block) { return block.isDestroyed(); });
        blocks.erase(iterator, end(blocks));

        if (numberOfBlocks == 0)
        {
            sound.stop();
            window.close();
            RenderWindow Super(VideoMode(800, 600), "Wygrana");
            SoundBuffer bufferW;
            bufferW.loadFromFile("Audio/wygranaAudio.wav");
            Sound soundW;
            soundW.setBuffer(bufferW);
            soundW.play();

            while (Super.isOpen())
            {
                Event aevent;
                while (Super.pollEvent(aevent))
                {
                    if (aevent.type == Event::Closed)
                    {
                        Super.close();
                    }
                    if (aevent.type == Event::KeyPressed)
                    {
                        if (aevent.key.code == Keyboard::Escape)
                        {
                            Super.close();
                        }
                    }
                }
                Super.clear();
                Super.draw(tloPrzegrana);
                Super.display();
            }
            return 2;
        }

        if (isGameOver1(ball) == true)
        {
            sound.stop();
            window.close();
            RenderWindow Super(VideoMode(800, 600), "Przegrana");
            SoundBuffer bufferL;
            bufferL.loadFromFile("Audio/koniecAudio.wav");
            Sound soundL;
            soundL.setBuffer(bufferL);
            soundL.setPlayingOffset(sf::seconds(10.f));
            soundL.play();
            while (Super.isOpen())
            {
                while (Super.isOpen())
                {
                    Event aevent;
                    while (Super.pollEvent(aevent))
                    {
                        if (aevent.type == Event::Closed)
                        {
                            Super.close();
                        }
                        if (aevent.type == Event::KeyPressed)
                        {
                            if (aevent.key.code == Keyboard::Escape)
                            {
                                Super.close();
                            }
                        }
                    }
                    Super.clear();
                    Super.draw(tloPrzegrana);
                    Super.display();
                }
            }
            return -1;
        }

        window.clear();
        window.draw(sprite1);
        window.draw(ball);
        window.draw(paddle);

        for (auto& block : blocks)
        {
            window.draw(block);
        }

        for (auto& buff : buffs)
        {
            window.draw(buff);
        }

        window.display();
    }

    return 0;
}
