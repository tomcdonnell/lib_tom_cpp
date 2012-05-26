/*************************************************************************************************\
*                                                                                                 *
* "geometry.cpp" -                                                                                *
*                                                                                                 *
*         Author - Tom McDonnell 2003                                                             *
*                                                                                                 *
\*************************************************************************************************/

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#include <TomsLibrary/geometry.h>
#include <TomsLibrary/misc.h>

#include <assert.h>

// GLOBAL FUNCTION DEFINITIONS ////////////////////////////////////////////////////////////////////

namespace TomsLibGeometry
{

 /*
  * Return which of the lines l1, l2 are in 'y = mx + c' representation.
  * Answer will be both, first, second, or neither.
  */
 enum possibilities whichLinesYeqMxPlusC(line l1, line l2)
 {
    enum possibilities p;

    // find which of the lines are in y = mx + c representation
         if (l1.rep == YeqMxPlusC && l2.rep == YeqMxPlusC) p = both;
    else if (l1.rep == YeqMxPlusC && l2.rep != YeqMxPlusC) p = first;
    else if (l1.rep != YeqMxPlusC && l2.rep == YeqMxPlusC) p = second;
    else                                                   p = neither;

    return p;
 }

 /*
  *
  */
 bool parallel(line l1, line l2)
 {
    switch (whichLinesYeqMxPlusC(l1, l2))
    {
     case both:    if (l1.m == l2.m       ) return true; break;
     case first:   if (l1.m *  l2.m == 1.0) return true; break;
     case second:  if (l1.m *  l2.m == 1.0) return true; break;
     case neither: if (l1.m == l2.m       ) return true; break;
    }
    return false;
 }

 /*
  *
  */
 line findLineEquation(rec2vector p1, rec2vector p2)
 {
    line l;

    double a = angle(p1, p2);

    if (   -pi / 4 < a && a <= pi / 4  // right quadrant
        || fabs(a) >= (3 * pi / 4)   ) // left  quadrant
    {
       // angle is in right or left quadrant, so build y = mx + c representation
       l.rep = YeqMxPlusC;
       l.m = (p1.x == p2.x)? 0: (p1.x < p2.x)? (p2.y - p1.y) / (p2.x - p1.x):
                                              (p1.y - p2.y) / (p1.x - p2.x);
       l.c = p1.y - l.m * p1.x;
       assert(-1.000001 <= l.m && l.m <= 1.000001);
    }
    else
    {
       // angle is in top or bottom quadrant, so build x = my + c representation
       l.rep = XeqMyPlusC;
       l.m = (p1.y == p2.y)? 0: (p1.y < p2.y)? (p2.x - p1.x) / (p2.y - p1.y):
                                              (p1.x - p2.x) / (p1.y - p2.y);
       l.c = p1.x - l.m * p1.y;
       assert(-1.000001 <= l.m && l.m <= 1.000001);
    }

    return l;
 }

 /*
  *
  */
 rec2vector intersection(line l1, line l2)
 {
    assert(-1.000001 <= l1.m && l1.m <= 1.000001); // allow for rounding errors
    assert(-1.000001 <= l2.m && l2.m <= 1.000001); // allow for rounding errors

    // PROBLEM: If test for parallel lines, then whichLinesYeq...() is invoked twice.  Inefficient.
    //if (parallel(l1, l2))
    //  error("Attempted to find intersection point of parallel lines.");

    // find intersection point
    rec2vector p;
    switch (whichLinesYeqMxPlusC(l1, l2))
    {
     case both:
       p.x = (l2.c - l1.c) / (l1.m - l2.m);
       p.y = l1.m * p.x + l1.c;
       break;

     case first:
       p.x = (l2.c + l2.m * l1.c) / (1 - l1.m * l2.m);
       p.y = l1.m * p.x + l1.c;
       break;

     case second:
       p.x = (l1.c + l1.m * l2.c) / (1 - l1.m * l2.m);
       p.y = l2.m * p.x + l2.c;
       break;

     case neither:
       p.y = (l2.c - l1.c) / (l1.m - l2.m);
       p.x = l1.m * p.y + l1.c;
       break;
    }

    return p;
 }

