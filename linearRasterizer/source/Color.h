#ifndef COLOR_H
#define COLOR_H

#include <limits>

namespace Gfx
{
enum ColorComponent { R = 0, G, B, A };

class Color
{
public: 
    explicit Color(
        const unsigned char r = 0, 
        const unsigned char g = 0, 
        const unsigned char b = 0, 
        const unsigned char a = std::numeric_limits<unsigned char>::max());
    Color(const Color& rhs);
    
    Color& operator=(const Color& rhs);
    Color operator*(const Color& rhs) const;

    unsigned int toInt() const;

    unsigned char r() const;
    unsigned char g() const;
    unsigned char b() const;
    unsigned char a() const;

    unsigned char& r();
    unsigned char& g();
    unsigned char& b();
    unsigned char& a();

    void set(
        const unsigned char r = 0, 
        const unsigned char g = 0, 
        const unsigned char b = 0, 
        const unsigned char a = std::numeric_limits<unsigned char>::max());

private:
    static const unsigned MAX_COLORS = 4;

    void set(const unsigned char* colors, const unsigned count);
    unsigned char mColors[MAX_COLORS];
};

} //end namespace Gfx
#endif // !COLOR_H

