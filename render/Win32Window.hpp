#ifndef BEBOP_SNAKE_2D_RENDER_WIN32WINDOW_HPP
#define BEBOP_SNAKE_2D_RENDER_WIN32WINDOW_HPP

#include "Windows.h"
#include "IWindow.hpp"

namespace bebop::snake2d::render
{

struct Win32Window : IWindow
{
    Win32Window(int width, int height, const char* title);
    ~Win32Window();

    void clear(std::uint32_t color) override;

    void drawCircle(int x, int y, int radius, std::uint32_t color) override;
    void drawText(int x, int y, const std::string& text, std::uint32_t color) override;

    void update() override;
    void processEvents(const KeyCallback& callback = nullptr) override;

    void close() override;
    bool isOpen() const override;

    LRESULT handleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

   private:
    static Key mapVirtualKey(WPARAM wParam);
    static COLORREF toColorRef(std::uint32_t argb);

    HDC hdc;
    HDC memDC;
    HBITMAP bitmap;
    BITMAPINFO bitmapInfo;
    std::vector<std::uint32_t> pixels;

    HWND hwnd;
    bool open = true;
    KeyCallback keyCallback = nullptr;

    static Win32Window* instance;
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};

}  // namespace bebop::snake2d::render

#endif  // BEBOP_SNAKE_2D_RENDER_WIN32WINDOW_HPP