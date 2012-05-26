/*************************************************************************************************\
*                                                                                                 *
* "geometry.h" -                                                                                  *
*                                                                                                 *
*       Author - Tom McDonnell 2003                                                               *
*                                                                                                 *
\*************************************************************************************************/

#ifndef GEOMETRY_H
#define GEOMETRY_H

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#include <TomsLibrary/vector.h>

// GLOBAL TYPE DEFINIIONS /////////////////////////////////////////////////////////////////////////

namespace TomsLibGeometry
{

 /*
  * Rectangle class.
  */
 class rect
 {
  public:
    double l, r, t, b; // x left, x right, y top, y bottom;
 };

 /*
  * Line representation.
  */
 enum lineRep {YeqMxPlusC, XeqMyPlusC};

 /*
  * used for function whichLinesYeqMxPlusC().
  */
 enum possibilities {both, first, second, neither};

 /*
  * If rep = YeqMxPlusC, line is defined by y = mx + c.
  * If rep = XeqMyPlusC, line is defined by x = my + c.
  * This is done to avoid floating point errors as m approaches infinity.
  * To minimise floating point errors, m should always fall within range (-1, 1).
  */
 class line
 {
  public:
    line(double m1 = 0, double c1 = 0, lineRep r = YeqMxPlusC) {m = m1; c = c1; rep = r;}

    double m, c;
    lineRep rep;
 };

} // end namespace TomsLibGeometry

// GLOBAL FUNCTION DECLARATIONS ///////////////////////////////////////////////////////////////////

namespace TomsLibGeometry
{
 using namespace TomsLibVector;

 enum possibilities whichLinesYeqMxPlusC(line, line);

 bool parallel(line, line);

 line findLineEquation(rec2vector, rec2vector);

 rec2vector intersection(line, line);
 rec2vector lineIntersectRect(rec2vector, rec2vector, rect);

 rec2vector (*lineIntersectCirc(const line &, const rec2vector &, const double &))[2];

 bool operator>(rec2vector, line);
 bool operator<(rec2vector, line);

}

// GLOBAL INLINE FUNCTION DEFINITIONS /////////////////////////////////////////////////////////////

namespace TomsLibGeometry
{
 using namespace TomsLibVector;

 /*
  * Return the angle between the line p1->p2 and the horizontal.
  */
 inline double angle(rec2vector p1, rec2vector p2)
 {
    return atan2(p2.y - p1.y, p2.x - p1.x);
 }

 /*
  *
  */
 inline bool insideRect(rec2vector p, rect r)
 {
    if (   r.l < p.x && p.x < r.r
        && r.b < p.y && p.y < r.t) return true;
    else                           return false;
 }

 /*
  *
  */
 inline void surrPointWithRect(rec2vector p, rec2vector rDim, rect &r)
 {
    r.l = p.x - rDim.x;
    r.r = p.x + rDim.x;
    r.t = p.y + rDim.y;
    r.b = p.y - rDim.y;
 }

 inline bool operator<(line l, rec2vector p) {return p > l;}
 inline bool operator>(line l, rec2vector p) {return p < l;}

} // end namespace TomsLibGeometry

#endif

/*****************************************END*OF*FILE*********************************************/
