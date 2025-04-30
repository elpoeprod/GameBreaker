#include "gamebreaker.hpp"

namespace GameBreaker {
    /**
    * convert degrees to radians or opposite
    * \sa deg - degree/radian
    **/
    double math::degtorad(double deg)
    {
        return deg * M_PI / 180;
    }
    /**
    * returns a length with given direction for x
    * \sa len - length
    * \sa dir - direction
    **/
    double math::lendir_x(double len, int dir)
    {
        return cos(degtorad(dir)) * len;
    }
    /**
    * returns a length with given direction for y
    * \sa len - length
    * \sa dir - direction
    **/
    double math::lendir_y(double len, int dir)
    {
        return sin(degtorad(dir)) * len;
    }
    /**
    * clamps a value between two others
    * \sa val - value that should be clamped
    * \sa minval - minimum value
    * \sa maxval - maximum value
    * \sa if val < minval return minval, else if val>maxval return maxval, else return val
    **/
    double math::clamp(double val, double minval, double maxval)
    {
        return val < minval ? minval : val > maxval ? maxval
                                                    : val;
    } // uhhhh

    /**
    * returns true if point is in rectangle
    * \sa px, py - point coordinates
    * \sa rx*, ry* - x/y of rectangle
    **/
    double math::point_in_rect(double px, double py, double rx1, double ry1, double rx2, double ry2)
    {
        return px > rx1 && py > ry1 && px <= rx2 && py <= ry2;
    }

    int math::round(double x) {
        return (int)std::round(x);
    }
}