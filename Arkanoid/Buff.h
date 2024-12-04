#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Buff : public Drawable // Dodaj dziedziczenie po Drawable
{
public:
    enum Type { Speed, Size, ExtraLife, WiderPaddle, MultipleBalls };

    Buff(Type type, float x, float y);

    void draw(RenderTarget& target, RenderStates state) const override; // Dodaj override
    Vector2f getPosition() const;
    Type getType() const;
    FloatRect getBounds() const;
    bool operator==(const Buff& other) const; // Dodaj deklaracjê operatora ==

private:
    RectangleShape shape;
    Type type;
};
