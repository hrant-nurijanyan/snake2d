#include "XDisplay.hpp"

bebop::snake2d::render::XDisplay::XDisplay() : display(XOpenDisplay(nullptr))
{
    if(!display)
    {
        throw std::runtime_error("Could not create display");
    }
}

Display* bebop::snake2d::render::XDisplay::get() 
{
    return display;
}

const Display* bebop::snake2d::render::XDisplay::get() const
{
    return display;
}

bebop::snake2d::render::XDisplay::~XDisplay()
{
    XCloseDisplay(display);
    display = nullptr;
}
