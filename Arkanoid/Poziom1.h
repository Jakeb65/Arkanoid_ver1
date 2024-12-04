/** \file Poziom1.h
* Odpowiada za pierwszy poziom
*/
#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "MainMenu.h"
#include <windows.h>
#include <cstdlib>
#include <SFML/Audio.hpp>
#include "Buff.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class Poziom1 {
public:
    int Start();
    void applyBuff(const Buff& buff, Paddle& paddle, Ball& ball); // Dodaj tê liniê
};
