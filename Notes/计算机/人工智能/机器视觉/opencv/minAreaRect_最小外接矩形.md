# minAreaRect_最小外接矩形

```cpp
RotatedRect rect_tmp2 = minAreaRect(contours2[i]);
```

```cpp
class CV_EXPORTS RotatedRect
{
public:
    //! default constructor
    RotatedRect();
    /** full constructor
    @param center The rectangle mass center.
    @param size Width and height of the rectangle.
    @param angle The rotation angle in a clockwise direction. When the angle is 0, 90, 180, 270 etc.,
    the rectangle becomes an up-right rectangle.
    */
    RotatedRect(const Point2f& center, const Size2f& size, float angle);
    /**
    Any 3 end points of the RotatedRect. They must be given in order (either clockwise or
    anticlockwise).
     */
    RotatedRect(const Point2f& point1, const Point2f& point2, const Point2f& point3);

    /** returns 4 vertices of the rectangle
    @param pts The points array for storing rectangle vertices. The order is bottomLeft, topLeft, topRight, bottomRight.
    */
    void points(Point2f pts[]) const;
    //! returns the minimal up-right integer rectangle containing the rotated rectangle
    Rect boundingRect() const;
    //! returns the minimal (exact) floating point rectangle containing the rotated rectangle, not intended for use with images
    Rect_<float> boundingRect2f() const;
    //! returns the rectangle mass center
    Point2f center;
    //! returns width and height of the rectangle
    Size2f size;
    //! returns the rotation angle. When the angle is 0, 90, 180, 270 etc., the rectangle becomes an up-right rectangle.
    float angle;
};
```