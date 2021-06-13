#include "Color.h"

#include <algorithm>


namespace Gfx
{
Color::Color(
    const unsigned char r /*= 0*/, 
    const unsigned char g /*= 0*/,
    const unsigned char b /*= 0*/, 
    const unsigned char a /*= UCHAR_MAX*/
)
{
    set(r, g, b, a);
}

Color::Color(const Color& rhs)
{
    set(rhs.mColors, MAX_COLORS);
}

Color& Color::operator=(const Color& rhs)
{
    set(rhs.mColors, MAX_COLORS);
    return *this;
}

Color Color::operator*(const Color& rhs) const
{
    unsigned char colors[MAX_COLORS];
    for (int i = 0; i < MAX_COLORS; ++i)
    {
        colors[i] = std::min(UCHAR_MAX, static_cast<int>(mColors[i]) * rhs.mColors[i]);
    }

    return Color(colors[R], colors[G], colors[B], colors[A]);
}

unsigned char Color::r() const
{
    return mColors[R];
}

unsigned char Color::g() const
{
    return mColors[G];
}

unsigned char Color::b() const
{
    return mColors[B];
}
unsigned char Color::a() const
{
    return mColors[A];
}

unsigned char& Color::r()
{
    return mColors[R];
}

unsigned char& Color::g()
{
    return mColors[G];
}

unsigned char& Color::b()
{
    return mColors[B];
}
unsigned char& Color::a()
{
    return mColors[A];
}

void Color::set(
    const unsigned char r /*= 0*/, 
    const unsigned char g /*= 0*/, 
    const unsigned char b /*= 0*/, 
    const unsigned char a /*= UCHAR_MAX*/
)
{
    mColors[R] = r;
    mColors[G] = g;
    mColors[B] = b;
    mColors[A] = a;
}

void Color::set(const unsigned char* colors, const unsigned count)
{
    for (unsigned i = 0; i < count; ++i)
    {
        mColors[i] = colors[i];
    }
}
} //end namespace Gfx