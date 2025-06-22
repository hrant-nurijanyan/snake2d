#ifndef BEBOP_SNAKE_2D_GAME_FRUIT_HPP
#define BEBOP_SNAKE_2D_GAME_FRUIT_HPP

#include "../render/IWindow.hpp"
#include "Vec2.hpp"

namespace bebop::snake2d::game
{

/**
 * Fruit is just a Vec2, nothing more
 */
using Fruit = Vec2;

struct RenderFruit
{
    static constexpr auto CIRCLE_RADIUS = 10;
    static constexpr auto FRUIT_COLOR = 0xFFFFFF00;

    /**
     * Renders the fruit on the window
     * @param fruit The fruit going to be rendered
     * @param window The window on which the fruit is going to be rendered
     */
    static void render(const Fruit& fruit, render::IWindow& window);
};
}  // namespace bebop::snake2d::game

#endif  // BEBOP_SNAKE_2D_GAME_FRUIT_HPP