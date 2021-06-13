#include "Window.h"
#include "../resource.h"
#include <cstring>

#include "Color.h"

extern LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

namespace Gfx
{
Window::Window(): 
    mWidth(0), 
    mHeight(0), 
    mIsRunning(false),
    mHwnd(0), mHdc(0), 
    mInstance(0), 
    mClassName("WndClass"), 
    mBitmap(0),
    mOldBitmap(0),
    mBitmapDC(0),
    mSurface(0)
{
}

Window::~Window()
{
    mBitmap = (HBITMAP)::SelectObject(mBitmapDC, mOldBitmap);
    ::DeleteObject(mBitmap);
    ::ReleaseDC(0, mBitmapDC);

    unregisterWndClass();
    ::ReleaseDC(mHwnd, mHdc);
    mIsRunning = false;

    mBitmap = 0;
    mBitmapDC = 0;
    mHdc = 0;
}

unsigned Window::width() const
{
    return mWidth;
}

unsigned Window::height() const
{
    return mHeight;
}

bool Window::isRunning() const
{
    return mIsRunning;
}

bool Window::registerWndClass(HINSTANCE instance)
{
    WNDCLASS wc;

    wc.style = CS_DBLCLKS;
    wc.lpfnWndProc = DefWindowProc;//WinProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = instance;
    wc.hIcon = 0;
    wc.hCursor = ::LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = 0;
    wc.lpszClassName = mClassName.c_str();

    return ::RegisterClass(&wc);
}

void Window::unregisterWndClass()
{
    ::UnregisterClass(mClassName.c_str(), mInstance);
}

bool Window::create(HINSTANCE instance, const char* name, const unsigned width, const unsigned height)
{
    if (!registerWndClass(instance))
        return false;

    HMENU hMenu = ::LoadMenu(instance, MAKEINTRESOURCE(IDR_MENU1));

    mHwnd = ::CreateWindow(
        mClassName.c_str(),
        name,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        width,
        height,
        0,
        hMenu,
        instance,
        0);

    if (!mHwnd)
        return false;

    mHdc = ::GetDC(mHwnd);
    ::ShowWindow(mHwnd, SW_SHOWNORMAL);

    RECT clientArea;
    ::GetClientRect(mHwnd, &clientArea);

    mIsRunning = true;
    mWidth = clientArea.right - clientArea.left;
    mHeight = clientArea.bottom - clientArea.top;
    mInstance = instance;

    createSecondaryBuffer(mWidth, mHeight);
   

    ::UpdateWindow(mHwnd);
    return true;
}

void Window::createSecondaryBuffer(const unsigned width, const unsigned height)
{
    BITMAPINFOHEADER bmpInfo;
    bmpInfo.biSize = sizeof(bmpInfo);
    bmpInfo.biBitCount = 32;
    bmpInfo.biClrImportant = 0;
    bmpInfo.biClrUsed = 0;
    bmpInfo.biCompression = BI_RGB;
    bmpInfo.biWidth = width;
    bmpInfo.biHeight = height;
    bmpInfo.biPlanes = 1;
    bmpInfo.biSizeImage = 0;
    bmpInfo.biXPelsPerMeter = 0;
    bmpInfo.biYPelsPerMeter = 0;

    HDC dc = ::CreateDC("Display", 0, 0, 0);
    mBitmapDC = ::CreateCompatibleDC(dc);

    mBitmap = ::CreateDIBSection(
        mBitmapDC,
        reinterpret_cast<BITMAPINFO*>(&bmpInfo),
        DIB_RGB_COLORS,
        reinterpret_cast<void**>(&mSurface),
        0,
        0
    );
    mOldBitmap = (HBITMAP)::SelectObject(mBitmapDC, mBitmap);
    clearSurface(0xFF);
    
    
    ::DeleteDC(dc);
}

void Window::present()
{
    ::BitBlt(
        mHdc,
        0,
        0,
        mWidth,
        mHeight,
        mBitmapDC,
        0,
        0,
        SRCCOPY
    );
    clearSurface(0xFF);
}

void Window::setPixel(const unsigned x, const unsigned y, const Color& color) const
{
    if (x >= mWidth || y >= mHeight)
        return;

    mSurface[mWidth * (mHeight - 1 - y) + x] = color.toInt();
}

void Window::processMessages()
{
    MSG msg; 
    while (::PeekMessage(&msg, mHwnd, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
            mIsRunning = false;
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }
}

const HWND Window::getWindowHandle() const
{
    return mHwnd;
}

void Window::clearSurface(int clearColor)
{
    std::memset(mSurface, clearColor, sizeof(unsigned) * mWidth * mHeight);
}

} //end namespace Gfx