#include <chrono>
#include <iostream>
#include <thread>
#include "game/Game.hpp"
#include "render/XWindow.hpp"

int main()
{
    bebop::snake2d::game::Game game(800, 600);
    game.run();
    return 0;
}
