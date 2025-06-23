#include "Win32Window.hpp"

bebop::snake2d::render::Win32Window* bebop::snake2d::render::Win32Window::instance = nullptr;

bebop::snake2d::render::Win32Window::Win32Window(int width, int height, const char* title)
{
    instance = this;

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = "Snake2DWindowClass";

    RegisterClass(&wc);

    hwnd = CreateWindowEx(0, wc.lpszClassName, title,
                          WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX), CW_USEDEFAULT,
                          CW_USEDEFAULT, width + 16, height + 39, nullptr, nullptr,
                          GetModuleHandle(nullptr), nullptr);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    hdc = GetDC(hwnd);
    memDC = CreateCompatibleDC(hdc);

    ZeroMemory(&bitmapInfo, sizeof(bitmapInfo));
    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.bmiHeader.biWidth = width;
    bitmapInfo.bmiHeader.biHeight = -height;  // top-down bitmap
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;

    void* bits;
    bitmap = CreateDIBSection(hdc, &bitmapInfo, DIB_RGB_COLORS, &bits, nullptr, 0);
    SelectObject(memDC, bitmap);
}

bebop::snake2d::render::Win32Window::~Win32Window()
{
    DeleteObject(bitmap);
    DeleteDC(memDC);
    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);
    UnregisterClass("Snake2DWindowClass", GetModuleHandle(nullptr));
}

void bebop::snake2d::render::Win32Window::clear(std::uint32_t color)
{
    RECT rect;
    GetClientRect(hwnd, &rect);

    HBRUSH brush = CreateSolidBrush(toColorRef(color));
    FillRect(memDC, &rect, brush);
    DeleteObject(brush);
}

void bebop::snake2d::render::Win32Window::drawCircle(int x, int y, int radius, std::uint32_t color)
{
    HBRUSH brush = CreateSolidBrush(toColorRef(color));
    HBRUSH oldBrush = (HBRUSH)SelectObject(memDC, brush);

    HPEN pen = CreatePen(PS_SOLID, 1, toColorRef(color));
    HPEN oldPen = (HPEN)SelectObject(memDC, pen);

    Ellipse(memDC, x - radius, y - radius, x + radius, y + radius);

    SelectObject(memDC, oldBrush);
    SelectObject(memDC, oldPen);
    DeleteObject(brush);
    DeleteObject(pen);
}

void bebop::snake2d::render::Win32Window::drawText(int x, int y, const std::string& text,
                                                   std::uint32_t color)
{
    SetBkMode(memDC, TRANSPARENT);
    SetTextColor(memDC, toColorRef(color));
    TextOutA(memDC, x, y, text.c_str(), static_cast<int>(text.size()));
}

void bebop::snake2d::render::Win32Window::update()
{
    int width = bitmapInfo.bmiHeader.biWidth;
    int height = -bitmapInfo.bmiHeader.biHeight;  // Negative height = top-down DIB

    BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);
}

void bebop::snake2d::render::Win32Window::processEvents(const KeyCallback& callback)
{
    MSG msg = {};
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_KEYDOWN)
        {
            Key key = mapVirtualKey(msg.wParam);
            if (key != Key::UNKNOWN && callback)
                callback(key);
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void bebop::snake2d::render::Win32Window::close()
{
    if (open)
    {
        open = false;
        PostMessage(hwnd, WM_CLOSE, 0, 0);
    }
}

bool bebop::snake2d::render::Win32Window::isOpen() const
{
    return open;
}

LRESULT bebop::snake2d::render::Win32Window::handleMessage(HWND hwnd, UINT uMsg, WPARAM wParam,
                                                           LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            open = false;
            PostQuitMessage(0);
            return 0;

        case WM_CLOSE:
            open = false;
            DestroyWindow(hwnd);  // triggers WM_DESTROY next
            return 0;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_SIZE:
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}


bebop::snake2d::render::Key bebop::snake2d::render::Win32Window::mapVirtualKey(WPARAM wParam)
{
    using Key = bebop::snake2d::render::Key;

    switch (wParam)
    {
        case VK_UP:
            return Key::UP;
        case VK_DOWN:
            return Key::DOWN;
        case VK_LEFT:
            return Key::LEFT;
        case VK_RIGHT:
            return Key::RIGHT;
        case VK_ESCAPE:
            return Key::ESCAPE;
        case 'P':
            return Key::p;
        case 'R':
            return Key::r;
        default:
            return Key::UNKNOWN;
    }
}

COLORREF bebop::snake2d::render::Win32Window::toColorRef(std::uint32_t argb)
{
    BYTE red = (argb >> 16) & 0xFF;
    BYTE green = (argb >> 8) & 0xFF;
    BYTE blue = argb & 0xFF;
    return RGB(red, green, blue);  // COLORREF is 0x00BBGGRR
}

LRESULT bebop::snake2d::render::Win32Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                                                        LPARAM lParam)
{
    if (instance)
    {
        return Win32Window::instance->handleMessage(hwnd, uMsg, wParam, lParam);
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
