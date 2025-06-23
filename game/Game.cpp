#include "Game.hpp"

bebop::snake2d::game::Game::Game(int width, int height)
    : width(width), height(height), snake({10, 10}, {1, 0}, 5)
{
#ifdef PLATFORM_WINDOWS
    window = std::make_unique<render::Win32Window>(width, height, "Snake2D");
#elif defined(PLATFORM_LINUX)
    window = std::make_unique<render::XWindow>(width, height, "Snake2D");
#endif
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

    while (window->isOpen())
    {
        auto now = std::chrono::steady_clock::now();
        float dt = std::chrono::duration<float>(now - lastTime).count();
        lastTime = now;

        window->processEvents(
            [&](render::Key key)
            {
                switch (key)
                {
                    case render::Key::UP:
                        snake.setDirection({0, -1});
                        break;
                    case render::Key::DOWN:
                        snake.setDirection({0, 1});
                        break;
                    case render::Key::LEFT:
                        snake.setDirection({-1, 0});
                        break;
                    case render::Key::RIGHT:
                        snake.setDirection({1, 0});
                        break;
                    case render::Key::p:
                        state =
                            state == GameState::PLAYING ? GameState::PAUSED : GameState::PLAYING;
                        break;
                    case render::Key::r:
                        if (state != GameState::GAME_OVER)
                            break;
                        restart();
                        break;
                    case render::Key::ESCAPE:
                        window->close();
                }
            });

        if (state == GameState::GAME_OVER)
        {
            gameOver();
            window->update();
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
            continue;
        }

        if (snake.eatsItself() || checkSnakeCollisionWithWalls())
        {
            state = GameState::GAME_OVER;
            continue;
        }

        int fruitIndex = snakeEatsFruit();
        if (fruitIndex != -1)
        {
            ++score;
            fruits[fruitIndex] = spawnFruit();
            snake.grow();
        }

        if (state != GameState::PAUSED)
            snake.move(dt);

        window->clear(WINDOW_BACKGROUND_COLOR);

        RenderSnake::render(snake, *window);

        std::for_each(fruits.begin(), fruits.end(),
                      [&](const auto& fruit) { RenderFruit::render(fruit, *window); });

        showScore();

        window->update();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));  // ~60 FPS
    }
}

bool bebop::snake2d::game::Game::checkSnakeCollisionWithWalls()
{
    const int GRID_WIDTH = width / (CIRCLE_RADIUS * 2);
    const int GRID_HEIGHT = height / (CIRCLE_RADIUS * 2);

    const auto& head = snake.head();
    return head.x < 0 || head.x >= GRID_WIDTH || head.y < 0 || head.y >= GRID_HEIGHT;
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

    window->drawText(textX, textY, scoreText, TEXT_COLOR);
}

void bebop::snake2d::game::Game::gameOver()
{
    window->clear(GAME_OVER_BACKGROUND_COLOR);

    constexpr const char* text = "Game Over! Press R to Restart";
    int textX = width / 2 - 200;
    int textY = height / 2;

    window->drawText(textX, textY, text, TEXT_COLOR);
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

    state = GameState::PLAYING;
    score = 0;
}
