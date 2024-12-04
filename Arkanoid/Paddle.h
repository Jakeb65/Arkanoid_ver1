///Paddle.h
/**
 * Plik naglowkowy zawierajacy klase
*/
#pragma once /// paletka
#include <SFML/Graphics.hpp>  

using namespace sf;
using namespace std;
/// Paddle
/**
 * Klasa z odwolaniem do klasy skladowej jezyka sfml zawierajaca funkcje
 * Konstruktory oraz destruktory uzwane do implementacji paletki
 * Implementacje wielkosci paletki szerokosc, wysokosc oraz predkosc
 * Zmienna wektorowa
*/
class Paddle : public Drawable
{
public:
    Paddle(float t_X, float t_Y);
    Paddle() = delete;
    ~Paddle() = default;

    void update();

    float left();
    float right();
    float top();
    float bottom();

    Vector2f getPosition();
    float getWidth() const;
    void setWidth(float width); // Dodaj tê liniê
    FloatRect getBounds() const;

private:
    void draw(RenderTarget& target, RenderStates state) const override;
    RectangleShape shape;
    float paddleWidth{ 80.0f }; // Zmieñ const na zmienn¹
    const float paddleHeight{ 20.0f };
    const float paddleVelocity{ 8.0f };
    Vector2f velocity{ paddleVelocity, 0.f };
};

