#ifndef WINDOW_H
#define WINDOW_H 

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#define NOMINMAX
#include <windows.h>
#include <string>


namespace Gfx
{

class Color;
class Window
{
public:
    explicit Window();
    ~Window();

    bool create(HINSTANCE instance, const char* name, const unsigned width, const unsigned  height);

    unsigned width() const;
    unsigned height() const;

    void setPixel(const unsigned x, const unsigned y, const Color& color) const;

    void processMessages();
    void present();
    bool isRunning() const;

    const HWND getWindowHandle() const;

private:
    //Prevent copy
    Window(const Window& rhs) = delete;
    Window& operator=(const Window& rhs) = delete;

    bool registerWndClass(HINSTANCE instance);
    void unregisterWndClass();
    void createSecondaryBuffer(const unsigned width, const unsigned height);
    void clearSurface(int clearColor);

    unsigned int mWidth, mHeight;
    bool mIsRunning;

    HWND mHwnd;
    HDC mHdc;
    HINSTANCE mInstance;
    std::string mClassName;

    HBITMAP mBitmap;
    HBITMAP mOldBitmap;
    HDC mBitmapDC;
    unsigned int* mSurface;

};
}

#endif // !WINDOW_H
