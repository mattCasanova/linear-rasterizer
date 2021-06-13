#include "Color.h"

#include <algorithm>


namespace Gfx
{
Color::Color(
    const unsigned char r /*= 0*/, 
    const unsigned char g /*= 0*/,
    const unsigned char b /*= 0*/, 
    const unsigned char a /*= std::numeric_limits<unsigned char>::max()*/
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
        int newColor = std::min(UCHAR_MAX, static_cast<int>(mColors[i]) * rhs.mColors[i]);
        colors[i] = static_cast<unsigned char>(newColor);
    }

    return Color(colors[R], colors[G], colors[B], colors[A]);
}

unsigned int Color::toInt() const
{
    unsigned int color = r() << 16;
    color |= g() << 8;
    color |= b();

    return color;
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
    const unsigned char a /*= std::numeric_limits<unsigned char>::max()*/
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