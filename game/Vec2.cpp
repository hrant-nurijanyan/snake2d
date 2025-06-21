#include "Vec2.hpp"

bool bebop::snake2d::game::Vec2::operator==(const Vec2& other) const
{
    return x == other.x && y == other.y;
}

bebop::snake2d::game::Vec2& bebop::snake2d::game::Vec2::operator+=(const Vec2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}
