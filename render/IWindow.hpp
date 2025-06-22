#ifndef BEBOP_SNAKE_2D_RENDER_IWINDOW_HPP
#define BEBOP_SNAKE_2D_RENDER_IWINDOW_HPP

#include <cstdint>
#include <functional>
#include <string>

namespace bebop::snake2d::render
{

enum class Key
{
    UNKNOWN,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ESCAPE,
    p,
    r
};

using KeyCallback = std::function<void(Key)>;

struct IWindow
{
    /**
     * Clear the window with the given color
     * @param color The color to be cleared with
     */
    virtual void clear(std::uint32_t) = 0;

    /**
     * Draws a circle on the window
     * @param cx The x coordinate of the center
     * @param cy The y coordinate of the center
     * @param radius The radius of the circle
     * @param color The color of the circle
     */
    virtual void drawCircle(int x, int y, int radius, std::uint32_t color) = 0;

    /**
     * Draws a text on the window
     * @param x The x coordinate of the text
     * @param y The y coordinate of the text
     * @param text The text
     * @param color The color
     */
    virtual void drawText(int x, int y, const std::string& text, std::uint32_t color) = 0;

    /**
     * Update is called to flush the display
     */
    virtual void update() = 0;

    /**
     * Process window events
     * @param onKeyPress The listener possibly nullptr, passed to this function.
     */
    virtual void processEvents(const KeyCallback& callback = nullptr) = 0;

    /**
     * Closes the window
     */
    virtual void close() = 0;

    /**
     * Boolean reporthing whether the window is still open... used in loops
     */
    virtual bool isOpen() const = 0;
};

}  // namespace bebop::snake2d::render

#endif  // BEBOP_SNAKE_2D_RENDER_IWINDOW_HPP