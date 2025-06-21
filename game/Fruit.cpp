#include "Fruit.hpp"

void bebop::snake2d::game::RenderFruit::render(const Fruit& fruit, render::XWindow& window)
{
    window.drawCircle(fruit.x * CIRCLE_RADIUS * 2, fruit.y * CIRCLE_RADIUS * 2, CIRCLE_RADIUS, FRUIT_COLOR);
}
