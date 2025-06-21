#ifndef BEBOP_SNAKE_2D_RENDER_XWINDOW_HPP
#define BEBOP_SNAKE_2D_RENDER_XWINDOW_HPP

#include <X11/Xutil.h>
#include <cstdint>
#include <functional>
#include <stdexcept>
#include <vector>

#include "XDisplay.hpp"

namespace bebop::snake2d::render
{

/**
 *
 * Struct representing a X11 Window(Linux)
 */
struct XWindow
{
    /**
     * The key callback function... used to pass as listeners
     */
    using KeyCallback = std::function<void(KeySym)>;

    XWindow(int width, int height, const char* title);
    ~XWindow();

    /**
     * Process window events
     * @param onKeyPress The listener possibly nullptr, passed to this function.
     */
    void processEvents(const KeyCallback& onKeyPress = nullptr);

    /**
     * Update is called to put the ximage on the display and flush it
     */
    void update();

    /**
     * Boolean reporthing whether the window is still open... used in loops
     */
    bool isOpen() const;

    /**
     * Clear the window with the given color
     * @param color The color to be cleared with
     */
    void clear(std::uint32_t color);

    /**
     * Draws a circle on the window
     * @param cx The x coordinate of the center
     * @param cy The y coordinate of the center
     * @param radius The radius of the circle
     * @param color The color of the circle
     */
    void drawCircle(int cx, int cy, int radius, std::uint32_t color);

    /**
     * Draws a text on the window
     * @param x The x coordinate of the text
     * @param y The y coordinate of the text
     * @param text The text
     * @param color The color
     */
    void drawText(int x, int y, const std::string& text, std::uint32_t color);

   private:
    /**
     * Save pixel in the pixels array later to be flushed into the ximage
     * @param x The x coordinate of the pixel
     * @param y The y coordinate of the pixel
     * @param color The color of the pixel
     */
    void setPixel(int x, int y, std::uint32_t color);

   private:
    int width;
    int height;
    std::vector<std::uint32_t> pixels;

    bool open = true;

    XDisplay xdisplay;
    XImage* ximage;
    Window window;

    Pixmap backBuffer;  
    GC gc; 
};

}  // namespace bebop::snake2d::render

#endif  // BEBOP_SNAKE_2D_RENDER_XWINDOW_HPP