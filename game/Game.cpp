#include "Game.hpp"

bebop::snake2d::game::Game::Game(int width, int height)
    : width(width), height(height), snake({5, 10}, {1, 0}, 5), window(width, height, "Snake2d")
{
    int spawned = 0;
    while (spawned < FRUIT_COUNT)
    {
        fruits[spawned] = spawnFruit();
        ++spawned;
    }
}

void bebop::snake2d::game::Game::run()
{
    auto lastTime = std::chrono::steady_clock::now();

    while (window.isOpen())
    {
        auto now = std::chrono::steady_clock::now();
        float dt = std::chrono::duration<float>(now - lastTime).count();
        lastTime = now;

        window.processEvents(
            [&](KeySym key)
            {
                switch (key)
                {
                    case XK_Up:
                        snake.setDirection({0, -1});
                        break;
                    case XK_Down:
                        snake.setDirection({0, 1});
                        break;
                    case XK_Left:
                        snake.setDirection({-1, 0});
                        break;
                    case XK_Right:
                        snake.setDirection({1, 0});
                        break;
                    case XK_r:
                        restart();
                        break;
                }
            });

        if (isGameOver)
        {
            gameOver();
            window.update();
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
            continue;
        }

        if (snake.eatsItself())
        {
            isGameOver = true;
            continue;
        }

        int fruitIndex = snakeEatsFruit();
        if (fruitIndex != -1)
        {
            ++score;
            fruits[fruitIndex] = spawnFruit();
            snake.grow();
        }

        snake.move(dt);

        window.clear(WINDOW_BACKGROUND_COLOR);

        RenderSnake::render(snake, window);

        std::for_each(fruits.begin(), fruits.end(),
                      [&](const auto& fruit) { RenderFruit::render(fruit, window); });

        showScore();

        window.update();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));  // ~60 FPS
    }
}

int bebop::snake2d::game::Game::snakeEatsFruit()
{
    auto it = std::find(fruits.begin(), fruits.end(), snake.segments.front());
    return it == fruits.end() ? -1 : std::distance(fruits.begin(), it);
}

bebop::snake2d::game::Fruit bebop::snake2d::game::Game::spawnFruit()
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> xdist(0, width / (CIRCLE_RADIUS * 2) - 1);
    std::uniform_int_distribution<int> ydist(0, height / (CIRCLE_RADIUS * 2) - 1);

    Fruit pos{xdist(rng), ydist(rng)};

    auto segmentsFound = std::find(snake.segments.begin(), snake.segments.end(), pos);
    auto spawnedFound = std::find(fruits.begin(), fruits.end(), pos);

    bool collides = segmentsFound != snake.segments.end() || spawnedFound != fruits.end();

    while (collides)
    {
        pos = Vec2{xdist(rng), ydist(rng)};
        auto segmentsFound = std::find(snake.segments.begin(), snake.segments.end(), pos);
        auto spawnedFound = std::find(fruits.begin(), fruits.end(), pos);
        collides = segmentsFound != snake.segments.end() || spawnedFound != fruits.end();
    }
    return pos;
}

void bebop::snake2d::game::Game::showScore()
{
    std::string scoreText = "Score: " + std::to_string(score);
    int textX = width - 200;
    int textY = 10;

    window.drawText(textX, textY, scoreText, TEXT_COLOR);
}

void bebop::snake2d::game::Game::gameOver()
{
    window.clear(GAME_OVER_BACKGROUND_COLOR);

    constexpr const char* text = "Game Over! Press R to Restart";
    int textX = width / 2 - 200;
    int textY = height / 2;

    window.drawText(textX, textY, text, TEXT_COLOR);
}

void bebop::snake2d::game::Game::restart()
{
    snake = Snake({5, 10}, {1, 0}, 5);
    std::fill(fruits.begin(), fruits.end(), Fruit{0, 0});

    int spawned = 0;
    while (spawned < FRUIT_COUNT)
    {
        fruits[spawned] = spawnFruit();
        ++spawned;
    }

    isGameOver = false;
}
