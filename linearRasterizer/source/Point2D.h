#ifndef POINT2D_H
#define POINT2D_H

namespace Gfx 
{

/*
* @class Point2D
* @brief Simple 2D point/vector class
*/
class Point2D
{
public:
    explicit inline Point2D(const float xx = 0.0f, const float yy = 0.0f);
    inline Point2D(const Point2D& rhs);

    inline Point2D& operator=(const Point2D& rhs);
    inline Point2D operator-(const Point2D& rhs) const;

    inline float crossZ(const Point2D& rhs) const;

    float x, y;
};

explicit inline Point2D::Point2D(const float xx, const float yy): x(xx), y(yy) {}
explicit inline Point2D::Point2D(const Point2D& rhs) : x(rhs.x), y(rhs.y) {}

inline Point2D& Point2D::operator=(const Point2D& rhs)
{
    x = rhs.x;
    y = rhs.y;
    return *this;
}

inline Point2D Point2D::operator-(const Point2D& rhs) const
{
    return Point2D(x - rhs.x, y - rhs.y);
}

inline float Point2D::crossZ(const Point2D& rhs) const
{
    return x * rhs.y - y * rhs.x;
}


} //end namespace gfx

#endif // !POINT_2D_H
