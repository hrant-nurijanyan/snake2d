#ifndef BEBOP_SNAKE_2D_GAME_VEC2_HPP
#define BEBOP_SNAKE_2D_GAME_VEC2_HPP

namespace bebop::snake2d::game
{

/**
 * Simple struct representing a vector in a 2D dimension
 */
struct Vec2
{
    int x, y;

    bool operator==(const Vec2& other) const;
    Vec2& operator+=(const Vec2& other);
};

}  // namespace bebop::snake2d::game

#endif  // BEBOP_SNAKE_2D_GAME_VEC2_HPP