#include "XWindow.hpp"

bebop::snake2d::render::XWindow::XWindow(int width, int height, const char* title)
    : width(width), height(height), pixels(width * height)
{
    Display* display = xdisplay.get();

    int screen = DefaultScreen(display);

    window = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0, width, height, 1,
                                 BlackPixel(display, screen), WhitePixel(display, screen));

    XStoreName(display, window, title);
    XSelectInput(display, window, ExposureMask | KeyPressMask | StructureNotifyMask);

    gc = XCreateGC(display, window, 0, nullptr);

    // Create the backBuffer pixmap for double buffering
    backBuffer = XCreatePixmap(display, window, width, height,
                               DefaultDepth(display, screen));

    // Create the XImage to map your pixels vector (if you use it for software rendering)
    ximage = XCreateImage(display, DefaultVisual(display, screen), DefaultDepth(display, screen),
                          ZPixmap, 0, reinterpret_cast<char*>(pixels.data()),
                          width, height, 32, 0);

    XMapWindow(display, window);
}

bebop::snake2d::render::XWindow::~XWindow()
{
     Display* display = xdisplay.get();
    if (ximage) {
        ximage->data = nullptr;
        XDestroyImage(ximage);
    }

    if (backBuffer) {
        XFreePixmap(display, backBuffer);
    }

    if (gc) {
        XFreeGC(display, gc);
    }
}

void bebop::snake2d::render::XWindow::processEvents(const KeyCallback& onKeyPress)
{
    while (XPending(xdisplay.get()))
    {
        XEvent event;
        XNextEvent(xdisplay.get(), &event);

        if (event.type == KeyPress)
        {
            KeySym keysym = XLookupKeysym(&event.xkey, 0);
            if (keysym == XK_Escape)
            {
                open = false;
                break;
            }
            onKeyPress(keysym);
        }
        else if (event.type == Expose)
        {
            update();
        }
    }
}

void bebop::snake2d::render::XWindow::update()
{
    Display* display = xdisplay.get();

    // Copy the backBuffer pixmap to the actual window in one atomic operation
    XCopyArea(display, backBuffer, window, gc, 0, 0, width, height, 0, 0);

    XFlush(display);
}

bool bebop::snake2d::render::XWindow::isOpen() const
{
    return open;
}

void bebop::snake2d::render::XWindow::clear(std::uint32_t color)
{
    Display* display = xdisplay.get();

    XSetForeground(display, gc, color);
    XFillRectangle(display, backBuffer, gc, 0, 0, width, height);}

void bebop::snake2d::render::XWindow::setPixel(int x, int y, std::uint32_t color)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;
    pixels[y * width + x] = color;
}

void bebop::snake2d::render::XWindow::drawCircle(int cx, int cy, int radius, std::uint32_t color)
{
    Display* display = xdisplay.get();

    XSetForeground(display, gc, color);
    XFillArc(display, backBuffer, gc, cx - radius, cy - radius, radius * 2, radius * 2, 0, 360 * 64);
}

void bebop::snake2d::render::XWindow::drawText(int x, int y, const std::string& text, std::uint32_t color)
{
    Display* display = xdisplay.get();

    // Set the foreground color for text drawing (convert uint32_t color to XColor)
    XSetForeground(display, gc, color);

    // Draw text to the backBuffer pixmap, NOT the window
    XDrawString(display, backBuffer, gc, x, y, text.c_str(), static_cast<int>(text.size()));
}
