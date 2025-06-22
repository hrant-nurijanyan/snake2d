#ifndef BEBOP_SNAKE_2D_GAME_SNAKE_HPP
#define BEBOP_SNAKE_2D_GAME_SNAKE_HPP

#include <algorithm>
#include <vector>

#include "../render/IWindow.hpp"
#include "Vec2.hpp"

namespace bebop::snake2d::game
{

/**
 * Struct representing a snake direction and body segments
 */
struct Snake
{
    Snake(const Vec2& position, const Vec2& direction, int segmentsCount);

    /**
     * Get the head of the snake
     * @returns The head of the snake
     */
    const Vec2& head() const;

    /**
     * Set direction of the snake, no opposite direction is allowed
     * @param newDirection The new direction to be set
     */
    void setDirection(const Vec2& newDirection);

    /**
     * Moves the snake based on frame delta passed
     * @param dt The delta time between the frames
     */
    void move(float dt);

    /**
     * Checks whether a snake eats itself
     */
    bool eatsItself() const;

    /**
     * Grows the snake by one segment
     */
    void grow();

    float moveTimer = 0.0f;
    static constexpr auto MOVE_DELAY = 0.1f;

    Vec2 direction;
    std::vector<Vec2> segments;
};

/**
 * Utility class to render a snake
 */
struct RenderSnake
{
    /**
     * Renders the snake on the window
     * @param snake The snake going to be rendered
     * @param window The window on which the snake is going to be rendered
     */
    static void render(const Snake& snake, render::IWindow& window);

   private:
    static constexpr auto CIRCLE_RADIUS = 10;
    static constexpr auto EYE_RADIUS = CIRCLE_RADIUS / 4;
    static constexpr auto EYE_OFFSET_X = CIRCLE_RADIUS / 2;
    static constexpr auto EYE_OFFSET_Y = CIRCLE_RADIUS / 3;

    static constexpr auto HEAD_COLOR = 0xFF00FF00;
    static constexpr auto BODY_COLOR = 0xFF007700;
    static constexpr auto EYE_COLOR = 0xFF000000;
};

}  // namespace bebop::snake2d::game

#endif  // BEBOP_SNAKE_2D_GAME_SNAKE_HPP