#include "Paddle.h"

Paddle::Paddle(float t_X, float t_Y)
{
    shape.setPosition(t_X, t_Y);
    shape.setSize({ paddleWidth, paddleHeight });
    shape.setFillColor(Color::Red);
    shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
}

void Paddle::update()
{
    shape.move(velocity);

    if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0)
        velocity.x = -paddleVelocity;
    else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < 800)
        velocity.x = paddleVelocity;
    else
        velocity.x = 0;
}

float Paddle::left()
{
    return shape.getPosition().x - shape.getSize().x / 2.f;
}

float Paddle::right()
{
    return shape.getPosition().x + shape.getSize().x / 2.f;
}

float Paddle::top()
{
    return shape.getPosition().y - shape.getSize().y / 2.f;
}

float Paddle::bottom()
{
    return shape.getPosition().y + shape.getSize().y / 2.f;
}

Vector2f Paddle::getPosition()
{
    return shape.getPosition();
}

float Paddle::getWidth() const
{
    return paddleWidth;
}

void Paddle::setWidth(float width) // Implementacja metody setWidth
{
    paddleWidth = width;
    shape.setSize({ paddleWidth, paddleHeight });
}

FloatRect Paddle::getBounds() const
{
    return shape.getGlobalBounds();
}

void Paddle::draw(RenderTarget& target, RenderStates state) const
{
    target.draw(shape, state);
}
