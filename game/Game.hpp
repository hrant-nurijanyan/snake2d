#ifndef BEBOP_SNAKE_2D_GAME_GAME_HPP
#define BEBOP_SNAKE_2D_GAME_GAME_HPP

#include <chrono>
#include <random>
#include <thread>

#include "../render/XWindow.hpp"
#include "Fruit.hpp"
#include "Snake.hpp"
#include "Vec2.hpp"

namespace bebop::snake2d::game
{

/**
 * The game struct holding all game objects and the logic
 */
struct Game
{
    Game(int width, int height);

    /**
     * Run the game
     */
    void run();

   private:
    int width;
    int height;

    static constexpr auto FRUIT_COUNT = 5;
    static constexpr auto CIRCLE_RADIUS = 10;

    static constexpr auto WINDOW_BACKGROUND_COLOR = 0xFF222222;
    static constexpr auto GAME_OVER_BACKGROUND_COLOR = 0xFF111111;

    static constexpr auto TEXT_COLOR = 0xFFFFFFFF;

    /**
     * Check whether the snake eats a fruit
     * @returns The index of the fruit its going to eat, and -1 if no fruit is eaten
     */
    int snakeEatsFruit();

    /**
     * Spawn a fruit in a random free grid and return it
     */
    Fruit spawnFruit();

    /**
     * Shows the score on the top right corner of the screen
     */
    void showScore();

    /**
     * Function that ends the game and shows the game over screen
     */
    void gameOver();

    /**
     * Restart the game
     */
    void restart();

    Snake snake;
    std::array<Fruit, FRUIT_COUNT> fruits;

    bool isGameOver = false;
    int score = 0;

    render::XWindow window;
};

}  // namespace bebop::snake2d::game

#endif  // BEBOP_SNAKE_2D_GAME_GAME_HPP