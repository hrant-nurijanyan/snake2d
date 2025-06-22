#include "Snake.hpp"

bebop::snake2d::game::Snake::Snake(const Vec2& position, const Vec2& direction, int segmentsCount)
    : direction(direction)
{
    segments.reserve(segmentsCount);
    for (int i = 0; i < segmentsCount; ++i)
    {
        Vec2 segmentPos{position.x - direction.x * i, position.y - direction.y * i};
        segments.emplace_back(segmentPos);
    }
}

const bebop::snake2d::game::Vec2& bebop::snake2d::game::Snake::head() const
{
    return segments.front();
}

void bebop::snake2d::game::Snake::setDirection(const Vec2& newDirection)
{
    if (newDirection.x != 0 && newDirection.x == -direction.x)
        return;
    if (newDirection.y != 0 && newDirection.y == -direction.y)
        return;

    direction = newDirection;
}

void bebop::snake2d::game::Snake::move(float dt)
{
    moveTimer += dt;

    if (moveTimer < MOVE_DELAY)
        return;

    moveTimer = 0.0f;

    if (direction.x == 0 && direction.y == 0)
        return;

    // Move body from tail to front
    for (int i = segments.size() - 1; i > 0; --i)
    {
        segments[i] = segments[i - 1];
    }

    // Move head based on direction
    segments[0] += direction;
}

bool bebop::snake2d::game::Snake::eatsItself() const
{
    return std::find(segments.begin() + 1, segments.end(), head()) != segments.end();
}

void bebop::snake2d::game::Snake::grow()
{
    Vec2 tail = segments.back();
    segments.emplace_back(tail);
}

void bebop::snake2d::game::RenderSnake::render(const Snake& snake, render::IWindow& window)
{
    // Render the head
    Vec2 head{snake.head().x * CIRCLE_RADIUS * 2, snake.head().y * CIRCLE_RADIUS * 2};

    window.drawCircle(head.x, head.y, CIRCLE_RADIUS, RenderSnake::HEAD_COLOR);

    // Render the eyes
    Vec2 leftEye{head.x - EYE_OFFSET_X, head.y};
    Vec2 rightEye{head.x + EYE_OFFSET_X, head.y};

    window.drawCircle(leftEye.x, leftEye.y, EYE_RADIUS, RenderSnake::EYE_COLOR);
    window.drawCircle(rightEye.x, rightEye.y, EYE_RADIUS, RenderSnake::EYE_COLOR);

    // Render the body
    for (int i = 1; i < snake.segments.size(); ++i)
    {
        Vec2 body{snake.segments[i].x * CIRCLE_RADIUS * 2, snake.segments[i].y * CIRCLE_RADIUS * 2};
        window.drawCircle(body.x, body.y, CIRCLE_RADIUS, RenderSnake::BODY_COLOR);
    }
}
