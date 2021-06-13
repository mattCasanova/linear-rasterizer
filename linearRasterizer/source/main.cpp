
#define WIN32_EXTRA_LEAN
#define NOMINMAX
#include <Windows.h>

#include "Window.h"

void update(Gfx::Window& window, DWORD& oldTime);

int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
    
    Gfx::Window window;
    if (!window.create(instance, "Linear Rasterizer", 800, 600))
        return 1;

    DWORD oldTime = ::timeGetTime();

    while (window.isRunning())
    {
        update(window, oldTime);
        window.present();
    }

    return 0;
}

void update(Gfx::Window& window, DWORD& oldTime)
{
    static const int TICKS_PER_SEC = 1000;
    static const float FPS_30 = TICKS_PER_SEC / 30.f;

    window.processMessages();

    DWORD newTime;
    while (true)
    {
        newTime = ::timeGetTime();
        if ((newTime - oldTime) < FPS_30)
            continue;

        oldTime = newTime;
        break;
    }
}