 /*
  * Find point where line segment begining at p1 and passing through p2
  * intersects with the screen boundary.
  */
 rec2vector lineIntersectRect(rec2vector p1, rec2vector p2, rect r)
 {
    // define rectangle as four lines (top, bottom, left, and right)
    line lineT(0.0, r.t, YeqMxPlusC), // y = 0.0x + r.t
         lineB(0.0, r.b, YeqMxPlusC), // y = 0.0x + r.b
         lineL(0.0, r.l, XeqMyPlusC), // x = 0.0y + r.l
         lineR(0.0, r.r, XeqMyPlusC), // x = 0.0y + r.r
         line;

    // find direction of line segment
    double a = angle(p1, p2);

    // find equation representation of line
    line = findLineEquation(p1, p2);

    // find which sides to test for intersection
    enum {TL, TR, BL, BR} sides;
         if (-pi     < a && a <= -pi / 2) sides = BL;
    else if (-pi / 2 < a && a <=  0     ) sides = BR;
    else if ( 0      < a && a <=  pi / 2) sides = TR;
    else if ( pi / 2 < a && a <=  pi    ) sides = TL;

    // find intersection point
    rec2vector p;
    switch (sides)
    {
     case BL:
       p = intersection(line, lineB);
       if (!(-1.0 <= p.x && p.x <= 1.0))
         p = intersection(line, lineL);
       break;

     case BR:
       p = intersection(line, lineB);
       if (!(-1.0 <= p.x && p.x <= 1.0))
         p = intersection(line, lineR);
       break;

     case TR:
       p = intersection(line, lineT);
       if (!(-1.0 <= p.x && p.x <= 1.0))
         p = intersection(line, lineR);
       break;

     case TL:
       p = intersection(line, lineT);
       if (!(-1.0 <= p.x && p.x <= 1.0))
         p = intersection(line, lineL);
       break;
    }

    return p;
 }

 /*
  * Find point(s) where line 'l' intersects
  * with a circle centred at 'p' with radius 'r'
  */
 rec2vector (*lineIntersectCirc(const line &l, const rec2vector &p, const double &r))[2]
 {
    using TomsLibMisc::error;

    rec2vector *soln = new rec2vector[2];

    double a, b, c, det;

    switch(l.rep)
    {
     case YeqMxPlusC:
       a = -(1 + pow(l.m, 2));
       b = 2.0 * (p.x - l.m * l.c + l.m * p.y);
       c = pow(r, 2) - pow(p.x, 2) - pow(l.c, 2) - pow(p.y, 2) + 2.0 * l.c * p.y;

       det = pow(b, 2) - 4 * a * c;
       if (det < 0)
         error("Determinant less than zero in findWhereP1HitP2() (YeqMxPlusC).");

       soln[0].x = (-b + sqrt(det)) / (2 * a); soln[0].y = l.m * soln[0].x + l.c;
       soln[1].x = (-b - sqrt(det)) / (2 * a); soln[1].y = l.m * soln[1].x + l.c;
       break;

     case XeqMyPlusC:
       a = -(1 + pow(l.m, 2));
       b = 2.0 * (p.y - l.m * l.c + l.m * p.x);
       c = pow(r, 2) - pow(p.y, 2) - pow(l.c, 2) - pow(p.x, 2) + 2.0 * l.c * p.x;

       det = pow(b, 2) - 4 * a * c;
       if (det < 0)
         error("Determinant less than zero in findWhereP1HitP2() (XeqMyPlusC).");

       soln[0].y = (-b + sqrt(det)) / (2 * a); soln[0].x = l.m * soln[0].y + l.c;
       soln[1].y = (-b - sqrt(det)) / (2 * a); soln[1].x = l.m * soln[1].y + l.c;
       break;
    }

    return (rec2vector (*)[2])soln;
 }

 /*
  * If p.y is higher on the y-axis than line l at x = p.x, return true.  Else false.
  */
 bool operator>(rec2vector p, line l)
 {
    bool b;
    switch (l.rep)
    {
     case YeqMxPlusC:
       if (p.y > l.m * p.x + l.c) b = true;
       else                       b = false;
       break;

     case XeqMyPlusC:
       if (p.y > (1.0 / l.m) * p.x + l.c / l.m) b = true;
       else                                     b = false;
       break;
    }
    return b;
 }

 /*
  * If p.y is lower on the y-axis than line l at x = p.x, return true.  Else false.
  */
 bool operator<(rec2vector p, line l)
 {
    bool b;
    switch (l.rep)
    {
     case YeqMxPlusC:
       if (p.y < l.m * p.x + l.c) b = true;
       else                       b = false;
       break;

     case XeqMyPlusC:
       if (p.y < (1.0 / l.m) * p.x + l.c / l.m) b = true;
       else                                     b = false;
       break;
    }
    return b;
 }

} // end namespace TomsLibGeometry

/*****************************************END*OF*FILE*********************************************/
