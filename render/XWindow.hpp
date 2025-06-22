#ifndef BEBOP_SNAKE_2D_RENDER_XWINDOW_HPP
#define BEBOP_SNAKE_2D_RENDER_XWINDOW_HPP

#include <X11/Xutil.h>
#include <stdexcept>
#include <vector>

#include "IWindow.hpp"
#include "XDisplay.hpp"

namespace bebop::snake2d::render
{

/**
 *
 * Struct representing a X11 Window(Linux)
 */
struct XWindow : IWindow
{

    XWindow(int width, int height, const char* title);
    ~XWindow();

    void clear(std::uint32_t color) override;

    void drawCircle(int cx, int cy, int radius, std::uint32_t color) override;
    void drawText(int x, int y, const std::string& text, std::uint32_t color) override;

    void update() override;
    void processEvents(const KeyCallback& onKeyPress = nullptr) override;

    bool isOpen() const;
    void close();

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