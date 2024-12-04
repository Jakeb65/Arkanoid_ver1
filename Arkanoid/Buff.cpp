#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Buff : public Drawable
{
public:
    enum Type { Speed, Size, ExtraLife, WiderPaddle, MultipleBalls };

    Buff(Type type, float x, float y);

    void draw(RenderTarget& target, RenderStates state) const override;
    Vector2f getPosition() const;
    Type getType() const;
    FloatRect getBounds() const;
    void update(); // Add this method to update the position
    bool operator==(const Buff& other) const;

private:
    RectangleShape shape;
    Type type;
    float speed{ 2.0f }; // Speed at which the buff falls
};

#include "Buff.h"

Buff::Buff(Type type, float x, float y) : type(type)
{
    shape.setSize(Vector2f(20, 20)); // Example size
    shape.setPosition(x, y);
    // Set the shape color or texture based on the buff type
}

void Buff::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(shape, states);
}

Vector2f Buff::getPosition() const
{
    return shape.getPosition();
}

Buff::Type Buff::getType() const
{
    return type;
}

FloatRect Buff::getBounds() const
{
    return shape.getGlobalBounds();
}

void Buff::update()
{
    shape.move(0, speed); // Move the buff downwards
}

bool Buff::operator==(const Buff& other) const
{
    return this->type == other.type && this->shape.getPosition() == other.shape.getPosition();
}
