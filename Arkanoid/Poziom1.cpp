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

using namespace std;
using namespace sf;

int LevelWidth = 1100;
int LevelHeight = 825;

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
    if (ball.bottom() >= LevelHeight)
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
*/
int Poziom1::Start()
{
    Ball ball(300, 400);
    Paddle paddle(400, 790);
    RenderWindow window(VideoMode(LevelWidth, LevelHeight), "Arcanoid - Poziom 1");
    
    window.setFramerateLimit(80); // Frame rate pozwala na zwiększenie tempa rozgrywki w tym prędkości piłki czy paletki
    Event event;
    unsigned blocksX{ 8 }, blocksY{ 6 }, blockWidth{ 70 }, blockHeight{ 30 };
    vector<Block> blocks;
    int numberOfBlocks = blocksX * blocksY;

    for (int i = 0; i < blocksY; i++)
    {
        for (int j = 0; j < blocksX; j++)
        {
            // Tworzenie bloku tylko na co drugim polu
            if ((i + j) % 2 == 0)  // co drugie pole tworzy blok, reszta jest pusta
            {
                blocks.emplace_back((j + 1) * (blockWidth + 50), (i + 1) * (blockHeight + 25), blockWidth, blockHeight);
            }
        }
    }



    Texture Poziom1;
    Poziom1.loadFromFile("Textury/level1.png");

    Sprite sprite1;
    sprite1.setTexture(Poziom1);

    SoundBuffer buffer;
    buffer.loadFromFile("Audio/level1Audio.wav");
    Sound sound;
    sound.setBuffer(buffer);
    sound.play();
    
    while (window.isOpen())
    {
        window.clear();
        window.draw(sprite1);
        window.pollEvent(event);

        if (event.type == Event::Closed)
        {
            window.close();
            break;
        }
    
        ball.update();
        paddle.update();
        collisionTest1(paddle, ball);
        if (isGameOver1(ball) == true)
        {
            sound.stop();
            window.close();

            return -1;
        }


        for (auto& block : blocks)
        {
            if (collisionTest1(block, ball))
            {
                numberOfBlocks--;
                break;
            }
        }

        auto iterator = remove_if(begin(blocks), end(blocks), [](Block& block) {return block.isDestroyed(); });
        blocks.erase(iterator, end(blocks));

        if (numberOfBlocks == 0)
        {
            sound.stop();
            window.close();

            return 2;
        }
        
        

        window.draw(ball);
        window.draw(paddle);

        for (auto& block : blocks)
        {
            window.draw(block);
        }
        
        window.display();
    }
}


