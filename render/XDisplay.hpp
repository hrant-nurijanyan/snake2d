#ifndef BEBOP_SNAKE_2D_RENDER_XDISPLAY_HPP
#define BEBOP_SNAKE_2D_RENDER_XDISPLAY_HPP

#include <X11/Xlib.h>
#include <stdexcept>

namespace bebop::snake2d::render
{

/**
 * RAII Struct for X11 Display(Linux)
 */
struct XDisplay
{
    XDisplay();
    ~XDisplay();

    Display* get();
    const Display* get() const;

   private:
    Display* display;
};

}  // namespace bebop::snake2d::render

#endif  // BEBOP_SNAKE_2D_RENDER_XDISPLAY_HPP